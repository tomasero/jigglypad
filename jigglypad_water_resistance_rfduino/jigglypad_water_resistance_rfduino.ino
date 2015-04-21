#include <RFduinoBLE.h>

const int LED_PIN = 1;
const int power1 = 5; //GPIO4
const int power2 = 4; //GPIO5
const int probe = 6; //GPIO6
const int resistorValue = 330;
int state = true;

void setup () {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED_PIN, LOW);
  delay(500);
  digitalWrite(LED_PIN,HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  
  // configure the RFduino BLE properties
  RFduinoBLE.advertisementData = "ledbtn";
  RFduinoBLE.advertisementInterval = 500;
  RFduinoBLE.deviceName = "RFduino";
  RFduinoBLE.txPowerLevel = -20;
  Serial.println("RFduino BLE Advertising interval is 500ms");
  Serial.println("RFduino BLE DeviceName: RFduino");
  Serial.println("RFduino BLE Tx Power Level: -20dBm");
  
  // start the BLE stack
  RFduinoBLE.begin();
  Serial.println("RFduino BLE stack started");
  
  initPower();
}

void loop () {
  RFduino_ULPDelay(INFINITE);
  float waterResistance = getWaterResistance();
  Serial.println(waterResistance);
  Serial.println("------------------");
  delay(1000);
  switchPolarity();
  delay(1000);
}

void switchPolarity () {
  if (!state) {
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
