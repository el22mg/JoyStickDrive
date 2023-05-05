#include "mbed.h"

#define WAIT_TIME_MS 100 

BufferedSerial pc(USBTX, USBRX, 115200); 

AnalogIn potY(PA_5);
AnalogIn potX(PA_6);
DigitalIn joyButton(PC_10);

DigitalOut led1(LED1);
BusOut leds(PC_0, PC_1, PB_0, PA_4);

float potYval;
float potXval;
int joyButtonVal;
bool running;
int prevState;


void init();
void tryChangeState(int output);


int main()
{
    init();

    while (true)
    {
        potYval = -2*(potY.read() - 0.5);
        potXval = 2*(potX.read() - 0.5);
        joyButtonVal = joyButton.read();

        
        if(joyButtonVal==1){
            led1 =! led1;
        }

        printf("\n\nPotY = %f", potYval);
        printf("\nPotX = %f", potXval);
        printf("\nprevState = %i", prevState);
        printf("\n");

        if(potYval>0.5){ //Forwards
            printf("Test1");
            tryChangeState(4);

        } else if(potYval<-0.5){ //Reverse
            tryChangeState(8);

        } else if(potXval>0.5){ //Clockwise turn
            tryChangeState(2);

        } else if(potXval<-0.5){ //Anticlockwise turn
            tryChangeState(1);

        } else{
            tryChangeState(0);

        }

        thread_sleep_for(WAIT_TIME_MS);
    }
}

void tryChangeState(int output){
    if(prevState!=output){
        if(running){ 
            //Stop buggy from running before acting
            printf("Test2");
            leds = 1;
            thread_sleep_for(60);

        }

        if(output!=0){
            printf("Test3");
            leds = output;
            running = 1;
            prevState = output;

        }else{
            printf("Test4");
            leds = 0;
            running = 0;
            prevState = 0;

        }
    }
}

void init(){
    running = 0;
    prevState = 0;
    joyButton.mode(PullUp);
}