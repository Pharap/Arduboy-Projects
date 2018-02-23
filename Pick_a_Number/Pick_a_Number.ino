#include <Arduboy.h>

Arduboy a;
uint8_t lastBtn;
byte state, low, high, guess, guesses;
float frame;

void setup() {
  a.begin();
  a.clear();
  a.setFrameRate(12);

  state = 0;
  lastBtn = 0;
  low = 0;
  high = 100;
  guess = 50;
  guesses = 1;

  frame = 0.0;
}

void printCentered(String msg, int y, int scale = 1) {
  a.setCursor(64 - msg.length() * scale * 3, y);
  a.print(msg);
}

void loop() {
  a.clear();
  uint8_t btn = a.buttonsState();

  switch(state) {
    case 0:
      a.setTextSize(2);
      printCentered("Pick a #", 8, 2);
      
      a.setTextSize(1);
      printCentered("Under 100", 25);
      printCentered("Press to Start", 48 + (int) (sin(frame) * 2.0));
      frame += 0.1;
      if(!lastBtn && btn) state = 1;
      break;

    case 1:
      a.setTextSize(2);
      printCentered("Is it " + ((String) guess) + "?", 8, 2);
  
      a.setTextSize(1);
      printCentered("O Correct", 32);
      printCentered("< Lower  ", 40);
      printCentered("> Higher ", 48);
  
      if(!lastBtn) {
        if(btn & 0b00001100) state = 2; // A or B
        else if(btn & 0b00100000) { // Left
          high = guess;
          guesses++;
          guess = (low + high) >> 1;
        } else if(btn & 0b01000000) { // Right
          low = guess;
          guesses++;
          guess = (low + high) >> 1;
        }
      }
      break;

    case 2:
      a.setTextSize(2);
      printCentered(((String) guesses) + " Guesses", 8, 2);
      
      a.setTextSize(1);
      printCentered("Try Again?", 48);

      if(!lastBtn && btn) state = 0, guesses = 1;
      break;
  }

  lastBtn = btn;
  a.display();
}

