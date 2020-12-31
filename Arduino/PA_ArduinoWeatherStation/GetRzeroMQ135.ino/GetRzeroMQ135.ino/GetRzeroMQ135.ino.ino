#include <MQ135.h>
#include <virtuabotixRTC.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>

#define RLOAD 1000
#define RZERO 23.32

MQ135 gasSensor = MQ135(A0); 
int val; 
int sensorPin = A0; 
int sensorValue = 0; 
LiquidCrystal_I2C lcd(0x27,20,4);
virtuabotixRTC myRTC(4,5,6);
const int chipSelect = 53;
String waktu;
String tanggal;
float zero;
float ppm;

void setup() {
  lcd.init();                       
  lcd.backlight();
  lcd.print("");
  myRTC.updateTime();
  Initialize_SDcard(); 
  Serial.begin(115200);
  pinMode(sensorPin, INPUT); 
} 
  
void loop() {
  myRTC.updateTime();
  /*Deskripsi Waktu*/
  waktu = String(myRTC.hours)+ ":" + String(myRTC.minutes);
  /*Deskripsi Tanggal*/
  tanggal = String(myRTC.dayofmonth) + "/" + 
  (myRTC.month) + "/" + (myRTC.year);
  
  
  Serial.println(waktu);
  Serial.println(tanggal); 
  val = analogRead(A0); 
  Serial.print ("raw = "); 
  Serial.println (val); 
  zero = gasSensor.getRZero(); 
  Serial.print ("rzero: "); 
  Serial.println (zero); 
  ppm = gasSensor.getPPM(); 
  Serial.print ("ppm: "); 
  Serial.println (ppm);

  
  //Menampilkan LCD
  /*AtasKiri*/
  lcd.setCursor(0, 0);
  lcd.print(zero);
  lcd.print(" rzero");
  /*BawahKiri*/  
  lcd.setCursor(0, 1);
  lcd.print(ppm);
  lcd.print("ppm");
  /*BawahKanan*/
  lcd.setCursor(11,1);
  lcd.print(waktu);

  delay(2000);

  //Menulis Log ke SDCard
  Write_SDcard();

} 

void Initialize_SDcard(){           //KelasKodeCekSDCard
  //Mengecek SD Card
  if (!SD.begin(chipSelect)) {
    Serial.println("Tidak ada kartu memori!");
    return;
  }
  
  //Membuat File Log
  Serial.println("Membuat file log.txt...");
  File dataFile = SD.open("Rzero.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println
    ("tanggal,waktu,zero,ppm");
    dataFile.close();
  }
}

void Write_SDcard()                 //KelasKodeTulisSDCard
{
  //Membuka file log
  File dataFile = SD.open("Rzero.txt", FILE_WRITE);

  //Menulis log
  if (dataFile) {
    dataFile.print(tanggal); 
    dataFile.print(","); 

    dataFile.print(waktu); 
    dataFile.print(","); 

    dataFile.print(zero); 
    dataFile.print(","); 

    dataFile.print(ppm); 
    dataFile.print(","); 

    dataFile.println(); 
    dataFile.close();

    delayMenit();
  }
  else
  Serial.println("Penulisan file gagal!");
}

void delayMenit()
{
  for(int count = 0; count < 60 ; count++)
  {
  delay(1000);
  }
}
