#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <DHT.h>

// ---------------- WIFI ----------------
#define WIFI_SSID "PGS@IOT"
#define WIFI_PASSWORD "presidential@IOT"

// ---------------- FIREBASE ----------------
#define FIREBASE_HOST "https://ttx22p-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_SECRET "Lxsxse8BbIRLeJB2zF780ahMNvxKj9rNwcEpV8Ap"

// ---------------- DHT11 ----------------
#define DHTPIN D4        // GPIO2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// ---------------- FIREBASE OBJECTS ----------------
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// ---------------- TIMERS ----------------
unsigned long sendDataPrevMillis = 0;
unsigned long printPrevMillis = 0;

const long sendInterval = 5000;   // Send every 5 seconds
const long printInterval = 5000;  // Print every 5 seconds

float temperature = 0;
float humidity = 0;

void setup() {

  Serial.begin(115200);
  delay(2000);

  Serial.println("\n--- NodeMCU DHT11 + Firebase REAL DATA ---");

  // Start DHT sensor
  dht.begin();

  // Connect WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected! IP: " + WiFi.localIP().toString());

  // Firebase config
  config.database_url = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_SECRET;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  if (Firebase.ready()) {
    Serial.println("Firebase connected (legacy mode)");
  } else {
    Serial.println("Firebase init failed - check secret / URL / rules");
  }
}

void loop() {

  unsigned long currentMillis = millis();

  // ---------- READ SENSOR ----------
  if (currentMillis - printPrevMillis >= printInterval) {

    printPrevMillis = currentMillis;

    temperature = dht.readTemperature(); // °C
    humidity = dht.readHumidity();       // %

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("❌ Failed to read from DHT11!");
      return;
    }

    Serial.println("--- SENSOR DATA ---");
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
    Serial.print("Humidity   : "); Serial.print(humidity); Serial.println(" %");
    Serial.println("------------------");
  }

  // ---------- SEND TO FIREBASE ----------
  if (Firebase.ready() && (currentMillis - sendDataPrevMillis >= sendInterval)) {

    sendDataPrevMillis = currentMillis;

    String path = "/sensor/staticTest";

    Serial.println("Sending data to Firebase...");

    if (Firebase.RTDB.setFloat(&fbdo, path + "/temperature", temperature)) {
      Serial.println("✔ Temperature sent");
    } else {
      Serial.println("✖ Temp failed: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, path + "/humidity", humidity)) {
      Serial.println("✔ Humidity sent");
    } else {
      Serial.println("✖ Humidity failed: " + fbdo.errorReason());
    }

    Firebase.RTDB.setString(&fbdo, path + "/lastUpdate",
                            "Millis: " + String(currentMillis));

    Serial.println("✔ Firebase upload complete\n");
  }
}
