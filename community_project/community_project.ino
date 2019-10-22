#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define BUTTON 13

int prevBtnState = 0;
int btnState = 0;

int song_list[] = {3, 5, 6, 7, 8, 9, 10, 11};
int len = sizeof(song_list) / sizeof(int);

int index = 0;
int flag = 1;
int count = 0;

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

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
    myDFPlayer.play(4); // Please give me trash
    delay(2000);
    flag *= -1;
  }
  if (btnState == 0 && flag < 0) {
    myDFPlayer.play(1); // Thank you
    delay(2000);
    flag *= -1;
    count++;
  }
  if (count == 3)
  {
    index = random(0, len);
    myDFPlayer.play(song_list[index]); // Any song
    if (btnState == 1) {
      myDFPlayer.pause();  // stop playing music
    }
    count = 0; // reset
  }
  prevBtnState = btnState;
}
