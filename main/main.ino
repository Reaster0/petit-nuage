#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "./html_page.h"

/* Put your SSID & Password */
const char* ssid = "Petit Nuage☁️";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

#define RAIN_PIN 14
#define LED_PIN 2

bool rainStatus = LOW;

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

void setup() {
	// Serial.begin(115200);
	pinMode(RAIN_PIN, OUTPUT);
	pinMode(LED_PIN, OUTPUT);

	digitalWrite(LED_PIN, LOW);

	WiFi.softAP(ssid, password);
	WiFi.softAPConfig(local_ip, gateway, subnet);
	delay(100);
	
	server.on("/", handle_OnConnect);
	server.on("/status", handle_status);
	server.on("/health", handle_health);
	server.on("/toggle/rain", handle_toggle_rain);
	server.onNotFound(handle_NotFound);
	
	server.begin();
	// Serial.println("HTTP server started");
}

// the loop function runs over and over again forever
void loop() {
	server.handleClient();

	digitalWrite(RAIN_PIN, rainStatus);

	delay(100);
}

void handle_OnConnect() {
//   Serial.println("Get client request");
  server.send(200, "text/html", index_html);
}

void handle_status() {
	// Serial.println("Get client request for status");
	StaticJsonDocument<200> doc;
  	doc["rain"] = rainStatus;
  	String output;
  	serializeJson(doc, output);
  	server.send(200, "application/json", output);
}

void handle_health() {
	// Serial.println("Get client request for health");
	server.send(200, "text/plain", "OK");
}

void handle_toggle_rain() {
	// Serial.println("Get client toggle with rain");
	rainStatus = !rainStatus;
	server.send(200);
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}