#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 6, 7);

int RedLed = 3;
int GreenLed = 8;
int YellowLed = 9;
int BuzzerPin = 10;
int SolarPin = A0;
int PowerSwitch = 13;
int ResetButton = 2;
int InverterLed = A3;

int deadThresh = 150;
int criticalThresh = 250;
int lowThresh = 400;
int fullThresh = 800;

unsigned long lastBlink = 0;
bool ledState = false;
String lastState = "";

bool systemOn = true;
bool systemShutdown = false;
bool lastPowerBtn = HIGH;
bool lastResetBtn = HIGH;

void setup() {
  pinMode(RedLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(YellowLed, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(InverterLed, OUTPUT);
  pinMode(PowerSwitch, INPUT_PULLUP);
  pinMode(ResetButton, INPUT_PULLUP);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void allOff() {
  digitalWrite(RedLed, LOW);
  digitalWrite(GreenLed, LOW);
  digitalWrite(YellowLed, LOW);
  digitalWrite(InverterLed, LOW);
  noTone(BuzzerPin);
  lcd.noDisplay();
}

void loop() {
  bool powerBtn = digitalRead(PowerSwitch);
  if (powerBtn == LOW && lastPowerBtn == HIGH) {
    systemOn = !systemOn;
    delay(200);
  }
  lastPowerBtn = powerBtn;

  bool resetBtn = digitalRead(ResetButton);
  if (resetBtn == LOW && lastResetBtn == HIGH) {
    systemShutdown = false;
    delay(200);
  }
  lastResetBtn = resetBtn;

  if (!systemOn) {
    allOff();
    return;
  }

  int solarValue = analogRead(SolarPin);

  if (systemShutdown) {
    if (solarValue >= deadThresh) {
      systemShutdown = false;
    } else {
      allOff();
      return;
    }
  }

  lcd.display();
  float voltage = solarValue * (5.0 / 1023.0);
  float current = voltage / 100.0;
  Serial.println(solarValue);

  String state;
  if (solarValue < deadThresh) state = "Dead";
  else if (solarValue < criticalThresh) state = "Critical";
  else if (solarValue < lowThresh) state = "Low";
  else if (solarValue < fullThresh) state = "Charging";
  else state = "Full";

  if (state == "Dead" && lastState != "Dead") {
    tone(BuzzerPin, 1000, 3000);
    delay(3000);
    noTone(BuzzerPin);
    systemShutdown = true;
    lastState = "Dead";
    return;
  }
  lastState = state;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.print(voltage);
  lcd.print(" I:");
  lcd.print(current, 3);

  if (state == "Full") {
    digitalWrite(GreenLed, HIGH);
    digitalWrite(RedLed, LOW);
    digitalWrite(YellowLed, LOW);
    digitalWrite(InverterLed, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Charging Complete");
  }
  else if (state == "Charging") {
    digitalWrite(RedLed, LOW);
    digitalWrite(GreenLed, LOW);
    digitalWrite(InverterLed, HIGH);
    if (millis() - lastBlink >= 300) {
      lastBlink = millis();
      ledState = !ledState;
      digitalWrite(YellowLed, ledState);
    }
    lcd.setCursor(0, 1);
    lcd.print("Charging");
  }
  else if (state == "Low") {
    digitalWrite(GreenLed, LOW);
    digitalWrite(YellowLed, LOW);
    digitalWrite(InverterLed, HIGH);
    if (millis() - lastBlink >= 700) {
      lastBlink = millis();
      ledState = !ledState;
      digitalWrite(RedLed, ledState);
      if (ledState) tone(BuzzerPin, 1000, 100);
    }
    lcd.setCursor(0, 1);
    lcd.print("Low Power");
  }
  else if (state == "Critical") {
    digitalWrite(GreenLed, LOW);
    digitalWrite(YellowLed, LOW);
    digitalWrite(InverterLed, HIGH);
    if (millis() - lastBlink >= 120) {
      lastBlink = millis();
      ledState = !ledState;
      digitalWrite(RedLed, ledState);
      if (ledState) tone(BuzzerPin, 1200, 60);
    }
    lcd.setCursor(0, 1);
    lcd.print("CRITICAL!");
  }
}
