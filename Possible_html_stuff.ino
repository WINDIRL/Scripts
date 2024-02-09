#include "WiFiS3.h"

char ssid[] = "WINDI";    //  your network SSID (name)
char pass[] = "HELPME123"; // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  // attempt to connect to WiFi network
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }

  // you're connected now, so print out the IP address
  Serial.println("Connected to wifi");
  printWiFiStatus();

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            String value = client.readStringUntil('\r');
            if (value != "") {
              // Process the received value (assuming it's an integer)
              int intValue = value.toInt();
              Serial.println("Received value: " + String(intValue));
              // You can store this value to EEPROM or perform any other action here
            }

            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head></head><body>");
            client.println("<h1>Value Received Successfully!</h1>");
            client.println("</body></html>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
