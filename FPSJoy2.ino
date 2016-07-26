// FPSJoy
// Chiyoung Kim

#include <HID.h>
#include <Keyboard.h>
#include <stdlib.h>

const int xIn = A0;
const int yIn = A1;
const int selIn = 2;

const double sensitivity = .5;

int vert, horz;
int minX, maxX, minY, maxY;
int deadXNeg, deadXPos, deadYNeg, deadYPos;
int xCalib, yCalib;

int xState, yState;

// volatile int sel = HIGH;
int sel = HIGH;

int currSel;

void setup() {
  // put your setup code here, to run once:
  pinMode(xIn, INPUT);
  pinMode(yIn, INPUT);
  pinMode(selIn, INPUT);

  digitalWrite(selIn, HIGH);

  // attachInterrupt(digitalPinToInterrupt(selIn), selFxn, FALLING);
  
  xCalib = analogRead(xIn);
  yCalib = analogRead(yIn);

  minX = -xCalib;
  maxX = 1023-xCalib;

  deadXNeg = (int)(minX/2);
  deadXPos = (int)(maxX/2);

  minY = -yCalib;
  maxY = 1023-yCalib;

  deadYNeg = (int)(minY/2);
  deadYPos = (int)(maxY/2);

  xState = 0;
  yState = 0;

  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  horz = analogRead(xIn) - xCalib;
  vert = analogRead(yIn) - yCalib;
  currSel = digitalRead(selIn);
  if (sel == HIGH && currSel == LOW) {
    Keyboard.press('E');
    Keyboard.release('E');
  }
  sel = currSel;
  if (horz > deadXNeg && horz < deadXPos) {
    horz = 0;
  }
  else if (horz <= deadXNeg) {
    horz = -1;
  }
  else if (horz >= deadXPos) {
    horz = 1;
  }
  if (vert > deadYNeg && vert < deadYPos) {
    vert = 0;
  }
  else if (vert >= deadYNeg) {
    vert = -1;
  }
  else if (vert <= deadYPos) {
    vert = 1;
  }

  switch (horz){
    case 0:
      if (xState == -1) {
        Keyboard.release('A');
      }
      else if (xState == 1) {
        Keyboard.release('D');
      }
      xState = 0;
      break;
    case 1:
      if (xState == -1) {
        Keyboard.release('A');
        Keyboard.press('D');
      }
      else if (xState == 0) {
        Keyboard.press('D');
      }
      xState = 1;
      break;
    case -1:
      if (xState == 0) {
        Keyboard.press('A');
      }
      else if (xState == 1) {
        Keyboard.release('D');
        Keyboard.press('A');
      }
      xState = -1;
  }
  
  switch (vert){
    case 0:
      if (yState == -1) {
        Keyboard.release('S');
      }
      else if (yState == 1) {
        Keyboard.release('W');
      }
      yState = 0;
      break;
    case 1:
      if (yState == -1) {
        Keyboard.release('S');
        Keyboard.press('W');
      }
      else if (yState == 0) {
        Keyboard.press('W');
      }
      yState = 1;
      break;
    case -1:
      if (yState == 0) {
        Keyboard.press('S');
      }
      else if (yState == 1) {
        Keyboard.release('W');
        Keyboard.press('S');
      }
      yState = -1;
  }
  Serial.println(xState);
  Serial.println(yState);
  
}

void selFxn() {
  Keyboard.write('E');
}

