/* Thermistor Reading
Reads voltage difference across thermsistor and 10k ohm resistor

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
float R2, temperature;

// Steinhart-Hart Coefficients
const float SH_A = 0.001125308852122;
const float SH_B = 0.000234711863267; 
const float SH_C = 0.000000085663516;

// Setup
void setup() {
  Serial.begin(BAUD_RATE);
}

// Read and print temperature
void loop() {
  // Read voltage difference to calculate thermistor resistance
  Vo = analogRead(THERM_PIN);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); // TODO Changing / to * causes it to increase appropriately but reading is still off
  float logR2 = log(R2);

  // Calculate temperature using Steinhart-Hart equation and coefficients
  temperature = (1.0000 / (SH_A + SH_B*logR2 + SH_C*logR2*logR2*logR2));
  temperature -= 273.15; // Temperature celcius
  // temperature = (temperature * 9.0)/ 5.0 + 32.0; // Celcius to fahrenheit

  // Print temperature
  Serial.print("Temperature: "); 
  Serial.print(temperature);
  Serial.println(" C"); 

  delay(DELAY * SEC); // Delay in seconds between temperature readings
}
