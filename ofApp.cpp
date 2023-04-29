#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofColor color;
	int hue = ofRandom(255);
	float len = 20;

	for (int x = -220; x <= 220; x += 220) {

		for (int y = -220; y <= 220; y += 220) {

			ofPushMatrix();
			ofTranslate(x, y);

			for (int i = 0; i < 3; i++) {

				vector<glm::vec2> vertices_1, vertices_2;
				float deg_start = ofRandom(360) + ofGetFrameNum() * ofRandom(3, 10);

				for (float deg = deg_start; deg < deg_start + 120; deg += 1) {

					auto noise_radius = ofMap(ofNoise(x + cos(deg * DEG_TO_RAD) * 0.5, y + sin(deg * DEG_TO_RAD) * 0.5, ofGetFrameNum() * 0.005), 0, 1, 50, 100);

					vertices_1.push_back(glm::vec2((noise_radius - len * 0.5) * cos(deg * DEG_TO_RAD), (noise_radius - len * 0.5) * sin(deg * DEG_TO_RAD)));
					vertices_2.push_back(glm::vec2((noise_radius + len * 0.5) * cos(deg * DEG_TO_RAD), (noise_radius + len * 0.5) * sin(deg * DEG_TO_RAD)));
				}

				reverse(vertices_2.begin(), vertices_2.end());

				color.setHsb(hue, 150, 255);

				ofFill();
				ofSetColor(color);

				ofBeginShape();
				ofVertices(vertices_1);
				ofVertices(vertices_2);
				ofEndShape(true);

				ofNoFill();
				ofSetColor(255);

				ofBeginShape();
				ofVertices(vertices_1);
				ofVertices(vertices_2);
				ofEndShape(true);

				hue = (hue + (int)ofRandom(20, 120)) % 255;
			}

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}