#include "constants.h"
#include "ofApp.h"
#include <random>

void ofApp::setup() {
	ofSetWindowTitle("Final Project");
	ofSetBackgroundColor(0, 0, 0);

	box2d.init();
	box2d.setGravity(0, 0);

	resetGame();
}

void ofApp::update() {
	ofSoundUpdate();
	updateFFT();

	checkForCollisions();
	box2d.update();

	if (!player.isPlaying() && boxes.empty()) {
		resetGame();
	}
}

void ofApp::draw() {
	ofSetColor(0, 0, 255);
	playerChar.draw();

	for (int i = 0; i < boxes.size(); i++) {
		ofSetColor(255, 0, 0);
		boxes[i].get()->draw();
	}

	drawScore();
}

void ofApp::keyPressed(int key) {
	int upperKey = toupper(key);

	if (upperKey == kPauseKey) {
		isPaused = true;
		player.setPaused(isPaused);

		for (int i = 0; i < boxes.size(); i++) {
			boxes[i].get()->setVelocity(0, 0);
		}
	}
	else if (upperKey == kUnpauseKey) {
		isPaused = false;
		player.setPaused(isPaused);

		for (int i = 0; i < boxes.size(); i++) {
			boxes[i].get()->setVelocity(0, kBoxVelocity);
		}
	}
	else if (upperKey == kResetKey) {
		resetGame();
	}
	else if (upperKey == kQuitKey) {
		ofExit();
	}

	if (!isPaused) {
		if (upperKey == kLeftKey) {
			playerChar.setPosition(3 * ofGetWindowWidth() / 8, playerChar.getPosition().y);
		}
		else if (upperKey == kMiddleKey) {
			playerChar.setPosition(ofGetWindowWidth() / 2, playerChar.getPosition().y);
		}
		else if (upperKey == kRightKey) {
			playerChar.setPosition(5 * ofGetWindowWidth() / 8, playerChar.getPosition().y);
		}
	}
}

void ofApp::checkForCollisions() {
	for (int i = 0; i < boxes.size(); i++) {
		bool isSameLane = abs(playerChar.getPosition().x - boxes[i].get()->getPosition().x) < 0.1;
		bool isSameHeight = abs(playerChar.getPosition().y - boxes[i].get()->getPosition().y) < kPlayerSize;
		bool isOffScreen = boxes[i].get()->getPosition().y > ofGetWindowHeight();

		if (isSameLane && isSameHeight) {
			boxes[i].get()->destroy();
			boxes.erase(boxes.begin() + i);
			playerPoints += kPointsPerBox;
			maxPoints += kPointsPerBox;
		}
		else if (isOffScreen) {
			boxes[i].get()->destroy();
			boxes.erase(boxes.begin() + i);
			maxPoints += kPointsPerBox;
		}
	}
}

void ofApp::updateFFT() {
	float firstBand = ofSoundGetSpectrum(kNumBands)[0];

	bool isBandSignificant = firstBand > average(bands) && firstBand - bands.back() > sqrt(variance(bands));
	
	if (player.getPositionMS() - position > 250 && !bands.empty() && isBandSignificant) {
		mt19937 generator(rand());
		uniform_int_distribution<> dist(3, 5);
		int randPosition = dist(generator) * ofGetWindowWidth() / 8;

		auto box = make_shared<ofxBox2dRect>();
		box.get()->setPhysics(1, 0, 0);
		box.get()->setup(box2d.getWorld(), randPosition, 100, kBoxSize, kBoxSize);
		box.get()->setVelocity(0, kBoxVelocity);

		boxes.push_back(box);
		position = player.getPositionMS();
	}

	// to eliminate noise
	if (firstBand > 0.001) {
		bands.push_back(firstBand);
	}
}

void ofApp::resetGame() {
	srand(static_cast<unsigned>(time(0)));

	playerChar.destroy();
	playerChar.setup(box2d.getWorld(), ofGetWindowWidth() / 2, ofGetWindowHeight() - 100, kPlayerSize, kPlayerSize);

	player.unload();
	string textBoxDescription = "Input song (add file extension, should be in data folder)";
	while (!player.isLoaded()) {
		string song = ofSystemTextBoxDialog(textBoxDescription, kQuitMessage);
		if (song == kQuitMessage) {
			std::exit(0);
		}
		player.load(song);
	}
	player.play();
	keyPressed(kUnpauseKey);

	position = 0;
	playerPoints = 0;
	maxPoints = 0;
	bands.clear();
	boxes.clear();
}

void ofApp::drawScore() {
	string scores = "Player Points: " + to_string(playerPoints) + 
		"\nMax Points: " + to_string(maxPoints) + 
		"\nAccuracy: " + to_string(calculateAccuracy(playerPoints, maxPoints)) + "%";

	ofSetColor(255, 255, 255);
	ofDrawBitmapString(scores, ofGetWindowWidth() / 8, ofGetWindowHeight() / 8);
}

float average(vector<float> bands) {
	float sum = 0;
	for (int i = 0; i < bands.size(); i++) {
		sum += bands[i];
	}
	return sum / bands.size();
}

float variance(vector<float> bands) {
	float mean = average(bands), sum = 0;
	for (int i = 0; i < bands.size(); i++) {
		sum += pow((bands[i] - mean), 2);
	}
	return sum / bands.size();
}

int calculateAccuracy(int playerPoints, int maxPoints) {
	if (maxPoints == 0) {
		return 100;
	}
	return (int)(100.0 * playerPoints / maxPoints);
}