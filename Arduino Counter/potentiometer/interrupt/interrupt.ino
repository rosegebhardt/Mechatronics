void setup(){
  pinMode(3,OUTPUT);
  pinMode(7,OUTPUT);
  cli();

  TCCR0A = B00000010;
  TCCR0B = B00000101;   // prescalar = 1024
  TCNT0 = 0;

  OCR0A = 156.25;       // 16E6/(100*1024) = 156.25
  TIMSK0 = B00000010;

  sei();
}

ISR(TIMER0_COMPA_vect){
  unsigned int threshold, value, error, gain;
  unsigned char prop;
  boolean dir;
  
  threshold = analogRead(A0);
  value = analogRead(A1);
  
  if (value == threshold){
    dir = 1;
    error = 0;
    digitalWrite(7,HIGH);
  } else if (value < threshold){
    dir = 1;
    error = threshold - value;
    digitalWrite(7,HIGH);
  } else{
    dir = 0;
    error = value - threshold;
    digitalWrite(7,LOW);
  }
  
  prop = map(error,0,1023,0,255);
  analogWrite(3,prop);
}

void loop(){
}
