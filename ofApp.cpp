#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int x = -300; x <= 300; x += 150) {

		for (int y = -300; y <= 300; y += 150) {

			ofPushMatrix();
			ofTranslate(x, y);

			auto rotate = ofMap(ofNoise(x * 0.005, y * 0.005, ofGetFrameNum() * 0.005), 0, 1, -360, 360);
			ofRotateY(rotate);
			ofRotateX(rotate);

			vector<glm::vec3> top, bottom;
			auto radius = 50;
			auto depth = 15;
			auto span = 5;
			for (auto deg = 0; deg < 360; deg += span) {

				top.push_back(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), depth * 0.5));
				bottom.push_back(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), depth * -0.5));

				ofSetColor(39);
				ofBeginShape();
				ofVertex(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), depth * 0.5 + 1));
				ofVertex(glm::vec3(radius * cos((deg + span) * DEG_TO_RAD), radius * sin((deg + span) * DEG_TO_RAD), depth * 0.5 + 1));
				ofVertex(glm::vec3(radius * cos((deg + span) * DEG_TO_RAD), radius * sin((deg + span) * DEG_TO_RAD), depth * -0.5 - 1));
				ofVertex(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), depth * -0.5 - 1));
				ofEndShape(true);
			}

			ofSetColor(239);

			ofBeginShape();
			ofVertices(top);
			ofEndShape(true);

			ofBeginShape();
			ofVertices(bottom);
			ofEndShape(true);

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