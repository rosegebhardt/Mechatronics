void setup()
{
  DDRD = 255;
  DDRB = 3;
  //Serial.begin(4800);
}

void loop()
{
  unsigned int eger;
  eger = analogRead(A5);
  PORTB = eger >> 8;
  PORTD = eger >> 0;
  Serial.println(eger);
}
