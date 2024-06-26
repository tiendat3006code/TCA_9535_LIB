#include <multi_tca_9535.h>
#include <tca_9535.h>

multi_tca_9535 tca(2);
int port = 5;

void setup() {
   // put your setup code here, to run once:
   tca.TCA_Init();
   tca.pinMode(WRITE);
   tca.digitalWriteAllBoard(OFF);
}

void loop() {
   // put your main code here, to run repeatedly:
   tca.digitalWrite(port, ON);
   delay(1000);
   tca.digitalWrite(port, OFF);
   delay(1000);
}
