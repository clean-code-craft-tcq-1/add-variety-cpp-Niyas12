#pragma once
#include <iostream>
#include <map>

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;


typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;



class ILogger
{
public:
	virtual void log_data(BreachType breachType) = 0;
};

class ControllerLogger : public ILogger
{
public:
	virtual void log_data(BreachType breachType);

};

class EmailLogger : public ILogger
{
	std::map<BreachType, std::string> map_breach_message =
	{ 
	{TOO_LOW ,"Hi, the temperature is too low" },
	{TOO_HIGH ,"Hi, the temperature is too high" },
	{NORMAL ,"Hi, the temperature is Normal" }
	};

public:
	virtual void log_data(BreachType breachType);

};

class Console : public ILogger
{
	std::map<BreachType, std::string> map_breach_message =
	{
	{TOO_LOW ,"Hi, the temperature is too low" },
	{TOO_HIGH ,"Hi, the temperature is too high" },
	{NORMAL ,"Hi, the temperature is Normal" }
	};

public:
	virtual void log_data(BreachType breachType);

};

class BMS_Alerter
{
	std::map<CoolingType, std::pair<double, double>> map_cooling = 
	{	{ PASSIVE_COOLING ,std::make_pair(0,35) },
		{ HI_ACTIVE_COOLING ,std::make_pair(0,45) },
		{ MED_ACTIVE_COOLING ,std::make_pair(0,40) }
	};

	BreachType inferBreach(double value, double lowerLimit, double upperLimit);
	BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

public:
	BreachType checkAndAlert(ILogger& logger, BatteryCharacter batteryChar, double temperatureInC);
};