const int helloBell = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(helloBell, OUTPUT);

}

void loop() {
  
  // StartBeep
  noTone(helloBell);
  delay(2000);
  tone(helloBell, 2000);
  delay(200);
  noTone(helloBell);
  delay(1000);
  
  // NokiaTune:
  tone(helloBell, 1319);
  delay(143);
  tone(helloBell, 1175);
  delay(143);
  tone(helloBell, 740);
  delay(277);
  tone(helloBell, 831);
  delay(277);
  tone(helloBell, 1109);
  delay(143);
  tone(helloBell, 988);
  delay(143);
  tone(helloBell, 587);
  delay(277);
  tone(helloBell, 659);
  delay(277);
  tone(helloBell, 988);
  delay(143);
  tone(helloBell, 880);
  delay(143);
  tone(helloBell, 554);
  delay(277);
  tone(helloBell, 659);
  delay(277);
  tone(helloBell, 880);
  delay(543);



}
