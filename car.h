#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

/*Configuration*/
#define WITH_ENGINE_TEMP_CONTROLLER 1
#define WITHOUT_ENGINE_TEMP_CONTROLLER 0
#define CAR_TYPE  WITH_ENGINE_TEMP_CONTROLLER

typedef enum {
    CLOSED_AC,
    OPENED_AC
}AC_State;


typedef enum{
    CLOSED_MOTOR,
    OPENED_MOTOR
}MotorState;

  #if  CAR_TYPE ==  WITH_ENGINE_TEMP_CONTROLLER
typedef enum {
    CLOSED_TEMPCONTROLLER,
    OPENED_TEMPCONTROLLER
}EngTempControllerState;
  #endif // CAR_TYPE

typedef struct {
    u8 CarSpeed ;
    f32 CarRoomTemperature ;
    f32 CarEngineTemperature;
    AC_State CarAC ;
    MotorState EngineState;

    #if  CAR_TYPE ==  WITH_ENGINE_TEMP_CONTROLLER
    EngTempControllerState EngTempController ;
    #endif // CAR_TYPE
}CAR;




#endif // CAR_H_INCLUDED
