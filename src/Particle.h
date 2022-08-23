//
//  Particle.h
//  gs-Particle-001
//
//  Created by Guillaume Sylvain on 2020-11-03.
//

#ifndef Particle_h
#define Particle_h

class Particle{
public:
    
    glm::vec2 mouse, center = glm::vec2(0,0);
    glm::vec2 pos_, force_att, force_rep, mass_, force_, oldVel_, newVel_, rot;
    float size_, attraction_, dt, length_, center_attr, angle;
    bool rotate;
    
    Particle(glm::vec2 location){
        mass_ = glm::vec2(ofRandom(1,3), ofRandom(1,3));
        pos_ = location;
        size_ = 0.001;
        attraction_ = -0.08;
        dt = 0.033;
        rotate = false;
        angle = 0.01;
    }
    
    void update(){
        
        // Force
        force_rep = mouse - pos_;
        force_att = center - pos_;
        
        force_att *= center_attr; // center_attraction
        
        length_ = glm::length(force_rep);
        length_ = length_ * length_;        // sqrt
        length_ += 0.1;                     // = ø division par 0
        length_ = attraction_ / length_;    
        force_rep = force_rep * length_;
        
        // Mass
        force_rep = force_rep / mass_;

        // combine les forces
        force_ = force_rep + force_att;
        
        // Ajout de velocité
        newVel_ = force_ + (oldVel_ * 0.97);
        oldVel_ = newVel_;
        
        // update
        newVel_ *= dt;
        
        // limit
        if(glm::length(newVel_) > 0.5f){
            newVel_ = glm::normalize(newVel_) * 0.5f;
        }
        
        if(rotate){
            pos_ += glm::rotate(newVel_, angle);
        } else pos_ += newVel_;
        
        keep_in_canvas();
    }
    
    void draw(){
        ofColor c = ofColor::blue;
        float hue = ofMap(mass_.x, 1, 3, 110, 155);
        c.setHue( hue );
        ofSetColor(c);
        ofDrawCircle(pos_.x, pos_.y, size_);
    }
    
    void keep_in_canvas() {
        if(pos_.x > 1) {
            pos_.x = -1;
        } else if(pos_.x < -1) {
            pos_.x = 1;
        }
        if(pos_.y > 1) {
            pos_.y = -1;
        } else if(pos_.y < -1) {
            pos_.y = 1;
        }
    }

    //ici on s'assure que les particules restent dans le canevas AVEC DU BOUNCE
    void keep_in_canvas_bounce() {
        if(pos_.x >= 1 - size_ || pos_.x <= size_) {
            newVel_.x *= -1;
            pos_.x = ofClamp(pos_.x, size_, 1 - size_);
        }
        if(pos_.y >= 1 - size_ || pos_.y <= size_) {
            newVel_.y *= -1;
            pos_.y = ofClamp(pos_.y, size_, 1 - size_);
        }
    }
};

#endif /* Particle_h */
