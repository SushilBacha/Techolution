#include <WiFi.h>
#include <EEPROM.h>
#include <SPI.h>
#include <PubSubClient.h>


#define ssid "Your SSID"
#define password "Your Wifi Password"
#define USE_SERIAL Serial
const char* mqtt_server = "broker.mqttdashboard.com";

//A0 of NodeMCU is connected to Analog pin of MQ-02
int Buzzer = 32;        // used for ESP32
int Gas_analog = A0;    // used for ESP32
int Gas_digital = 2;   // used for ESP32

WiFiClient espClient;
PubSubClient client(espClient);


void setup( )
{
Serial.begin(115200);
pinMode(Buzzer, OUTPUT);      
pinMode(Gas_digital, INPUT);
 Serial.begin(115200);
 setup_wifi();
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
 reconnect();
}



void setup_wifi()
{

delay(10);

Serial.print("connecting to");
 Serial.println(ssid);
 WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED)
 {
 delay(500);
 Serial.print("-");
 }

Serial.println();
 Serial.println("WiFi Connected");
 Serial.println("WiFi got IP");
 Serial.println();
 Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length)
{

Serial.print("Message arrived : ");
 Serial.print(topic);
 Serial.print(" : ");
 for (int i = 0; i < length; i++)
 {
 Serial.println((char)payload[i]);
 }
 if ((char)payload[0] == 'o' && (char)payload[1] == 'n')
 {
 digitalWrite(2, LOW);
 }
 else if ((char)payload[0] == 'o' && (char)payload[1] == 'f' && (char)payload[2] == 'f' ) {
 digitalWrite(2, HIGH);
 }

}

void reconnect()
{

while(!client.connected()){
Serial.println("Attempting MQTT connection");
if(client.connect("...HiveMQ clientId..."))
{
Serial.println("Connected");
client.publish("...Your_topic_to_read_temp...","Connected!");
client.subscribe("...Your_topic_to_control_led...");
Serial.print("subscribed!");
}
else
{
Serial.print("Failed, rc = ");
Serial.print(client.state());
Serial.println("Waiting for 5 seconds to try again");
delay(5000);
 }
 }
}

void loop()
{

if(!client.connected())
{
reconnect();
Serial.print("disconnected");
}
int gassensorAnalog = analogRead(Gas_analog);
  int gassensorDigital = digitalRead(Gas_digital);
  // Analog read for reading any analog input.
  Serial.print (gassensorAnalog);
  // Here, we print the value read through the serial monitor.
  Serial.println (" ");
  delay(100);
    if (gassensorAnalog > 1000) {
    Serial.println("Gas");
    digitalWrite (Buzzer, HIGH) ; //send tone
    delay(1000);
    digitalWrite (Buzzer, LOW) ;  //no tone
    client.publish("...Your_topic_to_read_temp...", gassensorAnalog);

  }
delay(1000);
client.loop();
}
