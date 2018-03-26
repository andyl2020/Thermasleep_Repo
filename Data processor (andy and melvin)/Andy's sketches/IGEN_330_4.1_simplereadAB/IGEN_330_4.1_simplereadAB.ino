
  int led = 13;
  
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(led,OUTPUT);
  //pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print("Hi");
  
  if(Serial.available()>0){ //someone types something in and hits enter

    //arduino reads data 
    int data = Serial.read(); 
    
    
    if(data == 'A'){
      digitalWrite(led, HIGH);
      Serial.println("Hi");
      //digitalWrite(LED_BUILTIN, HIGH); 
      delay(2000);
    }
    else
      //digitalWrite(LED_BUILTIN, LOW); 
      digitalWrite(led, LOW);
  }
}
