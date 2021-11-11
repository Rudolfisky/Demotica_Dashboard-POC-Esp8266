
// Load library's
#include <ESP8266WiFi.h>
#include <ArduinoMqttClient.h>


WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

//home router
const char* ssid     = "Hatter";
const char* password = "Wifi plz?";

// mqqt broker details
const char broker[] = "192.168.0.67";
int        port     = 1883;
const char topic[]  = "mytopic";
const char topic2[]  = "othertopic";
const char topic3[]  = "pubmilis";

//set interval for sending messages (milliseconds)
const long interval = 1000;
unsigned long previousMillis = 0;

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

}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;

    //record random value from A0, A1 and A2
    //  int Rvalue = analogRead(A0);
    //  int Rvalue2 = analogRead(A1);
    
    String message1 = "Hello there";
    String message2 = "General Kenobi";
    int message3 = currentMillis;

    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.println(message1);

    Serial.print("Sending message to topic: ");
    Serial.println(topic2);
    Serial.println(message2);

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic);
    mqttClient.print(message1);
    mqttClient.endMessage();

    mqttClient.beginMessage(topic2);
    mqttClient.print(message2);
    mqttClient.endMessage();

    mqttClient.beginMessage(topic3);
    mqttClient.print(message3);
    mqttClient.endMessage();

    Serial.println();
  }

}
