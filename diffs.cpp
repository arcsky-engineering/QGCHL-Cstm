diff --git a/android/AndroidManifest.xml b/android/AndroidManifest.xml
index 15c35bc6b..886a4d0ad 100644
--- a/android/AndroidManifest.xml
+++ b/android/AndroidManifest.xml
@@ -9,17 +9,15 @@
     <!-- %%INSERT_FEATURES -->
 
     <supports-screens android:largeScreens="true" android:normalScreens="true" android:anyDensity="true" android:smallScreens="true"/>
-    <application android:hardwareAccelerated="true" android:name="org.qtproject.qt5.android.bindings.QtApplication" android:label="-- %%INSERT_APP_NAME%% --" android:extractNativeLibs="true" android:icon="@drawable/icon">
-        <activity android:configChanges="orientation|uiMode|screenLayout|screenSize|smallestScreenSize|layoutDirection|locale|fontScale|keyboard|keyboardHidden|navigation|mcc|mnc|density" android:name="org.mavlink.qgroundcontrol.QGCActivity" android:label="-- %%INSERT_APP_NAME%% --" android:screenOrientation="sensorLandscape" android:launchMode="singleTask" android:keepScreenOn="true">
+    <application android:hardwareAccelerated="true" android:name="org.qtproject.qt5.android.bindings.QtApplication" android:label="Arcsky Control" android:extractNativeLibs="true" android:icon="@drawable/icon">
+        <activity android:configChanges="orientation|uiMode|screenLayout|screenSize|smallestScreenSize|layoutDirection|locale|fontScale|keyboard|keyboardHidden|navigation|mcc|mnc|density" android:name="org.mavlink.qgroundcontrol.QGCActivity" android:label="Arcsky Control" android:screenOrientation="sensorLandscape" android:launchMode="singleTask" android:keepScreenOn="true">
             <intent-filter>
                 <action android:name="android.intent.action.MAIN"/>
                 <category android:name="android.intent.category.LAUNCHER"/>
 
                 <!-- %%QGC_INSERT_ACTIVITY_INTENT_FILTER -->
             </intent-filter>
-
             <!-- %%QGC_INSERT_ACTIVITY_META_DATA -->
-
             <!-- Application arguments -->
             <!-- meta-data android:name="android.app.arguments" android:value="arg1 arg2 arg3"/ -->
             <!-- Application arguments -->
diff --git a/android/GooglePlayDailyIcon.png b/android/GooglePlayDailyIcon.png
old mode 100644
new mode 100755
index 087667afd..eacf71913
Binary files a/android/GooglePlayDailyIcon.png and b/android/GooglePlayDailyIcon.png differ
diff --git a/android/res/drawable-hdpi/icon.png b/android/res/drawable-hdpi/icon.png
index f6323cd90..18276ca70 100644
Binary files a/android/res/drawable-hdpi/icon.png and b/android/res/drawable-hdpi/icon.png differ
diff --git a/android/res/drawable-ldpi/icon.png b/android/res/drawable-ldpi/icon.png
index 8676e6502..a2161805f 100644
Binary files a/android/res/drawable-ldpi/icon.png and b/android/res/drawable-ldpi/icon.png differ
diff --git a/android/res/drawable-mdpi/icon.png b/android/res/drawable-mdpi/icon.png
index c1c760349..0df61ec83 100644
Binary files a/android/res/drawable-mdpi/icon.png and b/android/res/drawable-mdpi/icon.png differ
diff --git a/android/res/drawable-xhdpi/icon.png b/android/res/drawable-xhdpi/icon.png
index 58a1454d6..d93777cf4 100644
Binary files a/android/res/drawable-xhdpi/icon.png and b/android/res/drawable-xhdpi/icon.png differ
diff --git a/android/res/drawable-xxhdpi/icon.png b/android/res/drawable-xxhdpi/icon.png
index f74d76f41..c56814606 100644
Binary files a/android/res/drawable-xxhdpi/icon.png and b/android/res/drawable-xxhdpi/icon.png differ
diff --git a/android/res/drawable-xxxhdpi/icon.png b/android/res/drawable-xxxhdpi/icon.png
index f74d76f41..681e8646e 100644
Binary files a/android/res/drawable-xxxhdpi/icon.png and b/android/res/drawable-xxxhdpi/icon.png differ
diff --git a/custom/custom.pri b/custom/custom.pri
index 89b183051..dd163a11c 100644
--- a/custom/custom.pri
+++ b/custom/custom.pri
@@ -5,7 +5,7 @@ message("Adding Custom Herelink Plugin")
 
 CUSTOM_QGC_VER_MAJOR = 4
 CUSTOM_QGC_VER_MINOR = 4
-CUSTOM_QGC_VER_PATCH = 0
+CUSTOM_QGC_VER_PATCH = 1
 CUSTOM_QGC_VER_FIRST_BUILD = 0
 
 linux {
@@ -33,18 +33,18 @@ DEFINES += CUSTOMHEADER=\"\\\"HerelinkCorePlugin.h\\\"\"
 DEFINES += CUSTOMCLASS=HerelinkCorePlugin
 
 TARGET   = Herelink-QGroundControl
-DEFINES += QGC_APPLICATION_NAME='"\\\"Herelink QGroundControl\\\""'
-
-DEFINES += QGC_ORG_NAME=\"\\\"cubepilot.org\\\"\"
-DEFINES += QGC_ORG_DOMAIN=\"\\\"org.cubepilot\\\"\"
-
-QGC_APP_NAME        = "Herelink QGroundControl"
-QGC_BINARY_NAME     = "Herelink-QGroundControl"
-QGC_ORG_NAME        = "Cubepilot"
-QGC_ORG_DOMAIN      = "org.cubepilot"
-QGC_ANDROID_PACKAGE = "org.cubepilot.herelink_qgroundcontrol"
-QGC_APP_DESCRIPTION = "Herelink QGroundControl"
-QGC_APP_COPYRIGHT   = "Copyright (C) 2024 Cubepilot. All rights reserved."
+DEFINES += QGC_APPLICATION_NAME='"\\\"Arcsky Control\\\""'
+
+DEFINES += QGC_ORG_NAME=\"\\\"Arcsky\\\"\"
+DEFINES += QGC_ORG_DOMAIN=\"\\\"www.arcskytech.com\\\"\"
+
+QGC_APP_NAME        = "Arcsky Control"
+QGC_BINARY_NAME     = "Arcsky Control"
+QGC_ORG_NAME        = "Arcsky"
+QGC_ORG_DOMAIN      = "www.arcskytech.com"
+QGC_ANDROID_PACKAGE = "arcsky.ArcskyControl"
+QGC_APP_DESCRIPTION = "Arcsky Ground Control Station"
+QGC_APP_COPYRIGHT   = "Copyright (C) 2024 Arcsky. All rights reserved."
 
 # Remove code which the Herelink doesn't need
 DEFINES += \
diff --git a/custom/src/HerelinkCorePlugin.cc b/custom/src/HerelinkCorePlugin.cc
index 9b4827cf1..bb93c385f 100644
--- a/custom/src/HerelinkCorePlugin.cc
+++ b/custom/src/HerelinkCorePlugin.cc
@@ -133,29 +133,33 @@ void HerelinkCorePlugin::factValueGridCreateDefaultSettings(const QString& defau
 
     InstrumentValueData* value = column->value<InstrumentValueData*>(rowIndex++);
     value->setFact("Vehicle", "AltitudeRelative");
-    value->setIcon("arrow-thick-up.svg");
-    value->setText(value->fact()->shortDescription());
+    //value->setIcon("arrow-thick-up.svg");
+    value->setText("Alt (rel)");
+    //value->setText(value->fact()->shortDescription());
     value->setShowUnits(true);
 
     value = column->value<InstrumentValueData*>(rowIndex++);
     value->setFact("Vehicle", "DistanceToHome");
-    value->setIcon("bookmark copy 3.svg");
-    value->setText(value->fact()->shortDescription());
+    //value->setIcon("bookmark copy 3.svg");
+    //value->setText(value->fact()->shortDescription());
+    value->setText("Home Dist");
     value->setShowUnits(true);
 
     rowIndex    = 0;
     column      = factValueGrid.columns()->value<QmlObjectListModel*>(1);
 
     value = column->value<InstrumentValueData*>(rowIndex++);
-    value->setFact("Vehicle", "ClimbRate");
-    value->setIcon("arrow-simple-up.svg");
-    value->setText(value->fact()->shortDescription());
+    value->setFact("Vehicle", "FlightTime");
+    //value->setIcon("arrow-simple-up.svg");
+    //value->setText(value->fact()->shortDescription());
+    value->setText("Flight Time");
     value->setShowUnits(true);
 
     value = column->value<InstrumentValueData*>(rowIndex++);
     value->setFact("Vehicle", "GroundSpeed");
-    value->setIcon("arrow-simple-right.svg");
-    value->setText(value->fact()->shortDescription());
+    //value->setIcon("arrow-simple-right.svg");
+    //value->setText(value->fact()->shortDescription());
+    value->setText("Speed");
     value->setShowUnits(true);
 
 
@@ -178,14 +182,18 @@ void HerelinkCorePlugin::factValueGridCreateDefaultSettings(const QString& defau
     column      = factValueGrid.columns()->value<QmlObjectListModel*>(includeFWValues ? 3 : 2);
 
     value = column->value<InstrumentValueData*>(rowIndex++);
-    value->setFact("Vehicle", "FlightTime");
-    value->setIcon("timer.svg");
-    value->setText(value->fact()->shortDescription());
+    //value->setFact("Vehicle", "FlightTime");
+    value->setFact("Battery0","Voltage");
+    //value->setIcon("timer.svg");
+    //value->setText(value->fact()->shortDescription());
+    value->setText("Voltage");
     value->setShowUnits(false);
 
     value = column->value<InstrumentValueData*>(rowIndex++);
-    value->setFact("Vehicle", "FlightDistance");
-    value->setIcon("travel-walk.svg");
-    value->setText(value->fact()->shortDescription());
+    //value->setFact("Vehicle", "FlightDistance");
+    value->setFact("Battery0","Current");
+    //value->setIcon("travel-walk.svg");
+    //value->setText(value->fact()->shortDescription());
+    value->setText("Current");
     value->setShowUnits(true);
 }
diff --git a/qgcimages.qrc b/qgcimages.qrc
index e300b5f6b..1a3356d3d 100644
--- a/qgcimages.qrc
+++ b/qgcimages.qrc
@@ -207,5 +207,6 @@
         <file alias="Yield.svg">src/ui/toolbar/Images/Yield.svg</file>
         <file alias="ZoomMinus.svg">src/FlightMap/Images/ZoomMinus.svg</file>
         <file alias="ZoomPlus.svg">src/FlightMap/Images/ZoomPlus.svg</file>
+        <file alias="FuelTank.svg">src/ui/toolbar/Images/FuelTank.svg</file>
     </qresource>
 </RCC>
diff --git a/resources/NoVideoBackground.jpg b/resources/NoVideoBackground.jpg
old mode 100644
new mode 100755
index 678aa1460..83fe74c86
Binary files a/resources/NoVideoBackground.jpg and b/resources/NoVideoBackground.jpg differ
diff --git a/resources/QGCLogoBlack.svg b/resources/QGCLogoBlack.svg
old mode 100644
new mode 100755
index b242ff8c9..e057ebc8a
--- a/resources/QGCLogoBlack.svg
+++ b/resources/QGCLogoBlack.svg
@@ -1,30 +1,25 @@
-<?xml version="1.0" encoding="utf-8"?>
-<!-- Generator: Adobe Illustrator 19.2.1, SVG Export Plug-In . SVG Version: 6.00 Build 0)  -->
-<svg version="1.1" id="Layer_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"
-	 viewBox="0 0 215 215" style="enable-background:new 0 0 215 215;" xml:space="preserve">
-<style type="text/css">
-	.st0{fill:#231F20;}
-	.st1{fill:#5ECBF1;}
-	.st2{fill:none;stroke:#231F20;stroke-width:8;stroke-miterlimit:10;}
-</style>
-<path class="st0" d="M164.063,148.971l-10.179-10.179c5.993-8.679,9.511-19.197,9.511-30.54h-0.044
-	c0-27.905-21.19-50.857-48.345-53.617v23.318c15.334,2.768,26.72,16.891,25.137,33.349c-0.364,3.787-1.443,7.384-3.088,10.66
-	l-11.846-11.846l-16.406,16.406l10.812,10.812c-2.239,0.785-4.59,1.32-7.02,1.557c-16.415,1.601-30.514-9.699-33.36-24.959H55.903
-	c2.84,27.071,25.752,48.171,53.597,48.171v0.044c10.015,0,19.385-2.745,27.417-7.511l10.74,10.74L164.063,148.971z"/>
-<path class="st1" d="M103.747,39.064c-0.129,0-0.377,0.018-0.385,0.019c-33.409,2.944-60.044,29.582-62.971,63.031
-	c-0.002,0.023-0.021,0.329-0.022,0.358c-0.001,0.021-0.009,0.19-0.009,0.264c0,2.159,1.75,3.909,3.909,3.909
-	c2.097,0,3.808-1.651,3.904-3.723c0,0-0.002-0.001-0.002-0.001c2.546-29.719,26.159-53.412,55.822-56.045l0,0
-	c1.981-0.125,3.565-1.728,3.658-3.717c0.003-0.062,0.004-0.123,0.004-0.186C107.656,40.814,105.906,39.064,103.747,39.064z"/>
-<path class="st1" d="M103.752,54.604c-0.14,0-0.278,0.01-0.414,0.024c-0.002,0-0.056,0.005-0.061,0.006
-	c-25.063,2.893-45.007,23.272-47.393,47.639c0,0-0.03,0.32-0.03,0.486c0,2.159,1.75,3.909,3.909,3.909
-	c2.097,0,3.808-1.651,3.904-3.723c0.001-0.021,0.001-0.042,0.001-0.063c2.451-21.156,19.198-37.949,40.325-40.463l0-0.019
-	c1.982-0.124,3.569-1.709,3.662-3.7c0.003-0.061,0.004-0.123,0.004-0.185C107.66,56.354,105.91,54.604,103.752,54.604z"/>
-<path class="st1" d="M103.747,70.208c-0.247,0-0.494,0.024-0.729,0.068C86.917,73.008,74.167,85.81,71.513,101.94
-	c-0.009,0.043-0.015,0.086-0.023,0.129c-0.042,0.236-0.071,0.562-0.071,0.704c0,2.159,1.75,3.909,3.909,3.909
-	c0.155,0,0.308-0.009,0.458-0.027c1.826-0.213,3.268-1.686,3.434-3.526c0.005-0.057,0.031-0.316,0.038-0.357
-	c2.255-12.578,12.164-22.477,24.735-24.752c0,0,0.142-0.013,0.212-0.022c1.882-0.22,3.356-1.777,3.446-3.697
-	c0.003-0.062,0.004-0.123,0.004-0.186C107.656,71.958,105.906,70.208,103.747,70.208z"/>
-<g>
-	<path class="st2" d="M211.5,151.5c0,33-27,60-60,60h-88c-33,0-60-27-60-60v-88c0-33,27-60,60-60h88c33,0,60,27,60,60V151.5z"/>
-</g>
-</svg>
+<?xml version="1.0" encoding="UTF-8"?>
+<svg id="Layer_2" data-name="Layer 2" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 88.13 105.27">
+  <defs>
+    <style>
+      .cls-1 {
+        fill: #fff;
+        stroke-width: 0px;
+      }
+    </style>
+  </defs>
+  <g id="Logo_Only_White">
+    <g>
+      <g>
+        <path class="cls-1" d="M22.23,77.9L0,89,18.62,18.71h0c1.53-7.01,5.8-12.11,11.63-15.28l-8.03,74.47Z"/>
+        <polygon class="cls-1" points="24.24 82.18 40.84 94.25 17.34 105.27 .49 94.04 24.24 82.18"/>
+        <path class="cls-1" d="M40.84,0v88.41l-13.93-10.13L35.21,1.32c1.79-.59,3.68-1.03,5.63-1.32Z"/>
+      </g>
+      <g>
+        <path class="cls-1" d="M65.9,77.9l22.23,11.1-18.62-70.29h0c-1.53-7.01-5.8-12.11-11.63-15.28l8.03,74.47Z"/>
+        <polygon class="cls-1" points="63.89 82.18 47.29 94.25 70.79 105.27 87.64 94.04 63.89 82.18"/>
+        <path class="cls-1" d="M47.29,0v88.41s13.93-10.13,13.93-10.13L52.92,1.32C51.13.73,49.24.29,47.29,0Z"/>
+      </g>
+    </g>
+  </g>
+</svg>
\ No newline at end of file
diff --git a/resources/QGCLogoFull.svg b/resources/QGCLogoFull.svg
old mode 100644
new mode 100755
index ebfb890a6..e057ebc8a
--- a/resources/QGCLogoFull.svg
+++ b/resources/QGCLogoFull.svg
@@ -1,27 +1,25 @@
-<?xml version="1.0" encoding="utf-8"?>
-<!-- Generator: Adobe Illustrator 21.1.0, SVG Export Plug-In . SVG Version: 6.00 Build 0)  -->
-<svg version="1.1" id="Layer_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"
-	 width="72px" height="72px" viewBox="0 0 72 72" style="enable-background:new 0 0 72 72;" xml:space="preserve">
-<style type="text/css">
-	.st0{fill:#FFFFFF;}
-	.st1{fill:#4B2C6D;stroke:#FFFFFF;stroke-width:3;stroke-miterlimit:10;}
-	.st2{fill:#5ECBF1;}
-</style>
-<rect x="10.555" y="10.213" class="st0" width="50.924" height="50.582"/>
-<path class="st1" d="M50.296,1.8H21.704C10.726,1.8,1.8,10.726,1.8,21.704v28.591C1.8,61.274,10.726,70.2,21.704,70.2h28.591
-	c10.978,0,19.904-8.926,19.904-19.904V21.704C70.2,10.726,61.274,1.8,50.296,1.8z M49.748,55.802l-3.659-3.659
-	c-2.736,1.642-5.951,2.565-9.371,2.565l0,0c-9.508,0-17.374-7.216-18.331-16.484h7.969c0.958,5.233,5.78,9.097,11.423,8.55
-	c0.821-0.068,1.642-0.274,2.394-0.547l-3.728-3.728l5.609-5.609l4.07,4.036c0.547-1.129,0.923-2.36,1.06-3.659
-	c0.547-5.643-3.352-10.465-8.584-11.389v-7.969c9.268,0.958,16.519,8.789,16.519,18.331l0,0c0,3.865-1.197,7.49-3.249,10.431
-	l3.488,3.488L49.748,55.802z"/>
-<path class="st2" d="M34.7,12.607c-0.034,0-0.137,0-0.137,0c-11.423,0.992-20.52,10.123-21.546,21.546c0,0,0,0.103,0,0.137
-	c0,0,0,0.068,0,0.103c0,0.752,0.616,1.334,1.334,1.334c0.718,0,1.3-0.581,1.334-1.265l0,0c0.855-10.157,8.96-18.263,19.084-19.152
-	l0,0c0.684-0.034,1.231-0.581,1.265-1.265c0-0.034,0-0.034,0-0.068C36.068,13.189,35.453,12.607,34.7,12.607z"/>
-<path class="st2" d="M34.7,17.908c-0.034,0-0.103,0-0.137,0h-0.034c-8.584,0.992-15.39,7.969-16.211,16.279c0,0,0,0.103,0,0.171
-	c0,0.752,0.616,1.334,1.334,1.334c0.718,0,1.3-0.581,1.334-1.265c0,0,0,0,0-0.034c0.855-7.25,6.566-12.996,13.783-13.851l0,0
-	c0.684-0.034,1.231-0.581,1.265-1.265c0-0.034,0-0.034,0-0.068C36.068,18.49,35.453,17.908,34.7,17.908z"/>
-<path class="st2" d="M34.7,23.243c-0.068,0-0.171,0-0.239,0.034c-5.506,0.923-9.85,5.301-10.773,10.807v0.034
-	c0,0.068-0.034,0.205-0.034,0.239c0,0.752,0.581,1.334,1.334,1.334c0.068,0,0.103,0,0.171,0c0.616-0.068,1.129-0.581,1.163-1.197
-	c0-0.034,0-0.103,0-0.137c0.787-4.275,4.172-7.661,8.482-8.447c0,0,0.034,0,0.068,0c0.65-0.068,1.163-0.616,1.163-1.265
-	c0-0.034,0-0.034,0-0.068C36.068,23.859,35.453,23.243,34.7,23.243z"/>
-</svg>
+<?xml version="1.0" encoding="UTF-8"?>
+<svg id="Layer_2" data-name="Layer 2" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 88.13 105.27">
+  <defs>
+    <style>
+      .cls-1 {
+        fill: #fff;
+        stroke-width: 0px;
+      }
+    </style>
+  </defs>
+  <g id="Logo_Only_White">
+    <g>
+      <g>
+        <path class="cls-1" d="M22.23,77.9L0,89,18.62,18.71h0c1.53-7.01,5.8-12.11,11.63-15.28l-8.03,74.47Z"/>
+        <polygon class="cls-1" points="24.24 82.18 40.84 94.25 17.34 105.27 .49 94.04 24.24 82.18"/>
+        <path class="cls-1" d="M40.84,0v88.41l-13.93-10.13L35.21,1.32c1.79-.59,3.68-1.03,5.63-1.32Z"/>
+      </g>
+      <g>
+        <path class="cls-1" d="M65.9,77.9l22.23,11.1-18.62-70.29h0c-1.53-7.01-5.8-12.11-11.63-15.28l8.03,74.47Z"/>
+        <polygon class="cls-1" points="63.89 82.18 47.29 94.25 70.79 105.27 87.64 94.04 63.89 82.18"/>
+        <path class="cls-1" d="M47.29,0v88.41s13.93-10.13,13.93-10.13L52.92,1.32C51.13.73,49.24.29,47.29,0Z"/>
+      </g>
+    </g>
+  </g>
+</svg>
\ No newline at end of file
diff --git a/resources/QGCLogoWhite.svg b/resources/QGCLogoWhite.svg
old mode 100644
new mode 100755
index 9f045f9b2..e057ebc8a
--- a/resources/QGCLogoWhite.svg
+++ b/resources/QGCLogoWhite.svg
@@ -1,30 +1,25 @@
-<?xml version="1.0" encoding="utf-8"?>
-<!-- Generator: Adobe Illustrator 19.2.1, SVG Export Plug-In . SVG Version: 6.00 Build 0)  -->
-<svg version="1.1" id="Layer_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"
-	 viewBox="0 0 215 215" style="enable-background:new 0 0 215 215;" xml:space="preserve">
-<style type="text/css">
-	.st0{fill:#FFFFFF;}
-	.st1{fill:#5ECBF1;}
-	.st2{fill:none;stroke:#FFFFFF;stroke-width:8;stroke-miterlimit:10;}
-</style>
-<path class="st0" d="M164.063,148.971l-10.179-10.179c5.993-8.679,9.511-19.197,9.511-30.54h-0.044
-	c0-27.905-21.19-50.857-48.345-53.617v23.318c15.334,2.768,26.72,16.891,25.137,33.349c-0.364,3.787-1.443,7.384-3.088,10.66
-	l-11.846-11.846l-16.406,16.406l10.812,10.812c-2.239,0.785-4.59,1.32-7.02,1.557c-16.415,1.601-30.514-9.699-33.36-24.959H55.903
-	c2.84,27.071,25.752,48.171,53.597,48.171v0.044c10.015,0,19.385-2.745,27.417-7.511l10.74,10.74L164.063,148.971z"/>
-<path class="st1" d="M103.747,39.064c-0.129,0-0.377,0.018-0.385,0.019c-33.409,2.944-60.044,29.582-62.971,63.031
-	c-0.002,0.023-0.021,0.329-0.022,0.358c-0.001,0.021-0.009,0.19-0.009,0.264c0,2.159,1.75,3.909,3.909,3.909
-	c2.097,0,3.808-1.651,3.904-3.723c0,0-0.002-0.001-0.002-0.001c2.546-29.719,26.159-53.412,55.822-56.045l0,0
-	c1.981-0.125,3.565-1.728,3.658-3.717c0.003-0.062,0.004-0.123,0.004-0.186C107.656,40.814,105.906,39.064,103.747,39.064z"/>
-<path class="st1" d="M103.752,54.604c-0.14,0-0.278,0.01-0.414,0.024c-0.002,0-0.056,0.005-0.061,0.006
-	c-25.063,2.893-45.007,23.272-47.393,47.639c0,0-0.03,0.32-0.03,0.486c0,2.159,1.75,3.909,3.909,3.909
-	c2.097,0,3.808-1.651,3.904-3.723c0.001-0.021,0.001-0.042,0.001-0.063c2.451-21.156,19.198-37.949,40.325-40.463l0-0.019
-	c1.982-0.124,3.569-1.709,3.662-3.7c0.003-0.061,0.004-0.123,0.004-0.185C107.66,56.354,105.91,54.604,103.752,54.604z"/>
-<path class="st1" d="M103.747,70.208c-0.247,0-0.494,0.024-0.729,0.068C86.917,73.008,74.167,85.81,71.513,101.94
-	c-0.009,0.043-0.015,0.086-0.023,0.129c-0.042,0.236-0.071,0.562-0.071,0.704c0,2.159,1.75,3.909,3.909,3.909
-	c0.155,0,0.308-0.009,0.458-0.027c1.826-0.213,3.268-1.686,3.434-3.526c0.005-0.057,0.031-0.316,0.038-0.357
-	c2.255-12.578,12.164-22.477,24.735-24.752c0,0,0.142-0.013,0.212-0.022c1.882-0.22,3.356-1.777,3.446-3.697
-	c0.003-0.062,0.004-0.123,0.004-0.186C107.656,71.958,105.906,70.208,103.747,70.208z"/>
-<g>
-	<path class="st2" d="M211.5,151.5c0,33-27,60-60,60h-88c-33,0-60-27-60-60v-88c0-33,27-60,60-60h88c33,0,60,27,60,60V151.5z"/>
-</g>
-</svg>
+<?xml version="1.0" encoding="UTF-8"?>
+<svg id="Layer_2" data-name="Layer 2" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 88.13 105.27">
+  <defs>
+    <style>
+      .cls-1 {
+        fill: #fff;
+        stroke-width: 0px;
+      }
+    </style>
+  </defs>
+  <g id="Logo_Only_White">
+    <g>
+      <g>
+        <path class="cls-1" d="M22.23,77.9L0,89,18.62,18.71h0c1.53-7.01,5.8-12.11,11.63-15.28l-8.03,74.47Z"/>
+        <polygon class="cls-1" points="24.24 82.18 40.84 94.25 17.34 105.27 .49 94.04 24.24 82.18"/>
+        <path class="cls-1" d="M40.84,0v88.41l-13.93-10.13L35.21,1.32c1.79-.59,3.68-1.03,5.63-1.32Z"/>
+      </g>
+      <g>
+        <path class="cls-1" d="M65.9,77.9l22.23,11.1-18.62-70.29h0c-1.53-7.01-5.8-12.11-11.63-15.28l8.03,74.47Z"/>
+        <polygon class="cls-1" points="63.89 82.18 47.29 94.25 70.79 105.27 87.64 94.04 63.89 82.18"/>
+        <path class="cls-1" d="M47.29,0v88.41s13.93-10.13,13.93-10.13L52.92,1.32C51.13.73,49.24.29,47.29,0Z"/>
+      </g>
+    </g>
+  </g>
+</svg>
\ No newline at end of file
diff --git a/resources/icons/android_512x512.png b/resources/icons/android_512x512.png
old mode 100644
new mode 100755
index 6c3e9913b..eacf71913
Binary files a/resources/icons/android_512x512.png and b/resources/icons/android_512x512.png differ
diff --git a/resources/icons/android_dev_512x512.png b/resources/icons/android_dev_512x512.png
old mode 100644
new mode 100755
index 41f369561..eacf71913
Binary files a/resources/icons/android_dev_512x512.png and b/resources/icons/android_dev_512x512.png differ
diff --git a/resources/icons/qgroundcontrol.ico b/resources/icons/qgroundcontrol.ico
old mode 100644
new mode 100755
index 3cd85b3aa..790658a5e
Binary files a/resources/icons/qgroundcontrol.ico and b/resources/icons/qgroundcontrol.ico differ
diff --git a/resources/icons/qgroundcontrol.png b/resources/icons/qgroundcontrol.png
old mode 100644
new mode 100755
index 8a313ccde..eacf71913
Binary files a/resources/icons/qgroundcontrol.png and b/resources/icons/qgroundcontrol.png differ
diff --git a/src/AutoPilotPlugins/APM/APMFlightModesComponent.cc b/src/AutoPilotPlugins/APM/APMFlightModesComponent.cc
index f07ddfb0e..2758bb7ba 100644
--- a/src/AutoPilotPlugins/APM/APMFlightModesComponent.cc
+++ b/src/AutoPilotPlugins/APM/APMFlightModesComponent.cc
@@ -15,7 +15,7 @@
 
 APMFlightModesComponent::APMFlightModesComponent(Vehicle* vehicle, AutoPilotPlugin* autopilot, QObject* parent) :
     VehicleComponent(vehicle, autopilot, parent),
-    _name(tr("Flight Modes"))
+    _name(tr("RC Options"))//_name(tr("Flight Modes"))
 {
 }
 
diff --git a/src/AutoPilotPlugins/APM/APMFlightModesComponent.qml b/src/AutoPilotPlugins/APM/APMFlightModesComponent.qml
index 11b3f4069..58fcd50dc 100644
--- a/src/AutoPilotPlugins/APM/APMFlightModesComponent.qml
+++ b/src/AutoPilotPlugins/APM/APMFlightModesComponent.qml
@@ -50,132 +50,132 @@ SetupPage {
             width:      availableWidth
             spacing:     _margins
 
-            Column {
-                spacing: _margins
-
-                QGCLabel {
-                    id:             flightModeLabel
-                    text:           qsTr("Flight Mode Settings") + (_fltmodeChExists ? "" : qsTr(" (Channel 5)"))
-                    font.family:    ScreenTools.demiboldFontFamily
-                }
-
-                Rectangle {
-                    id:     flightModeSettings
-                    width:  flightModeColumn.width + (_margins * 2)
-                    height: flightModeColumn.height + ScreenTools.defaultFontPixelHeight
-                    color:  qgcPal.windowShade
-
-                    Column {
-                        id:                 flightModeColumn
-                        anchors.margins:    ScreenTools.defaultFontPixelWidth
-                        anchors.left:       parent.left
-                        anchors.top:        parent.top
-                        spacing:            ScreenTools.defaultFontPixelHeight
-
-                        Row {
-                            spacing:    _margins
-                            visible:    _fltmodeChExists
-
-                            QGCLabel {
-                                id:                 modeChannelLabel
-                                anchors.baseline:   modeChannelCombo.baseline
-                                text:               qsTr("Flight mode channel:")
-                            }
-
-                            QGCComboBox {
-                                id:             modeChannelCombo
-                                width:          ScreenTools.defaultFontPixelWidth * 15
-                                model:          [ qsTr("Not assigned"), qsTr("Channel 1"), qsTr("Channel 2"),
-                                    qsTr("Channel 3"),    qsTr("Channel 4"), qsTr("Channel 5"),
-                                    qsTr("Channel 6"),    qsTr("Channel 7"), qsTr("Channel 8") ]
-
-                                currentIndex:   _fltmodeCh.value
-                                onActivated:    _fltmodeCh.value = index
-                            }
-                        }
-
-                        GridLayout {
-                            rows:   _customSimpleMode ? 7 : 6
-                            flow:   GridLayout.TopToBottom
-
-                            QGCLabel { text: ""; visible: _customSimpleMode }
-                            Repeater {
-                                model:  6
-
-                                QGCLabel {
-                                    text:   qsTr("Flight Mode ") + index
-                                    color:  controller.activeFlightMode == index ? "yellow" : qgcPal.text
-
-                                    property int index: modelData + 1
-                                }
-                            }
-
-                            QGCLabel { text: ""; visible: _customSimpleMode }
-                            Repeater {
-                                model:  6
-
-                                FactComboBox {
-                                    Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 15
-                                    fact:                   controller.getParameterFact(-1, _modeParamPrefix + index)
-                                    indexModel:             false
-
-                                    property int index: modelData + 1
-                                }
-                            }
-
-                            QGCLabel {
-                                text:           qsTr("Simple")
-                                font.pointSize: ScreenTools.smallFontPointSize
-                                visible:        _customSimpleMode
-                            }
-                            Repeater {
-                                model:  controller.simpleModeEnabled
-                                QGCCheckBox {
-                                    Layout.alignment:   Qt.AlignHCenter
-                                    visible:            _customSimpleMode
-                                    checked:            modelData
-                                    onClicked:          controller.setSimpleMode(index, checked)
-                                }
-                            }
-
-                            QGCLabel {
-                                text:           qsTr("Super-Simple")
-                                font.pointSize: ScreenTools.smallFontPointSize
-                                visible:        _customSimpleMode
-                            }
-                            Repeater {
-                                model:  controller.superSimpleModeEnabled
-                                QGCCheckBox {
-                                    Layout.alignment:   Qt.AlignHCenter
-                                    visible:            _customSimpleMode
-                                    checked:            modelData
-                                    onClicked:          controller.setSuperSimpleMode(index, checked)
-                                }
-                            }
-
-                            QGCLabel { text: ""; visible: _customSimpleMode }
-                            Repeater {
-                                model:  6
-
-                                QGCLabel { text: _pwmStrings[modelData] }
-                            }
-                        }
-
-                        RowLayout {
-                            spacing: _margins
-                            visible: controller.simpleModesSupported
-
-                            QGCLabel { text: qsTr("Simple Mode") }
-
-                            QGCComboBox {
-                                model:          controller.simpleModeNames
-                                currentIndex:   controller.simpleMode
-                                onActivated:    controller.simpleMode = index
-                            }
-                        }
-                    } // Column - Flight Modes
-                } // Rectangle - Flight Modes
-            } // Column - Flight Modes
+//            Column {
+//                spacing: _margins
+
+//                QGCLabel {
+//                    id:             flightModeLabel
+//                    text:           qsTr("Flight Mode Settings") + (_fltmodeChExists ? "" : qsTr(" (Channel 5)"))
+//                    font.family:    ScreenTools.demiboldFontFamily
+//                }
+
+//                Rectangle {
+//                    id:     flightModeSettings
+//                    width:  flightModeColumn.width + (_margins * 2)
+//                    height: flightModeColumn.height + ScreenTools.defaultFontPixelHeight
+//                    color:  qgcPal.windowShade
+
+//                    Column {
+//                        id:                 flightModeColumn
+//                        anchors.margins:    ScreenTools.defaultFontPixelWidth
+//                        anchors.left:       parent.left
+//                        anchors.top:        parent.top
+//                        spacing:            ScreenTools.defaultFontPixelHeight
+
+////                        Row {
+////                            spacing:    _margins
+////                            visible:    _fltmodeChExists
+
+////                            QGCLabel {
+////                                id:                 modeChannelLabel
+////                                anchors.baseline:   modeChannelCombo.baseline
+////                                text:               qsTr("Flight mode channel:")
+////                            }
+
+////                            QGCComboBox {
+////                                id:             modeChannelCombo
+////                                width:          ScreenTools.defaultFontPixelWidth * 15
+////                                model:          [ qsTr("Not assigned"), qsTr("Channel 1"), qsTr("Channel 2"),
+////                                    qsTr("Channel 3"),    qsTr("Channel 4"), qsTr("Channel 5"),
+////                                    qsTr("Channel 6"),    qsTr("Channel 7"), qsTr("Channel 8") ]
+
+////                                currentIndex:   _fltmodeCh.value
+////                                onActivated:    _fltmodeCh.value = index
+////                            }
+////                        }
+
+////                        GridLayout {
+////                            rows:   _customSimpleMode ? 7 : 6
+////                            flow:   GridLayout.TopToBottom
+
+////                            QGCLabel { text: ""; visible: _customSimpleMode }
+////                            Repeater {
+////                                model:  6
+
+////                                QGCLabel {
+////                                    text:   qsTr("Flight Mode ") + index
+////                                    color:  controller.activeFlightMode == index ? "yellow" : qgcPal.text
+
+////                                    property int index: modelData + 1
+////                                }
+////                            }
+
+////                            QGCLabel { text: ""; visible: _customSimpleMode }
+////                            Repeater {
+////                                model:  6
+
+////                                FactComboBox {
+////                                    Layout.preferredWidth:  ScreenTools.defaultFontPixelWidth * 15
+////                                    fact:                   controller.getParameterFact(-1, _modeParamPrefix + index)
+////                                    indexModel:             false
+
+////                                    property int index: modelData + 1
+////                                }
+////                            }
+
+////                            QGCLabel {
+////                                text:           qsTr("Simple")
+////                                font.pointSize: ScreenTools.smallFontPointSize
+////                                visible:        _customSimpleMode
+////                            }
+////                            Repeater {
+////                                model:  controller.simpleModeEnabled
+////                                QGCCheckBox {
+////                                    Layout.alignment:   Qt.AlignHCenter
+////                                    visible:            _customSimpleMode
+////                                    checked:            modelData
+////                                    onClicked:          controller.setSimpleMode(index, checked)
+////                                }
+////                            }
+
+////                            QGCLabel {
+////                                text:           qsTr("Super-Simple")
+////                                font.pointSize: ScreenTools.smallFontPointSize
+////                                visible:        _customSimpleMode
+////                            }
+////                            Repeater {
+////                                model:  controller.superSimpleModeEnabled
+////                                QGCCheckBox {
+////                                    Layout.alignment:   Qt.AlignHCenter
+////                                    visible:            _customSimpleMode
+////                                    checked:            modelData
+////                                    onClicked:          controller.setSuperSimpleMode(index, checked)
+////                                }
+////                            }
+
+////                            QGCLabel { text: ""; visible: _customSimpleMode }
+////                            Repeater {
+////                                model:  6
+
+////                                QGCLabel { text: _pwmStrings[modelData] }
+////                            }
+////                        }
+
+////                        RowLayout {
+////                            spacing: _margins
+////                            visible: controller.simpleModesSupported
+
+////                            QGCLabel { text: qsTr("Simple Mode") }
+
+////                            QGCComboBox {
+////                                model:          controller.simpleModeNames
+////                                currentIndex:   controller.simpleMode
+////                                onActivated:    controller.simpleMode = index
+////                            }
+////                        }
+//                    } // Column - Flight Modes
+//                } // Rectangle - Flight Modes
+//            } // Column - Flight Modes
 
             Column {
                 spacing: _margins
diff --git a/src/AutoPilotPlugins/APM/APMPowerComponent.qml b/src/AutoPilotPlugins/APM/APMPowerComponent.qml
index 8baf43577..fc77cb0db 100644
--- a/src/AutoPilotPlugins/APM/APMPowerComponent.qml
+++ b/src/AutoPilotPlugins/APM/APMPowerComponent.qml
@@ -124,161 +124,161 @@ SetupPage {
                         sourceComponent:    _batt1FullSettings.visible ? powerSetupComponent : undefined
 
                         property Fact armVoltMin:       controller.getParameterFact(-1, "r.BATT_ARM_VOLT", false /* reportMissing */)
-                        property Fact battAmpPerVolt:   controller.getParameterFact(-1, "r.BATT_AMP_PERVLT", false /* reportMissing */)
-                        property Fact battAmpOffset:    controller.getParameterFact(-1, "BATT_AMP_OFFSET", false /* reportMissing */)
+                        //property Fact battAmpPerVolt:   controller.getParameterFact(-1, "r.BATT_AMP_PERVLT", false /* reportMissing */)
+                        //property Fact battAmpOffset:    controller.getParameterFact(-1, "BATT_AMP_OFFSET", false /* reportMissing */)
                         property Fact battCapacity:     controller.getParameterFact(-1, "BATT_CAPACITY", false /* reportMissing */)
-                        property Fact battCurrPin:      controller.getParameterFact(-1, "BATT_CURR_PIN", false /* reportMissing */)
-                        property Fact battMonitor:      controller.getParameterFact(-1, "BATT_MONITOR", false /* reportMissing */)
-                        property Fact battVoltMult:     controller.getParameterFact(-1, "BATT_VOLT_MULT", false /* reportMissing */)
-                        property Fact battVoltPin:      controller.getParameterFact(-1, "BATT_VOLT_PIN", false /* reportMissing */)
+                        //property Fact battCurrPin:      controller.getParameterFact(-1, "BATT_CURR_PIN", false /* reportMissing */)
+                        //property Fact battMonitor:      controller.getParameterFact(-1, "BATT_MONITOR", false /* reportMissing */)
+                        //property Fact battVoltMult:     controller.getParameterFact(-1, "BATT_VOLT_MULT", false /* reportMissing */)
+                        //property Fact battVoltPin:      controller.getParameterFact(-1, "BATT_VOLT_PIN", false /* reportMissing */)
                         property FactGroup  _batteryFactGroup:  _batt1FullSettings.visible ? controller.vehicle.getFactGroup("battery0") : null
-                        property Fact vehicleVoltage:   _batteryFactGroup ? _batteryFactGroup.voltage : null
-                        property Fact vehicleCurrent:   _batteryFactGroup ? _batteryFactGroup.current : null
+                        //property Fact vehicleVoltage:   _batteryFactGroup ? _batteryFactGroup.voltage : null
+                        //property Fact vehicleCurrent:   _batteryFactGroup ? _batteryFactGroup.current : null
                     }
                 }
             }
 
-            // Battery2 Monitor settings only - used when only monitor param is available
-            Column {
-                spacing: _margins / 2
-                visible: !_batt2MonitorEnabled || !_batt2ParamsAvailable
-
-                QGCLabel {
-                    text:       qsTr("Battery 2")
-                    font.family: ScreenTools.demiboldFontFamily
-                }
-
-                Rectangle {
-                    width:  batt2Column.x + batt2Column.width + _margins
-                    height: batt2Column.y + batt2Column.height + _margins
-                    color:  ggcPal.windowShade
-
-                    ColumnLayout {
-                        id:                 batt2Column
-                        anchors.margins:    _margins
-                        anchors.top:        parent.top
-                        anchors.left:       parent.left
-                        spacing:            ScreenTools.defaultFontPixelWidth
-
-                        RowLayout {
-                            id:                 batt2MonitorRow
-                            spacing:            ScreenTools.defaultFontPixelWidth
-
-                            QGCLabel { text: qsTr("Battery2 monitor:") }
-                            FactComboBox {
-                                id:         monitor2Combo
-                                fact:       _batt2Monitor
-                                indexModel: false
-                                sizeToContents: true
-                            }
-                        }
-
-                        QGCLabel {
-                            text:       _restartRequired
-                            visible:    _showBatt2Reboot
-                        }
-
-                        QGCButton {
-                            text:       qsTr("Reboot vehicle")
-                            visible:    _showBatt2Reboot
-                            onClicked:  controller.vehicle.rebootVehicle()
-                        }
-                    }
-                }
-            }
-
-            // Battery 2 settings - Used when full params are available
-            Column {
-                id:         batt2FullSettings
-                spacing:    _margins / 2
-                visible:    _batt2MonitorEnabled && _batt2ParamsAvailable
-
-                QGCLabel {
-                    text:       qsTr("Battery 2")
-                    font.family: ScreenTools.demiboldFontFamily
-                }
-
-                Rectangle {
-                    width:  battery2Loader.x + battery2Loader.width + _margins
-                    height: battery2Loader.y + battery2Loader.height + _margins
-                    color:  ggcPal.windowShade
-
-                    Loader {
-                        id:                 battery2Loader
-                        anchors.margins:    _margins
-                        anchors.top:        parent.top
-                        anchors.left:       parent.left
-                        sourceComponent:    batt2FullSettings.visible ? powerSetupComponent : undefined
-
-                        property Fact armVoltMin:       controller.getParameterFact(-1, "r.BATT2_ARM_VOLT", false /* reportMissing */)
-                        property Fact battAmpPerVolt:   controller.getParameterFact(-1, "r.BATT2_AMP_PERVLT", false /* reportMissing */)
-                        property Fact battAmpOffset:    controller.getParameterFact(-1, "BATT2_AMP_OFFSET", false /* reportMissing */)
-                        property Fact battCapacity:     controller.getParameterFact(-1, "BATT2_CAPACITY", false /* reportMissing */)
-                        property Fact battCurrPin:      controller.getParameterFact(-1, "BATT2_CURR_PIN", false /* reportMissing */)
-                        property Fact battMonitor:      controller.getParameterFact(-1, "BATT2_MONITOR", false /* reportMissing */)
-                        property Fact battVoltMult:     controller.getParameterFact(-1, "BATT2_VOLT_MULT", false /* reportMissing */)
-                        property Fact battVoltPin:      controller.getParameterFact(-1, "BATT2_VOLT_PIN", false /* reportMissing */)
-                        property FactGroup  _batteryFactGroup:  batt2FullSettings.visible ? controller.vehicle.getFactGroup("battery1") : null
-                        property Fact vehicleVoltage:   _batteryFactGroup ? _batteryFactGroup.voltage : null
-                        property Fact vehicleCurrent:   _batteryFactGroup ? _batteryFactGroup.current : null
-                    }
-                }
-            }
-
-            Column {
-                spacing:    _margins / 2
-                visible:    _escCalibrationAvailable
-
-                QGCLabel {
-                    text:       qsTr("ESC Calibration")
-                    font.family: ScreenTools.demiboldFontFamily
-                }
-
-                Rectangle {
-                    width:  escCalibrationHolder.x + escCalibrationHolder.width + _margins
-                    height: escCalibrationHolder.y + escCalibrationHolder.height + _margins
-                    color:  ggcPal.windowShade
-
-                    Column {
-                        id:         escCalibrationHolder
-                        x:          _margins
-                        y:          _margins
-                        spacing:    _margins
-
-                        Column {
-                            spacing: _margins
-
-                            QGCLabel {
-                                text:   qsTr("WARNING: Remove props prior to calibration!")
-                                color:  qgcPal.warningText
-                            }
-
-                            Row {
-                                spacing: _margins
-
-                                QGCButton {
-                                    text: qsTr("Calibrate")
-                                    enabled:    _escCalibration && _escCalibration.rawValue === 0
-                                    onClicked:  if(_escCalibration) _escCalibration.rawValue = 3
-                                }
-
-                                Column {
-                                    enabled: _escCalibration && _escCalibration.rawValue === 3
-                                    QGCLabel { text:   _escCalibration ? (_escCalibration.rawValue === 3 ? qsTr("Now perform these steps:") : qsTr("Click Calibrate to start, then:")) : "" }
-                                    QGCLabel { text:   qsTr("- Disconnect USB and battery so flight controller powers down") }
-                                    QGCLabel { text:   qsTr("- Connect the battery") }
-                                    QGCLabel { text:   qsTr("- The arming tone will be played (if the vehicle has a buzzer attached)") }
-                                    QGCLabel { text:   qsTr("- If using a flight controller with a safety button press it until it displays solid red") }
-                                    QGCLabel { text:   qsTr("- You will hear a musical tone then two beeps") }
-                                    QGCLabel { text:   qsTr("- A few seconds later you should hear a number of beeps (one for each battery cell you're using)") }
-                                    QGCLabel { text:   qsTr("- And finally a single long beep indicating the end points have been set and the ESC is calibrated") }
-                                    QGCLabel { text:   qsTr("- Disconnect the battery and power up again normally") }
-                                }
-                            }
-                        }
-                    }
-                }
-            }
+//            // Battery2 Monitor settings only - used when only monitor param is available
+//            Column {
+//                spacing: _margins / 2
+//                visible: !_batt2MonitorEnabled || !_batt2ParamsAvailable
+
+//                QGCLabel {
+//                    text:       qsTr("Battery 2")
+//                    font.family: ScreenTools.demiboldFontFamily
+//                }
+
+//                Rectangle {
+//                    width:  batt2Column.x + batt2Column.width + _margins
+//                    height: batt2Column.y + batt2Column.height + _margins
+//                    color:  ggcPal.windowShade
+
+//                    ColumnLayout {
+//                        id:                 batt2Column
+//                        anchors.margins:    _margins
+//                        anchors.top:        parent.top
+//                        anchors.left:       parent.left
+//                        spacing:            ScreenTools.defaultFontPixelWidth
+
+//                        RowLayout {
+//                            id:                 batt2MonitorRow
+//                            spacing:            ScreenTools.defaultFontPixelWidth
+
+//                            QGCLabel { text: qsTr("Battery2 monitor:") }
+//                            FactComboBox {
+//                                id:         monitor2Combo
+//                                fact:       _batt2Monitor
+//                                indexModel: false
+//                                sizeToContents: true
+//                            }
+//                        }
+
+//                        QGCLabel {
+//                            text:       _restartRequired
+//                            visible:    _showBatt2Reboot
+//                        }
+
+//                        QGCButton {
+//                            text:       qsTr("Reboot vehicle")
+//                            visible:    _showBatt2Reboot
+//                            onClicked:  controller.vehicle.rebootVehicle()
+//                        }
+//                    }
+//                }
+//            }
+
+//            // Battery 2 settings - Used when full params are available
+//            Column {
+//                id:         batt2FullSettings
+//                spacing:    _margins / 2
+//                visible:    _batt2MonitorEnabled && _batt2ParamsAvailable
+
+//                QGCLabel {
+//                    text:       qsTr("Battery 2")
+//                    font.family: ScreenTools.demiboldFontFamily
+//                }
+
+//                Rectangle {
+//                    width:  battery2Loader.x + battery2Loader.width + _margins
+//                    height: battery2Loader.y + battery2Loader.height + _margins
+//                    color:  ggcPal.windowShade
+
+//                    Loader {
+//                        id:                 battery2Loader
+//                        anchors.margins:    _margins
+//                        anchors.top:        parent.top
+//                        anchors.left:       parent.left
+//                        sourceComponent:    batt2FullSettings.visible ? powerSetupComponent : undefined
+
+//                        property Fact armVoltMin:       controller.getParameterFact(-1, "r.BATT2_ARM_VOLT", false /* reportMissing */)
+//                        property Fact battAmpPerVolt:   controller.getParameterFact(-1, "r.BATT2_AMP_PERVLT", false /* reportMissing */)
+//                        property Fact battAmpOffset:    controller.getParameterFact(-1, "BATT2_AMP_OFFSET", false /* reportMissing */)
+//                        property Fact battCapacity:     controller.getParameterFact(-1, "BATT2_CAPACITY", false /* reportMissing */)
+//                        property Fact battCurrPin:      controller.getParameterFact(-1, "BATT2_CURR_PIN", false /* reportMissing */)
+//                        property Fact battMonitor:      controller.getParameterFact(-1, "BATT2_MONITOR", false /* reportMissing */)
+//                        property Fact battVoltMult:     controller.getParameterFact(-1, "BATT2_VOLT_MULT", false /* reportMissing */)
+//                        property Fact battVoltPin:      controller.getParameterFact(-1, "BATT2_VOLT_PIN", false /* reportMissing */)
+//                        property FactGroup  _batteryFactGroup:  batt2FullSettings.visible ? controller.vehicle.getFactGroup("battery1") : null
+//                        property Fact vehicleVoltage:   _batteryFactGroup ? _batteryFactGroup.voltage : null
+//                        property Fact vehicleCurrent:   _batteryFactGroup ? _batteryFactGroup.current : null
+//                    }
+//                }
+//            }
+
+//            Column {
+//                spacing:    _margins / 2
+//                visible:    _escCalibrationAvailable
+
+//                QGCLabel {
+//                    text:       qsTr("ESC Calibration")
+//                    font.family: ScreenTools.demiboldFontFamily
+//                }
+
+//                Rectangle {
+//                    width:  escCalibrationHolder.x + escCalibrationHolder.width + _margins
+//                    height: escCalibrationHolder.y + escCalibrationHolder.height + _margins
+//                    color:  ggcPal.windowShade
+
+//                    Column {
+//                        id:         escCalibrationHolder
+//                        x:          _margins
+//                        y:          _margins
+//                        spacing:    _margins
+
+//                        Column {
+//                            spacing: _margins
+
+//                            QGCLabel {
+//                                text:   qsTr("WARNING: Remove props prior to calibration!")
+//                                color:  qgcPal.warningText
+//                            }
+
+//                            Row {
+//                                spacing: _margins
+
+//                                QGCButton {
+//                                    text: qsTr("Calibrate")
+//                                    enabled:    _escCalibration && _escCalibration.rawValue === 0
+//                                    onClicked:  if(_escCalibration) _escCalibration.rawValue = 3
+//                                }
+
+//                                Column {
+//                                    enabled: _escCalibration && _escCalibration.rawValue === 3
+//                                    QGCLabel { text:   _escCalibration ? (_escCalibration.rawValue === 3 ? qsTr("Now perform these steps:") : qsTr("Click Calibrate to start, then:")) : "" }
+//                                    QGCLabel { text:   qsTr("- Disconnect USB and battery so flight controller powers down") }
+//                                    QGCLabel { text:   qsTr("- Connect the battery") }
+//                                    QGCLabel { text:   qsTr("- The arming tone will be played (if the vehicle has a buzzer attached)") }
+//                                    QGCLabel { text:   qsTr("- If using a flight controller with a safety button press it until it displays solid red") }
+//                                    QGCLabel { text:   qsTr("- You will hear a musical tone then two beeps") }
+//                                    QGCLabel { text:   qsTr("- A few seconds later you should hear a number of beeps (one for each battery cell you're using)") }
+//                                    QGCLabel { text:   qsTr("- And finally a single long beep indicating the end points have been set and the ESC is calibrated") }
+//                                    QGCLabel { text:   qsTr("- Disconnect the battery and power up again normally") }
+//                                }
+//                            }
+//                        }
+//                    }
+//                }
+//            }
         } // Flow
     } // Component - powerPageComponent
 
@@ -289,24 +289,24 @@ SetupPage {
             spacing: _margins
 
             property real _margins:         ScreenTools.defaultFontPixelHeight / 2
-            property bool _showAdvanced:    sensorCombo.currentIndex === sensorModel.count - 1
+            property bool _showAdvanced:    false // sensorCombo.currentIndex === sensorModel.count - 1
             property real _fieldWidth:      ScreenTools.defaultFontPixelWidth * 25
 
-            Component.onCompleted: calcSensor()
-
-            function calcSensor() {
-                for (var i=0; i<sensorModel.count - 1; i++) {
-                    if (sensorModel.get(i).voltPin === battVoltPin.value &&
-                            sensorModel.get(i).currPin === battCurrPin.value &&
-                            Math.abs(sensorModel.get(i).voltMult - battVoltMult.value) < 0.001 &&
-                            Math.abs(sensorModel.get(i).ampPerVolt - battAmpPerVolt.value) < 0.0001 &&
-                            Math.abs(sensorModel.get(i).ampOffset - battAmpOffset.value) < 0.0001) {
-                        sensorCombo.currentIndex = i
-                        return
-                    }
-                }
-                sensorCombo.currentIndex = sensorModel.count - 1
-            }
+//            Component.onCompleted: calcSensor()
+
+//            function calcSensor() {
+//                for (var i=0; i<sensorModel.count - 1; i++) {
+//                    if (sensorModel.get(i).voltPin === battVoltPin.value &&
+//                            sensorModel.get(i).currPin === battCurrPin.value &&
+//                            Math.abs(sensorModel.get(i).voltMult - battVoltMult.value) < 0.001 &&
+//                            Math.abs(sensorModel.get(i).ampPerVolt - battAmpPerVolt.value) < 0.0001 &&
+//                            Math.abs(sensorModel.get(i).ampOffset - battAmpOffset.value) < 0.0001) {
+//                        sensorCombo.currentIndex = i
+//                        return
+//                    }
+//                }
+//                sensorCombo.currentIndex = sensorModel.count - 1
+//            }
 
             QGCPalette { id: palette; colorGroupEnabled: true }
 
@@ -369,14 +369,14 @@ SetupPage {
                 rowSpacing:     _margins
                 columnSpacing:  _margins
 
-                QGCLabel { text: qsTr("Battery monitor:") }
+//                QGCLabel { text: qsTr("Battery monitor:") }
 
-                FactComboBox {
-                    id:         monitorCombo
-                    fact:       battMonitor
-                    indexModel: false
-                    sizeToContents: true
-                }
+//                FactComboBox {
+//                    id:         monitorCombo
+//                    fact:       battMonitor
+//                    indexModel: false
+//                    sizeToContents: true
+//                }
 
                 QGCLabel {
                     Layout.row:     1
@@ -402,134 +402,134 @@ SetupPage {
                     fact:   armVoltMin
                 }
 
-                QGCLabel {
-                    Layout.row:     3
-                    Layout.column:  0
-                    text:           qsTr("Power sensor:")
-                }
-
-                QGCComboBox {
-                    id:                     sensorCombo
-                    Layout.minimumWidth:    _fieldWidth
-                    model:                  sensorModel
-                    textRole:               "text"
-
-                    onActivated: {
-                        if (index < sensorModel.count - 1) {
-                            battVoltPin.value = sensorModel.get(index).voltPin
-                            battCurrPin.value = sensorModel.get(index).currPin
-                            battVoltMult.value = sensorModel.get(index).voltMult
-                            battAmpPerVolt.value = sensorModel.get(index).ampPerVolt
-                            battAmpOffset.value = sensorModel.get(index).ampOffset
-                        } else {
-
-                        }
-                    }
-                }
-
-                QGCLabel {
-                    Layout.row:     4
-                    Layout.column:  0
-                    text:           qsTr("Current pin:")
-                    visible:        _showAdvanced
-                }
-
-                FactComboBox {
-                    Layout.minimumWidth:    _fieldWidth
-                    fact:                   battCurrPin
-                    indexModel:             false
-                    visible:                _showAdvanced
-                    sizeToContents:         true
-                }
-
-                QGCLabel {
-                    Layout.row:     5
-                    Layout.column:  0
-                    text:           qsTr("Voltage pin:")
-                    visible:        _showAdvanced
-                }
-
-                FactComboBox {
-                    Layout.minimumWidth:    _fieldWidth
-                    fact:                   battVoltPin
-                    indexModel:             false
-                    visible:                _showAdvanced
-                    sizeToContents:         true
-                }
-
-                QGCLabel {
-                    Layout.row:     6
-                    Layout.column:  0
-                    text:           qsTr("Voltage multiplier:")
-                    visible:        _showAdvanced
-                }
-
-                FactTextField {
-                    width:      _fieldWidth
-                    fact:       battVoltMult
-                    visible:    _showAdvanced
-                }
-
-                QGCButton {
-                    text:       qsTr("Calculate")
-                    visible:    _showAdvanced
-                    onClicked:  calcVoltageMultiplierDlgComponent.createObject(mainWindow, { vehicleVoltageFact: vehicleVoltage, battVoltMultFact: battVoltMult }).open()
-                }
-
-                QGCLabel {
-                    Layout.columnSpan:  3
-                    Layout.fillWidth:   true
-                    font.pointSize:     ScreenTools.smallFontPointSize
-                    wrapMode:           Text.WordWrap
-                    text:               qsTr("If the battery voltage reported by the vehicle is largely different than the voltage read externally using a voltmeter you can adjust the voltage multiplier value to correct this. Click the Calculate button for help with calculating a new value.")
-                    visible:            _showAdvanced
-                }
-
-                QGCLabel {
-                    text:       qsTr("Amps per volt:")
-                    visible:    _showAdvanced
-                }
-
-                FactTextField {
-                    width:      _fieldWidth
-                    fact:       battAmpPerVolt
-                    visible:    _showAdvanced
-                }
-
-                QGCButton {
-                    text:       qsTr("Calculate")
-                    visible:    _showAdvanced
-                    onClicked:  calcAmpsPerVoltDlgComponent.createObject(mainWindow, { vehicleCurrentFact: vehicleCurrent, battAmpPerVoltFact: battAmpPerVolt }).open()
-                }
-
-                QGCLabel {
-                    Layout.columnSpan:  3
-                    Layout.fillWidth:   true
-                    font.pointSize:     ScreenTools.smallFontPointSize
-                    wrapMode:           Text.WordWrap
-                    text:               qsTr("If the current draw reported by the vehicle is largely different than the current read externally using a current meter you can adjust the amps per volt value to correct this. Click the Calculate button for help with calculating a new value.")
-                    visible:            _showAdvanced
-                }
-
-                QGCLabel {
-                    text:       qsTr("Amps Offset:")
-                    visible:    _showAdvanced
-                }
-
-                FactTextField {
-                    width:      _fieldWidth
-                    fact:       battAmpOffset
-                    visible:    _showAdvanced
-                }
-
-                QGCLabel {
-                    Layout.columnSpan:  3
-                    Layout.fillWidth:   true
-                    font.pointSize:     ScreenTools.smallFontPointSize
-                    wrapMode:           Text.WordWrap
-                    text:               qsTr("If the vehicle reports a high current read when there is little or no current going through it, adjust the Amps Offset. It should be equal to the voltage reported by the sensor when the current is zero.")
-                    visible:            _showAdvanced
-                }
+//                QGCLabel {
+//                    Layout.row:     3
+//                    Layout.column:  0
+//                    text:           qsTr("Power sensor:")
+//                }
+
+//                QGCComboBox {
+//                    id:                     sensorCombo
+//                    Layout.minimumWidth:    _fieldWidth
+//                    model:                  sensorModel
+//                    textRole:               "text"
+
+//                    onActivated: {
+//                        if (index < sensorModel.count - 1) {
+//                            battVoltPin.value = sensorModel.get(index).voltPin
+//                            battCurrPin.value = sensorModel.get(index).currPin
+//                            battVoltMult.value = sensorModel.get(index).voltMult
+//                            battAmpPerVolt.value = sensorModel.get(index).ampPerVolt
+//                            battAmpOffset.value = sensorModel.get(index).ampOffset
+//                        } else {
+
+//                        }
+//                    }
+//                }
+
+//                QGCLabel {
+//                    Layout.row:     4
+//                    Layout.column:  0
+//                    text:           qsTr("Current pin:")
+//                    visible:        _showAdvanced
+//                }
+
+//                FactComboBox {
+//                    Layout.minimumWidth:    _fieldWidth
+//                    fact:                   battCurrPin
+//                    indexModel:             false
+//                    visible:                _showAdvanced
+//                    sizeToContents:         true
+//                }
+
+//                QGCLabel {
+//                    Layout.row:     5
+//                    Layout.column:  0
+//                    text:           qsTr("Voltage pin:")
+//                    visible:        _showAdvanced
+//                }
+
+//                FactComboBox {
+//                    Layout.minimumWidth:    _fieldWidth
+//                    fact:                   battVoltPin
+//                    indexModel:             false
+//                    visible:                _showAdvanced
+//                    sizeToContents:         true
+//                }
+
+//                QGCLabel {
+//                    Layout.row:     6
+//                    Layout.column:  0
+//                    text:           qsTr("Voltage multiplier:")
+//                    visible:        _showAdvanced
+//                }
+
+//                FactTextField {
+//                    width:      _fieldWidth
+//                    fact:       battVoltMult
+//                    visible:    _showAdvanced
+//                }
+
+//                QGCButton {
+//                    text:       qsTr("Calculate")
+//                    visible:    _showAdvanced
+//                    onClicked:  calcVoltageMultiplierDlgComponent.createObject(mainWindow, { vehicleVoltageFact: vehicleVoltage, battVoltMultFact: battVoltMult }).open()
+//                }
+
+//                QGCLabel {
+//                    Layout.columnSpan:  3
+//                    Layout.fillWidth:   true
+//                    font.pointSize:     ScreenTools.smallFontPointSize
+//                    wrapMode:           Text.WordWrap
+//                    text:               qsTr("If the battery voltage reported by the vehicle is largely different than the voltage read externally using a voltmeter you can adjust the voltage multiplier value to correct this. Click the Calculate button for help with calculating a new value.")
+//                    visible:            _showAdvanced
+//                }
+
+//                QGCLabel {
+//                    text:       qsTr("Amps per volt:")
+//                    visible:    _showAdvanced
+//                }
+
+//                FactTextField {
+//                    width:      _fieldWidth
+//                    fact:       battAmpPerVolt
+//                    visible:    _showAdvanced
+//                }
+
+//                QGCButton {
+//                    text:       qsTr("Calculate")
+//                    visible:    _showAdvanced
+//                    onClicked:  calcAmpsPerVoltDlgComponent.createObject(mainWindow, { vehicleCurrentFact: vehicleCurrent, battAmpPerVoltFact: battAmpPerVolt }).open()
+//                }
+
+//                QGCLabel {
+//                    Layout.columnSpan:  3
+//                    Layout.fillWidth:   true
+//                    font.pointSize:     ScreenTools.smallFontPointSize
+//                    wrapMode:           Text.WordWrap
+//                    text:               qsTr("If the current draw reported by the vehicle is largely different than the current read externally using a current meter you can adjust the amps per volt value to correct this. Click the Calculate button for help with calculating a new value.")
+//                    visible:            _showAdvanced
+//                }
+
+//                QGCLabel {
+//                    text:       qsTr("Amps Offset:")
+//                    visible:    _showAdvanced
+//                }
+
+//                FactTextField {
+//                    width:      _fieldWidth
+//                    fact:       battAmpOffset
+//                    visible:    _showAdvanced
+//                }
+
+//                QGCLabel {
+//                    Layout.columnSpan:  3
+//                    Layout.fillWidth:   true
+//                    font.pointSize:     ScreenTools.smallFontPointSize
+//                    wrapMode:           Text.WordWrap
+//                    text:               qsTr("If the vehicle reports a high current read when there is little or no current going through it, adjust the Amps Offset. It should be equal to the voltage reported by the sensor when the current is zero.")
+//                    visible:            _showAdvanced
+//                }
 
             } // GridLayout
         } // Column
diff --git a/src/AutoPilotPlugins/APM/APMSafetyComponent.qml b/src/AutoPilotPlugins/APM/APMSafetyComponent.qml
index 8c75d700b..6a768a850 100644
--- a/src/AutoPilotPlugins/APM/APMSafetyComponent.qml
+++ b/src/AutoPilotPlugins/APM/APMSafetyComponent.qml
@@ -718,47 +718,47 @@ SetupPage {
                 sourceComponent: controller.vehicle.fixedWing ? planeRTL : undefined
             }
 
-            Column {
-                spacing: _margins / 2
-
-                QGCLabel {
-                    text:           qsTr("Arming Checks")
-                    font.family:    ScreenTools.demiboldFontFamily
-                }
-
-                Rectangle {
-                    width:  flowLayout.width
-                    height: armingCheckInnerColumn.height + (_margins * 2)
-                    color:  ggcPal.windowShade
-
-                    Column {
-                        id:                 armingCheckInnerColumn
-                        anchors.margins:    _margins
-                        anchors.top:        parent.top
-                        anchors.left:       parent.left
-                        anchors.right:      parent.right
-                        spacing: _margins
-
-                        FactBitmask {
-                            id:                 armingCheckBitmask
-                            anchors.left:       parent.left
-                            anchors.right:      parent.right
-                            firstEntryIsAll:    true
-                            fact:               _armingCheck
-                        }
-
-                        QGCLabel {
-                            id:             armingCheckWarning
-                            anchors.left:   parent.left
-                            anchors.right:  parent.right
-                            wrapMode:       Text.WordWrap
-                            color:          qgcPal.warningText
-                            text:            qsTr("Warning: Turning off arming checks can lead to loss of Vehicle control.")
-                            visible:        _armingCheck.value != 1
-                        }
-                    }
-                } // Rectangle - Arming checks
-            } // Column - Arming Checks
+//            Column {
+//                spacing: _margins / 2
+
+//                QGCLabel {
+//                    text:           qsTr("Arming Checks")
+//                    font.family:    ScreenTools.demiboldFontFamily
+//                }
+
+//                Rectangle {
+//                    width:  flowLayout.width
+//                    height: armingCheckInnerColumn.height + (_margins * 2)
+//                    color:  ggcPal.windowShade
+
+//                    Column {
+//                        id:                 armingCheckInnerColumn
+//                        anchors.margins:    _margins
+//                        anchors.top:        parent.top
+//                        anchors.left:       parent.left
+//                        anchors.right:      parent.right
+//                        spacing: _margins
+
+//                        FactBitmask {
+//                            id:                 armingCheckBitmask
+//                            anchors.left:       parent.left
+//                            anchors.right:      parent.right
+//                            firstEntryIsAll:    true
+//                            fact:               _armingCheck
+//                        }
+
+//                        QGCLabel {
+//                            id:             armingCheckWarning
+//                            anchors.left:   parent.left
+//                            anchors.right:  parent.right
+//                            wrapMode:       Text.WordWrap
+//                            color:          qgcPal.warningText
+//                            text:            qsTr("Warning: Turning off arming checks can lead to loss of Vehicle control.")
+//                            visible:        _armingCheck.value != 1
+//                        }
+//                    }
+//                } // Rectangle - Arming checks
+//            } // Column - Arming Checks
         } // Flow
     } // Component - safetyPageComponent
 } // SetupView
diff --git a/src/AutoPilotPlugins/APM/APMSensorsComponent.qml b/src/AutoPilotPlugins/APM/APMSensorsComponent.qml
index b032bca7b..289bf357b 100644
--- a/src/AutoPilotPlugins/APM/APMSensorsComponent.qml
+++ b/src/AutoPilotPlugins/APM/APMSensorsComponent.qml
@@ -446,150 +446,150 @@ SetupPage {
                         }
                     }
 
-                    Column {
-                        width:      40 * ScreenTools.defaultFontPixelWidth
-                        spacing:    ScreenTools.defaultFontPixelHeight
-
-                        QGCLabel {
-                            width:      parent.width
-                            wrapMode:   Text.WordWrap
-                            text:       _orientationDialogHelp
-                        }
-
-                        Column {
-                            QGCLabel { text: qsTr("Autopilot Rotation:") }
-
-                            FactComboBox {
-                                width:      rotationColumnWidth
-                                indexModel: false
-                                fact:       boardRot
-                            }
-                        }
-
-                        Column {
-
-                            visible: _orientationDialogCalType == _calTypeAccel
-                            spacing: ScreenTools.defaultFontPixelHeight
-
-                            QGCLabel {
-                                width:      parent.width
-                                wrapMode:   Text.WordWrap
-                                text: qsTr("Simple accelerometer calibration is less precise but allows calibrating without rotating the vehicle. Check this if you have a large/heavy vehicle.")
-                            }
-
-                            QGCCheckBox {
-                                text: "Simple Accelerometer Calibration"
-                                onClicked: _doSimpleAccelCal = this.checked
-                            }
-                        }
-
-                        Repeater {
-                            model:      _orientationsDialogShowCompass ? 3 : 0
-                            delegate:   singleCompassSettingsComponent
-                        }
-
-                        QGCLabel {
-                            id:         magneticDeclinationLabel
-                            width:      parent.width
-                            visible:    globals.activeVehicle.sub && _orientationsDialogShowCompass
-                            text:       qsTr("Magnetic Declination")
-                        }
-
-                        Column {
-                            visible:            magneticDeclinationLabel.visible
-                            anchors.margins:    ScreenTools.defaultFontPixelWidth
-                            anchors.left:       parent.left
-                            anchors.right:      parent.right
-                            spacing:            ScreenTools.defaultFontPixelHeight
-
-                            QGCCheckBox {
-                                id:                           manualMagneticDeclinationCheckBox
-                                text:                         qsTr("Manual Magnetic Declination")
-                                property Fact autoDecFact:    controller.getParameterFact(-1, "COMPASS_AUTODEC")
-                                property int manual:          0
-                                property int automatic:       1
-
-                                checked:    autoDecFact.rawValue === manual
-                                onClicked:  autoDecFact.value = (checked ? manual : automatic)
-                            }
-
-                            FactTextField {
-                                fact:       sensorParams.declinationFact
-                                enabled:    manualMagneticDeclinationCheckBox.checked
-                            }
-                        }
-
-                        Item { height: ScreenTools.defaultFontPixelHeight; width: 10 } // spacer
-
-                        QGCLabel {
-                            id:         northCalibrationLabel
-                            width:      parent.width
-                            visible:    _orientationsDialogShowCompass
-                            wrapMode:   Text.WordWrap
-                            text:       qsTr("Fast compass calibration given vehicle position and yaw. This ") +
-                                        qsTr("results in zero diagonal and off-diagonal elements, so is only ") +
-                                        qsTr("suitable for vehicles where the field is close to spherical. It is ") +
-                                        qsTr("useful for large vehicles where moving the vehicle to calibrate it ") +
-                                        qsTr("is difficult. Point the vehicle North before using it.")
-                        }
-
-                        Column {
-                            visible:            northCalibrationLabel.visible
-                            anchors.margins:    ScreenTools.defaultFontPixelWidth
-                            anchors.left:       parent.left
-                            anchors.right:      parent.right
-                            spacing:            ScreenTools.defaultFontPixelHeight
-
-                            QGCCheckBox {
-                                id:             northCalibrationCheckBox
-                                visible:        northCalibrationLabel.visible
-                                text:           qsTr("Fast Calibration")
-                            }
-
-                            QGCLabel {
-                                id:         northCalibrationManualPosition
-                                width:      parent.width
-                                visible:    northCalibrationCheckBox.checked && !globals.activeVehicle.coordinate.isValid
-                                wrapMode:   Text.WordWrap
-                                text:       qsTr("Vehicle has no Valid positon, please provide it")
-                            }
-
-                            QGCCheckBox {
-                                visible:    northCalibrationManualPosition.visible && _gcsPosition.isValid
-                                id:         useGcsPositionCheckbox
-                                text:       qsTr("Use GCS position instead")
-                                checked:    _gcsPosition.isValid
-                            }
-                            QGCCheckBox {
-                                visible:    northCalibrationManualPosition.visible && !_gcsPosition.isValid
-                                id:         useMapPositionCheckbox
-                                text:       qsTr("Use current map position instead")
-                            }
-
-                            QGCLabel {
-                                width:      parent.width
-                                visible:    useMapPositionCheckbox.checked
-                                wrapMode:   Text.WordWrap
-                                text:       qsTr(`Lat: ${_mapPosition.latitude.toFixed(4)} Lon: ${_mapPosition.longitude.toFixed(4)}`)
-                            }
-
-                            FactTextField {
-                                id:         northCalLat
-                                visible:    !useGcsPositionCheckbox.checked && !useMapPositionCheckbox.checked && northCalibrationCheckBox.checked
-                                text:       "0.00"
-                                textColor:  isNaN(parseFloat(text)) ? qgcPal.warningText: qgcPal.textFieldText
-                                enabled:    !useGcsPositionCheckbox.checked
-                            }
-                            FactTextField {
-                                id:         northCalLon
-                                visible:    !useGcsPositionCheckbox.checked && !useMapPositionCheckbox.checked && northCalibrationCheckBox.checked
-                                text:       "0.00"
-                                textColor:  isNaN(parseFloat(text)) ? qgcPal.warningText: qgcPal.textFieldText
-                                enabled:    !useGcsPositionCheckbox.checked
-                            }
-
-                        }
-                    }
+//                    Column {
+//                        width:      40 * ScreenTools.defaultFontPixelWidth
+//                        spacing:    ScreenTools.defaultFontPixelHeight
+
+//                        QGCLabel {
+//                            width:      parent.width
+//                            wrapMode:   Text.WordWrap
+//                            text:       _orientationDialogHelp
+//                        }
+
+//                        Column {
+//                            QGCLabel { text: qsTr("Autopilot Rotation:") }
+
+//                            FactComboBox {
+//                                width:      rotationColumnWidth
+//                                indexModel: false
+//                                fact:       boardRot
+//                            }
+//                        }
+
+//                        Column {
+
+//                            visible: _orientationDialogCalType == _calTypeAccel
+//                            spacing: ScreenTools.defaultFontPixelHeight
+
+//                            QGCLabel {
+//                                width:      parent.width
+//                                wrapMode:   Text.WordWrap
+//                                text: qsTr("Simple accelerometer calibration is less precise but allows calibrating without rotating the vehicle. Check this if you have a large/heavy vehicle.")
+//                            }
+
+//                            QGCCheckBox {
+//                                text: "Simple Accelerometer Calibration"
+//                                onClicked: _doSimpleAccelCal = this.checked
+//                            }
+//                        }
+
+//                        Repeater {
+//                            model:      _orientationsDialogShowCompass ? 3 : 0
+//                            delegate:   singleCompassSettingsComponent
+//                        }
+
+//                        QGCLabel {
+//                            id:         magneticDeclinationLabel
+//                            width:      parent.width
+//                            visible:    globals.activeVehicle.sub && _orientationsDialogShowCompass
+//                            text:       qsTr("Magnetic Declination")
+//                        }
+
+//                        Column {
+//                            visible:            magneticDeclinationLabel.visible
+//                            anchors.margins:    ScreenTools.defaultFontPixelWidth
+//                            anchors.left:       parent.left
+//                            anchors.right:      parent.right
+//                            spacing:            ScreenTools.defaultFontPixelHeight
+
+//                            QGCCheckBox {
+//                                id:                           manualMagneticDeclinationCheckBox
+//                                text:                         qsTr("Manual Magnetic Declination")
+//                                property Fact autoDecFact:    controller.getParameterFact(-1, "COMPASS_AUTODEC")
+//                                property int manual:          0
+//                                property int automatic:       1
+
+//                                checked:    autoDecFact.rawValue === manual
+//                                onClicked:  autoDecFact.value = (checked ? manual : automatic)
+//                            }
+
+//                            FactTextField {
+//                                fact:       sensorParams.declinationFact
+//                                enabled:    manualMagneticDeclinationCheckBox.checked
+//                            }
+//                        }
+
+//                        Item { height: ScreenTools.defaultFontPixelHeight; width: 10 } // spacer
+
+//                        QGCLabel {
+//                            id:         northCalibrationLabel
+//                            width:      parent.width
+//                            visible:    _orientationsDialogShowCompass
+//                            wrapMode:   Text.WordWrap
+//                            text:       qsTr("Fast compass calibration given vehicle position and yaw. This ") +
+//                                        qsTr("results in zero diagonal and off-diagonal elements, so is only ") +
+//                                        qsTr("suitable for vehicles where the field is close to spherical. It is ") +
+//                                        qsTr("useful for large vehicles where moving the vehicle to calibrate it ") +
+//                                        qsTr("is difficult. Point the vehicle North before using it.")
+//                        }
+
+//                        Column {
+//                            visible:            northCalibrationLabel.visible
+//                            anchors.margins:    ScreenTools.defaultFontPixelWidth
+//                            anchors.left:       parent.left
+//                            anchors.right:      parent.right
+//                            spacing:            ScreenTools.defaultFontPixelHeight
+
+//                            QGCCheckBox {
+//                                id:             northCalibrationCheckBox
+//                                visible:        northCalibrationLabel.visible
+//                                text:           qsTr("Fast Calibration")
+//                            }
+
+//                            QGCLabel {
+//                                id:         northCalibrationManualPosition
+//                                width:      parent.width
+//                                visible:    northCalibrationCheckBox.checked && !globals.activeVehicle.coordinate.isValid
+//                                wrapMode:   Text.WordWrap
+//                                text:       qsTr("Vehicle has no Valid positon, please provide it")
+//                            }
+
+//                            QGCCheckBox {
+//                                visible:    northCalibrationManualPosition.visible && _gcsPosition.isValid
+//                                id:         useGcsPositionCheckbox
+//                                text:       qsTr("Use GCS position instead")
+//                                checked:    _gcsPosition.isValid
+//                            }
+//                            QGCCheckBox {
+//                                visible:    northCalibrationManualPosition.visible && !_gcsPosition.isValid
+//                                id:         useMapPositionCheckbox
+//                                text:       qsTr("Use current map position instead")
+//                            }
+
+//                            QGCLabel {
+//                                width:      parent.width
+//                                visible:    useMapPositionCheckbox.checked
+//                                wrapMode:   Text.WordWrap
+//                                text:       qsTr(`Lat: ${_mapPosition.latitude.toFixed(4)} Lon: ${_mapPosition.longitude.toFixed(4)}`)
+//                            }
+
+//                            FactTextField {
+//                                id:         northCalLat
+//                                visible:    !useGcsPositionCheckbox.checked && !useMapPositionCheckbox.checked && northCalibrationCheckBox.checked
+//                                text:       "0.00"
+//                                textColor:  isNaN(parseFloat(text)) ? qgcPal.warningText: qgcPal.textFieldText
+//                                enabled:    !useGcsPositionCheckbox.checked
+//                            }
+//                            FactTextField {
+//                                id:         northCalLon
+//                                visible:    !useGcsPositionCheckbox.checked && !useMapPositionCheckbox.checked && northCalibrationCheckBox.checked
+//                                text:       "0.00"
+//                                textColor:  isNaN(parseFloat(text)) ? qgcPal.warningText: qgcPal.textFieldText
+//                                enabled:    !useGcsPositionCheckbox.checked
+//                            }
+
+//                        }
+//                    }
                 }
             }
 
@@ -687,59 +687,59 @@ SetupPage {
                         }
                     }
 
-                    QGCButton {
-                        width:  _buttonWidth
-                        text:   _levelHorizonText
-
-                        readonly property string _levelHorizonText: qsTr("Level Horizon")
-
-                        onClicked: {
-                            if (controller.accelSetupNeeded) {
-                                mainWindow.showMessageDialog(_levelHorizonText, qsTr("Accelerometer must be calibrated prior to Level Horizon."))
-                            } else {
-                                mainWindow.showMessageDialog(_levelHorizonText,
-                                                             qsTr("To level the horizon you need to place the vehicle in its level flight position and press Ok."),
-                                                             StandardButton.Cancel | StandardButton.Ok,
-                                                             function() { controller.levelHorizon() })
-                            }
-                        }
-                    }
-
-                    QGCButton {
-                        width:      _buttonWidth
-                        text:       qsTr("Gyro")
-                        visible:    globals.activeVehicle && (globals.activeVehicle.multiRotor | globals.activeVehicle.rover | globals.activeVehicle.sub)
-                        onClicked:  mainWindow.showMessageDialog(qsTr("Calibrate Gyro"),
-                                                                 qsTr("For Gyroscope calibration you will need to place your vehicle on a surface and leave it still.\n\nClick Ok to start calibration."),
-                                                                 StandardButton.Cancel | StandardButton.Ok,
-                                                                 function() { controller.calibrateGyro() })
-                    }
-
-                    QGCButton {
-                        width:      _buttonWidth
-                        text:       _calibratePressureText
-                        onClicked:  mainWindow.showMessageDialog(_calibratePressureText,
-                                                                 qsTr("Pressure calibration will set the %1 to zero at the current pressure reading. %2").arg(_altText).arg(_helpTextFW),
-                                                                 StandardButton.Cancel | StandardButton.Ok,
-                                                                 function() { controller.calibratePressure() })
-
-                        readonly property string _altText:                  globals.activeVehicle.sub ? qsTr("depth") : qsTr("altitude")
-                        readonly property string _helpTextFW:               globals.activeVehicle.fixedWing ? qsTr("To calibrate the airspeed sensor shield it from the wind. Do not touch the sensor or obstruct any holes during the calibration.") : ""
-                        readonly property string _calibratePressureText:    globals.activeVehicle.fixedWing ? qsTr("Baro/Airspeed") : qsTr("Pressure")
-                    }
-
-                    QGCButton {
-                        width:      _buttonWidth
-                        text:       qsTr("CompassMot")
-                        visible:    globals.activeVehicle ? globals.activeVehicle.supportsMotorInterference : false
-                        onClicked:  compassMotDialogComponent.createObject(mainWindow).open()
-                    }
-
-                    QGCButton {
-                        width:      _buttonWidth
-                        text:       qsTr("Sensor Settings")
-                        onClicked:  showOrientationsDialog(_calTypeSet)
-                    }
+//                    QGCButton {
+//                        width:  _buttonWidth
+//                        text:   _levelHorizonText
+
+//                        readonly property string _levelHorizonText: qsTr("Level Horizon")
+
+//                        onClicked: {
+//                            if (controller.accelSetupNeeded) {
+//                                mainWindow.showMessageDialog(_levelHorizonText, qsTr("Accelerometer must be calibrated prior to Level Horizon."))
+//                            } else {
+//                                mainWindow.showMessageDialog(_levelHorizonText,
+//                                                             qsTr("To level the horizon you need to place the vehicle in its level flight position and press Ok."),
+//                                                             StandardButton.Cancel | StandardButton.Ok,
+//                                                             function() { controller.levelHorizon() })
+//                            }
+//                        }
+//                    }
+
+//                    QGCButton {
+//                        width:      _buttonWidth
+//                        text:       qsTr("Gyro")
+//                        visible:    globals.activeVehicle && (globals.activeVehicle.multiRotor | globals.activeVehicle.rover | globals.activeVehicle.sub)
+//                        onClicked:  mainWindow.showMessageDialog(qsTr("Calibrate Gyro"),
+//                                                                 qsTr("For Gyroscope calibration you will need to place your vehicle on a surface and leave it still.\n\nClick Ok to start calibration."),
+//                                                                 StandardButton.Cancel | StandardButton.Ok,
+//                                                                 function() { controller.calibrateGyro() })
+//                    }
+
+//                    QGCButton {
+//                        width:      _buttonWidth
+//                        text:       _calibratePressureText
+//                        onClicked:  mainWindow.showMessageDialog(_calibratePressureText,
+//                                                                 qsTr("Pressure calibration will set the %1 to zero at the current pressure reading. %2").arg(_altText).arg(_helpTextFW),
+//                                                                 StandardButton.Cancel | StandardButton.Ok,
+//                                                                 function() { controller.calibratePressure() })
+
+//                        readonly property string _altText:                  globals.activeVehicle.sub ? qsTr("depth") : qsTr("altitude")
+//                        readonly property string _helpTextFW:               globals.activeVehicle.fixedWing ? qsTr("To calibrate the airspeed sensor shield it from the wind. Do not touch the sensor or obstruct any holes during the calibration.") : ""
+//                        readonly property string _calibratePressureText:    globals.activeVehicle.fixedWing ? qsTr("Baro/Airspeed") : qsTr("Pressure")
+//                    }
+
+//                    QGCButton {
+//                        width:      _buttonWidth
+//                        text:       qsTr("CompassMot")
+//                        visible:    globals.activeVehicle ? globals.activeVehicle.supportsMotorInterference : false
+//                        onClicked:  compassMotDialogComponent.createObject(mainWindow).open()
+//                    }
+
+//                    QGCButton {
+//                        width:      _buttonWidth
+//                        text:       qsTr("Sensor Settings")
+//                        onClicked:  showOrientationsDialog(_calTypeSet)
+//                    }
                 } // Column - Cal Buttons
 
                 Column {
diff --git a/src/AutoPilotPlugins/Common/RadioComponent.qml b/src/AutoPilotPlugins/Common/RadioComponent.qml
index b429e815b..7437fadb8 100644
--- a/src/AutoPilotPlugins/Common/RadioComponent.qml
+++ b/src/AutoPilotPlugins/Common/RadioComponent.qml
@@ -347,7 +347,7 @@ SetupPage {
                     border.width:   1
                 }
 
-                QGCLabel { text: qsTr("Additional Radio setup:") }
+                //QGCLabel { text: qsTr("Additional Radio setup:") }
 
                 GridLayout {
                     id:                 switchSettingsGrid
@@ -381,21 +381,21 @@ SetupPage {
                     }
                 }
 
-                RowLayout {
-                    QGCButton {
-                        id:         bindButton
-                        text:       qsTr("Spektrum Bind")
-                        onClicked:  spektrumBindDialogComponent.createObject(mainWindow).open()
-                    }
-
-                    QGCButton {
-                        text:       qsTr("Copy Trims")
-                        onClicked:  mainWindow.showMessageDialog(qsTr("Copy Trims"),
-                                                                 qsTr("Center your sticks and move throttle all the way down, then press Ok to copy trims. After pressing Ok, reset the trims on your radio back to zero."),
-                                                                 StandardButton.Ok | StandardButton.Cancel,
-                                                                 function() { controller.copyTrims() })
-                    }
-                }
+//                RowLayout {
+//                    QGCButton {
+//                        id:         bindButton
+//                        text:       qsTr("Spektrum Bind")
+//                        onClicked:  spektrumBindDialogComponent.createObject(mainWindow).open()
+//                    }
+
+//                    QGCButton {
+//                        text:       qsTr("Copy Trims")
+//                        onClicked:  mainWindow.showMessageDialog(qsTr("Copy Trims"),
+//                                                                 qsTr("Center your sticks and move throttle all the way down, then press Ok to copy trims. After pressing Ok, reset the trims on your radio back to zero."),
+//                                                                 StandardButton.Ok | StandardButton.Cancel,
+//                                                                 function() { controller.copyTrims() })
+//                    }
+//                }
             } // Column - Left Column
 
             Item {
diff --git a/src/FirmwarePlugin/APM/APMBrandImage.png b/src/FirmwarePlugin/APM/APMBrandImage.png
old mode 100644
new mode 100755
index 2a0692eca..3e2ea074e
Binary files a/src/FirmwarePlugin/APM/APMBrandImage.png and b/src/FirmwarePlugin/APM/APMBrandImage.png differ
diff --git a/src/FirmwarePlugin/APM/ArduCopterFirmwarePlugin.cc b/src/FirmwarePlugin/APM/ArduCopterFirmwarePlugin.cc
index d54e25a3f..4f2f97cfe 100644
--- a/src/FirmwarePlugin/APM/ArduCopterFirmwarePlugin.cc
+++ b/src/FirmwarePlugin/APM/ArduCopterFirmwarePlugin.cc
@@ -56,31 +56,31 @@ ArduCopterFirmwarePlugin::ArduCopterFirmwarePlugin(void)
 {
     setSupportedModes({
         APMCopterMode(APMCopterMode::STABILIZE,     true),
-        APMCopterMode(APMCopterMode::ACRO,          true),
+        APMCopterMode(APMCopterMode::ACRO,          false),
         APMCopterMode(APMCopterMode::ALT_HOLD,      true),
         APMCopterMode(APMCopterMode::AUTO,          true),
-        APMCopterMode(APMCopterMode::GUIDED,        true),
+        APMCopterMode(APMCopterMode::GUIDED,        false),
         APMCopterMode(APMCopterMode::LOITER,        true),
         APMCopterMode(APMCopterMode::RTL,           true),
-        APMCopterMode(APMCopterMode::CIRCLE,        true),
+        APMCopterMode(APMCopterMode::CIRCLE,        false),
         APMCopterMode(APMCopterMode::LAND,          true),
-        APMCopterMode(APMCopterMode::DRIFT,         true),
-        APMCopterMode(APMCopterMode::SPORT,         true),
-        APMCopterMode(APMCopterMode::FLIP,          true),
-        APMCopterMode(APMCopterMode::AUTOTUNE,      true),
-        APMCopterMode(APMCopterMode::POS_HOLD,      true),
-        APMCopterMode(APMCopterMode::BRAKE,         true),
-        APMCopterMode(APMCopterMode::THROW,         true),
-        APMCopterMode(APMCopterMode::AVOID_ADSB,    true),
-        APMCopterMode(APMCopterMode::GUIDED_NOGPS,  true),
-        APMCopterMode(APMCopterMode::SMART_RTL,     true),
-        APMCopterMode(APMCopterMode::FLOWHOLD,      true),
-        APMCopterMode(APMCopterMode::FOLLOW,        true),
-        APMCopterMode(APMCopterMode::ZIGZAG,        true),
-        APMCopterMode(APMCopterMode::SYSTEMID,      true),
-        APMCopterMode(APMCopterMode::AUTOROTATE,    true),
-        APMCopterMode(APMCopterMode::AUTO_RTL,      true),
-        APMCopterMode(APMCopterMode::TURTLE,        true),
+        APMCopterMode(APMCopterMode::DRIFT,         false),
+        APMCopterMode(APMCopterMode::SPORT,         false),
+        APMCopterMode(APMCopterMode::FLIP,          false),
+        APMCopterMode(APMCopterMode::AUTOTUNE,      false),
+        APMCopterMode(APMCopterMode::POS_HOLD,      false),
+        APMCopterMode(APMCopterMode::BRAKE,         false),
+        APMCopterMode(APMCopterMode::THROW,         false),
+        APMCopterMode(APMCopterMode::AVOID_ADSB,    false),
+        APMCopterMode(APMCopterMode::GUIDED_NOGPS,  false),
+        APMCopterMode(APMCopterMode::SMART_RTL,     false),
+        APMCopterMode(APMCopterMode::FLOWHOLD,      false),
+        APMCopterMode(APMCopterMode::FOLLOW,        false),
+        APMCopterMode(APMCopterMode::ZIGZAG,        false),
+        APMCopterMode(APMCopterMode::SYSTEMID,      false),
+        APMCopterMode(APMCopterMode::AUTOROTATE,    false),
+        APMCopterMode(APMCopterMode::AUTO_RTL,      false),
+        APMCopterMode(APMCopterMode::TURTLE,        false),
     });
 
     if (!_remapParamNameIntialized) {
diff --git a/src/FirmwarePlugin/FirmwarePlugin.cc b/src/FirmwarePlugin/FirmwarePlugin.cc
index b8d753c61..7919103af 100644
--- a/src/FirmwarePlugin/FirmwarePlugin.cc
+++ b/src/FirmwarePlugin/FirmwarePlugin.cc
@@ -357,577 +357,628 @@ const QVariantList& FirmwarePlugin::cameraList(const Vehicle*)
         CameraMetaData* metaData;
 
         metaData = new CameraMetaData(
-                    // Canon S100 @ 5.2mm f/2
-                    "Canon S100 PowerShot",     // canonical name saved in plan file
-                    tr("Canon"),                // brand
-                    tr("S100 PowerShot"),       // model
-                    7.6,                        // sensorWidth
-                    5.7,                        // sensorHeight
-                    4000,                       // imageWidth
-                    3000,                       // imageHeight
-                    5.2,                        // focalLength
+                    // Sony ILX-LR1 with 35mm Lens
+                    "Sony ILX-LR1-35mm",     // canonical name saved in plan file
+                    tr("Sony"),                // brand
+                    tr("ILX-LR1-35mm"),       // model
+                    35.81,                        // sensorWidth
+                    23.88,                        // sensorHeight
+                    7360,                       // imageWidth
+                    4912,                       // imageHeight
+                    35,                        // focalLength
                     true,                       // true: landscape orientation
                     false,                      // true: camera is fixed orientation
-                    0,                          // minimum trigger interval
-                    tr("Canon S100 PowerShot"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+                    0.4,                          // minimum trigger interval
+                    tr("Sony ILX-LR1-35mm"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
                     this);                      // parent
         _cameraList.append(QVariant::fromValue(metaData));
 
         metaData = new CameraMetaData(
-                    //tr("Canon EOS-M 22mm f/2"),
-                    "Canon EOS-M 22mm",
-                    tr("Canon"),
-                    tr("EOS-M 22mm"),
-                    22.3,                   // sensorWidth
-                    14.9,                   // sensorHeight
-                    5184,                   // imageWidth
-                    3456,                   // imageHeight
-                    22,                     // focalLength
-                    true,                   // true: landscape orientation
-                    false,                  // true: camera is fixed orientation
-                    0,                      // minimum trigger interval
-                    tr("Canon EOS-M 22mm"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);                  // parent
+                    // Sony ILX-LR1 with 35mm Lens
+                    "Sony ILX-LR1-21mm",     // canonical name saved in plan file
+                    tr("Sony"),                // brand
+                    tr("ILX-LR1-21mm"),       // model
+                    35.81,                        // sensorWidth
+                    23.88,                        // sensorHeight
+                    7360,                       // imageWidth
+                    4912,                       // imageHeight
+                    21,                        // focalLength
+                    true,                       // true: landscape orientation
+                    false,                      // true: camera is fixed orientation
+                    0.4,                          // minimum trigger interval
+                    tr("Sony ILX-LR1-21mm"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+                    this);                      // parent
         _cameraList.append(QVariant::fromValue(metaData));
 
         metaData = new CameraMetaData(
-                    // Canon G9X @ 10.2mm f/2
-                    "Canon G9 X PowerShot",
-                    tr("Canon"),
-                    tr("G9 X PowerShot"),
-                    13.2,                       // sensorWidth
-                    8.8,                        // sensorHeight
-                    5488,                       // imageWidth
-                    3680,                       // imageHeight
-                    10.2,                       // focalLength
+                    // RESEPI HESAI XT32 LiDAR
+                    "Hesai XT32",     // canonical name saved in plan file
+                    tr("Inertial Labs"),                // brand
+                    tr("RESEPI HESAI XT32"),       // model
+                    23.50,                        // sensorWidth
+                    15.60,                        // sensorHeight
+                    6058,                       // imageWidth
+                    4012,                       // imageHeight
+                    18,                        // focalLength
                     true,                       // true: landscape orientation
                     false,                      // true: camera is fixed orientation
                     0,                          // minimum trigger interval
-                    tr("Canon G9 X PowerShot"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+                    tr("RESEPI HESAI XT32"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
                     this);                      // parent
         _cameraList.append(QVariant::fromValue(metaData));
 
-        metaData = new CameraMetaData(
-                    // Canon SX260 HS @ 4.5mm f/3.5
-                    "Canon SX260 HS PowerShot",
-                    tr("Canon"),
-                    tr("SX260 HS PowerShot"),
-                    6.17,                           // sensorWidth
-                    4.55,                           // sensorHeight
-                    4000,                           // imageWidth
-                    3000,                           // imageHeight
-                    4.5,                            // focalLength
-                    true,                           // true: landscape orientation
-                    false,                          // true: camera is fixed orientation
-                    0,                              // minimum trigger interval
-                    tr("Canon SX260 HS PowerShot"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);                          // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "GoPro Hero 4",
-                    tr("GoPro"),
-                    tr("Hero 4"),
-                    6.17,               // sensorWidth
-                    4.55,               // sendsorHeight
-                    4000,               // imageWidth
-                    3000,               // imageHeight
-                    2.98,               // focalLength
-                    true,               // landscape
-                    false,              // fixedOrientation
-                    0,                  // minTriggerInterval
-                    tr("GoPro Hero 4"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Parrot Sequioa RGB",
-                    tr("Parrot"),
-                    tr("Sequioa RGB"),
-                    6.17,                       // sensorWidth
-                    4.63,                       // sendsorHeight
-                    4608,                       // imageWidth
-                    3456,                       // imageHeight
-                    4.9,                        // focalLength
-                    true,                       // landscape
-                    false,                      // fixedOrientation
-                    1,                          // minTriggerInterval
-                    tr("Parrot Sequioa RGB"),   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Parrot Sequioa Monochrome",
-                    tr("Parrot"),
-                    tr("Sequioa Monochrome"),
-                    4.8,                                // sensorWidth
-                    3.6,                                // sendsorHeight
-                    1280,                               // imageWidth
-                    960,                                // imageHeight
-                    4.0,                                // focalLength
-                    true,                               // landscape
-                    false,                              // fixedOrientation
-                    0.8,                                // minTriggerInterval
-                    tr("Parrot Sequioa Monochrome"),    // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "RedEdge",
-                    tr("RedEdge"),
-                    tr("RedEdge"),
-                    4.8,            // sensorWidth
-                    3.6,            // sendsorHeight
-                    1280,           // imageWidth
-                    960,            // imageHeight
-                    5.5,            // focalLength
-                    true,           // landscape
-                    false,          // fixedOrientation
-                    0,              // minTriggerInterval
-                    tr("RedEdge"),  // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    // Ricoh GR II 18.3mm f/2.8
-                    "Ricoh GR II",
-                    tr("Ricoh"),
-                    tr("GR II"),
-                    23.7,               // sensorWidth
-                    15.7,               // sendsorHeight
-                    4928,               // imageWidth
-                    3264,               // imageHeight
-                    18.3,               // focalLength
-                    true,               // landscape
-                    false,              // fixedOrientation
-                    0,                  // minTriggerInterval
-                    tr("Ricoh GR II"),  // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sentera Double 4K Sensor",
-                    tr("Sentera"),
-                    tr("Double 4K Sensor"),
-                    6.2,                // sensorWidth
-                    4.65,               // sendsorHeight
-                    4000,               // imageWidth
-                    3000,               // imageHeight
-                    5.4,                // focalLength
-                    true,               // landscape
-                    false,              // fixedOrientation
-                    0.8,                // minTriggerInterval
-                    tr("Sentera Double 4K Sensor"),// SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sentera NDVI Single Sensor",
-                    tr("Sentera"),
-                    tr("NDVI Single Sensor"),
-                    4.68,               // sensorWidth
-                    3.56,               // sendsorHeight
-                    1248,               // imageWidth
-                    952,                // imageHeight
-                    4.14,               // focalLength
-                    true,               // landscape
-                    false,              // fixedOrientation
-                    0.5,                // minTriggerInterval
-                    tr("Sentera NDVI Single Sensor"),// SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sentera 6X Sensor",
-                    tr("Sentera"),
-                    tr("6X Sensor"),
-                    6.57,               // sensorWidth
-                    4.93,               // sendsorHeight
-                    1904,               // imageWidth
-                    1428,               // imageHeight
-                    8.0,                // focalLength
-                    true,               // true: landscape orientation
-                    false,              // true: camera is fixed orientation
-                    0.2,                // minimum trigger interval
-                    tr(""),             // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sentera 65R Sensor",
-                    tr("Sentera"),
-                    tr("65R Sensor"),
-                    29.9,                // sensorWidth
-                    22.4,                // sendsorHeight
-                    9344,                // imageWidth
-                    7000,                // imageHeight
-                    27.4,                // focalLength
-                    true,                // landscape
-                    false,               // fixedOrientation
-                    0.3,                 // minTriggerInterval
-                    tr(""),              // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);               // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    //-- http://www.sony.co.uk/electronics/interchangeable-lens-cameras/ilce-6000-body-kit#product_details_default
-                    // Sony a6000 Sony 16mm f/2.8"
-                    "Sony a6000 16mm",
-                    tr("Sony"),
-                    tr("a6000 16mm"),
-                    23.5,                   // sensorWidth
-                    15.6,                   // sensorHeight
-                    6000,                   // imageWidth
-                    4000,                   // imageHeight
-                    16,                     // focalLength
-                    true,                   // true: landscape orientation
-                    false,                  // true: camera is fixed orientation
-                    1.0,                    // minimum trigger interval
-                    tr("Sony a6000 16mm"),  // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);                  // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sony a6000 35mm",
-                    tr("Sony"),
-                    tr("a6000 35mm"),
-                    23.5,               // sensorWidth
-                    15.6,               // sensorHeight
-                    6000,               // imageWidth
-                    4000,               // imageHeight
-                    35,                 // focalLength
-                    true,               // true: landscape orientation
-                    false,              // true: camera is fixed orientation
-                    1.0,                // minimum trigger interval
-                    "",
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sony a6300 Zeiss 21mm f/2.8",
-                    tr("Sony"),
-                    tr("a6300 Zeiss 21mm f/2.8"),
-                    23.5,               // sensorWidth
-                    15.6,               // sensorHeight
-                    6000,               // imageWidth
-                    4000,               // imageHeight
-                    21,                 // focalLength
-                    true,               // true: landscape orientation
-                    false,              // true: camera is fixed orientation
-                    1.0,                // minimum trigger interval
-                    tr("Sony a6300 Zeiss 21mm f/2.8"),// SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sony a6300 Sony 28mm f/2.0",
-                    tr("Sony"),
-                    tr("a6300 Sony 28mm f/2.0"),
-                    23.5,                               // sensorWidth
-                    15.6,                               // sensorHeight
-                    6000,                               // imageWidth
-                    4000,                               // imageHeight
-                    28,                                 // focalLength
-                    true,                               // true: landscape orientation
-                    false,              // true: camera is fixed orientation
-                    1.0,                                // minimum trigger interval
-                    tr("Sony a6300 Sony 28mm f/2.0"),   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);                              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sony a7R II Zeiss 21mm f/2.8",
-                    tr("Sony"),
-                    tr("a7R II Zeiss 21mm f/2.8"),
-                    35.814,                             // sensorWidth
-                    23.876,                             // sensorHeight
-                    7952,                               // imageWidth
-                    5304,                               // imageHeight
-                    21,                                 // focalLength
-                    true,                               // true: landscape orientation
-                    true,                               // true: camera is fixed orientation
-                    1.0,                                // minimum trigger interval
-                    tr("Sony a7R II Zeiss 21mm f/2.8"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);                              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sony a7R II Sony 28mm f/2.0",
-                    tr("Sony"),
-                    tr("a7R II Sony 28mm f/2.0"),
-                    35.814,             // sensorWidth
-                    23.876,             // sensorHeight
-                    7952,               // imageWidth
-                    5304,               // imageHeight
-                    28,                 // focalLength
-                    true,               // true: landscape orientation
-                    true,               // true: camera is fixed orientation
-                    1.0,                // minimum trigger interval
-                    tr("Sony a7R II Sony 28mm f/2.0"),// SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sony a7r III 35mm",
-                    tr("Sony"),
-                    tr("a7r III 35mm"),
-                    35.9,               // sensorWidth
-                    24.0,               // sensorHeight
-                    7952,               // imageWidth
-                    5304,               // imageHeight
-                    35,                 // focalLength
-                    true,               // true: landscape orientation
-                    false,              // true: camera is fixed orientation
-                    1.0,                // minimum trigger interval
-                    "",
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sony a7r IV 35mm",
-                    tr("Sony"),
-                    tr("a7r IV 35mm"),
-                    35.7,               // sensorWidth
-                    23.8,               // sensorHeight
-                    9504,               // imageWidth
-                    6336,               // imageHeight
-                    35,                 // focalLength
-                    true,               // true: landscape orientation
-                    false,               // true: camera is fixed orientation
-                    1.0,                // minimum trigger interval
-                    "",
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sony DSC-QX30U @ 4.3mm f/3.5",
-                    tr("Sony"),
-                    tr("DSC-QX30U @ 4.3mm f/3.5"),
-                    7.82,                               // sensorWidth
-                    5.865,                              // sensorHeight
-                    5184,                               // imageWidth
-                    3888,                               // imageHeight
-                    4.3,                                // focalLength
-                    true,                               // true: landscape orientation
-                    false,                              // true: camera is fixed orientation
-                    2.0,                                // minimum trigger interval
-                    tr("Sony DSC-QX30U @ 4.3mm f/3.5"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);                              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sony DSC-RX0",
-                    tr("Sony"),
-                    tr("DSC-RX0"),
-                    13.2,               // sensorWidth
-                    8.8,                // sensorHeight
-                    4800,               // imageWidth
-                    3200,               // imageHeight
-                    7.7,                // focalLength
-                    true,               // true: landscape orientation
-                    false,              // true: camera is fixed orientation
-                    0,                  // minimum trigger interval
-                    tr("Sony DSC-RX0"),// SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Sony DSC-RX1R II 35mm",
-                    tr("Sony"),
-                    tr("DSC-RX1R II 35mm"),
-                    35.9,             // sensorWidth
-                    24.0,             // sensorHeight
-                    7952,               // imageWidth
-                    5304,               // imageHeight
-                    35,                 // focalLength
-                    true,               // true: landscape orientation
-                    false,              // true: camera is fixed orientation
-                    1.0,                // minimum trigger interval
-                    "",
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    //-- http://www.sony.co.uk/electronics/interchangeable-lens-cameras/ilce-qx1-body-kit/specifications
-                    //-- http://www.sony.com/electronics/camera-lenses/sel16f28/specifications
-                    //tr("Sony ILCE-QX1 Sony 16mm f/2.8"),
-                    "Sony ILCE-QX1",
-                    tr("Sony"),
-                    tr("ILCE-QX1"),
-                    23.2,                   // sensorWidth
-                    15.4,                   // sensorHeight
-                    5456,                   // imageWidth
-                    3632,                   // imageHeight
-                    16,                     // focalLength
-                    true,                   // true: landscape orientation
-                    false,                  // true: camera is fixed orientation
-                    0,                      // minimum trigger interval
-                    tr("Sony ILCE-QX1"),    // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);                  // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    //-- http://www.sony.co.uk/electronics/interchangeable-lens-cameras/ilce-qx1-body-kit/specifications
-                    // Sony NEX-5R Sony 20mm f/2.8"
-                    "Sony NEX-5R 20mm",
-                    tr("Sony"),
-                    tr("NEX-5R 20mm"),
-                    23.2,                   // sensorWidth
-                    15.4,                   // sensorHeight
-                    4912,                   // imageWidth
-                    3264,                   // imageHeight
-                    20,                     // focalLength
-                    true,                   // true: landscape orientation
-                    false,                  // true: camera is fixed orientation
-                    1,                      // minimum trigger interval
-                    tr("Sony NEX-5R 20mm"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);                  // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    // Sony RX100 II @ 10.4mm f/1.8
-                    "Sony RX100 II 28mm",
-                    tr("Sony"),
-                    tr("RX100 II 28mm"),
-                    13.2,                // sensorWidth
-                    8.8,                 // sensorHeight
-                    5472,                // imageWidth
-                    3648,                // imageHeight
-                    10.4,                // focalLength
-                    true,                // true: landscape orientation
-                    false,               // true: camera is fixed orientation
-                    0,                   // minimum trigger interval
-                    tr("Sony RX100 II 28mm"),// SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);               // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Yuneec CGOET",
-                    tr("Yuneec"),
-                    tr("CGOET"),
-                    5.6405,             // sensorWidth
-                    3.1813,             // sensorHeight
-                    1920,               // imageWidth
-                    1080,               // imageHeight
-                    3.5,                // focalLength
-                    true,               // true: landscape orientation
-                    true,               // true: camera is fixed orientation
-                    1.3,                // minimum trigger interval
-                    tr("Yuneec CGOET"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Yuneec E10T",
-                    tr("Yuneec"),
-                    tr("E10T"),
-                    5.6405,             // sensorWidth
-                    3.1813,             // sensorHeight
-                    1920,               // imageWidth
-                    1080,               // imageHeight
-                    23,                 // focalLength
-                    true,               // true: landscape orientation
-                    true,               // true: camera is fixed orientation
-                    1.3,                // minimum trigger interval
-                    tr("Yuneec E10T"),  // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Yuneec E50",
-                    tr("Yuneec"),
-                    tr("E50"),
-                    6.2372,             // sensorWidth
-                    4.7058,             // sensorHeight
-                    4000,               // imageWidth
-                    3000,               // imageHeight
-                    7.2,                // focalLength
-                    true,               // true: landscape orientation
-                    true,               // true: camera is fixed orientation
-                    1.3,                // minimum trigger interval
-                    tr("Yuneec E50"),   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Yuneec E90",
-                    tr("Yuneec"),
-                    tr("E90"),
-                    13.3056,            // sensorWidth
-                    8.656,              // sensorHeight
-                    5472,               // imageWidth
-                    3648,               // imageHeight
-                    8.29,               // focalLength
-                    true,               // true: landscape orientation
-                    true,               // true: camera is fixed orientation
-                    1.3,                // minimum trigger interval
-                    tr("Yuneec E90"),   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Flir Duo R",
-                    tr("Flir"),
-                    tr("Duo R"),
-                    160,                // sensorWidth
-                    120,                // sensorHeight
-                    1920,               // imageWidth
-                    1080,               // imageHeight
-                    1.9,                // focalLength
-                    true,               // true: landscape orientation
-                    false,              // true: camera is fixed orientation
-                    0,                  // minimum trigger interval
-                    tr("Flir Duo R"),   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Flir Duo Pro R",
-                    tr("Flir"),
-                    tr("Duo Pro R"),
-                    10.88,                // sensorWidth
-                    8.704,                // sensorHeight
-                    640,               // imageWidth
-                    512,               // imageHeight
-                    19,                // focalLength
-                    true,               // true: landscape orientation
-                    false,              // true: camera is fixed orientation
-                    1.0,                  // minimum trigger interval
-                    "",   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Workswell Wiris Security Thermal Camera",
-                    tr("Workswell"),
-                    tr("Wiris Security"),
-                    13.6,                // sensorWidth
-                    10.2,                // sensorHeight
-                    800,               // imageWidth
-                    600,               // imageHeight
-                    35,                // focalLength
-                    true,               // true: landscape orientation
-                    false,              // true: camera is fixed orientation
-                    1.8,                  // minimum trigger interval
-                    "",   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
-
-        metaData = new CameraMetaData(
-                    "Workswell Wiris Security Visual Camera",
-                    tr("Workswell"),
-                    tr("Wiris Security"),
-                    4.826,                // sensorWidth
-                    3.556,                // sensorHeight
-                    1920,               // imageWidth
-                    1080,               // imageHeight
-                    4.3,                // focalLength
-                    true,               // true: landscape orientation
-                    false,              // true: camera is fixed orientation
-                    1.8,                  // minimum trigger interval
-                    "",   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
-                    this);              // parent
-        _cameraList.append(QVariant::fromValue(metaData));
+//        metaData = new CameraMetaData(
+//                    // Canon S100 @ 5.2mm f/2
+//                    "Canon S100 PowerShot",     // canonical name saved in plan file
+//                    tr("Canon"),                // brand
+//                    tr("S100 PowerShot"),       // model
+//                    7.6,                        // sensorWidth
+//                    5.7,                        // sensorHeight
+//                    4000,                       // imageWidth
+//                    3000,                       // imageHeight
+//                    5.2,                        // focalLength
+//                    true,                       // true: landscape orientation
+//                    false,                      // true: camera is fixed orientation
+//                    0,                          // minimum trigger interval
+//                    tr("Canon S100 PowerShot"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);                      // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    //tr("Canon EOS-M 22mm f/2"),
+//                    "Canon EOS-M 22mm",
+//                    tr("Canon"),
+//                    tr("EOS-M 22mm"),
+//                    22.3,                   // sensorWidth
+//                    14.9,                   // sensorHeight
+//                    5184,                   // imageWidth
+//                    3456,                   // imageHeight
+//                    22,                     // focalLength
+//                    true,                   // true: landscape orientation
+//                    false,                  // true: camera is fixed orientation
+//                    0,                      // minimum trigger interval
+//                    tr("Canon EOS-M 22mm"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);                  // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    // Canon G9X @ 10.2mm f/2
+//                    "Canon G9 X PowerShot",
+//                    tr("Canon"),
+//                    tr("G9 X PowerShot"),
+//                    13.2,                       // sensorWidth
+//                    8.8,                        // sensorHeight
+//                    5488,                       // imageWidth
+//                    3680,                       // imageHeight
+//                    10.2,                       // focalLength
+//                    true,                       // true: landscape orientation
+//                    false,                      // true: camera is fixed orientation
+//                    0,                          // minimum trigger interval
+//                    tr("Canon G9 X PowerShot"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);                      // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    // Canon SX260 HS @ 4.5mm f/3.5
+//                    "Canon SX260 HS PowerShot",
+//                    tr("Canon"),
+//                    tr("SX260 HS PowerShot"),
+//                    6.17,                           // sensorWidth
+//                    4.55,                           // sensorHeight
+//                    4000,                           // imageWidth
+//                    3000,                           // imageHeight
+//                    4.5,                            // focalLength
+//                    true,                           // true: landscape orientation
+//                    false,                          // true: camera is fixed orientation
+//                    0,                              // minimum trigger interval
+//                    tr("Canon SX260 HS PowerShot"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);                          // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "GoPro Hero 4",
+//                    tr("GoPro"),
+//                    tr("Hero 4"),
+//                    6.17,               // sensorWidth
+//                    4.55,               // sendsorHeight
+//                    4000,               // imageWidth
+//                    3000,               // imageHeight
+//                    2.98,               // focalLength
+//                    true,               // landscape
+//                    false,              // fixedOrientation
+//                    0,                  // minTriggerInterval
+//                    tr("GoPro Hero 4"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Parrot Sequioa RGB",
+//                    tr("Parrot"),
+//                    tr("Sequioa RGB"),
+//                    6.17,                       // sensorWidth
+//                    4.63,                       // sendsorHeight
+//                    4608,                       // imageWidth
+//                    3456,                       // imageHeight
+//                    4.9,                        // focalLength
+//                    true,                       // landscape
+//                    false,                      // fixedOrientation
+//                    1,                          // minTriggerInterval
+//                    tr("Parrot Sequioa RGB"),   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Parrot Sequioa Monochrome",
+//                    tr("Parrot"),
+//                    tr("Sequioa Monochrome"),
+//                    4.8,                                // sensorWidth
+//                    3.6,                                // sendsorHeight
+//                    1280,                               // imageWidth
+//                    960,                                // imageHeight
+//                    4.0,                                // focalLength
+//                    true,                               // landscape
+//                    false,                              // fixedOrientation
+//                    0.8,                                // minTriggerInterval
+//                    tr("Parrot Sequioa Monochrome"),    // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "RedEdge",
+//                    tr("RedEdge"),
+//                    tr("RedEdge"),
+//                    4.8,            // sensorWidth
+//                    3.6,            // sendsorHeight
+//                    1280,           // imageWidth
+//                    960,            // imageHeight
+//                    5.5,            // focalLength
+//                    true,           // landscape
+//                    false,          // fixedOrientation
+//                    0,              // minTriggerInterval
+//                    tr("RedEdge"),  // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    // Ricoh GR II 18.3mm f/2.8
+//                    "Ricoh GR II",
+//                    tr("Ricoh"),
+//                    tr("GR II"),
+//                    23.7,               // sensorWidth
+//                    15.7,               // sendsorHeight
+//                    4928,               // imageWidth
+//                    3264,               // imageHeight
+//                    18.3,               // focalLength
+//                    true,               // landscape
+//                    false,              // fixedOrientation
+//                    0,                  // minTriggerInterval
+//                    tr("Ricoh GR II"),  // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sentera Double 4K Sensor",
+//                    tr("Sentera"),
+//                    tr("Double 4K Sensor"),
+//                    6.2,                // sensorWidth
+//                    4.65,               // sendsorHeight
+//                    4000,               // imageWidth
+//                    3000,               // imageHeight
+//                    5.4,                // focalLength
+//                    true,               // landscape
+//                    false,              // fixedOrientation
+//                    0.8,                // minTriggerInterval
+//                    tr("Sentera Double 4K Sensor"),// SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sentera NDVI Single Sensor",
+//                    tr("Sentera"),
+//                    tr("NDVI Single Sensor"),
+//                    4.68,               // sensorWidth
+//                    3.56,               // sendsorHeight
+//                    1248,               // imageWidth
+//                    952,                // imageHeight
+//                    4.14,               // focalLength
+//                    true,               // landscape
+//                    false,              // fixedOrientation
+//                    0.5,                // minTriggerInterval
+//                    tr("Sentera NDVI Single Sensor"),// SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sentera 6X Sensor",
+//                    tr("Sentera"),
+//                    tr("6X Sensor"),
+//                    6.57,               // sensorWidth
+//                    4.93,               // sendsorHeight
+//                    1904,               // imageWidth
+//                    1428,               // imageHeight
+//                    8.0,                // focalLength
+//                    true,               // true: landscape orientation
+//                    false,              // true: camera is fixed orientation
+//                    0.2,                // minimum trigger interval
+//                    tr(""),             // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sentera 65R Sensor",
+//                    tr("Sentera"),
+//                    tr("65R Sensor"),
+//                    29.9,                // sensorWidth
+//                    22.4,                // sendsorHeight
+//                    9344,                // imageWidth
+//                    7000,                // imageHeight
+//                    27.4,                // focalLength
+//                    true,                // landscape
+//                    false,               // fixedOrientation
+//                    0.3,                 // minTriggerInterval
+//                    tr(""),              // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);               // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    //-- http://www.sony.co.uk/electronics/interchangeable-lens-cameras/ilce-6000-body-kit#product_details_default
+//                    // Sony a6000 Sony 16mm f/2.8"
+//                    "Sony a6000 16mm",
+//                    tr("Sony"),
+//                    tr("a6000 16mm"),
+//                    23.5,                   // sensorWidth
+//                    15.6,                   // sensorHeight
+//                    6000,                   // imageWidth
+//                    4000,                   // imageHeight
+//                    16,                     // focalLength
+//                    true,                   // true: landscape orientation
+//                    false,                  // true: camera is fixed orientation
+//                    1.0,                    // minimum trigger interval
+//                    tr("Sony a6000 16mm"),  // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);                  // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sony a6000 35mm",
+//                    tr("Sony"),
+//                    tr("a6000 35mm"),
+//                    23.5,               // sensorWidth
+//                    15.6,               // sensorHeight
+//                    6000,               // imageWidth
+//                    4000,               // imageHeight
+//                    35,                 // focalLength
+//                    true,               // true: landscape orientation
+//                    false,              // true: camera is fixed orientation
+//                    1.0,                // minimum trigger interval
+//                    "",
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sony a6300 Zeiss 21mm f/2.8",
+//                    tr("Sony"),
+//                    tr("a6300 Zeiss 21mm f/2.8"),
+//                    23.5,               // sensorWidth
+//                    15.6,               // sensorHeight
+//                    6000,               // imageWidth
+//                    4000,               // imageHeight
+//                    21,                 // focalLength
+//                    true,               // true: landscape orientation
+//                    false,              // true: camera is fixed orientation
+//                    1.0,                // minimum trigger interval
+//                    tr("Sony a6300 Zeiss 21mm f/2.8"),// SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sony a6300 Sony 28mm f/2.0",
+//                    tr("Sony"),
+//                    tr("a6300 Sony 28mm f/2.0"),
+//                    23.5,                               // sensorWidth
+//                    15.6,                               // sensorHeight
+//                    6000,                               // imageWidth
+//                    4000,                               // imageHeight
+//                    28,                                 // focalLength
+//                    true,                               // true: landscape orientation
+//                    false,              // true: camera is fixed orientation
+//                    1.0,                                // minimum trigger interval
+//                    tr("Sony a6300 Sony 28mm f/2.0"),   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);                              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sony a7R II Zeiss 21mm f/2.8",
+//                    tr("Sony"),
+//                    tr("a7R II Zeiss 21mm f/2.8"),
+//                    35.814,                             // sensorWidth
+//                    23.876,                             // sensorHeight
+//                    7952,                               // imageWidth
+//                    5304,                               // imageHeight
+//                    21,                                 // focalLength
+//                    true,                               // true: landscape orientation
+//                    true,                               // true: camera is fixed orientation
+//                    1.0,                                // minimum trigger interval
+//                    tr("Sony a7R II Zeiss 21mm f/2.8"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);                              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sony a7R II Sony 28mm f/2.0",
+//                    tr("Sony"),
+//                    tr("a7R II Sony 28mm f/2.0"),
+//                    35.814,             // sensorWidth
+//                    23.876,             // sensorHeight
+//                    7952,               // imageWidth
+//                    5304,               // imageHeight
+//                    28,                 // focalLength
+//                    true,               // true: landscape orientation
+//                    true,               // true: camera is fixed orientation
+//                    1.0,                // minimum trigger interval
+//                    tr("Sony a7R II Sony 28mm f/2.0"),// SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sony a7r III 35mm",
+//                    tr("Sony"),
+//                    tr("a7r III 35mm"),
+//                    35.9,               // sensorWidth
+//                    24.0,               // sensorHeight
+//                    7952,               // imageWidth
+//                    5304,               // imageHeight
+//                    35,                 // focalLength
+//                    true,               // true: landscape orientation
+//                    false,              // true: camera is fixed orientation
+//                    1.0,                // minimum trigger interval
+//                    "",
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sony a7r IV 35mm",
+//                    tr("Sony"),
+//                    tr("a7r IV 35mm"),
+//                    35.7,               // sensorWidth
+//                    23.8,               // sensorHeight
+//                    9504,               // imageWidth
+//                    6336,               // imageHeight
+//                    35,                 // focalLength
+//                    true,               // true: landscape orientation
+//                    false,               // true: camera is fixed orientation
+//                    1.0,                // minimum trigger interval
+//                    "",
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sony DSC-QX30U @ 4.3mm f/3.5",
+//                    tr("Sony"),
+//                    tr("DSC-QX30U @ 4.3mm f/3.5"),
+//                    7.82,                               // sensorWidth
+//                    5.865,                              // sensorHeight
+//                    5184,                               // imageWidth
+//                    3888,                               // imageHeight
+//                    4.3,                                // focalLength
+//                    true,                               // true: landscape orientation
+//                    false,                              // true: camera is fixed orientation
+//                    2.0,                                // minimum trigger interval
+//                    tr("Sony DSC-QX30U @ 4.3mm f/3.5"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);                              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sony DSC-RX0",
+//                    tr("Sony"),
+//                    tr("DSC-RX0"),
+//                    13.2,               // sensorWidth
+//                    8.8,                // sensorHeight
+//                    4800,               // imageWidth
+//                    3200,               // imageHeight
+//                    7.7,                // focalLength
+//                    true,               // true: landscape orientation
+//                    false,              // true: camera is fixed orientation
+//                    0,                  // minimum trigger interval
+//                    tr("Sony DSC-RX0"),// SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Sony DSC-RX1R II 35mm",
+//                    tr("Sony"),
+//                    tr("DSC-RX1R II 35mm"),
+//                    35.9,             // sensorWidth
+//                    24.0,             // sensorHeight
+//                    7952,               // imageWidth
+//                    5304,               // imageHeight
+//                    35,                 // focalLength
+//                    true,               // true: landscape orientation
+//                    false,              // true: camera is fixed orientation
+//                    1.0,                // minimum trigger interval
+//                    "",
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    //-- http://www.sony.co.uk/electronics/interchangeable-lens-cameras/ilce-qx1-body-kit/specifications
+//                    //-- http://www.sony.com/electronics/camera-lenses/sel16f28/specifications
+//                    //tr("Sony ILCE-QX1 Sony 16mm f/2.8"),
+//                    "Sony ILCE-QX1",
+//                    tr("Sony"),
+//                    tr("ILCE-QX1"),
+//                    23.2,                   // sensorWidth
+//                    15.4,                   // sensorHeight
+//                    5456,                   // imageWidth
+//                    3632,                   // imageHeight
+//                    16,                     // focalLength
+//                    true,                   // true: landscape orientation
+//                    false,                  // true: camera is fixed orientation
+//                    0,                      // minimum trigger interval
+//                    tr("Sony ILCE-QX1"),    // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);                  // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    //-- http://www.sony.co.uk/electronics/interchangeable-lens-cameras/ilce-qx1-body-kit/specifications
+//                    // Sony NEX-5R Sony 20mm f/2.8"
+//                    "Sony NEX-5R 20mm",
+//                    tr("Sony"),
+//                    tr("NEX-5R 20mm"),
+//                    23.2,                   // sensorWidth
+//                    15.4,                   // sensorHeight
+//                    4912,                   // imageWidth
+//                    3264,                   // imageHeight
+//                    20,                     // focalLength
+//                    true,                   // true: landscape orientation
+//                    false,                  // true: camera is fixed orientation
+//                    1,                      // minimum trigger interval
+//                    tr("Sony NEX-5R 20mm"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);                  // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    // Sony RX100 II @ 10.4mm f/1.8
+//                    "Sony RX100 II 28mm",
+//                    tr("Sony"),
+//                    tr("RX100 II 28mm"),
+//                    13.2,                // sensorWidth
+//                    8.8,                 // sensorHeight
+//                    5472,                // imageWidth
+//                    3648,                // imageHeight
+//                    10.4,                // focalLength
+//                    true,                // true: landscape orientation
+//                    false,               // true: camera is fixed orientation
+//                    0,                   // minimum trigger interval
+//                    tr("Sony RX100 II 28mm"),// SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);               // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Yuneec CGOET",
+//                    tr("Yuneec"),
+//                    tr("CGOET"),
+//                    5.6405,             // sensorWidth
+//                    3.1813,             // sensorHeight
+//                    1920,               // imageWidth
+//                    1080,               // imageHeight
+//                    3.5,                // focalLength
+//                    true,               // true: landscape orientation
+//                    true,               // true: camera is fixed orientation
+//                    1.3,                // minimum trigger interval
+//                    tr("Yuneec CGOET"), // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Yuneec E10T",
+//                    tr("Yuneec"),
+//                    tr("E10T"),
+//                    5.6405,             // sensorWidth
+//                    3.1813,             // sensorHeight
+//                    1920,               // imageWidth
+//                    1080,               // imageHeight
+//                    23,                 // focalLength
+//                    true,               // true: landscape orientation
+//                    true,               // true: camera is fixed orientation
+//                    1.3,                // minimum trigger interval
+//                    tr("Yuneec E10T"),  // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Yuneec E50",
+//                    tr("Yuneec"),
+//                    tr("E50"),
+//                    6.2372,             // sensorWidth
+//                    4.7058,             // sensorHeight
+//                    4000,               // imageWidth
+//                    3000,               // imageHeight
+//                    7.2,                // focalLength
+//                    true,               // true: landscape orientation
+//                    true,               // true: camera is fixed orientation
+//                    1.3,                // minimum trigger interval
+//                    tr("Yuneec E50"),   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Yuneec E90",
+//                    tr("Yuneec"),
+//                    tr("E90"),
+//                    13.3056,            // sensorWidth
+//                    8.656,              // sensorHeight
+//                    5472,               // imageWidth
+//                    3648,               // imageHeight
+//                    8.29,               // focalLength
+//                    true,               // true: landscape orientation
+//                    true,               // true: camera is fixed orientation
+//                    1.3,                // minimum trigger interval
+//                    tr("Yuneec E90"),   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Flir Duo R",
+//                    tr("Flir"),
+//                    tr("Duo R"),
+//                    160,                // sensorWidth
+//                    120,                // sensorHeight
+//                    1920,               // imageWidth
+//                    1080,               // imageHeight
+//                    1.9,                // focalLength
+//                    true,               // true: landscape orientation
+//                    false,              // true: camera is fixed orientation
+//                    0,                  // minimum trigger interval
+//                    tr("Flir Duo R"),   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Flir Duo Pro R",
+//                    tr("Flir"),
+//                    tr("Duo Pro R"),
+//                    10.88,                // sensorWidth
+//                    8.704,                // sensorHeight
+//                    640,               // imageWidth
+//                    512,               // imageHeight
+//                    19,                // focalLength
+//                    true,               // true: landscape orientation
+//                    false,              // true: camera is fixed orientation
+//                    1.0,                  // minimum trigger interval
+//                    "",   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Workswell Wiris Security Thermal Camera",
+//                    tr("Workswell"),
+//                    tr("Wiris Security"),
+//                    13.6,                // sensorWidth
+//                    10.2,                // sensorHeight
+//                    800,               // imageWidth
+//                    600,               // imageHeight
+//                    35,                // focalLength
+//                    true,               // true: landscape orientation
+//                    false,              // true: camera is fixed orientation
+//                    1.8,                  // minimum trigger interval
+//                    "",   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
+
+//        metaData = new CameraMetaData(
+//                    "Workswell Wiris Security Visual Camera",
+//                    tr("Workswell"),
+//                    tr("Wiris Security"),
+//                    4.826,                // sensorWidth
+//                    3.556,                // sensorHeight
+//                    1920,               // imageWidth
+//                    1080,               // imageHeight
+//                    4.3,                // focalLength
+//                    true,               // true: landscape orientation
+//                    false,              // true: camera is fixed orientation
+//                    1.8,                  // minimum trigger interval
+//                    "",   // SHOULD BE BLANK FOR NEWLY ADDED CAMERAS. Deprecated translation from older builds.
+//                    this);              // parent
+//        _cameraList.append(QVariant::fromValue(metaData));
     }
 
     return _cameraList;
diff --git a/src/FlightDisplay/FlyViewWidgetLayer.qml b/src/FlightDisplay/FlyViewWidgetLayer.qml
index 509d60e4d..6391e49aa 100644
--- a/src/FlightDisplay/FlyViewWidgetLayer.qml
+++ b/src/FlightDisplay/FlyViewWidgetLayer.qml
@@ -256,7 +256,7 @@ Item {
         anchors.top:            parent.top
         z:                      QGroundControl.zOrderWidgets
         maxHeight:              parent.height - y - parentToolInsets.bottomEdgeLeftInset - _toolsMargin
-        visible:                !QGroundControl.videoManager.fullScreen
+        visible:                false // !QGroundControl.videoManager.fullScreen
 
         onDisplayPreFlightChecklist: preFlightChecklistPopup.createObject(mainWindow).open()
 
diff --git a/src/FlightDisplay/TelemetryValuesBar.qml b/src/FlightDisplay/TelemetryValuesBar.qml
index 136cfe175..15d31e4a3 100644
--- a/src/FlightDisplay/TelemetryValuesBar.qml
+++ b/src/FlightDisplay/TelemetryValuesBar.qml
@@ -60,7 +60,7 @@ Rectangle {
                 sourceSize.width:   width
                 color:              qgcPal.text
                 fillMode:           Image.PreserveAspectFit
-                visible:            bottomMode
+                visible:            false //bottomMode
 
                 QGCMouseArea {
                     fillItem:   parent
diff --git a/src/QGCPalette.cc b/src/QGCPalette.cc
index ddf26fd54..5a728be46 100644
--- a/src/QGCPalette.cc
+++ b/src/QGCPalette.cc
@@ -85,7 +85,7 @@ void QGCPalette::_buildMap()
 
     // Colors not affecting by theming
     //                                              Disabled    Enabled
-    DECLARE_QGC_NONTHEMED_COLOR(brandingPurple,     "#4A2C6D", "#4A2C6D")
+    DECLARE_QGC_NONTHEMED_COLOR(brandingPurple,     "#DE881E", "#DE881E")//"#4A2C6D", "#4A2C6D")
     DECLARE_QGC_NONTHEMED_COLOR(brandingBlue,       "#48D6FF", "#6045c5")
     DECLARE_QGC_NONTHEMED_COLOR(toolStripFGColor,   "#707070", "#ffffff")
 
diff --git a/src/Vehicle/Vehicle.cc b/src/Vehicle/Vehicle.cc
index 324642ec4..733e921c4 100644
--- a/src/Vehicle/Vehicle.cc
+++ b/src/Vehicle/Vehicle.cc
@@ -694,6 +694,22 @@ void Vehicle::_mavlinkMessageReceived(LinkInterface* link, mavlink_message_t mes
         factGroup->handleMessage(this, message);
     }
 
+//    // check to see if we have timed out on the generator status message
+//    if (Vehicle::_generatorFactGroup._msgReceived> 0)
+//    {
+//        // start timer
+//        _genStatusTimer.setInterval(10000);
+//        Vehicle::_generatorFactGroup._msgReceived = 0;
+//        Vehicle::_generatorFactGroup._timeoutCntStarted = 1;
+//    }
+
+//    if ((Vehicle::_generatorFactGroup._timeoutCntStarted > 0) && (!_genStatusTimer.isActive()))
+//    {
+//        // set timeout flag
+//        Vehicle::_generatorFactGroup._timeout = 1;
+//        Vehicle::_generatorFactGroup._timeoutCntStarted = 0;
+//    }
+
     switch (message.msgid) {
     case MAVLINK_MSG_ID_HOME_POSITION:
         _handleHomePosition(message);
diff --git a/src/Vehicle/Vehicle.h b/src/Vehicle/Vehicle.h
index a8d12f974..7d9d909a8 100644
--- a/src/Vehicle/Vehicle.h
+++ b/src/Vehicle/Vehicle.h
@@ -1509,6 +1509,8 @@ private:
     // We use this to limit above terrain altitude queries based on distance and altitude change
     QGeoCoordinate              _altitudeAboveTerrLastCoord;
     float                       _altitudeAboveTerrLastRelAlt = qQNaN();
+
+    QTimer                      _genStatusTimer;
 };
 
 Q_DECLARE_METATYPE(Vehicle::MavCmdResultFailureCode_t)
diff --git a/src/Vehicle/VehicleGeneratorFactGroup.cc b/src/Vehicle/VehicleGeneratorFactGroup.cc
index 9cfbd7d93..c28a8830c 100644
--- a/src/Vehicle/VehicleGeneratorFactGroup.cc
+++ b/src/Vehicle/VehicleGeneratorFactGroup.cc
@@ -82,6 +82,10 @@ void VehicleGeneratorFactGroup::_handleGeneratorStatus(mavlink_message_t& messag
     genTemp()->setRawValue              (generator.generator_temperature == INT16_MAX ? qQNaN() : generator.generator_temperature);
     runtime()->setRawValue              (generator.runtime == UINT32_MAX ? qQNaN() : generator.runtime);
     timeMaintenance()->setRawValue      (generator.time_until_maintenance == INT32_MAX ? qQNaN() : generator.time_until_maintenance);
+
+    _msgReceived = 1;
+    //VehicleGeneratorFactGroup::_msgReceived = 1;
+    //VehicleGeneratorFactGroup::_timeout = 0;
 }
 
 void VehicleGeneratorFactGroup::_updateGeneratorFlags() {
@@ -107,4 +111,4 @@ void VehicleGeneratorFactGroup::_updateGeneratorFlags() {
         }
     }
     emit flagsListGeneratorChanged();
-}
\ No newline at end of file
+}
diff --git a/src/Vehicle/VehicleGeneratorFactGroup.h b/src/Vehicle/VehicleGeneratorFactGroup.h
index c27db7b40..79794a61b 100644
--- a/src/Vehicle/VehicleGeneratorFactGroup.h
+++ b/src/Vehicle/VehicleGeneratorFactGroup.h
@@ -51,6 +51,12 @@ public:
     static const char* _runtimeFactName;
     static const char* _timeMaintenanceFactName;
 
+//    static float _lastReadTime;
+//    static uint8_t _timeout;
+    uint8_t _msgReceived;
+    uint8_t _timeoutCntStarted;
+    uint8_t _timeout;
+
 signals:
     void flagsListGeneratorChanged();
 
diff --git a/src/VehicleSetup/SetupView.qml b/src/VehicleSetup/SetupView.qml
index cd190b39c..028153d96 100644
--- a/src/VehicleSetup/SetupView.qml
+++ b/src/VehicleSetup/SetupView.qml
@@ -262,7 +262,7 @@ Rectangle {
                 setupIndicator:     true
                 setupComplete:      _activeJoystick ? _activeJoystick.calibrated || _buttonsOnly : false
                 exclusiveGroup:     setupButtonGroup
-                visible:            _fullParameterVehicleAvailable && joystickManager.joysticks.length !== 0
+                visible:            false //_fullParameterVehicleAvailable && joystickManager.joysticks.length !== 0
                 text:               _forcedToButtonsOnly ? qsTr("Buttons") : qsTr("Joystick")
                 Layout.fillWidth:   true
                 onClicked:          showPanel(this, "JoystickConfig.qml")
@@ -282,7 +282,7 @@ Rectangle {
                     setupComplete:      modelData.setupComplete
                     exclusiveGroup:     setupButtonGroup
                     text:               modelData.name
-                    visible:            modelData.setupSource.toString() !== ""
+                    visible:            modelData.name !== "Motors" && modelData.name !== "Tuning" && modelData.name !== "Remote Support" && modelData.name !== "Frame" && modelData.name !== "Camera"
                     Layout.fillWidth:   true
                     onClicked:          showVehicleComponentPanel(modelData)
                 }
diff --git a/src/VehicleSetup/VehicleSummary.qml b/src/VehicleSetup/VehicleSummary.qml
index 9456c09cb..fa69c9021 100644
--- a/src/VehicleSetup/VehicleSummary.qml
+++ b/src/VehicleSetup/VehicleSummary.qml
@@ -103,7 +103,7 @@ Rectangle {
                         width:      _summaryBoxWidth
                         height:     ScreenTools.defaultFontPixelHeight * 13
                         color:      qgcPal.windowShade
-                        visible:    modelData.summaryQmlSource.toString() !== ""
+                        visible:    modelData.name !== "Motors" && modelData.name !== "Tuning" && modelData.name !== "Remote Support" && modelData.name !== "Frame" && modelData.name !== "Camera"
                         border.width: 1
                         border.color: qgcPal.text
                         Component.onCompleted: {
@@ -131,12 +131,12 @@ Rectangle {
                                 visible:                modelData.requiresSetup && modelData.setupSource !== ""
                             }
 
-                            onClicked : {
-                                //console.log(modelData.setupSource)
-                                if (modelData.setupSource !== "") {
-                                    setupView.showVehicleComponentPanel(modelData)
-                                }
-                            }
+//                            onClicked : {
+//                                //console.log(modelData.setupSource)
+//                                if (modelData.setupSource !== "") {
+//                                    setupView.showVehicleComponentPanel(modelData)
+//                                }
+//                            }
                         }
                         // Summary Qml
                         Rectangle {
diff --git a/src/api/QGCOptions.h b/src/api/QGCOptions.h
index 7b5926d55..b84980ca2 100644
--- a/src/api/QGCOptions.h
+++ b/src/api/QGCOptions.h
@@ -30,7 +30,7 @@ public:
     Q_PROPERTY(bool                     guidedBarShowROI                READ guidedBarShowROI               NOTIFY guidedBarShowROIChanged)
 
 protected:
-    virtual bool    showMultiVehicleList        () const { return true; }
+    virtual bool    showMultiVehicleList        () const { return false; }
     virtual bool    showMapScale                () const { return true; }
     virtual bool    showInstrumentPanel         () const { return true; }
     virtual bool    guidedBarShowEmergencyStop  () const { return true; }
@@ -109,22 +109,22 @@ public:
     virtual QColor  toolbarBackgroundDark           () const;
     /// By returning false you can hide the following sensor calibration pages
     virtual bool    showSensorCalibrationCompass    () const { return true; }
-    virtual bool    showSensorCalibrationGyro       () const { return true; }
+    virtual bool    showSensorCalibrationGyro       () const { return false; }
     virtual bool    showSensorCalibrationAccel      () const { return true; }
     virtual bool    showSensorCalibrationLevel      () const { return true; }
-    virtual bool    showSensorCalibrationAirspeed   () const { return true; }
+    virtual bool    showSensorCalibrationAirspeed   () const { return false; }
     virtual bool    wifiReliableForCalibration      () const { return false; }
     virtual bool    sensorsHaveFixedOrientation     () const { return false; }
-    virtual bool    showFirmwareUpgrade             () const { return true; }
+    virtual bool    showFirmwareUpgrade             () const { return false; }
     virtual bool    missionWaypointsOnly            () const { return false; }  ///< true: Only allow waypoints and complex items in Plan
-    virtual bool    multiVehicleEnabled             () const { return true; }   ///< false: multi vehicle support is disabled
+    virtual bool    multiVehicleEnabled             () const { return false; }   ///< false: multi vehicle support is disabled
     virtual bool    guidedActionsRequireRCRSSI      () const { return false; }  ///< true: Guided actions will be disabled is there is no RC RSSI
     virtual bool    showOfflineMapExport            () const { return true; }
     virtual bool    showOfflineMapImport            () const { return true; }
     virtual bool    showMissionAbsoluteAltitude     () const { return true; }
     virtual bool    showSimpleMissionStart          () const { return false; }
     virtual bool    disableVehicleConnection        () const { return false; }  ///< true: vehicle connection is disabled
-    virtual bool    checkFirmwareVersion            () const { return true; }
+    virtual bool    checkFirmwareVersion            () const { return false; }
     virtual bool    showMavlinkLogOptions           () const { return true; }
     virtual bool    allowJoystickSelection          () const { return true; }   ///< false: custom build has automatically enabled a specific joystick
     /// Desktop builds save the main application size and position on close (and restore it on open)
diff --git a/src/ui/toolbar/BatteryIndicator.qml b/src/ui/toolbar/BatteryIndicator.qml
index 9d68fc3c7..14c10c2ef 100644
--- a/src/ui/toolbar/BatteryIndicator.qml
+++ b/src/ui/toolbar/BatteryIndicator.qml
@@ -28,6 +28,7 @@ Item {
     property bool showIndicator: true
 
     property var _activeVehicle: QGroundControl.multiVehicleManager.activeVehicle
+    property var _generator: QGroundControl.multiVehicleManager.activeVehicle.generator
 
     Row {
         id:             batteryIndicatorRow
@@ -77,16 +78,40 @@ Item {
             }
 
             function getBatteryPercentageText() {
-                if (!isNaN(battery.percentRemaining.rawValue)) {
-                    if (battery.percentRemaining.rawValue > 98.9) {
-                        return qsTr("100%")
-                    } else {
-                        return battery.percentRemaining.valueString + battery.percentRemaining.units
+                if (_activeVehicle.generator.runtime.rawValue !== null)
+                {
+                    //console.log("generator fact exists")
+                     if (_activeVehicle.generator.busVoltage.rawValue > 0){
+                         //console.log("gen runtime more than 0")
+                         if (!isNaN(battery.percentRemaining.rawValue)) {
+                            if (battery.percentRemaining.rawValue > 98.9) {
+                                return qsTr("100%")
+                            } else {
+                                return battery.percentRemaining.valueString + battery.percentRemaining.units
+                            }
+                        }
+                    }
+                    if (!isNaN(battery.voltage.rawValue)) {
+                        return battery.voltage.valueString + battery.voltage.units
+                    }
+                }
+                else
+                {
+                    //console.log("generator null")
+//                    if (!isNaN(battery.percentRemaining.rawValue)) {
+//                        if (battery.percentRemaining.rawValue > 98.9) {
+//                            return qsTr("100%")
+//                        } else {
+//                            return battery.percentRemaining.valueString + battery.percentRemaining.units
+//                        }
+//                    } else if (!isNaN(battery.voltage.rawValue)) {
+//                        return battery.voltage.valueString + battery.voltage.units
+//                    } else if (battery.chargeState.rawValue !== MAVLink.MAV_BATTERY_CHARGE_STATE_UNDEFINED) {
+//                        return battery.chargeState.enumStringValue
+//                    }
+                    if (!isNaN(battery.voltage.rawValue)) {
+                        return battery.voltage.valueString + battery.voltage.units
                     }
-                } else if (!isNaN(battery.voltage.rawValue)) {
-                    return battery.voltage.valueString + battery.voltage.units
-                } else if (battery.chargeState.rawValue !== MAVLink.MAV_BATTERY_CHARGE_STATE_UNDEFINED) {
-                    return battery.chargeState.enumStringValue
                 }
                 return ""
             }
@@ -96,7 +121,7 @@ Item {
                 anchors.bottom:     parent.bottom
                 width:              height
                 sourceSize.width:   width
-                source:             "/qmlimages/Battery.svg"
+                source:             (_activeVehicle.generator.busVoltage.rawValue > 0) && (_activeVehicle.generator._timeout < 1) ? "/qmlimages/FuelTank.svg" : "/qmlimages/Battery.svg"
                 fillMode:           Image.PreserveAspectFit
                 color:              getBatteryColor()
             }
@@ -142,7 +167,7 @@ Item {
 
                 QGCLabel {
                     Layout.alignment:   Qt.AlignCenter
-                    text:               qsTr("Battery Status")
+                    text:               _activeVehicle.generator ? qsTr("Generator Status") : qsTr("Battery Status")
                     font.family:        ScreenTools.demiboldFontFamily
                 }
 
@@ -165,7 +190,7 @@ Item {
                                     property var battery: object
                                 }
 
-                                QGCLabel { text: qsTr("Battery %1").arg(object.id.rawValue) }
+                                QGCLabel { text: qsTr("Bat/Gen %1").arg(object.id.rawValue) }
                                 QGCLabel { text: qsTr("Charge State");                          visible: batteryValuesAvailable.chargeStateAvailable }
                                 QGCLabel { text: qsTr("Remaining");                             visible: batteryValuesAvailable.timeRemainingAvailable }
                                 QGCLabel { text: qsTr("Remaining") }
diff --git a/src/ui/toolbar/MainStatusIndicator.qml b/src/ui/toolbar/MainStatusIndicator.qml
index 1e2ff5f2c..9586c7ed0 100644
--- a/src/ui/toolbar/MainStatusIndicator.qml
+++ b/src/ui/toolbar/MainStatusIndicator.qml
@@ -174,31 +174,31 @@ RowLayout {
                     id:         mainLayout
                     spacing:    _spacing
 
-                    QGCButton {
-                        Layout.leftMargin:  _healthAndArmingChecksSupported ? width / 2 : 0
-                        Layout.alignment:   _healthAndArmingChecksSupported ? Qt.AlignLeft : Qt.AlignHCenter
-                        // FIXME: forceArm is not possible anymore if _healthAndArmingChecksSupported == true
-                        enabled:            _armed || !_healthAndArmingChecksSupported || _activeVehicle.healthAndArmingCheckReport.canArm
-                        text:               _armed ?  qsTr("Disarm") : (forceArm ? qsTr("Force Arm") : qsTr("Arm"))
-
-                        property bool forceArm: false
-
-                        onPressAndHold: forceArm = true
-
-                        onClicked: {
-                            if (_armed) {
-                                mainWindow.disarmVehicleRequest()
-                            } else {
-                                if (forceArm) {
-                                    mainWindow.forceArmVehicleRequest()
-                                } else {
-                                    mainWindow.armVehicleRequest()
-                                }
-                            }
-                            forceArm = false
-                            mainWindow.hideIndicatorPopup()
-                        }
-                    }
+//                    QGCButton {
+//                        Layout.leftMargin:  _healthAndArmingChecksSupported ? width / 2 : 0
+//                        Layout.alignment:   _healthAndArmingChecksSupported ? Qt.AlignLeft : Qt.AlignHCenter
+//                        // FIXME: forceArm is not possible anymore if _healthAndArmingChecksSupported == true
+//                        enabled:            _armed || !_healthAndArmingChecksSupported || _activeVehicle.healthAndArmingCheckReport.canArm
+//                        text:               _armed ?  qsTr("Disarm") : (forceArm ? qsTr("Force Arm") : qsTr("Arm"))
+
+//                        property bool forceArm: false
+
+//                        onPressAndHold: forceArm = true
+
+//                        onClicked: {
+//                            if (_armed) {
+//                                mainWindow.disarmVehicleRequest()
+//                            } else {
+//                                if (forceArm) {
+//                                    mainWindow.forceArmVehicleRequest()
+//                                } else {
+//                                    mainWindow.armVehicleRequest()
+//                                }
+//                            }
+//                            forceArm = false
+//                            mainWindow.hideIndicatorPopup()
+//                        }
+//                    }
 
                     QGCLabel {
                         Layout.alignment:   Qt.AlignHCenter
diff --git a/src/ui/toolbar/MainToolBar.qml b/src/ui/toolbar/MainToolBar.qml
index 9a183ffd2..11f8a218d 100644
--- a/src/ui/toolbar/MainToolBar.qml
+++ b/src/ui/toolbar/MainToolBar.qml
@@ -77,7 +77,22 @@ Rectangle {
             logo:                   true
             onClicked:              mainWindow.showToolSelectDialog()
         }
-
+        QGCToolBarButton {
+            id:                     flyButton
+            Layout.preferredHeight: viewButtonRow.height
+            icon.source:            "/qmlimages/PaperPlane.svg"
+            logo:                   true
+            onClicked:              mainWindow.showFlyView()
+            visible:                currentToolbar === planViewToolbar
+        }
+        QGCToolBarButton {
+            id:                     planButton
+            Layout.preferredHeight: viewButtonRow.height
+            icon.source:            "/qmlimages/Plan.svg"
+            logo:                   true
+            onClicked:              mainWindow.showPlanView()
+            visible:                currentToolbar === flyViewToolbar
+        }
         MainStatusIndicator {
             Layout.preferredHeight: viewButtonRow.height
             visible:                currentToolbar === flyViewToolbar
diff --git a/src/ui/toolbar/ModeIndicator.qml b/src/ui/toolbar/ModeIndicator.qml
index 75dcf7a43..c69712aa7 100644
--- a/src/ui/toolbar/ModeIndicator.qml
+++ b/src/ui/toolbar/ModeIndicator.qml
@@ -27,6 +27,7 @@ QGCComboBox {
     currentIndex:           -1
     sizeToContents:         true
 
+
     property bool showIndicator: true
 
     property var _activeVehicle:    QGroundControl.multiVehicleManager.activeVehicle
diff --git a/src/ui/toolbar/TelemetryRSSIIndicator.qml b/src/ui/toolbar/TelemetryRSSIIndicator.qml
index b51a392b2..1493e28bc 100644
--- a/src/ui/toolbar/TelemetryRSSIIndicator.qml
+++ b/src/ui/toolbar/TelemetryRSSIIndicator.qml
@@ -79,7 +79,7 @@ Item {
         anchors.bottom:     parent.bottom
         width:              height
         sourceSize.height:  height
-        source:             "/qmlimages/TelemRSSI.svg"
+        source:             "/qmlimages/RC.svg"
         fillMode:           Image.PreserveAspectFit
         color:              qgcPal.buttonText
     }
