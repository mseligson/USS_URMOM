/* Internal heating pad trigger using thermistor reading of temperature
Reads voltage difference across thermsistor and 10k ohm resistor

Using equations:
Vo = Vin * (R2/(R1+R2))
so R2 = R1 * (Vin/Vout - 1)
Steinhart-Hart equation: 1/T = A + BlnR + C(lnR)^3

Serial print temp reading every customizable DELAY amount
@authors Andromeda Kepecs, Amy Wyatt
*/

// Digital output pin for heating pads
const int HEAT_PAD = 10;

// Analog input pin for thermistor
const int THERM_PIN = 0;

// Temps to trigger heating pad in Celcius
const int MIN_TEMP = 10;
const int MAX_TEMP = 15;

// Timing
const int DELAY = 5; // How many seconds the sensor takes a reading
const int SEC = 1000; // 1 sec = 1000 ms
const int BAUD_RATE = 9600;

// Steinhart-Hart Coefficients
const float SH_A = 0.001125308852122;
const float SH_B = 0.000234711863267; 
const float SH_C = 0.000000085663516;

const float R1 = 10000; // Value of resistor used in series with thermistor

void setup() {
  pinMode(HEAT_PAD, OUTPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  // Read in temperature
  int Vo = analogRead(THERM_PIN); // Read in voltage from thermistor pin
  float R2 = calculate_resistance(Vo, R1);
  int temperature = int(calculate_temperature(R2));

  // Trigger heating pad if below min temperature
  if (temperature < MIN_TEMP) {
    digitalWrite(HEAT_PAD, HIGH);
  }
  else if (temperature > MAX_TEMP) {
    digitalWrite(HEAT_PAD, LOW);
  }
  Serial.print("Temp in celcius: ");
  Serial.println(temperature);


  delay(DELAY * SEC); // Delay in seconds between temperature readings
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


