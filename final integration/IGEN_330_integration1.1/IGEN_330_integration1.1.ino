
int led = 13; //test led 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()>0){ //someone types something in and hits enter

    //arduino reads data 
    int data = Serial.read(); 

    //if HOT is received 
    if(data == 'H'){
      digitalWrite(led, HIGH);
      Serial.println("H");
      delay(2000);
    }

    //if COLD is received 
    else if(data == 'C'){
      digitalWrite(led, LOW);
      Serial.println("C");
      delay(2000);
    }
    
  }
}
