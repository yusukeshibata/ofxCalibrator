# ofxCalibrator

Openframeworks addon for calibration.  
Distort FBO for projection calibration.  

## How to calibrate

Test calibrator is in `examples/setup.app`.  
setup.app load config from `bin/data/config.json` and generate calibration data at `bin/data/config.caliration.json`.  
Press `s` key for save current calibration.  
Press `1-9` key to change screen to calibrate.  
Press `LEFT_ARROW` to add column to current calibrating screen.  
Press `RIGHT_ARROW` to remove last added column from current calibrating screen.  
Press `BOTTOM_ARROW` to add row to current calibrating screen.  
Press `TOP_ARROW` to remove last added row from current calibrating screen.  

Drag corner point for calibrate current screen.  

### Calibrator application

To your app's Project.xcconfig
```
HEADER_SEARCH_PATHS = $("HEADER_SEARCH_PATHS") "$(OF_PATH)/addons/ofxJSON/libs/jsoncpp/include"
```

in ofApp.h
```c
#include "ofMain.h"
#include "ofxCalibrator.h"

class ofApp : public ofBaseApp{
	...
	ofxCalibrator calib;
	...
}
```

in ofApp.cpp
```c
void ofApp::setup() {
	...
	calib.load("distort");
	...
}
void ofApp::draw() {
	calib.draw(&fbo);
}
```

in your `bin/data/distort.json`
```json
{
	"width":3840,	
	"height":1080,
	"screencol":4,
	"screenrow":1,
	"divx":8,			
	"divy":8,
	"reverse":false
}
```
This setting loads `bin/data/distort.json` and use calibration data `bin/data/distort.calibration.json`

`width` : FBO width  
`height` : FBO height  
`screencol` : FBO grid column num  
`screenrow` : FBO grid row num## How to draw with calibrated data  
`divx`,`divy` : Draw each cell separately 8 grid  
`reverse` : FALSE:Crop mode,TRUE:Distort mode

To your app's Project.xcconfig
```
HEADER_SEARCH_PATHS = $("HEADER_SEARCH_PATHS") "$(OF_PATH)/addons/ofxJSON/libs/jsoncpp/include"
```

in ofApp.h
```c
#include "ofMain.h"
#include "ofxCalibrator.h"

class ofApp : public ofBaseApp{
	...
	ofxCalibrator calib;
	...
}
```

in ofApp.cpp
```c
void ofApp::setup() {
	...
	calib.load("distort");
	...
}
void ofApp::draw() {
	calib.draw(&fbo);
}
```

in your `bin/data/distort.json`
```json
{
	"width":3840,
	"height":1080,
	"screencol":4,
	"screenrow":1,
	"divx":8,
	"divy":8,
	"reverse":false
}
```

This setting loads `bin/data/distort.json` and use calibration data `bin/data/distort.calibration.json`.
