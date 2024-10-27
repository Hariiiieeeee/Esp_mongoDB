#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "chittuKuruvi";         // Replace with your Wi-Fi SSID
const char* password = "1234hari"; // Replace with your Wi-Fi password

const char* serverName = "http://192.168.1.39:5000/addData"; // Replace with your local machine's IP

WiFiClient wifiClient; // Create a WiFiClient object

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Connect to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Specify request destination using the new API
    http.begin(wifiClient, serverName);
    http.addHeader("Content-Type", "application/json");

    // Create JSON string with your sensor data
    String jsonData = "{\"temperature\": 25.6, \"humidity\": 60}";

    // Send the request
    int httpResponseCode = http.POST(jsonData);

    // Check the response code
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    // End the connection
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }

  delay(60000); // Send data every 60 seconds
}
