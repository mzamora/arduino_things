#include "Adafruit_Sensor.h"
#include "DHT.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "OneWire.h"
#include "DallasTemperature.h"

// Set DHT pin:
#define DHTPIN 2

// Define SDA and SCL pin for LCD:
#define SDAPin A4 // Data pin
#define SCLPin A5 // Clock pin

// Set DHT type, uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

int SensorPin = A0;

// Initialize DHT sensor for normal 16mhz Arduino:
DHT dht = DHT(DHTPIN, DHTTYPE);

OneWire ourWire(4);
DallasTemperature sensors(&ourWire);

// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered):
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); //Change to (0x27,20,4) for 2004 LCD

void setup() {
  // Setup sensor:
  dht.begin();
  sensors.begin();

  // Initiate the LCD:
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Wait a few seconds between measurements:
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  // Read the humidity in %:
  float h = dht.readHumidity();
  // Read the temperature as Celsius:
  float t = dht.readTemperature();
  // Read the temperature as Fahrenheit:
  float f = dht.readTemperature(true);

  // Compute heat index in Fahrenheit (default):
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius:
  float hic = dht.computeHeatIndex(t, h, false);

  // Read the substrate humidity
  int s_h = analogRead(SensorPin);
  s_h = map(s_h,1023,200,0,100);

  // soil temperature
  sensors.requestTemperatures();
  float ts=sensors.getTempCByIndex(0);

  // Print the temperature and the humidity on the LCD:
  lcd.setCursor(0, 0);
  lcd.print("Aire  ");
  lcd.print(t,1);
  lcd.print("\xDF" "C");
  lcd.print(" ");
  lcd.print(h,0);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Suelo ");
  lcd.print(ts,1);
  lcd.print("\xDF" "C ");
  lcd.print(s_h);
  lcd.print("%");
  
  
}
