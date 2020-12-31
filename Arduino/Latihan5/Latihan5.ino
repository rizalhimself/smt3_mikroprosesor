int led1 = 8;
int led2 = 9;
int led3 = 10;
int led4 = 11;

int brightness = 0;
int fadeAmount = 5;
int ledDelay = 100;

void setup(/* arguments */) {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop(/* arguments */) {
  analogWrite(led1, brightness);
  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  analogWrite(led2, LOW);
  analogWrite(led3, LOW);
  analogWrite(led4, LOW);
  delay(ledDelay);


  analogWrite(led1, LOW);
  analogWrite(led2, brightness);
  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  analogWrite(led3, LOW);
  analogWrite(led4, LOW);
  delay(ledDelay);


  analogWrite(led1, LOW);
  analogWrite(led2, LOW);
  analogWrite(led3, brightness);
  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  analogWrite(led4, LOW);
  delay(ledDelay);


  analogWrite(led1, LOW);
  analogWrite(led2, LOW);
  analogWrite(led3, LOW);
  analogWrite(led4, brightness);
  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(ledDelay);

}
