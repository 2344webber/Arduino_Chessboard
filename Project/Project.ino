#include <D:\Project\Arduino\Project\shift.cpp>
#include <D:\Project\Arduino\Project\chess_detect.cpp>
#include<FastLED.h>
//#include <C:\Project\shift.cpp>
//#include <C:\Project\chess_detect.cpp>
#define NUM_LEDS 64
#define LED_type WS2812B
#define COLOR GRB
#define LED_pin 4
#define load 6
#define dataIn 5
#define clockIn 7

CRGB leds[NUM_LEDS];
int O, Updown, ifUpdown, firsthand = 1, start = 1;
bool state[64];
char eatmove[64];
bool checkboard[64] = {1, 1, 1, 1, 1, 1, 1, 1,
                       1, 1, 1, 1, 1, 1, 1, 1,
                       0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0,
                       1, 1, 1, 1, 1, 1, 1, 1,
                       1, 1, 1, 1, 1, 1, 1, 1,
                      };
int chess[64] = {1, 2, 3, 4, 5, 6, 7, 8,
                 9, 9, 9, 9, 9, 9, 9, 9,
                 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0,
                 10, 10, 10, 10, 10, 10, 10, 10,
                 11, 12, 13, 14, 15, 16, 17, 18,
                };
shift165 sft(load, dataIn, clockIn, 8);

void setup()
{
  Serial.begin(9600);
  pinMode(load, OUTPUT);
  pinMode(clockIn, OUTPUT);
  pinMode(dataIn, INPUT);
  pinMode(LED_pin, OUTPUT);
  FastLED.addLeds<WS2812B,LED_pin,GRB>(leds,NUM_LEDS);

  for (int i = 0; i < 64; i++) {
    
  }
  //setBoard(firsthand);
}

void loop()
{
  chessRead();
  if (start) {
    boardCheck(state, checkboard);
  }
  /*顯示棋盤狀態*/
  Serial.println("目前狀態:");
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      //Serial.print(chessname[8 * i + j]);
    }
    Serial.print("\n");
  }
  for (int i = 0; i < 64; i++) {
    if (sft.read(i) != state[i]) {
      Updown = i;
      ifUpdown = 1;
      break;
    }
  }
  if (ifUpdown) {
    for (int i = 0; i < 64; i++) {

    }
  }
  delay(2000);
}

void chessRead()
{
  digitalWrite(load, 0);
  delayMicroseconds(3);
  digitalWrite(load, 1);
  for (int i = 0; i < 64; i++) {
    state[i] = sft.read(i);
  }
}

void foreach (bool x[], bool y[], bool z[]) {
  for (int i = 0; i < sizeof(x); i++) {
    int count = x[i];
    if (count == z[i]) {
      O += 1;
      y[i] = 0;
    }
    else {
      y[i] = 1;
    }
  }
}

void boardCheck(bool check[64] , bool board[64])
{
  bool errorpin[64];
  foreach(check, errorpin, board);
  if (O == 64) {
    Serial.println("success");
    start = 0;
  }
  else {
    Serial.print("錯誤腳位:");
    for (int i = 0; i < sizeof(errorpin); i++) {
      Serial.print(errorpin[i]);
      Serial.print(",");
    } Serial.println(" ");
  }
}

/*void setBoard(int type) {
  if (type == 1) { //上黑下白
    for (int ii = 0; ii < 64; ii++) {
      if (chess[ii] == 1 || chess[ii] == 8) chessname[ii] = 'E';
      else if (chess[ii] == 2 || chess[ii] == 7) chessname[ii] = 'D';
      else if (chess[ii] == 3 || chess[ii] == 6) chessname[ii] = 'C';
      else if (chess[ii] == 4) chessname[ii] = 'B';
      else if (chess[ii] == 5) chessname[ii] = 'A';
      else if (chess[ii] == 11 || chess[ii] == 18) chessname[ii] = 'e';
      else if (chess[ii] == 12 || chess[ii] == 17) chessname[ii] = 'd';
      else if (chess[ii] == 13 || chess[ii] == 16) chessname[ii] = 'c';
      else if (chess[ii] == 14) chessname[ii] = 'b';
      else if (chess[ii] == 15) chessname[ii] = 'a';
      else if (chess[ii] == 9) chessname[ii] = 'F';
      else if (chess[ii] == 10) chessname[ii] = 'f';
      else chessname[ii] = 'X';
    }
  }
  if (type == 0) { //上白下黑
    for (int ii = 0; ii < 64; ii++) {
      if (chess[ii] == 1 || chess[ii] == 8) chessname[ii] = 'e';
      else if (chess[ii] == 2 || chess[ii] == 7) chessname[ii] = 'd';
      else if (chess[ii] == 3 || chess[ii] == 6) chessname[ii] = 'c';
      else if (chess[ii] == 4) chessname[ii] = 'a';
      else if (chess[ii] == 5) chessname[ii] = 'b';
      else if (chess[ii] == 11 || chess[ii] == 18) chessname[ii] = 'E';
      else if (chess[ii] == 12 || chess[ii] == 17) chessname[ii] = 'D';
      else if (chess[ii] == 13 || chess[ii] == 16) chessname[ii] = 'C';
      else if (chess[ii] == 14) chessname[ii] = 'A';
      else if (chess[ii] == 15) chessname[ii] = 'B';
      else if (chess[ii] == 9) chessname[ii] = 'f';
      else if (chess[ii] == 10) chessname[ii] = 'F';
      else chessname[ii] = 'X';
    }
  }
  }*/
