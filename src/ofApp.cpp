#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    light.setup();
    mouseActive = false;
    ofBackground(0);
    
    canvas_width = ofGetWidth();
    canvas_height = ofGetHeight();
    
    fbo.allocate(canvas_width, canvas_height);
    fbo.begin();
    ofClear(0,0,0);
    fbo.end();
    
    project_width = fbo.getWidth();
    project_height = fbo.getHeight();
    
    for(int i = 0; i < NUM_PARTICLES; i++){
        glm::vec2 position(ofRandom(-1,1), ofRandom(-1,1));
        //particles.push_back(p);
        particles.push_back(std::make_shared<Particle>(position));
    }
    
    gui.setup();
    gui.add(attraction.setup("attraction", -0.06, -0.5, 0.5));
    gui.add(center_attr.setup("center_attraction", 0.21, -0.5, 0.5));
    gui.add(dt.setup("dt", 0.033, 0, 0.1));
    gui.add(rotation_speed.setup("rotation_speed", 0.001, -0.1, 0.1));
    gui.add(alpha.setup("alpha", 15, 0, 25));
    gui.add(lightPos.setup("lightPos", ofVec3f(project_width/2,project_height/2,300), ofVec3f(0,0,0), ofVec3f(project_width,project_height,500)));
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){

    
    if(mouseActive){
        mousePos = glm::vec2((ofGetMouseX() / project_width) - 0.5, (ofGetMouseY() / project_height) - 0.5);
    } else mousePos = {0,0};
    
    light.setPosition(lightPos->x, lightPos->y, lightPos->z);
    light.enable();
    fbo.begin();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnableAlphaBlending();
    ofSetColor(0,0,0,alpha);
    ofDrawRectangle(0,0, project_width, project_height);
    ofSetColor(255);

    for(auto &p:particles){
        p->dt = dt;
        p->attraction_ = attraction;
        p->center_attr = center_attr;
        p->angle = rotation_speed;
        p->mouse = mousePos;
    
        p->update();
        
        ofPushMatrix();
        ofTranslate(canvas_width/2, canvas_height/2);
        ofScale(canvas_width, canvas_height);
        p->draw();
        ofPopMatrix();
        
    }

    fbo.end();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofDrawBitmapString(ofToString(mousePos), 10, 10);
    fbo.draw(0,0);
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == 'm'){
        mouseActive = !mouseActive;
    }
    
    if(key == 'r'){
        for(auto &p:particles){
            p->rotate = !p->rotate;
        }
    }
    
    float rotTest = 90.;
    if(key == 't'){
        ofLogNotice("before") << testRotate;
        testRotate = glm::rotate(testRotate, rotTest, glm::vec3(0.0, 1.0, 0.0));
        ofLogNotice("after") << testRotate;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
   
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
