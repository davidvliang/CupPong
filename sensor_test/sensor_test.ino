void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(6,INPUT);
pinMode(5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int temp = digitalRead(6);
  digitalWrite(5, LOW);

  while(1){
    temp = digitalRead(6);
    if(temp == HIGH){
      Serial.println("Sensor was tripped");  
      digitalWrite(5, HIGH);
      delay(3000);
      digitalWrite(5, LOW);
    }
    else{
       Serial.println("Sensor was not tripped");
    }
  }
}
