#include <ezButton.h>

ezButton settStatusKnapp(13);

const int rPin = 9;
const int gPin = 11;
const int bPin = 10;

int fargeStatus = 0;

void setup() {
  Serial.begin(9600);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

void loop() {
  settStatusKnapp.loop();
  if (settStatusKnapp.isPressed()) {
    settFarge();
  }
}

void settFarge() {
  fargeStatus++;
  if (fargeStatus > 3) {
    fargeStatus = 0;
  }
  Serial.println(fargeStatus);
    switch (fargeStatus) {
    case 0:
    visFarge(LOW, LOW, LOW); // lyser ikke
    break;
    case 1:
    visFarge(HIGH, LOW, LOW); // rød
    break;
    case 2:
    visFarge(HIGH, HIGH, LOW); // gul
    break;
    case 3:
    visFarge(LOW, HIGH, LOW); // grønn
    break;
    }
  Serial.print("Ny fargestatus: ");
  Serial.println(fargeStatus);
}


  void visFarge(int rVerdi, int gVerdi, int bVerdi) {
  digitalWrite(rPin, rVerdi);
  digitalWrite(gPin, gVerdi);
  digitalWrite(bPin, bVerdi);
  }
