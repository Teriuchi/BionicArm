// Miika Laeslehto & Jaakko Palomäki

#include <Servo.h>                // Servo library
Servo finger;                     // Määritetään servo
int flex = 0;                     // Onko sormi koukistettu
int raja = 20;                    // EMG rajan ylitys aktivoimaan servo
unsigned long edellinenLiike = 0; // Säilyttää milloin viimeksi servo liikkunut
const long viive = 3000;       // viive

void setup() {
  finger.attach(3);   //Servo
  pinMode(A0, INPUT); //EMG
  Serial.begin(9600); // Serial monitor
  finger.write(0);    //Nollataan servo
  
}

void loop() {
  int emg = analogRead(A0); // lukee myosignaalin
  unsigned long kulunutAika = millis(); // muuttuva tila
  
  if(emg > raja && flex == 0 && kulunutAika - edellinenLiike >= viive){
    finger.write(180);  
    flex = 1;
  }    
  else if(emg > raja && flex == 1 && kulunutAika - edellinenLiike >= viive){
    finger.write(0);
    flex = 0;
  }
  
  Serial.println(analogRead(A0));  // Tulostaa EMG-signaalin arvon
  
  delay(10);  // Viive jotta stabiili
}
