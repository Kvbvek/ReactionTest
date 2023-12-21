#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>

#define ACTION_BUTTON 2
#define RED 8
#define GREEN 9
#define BLUE 10

Adafruit_SSD1306 display(128, 32, &Wire);
static bool RedLed = true;
static bool GreenLed = false;
static bool BlueLed = false;
unsigned int ReactionTime = 0;
unsigned int ReactionTimeRefer = 0;
unsigned int TimeLimit = 0;
enum State {WAIT_FOR_TEST,WAIT_FOR_INTERRUPT,TESTED,END};
State myState = WAIT_FOR_TEST;
String ReactionStringValue = "0";

void setup() {
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(ACTION_BUTTON,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ACTION_BUTTON), ISR_ReactionTimeMeasure, FALLING);
  
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Reaction Test"));
  display.display();
  digitalWrite(RED,LOW);
  digitalWrite(GREEN,LOW);
  digitalWrite(BLUE,LOW);
  TimeLimit = random(3000,7000);
}

void loop() {
  digitalWrite(RED,RedLed);
  digitalWrite(GREEN,GreenLed);
  digitalWrite(BLUE,BlueLed);
  switch(myState){
    case WAIT_FOR_TEST:
      if(millis() == TimeLimit){
        RedLed = false;
        GreenLed = true;
        ReactionTimeRefer = millis();
        myState = WAIT_FOR_INTERRUPT;
      } 
      else{
        myState = WAIT_FOR_TEST;
      }
      break;
    case WAIT_FOR_INTERRUPT:
      myState = WAIT_FOR_INTERRUPT;
      break;
    case TESTED:
      detachInterrupt(digitalPinToInterrupt(ACTION_BUTTON));
      display.clearDisplay();
      display.setTextSize(3);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(10,2);
      display.println(ReactionStringValue + "ms");
      display.display();
      myState = END;
      break;
    case END:
      myState = END;
      break;
  }
}

void ISR_ReactionTimeMeasure(){
  BlueLed = true;
  GreenLed = false;
  ReactionTime = millis() - ReactionTimeRefer;
  ReactionStringValue = String(ReactionTime);
  myState = TESTED;
}