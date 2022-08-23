#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ofxGui.h"

#define NUM_PARTICLES 20000

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofLight light;
    
    ofFbo fbo;
    // Avec object c++
    std::vector<std::shared_ptr<Particle>> particles;
    //std::vector<Particle*> particles;
    
    ofxPanel gui;
    ofxFloatSlider attraction, dt, center_attr, rotation_speed, alpha;
    ofxVec3Slider lightPos;
    
    glm::vec2 mousePos;
    bool mouseActive;
    
    float canvas_width, canvas_height;
    float project_width, project_height;
    
    glm::vec3 testRotate = glm::vec3(0.4,0.5,0.6);
};
