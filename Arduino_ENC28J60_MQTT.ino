#include <SPI.h>
#include <EthernetENC.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 178, 200);
IPAddress server(192, 168, 178, 84);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

EthernetClient ethClient;
PubSubClient client(ethClient);

void warningBlink() {
  for (int i=0;i<5;i++) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(500);                       // wait for a second
  }
}

void reconnect() {
  // Loop until we're reconnected
  Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("asgard/deurcontroller","ON");
      // ... and resubscribe
      client.subscribe("asgard/deurbel");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      warningBlink();
    }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(57600);
  Ethernet.init(8);

  client.setServer("192.168.178.84", 1883);
  client.setCallback(callback);

  Ethernet.begin(mac, ip);

  // Allow the hardware to sort itself out
  delay(1500);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
