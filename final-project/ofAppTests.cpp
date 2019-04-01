#define CATCH_CONFIG_MAIN
#include "catch.h"
#include "./src/ofApp.h"

TEST_CASE("Test average", "[tests]") {
	vector<float> v1 = {0, 2, 4, 5.5};

	REQUIRE(average(v1) == 2.875);
}

TEST_CASE("Test variance", "[tests]") {
	vector<float> v1 = {0, 2, 4, 5.5};

	REQUIRE(variance(v1) == 4.296875);
}

TEST_CASE("Test calculating accuracy", "[tests]") {
	SECTION("Regular case") {
		REQUIRE(calculateAccuracy(2, 6) == 33);
	}
	SECTION("Divide by zero") {
		REQUIRE(calculateAccuracy(0, 0) == 100);
	}
}