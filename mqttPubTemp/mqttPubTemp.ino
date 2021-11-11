
// Load library's
#include <ESP8266WiFi.h>
#include <ArduinoMqttClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//home router
const char* ssid     = "Hatter";
const char* password = "Wifi plz?";

// mqqt broker details
const char broker[] = "192.168.0.70";
int        port     = 1883;
const char topic[]  = "tempC";
const char topic2[]  = "tempF";
const char topic3[]  = "tempSensorUptime";

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;     

//interval for sending messages (milliseconds)
const long dataInterval = 1000;
unsigned long previousDataMillis = 0;

//interval for reconnecting (milliseconds)
const long reconnectInterval = 60000;
unsigned long previousReconnectMillis = 0;

//connection state
bool connected = false;

// setup instances
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // connect mqtt broker
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);
  mqttClient.setUsernamePassword("admin","1234");
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }
  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
  connected = true;

  // Start the DS18B20 sensor
  sensors.begin();
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();
  

  unsigned long currentMillis = millis();

  if (currentMillis - previousReconnectMillis >= reconnectInterval){
    previousReconnectMillis = currentMillis;
    if (!mqttClient.connect(broker, port)) {
      Serial.print("MQTT connection failed! Error code = ");
      Serial.println(mqttClient.connectError());
      
      while (1);
    }
    Serial.println("refresh connection");
  }

  if (currentMillis - previousDataMillis >= dataInterval) {
    // save the last time a message was sent
    previousDataMillis = currentMillis;

    //get uptime
    String uptime = timeSinceStart();

    // get temp
    sensors.requestTemperatures(); 
    float temperatureC = sensors.getTempCByIndex(0);
    float temperatureF = sensors.getTempFByIndex(0);

    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.println(temperatureC);

    Serial.print("Sending message to topic: ");
    Serial.println(topic2);
    Serial.println(temperatureF);

    Serial.print("Sending message to topic: ");
    Serial.println(topic3);
    Serial.println(uptime);

    // send message
    mqttClient.beginMessage(topic);
    mqttClient.print(temperatureC);
    mqttClient.endMessage();

    mqttClient.beginMessage(topic2);
    mqttClient.print(temperatureF);
    mqttClient.endMessage();
    
    mqttClient.beginMessage(topic3);
    mqttClient.print(uptime);
    mqttClient.endMessage();
    
    Serial.println();
  }

}
String timeSinceStart()
{
  int times = millis();
  int millisec  = times % 100;
  int tseconds = times/1000; // converts millis to sseconds
  int tminutes = tseconds / 60; // converts total seconds to total
  int seconds = tseconds % 60; 
  int minutes = tminutes % 60;
  int thours = tminutes / 60;
  int hours = thours % 60;
  
  String DisplayTime = "h" + String(hours,DEC) + ": m" + String(minutes,DEC) + ": s" + String(seconds,DEC);

  return DisplayTime;
}
