//#include <DHT.h>
//#include <DHT_U.h>
//#include <SD.h>

//wifi and firebase -------------------------------------------------------

#include <WiFi.h>
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Redmi Note 10"
#define WIFI_PASSWORD "nassim43"

// Insert Firebase project API Key
#define API_KEY "AIzaSyAy3dN0dAOw8BUvSDTGVvEdtQtRc18wkWw"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://esp32-firebase-7154a-default-rtdb.firebaseio.com"
//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;


//moteur
//const int relay =26;

//dht11
#include "DHT.h"
#define DHTPIN 22 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);




void setup() {
  Serial.begin(115200);
  
  //connect to wifi and firebase   ***************************
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

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
 else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  

  
  //relay pin mode:************************************************
//  pinMode(relay,OUTPUT)



  //dht11***************************************************
  dht.begin();



}

void loop() {
  //dht11
  // Wait a few seconds between measurements.
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  /*if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }*/
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));




  //niveau d eau 
  int val=analogRead(23);
  float eau=(float) 5*val/1023;
  Serial.print("pluie est ");  
  Serial.println(eau);
  
  //humidite de sol
  int humiditeSol = analogRead(24);
  Serial.print("la humidite de sol est ");  
  Serial.println(humiditeSol);

  
  delay(3000);



   //moteur code
   
  //digitalWrite(relay, LOW);//moteur on
  //Serial.println("Current Flowing");
  //delay(5000); 
  //digitalWrite(relay, HIGH);// moyeur off
  //Serial.println("Current not Flowing");
  //delay(5000);

if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setFloat(&fbdo, "test/pluie", 1)){
      Serial.println("PASSED");
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    count++;
    // Write an Float number on the database path test/float
    /*if (Firebase.RTDB.setFloat(&fbdo, "test/humidite", h)){
      Serial.println("PASSED");
     
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }*/

     if (Firebase.RTDB.setInt(&fbdo, "test/humiditeSol", humiditeSol)){
      Serial.println("PASSED");
     
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}
