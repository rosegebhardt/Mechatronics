byte counter = 0;

void setup()
{
  for(int h=0;h<8;h++){
    pinMode((h+2), OUTPUT);
  }
}

void loop()
{
  for(int i=0; i<8; i++){
    
    int power_ip0 = 1;
    int power_ip1 = 1;
    
    for(int j=0; j<i; j++){
      power_ip0 = 2*power_ip0;
    }
    for(int k=0; k<(i+1); k++){
      power_ip1 = 2*power_ip1;
    }
    
    if((counter%power_ip1)<power_ip0){
      digitalWrite((i+2),LOW);
    }
    else{
      digitalWrite((i+2),HIGH);
    }
  }
  delay(200); 
  counter = counter+1;
}
