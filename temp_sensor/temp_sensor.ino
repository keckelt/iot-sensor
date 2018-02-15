
#include <Basecamp.hpp>
#include "DHT.h"


#define DHTPIN 27     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Baud Rate of 115200, just like the uplaod speed I've set here in Arduino IDE (Tools -> Upload Speed)
// DEBUG_PRINTLN = Serial.println => Appends NL & CR 




Basecamp iot;

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(115200);
 
  Serial.println("Setup DHT Temp Sensor");
  dht.begin();

  Serial.println("Setup IoT");
  iot.begin();

  iot.mqtt.onConnect(transmitStatus);

  Serial.println("Setup done");
}

void loop() {
    delay(10*1000);
    
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float f_humidity = 30; //dht.readHumidity();
    float f_temp = dht.readTemperature(); // Read temperature as Celsius (the default)

    
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(f_humidity) || isnan(f_temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Temporary variables
    char celsius[7];
    dtostrf(f_temp, 5, 2, celsius); 
    char humidity[7];
    dtostrf(f_humidity, 5, 2, humidity);

    iot.mqtt.publish("flat/entrance/temp", 1, false, celsius);
    iot.mqtt.publish("flat/entrance/humidity", 1, false, humidity);
    
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%\t");
    Serial.print("Temperature: ");
    Serial.print(celsius);    
    Serial.println("°C");

    delay(50*1000);
}

void transmitStatus(bool sessionPresent) {
    Serial.println("Connected to MQTT broker.");
    //iot.mqtt.publish("flat/entrance/status", 1, false, "alive" );
}
