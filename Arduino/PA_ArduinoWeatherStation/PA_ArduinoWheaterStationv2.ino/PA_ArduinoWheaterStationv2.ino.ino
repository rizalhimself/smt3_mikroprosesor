//Library Digunakan
#include <DHT.h>
#include <virtuabotixRTC.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <MQ135.h>


//Deklarasi Hardware
/*Koneksi*/
#define DHTPIN 3
#define DHTTYPE DHT11
#define DEBUG true
/*Tipe*/
SoftwareSerial esp8266(10,11);
LiquidCrystal_I2C lcd(0x27,20,4); 
DHT dht(DHTPIN, DHTTYPE);
virtuabotixRTC myRTC(4,5,6);
const int chipSelect = 53;
MQ135 gasSensor = MQ135(A0);
/*Konfigurasi Password AP untuk koneksi ke internet*/
#define SSID "RizalNet"
#define PASS "blackbird"
/*Konfigurasi Thingspeak*/
#define IP "api.thingspeak.com" //IP Thingspeak
String msg = "GET /update?key=CX1FF9ZGH4RUS2SK"; //API Key ThinkSpeak
/*Koreksi sensor MQ135 untuk pendeteksian kadar CO2*/
#define RLOAD 1000
#define RZERO 23.32 


//Deklarasi Variabel
float kelembapan, suhu;
int kualitasUdara;
const char* deskSh;
const char* deskKlb;
const char* deskKu;
String waktu;
String tanggal;
int error;
int val; 
int sensorPin = A0; 
int sensorValue = 0;


void setup()                        //MainKodeStatis
{
  dht.begin();
  lcd.init();                       
  lcd.backlight();
  lcd.print("");
  Serial.begin(9600);
  myRTC.updateTime();
  pinMode(sensorPin, INPUT); 
  Initialize_SDcard();
  esp8266.begin(9600);
  Serial.println("Mengecek modul ESP8266");
  esp8266.println("AT+RST");
  esp8266.println("AT");
  if (esp8266.find("OK")){
    Serial.println("Terkoneksi dengan modul ESP8266");
    connectWiFi();
  }
  else {
    Serial.println("Modul ESP8266 tidak terdeteksi");
  }
  
  //WelcomeScreen
  lcd.setCursor(3,0);
  lcd.print("Env-Monitor");
  lcd.setCursor(1,1);
  lcd.print("by Kelompok 10");
  delay(2000);
  lcd.clear();
  lcd.setCursor(4,1);
  lcd.print(myRTC.dayofmonth);
  lcd.print("/");
  lcd.print(myRTC.month);
  lcd.print("/");
  lcd.print(myRTC.year);
  delay(2000);
  lcd.clear();
}


void loop()                         //MainKodePerulangan
{
  //Ambil Data Sensor
  kelembapan = dht.readHumidity();
  suhu = dht.readTemperature();
  val = analogRead(A0);
  myRTC.updateTime();
  kualitasUdara = gasSensor.getPPM(); 

  //Mengisi variabel deskripsi
  /*Deskripsi Udara*/
  if (suhu > 32.00){
    deskSh = "panas";
  } else if (suhu >= 29.00 && suhu <= 32.00){
    deskSh = "normal";
  } else if (suhu < 29.00){
    deskSh = "dingin";
  }
  /*Deskripsi Kelembapan*/
  if (kelembapan > 80.00){
    deskKlb = "lembab";
  } else if (kelembapan >= 73.00 && kelembapan <= 80.00){
    deskKlb = "normal";
  } else if (kelembapan < 73.00){
    deskKlb = "kering";
  }
  /*Deskripsi Kualitas Udara*/
  if (kualitasUdara > 4001){
    deskKu = "buruk  ";
  } else if (kualitasUdara >= 700 && kualitasUdara <= 4000){
    deskKu = "sedang ";
  } else if (kualitasUdara < 699){
    deskKu = "baik";
  }
  /*Deskripsi Waktu*/
  waktu = String(myRTC.hours)+ ":" + String(myRTC.minutes);
  /*Deskripsi Tanggal*/
  tanggal = String(myRTC.dayofmonth) + "/" + 
  (myRTC.month) + "/" + (myRTC.year);
  
  //Menampilkan deskripsi ke Serial
  Serial.println(deskSh);
  Serial.println(deskKlb);
  Serial.println(deskKu);
  Serial.println(waktu);
  Serial.println(tanggal);

  //Menampilkan LCD
  /*AtasKiri*/
  lcd.setCursor(0, 0);
  lcd.print(kualitasUdara);
  lcd.print("ppm");
  /*BawahKiri*/  
  lcd.setCursor(0, 1);
  lcd.print(suhu);
  lcd.print(" C");
  /*BawahKanan*/
  lcd.setCursor(9,1);
  lcd.print(kelembapan);
  lcd.print(" %");

  //Menulis Log ke SDCard
  Write_SDcard();

  //Menulis Log ke ThinkSpeak
  esp8266.println("AT");
  if (esp8266.find("OK")){
    uploadData();
  }
  
  //Setting Delay
  delay(100);

  //Menampilkan LCD (Animasi)
  /*AtasKanan*/
  lcd.setCursor(9,0);
  lcd.print("Jam");
  delay(1000);
  lcd.setCursor(9, 0);
  lcd.print("         ");
  lcd.setCursor(9, 0);
  for(int j = 0; j < 5; j++){
    lcd.print(waktu[j]);
    delay(400);  
  }
  lcd.setCursor(9, 0);
  lcd.print("         ");
  lcd.setCursor(9,0);
  lcd.print("Suhu");
  delay(1000);
  lcd.setCursor(9, 0);
  lcd.print("         ");
  lcd.setCursor(9, 0);
  for(int j = 0; j < 6; j++){
    lcd.print(deskSh[j]);
    delay(300);  
  }
  lcd.setCursor(9, 0);
  lcd.print("         ");
  lcd.setCursor(8, 0);
  lcd.print("Klmbapan");
  delay(1000);
  lcd.setCursor(8, 0);
  lcd.print("          ");
  lcd.setCursor(9, 0);
  for(int j = 0; j < 6; j++){
    lcd.print(deskKlb[j]);
    delay(300);  
  }
  lcd.setCursor(9, 0);
  lcd.print("         ");
  lcd.setCursor(9,0);
  lcd.print("Udara");
  delay(1000);
  lcd.setCursor(9, 0);
  lcd.print("         ");
  lcd.setCursor(9, 0);
  for(int j = 0; j < 6 ; j++){
    lcd.print(deskKu[j]);
    delay(300);  
  }
  lcd.setCursor(9, 0);
  lcd.print("         ");
  
}


void Initialize_SDcard(){           //KelasKodeCekSDCard
  //Mengecek SD Card
  if (!SD.begin(chipSelect)) {
    Serial.println("Tidak ada kartu memori!");
    return;
  }
  
  //Membuat File Log
  Serial.println("Membuat file log.txt...");
  File dataFile = SD.open("LoggerCD.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println
    ("tanggal,waktu,suhu,kelembapan,kualitasUdara");
    dataFile.close();
  }
}


void Write_SDcard()                 //KelasKodeTulisSDCard
{
  //Membuka file log
  File dataFile = SD.open("LoggerCD.txt", FILE_WRITE);

  //Menulis log
  if (dataFile) {
    dataFile.print(tanggal); 
    dataFile.print(","); 

    dataFile.print(waktu); 
    dataFile.print(","); 

    dataFile.print(suhu); 
    dataFile.print(","); 

    dataFile.print(kelembapan); 
    dataFile.print(","); 

    dataFile.print(kualitasUdara); 
    dataFile.print(","); 

    dataFile.println(); 
    dataFile.close(); 
  }
  else
  Serial.println("Penulisan file gagal!");
}


void uploadData()                    //KelasUploadData
{
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",15";
  Serial.println(cmd);
  esp8266.println(cmd);
  delay(2000);
  if(esp8266.find("Error"))
  {
    return;
  }
  cmd = msg ;
  cmd += "&field1=";    //field 1 untuk suhu
  cmd += suhu;
  cmd += "&field2=";    //field 2 untuk kelembapan
  cmd += kelembapan;
  cmd += "&field3=";    //field 3 untuk kualitasUdara
  cmd += kualitasUdara;
  cmd += "\r\n";
  Serial.print("AT+CIPSEND=");
  esp8266.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  esp8266.println(cmd.length());
  if(esp8266.find(">"))
  {
    Serial.print(cmd);
    esp8266.print(cmd);
  }
  else
  {
    Serial.println("AT+CIPCLOSE");
    esp8266.println("AT+CIPCLOSE");
    //Resend...
    error=1;
  }
}


boolean connectWiFi()                  //KelasKonekWifi
{
  Serial.println("AT+CWMODE=1");
  esp8266.println("AT+CWMODE=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  Serial.println(cmd);
  esp8266.println(cmd);
  delay(5000);
  if(esp8266.find("OK"))
  {
    return true;
  }
  else
  {
    return false;
  }
}
