#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
	BMS_Alerter alerter;
	EmailLogger email;
	BatteryCharacter battery_char;
	battery_char.coolingType = PASSIVE_COOLING;
	alerter.checkAndAlert(email, battery_char, 40.0);
	alerter.checkAndAlert(email, battery_char, -1.0);
	alerter.checkAndAlert(email, battery_char, 5.0);

	ControllerLogger controller;
	alerter.checkAndAlert(controller, battery_char, 40.0);
}
