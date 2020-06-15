#include <PID_v1.h>

#define PIN_INPUT A2
#define PIN_OUTPUT 12

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

void setup()
{
  //initialize the variables we're linked to
  Input = analogRead(PIN_INPUT);
  Setpoint = 500;

  //turn the PID on
  //myPID.SetMode(AUTOMATIC);
}

void loop()
{
  unsigned int ki,kp,kd;
  double Kp,Kd,Ki;
  
  ki = analogRead(A3);
  kp = analogRead(A4);
  kd = analogRead(A5);

  Kp = (double)kp;
  Kd = (double)kd;
  Ki = (double)ki;

  //Specify the links and initial tuning parameters
  PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
  myPID.SetMode(AUTOMATIC);
  
  Input = analogRead(PIN_INPUT);
  myPID.Compute();
  analogWrite(PIN_OUTPUT, Output);
}
