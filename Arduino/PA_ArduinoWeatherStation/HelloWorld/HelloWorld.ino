#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 3
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Suhu  Kelembapan");
}


void loop()
{
  lcd.setCursor(0, 1);
  float k = dht.readHumidity();
  float s = dht.readTemperature();

  
  lcd.print(s);
  lcd.setCursor(8,1);
  lcd.print(k);

  delay(2000);
}
