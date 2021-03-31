#include "typewise-alert.h"
#include <stdio.h>

BreachType BMS_Alerter::inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType BMS_Alerter::classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {

  auto limits = map_cooling[coolingType];
  return inferBreach(temperatureInC, limits.first, limits.second);
}



void BMS_Alerter::checkAndAlert(ILogger &logger, BatteryCharacter batteryChar, double temperatureInC) 
{
  logger.log_data(classifyTemperatureBreach(batteryChar.coolingType, temperatureInC));
}

void ControllerLogger::log_data(BreachType breachType)
{
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

void EmailLogger::log_data(BreachType breachType)
{
    const char* recepient = "a.b@c.com";

    std::cout << "To: " << recepient << "\n";
    std::cout<< map_breach_message[breachType] << "\n";

}