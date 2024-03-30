const int flexPin = 12; 
const int ledPin = 2; 

void setup() { 
  Serial.begin(115200);
  pinMode(ledPin,OUTPUT);
} 

void loop(){ 
  int flexValue;
  flexValue = analogRead(flexPin);
  Serial.println(flexValue);
 
  if(flexValue<500)
     digitalWrite(ledPin,HIGH);
  else
    digitalWrite(ledPin,LOW);
 
  delay(20);
} 