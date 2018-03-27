//initializes/defines the output pin of the LM335 temperature sensor
int outputPin= 0;
//this sets the ground pin to LOW and the input voltage pin to high
void setup()
{
Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT);
}

//main loop
void loop()
{  
safety_check();
}


void safety_check(){
  int delay_time = 1000;
  int rawvoltage= analogRead(outputPin);
  float millivolts= (rawvoltage/1024.0) * 5000;
  
  float kelvin= (millivolts/10);
  float celsius= kelvin - 273.15;
  float fahrenheit= ((celsius * 9)/5 +32);
  
  int upper_limit = 20;
  int lower_limit = 0;


    
  while (celsius> upper_limit || celsius < lower_limit){
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("This is the current temperature in Celsius:   ");
    Serial.print(celsius);
    Serial.print("        Too Hot Bro");
    Serial.print("    Not exiting until safe\n");
    delay(delay_time);
    
    rawvoltage= analogRead(outputPin);
    millivolts= (rawvoltage/1024.0) * 5000;
    kelvin= (millivolts/10);
    celsius= kelvin - 273.15;
    
  }
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("This is the current temperature in Celsius:   ");
    Serial.print(celsius);
    Serial.print("        ");   
    Serial.print("All good bro\n");
    
    delay(delay_time);

 
}


