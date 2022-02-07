// Buzzer Psuedo Code

const int buzzer = 12;
const int on = 2000; // buzz for 2 sec
const int wait = 20000; // wait for 20 sec between buzzes

// Psuedo normal conditions
const int altitude = 40; // balloon altitude is 40 ft
const int time_hrs = 5; // more than 5 hours have elapsed
const int pressure = 15; // pressure is 15 psi

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // If balloon has landed (time > 4 hrs AND alt < 50 ft or psi > 10)
  if (time_hrs > 4 && (altitude < 50 || pressure > 10)) { 
    // Buzzer goes on, then waits
    digitalWrite(buzzer, HIGH);
    delay(on);
    digitalWrite(buzzer, LOW);
    delay(wait);
   }
  
}
