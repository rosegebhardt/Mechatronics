unsigned int setpoint = 500;
signed int last_error = 0; 
signed int error_history = 0; 
signed int his = 0;

void setup() {
  
  pinMode(3,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(4,OUTPUT);
  
  cli();
  TCCR0A = B00000010;
  TCCR0B = B00000101;
  TCNT0 = 0;
  OCR0A = 156;
  TIMSK0 = B00000010;
  sei();
}

ISR(TIMER0_COMPA_vect){
  
  unsigned int value, kgain, dgain, igain, pwm, lcv;
  signed int error, derv, response, integral, error_sum;
  unsigned char prop;
  boolean dir;
  float fkgain, fdgain, figain, fprop, fderv, fint, fres;

  value = analogRead(A2);
  igain = analogRead(A3);
  kgain = analogRead(A4);
  dgain = analogRead(A5);

  fkgain = (float)kgain;
  fdgain = (float)dgain;
  figain = (float)igain;

  error = setpoint - value;
  
  fprop = fkgain*(float)error/5;
  
  fderv = (float)(error-last_error);
  
  if(his < 10){
    error_history += error;
    his ++;
  } else{
    his = 0;
    error_history = 0;
  }

  fint = (float)error_history/100;
  fint = fint*figain;
  last_error = error;
  
  if(abs(fprop) < abs(fderv)){
    fderv = fprop;
  }
  
  fres = fprop + fderv + fint;
  
  if(fres<0){
    dir = 0; 
    fres = -fres;
  } else{
    dir = 1;
  }
  
  if(fres > 1023){
    fres = 1023;
  }

  pwm = map((int)fres, 0, 1023, 0, 255);

   digitalWrite(12,dir);
   digitalWrite(4,dir);
   analogWrite(3,pwm);
}

void loop() {
  digitalWrite(9,LOW);
}
