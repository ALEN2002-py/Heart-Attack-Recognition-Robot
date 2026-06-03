#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include "ESP8266_AT.h"
/* Select Demo */
//#define RECEIVE_DEMO			/* Define RECEIVE demo */
#define SEND_DEMO			/* Define SEND demo */
/* Define Required fields shown below */
#define DOMAIN          "api.thingspeak.com"
#define PORT            "80"
#define API_WRITE_KEY   "Write your Write Key here"
#define CHANNEL_ID      "Write your Channel ID here"
#define SSID            "Write your WIFI SSID here"
#define PASSWORD        "Write your WIFI Password here"
char _buffer[150];
uint8_t Connect_Status;
#ifdef SEND_DEMO
uint8_t Sample = 0;
#endif
int const PULSE_SENSOR_PIN = A1;   // 'S' Signal pin connected to A0
int Signal;                // Store incoming ADC data. Value can range from 0-1024
int Threshold = 550;       // Determine which Signal to "count as a beat" and which to ignore.
void setup() {
//ecg sensor
Serial.begin(9600);
pinMode(10, INPUT); // Setup for leads off detection LO +
pinMode(11, INPUT); // Setup for leads off detection LO -
//pulse sensor
pinMode(LED_BUILTIN,OUTPUT);  // Built-in LED will blink to your heartbeat
//mlx90614
Serial.println("Adafruit MLX90614 test");  
mlx.begin();  
//wifi module
while(!ESP8266_Begin());
    ESP8266_WIFIMode(BOTH_STATION_AND_ACCESPOINT);	/* 3 = Both (AP and STA) */
    ESP8266_ConnectionMode(SINGLE);     			/* 0 = Single; 1 = Multi */
    ESP8266_ApplicationMode(NORMAL);    			/* 0 = Normal Mode; 1 = Transperant Mode */
    if(ESP8266_connected() == ESP8266_NOT_CONNECTED_TO_AP)/*Check WIFI connection*/
    ESP8266_JoinAccessPoint(SSID, PASSWORD);		/*Connect to WIFI*/
    ESP8266_Start(0, DOMAIN, PORT);	
}
 
void loop() {
  Connect_Status = ESP8266_connected();
    if(Connect_Status == ESP8266_NOT_CONNECTED_TO_AP)	/*Again check connection to WIFI*/
    ESP8266_JoinAccessPoint(SSID, PASSWORD);		/*Connect to WIFI*/
    if(Connect_Status == ESP8266_TRANSMISSION_DISCONNECTED)
    ESP8266_Start(0, DOMAIN, PORT);			/*Connect to TCP port*/

    #ifdef SEND_DEMO
    memset(_buffer, 0, 150);
    sprintf(_buffer, "GET /update?api_key=%s&field1=%d", API_WRITE_KEY, Sample++); 	/*connect to thingspeak server to post data using your API_WRITE_KEY*/
    ESP8266_Send(_buffer);
    delay(15000); 					/* Thingspeak server delay */
    #endif
    
    #ifdef RECEIVE_DEMO
    memset(_buffer, 0, 150);
    sprintf(_buffer, "GET /channels/%s/feeds/last.txt", CHANNEL_ID); /*Connect to thingspeak server to get data using your channel ID*/
    ESP8266_Send(_buffer);
    Read_Data(_buffer);
    delay(600);
    #endif
  Serial.println("===================================Welcome to the heart attack detection system=======================-");
  Serial.println("Enter any of the following choices: ");
  int c;
  while(1){
    Serial.println("1. Lets analyse Electrocardiogram graph of your heart:");
    Serial.println("2. Beats per minute of your heart:");
    Serial.println("3.Check your Body temperature:");
    scanf("%d",c);
    switch(c){
      case 1://ecg sensor
            if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
              Serial.println('!');
            }
            else{
              // send the value of analog input 0:
              Serial.println(analogRead(A0));
            }
            //Wait for a bit to keep serial data from saturating
            delay(1);
            break;
//pulse sensor
      case 2:
            Signal = analogRead(PULSE_SENSOR_PIN); // Read the sensor value
          	Serial.println(Signal);                // Send the signal value to serial plotter
            if(Signal > Threshold){                // If the signal is above threshold, turn on the LED
		          digitalWrite(LED_BUILTIN,HIGH);
          	} 
            else{
		            digitalWrite(LED_BUILTIN,LOW);     // Else turn off the LED
	          }
	          delay(10);
            break;
  //mlx90614
      case 3:
            Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
            Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
            Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
            Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
            Serial.println();
            delay(500);
            break;
      default:
            Serial.println("Please select any one othe choice");
            break;
    }
  }

}
