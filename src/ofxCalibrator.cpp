#include "ofxCalibrator.h"
#include "ofxJSONElement.h"

#define PLOTSIZE 40

void ofxCalibrator::draw(ofFbo *fbo) {
	int i,j;
	
	for(i=0;i<screens.size();i++) {
		screen_t *screen = screens[i];
		for(j=0;j<screen->faces.size();j++) {
			face_t *face = screen->faces[j];
			face->fbo.begin();
			ofPushStyle();
			ofSetHexColor(0x000000);
			ofDrawRectangle(0,0,face->fbo.getWidth(),face->fbo.getHeight());
			ofPopStyle();
			fbo->draw(-face->offsetx,-face->offsety);
			face->fbo.end();

			face->fbo.getTexture().bind();
			face->vbo.draw(GL_QUADS,0,4);
			face->fbo.getTexture().unbind();

			// glActiveTexture(GL_TEXTURE0_ARB);
			// fbo_bg.getTexture().bind();
			// 
			// //draw a quad the size of the frame
			// glBegin(GL_QUADS);
			// glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 0);
			// glVertex2f(face->lt->x, face->lt->y);
			// glMultiTexCoord2d(GL_TEXTURE0_ARB, fbo_bg.getWidth(), 0);
			// glVertex2f(face->rt->x, face->rt->y);
			// glMultiTexCoord2d(GL_TEXTURE0_ARB, fbo_bg.getWidth(), fbo_bg.getHeight());
			// glVertex2f(face->rb->x, face->rb->y);
			// glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, fbo_bg.getHeight());
			// glVertex2f(face->lb->x, face->lb->y);
			// glEnd();
			// 
			// glActiveTexture(GL_TEXTURE0_ARB);
			// fbo_bg.getTexture().unbind();
			// 
			// 
			// glActiveTexture(GL_TEXTURE1_ARB);
			// face->fbo.getTexture().bind();
			// 
			// //draw a quad the size of the frame
			// glBegin(GL_QUADS);
			// glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, 0);
			// glVertex2f(face->lt->x, face->lt->y);
			// glMultiTexCoord2d(GL_TEXTURE1_ARB, face->fbo.getWidth(), 0);
			// glVertex2f(face->rt->x, face->rt->y);
			// glMultiTexCoord2d(GL_TEXTURE1_ARB, face->fbo.getWidth(), face->fbo.getHeight());
			// glVertex2f(face->rb->x, face->rb->y);
			// glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, face->fbo.getHeight());
			// glVertex2f(face->lb->x, face->lb->y);
			// glEnd();
			// 
			// //deactive and clean up
			// glActiveTexture(GL_TEXTURE1_ARB);
			// face->fbo.getTexture().unbind();
		}
	}
}

void ofxCalibrator::mousePressed(int x, int y) {
	int fw = fbo.getWidth();
	int fh = fbo.getHeight();
	int ww = ofGetWidth();
	int wh = ofGetHeight();
	float per = min((float)ww/(float)fw,(float)wh/(float)fh);
	int w = fw*per;
	int h = fh*per;
	float mx = (x-(ww-w)/2)/per;
	float my = (y-(wh-h)/2)/per;
	
	int i,j;
	p_dragging = NULL;
	for(i=0;i<current_screen->points.size();i++) {
		point_t *p = current_screen->points[i];
		float d = sqrt((mx-p->x)*(mx-p->x)+(my-p->y)*(my-p->y));
		if(d < PLOTSIZE) {
			p_dragging = p;
			return;
		}
	}
}
void ofxCalibrator::mouseDragged(int x, int y) {
	
	if(p_dragging == NULL) return;
	int fw = fbo.getWidth();
	int fh = fbo.getHeight();
	int ww = ofGetWidth();
	int wh = ofGetHeight();
	float per = min((float)ww/(float)fw,(float)wh/(float)fh);
	int w = fw*per;
	int h = fh*per;
	float mx = (x-(ww-w)/2)/per;
	float my = (y-(wh-h)/2)/per;
	p_dragging->x = mx;
	p_dragging->y = my;
}
ofFbo *ofxCalibrator::getFbo() {
	return &fbo;
}
void ofxCalibrator::update() {
	int i,j;
	fbo.begin();
	ofBackgroundHex(0x000000);
	ofSetColor(0xff,0,0);
	ofNoFill();
	ofSetLineWidth(4);
	for(i=0;i<screens.size();i++) {
		screen_t *screen = screens[i];
		int size = screen->faces.size();
		if(size == 0) continue;
		for(j=0; j<size; j++) {
			face_t *f = screen->faces[j];
			ofDrawLine(f->lt->x,f->lt->y,f->rt->x,f->rt->y);
			ofDrawLine(f->rt->x,f->rt->y,f->rb->x,f->rb->y);
			ofDrawLine(f->rb->x,f->rb->y,f->lb->x,f->lb->y);
			ofDrawLine(f->lb->x,f->lb->y,f->lt->x,f->lt->y);
			if(screen == current_screen ) {
				ofDrawRectangle(f->lt->x-PLOTSIZE/2,f->lt->y-PLOTSIZE/2,PLOTSIZE,PLOTSIZE);
				ofDrawRectangle(f->rt->x-PLOTSIZE/2,f->rt->y-PLOTSIZE/2,PLOTSIZE,PLOTSIZE);
				ofDrawRectangle(f->rb->x-PLOTSIZE/2,f->rb->y-PLOTSIZE/2,PLOTSIZE,PLOTSIZE);
				ofDrawRectangle(f->lb->x-PLOTSIZE/2,f->lb->y-PLOTSIZE/2,PLOTSIZE,PLOTSIZE);
			}
		}
	}
	fbo.end();
}
void ofxCalibrator::setCurrentScreen(int index) {
	if(index < screens.size())
		current_screen = screens[index];
}
void ofxCalibrator::prepare() {
	int i,j;
	float w = (float)width/(float)screens.size();
	for(i=0;i<screens.size();i++) {
		screen_t *screen = screens[i];
		for(j=0;j<screen->faces.size();j++) {
			face_t *face = screen->faces[j];
			face->fbo.allocate(face->ow,face->oh);
		}
	}
	fbo_bg.allocate(64,64);
	fbo_bg.begin();
	ofSetHexColor(0xffffff);
	ofDrawRectangle(0,0,fbo_bg.getWidth(),fbo_bg.getHeight());
	fbo_bg.end();
}
ofxCalibrator::ofxCalibrator() {
}
void ofxCalibrator::load() {
	int i,j;
	ofxJSONElement json;
	if(json.open("config.json")) {
		width = json["width"].asInt();
		height = json["height"].asInt();
		screenrow = json["screenrow"].asInt();
		screencol = json["screencol"].asInt();
	}
	if(width == 0) width = ofGetWidth();
	if(height == 0) height = ofGetHeight();
	if(screenrow == 0) screenrow = 1;
	if(screencol == 0) screencol = 3;
	for(i=0; i<screenrow;i++) {
		for(j=0; j<screencol;j++) {
			screen_t *screen = new screen_t();
			screen->index = i*screencol+j;
			screen->row = i;
			screen->col = j;
			screen->rows = 0;
			screen->cols = 0;
			screens.push_back(screen);
		}
	}
	char key[1024];
	ofxJSONElement settings;
	if(settings.open("calibration.json")) {
		for(i=0;i<screens.size();i++) {
			current_screen = screens[i];
			sprintf(key,".screen%d.colnum",current_screen->index);
			current_screen->cols = settings[key].asInt();
			sprintf(key,".screen%d.rownum",current_screen->index);
			current_screen->rows = settings[key].asInt();
			sprintf(key,".screen%d.facenum",current_screen->index);
			int facenum = settings[key].asInt();
			sprintf(key,".screen%d.pointnum",current_screen->index);
			int pointnum = settings[key].asInt();
			for(j=0; j<pointnum;j++) {
				sprintf(key,".screen%d.point%d_x",current_screen->index,j);
				float x = settings[key].asFloat();
				sprintf(key,".screen%d.point%d_y",current_screen->index,j);
				float y = settings[key].asFloat();
				newpoint(x,y);
			}
			for(j=0;j<facenum;j++) {
				face_t *face = new face_t();
				
				sprintf(key,".screen%d.face%d_offsetx",current_screen->index,j);
				face->offsetx = settings[key].asFloat();
				sprintf(key,".screen%d.face%d_offsety",current_screen->index,j);
				face->offsety = settings[key].asFloat();
				
				sprintf(key,".screen%d.face%d_ox", current_screen->index,j);
				face->ox = settings[key].asFloat();
				sprintf(key,".screen%d.face%d_oy", current_screen->index,j);
				face->oy = settings[key].asFloat();
				sprintf(key,".screen%d.face%d_ow", current_screen->index,j);
				face->ow = settings[key].asFloat();
				sprintf(key,".screen%d.face%d_oh", current_screen->index,j);
				face->oh = settings[key].asFloat();
				
				sprintf(key,".screen%d.face%d_lt",current_screen->index,j);
				int lt = settings[key].asInt();
				sprintf(key,".screen%d.face%d_rt",current_screen->index,j);
				int rt = settings[key].asInt();
				sprintf(key,".screen%d.face%d_rb",current_screen->index,j);
				int rb = settings[key].asInt();
				sprintf(key,".screen%d.face%d_lb",current_screen->index,j);
				int lb = settings[key].asInt();
				//
				face->lt = current_screen->points[lt];
				face->rt = current_screen->points[rt];
				face->rb = current_screen->points[rb];
				face->lb = current_screen->points[lb];
				
				face->vertices[0].x = face->lt->x;
				face->vertices[0].y = face->lt->y;
				face->vertices[1].x = face->rt->x;
				face->vertices[1].y = face->rt->y;
				face->vertices[2].x = face->rb->x;
				face->vertices[2].y = face->rb->y;
				face->vertices[3].x = face->lb->x;
				face->vertices[3].y = face->lb->y;
				face->texcoords[0].x = 0;
				face->texcoords[0].y = 0;
				face->texcoords[1].x = 1;
				face->texcoords[1].y = 0;
				face->texcoords[2].x = 1;
				face->texcoords[2].y = 1;
				face->texcoords[3].x = 0;
				face->texcoords[3].y = 1;
				face->vbo.setVertexData(face->vertices,4, GL_STATIC_DRAW);
				face->vbo.setTexCoordData(face->texcoords,4, GL_STATIC_DRAW);

				sprintf(key,".screen%d.face%d_row",current_screen->index,j);
				face->row = settings[key].asInt();
				sprintf(key,".screen%d.face%d_col",current_screen->index,j);
				face->col = settings[key].asInt();
				char k[16];
				sprintf(k,"%d_%d", face->row, face->col);
				current_screen->facemap.insert(map<string,face_t *>::value_type(k,face));
				current_screen->faces.push_back(face);
			}
		}
	}
	prepare();
	current_screen = screens[0];
	fbo.allocate(width, height);
}

void ofxCalibrator::save() {
	int i,j;
	char key[1024];
	ofxJSONElement settings;
	for(i=0;i<screens.size();i++) {
		screen_t *screen = screens[i];
		sprintf(key, ".screen%d.colnum", screen->index);
		settings[key] = (int)screen->cols;
		sprintf(key, ".screen%d.rownum", screen->index);
		settings[key] =  (int)screen->rows;
		sprintf(key, ".screen%d.facenum", screen->index);
		settings[key] =  (int)screen->faces.size();
		sprintf(key, ".screen%d.pointnum", screen->index);
		settings[key] =  (int)screen->points.size();
		for(j=0; j<screen->points.size();j++) {
			point_t *p = screen->points[j];
			p->index = j;
			sprintf(key,".screen%d.point%d_x", screen->index,j);
			settings[key] =  p->x;
			sprintf(key,".screen%d.point%d_y", screen->index,j);
			settings[key] =  p->y;
		}
		for(j=0; j<screen->faces.size();j++) {
			face_t *f = screen->faces[j];
			sprintf(key,".screen%d.face%d_row", screen->index,j);
			settings[key] =  f->row;
			sprintf(key,".screen%d.face%d_col", screen->index,j);
			settings[key] =  f->col;
			
			sprintf(key,".screen%d.face%d_offsetx", screen->index,j);
			settings[key] =  f->offsetx;
			sprintf(key,".screen%d.face%d_offsety", screen->index,j);
			settings[key] =  f->offsety;
			
			sprintf(key,".screen%d.face%d_ox", screen->index,j);
			settings[key] =  f->ox;
			sprintf(key,".screen%d.face%d_oy", screen->index,j);
			settings[key] =  f->oy;
			sprintf(key,".screen%d.face%d_ow", screen->index,j);
			settings[key] =  f->ow;
			sprintf(key,".screen%d.face%d_oh", screen->index,j);
			settings[key] =  f->oh;
			
			sprintf(key,".screen%d.face%d_lt", screen->index,j);
			settings[key] =  f->lt->index;
			sprintf(key,".screen%d.face%d_rt", screen->index,j);
			settings[key] =  f->rt->index;
			sprintf(key,".screen%d.face%d_rb", screen->index,j);
			settings[key] =  f->rb->index;
			sprintf(key,".screen%d.face%d_lb", screen->index,j);
			settings[key] =  f->lb->index;
		}
	}
	settings.save("calibration.json");
}
point_t *ofxCalibrator::newpoint(int x, int y) {
	point_t *p = new point_t;
	points.push_back(p);
	current_screen->points.push_back(p);
	p->x = x;
	p->y = y;
	return p;
}
void ofxCalibrator::deletepoint(point_t *p) {
	vector<point_t *>::iterator it = current_screen->points.begin();
	while(it !=current_screen->points.end()) {
		if(*it == p) {
			current_screen->points.erase(it);
			break;
		}
		it++;
	}
	it = points.begin();
	while(it !=points.end()) {
		if(*it == p) {
			points.erase(it);
			break;
		}
		it++;
	}
	delete p;
}
void ofxCalibrator::push_col() {
	int i;
	face_t *face;
	char key[16];
	if(current_screen->rows == 0 && current_screen->cols == 0) {
		face = new face_t();
		face->row = 0;
		face->col = 0;
		face->lt = newpoint(0,0);
		face->rt = newpoint(width, 0);
		face->rb = newpoint(width, height);
		face->lb = newpoint(0, height);
		sprintf(key,"%d_%d",face->row,face->col);
		current_screen->facemap.insert(map<string,face_t *>::value_type(key,face));
		current_screen->faces.push_back(face);
		current_screen->rows += 1;
	} else {
		point_t *rb_prev = NULL;
		for(i=0;i<current_screen->rows;i++) {
			sprintf(key,"%d_%d",i,current_screen->cols-1);
			face_t *last_face = current_screen->facemap[key];
			face = new face_t();
			face->row = i;
			face->col = current_screen->cols;
			face->lt = last_face->rt;
			face->rt = rb_prev == NULL ? newpoint(width,0) : rb_prev;
			rb_prev = face->rb = newpoint(width,height);
			face->lb = last_face->rb;
			sprintf(key,"%d_%d",face->row,face->col);
			current_screen->facemap.insert(map<string,face_t *>::value_type(key,face));
			current_screen->faces.push_back(face);
		}
	}
	current_screen->cols += 1;
	rebuild_faces();
}
void ofxCalibrator::push_row() {
	int i;
	face_t *face;
	char key[16];
	if(current_screen->rows == 0 && current_screen->cols == 0) {
		face = new face_t();
		face->row = 0;
		face->col = 0;
		face->lt = newpoint(0,0);
		face->rt = newpoint(width, 0);
		face->rb = newpoint(width, height);
		face->lb = newpoint(0, height);
		sprintf(key,"%d_%d",face->row,face->col);
		current_screen->facemap.insert(map<string,face_t *>::value_type(key,face));
		current_screen->faces.push_back(face);
		current_screen->cols += 1;
	} else {
		point_t *rb_prev = NULL;
		for(i=0;i<current_screen->cols;i++) {
			sprintf(key,"%d_%d",current_screen->rows-1,i);
			face_t *last_face = current_screen->facemap[key];
			face = new face_t();
			face->row = current_screen->rows;
			face->col = i;
			face->lt = last_face->lb;
			face->rt = last_face->rb;
			face->lb = rb_prev == NULL ? newpoint(0,height) : rb_prev;
			rb_prev = face->rb = newpoint(width,height);
			sprintf(key,"%d_%d",face->row,face->col);
			current_screen->facemap.insert(map<string,face_t *>::value_type(key,face));
			current_screen->faces.push_back(face);
		}
	}
	current_screen->rows += 1;
	rebuild_faces();
}
void ofxCalibrator::pop_row() {
	int i,j;
	face_t *face, *last_face;
	char key[16];
	if(current_screen->faces.size() == 0) return;
	for(i=0;i<current_screen->cols;i++) {
		sprintf(key,"%d_%d",current_screen->rows-1,i);
		last_face = current_screen->facemap[key];
		vector<face_t *>::iterator it = current_screen->faces.begin();
		while(it != current_screen->faces.end()) {
			face = *it;
			if(face->row == current_screen->rows-1 && face->col == i) {
				current_screen->faces.erase(it);
				break;
			}
			it++;
		}
		deletepoint(last_face->lb);
		if(current_screen->rows == 1) deletepoint(last_face->lt);
		if(i < current_screen->cols-1) {
			map<string, face_t *>::iterator it = current_screen->facemap.begin();
			while(it != current_screen->facemap.end()) {
				if((*it).second == last_face) {
					current_screen->facemap.erase(it);
					break;
				}
				it++;
			}
			delete last_face;
		}
	}
	deletepoint(last_face->rb);
	if(current_screen->rows == 1) deletepoint(last_face->rt);
	map<string, face_t *>::iterator it = current_screen->facemap.begin();
	while(it != current_screen->facemap.end()) {
		if((*it).second == last_face) {
			current_screen->facemap.erase(it);
			break;
		}
		it++;
	}
	delete last_face;
	current_screen->rows -= 1;
	if(current_screen->rows == 0) current_screen->cols = 0;
	rebuild_faces();
}
void ofxCalibrator::pop_col() {
	int i,j;
	face_t *face, *last_face;
	char key[16];
	if(current_screen->faces.size() == 0) return;
	for(i=0;i<current_screen->rows;i++) {
		sprintf(key,"%d_%d",i,current_screen->cols-1);
		last_face = current_screen->facemap[key];
		vector<face_t *>::iterator it = current_screen->faces.begin();
		while(it != current_screen->faces.end()) {
			face = *it;
			if(face->row == i && face->col == current_screen->cols-1) {
				current_screen->faces.erase(it);
				break;
			}
			it++;
		}
		deletepoint(last_face->rt);
		if(current_screen->cols == 1) deletepoint(last_face->lt);
		if(i < current_screen->rows-1) {
			map<string, face_t *>::iterator it = current_screen->facemap.begin();
			while(it != current_screen->facemap.end()) {
				if((*it).second == last_face) {
					current_screen->facemap.erase(it);
					break;
				}
				it++;
			}
			delete last_face;
		}
	}
	if(current_screen->cols == 1) deletepoint(last_face->lb);
	deletepoint(last_face->rb);
	map<string, face_t *>::iterator it = current_screen->facemap.begin();
	while(it != current_screen->facemap.end()) {
		if((*it).second == last_face) {
			current_screen->facemap.erase(it);
			break;
		}
		it++;
	}
	delete last_face;
	current_screen->cols -= 1;
	if(current_screen->cols == 0) current_screen->rows = 0;
	rebuild_faces();
}
void ofxCalibrator::rebuild_faces() {
	int i,j;
	char key[16];
	int cols = current_screen->cols;
	int rows = current_screen->rows;
	if(cols == 0 || rows == 0) return;
	float w = (float)width/(float)screencol;
	float h = (float)height/(float)screenrow;
	float x = (float)current_screen->col*w;
	float y = (float)current_screen->row*h;
	float fwidth = w/(float)cols;
	float fheight = h/(float)rows;
	for(i=0; i<cols; i++) {
		for(j=0;j<rows; j++) {
			sprintf(key,"%d_%d",j,i);
			face_t *f = current_screen->facemap[key];
			f->ox = f->lt->x = x+(float)i*fwidth;
			f->lb->x = x+(float)i*fwidth;
			f->rt->x = x+(float)(i+1)*fwidth;
			f->rb->x = x+(float)(i+1)*fwidth;
			f->oy = f->lt->y = y+(float)j*fheight;
			f->lb->y = y+(float)(j+1)*fheight;
			f->rt->y = y+(float)j*fheight;
			f->rb->y = y+(float)(j+1)*fheight;
			f->ow = fwidth;
			f->oh = fheight;
			float px = (float)width/(float)screencol;
			float py = (float)height/(float)screenrow;
			f->offsetx = (float)current_screen->col*px + px/(float)current_screen->cols*(float)i;
			f->offsety = (float)current_screen->row*py + py/(float)current_screen->rows*(float)j;
		}
	}
}
