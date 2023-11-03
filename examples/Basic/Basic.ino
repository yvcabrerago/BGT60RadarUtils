#include <bgt60-ino.hpp>
#include <bgt60-platf-ino.hpp>
#include <BGT60RadarUtils.h> 

// Configure the correct terminals!
#define TD 5
#define PD 6

Bgt60Ino radarShield(TD, PD);
BGT60RadarUtils radar(&radarShield);

void setup() {
  Serial.begin(115200);
  Error_t init_status = radarShield.init();
  if (init_status == OK) {
    Serial.println("radar init good");
  }
  else {
    Serial.println("radar init bad");
  }
  radar.StatusFunctions[Bgt60::NO_DIR][Bgt60::DEPARTING] = &Fun1;
  radar.StatusFunctions[Bgt60::NO_DIR][Bgt60::APPROACHING] = &Fun2;
  radar.StatusFunctions[Bgt60::DEPARTING][Bgt60::NO_DIR] = &Fun3;
  radar.StatusFunctions[Bgt60::DEPARTING][Bgt60::APPROACHING] = &Fun4;
  radar.StatusFunctions[Bgt60::APPROACHING][Bgt60::NO_DIR] = &Fun5;
  radar.StatusFunctions[Bgt60::APPROACHING][Bgt60::DEPARTING] = &Fun6;
}

void Fun1(){Serial.println("From no dir to departing");}
void Fun2(){Serial.println("From no dir to approaching");}
void Fun3(){Serial.println("From departing to no dir");}
void Fun4(){Serial.println("From departing to approaching");}
void Fun5(){Serial.println("From approaching to no dir");}
void Fun6(){Serial.println("From approaching to departing");}

void loop() {
  delay(3000);
  radar.checkStatus();
}
