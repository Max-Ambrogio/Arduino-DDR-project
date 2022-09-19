#include <Adafruit_NeoPixel.h>

#define LED_PIN_1      2


//timing for time stays lit for simon says 
//timings for time in between
//timeing for user clicks


// How many NeoPixels are attached to the Arduino?
#define LED_COUNT    4


Adafruit_NeoPixel strip_1(LED_COUNT, LED_PIN_1, NEO_GRB + NEO_KHZ800);

int button1 = A0;
int button2 = A1;
int button3 = A2;
int button4 = A3;
int buttonG = A5;

int button1LastValue = 0;
int button2LastValue = 0;
int button3LastValue = 0;
int button4LastValue = 0;

int delta_threshold = 500;

void setup() {
  Serial.begin(9600);
  Serial.println("Simon Says!");
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  strip_1.begin();
  strip_1.clear();
  strip_1.show();
  delay(500);
  strip_1.setPixelColor(0,15,0,0);
  strip_1.setPixelColor(1,0,15,0);
  strip_1.setPixelColor(2,0,0,15);
  strip_1.setPixelColor(3,15,15,0);
  strip_1.show();
}



/*
 a instantaneous change is how
 check for instantaeous change for adding to user input array 
 check for long change for led change visual 
*/

void loop() {
  int testB1 = analogRead(button1);
  int B1Delta = button1LastValue - testB1;
  button1LastValue = testB1;
  if (B1Delta < -delta_threshold) {
    strip_1.setPixelColor(0,250,0,0);

  } else if (B1Delta > delta_threshold) {
    strip_1.setPixelColor(0,15,0,0);

  }
  analogRead(buttonG);
  Serial.print("buttonOne:");
  Serial.print(B1Delta);
  Serial.print(",");
  
  
  int testB2 = analogRead(button2);
  int B2Delta = button2LastValue - testB2;
  button2LastValue = testB2;
  if (B2Delta < -delta_threshold) {
    strip_1.setPixelColor(1,0,250,0);

  } else if (B2Delta > delta_threshold) {
    strip_1.setPixelColor(1,0,15,0);
  }
  analogRead(buttonG);
 
  Serial.print("buttonTwo:");
  Serial.print(B2Delta);
  Serial.print(",");
  


  int testB3 = analogRead(button3);
  int B3Delta = button3LastValue - testB3;
  button3LastValue = testB3;
  if (B3Delta < -delta_threshold) {
    strip_1.setPixelColor(2,0,0,250);

  } else if (B3Delta > delta_threshold) {
    strip_1.setPixelColor(2,0,0,15);
  }
  analogRead(buttonG);
 
  Serial.print("buttonThree:");
  Serial.print(B3Delta);
  Serial.print(",");
  


  int testB4 = analogRead(button4);
  int B4Delta = button4LastValue - testB4;
  button4LastValue = testB4;
  if (B4Delta < -delta_threshold) {
    strip_1.setPixelColor(3,200,250,0);

  } else if (B4Delta > delta_threshold) {
    strip_1.setPixelColor(3,15,15,0);
  }
  analogRead(buttonG);
 
  Serial.print("buttonFour:");
  Serial.print(B4Delta);
  Serial.println("");

  strip_1.show();

  delay(50);
}
