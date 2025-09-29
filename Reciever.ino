#include <WiFi.h>
#include <WiFiUdp.h>

// --- WiFi credentials ---
const char* ssid     = "";   // <-- enter your WiFi SSID
const char* password = "";   // <-- enter your WiFi password

// --- UDP settings ---
WiFiUDP udp;
const int udpPort = 4210;  // must match sender
#define LED_PIN 5          // LED on D5 (GPIO 5)

int expectedSeq = 0;       // expecting DATA-0 first

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Starting Receiver ESP32...");
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nReceiver connected to WiFi");
  Serial.print("Receiver IP: ");
  Serial.println(WiFi.localIP());

  udp.begin(udpPort);
  Serial.println("UDP receiver started");
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char buffer[50];
    int len = udp.read(buffer, 50);
    if (len > 0) buffer[len] = '\0';

    String data = String(buffer);
    data.trim();
    Serial.println("Received: " + data);

    // Check if frame matches expected sequence
    if (data == "DATA-" + String(expectedSeq)) {
      // Toggle LED on D5
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));

      // Send ACK back to sender
      String ack = "ACK-" + String(expectedSeq);
      udp.beginPacket(udp.remoteIP(), udp.remotePort());
      udp.print(ack);
      udp.endPacket();
      Serial.println("Sent: " + ack);

      // Expect next sequence number
      expectedSeq = 1 - expectedSeq;
    } else {
      Serial.println("Unexpected frame, ignored");
    }
  }
}
