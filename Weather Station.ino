#include <DHT.h>
#include <SoftwareSerial.h>

// Define sensor pins
#define DHTPIN 2      
#define DHTTYPE DHT11 
#define QT135_AO A0   
#define QT135_DO 3    
#define LDRPIN A1     

// Define Bluetooth module pins
#define BT_TX 10  
#define BT_RX 11  

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Initialize SoftwareSerial for Bluetooth
SoftwareSerial BTSerial(BT_TX, BT_RX);

void setup() {
    Serial.begin(9600);  
    BTSerial.begin(9600); 
    
    dht.begin();
    pinMode(QT135_DO, INPUT);
}

void loop() {
    // Read DHT11 Data
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Read Air Quality
    int airQualityAnalog = analogRead(QT135_AO);
    int airQualityDigital = digitalRead(QT135_DO);
    int AQI = (airQualityAnalog * 500) / 1023; 

    // Read LDR and convert to percentage
    int ldrRaw = analogRead(LDRPIN);
    int lightPercentage = ((ldrRaw / 1023.0)) * 100;

    // Determine AQI category
    String AQIStatus;
    if (AQI <= 50) AQIStatus = "Good";
    else if (AQI <= 100) AQIStatus = "Moderate";
    else if (AQI <= 150) AQIStatus = "Unhealthy (Sensitive)";
    else if (AQI <= 200) AQIStatus = "Unhealthy";
    else if (AQI <= 300) AQIStatus = "Very Unhealthy";
    else AQIStatus = "Hazardous";

    // Send formatted data to Serial Bluetooth Terminal
    BTSerial.println("===========================");
    BTSerial.println(" Sensor Data Update:");
    BTSerial.println(" Temperature: " + String(temperature) + "°C");
    BTSerial.println(" Humidity: " + String(humidity) + "%");
    BTSerial.println(" AQI: " + String(AQI) + " (" + AQIStatus + ")");
    BTSerial.println(" Light: " + String(lightPercentage) + "%");
    BTSerial.println("===========================\n");

    // Debug on Serial Monitor (for Arduino IDE)
    Serial.println("===========================");
    Serial.println(" Sensor Data Update:");
    Serial.println(" Temperature: " + String(temperature) + "°C");
    Serial.println(" Humidity: " + String(humidity) + "%");
    Serial.println(" AQI: " + String(AQI) + " (" + AQIStatus + ")");
    Serial.println(" Light: " + String(lightPercentage) + "%");
    Serial.println("===========================\n");

    // Wait for 1 second before next reading
    delay(5000);
}
