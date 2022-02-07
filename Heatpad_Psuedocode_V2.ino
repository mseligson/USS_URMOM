// Heating Pad Trigger Pseudo Code V2
const int heatpad = 10;
const int green_led = 8;

// temperature in fahrenheit
const int min_temp = 45;
int temp = 20;

void setup() {
  pinMode(heatpad, OUTPUT);
  pinMode(green_led, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // Read temperature
  
  
  // Trigger heating 
  if (temp < min_temp) {
    // turn on heater
    digitalWrite(heatpad, HIGH);
    digitalWrite(green_led, HIGH);

    // psuedocode mimicking heating up over time
    delay(250);
    temp = temp + 1;
    
  }
  else { // temp > min_temp
    // turn off heater
    digitalWrite(heatpad, LOW);
    digitalWrite(green_led, LOW);

    Serial.print("done!");
    delay(10000);

    temp = 20;
    
  }
  
  // Print temperature
  Serial.print("temperature: ");
  Serial.println(temp);

}
