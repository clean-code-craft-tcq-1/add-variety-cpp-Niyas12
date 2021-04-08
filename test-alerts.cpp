#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
	BMS_Alerter alerter;
	EmailLogger email;
	BatteryCharacter battery_char;
	battery_char.coolingType = PASSIVE_COOLING;
	REQUIRE(alerter.checkAndAlert(email, battery_char, 40.0) == TOO_HIGH);
	REQUIRE(alerter.checkAndAlert(email, battery_char, -1.0) == TOO_LOW);
	REQUIRE(alerter.checkAndAlert(email, battery_char, 5.0) == NORMAL);

	ControllerLogger controller;
	REQUIRE(alerter.checkAndAlert(controller, battery_char, 40.0) == TOO_HIGH);

	Console console;
	REQUIRE(alerter.checkAndAlert(console, battery_char, 40.0) == TOO_HIGH);
}
