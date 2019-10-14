#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define BUTTON 13
int prevBtnState = 0;
int btnState = 0;

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int flag = 1;

void setup()
{
  pinMode(BUTTON, OUTPUT);
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true) {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
}

void loop()
{
  btnState = digitalRead(BUTTON);
  if (btnState == 1 && btnState != prevBtnState) {
    // open the basket
    Serial.println("Is pressed");
    myDFPlayer.play(3); // Please give me trash
    delay(2000);
    flag *= -1;
  }
  if (btnState == 0 && flag < 0) {
    Serial.println("Is not pressed");
    myDFPlayer.play(2);
    delay(1500);
    flag *= -1;
  }
  prevBtnState = btnState;
}
