
#define DEBUG 1
// Baud Rate of 115200, just like the uplaod speed I've set here in Arduino IDE (Tools -> Upload Speed)
// DEBUG_PRINTLN = Serial.println => Appends NL & CR 

#include <Basecamp.hpp>

Basecamp iot;

void setup() {
  iot.begin();

  DEBUG_PRINTLN("Hello World");
  
  iot.mqtt.onConnect(transmitStatus);
  iot.mqtt.onPublish(suspendESP);

  DEBUG_PRINTLN("Setup done");
}

void loop() {
  //DEBUG_PRINTLN("Loopy Loopy");
}

void transmitStatus(bool sessionPresent) {
    DEBUG_PRINTLN("I AM ALIVE");
    iot.mqtt.publish("flat/entrance/status", 1, true, "alive" );
}

void suspendESP(uint16_t packetId) {
  delay(150);
  DEBUG_PRINTLN("Data published");
  delay(5000);
  transmitStatus(true);
}
