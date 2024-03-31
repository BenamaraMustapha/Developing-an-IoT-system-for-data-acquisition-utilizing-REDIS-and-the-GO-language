/*
	ESP8266-WS_Clent.ino - 	Esp8266 Websockets Client
	2020, by José Augusto Cintra 
  http://www.josecintra.com/blog

  This is free and unencumbered software released into the public domain.
  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.
  For more information, please refer to <http://unlicense.org/>

	This sketch:
        1. Connects to a WiFi network
        2. Connects to a Websockets server
        3. Periodically sends data from a temperature sensor to the server
        4. Receives return messages from the server
*/

// From library Manager
#include <ArduinoWebsockets.h> 
#include <ESP8266WiFi.h>
#include <neotimer.h>

const char* ssid = "x";  //Enter your SSID
const char* password = "y"; //Enter your Password
const char* websockets_server_host = "192.168.0.0"; //Enter your server adress
const uint16_t websockets_server_port = 8080; // Enter server port

Neotimer mytimer = Neotimer(10000); // Intervalo de tempo para envio dos dados do sensor
String tempString;
String sensor = "TMP|5";
using namespace websockets;

WebsocketsClient client;
void setup() {
    Serial.begin(9600);
    
    // Connect to wifi
    WiFi.begin(ssid, password);

    // Wait some time to connect to wifi
    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        Serial.print(".");
        delay(1000);
    }

    // Check if connected to wifi
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("No Wifi!");
        return;
    }

    Serial.println("Connected to Wifi, Connecting to server.");
    // try to connect to Websockets server
    bool connected = client.connect(websockets_server_host, websockets_server_port, "/");
    if(connected) {
        Serial.println("Connecetd!");
        //client.send("Hello Server");
    } else {
        Serial.println("Not Connected!");
    }
    
    // run callback when messages are received
    client.onMessage([&](WebsocketsMessage message) {
        Serial.print("Got Message: ");
        Serial.println(message.data());
    });
}

void loop() {
  // let the websockets client check for incoming messages
  if(client.available()) {
    client.poll();
  }
  // Periodic sending of temperature sensor data to the customer
  if (mytimer.repeat()) {
    tempString = readTemperature();
    Serial.println(tempString);
    client.send(sensor + "@" +tempString);
  }
}

// Temperature reading and calculation by the thermistor
double readTemperature() {
  // Code extracted from the 'Thermistor Interfacing with NodeMCU' tutorial available at:
  // https://www.electronicwings.com/nodemcu/thermistor-interfacing-with-nodemcu

  const double VCC = 3.3; // NodeMCU on board 3.3v vcc
  const double R2 = 10000; // 10k ohm series resistor
  const double adc_resolution = 1023; // 10-bit adc
  const double A = 0.001129148; // thermistor equation parameters
  const double B = 0.000234125;
  const double C = 0.0000000876741;
  double Vout, Rth, temperature, adc_value;

  adc_value = analogRead(A0);
  Vout = (adc_value * VCC) / adc_resolution;
  Rth = (VCC * R2 / Vout) - R2;

  temperature = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)), 3))));  // Temperature in kelvin
  temperature = temperature - 273.15;  // Temperature in degree celsius
  delay(500);
  return (temperature);

}
