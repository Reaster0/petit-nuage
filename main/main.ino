#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "./html_page.h"

/* Put your SSID & Password */
const char* ssid = "Petit Nuage☁️";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

#define RAIN_PIN 14
#define ORAGE_PIN 12
#define LED_PIN 2

bool rainStatus = LOW;
bool orageStatus = LOW;
bool ledStatus = HIGH;


/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

void setup() {
	Serial.begin(115200);
	pinMode(RAIN_PIN, OUTPUT);
	pinMode(ORAGE_PIN, OUTPUT);
	pinMode(LED_PIN, OUTPUT);

	WiFi.softAP(ssid, password);
	WiFi.softAPConfig(local_ip, gateway, subnet);
	delay(100);
	
	server.on("/", handle_OnConnect);
	server.on("/status", handle_status);
	server.on("/toggle/rain", handle_toggle_rain);
	server.on("/toggle/orage", handle_toggle_orage);
	server.on("/toggle/led", handle_toggle_led);
	server.onNotFound(handle_NotFound);
	
	server.begin();
	Serial.println("HTTP server started");
}

// the loop function runs over and over again forever
void loop() {
	server.handleClient();

	digitalWrite(RAIN_PIN, rainStatus);
	digitalWrite(ORAGE_PIN, orageStatus);
	digitalWrite(LED_PIN, ledStatus);

	delay(100);
}

void handle_OnConnect() {
  Serial.println("Get client request");
  server.send(200, "text/html", index_html);
}

void handle_status() {
	Serial.println("Get client request for status");
	StaticJsonDocument<200> doc;
  	doc["rain"] = rainStatus;
  	doc["orage"] = orageStatus;
  	doc["led"] = !ledStatus; // the main led is inverted
  	String output;
  	serializeJson(doc, output);
  	server.send(200, "application/json", output);
}

void handle_toggle_rain() {
	Serial.println("Get client toggle with rain");
	rainStatus = !rainStatus;
	server.send(200);
}

void handle_toggle_orage() {
	Serial.println("Get client toggle with orage");
	orageStatus = !orageStatus;
	server.send(200);
}

void handle_toggle_led() {
	Serial.println("Get client toggle with led");
	ledStatus = !ledStatus;
	server.send(200);
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}