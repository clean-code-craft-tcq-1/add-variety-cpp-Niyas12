#include "typewise-alert.h"
#include <stdio.h>

std::map<BreachType, std::string> map_breach_message =
{
{TOO_LOW ,"Hi, the temperature is too low" },
{TOO_HIGH ,"Hi, the temperature is too high" },
{NORMAL ,"Hi, the temperature is Normal" }
};

std::map<CoolingType, std::pair<double, double>> map_cooling =
{ { PASSIVE_COOLING ,std::make_pair(0,35) },
    { HI_ACTIVE_COOLING ,std::make_pair(0,45) },
    { MED_ACTIVE_COOLING ,std::make_pair(0,40) }
};

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



BreachType BMS_Alerter::checkAndAlert(ILogger &logger, BatteryCharacter batteryChar, double temperatureInC)
{
    auto  breach = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    logger.log_data(breach);

    return breach;
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

void Console::log_data(BreachType breachType)
{
    std::cout << map_breach_message[breachType] << "\n";
}
