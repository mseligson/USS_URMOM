/*
Measuring the outputs of three thermistors measuring external temp of USS Urmom
Reads voltage difference across each thermsistor and 10k ohm resistor 

Uses Jameco Electronics LM05-103 K thermistors

Using equations:
Vo = Vin * (R2/(R1+R2))
so R2 = R1 * (Vin/Vout - 1)
Steinhart-Hart equation: 1/T = A + BlnR + C(lnR)^3

@author Andromeda Kepecs

TODO readings become less consistent when more thermistors are added
TODO Calibrate individual thermistors
*/

// Analog input pin for each thermistor
const int THERM_PIN1 = 0;
const int THERM_PIN2 = 1;
const int THERM_PIN3 = 2;

// Timing 
const int DELAY = 5; // How often a reading is taken in seconds
const int SEC = 1000;
const int BAUD_RATE = 9600;

// Steinhart-Hart Coefficients for a generic 10k ohm thermistor
// TODO create 9 constant variables of SH coefficients calibrated to each specific thermistor
const float SH_A = 0.001125308852122;
const float SH_B = 0.000234711863267; 
const float SH_C = 0.000000085663516;

const float RESISTANCE1 = 10000; // Value of resistor used in series with thermistor

void setup() {
  Serial.begin(BAUD_RATE);
}

void loop() {
  // Read temperature for thermistor 1
  int Vo = analogRead(THERM_PIN1);
  float resistance2 = calculate_resistance(Vo, RESISTANCE1);
  float temperature1 = calculate_temperature(resistance2);

  // Read temperature for thermistor 2
  Vo = analogRead(THERM_PIN2);
  resistance2 = calculate_resistance(Vo, RESISTANCE1);
  float temperature2 = calculate_temperature(resistance2); 

  // Read temperature for thermistor 3
  Vo = analogRead(THERM_PIN2);
  resistance2 = calculate_resistance(Vo, RESISTANCE1);
  float temperature3 = calculate_temperature(resistance2);  

  // Serial print readings
  Serial.print("Temp in celcius for thermistor 1: ");
  Serial.println(temperature1);
  Serial.print("Temp in celcius for thermistor 2: ");
  Serial.println(temperature2);
  Serial.print("Temp in celcius for thermistor 3: ");
  Serial.println(temperature3);

  delay(DELAY * SEC);

}

/* Calculate resistance of thermistor from voltage reading
@param int v, voltage reading
@param float r1, value of resistor in series
returns float r2
*/
float calculate_resistance(int v, float r1) {
  float r2 = r1 * (1023.0 / float(v) - 1.0);
  return r2;
}

/* Calculate temperature using Steinhart-Hart equation and coefficients for a 10k ohm resistor
@param float r, resistance of thermistor
returns float temperature in degrees celcius
*/
float calculate_temperature(float r) {
  float logr = log(r);
  float temperature = (1.00 / (SH_A + SH_B*logr + SH_C*logr*logr*logr)); // Temperature in Kelvin
  temperature -= 273.15; // Temperature in celcius
  return temperature;
}