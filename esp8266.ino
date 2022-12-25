#include <ArduinoWiFiServer.h>
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>

#include <SD.h>
#include <Firebase_ESP_Client.h>


#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

#define DATABASE_URL "https://esp32-firebase-7154a-default-rtdb.firebaseio.com"
#define API_KEY "AIzaSyAy3dN0dAOw8BUvSDTGVvEdtQtRc18wkWw"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;





#define WIFI_SSID "Redmi Note 10"
#define WIFI_PASSWORD "nassim43"

#include <SoftwareSerial.h>

SoftwareSerial espSerial(3, 2); // RX , TX  de la carte esp8266



void setup() {
  
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
config.api_key = API_KEY;
config.database_url = DATABASE_URL;


  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
   boolean  signupOK = true;
  }
 else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  

  // put your setup code here, to run once:
Serial.begin(115200);
espSerial.begin(115200);
delay(2000);

}

void loop() {

  
 int pluie;
  // put your mFirebase.getFloat("number");
      Firebase.RTDB.getInt(&fbdo, "/test/pluie"); 

      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      Serial.print("pluie ");
      Serial.println(fbdo.to<int>());
      espSerial.write(fbdo.to<int>());
      }
  
//espSerial.write(x);
delay(1000);

    
}
