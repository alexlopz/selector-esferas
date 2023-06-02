#include <Servo.h>
#include <LiquidCrystal_I2C.h> 
#include<Wire.h>
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
Servo topServo;
Servo bottomServo;
int frequency = 0;
int color = 0;
int temp = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  topServo.attach(7);
  bottomServo.attach(8);
  Serial.begin(9600);

  Serial.println(topServo.read());

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lector de esferas...");
  delay(3000);
}
void loop() {
  topServo.write(130);
  Serial.println("inicio");
  delay(2000);

  for (int i = 130; i > 90; i--) {
    topServo.write(i);
    delay(8);
  }
  delay(1000);

  lcd.clear();
  lcd.print("leyendo esfera...");
  color = readColor();
  delay(10);
  switch (color) {
    case 1:
      bottomServo.write(20);
      Serial.println("se mueve rojo");
      break;
    case 2:
      bottomServo.write(50);
      Serial.println("se mueve amarillo");
      break;
    case 3:
      bottomServo.write(90);
      Serial.println("se mueve verde");
      break;
    case 0:
      lcd.clear();
      lcd.print("Desconocido");
      break;
  }
  delay(300);

  for (int i = 90; i > 44; i--) {
    topServo.write(i);
    delay(8);
  }
  delay(200);

  for (int i = 44; i < 130; i++) {
    topServo.write(i);
    delay(2);
  }
  color = 0;
}
// Custom Function - readColor()
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);
  if (R<135 & R>99 & G<245 & G>201) {// ROJO
    color = 1; 
    lcd.clear();
    lcd.print("Rojo :)");
    Serial.println("rojo");
  }
  if (R<107 & R>70 & G<105 & G>85) { // AMARILLO
    color = 2; 
    lcd.clear();
    lcd.print("Amarillo :)");
    Serial.println("amarillo");
  }
  if (R<165 & R>145 & G<120 & G>100) {// VERDE
    color = 3;
    lcd.clear();
    lcd.print("Verde :)");
    Serial.println("verde");
  }

  return color;
}
