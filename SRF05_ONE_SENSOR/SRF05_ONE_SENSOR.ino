#include <HCSR04.h>
#include "Packetizer.h"

#define NR_OF_SAMPLES 4
#define TRIG_PIN      5
#define ECHO_PIN_1    6

HCSR04      hc(TRIG_PIN, ECHO_PIN_1); // first argument is trig pin, second is the echo
Packetizer  pack1(0);                 // arg: address of the sensor (0-127), use it to labeling sensors, 0 is the first, 1 is the second, and so...

int         values[NR_OF_SAMPLES] = { 0 };
byte        count  = 0;
int         prev = 0;
int         max_value = 0;
int         min_value = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  values[count] = hc.dist();

  // pack1.packetize(value) return a byte pointer
  //Serial.write(pack1.packetize(value), pack1.SIZE);  
  //if ((value < 4) | (value < 500))
    //Serial.write(pack1.packetize(value), pack1.SIZE);

  int somma = 0;
  
  for (int i=0; i<NR_OF_SAMPLES; i++) {
    somma += values[i];
  }

  /*
  for (int i = 0; i < NR_OF_SAMPLES; i++) {
    if (values[i] > max_value) max_value = values[i];
    if (values[i] < min_value) min_value = values[i];
  }

  somma = somma - max_value - min_value;
*/
  int median = int(somma / (float)NR_OF_SAMPLES);


  
  if (median != prev) {
    Serial.println(median);
    prev = median;
  }
  
  //Serial.println(median);

/*
  int value = hc.dist();
  if (value < 600)
    Serial.println(value);
  */
  count++;
  if (count >= NR_OF_SAMPLES) count = 0;
  
  delay(1);
  
}
