const int power1 = 2;
const int power2 = 3;
const int probe = A0;
const int resistorValue = 220;
int state = true;

void setup () {
  Serial.begin(9600);
  initPower();
}

void loop () {
  float waterResistance = getWaterResistance();
  Serial.println(waterResistance);
  Serial.println("------------------");
  delay(1000);
  switchPolarity();
  delay(1000);
}

void switchPolarity () {
  if (state) {
    digitalWrite(power1, HIGH);
    digitalWrite(power2, LOW);
  } else {
    digitalWrite(power1, LOW);
    digitalWrite(power2, HIGH);
  }
  state = !state;
}

float getWaterResistance () {
  Serial.print("State: ");
  Serial.println(state);
  int value = analogRead(probe);
  float voltage = value * (5.0 / 1023.0);
  Serial.print("Value: ");
  Serial.println(value);
  Serial.print("Voltage: ");
  Serial.println(voltage);
  int output = 0;
  if (state) {
//    output = (40*voltage)/(1 - (voltage/5));
    output = (voltage * resistorValue)/(5 - voltage);
  } else {
    output = (5 * resistorValue)/voltage - resistorValue;
//    output = (1000/voltage) - 200;
  }
  Serial.print("Output: ");
  Serial.println(output);
  return output;
}

void initPower () {
   pinMode(power1, OUTPUT);
   pinMode(power2, OUTPUT); 
  digitalWrite(power1, HIGH);
  digitalWrite(power2, LOW);
}
