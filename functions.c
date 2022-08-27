#include <stdio.h>
#include "functions.h"
extern CAR car ;
void SysInit(){
    car.EngineState = CLOSED_MOTOR ;
    car.CarSpeed = 0 ;
    car.CarRoomTemperature = 20 ;
    car.CarEngineTemperature = 30 ;
    car.CarAC = CLOSED_AC ;
    #if  CAR_TYPE ==  WITH_ENGINE_TEMP_CONTROLLER
    car.EngTempController = CLOSED_TEMPCONTROLLER ;
    #endif // CAR_TYPE
}
void DisplayStartScreen(){

    BOOL RepeatFlag = FALSE  ;
    u8 UserAnswer ;
    printf("\n--------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t INITIAL SCREEN") ;
    printf("\n--------------------------------------------------------------------------------------------------------------------\n");
    do{
    if (RepeatFlag==TRUE){
        printf("\n\n");
    }
    printf("Enter A to turn on vehicle Engine\n") ;
    printf("Enter B to turn off vehicle Engine\n") ;
    printf("Enter C to Quit the system\n") ;
    printf("Your answer : ") ;
    scanf(" %c",&UserAnswer) ;


    if (UserAnswer== 'A' || UserAnswer == 'C')
        RepeatFlag = FALSE ;

    else if (UserAnswer == 'B')
        {

           SysInit();
        }
    else RepeatFlag = TRUE  ;

    }while(RepeatFlag);

    if (UserAnswer == 'A')
        {
        car.EngineState = OPENED_MOTOR ;
        DisplaySensors();
        }
   else if (UserAnswer=='C'){
    printf("\n--------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t  System Exit") ;
    printf("\n--------------------------------------------------------------------------------------------------------------------\n");
    exit(0);
   }
}
void DisplaySensors(){

    u8 UserAnswer ;
    BOOL RepitFlag = FALSE ;
    printf("\n--------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t The system in Displaying Sensors State") ;
    printf("\n--------------------------------------------------------------------------------------------------------------------\n");

 do{
    printf("Enter A to turn off vehicle Engine\n") ;
    printf("Enter B to Set the traffic light color\n") ;
    printf("Enter C to Set Temperature Sensor\n");
    #if  CAR_TYPE ==  WITH_ENGINE_TEMP_CONTROLLER
    printf("Enter D to Set Engine Temperature Sensor \n");
    #endif // CAR_TYPE

    printf("Your answer : ") ;
    scanf(" %c",&UserAnswer) ;

        switch(UserAnswer)
        {
            case 'A' :  SysInit();
                        DisplayStartScreen() ;
                        RepitFlag = FALSE;
                        break ;

            case 'B' :  SetCarSpeed();
                        RepitFlag = FALSE;
                        break;

            case 'C' :  SetRoomTemperatureSensor();
                        RepitFlag = FALSE;
                        break ;

            # if  CAR_TYPE ==  WITH_ENGINE_TEMP_CONTROLLER
            case 'D' :  SetEngTemperatureSensor();
                        RepitFlag = FALSE;
                        break ;
            #endif // CAR_TYPE
        default  : RepitFlag = TRUE ;

    }


    }while(RepitFlag);

}
void SetCarSpeed() {
    u8 SpeedSensor ;
    BOOL RepitFlag = FALSE ;

    printf("\n--------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t The system in Reading speed sensor state") ;
    printf("\n--------------------------------------------------------------------------------------------------------------------\n");

   do{
    printf("G for 100 km/h \n");
    printf("O for 30  km/h \n");
    printf("R for 0   km\n");
    printf("Sensor Read : ") ;
    scanf(" %c",&SpeedSensor) ;

        switch(SpeedSensor) {
            case 'G' : car.CarSpeed = 100 ;
                       RepitFlag = FALSE;
                       break ;

            case 'O' : car.CarSpeed = 30 ;
                       printf("Car AC %s ",(car.CarAC == CLOSED_AC?"is opened":"is already opened") );

                       if (car.CarAC == CLOSED_AC)
                        {
                            car.CarAC = OPENED_AC ;
                            car.CarRoomTemperature= ((5.0/4)*car.CarRoomTemperature) + 1 ;
                        }

                        #if  CAR_TYPE ==  WITH_ENGINE_TEMP_CONTROLLER
                            printf("Car Engine Controller %s , Engine temperature became %.2f\n",(car.EngTempController == CLOSED_TEMPCONTROLLER?"is opened":"is already opened"),((5.0/4)*car.CarRoomTemperature) + 1 );
                            if (car.EngTempController == CLOSED_TEMPCONTROLLER)
                            {
                                car.EngTempController= OPENED_TEMPCONTROLLER;
                                car.CarEngineTemperature= ((5.0/4)*car.CarEngineTemperature) + 1 ;
                            }
                        #endif // CAR_TYPE
                       RepitFlag = FALSE;
                       break ;

            case 'R' : car.CarSpeed = 0 ;
                       RepitFlag = FALSE;
                       break ;

            default  : printf("Please Enter a correct value\n");
                       RepitFlag = TRUE ;
        }
    }while (RepitFlag);

    DisplayStatus();
    DisplaySensors();
}

void SetRoomTemperatureSensor(){
    u8 TempSensor ;
    BOOL RepitFlag = FALSE ;
    printf("\n--------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t The system in Reading Room Temperature sensor state") ;
    printf("\n--------------------------------------------------------------------------------------------------------------------\n");


    printf("Enter Temperature sensor value : ");
    scanf(" %d",&TempSensor);
    if (TempSensor < 10 || TempSensor > 30 )
    {
        car.CarAC=OPENED_AC;
        car.CarRoomTemperature =20 ;
        printf("Car AC is opened ");
    }

    else
    {
        car.CarRoomTemperature = TempSensor ;
        if (car.CarAC==CLOSED_AC)
            printf("Car AC is already closed");

        else
        {
                printf("Car AC is closed");
                car.CarAC = CLOSED_AC ;
        }
    }
    DisplayStatus();
    DisplaySensors();

}


#if  CAR_TYPE ==  WITH_ENGINE_TEMP_CONTROLLER
void SetEngTemperatureSensor(){
u8 TempSensor ;
printf("Reading Engine Temperature value : ");
scanf(" %d",&TempSensor);

    if (TempSensor<100)
    {
        car.CarEngineTemperature = 125 ;
        car.EngTempController = OPENED_TEMPCONTROLLER ;
    }
else if (TempSensor>150)
    {
        car.CarEngineTemperature = 125 ;
        car.EngTempController = OPENED_TEMPCONTROLLER ;
    }

else {
        car.EngTempController = CLOSED_TEMPCONTROLLER ;
        car.CarEngineTemperature = TempSensor ;
     }
    printf("Engine Controller status is %s ",(car.EngTempController ==OPENED_TEMPCONTROLLER?"Closed":"Opened"));
    DisplayStatus();
    DisplaySensors();
}
#endif // CAR_TYPE

void DisplayStatus(){

    printf("\n--------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\tSYSTEM STATUS") ;
    printf("\n--------------------------------------------------------------------------------------------------------------------\n");

    printf("Engine State : %s\n",car.EngineState==OPENED_MOTOR?"ON":"OFF");
    printf("AC State : %s\n",car.CarAC==OPENED_AC?"ON":"OFF");
    printf("Vehicle speed : %d\n",car.CarSpeed);
    printf("Room temperature : %.2f\n",car.CarRoomTemperature);

    #if CAR_TYPE ==  WITH_ENGINE_TEMP_CONTROLLER
    printf("Engine Temperature Controller State : %s\n" ,car.EngTempController==OPENED_TEMPCONTROLLER?"ON":"OFF" );
    printf("Engine Temperature : %.2f \n" , car.CarEngineTemperature);
    #endif // CAR_TYPE

}
