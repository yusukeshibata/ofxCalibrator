#ifndef __Calibration__ofxCalibrator__
#define __Calibration__ofxCalibrator__

#include <iostream>
#include "ofMain.h"
#include <vector>
#include <map>

typedef struct _point_t {
    int index;
    float x;
    float y;
} point_t;

typedef struct _face_t {
    ofFbo fbo;
    int col,row;
    float offsetx,offsety;
    float ox,oy,ow,oh;
    point_t *lt, *rt, *rb, *lb;
} face_t;
typedef struct _screen_t {
    int index;
    int row,col;
    int rows,cols;
    map<string, face_t*> facemap;
    vector <point_t *> points;
    vector <face_t *> faces;
} screen_t;

class ofxCalibrator {
    
    point_t *p_dragging;
    vector<screen_t *> screens;
    vector<point_t *> points;
    point_t *newpoint(int x, int y);
    void deletepoint(point_t *p);
    void rebuild_faces();
    void prepare();
    ofFbo fbo,fbo_bg;
    
    screen_t *current_screen;
    int width, height;
    int screenrow,screencol;
public:
    void load();
    ofxCalibrator();
    void draw(ofFbo *fbo);
    void setCurrentScreen(int index);
    void push_col();
    void pop_col();
    void push_row();
    void pop_row();
    void save();
    void update();
    ofFbo *getFbo();
    void mousePressed(int x, int y);
    void mouseDragged(int x, int y);
};


#endif /* defined(__Calibration__ofxCalibrator__) */
