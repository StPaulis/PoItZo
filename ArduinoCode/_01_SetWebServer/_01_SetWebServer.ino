// http://<IP>/arduino/webserver/
#include <Wire.h>
#include <UnoWiFiDevEd.h>

const int VAL_PROBE = 0;
const int MOISTURE_LEVEL = 250;

void setup() {
  Serial.begin(4800);
  Wifi.begin();
  Wifi.println("Web Server is up");
  Serial.println("nEEDSaPP");
}
void loop() {

  while (Wifi.available()) {
    Serial.println("in");
    process(Wifi);    
  }
  delay(1000);

  Serial.println("Humidity");
  Serial.println((analogRead(0) - 1024) * -1> 250);

  if ((analogRead(0) - 1024) * -1> 250) {
    digitalWrite(13, LOW);
     Serial.println("LOW");
  } else   {
    digitalWrite(13, HIGH);
    Serial.println("HIGH");
  }
  delay(1000);
  
}

void process(WifiData client) {
  // read the command
  String command = client.readStringUntil('/');

  if (command == "webserver") {
    WebServer(client);
  }
}
void WebServer(WifiData client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println("Refresh: 20");  // refresh the page automatically every  sec
  client.println();
  client.println("<html>");
  client.println("<head> <title>Needsapp Results</title> </head>");
  client.print("<body>");
  float sensorReading;
  for (int analogChannel = 0; analogChannel < 3; analogChannel++) {
    switch (analogChannel) {
      case 0:
        sensorReading = analogRead(analogChannel);
        client.print("Humidity:  ");

        client.print((sensorReading - 1024) * -1);
        client.print("<br/>");
        break;
      case 1:
        sensorReading = analogRead(analogChannel);
        client.print("Temp:  ");

        client.print(((sensorReading  / 1024.0) * 5000) / 10);
        client.print("c<br/>");
        break;
      case 2:
        sensorReading = analogRead(analogChannel);

        client.print("SoilTemp:  ");
        client.print(((sensorReading  / 1024.0) * 5000) / 10);
        client.print("c<br/>");
        break;
    }
  }

  client.print("</body>");
  client.println("</html>");
  client.print(DELIMITER);

}
