#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

class ofApp : public ofBaseApp {
private:
	ofSoundPlayer player;
	vector<float> bands;
	bool isPaused;
	int position;

	int playerPoints;
	int maxPoints;

	ofxBox2d box2d;
	ofxBox2dRect playerChar;
	vector<shared_ptr<ofxBox2dRect>> boxes;

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void checkForCollisions();
	void updateFFT();
	void resetGame();
	void drawScore();
};

float average(vector<float> bands);
float variance(vector<float> bands);
int calculateAccuracy(int playerPoints, int maxPoints);