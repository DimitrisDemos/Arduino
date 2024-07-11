#include <WiFi.h>
#include <PubSubClient.h>
#include <stdio.h>
#include<string.h>
#include <LiquidCrystal.h>

#define PIN_RELAY_1  32 // The ESP32 pin GPIO33 connected to the IN1 pin of relay module
#define PIN_RELAY_2  33 // The ESP32 pin GPIO32 connected to the IN2 pin of relay module
 

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
#define pinRs 13
#define pinEn 12
#define pinD4 14
#define pinD5 27
#define pinD6 26
#define pinD7 25
LiquidCrystal lcd(pinRs, pinEn, pinD4, pinD5, pinD6, pinD7);


// WiFi
const char *ssid = "VODAFONE_1278"; // Enter your Wi-Fi name
const char *password = "gk6gbfm97538e2t4";  // Enter Wi-Fi password

// MQTT Broker
const char *mqtt_broker = "Mqtt.motesense.com";
const char *topic = "emqx/esp32";
const char *mqtt_username = "demos";
const char *mqtt_password = "demos1#$";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

byte nuidPICC[4] = {'77', '3d', '61', '9b'};
//void callback(char *topic, byte *payload, unsigned int length);

void setup() {
    // Set software serial baud to 115200;
    //Serial.begin(115200);
    // initialize digital pin as an output.
    pinMode(PIN_RELAY_1, OUTPUT);
    pinMode(PIN_RELAY_2, OUTPUT);
    
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    // Connecting to a WiFi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        lcd.println("Connecting to WiFi..");
    }
    lcd.println("Connected to the Wi-Fi network");
    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
   
    
    while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        lcd.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            lcd.println("Public EMQX MQTT broker connected");
        } else {
            lcd.print("failed with state ");
            lcd.print(client.state());
            delay(2000);
        }
    }

    char msg[50];
    msg[0]='\0';
    array_to_string(nuidPICC,4,msg);


    // Publish and subscribe
    client.publish(topic, msg);
    client.subscribe(topic);

    client.setCallback(callback);
}

void callback(char *topic, byte *payload, unsigned int length) {
    String s = String();
    //lcd.println();
    lcd.print("Message arrived in topic: ");
    lcd.println(topic);
    lcd.print("Message:");
    for (int i = 0; i < length; i++) {
        lcd.print((char) payload[i]);
        s += (char) payload[i];
    }
   // lcd.println();
   // lcd.println("-----------------------");
   // lcd.println(s);
    if (s == "true"){
      lcd.println("Access Granted");
      OpenLock();
    }
    payload[length]='\0';
    s = "";
}

void array_to_string(byte a[],unsigned int len,char buffer[])
{
  for(unsigned int i=0;i<len;i++)
  {
    byte nib1=(a[i]>>4)&0x0F;
    byte nib2=(a[i]>>0)&0x0F;
    buffer[i*2+0]=nib1 < 0x0A ? '0' + nib1 : 'A'+ nib1 - 0x0A;
    buffer[i*2+1]=nib2 < 0x0A ? '0' + nib2 : 'A'+ nib2 - 0x0A;
  }
  buffer[len*2]='\0';
}


void OpenLock(){
  lcd.println("Turn on PIN_RELAY_1");
  digitalWrite(PIN_RELAY_1, HIGH);
  digitalWrite(PIN_RELAY_2, LOW);
  delay(3000);
  lcd.println("Turn on PIN_RELAY_2");
  digitalWrite(PIN_RELAY_1, LOW);
  digitalWrite(PIN_RELAY_2, HIGH);
  delay(3000);
  digitalWrite(PIN_RELAY_2, LOW);
}

void loop() {
    client.loop();
}
