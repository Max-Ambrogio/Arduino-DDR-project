#include <Adafruit_NeoPixel.h>

#define LED_PIN_1      2


// const int BUTTON_PRESS_THRESHOLD = 500;

//timing for time stays lit for simon says 
//timings for time in between
//timeing for user clicks


// How many NeoPixels are attached to the Arduino?
#define LED_COUNT    4

Adafruit_NeoPixel strip_1(LED_COUNT, LED_PIN_1, NEO_GRB + NEO_KHZ800);

const int buttonPin = 2;

const int MAX_LEVEL = 10; //set max level

int sequence[MAX_LEVEL]; 
int yourSequence[MAX_LEVEL] = {0,0,0,0,0,0,0,0,0,0}; 
int yourSequenceIndex = 0;



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


bool correct;
int phase = 0 ;
/* phases
0 respawn
1 simon says
2 user plays
3 right or wrong feedback
4 restart or loop back to phase 0
*/
int level = 1;

int velocity = 1000;

void setup() {
  Serial.begin(9600);
  Serial.println("start()");
  pinMode(button1, INPUT);
  pinMode(button2, INPUT); 
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  // pinMode(button, INPUT);
  
  
  pinMode(2, OUTPUT);
  
}

void loop(){
  if (phase == 0) {
    // respawn
    generate_sequence();
    level = 0;
    change_phase(1);
    
  } else if (phase == 1) {
    // coming back for the next level
    // simon says
    
    level++;
    for (int i = 0; i < MAX_LEVEL; i++){
      yourSequence[i] = 0;
    };
    yourSequenceIndex = 0;
    show_sequence();
    change_phase(2);
    
  } else if (phase == 2) {
    // user plays
    get_sequence();
    // check if buttons are down.
    // if a button is down, add to yourSequence
    // compare sequences. this is where the tough logic is
    // if they match "so far" but its still incomplete, do nothing
    // if they dont match, set correct = false, change phase to 3
    // if they do match perfectly, set correct = true, change phase to 3
    
  } else if (phase == 3) {
    // right or wrong feedback (flashing lights)
    // if correct, happy lights, if not sad lights
    // phase = 4
    
  } else if (phase == 4) {
    // restart whole game or respawn at next level
    // if correct, phase 0,
    // if !correct, level = 0, phase = 0
    
  } else {
    // huh?
    Serial.print("WHAATTTTT");
  }

}

void change_phase(int newPhase) {
  Serial.print("change phase:");
  Serial.println(newPhase);
  phase = newPhase;
}

void generate_sequence(){
  randomSeed(millis()); //crazy random
  for (int i = 0; i < MAX_LEVEL; i++){
    sequence[i] = random(1,5);
  };
  
  Serial.print("New sequence: ");
  Serial.print(sequence[0]);
  Serial.print(", ");
  Serial.print(sequence[1]);
  Serial.print(", ");
  Serial.print(sequence[2]);
  Serial.print(", ");
  Serial.print(sequence[3]);
  Serial.print(", ");
  Serial.print(sequence[4]);
  Serial.print(", ");
  Serial.print(sequence[5]);
  Serial.print(", ");
  Serial.print(sequence[6]);
  Serial.print(", ");
  Serial.print(sequence[7]);
  Serial.print(", ");
  Serial.print(sequence[8]);
  Serial.print(", ");
  Serial.println(sequence[9]);
}

void show_sequence(){
  for (int i = 0; i < level; i++){ 
    strip_1.setPixelColor(0, 0, 0, 0);
    strip_1.setPixelColor(1, 0, 0, 0);
    strip_1.setPixelColor(2, 0, 0, 0);
    strip_1.setPixelColor(3, 0, 0, 0);
    
    if (sequence[i] == 1) {
      strip_1.setPixelColor(0, 255, 0, 0);
    } else if (sequence[i] == 2) {
      strip_1.setPixelColor(1, 0, 255, 0);
    } else if (sequence[i] == 3) {
      strip_1.setPixelColor(2, 0, 0, 255);
    } else if (sequence[i] == 4) {
      strip_1.setPixelColor(3, 200, 0, 200);
    } else {
      // huh?
    }
    
    strip_1.show();
    delay(velocity);
    strip_1.clear();
    strip_1.show();
    delay(200);
  }
}

void get_sequence(){
  
  //reset led color
  strip_1.setPixelColor(0, 0, 0, 0);
  strip_1.setPixelColor(1, 0, 0, 0);
  strip_1.setPixelColor(2, 0, 0, 0);
  strip_1.setPixelColor(3, 0, 0, 0);
  
  // int A1value = analogRead(A1);
  // int A2value = analogRead(A2);
  // int A3value = analogRead(A3);
  // int A4value = analogRead(A4);

  // Serial.print("values ");
  // Serial.print(A1value);
  // Serial.print(", ");
  // Serial.print(A2value);
  // Serial.print(", ");
  // Serial.print(A3value);
  // Serial.print(", ");
  // Serial.println(A4value);

  int testB1 = analogRead(button1);
  int B1Delta = button1LastValue - testB1;
  button1LastValue = testB1;
  int testB2 = analogRead(button2);
  int B2Delta = button2LastValue - testB2;
  button2LastValue = testB2;
  int testB3 = analogRead(button3);
  int B3Delta = button3LastValue - testB3;
  button3LastValue = testB3;
  int testB4 = analogRead(button4);
  int B4Delta = button4LastValue - testB4;
  button4LastValue = testB4;

  
  // if(A1value >= BUTTON_PRESS_THRESHOLD){
  //   yourSequence[ yourSequenceIndex ] = 1;
  //   strip_1.setPixelColor(0, 255, 0, 0);
  //   Serial.println("user input: 1");
  //   yourSequenceIndex++;

  // } else if(A2value >= BUTTON_PRESS_THRESHOLD){
  //   yourSequence[ yourSequenceIndex ] = 2;
  //   strip_2.setPixelColor(0, 0, 255, 0);
  //   Serial.println("user input: 2");
  //   yourSequenceIndex++;

  // } else if(A3value >= BUTTON_PRESS_THRESHOLD){
  //   yourSequence[ yourSequenceIndex ] = 3;
  //   strip_3.setPixelColor(0, 0, 0, 255);
  //   Serial.println("user input: 3");
  //   yourSequenceIndex++;

  // } else if(A4value >= BUTTON_PRESS_THRESHOLD){
  //   yourSequence[ yourSequenceIndex ] = 4;
  //   strip_4.setPixelColor(0, 255, 0, 255);
  //   Serial.println("user input: 4");
  //   yourSequenceIndex++;

  // } else {

  
  if(B1Delta < -delta_threshold){
    yourSequence[ yourSequenceIndex ] = 1;
    strip_1.setPixelColor(0, 255, 0, 0);
    Serial.println("user input: 1");
    Serial.println(B1Delta);
    yourSequenceIndex++;
    analogRead(buttonG);

  } else if(B2Delta < -delta_threshold){
    yourSequence[ yourSequenceIndex ] = 2;
    strip_1.setPixelColor(1, 0, 255, 0);
    Serial.println("user input: 2");
    Serial.println(B2Delta);
    yourSequenceIndex++;
    analogRead(buttonG);

  } else if(B3Delta < -delta_threshold){
    yourSequence[ yourSequenceIndex ] = 3;
    strip_1.setPixelColor(2, 0, 0, 255);
    Serial.println("user input: 3");
    Serial.println(B3Delta);
    yourSequenceIndex++;
    analogRead(buttonG);

  } else if(B4Delta < -delta_threshold){
    yourSequence[ yourSequenceIndex ] = 4;
    strip_1.setPixelColor(3, 200, 0, 200);
    Serial.println("user input: 4");
    Serial.println(B4Delta);
    yourSequenceIndex++;
    analogRead(buttonG);

  } else {
    // Serial.println("no user input");
    strip_1.setPixelColor(0, 15, 0, 0);
    strip_1.setPixelColor(1, 0, 15, 0);
    strip_1.setPixelColor(2, 0, 0, 15);
    strip_1.setPixelColor(3, 15, 0, 15);
  }
  delay(50);
  analogRead(buttonG);

  if (compareSequencesInProgress() == 1) {
    if (compareSequencesExactly() == 1) {
      // you beat this level
      Serial.println("you beat the level");
      strip_1.setPixelColor(0, 0, 200, 0);
      strip_1.setPixelColor(1, 0, 200, 0);
      strip_1.setPixelColor(2, 0, 200, 0);
      strip_1.setPixelColor(3, 0, 200, 0);
      strip_1.show();
      strip_1.clear();
      delay(400);
      strip_1.setPixelColor(0, 0, 0, 0);
      strip_1.setPixelColor(1, 0, 0, 0);
      strip_1.setPixelColor(2, 0, 0, 0);
      strip_1.setPixelColor(3, 0, 0, 0);
      strip_1.show();
      strip_1.clear();
      delay(400);
      strip_1.setPixelColor(0, 0, 200, 0);
      strip_1.setPixelColor(1, 0, 200, 0);
      strip_1.setPixelColor(2, 0, 200, 0);
      strip_1.setPixelColor(3, 0, 200, 0);
      strip_1.show();
      strip_1.clear();
      delay(400);
      strip_1.setPixelColor(0, 0, 0, 0);
      strip_1.setPixelColor(1, 0, 0, 0);
      strip_1.setPixelColor(2, 0, 0, 0);
      strip_1.setPixelColor(3, 0, 0, 0);
      strip_1.show();
      strip_1.clear();
      delay(400);
      strip_1.setPixelColor(0, 0, 200, 0);
      strip_1.setPixelColor(1, 0, 200, 0);
      strip_1.setPixelColor(2, 0, 200, 0);
      strip_1.setPixelColor(3, 0, 200, 0);
      strip_1.show();
      strip_1.clear();
      delay(400);
      strip_1.setPixelColor(0, 15, 0, 0);
      strip_1.setPixelColor(1, 0, 15, 0);
      strip_1.setPixelColor(2, 0, 0, 15);
      strip_1.setPixelColor(3, 15, 0, 15);
      strip_1.show();
      
      change_phase(1);
      Serial.print("You are on level ");
      Serial.println(level);
      delay(1000);
    } else {
      // all good, keep going
      // Serial.println("all good keep going");
    }
  } else {
    // WOMP WOMP
    // show all read, reset, etc
      strip_1.setPixelColor(0, 200, 0, 0);
      strip_1.setPixelColor(1, 200, 0, 0);
      strip_1.setPixelColor(2, 200, 0, 0);
      strip_1.setPixelColor(3, 200, 0, 0);
      strip_1.show();
      strip_1.clear();
      delay(400);
      strip_1.setPixelColor(0, 0, 0, 0);
      strip_1.setPixelColor(1, 0, 0, 0);
      strip_1.setPixelColor(2, 0, 0, 0);
      strip_1.setPixelColor(3, 0, 0, 0);
      strip_1.show();
      strip_1.clear();
      delay(400);
      strip_1.setPixelColor(0, 200, 0, 0);
      strip_1.setPixelColor(1, 200, 0, 0);
      strip_1.setPixelColor(2, 200, 0, 0);
      strip_1.setPixelColor(3, 200, 0, 0);
      strip_1.show();
      strip_1.clear();
      delay(400);
      strip_1.setPixelColor(0, 0, 0, 0);
      strip_1.setPixelColor(1, 0, 0, 0);
      strip_1.setPixelColor(2, 0, 0, 0);
      strip_1.setPixelColor(3, 0, 0, 0);
      strip_1.show();
      strip_1.clear();
      delay(400);
      strip_1.setPixelColor(0, 200, 0, 0);
      strip_1.setPixelColor(1, 200, 0, 0);
      strip_1.setPixelColor(2, 200, 0, 0);
      strip_1.setPixelColor(3, 200, 0, 0);
      strip_1.show();
      strip_1.clear();
      delay(400);
      strip_1.setPixelColor(0, 15, 0, 0);
      strip_1.setPixelColor(1, 0, 15, 0);
      strip_1.setPixelColor(2, 0, 0, 15);
      strip_1.setPixelColor(3, 15, 0, 15);
      strip_1.show();
      Serial.println("BOOOOOOOOOOOOO");

      change_phase(0);
      delay(5000);
  }

  strip_1.show();

  // delay(1000);
}

int compareSequencesInProgress() {
  // Serial.println("compareSequencesInProgress()");
  // yourSequence vs sequence
  for (int i = 0; i < level; i++){
    if (yourSequence[i] == 0 || yourSequence[i] == sequence[i]) {
      // MATCHING SO FAR
    } else {
      // MISMATCH
      return 0;
    }
  }
  return 1;
}


int compareSequencesExactly() {
  // yourSequence vs sequence
  for (int i = 0; i < level; i++){
    if (yourSequence[i] == sequence[i]) {
      // MATCHING ALL THE WAY
    } else {
      // MISMATCH
      return 0;
    }
  }
  return 1;
}



