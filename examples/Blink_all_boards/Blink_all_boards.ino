#include <tca_9535.h>
#include <multi_tca_9535.h>

//Number of boards
multi_tca_9535 tca(2);

void setup() {
  // put your setup code here, to run once:
  tca.TCA_Init();
  tca.pinMode(WRITE);
  tca.digitalWriteAllBoard(OFF);
}

void loop() {
  // put your main code here, to run repeatedly:
  tca.digitalWriteAllBoard(ON);
  delay(1000);
  tca.digitalWriteAllBoard(OFF);
  delay(1000);
}
