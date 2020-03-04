#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define MAX_ANALOG_VALUE 1024.0

/*
 * A0 - Potmeter temperature
 * A1 - Potmeter humidity
 * A4 - I2C for LCD
 * A5 - I2C for LCD
 * D2 - DHT top of chamber
 * D3 - DHT bottom of chamber
 * D9 - Heater on/off
 * D10 - Humidity on/off
 * D11 - Fan on/off
 * 
 * The DHT at the top is used to check the temperature,
 * the DHT at the bottom is used to control the fan.
 */

// The Degree symbol
byte degree[8] = {
  // shape of the degree symbol
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};

DHT dht_high(2, DHT22);
DHT dht_low(3, DHT22);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

void setup() {
  // The LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Initializing...");
  
  // The two potmeters are analog inputs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  // The heater, humidity and fan are outputs
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);

  // The two temperature sensors
  dht_high.begin();
  dht_low.begin();

  // Now wait. No idea why, but why not
  delay(3000);

  // Show the basic layout in the LCD
  lcd.createChar(1, degree);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Proofing");
  lcd.setCursor(0,1);
  lcd.print("         Temp   Hum");
  lcd.setCursor(0, 2);
  lcd.print("Target:");
  lcd.setCursor(0, 3);
  lcd.print("Current:");
}

float hum_set = 0;
float temp_set = 0;
float hum_low = 0;
float hum_high = 0;
float temp_low = 0;
float temp_high = 0;

unsigned long humidity_last_time = 0;

// Check the values below with isnan(float)

void loop() {
  /*
   * Reading the new values set with the control knobs
   */
  // Convert temperature to a range between 20-35 deg
  temp_set = 20.0 + (float)analogRead(A0) / (MAX_ANALOG_VALUE/15.0);
  // Convert humidity to a range between 20-100%
  hum_set = 20.0 + (float)analogRead(A1) / (MAX_ANALOG_VALUE/80.0);

  /*
   * Reading the values of the top and bottom DHTs
   */
  hum_low = dht_low.readHumidity();
  temp_low = dht_low.readHumidity();
  hum_high = dht_high.readHumidity();
  temp_high = dht_high.readHumidity();

  /*
   * We have measured everything we need to measure.
   * Now set stuff
   */

  // If top temperature is too low, enable heater
  if(temp_high < temp_set)
    digitalWrite(9, HIGH);
  else
    digitalWrite(9, LOW);

  // If the humidity is too low, enable atomizer
  // But for 1 second, and only every 20 seconds
  if(hum_high < hum_set) {
    if(millis() - humidity_last_time > 20000) {
      // It's already 20 seconds ago, so turn it on
      digitalWrite(10, HIGH);
      humidity_last_time = millis();
    } else if(millis() - humidity_last_time > 2000) {
      // Turned it on 2 seconds ago, now turn it off
      digitalWrite(10, LOW);
    } else {
      // In any other case, probably error, so turn it off anyway
      digitalWrite(10, LOW);
    }
  } else {
    // Turn it off no matter what
    digitalWrite(10, LOW);
  }

  // If heater or atomizer is on, or if the difference
  // between the top and bottom DHTs is too large,
  // enable the fan
  if(digitalRead(9) || digitalRead(10) || abs(hum_high-hum_low) > 5 || abs(temp_high-temp_low) > 1.0)
    digitalWrite(11, HIGH);
  else
    digitalWrite(11, LOW);

  /*
   * Update the LCD with the current values
   */

  // Write the current elapsed time (accuracy of internal clock)
  lcd.setCursor(12,0);
  int curtime = millis() / 1000;
  int hours = curtime / 3600;
  int minutes = (curtime - hours*3600) / 60;
  int seconds = curtime - hours*3600 - minutes*60;

  if(hours < 10)
    lcd.print("0");
  lcd.print(hours);
  lcd.print(":");
  if(minutes < 10)
    lcd.print("0");
  lcd.print(minutes);
  if(seconds < 10)
    lcd.print("0");
  lcd.print(seconds);

  // Write the target values
  lcd.setCursor(9,2);
  lcd.print(temp_set, 1);
  lcd.write(1);
  lcd.print("C ");
  lcd.setCursor(16,2);
  lcd.print(hum_set, 0);
  lcd.print("% ");

  // Write the current values
  lcd.setCursor(9,2);
  lcd.print(temp_high, 1);
  lcd.write(1);
  lcd.print("C ");
  lcd.setCursor(16,2);
  lcd.print(hum_high, 0);
  lcd.print("% ");
}
