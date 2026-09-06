// C++ code
//
int battery_level = 0;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop()
{
  battery_level = analogRead(A0);
  if (battery_level < 500) {
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
  } else {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
  }
  delay(10); // Delay a little bit to improve simulation performance
}
