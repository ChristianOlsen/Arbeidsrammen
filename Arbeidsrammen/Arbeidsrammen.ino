#include <QList.h>
#include <LiquidCrystal.h>
#include <ezButton.h>

const int DBtime = 80;

QList<String> gjoremaal;
LiquidCrystal skjermer[2] = {LiquidCrystal (6, 7, 5, 4, 3, 2),
                             LiquidCrystal (13, 12, 11, 10, 9, 8)
                            };
int antSkjermer = sizeof(skjermer) / sizeof(LiquidCrystal);

ezButton fjernGMKnapp(A0);
ezButton navigerOppKnapp(A1);
ezButton navigerNedKnapp(A2);
ezButton settStatusKnapp(A4);

int gjoremaalValg = 1;
int fargeStatus = 0;


void setup() {
  Serial.begin(9600);

  leggTilGM("Sortere mapper");
  leggTilGM("Oppdater kalender");
  leggTilGM("Bestill permer");
  leggTilGM("Oppdater klient02");
  leggTilGM("Hjelp Kaare med oppgave");
  fjernGM();

  visTekst();
}

void loop() {
  if (gjoremaal.size() != 0) {
    fjernGMKnapp.loop();
    if (fjernGMKnapp.isPressed()) {
      fjernGM();
    }
    navigerOppKnapp.loop();
    if (navigerOppKnapp.isPressed()) {
      Serial.println("opp pressed");
      navigerOpp();
    }
    navigerNedKnapp.loop();
    if (navigerNedKnapp.isPressed()) {
      Serial.println("ned pressed");
      navigerNed();
    }
  }

  settStatusKnapp.loop();
  if (settStatusKnapp.isPressed()) {
    settFarge();
  }
  //endreFarge();

}

void leggTilGM(String tekst) {
  gjoremaal.push_back(tekst);
  Serial.print("La til gjoremaal: ");
  Serial.println(gjoremaal.back());
  visTekst();
}

void fjernGM() {
  Serial.print("Fjerner: ");
  Serial.println(gjoremaal.get(gjoremaalValg));
  gjoremaal.clear(gjoremaalValg);
  Serial.println("Gjoremaal er naa:");
  for (int i = 0; i < gjoremaal.size(); i++) {
    Serial.println(gjoremaal.get(i));
  }
  visTekst();
}

void visTekst() {
  for (int i = 0; i < antSkjermer; i++) {
    skjermer[i].clear();
  }
  if (gjoremaal.size() == 0) {
    skjermer[0].begin(16, 2);
    skjermer[0].setCursor(0, 0);
    skjermer[0].print("Ingen gjoremaal");
  } else {
    int valg = gjoremaalValg;
    for (int i = 0; i < antSkjermer; i++) {
      if (valg >= gjoremaal.size()) {
        valg = 0;
      }
      skjermer[i].begin(16, 2);
      skjermer[i].setCursor(0, 0);
      skjermer[i].print(gjoremaal.get(valg));
      valg++;
      //Serial.print(gjoremaal.get(valg));
    }
  }

}

void navigerOpp() {
  gjoremaalValg++;
  if (gjoremaalValg >= gjoremaal.size()) {
    gjoremaalValg = 0;
  }
  Serial.print("GMvalg: ");
  Serial.println(gjoremaalValg);
  visTekst();
}

void navigerNed() {
  gjoremaalValg--;
  if (gjoremaalValg < 0) {
    gjoremaalValg = gjoremaal.size() - 1;
  }
  Serial.print("GMvalg: ");
  Serial.println(gjoremaalValg);
  visTekst();
}

// Denne koden brukes i den andre arduinoen, 
// grunnet mangel på pins
void settFarge() {
  fargeStatus++;
  if (fargeStatus > 3) {
    fargeStatus = 0;
  }
  /*
    switch (fargeStatus) {
    case 0:
    visFarge(LOW, LOW, LOW);
    break;
    case 1:
    visFarge(HIGH, LOW, LOW);
    break;
    case 2:
    visFarge(HIGH, HIGH, LOW);
    break;
    case 3:
    visFarge(LOW, HIGH, LOW);
    break;
    }
  */
  Serial.print("Ny fargestatus: ");
  Serial.println(fargeStatus);
}

/*
  void visFarge(int rVerdi, int gVerdi, int bVerdi) {
  digitalWrite(rPin, rVerdi);
  digitalWrite(gPin, gVerdi);
  digitalWrite(bPin, bVerdi);
  }
*/
