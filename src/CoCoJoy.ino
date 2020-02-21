// Program used to test CoCo3 joystick
//------------------------------------------------------------

#include <Joystick.h>



Joystick_ Joystick[1] = {
  Joystick_(0x01,
            JOYSTICK_TYPE_JOYSTICK ,
            1, //Button Count
            0, //Hat count
            true,true,false,   //X and Y, but no Z
            false,false,false, // No Rx, Ry, or Rz
            false,false,       // No rudder or throttle
            false,false,false) // No accelerator, brake, or steering

};

// Set to true to test "Auto Send" mode or false to test "Manual Send" mode.
const bool testAutoSendMode = true;
//const bool testAutoSendMode = false;

int x,y,old_x,old_y;
boolean button,old_button;
boolean send = false;

#define MIN_X 0
#define MAX_X 65535
#define MIN_Y 0
#define MAX_Y 65535





unsigned int smoothRead(unsigned char analogPort)
{
  const int numReadings = 10;

  int total = 0;                  // the running total
  int average = 0;                // the average

 for (int i=0 ; i< numReadings; i++)
 {
  total = total + analogRead(analogPort);
  delay(1);
 }


  average = total / numReadings;
  delay(1);
  return(average);

}
void setup() {

    Joystick[0].setXAxisRange(MIN_X, MAX_X);
    Joystick[0].setYAxisRange(MIN_Y, MAX_Y);

    if (testAutoSendMode)
    {
      Joystick[0].begin();
    }
    else
    {
      Joystick[0].begin(false);
    }


  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  delay(1000);
}

void loop() {


  x=map(smoothRead(A2),0,1023,MIN_X,MAX_X);
  y=map(smoothRead(A1),0,1023,MIN_Y,MAX_Y);
  button = !digitalRead(10);

  Joystick[0].setXAxis(x);
  Joystick[0].setYAxis(y);

  if(button){
    Joystick[0].pressButton(0);
  }
  else {
    Joystick[0].releaseButton(0);
  }

  if ((x !=old_x) || y!=old_y || button != old_button)
  {
    send=true;
    old_x=x;
    old_y=y;
    old_button=button;
  }

  if (testAutoSendMode == false && send)
  {
    Joystick[0].sendState();
    send=false;
  }
}
