#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define MAX_ANALOG_VALUE 1024.0

/*
 * A4 - I2C for LCD
 * A5 - I2C for LCD
 * D2 - DHT top of chamber
 * D3 - DHT bottom of chamber
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
  lcd.print("Top:");
  lcd.setCursor(0, 3);
  lcd.print("Bottom:");
}

float hum_low = 0;
float hum_high = 0;
float temp_low = 0;
float temp_high = 0;

// Check the values below with isnan(float)

void loop() {
  /*
   * Reading the values of the top and bottom DHTs
   */
  hum_low = dht_low.readHumidity();
  temp_low = dht_low.readHumidity();
  hum_high = dht_high.readHumidity();
  temp_high = dht_high.readHumidity();

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

  // Write the high DHT22 values
  lcd.setCursor(9,2);
  lcd.print(temp_high, 1);
  lcd.write(1);
  lcd.print("C ");
  lcd.setCursor(16,2);
  lcd.print(hum_high, 0);
  lcd.print("% ");

  // Write the low DHT22 values
  lcd.setCursor(9,2);
  lcd.print(temp_low, 1);
  lcd.write(1);
  lcd.print("C ");
  lcd.setCursor(16,2);
  lcd.print(hum_low, 0);
  lcd.print("% ");
}
