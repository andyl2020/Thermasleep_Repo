
int led = 13; //test led 


//initializes/defines the output pin of the LM335 temperature sensor
int outputPin= 0;
//this sets the ground pin to LOW and the input voltage pin to high
#define upper_limit 20
#define lower_limit 0
#define delay_time 1000

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //check if temperature is not out of bounds 
  safety_check();

  delay(delay_time); //gives enough time for serial input 
  Serial.println("GO");
  delay(delay_time);
  
  if(Serial.available()>0){ //someone types something in and hits enter

    //arduino reads data 
    int data = Serial.read(); 

    //if HOT is received 
    if(data == 'H'){
      digitalWrite(led, HIGH);
      Serial.println("Hot");
      delay(delay_time);
    }

    //if COLD is received 
    else if(data == 'C'){
      digitalWrite(led, LOW);
      Serial.println("Cold");
      delay(delay_time);
    }
    
  }
}


//***************************************************************************************************************************************************************************************************************************
//function for safety testing
void safety_check(){

  int rawvoltage= analogRead(outputPin);
  float millivolts= (rawvoltage/1024.0) * 5000;
  
  float kelvin= (millivolts/10);
  float celsius= kelvin - 273.15;
  float fahrenheit= ((celsius * 9)/5 +32);
  
  //stuck in loop if temp is outside safety range 
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

    //for printing purposes
    delay(delay_time);
 
}
//***************************************************************************************************************************************************************************************************************************
