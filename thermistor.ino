/* Thermistor Reading
Reads voltage difference across thermsistor (~125k ohm at room temp) 
and 100k ohm resistor connected in series

Using equations:
Vo = Vin * (R2/(R1+R2))
so R2 = R1 * (Vin/Vout - 1)
Steinhart-Hart equation: 1/T = A + BlnR + C(lnR)^3

Serial print temp reading every customizable DELAY amount
@author Andromeda Kepecs
*/

const int BAUD_RATE = 9600; // Baud rate
const int SEC = 1000; // 1 SEC = 1000 ms

const int DELAY = 5; // Serial print every amount of seconds
const int THERM_PIN = 0; // Thermsistor is connected to this pin

const float R1 = 10000; // Value of resistor

int Vo;
float R2, T;

// Steinhart-Hart Coefficients for a 10k ohm thermistor
const float A = 0.001125308852122;
const float B = 0.000234711863267; 
const float C = 0.000000085663516;

// Setup
void setup() {
  Serial.begin(BAUD_RATE);
}

// Read and print temperature
void loop() {
  Vo = analogRead(THERM_PIN);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); // TODO Changing / to * causes it to increase appropriately but reading is still off
  float logR2 = log(R2);
  Serial.println(R2);

  T = (1.0000 / (A + B*logR2 + C*logR2*logR2*logR2));
  Serial.println(T);
  T -= 273.15;
  Serial.println(T);
  T = (T * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" F"); 

  delay(5 * SEC);

}
