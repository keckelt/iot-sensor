int lastSend;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("millis test");
  lastSend = millis();
}


void loop() {
  // put your main code here, to run repeatedly:
  
  int since = millis() - lastSend;
  if(since > 3000) {
    Serial.println(millis());  
    lastSend = millis();
  }
}
