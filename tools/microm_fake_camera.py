#!/usr/bin/env python3
"""Fake OFIL micROM camera, for exercising the QGC UI without hardware.

Speaks enough of the camera's UDP protocol to make MicROMController believe it
is talking to a real micROM: answers keepalives, acknowledges photo and video
commands, and remembers zoom / gain / UV colour so the sliders round-trip.

Usage:

    python tools/microm_fake_camera.py            # healthy camera
    python tools/microm_fake_camera.py --no-sd    # camera with no SD card

Then in QGroundControl:

    Settings > General > Enable micROM UV Camera Interface   (restart required)
    Settings > General > micROM Camera IP  ->  127.0.0.1
    Settings > Video   > Video Source      ->  micROM UV Camera

Within one keepalive interval (5 s) the fly view capture widget goes live.
There will be no actual video, which is fine: the widget keys off the selected
source plus the keepalive, not off a running stream.

Protocol notes (see src/MicROM/MicROMController.cc):
  - QGC sends commands to  <camera ip>:4526  from an ephemeral port
  - QGC listens for responses on port 4527, so replies go to 4527 explicitly
    rather than back to the sender's port
  - Commands from QGC are IC_*, responses from the camera are CI_*
"""

import argparse
import socket
import sys

CMD_PORT = 4526   # we listen here
RSP_PORT = 4527   # QGC listens here


class FakeCamera:
    def __init__(self, sd_present=True):
        self.zoom = 0
        self.gain = 130
        self.uv_color = 0
        self.recording = False
        self.sd_present = sd_present

    def handle(self, cmd):
        """Map one IC_ command to a list of CI_ responses."""

        # Keepalive. Answering this is what flips 'connected' to true.
        if cmd == "IC_ALVS":
            return ["CI_ALVR"]

        # QGC answering a keepalive we initiated; nothing to say back.
        if cmd == "IC_ALVR":
            return []

        # Take photo
        if cmd == "IC_KSP":
            if not self.sd_present:
                return ["CI_KSPERR"]
            return ["CI_KSP"]

        # Start/stop video is the same toggle command both ways
        if cmd == "IC_KSV":
            if not self.sd_present:
                return ["CI_KRVERR"]
            self.recording = not self.recording
            return ["CI_KSV"]

        # Setters echo the value back, which is how the UI confirms them
        for prefix, attr, lo, hi in (("IC_MZS",  "zoom",     0, 13),
                                     ("IC_GAS",  "gain",     0, 255),
                                     ("IC_UVCS", "uv_color", 0, 7)):
            if cmd.startswith(prefix):
                try:
                    value = int(cmd[len(prefix):])
                except ValueError:
                    return []
                value = max(lo, min(hi, value))
                setattr(self, attr, value)
                # Response prefix is the command prefix with IC_ -> CI_
                return ["CI_" + prefix[3:] + str(value)]

        # Queries, sent once on connect
        if cmd == "IC_MZQ":
            return ["CI_MZR%d" % self.zoom]
        if cmd == "IC_GAQ":
            return ["CI_GAR%d" % self.gain]
        if cmd == "IC_UVCQ":
            return ["CI_UVCR%d" % self.uv_color]
        if cmd == "IC_SDPQ":
            return ["CI_SDPR%d" % (1 if self.sd_present else 0)]

        return None   # unknown; caller logs it


def main():
    parser = argparse.ArgumentParser(description="Fake OFIL micROM camera for QGC UI testing")
    parser.add_argument("--bind", default="0.0.0.0",
                        help="address to listen on (default: all interfaces)")
    parser.add_argument("--no-sd", action="store_true",
                        help="report no SD card, and fail photo/video with errors")
    args = parser.parse_args()

    cam = FakeCamera(sd_present=not args.no_sd)

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # Deliberately no SO_REUSEADDR: it would let a second copy bind the same
    # port and silently steal datagrams, so a forgotten instance would answer
    # with stale state and look like a UI bug. Better to fail loudly here.
    try:
        sock.bind((args.bind, CMD_PORT))
    except OSError as exc:
        sys.exit("Could not bind %s:%d - %s\n"
                 "Is another copy already running, or QGC using the port?"
                 % (args.bind, CMD_PORT, exc))

    print("Fake micROM listening on %s:%d, replying to port %d"
          % (args.bind, CMD_PORT, RSP_PORT))
    print("SD card: %s" % ("present" if cam.sd_present else "ABSENT"))
    print("Point QGC's 'micROM Camera IP' at this machine (127.0.0.1 if local).")
    print("Ctrl-C to stop.\n")

    while True:
        data, sender = sock.recvfrom(4096)
        cmd = data.decode("latin-1").strip()
        responses = cam.handle(cmd)

        if responses is None:
            print("  <- %-14s (unknown, ignored)" % cmd)
            continue

        for response in responses:
            sock.sendto(response.encode("latin-1"), (sender[0], RSP_PORT))

        # Keepalives are every 5s and would drown out anything interesting
        if cmd != "IC_ALVS":
            state = "rec" if cam.recording else "idle"
            print("  <- %-14s -> %-12s [zoom %d, gain %d, uv %d, %s]"
                  % (cmd, ",".join(responses) or "-",
                     cam.zoom, cam.gain, cam.uv_color, state))


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\nStopped.")
