#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "Booleans.h"
#include "std_types.h"
#include "car.h"


void SysInit();
void DisplayStartScreen();
void DisplaySensors();
void SetCarSpeed();
void SetRoomTemperatureSensor();
void SetEngTemperatureSensor();
#if  CAR_TYPE ==  WITH_ENGINE_TEMP_CONTROLLER
void SetEngTemperatureSensor();
#endif // CAR_TYPE


#endif
