#include <IRremote.h>

IRsend irsend;

unsigned int baudRate = 9600;
unsigned int shortBreak = 400;
unsigned int longBreak = 5000;
unsigned int frequency = 38;
unsigned int menuBtn[68] = {9200,4500,650,500,650,1650,650,1650,700,1600,700,500,650,1650,650,1650,650,1650,650,1650,700,1600,700,1650,650,500,650,550,650,500,650,550,650,1650,650,1650,650,1650,650,550,650,500,650,550,650,500,650,500,700,500,650,500,700,1650,650,1650,650,1650,650,1650,650,500,700,500,650,1650,650};
unsigned int playBtn[68] = {9200,4500,650,500,650,1650,650,1650,700,1650,650,500,650,1650,650,1650,650,1650,650,1650,700,1600,700,1600,700,500,650,550,650,500,650,500,700,1650,650,1650,650,500,650,1650,650,550,650,500,650,550,600,550,650,550,650,500,650,1650,650,1650,650,1650,650,1700,650,500,650,500,700,1650,650};
unsigned int leftBtn[68] = {9200,4550,600,550,650,1650,650,1650,650,1700,600,550,650,1650,650,1650,650,1700,600,1700,600,1700,650,1650,650,550,600,550,650,550,600,550,650,1650,650,1700,600,550,650,550,600,1700,650,500,650,550,650,500,650,550,650,550,600,1700,600,1700,600,1700,650,1650,650,550,600,550,650,1650,650};
unsigned int rightBtn[68] = {9200,4500,650,550,650,1650,650,1650,650,1650,650,550,650,1650,650,1650,650,1650,650,1650,650,1650,650,1650,650,550,650,500,700,500,650,500,650,1650,700,500,650,1650,650,1650,650,550,600,550,650,550,650,500,650,550,650,500,650,1650,650,1650,650,1650,700,1600,700,500,650,550,650,1650,650};
unsigned int topBtn[68] = {9340,4600,580,580,640,1640,600,1700,580,1700,600,560,580,1700,600,1700,580,1700,600,1700,580,1700,600,1700,580,580,560,580,580,580,580,580,580,1700,580,580,580,1700,580,580,580,1700,580,580,580,580,580,560,600,560,580,580,580,560,600,580,560,580,580,1700,580,1720,580,1700,580,600,580}; 
unsigned int bottomBtn[68] = {9360,4580,580,580,580,1700,580,1700,600,1700,580,560,600,1700,580,1700,580,1720,580,1700,580,1700,600,1680,600,560,580,580,580,560,600,560,580,1700,600,560,580,580,580,1700,580,1700,580,580,580,580,580,600,560,560,580,580,580,560,600,580,560,560,600,1700,580,1700,580,1720,580,580,580};
unsigned int btnRawLength = 68;
int ansi = 0;

void menu() {
    irsend.sendRaw(menuBtn, btnRawLength, frequency);
    delay(shortBreak);
}

void play() {
    irsend.sendRaw(playBtn, btnRawLength, frequency);
    delay(shortBreak);
}

void left() {
    irsend.sendRaw(leftBtn, btnRawLength, frequency);
    delay(shortBreak);
}

void right() {
    irsend.sendRaw(rightBtn, btnRawLength, frequency);
    delay(shortBreak);
}

void top() {
    irsend.sendRaw(topBtn, btnRawLength, frequency);
    delay(shortBreak);
}

void bottom() {
    irsend.sendRaw(bottomBtn, btnRawLength, frequency);
    delay(shortBreak);
}

void turnOn() {
    menu();
    delay(longBreak);
}

void setup() {
  Serial.begin(baudRate);
  delay(shortBreak);
  turnOn();
  Serial.println("Initialized.");
}

void loop() {
  while (Serial.available() > 0) {
    int code = Serial.read();
    switch (code) {
    case 13:
    case 32:
      Serial.println("+PLAY");
      play();
      Serial.println("-PLAY");
      ansi = 0;
      break;
    case 127:
      Serial.println("+MENU");
      menu();
      Serial.println("-MENU");
      ansi = 0;
      break;
    case 27:
      ansi = 1;
      break;
    case 91:
      if (ansi > 0) {
        ansi = 2;
      } else {
        ansi = 0;
      }
      break;
    case 65:
      if (ansi == 2) {
        Serial.println("+UP");
        top();
        Serial.println("-UP");
      }
      ansi = 0;
      break;
    case 68:
      if (ansi == 2) {
        Serial.println("+LEFT");
        left();
        Serial.println("-LEFT");
      }
      ansi = 0;
      break;
    case 66:
      if (ansi == 2) {
        Serial.println("+DOWN");
        bottom();
        Serial.println("-DOWN");
      }
      ansi = 0;
      break;
    case 67:
      if (ansi == 2) {
        Serial.println("+RIGHT");
        right();
        Serial.println("-RIGHT");
      }
      ansi = 0;
      break;
    default:
      //Serial.print("unknown ");
      //Serial.println(code);
      break;
    }
  }
}
