/*
 *  @author:            Cao Tien Dat
 *  @board designer:    Nguyen Minh Duc
 *  @time:              10/1/2024
 *  @version:           v1.1
 *  @purpose: Arduino library for t302_workshop TCA9535 board.
 *  Header file for TCA_9535 IC.
 *  Run on PlatformIo and Arduino IDE.
 *  This IC use I2C communnicate to read, write, set polarity to 16 ports.
 */

#ifndef TCA9535_H
#define TCA9535_H

#include <Arduino.h>
#include <Wire.h>
#include <stdbool.h>
#include <stdint.h>
#include <vector>
#include "config.h"

using namespace std;

class TCA9535 {
  private:
   uint8_t _address;
   TwoWire* _wire;
   uint8_t _mode;

   enum TCA9535_STATUS {
      TCA9535_OK,
      TCA9535_I2C_ERROR,
      TCA9535_PORT_ERROR,
   };

   TCA9535_STATUS _status;

   // myFunction
   void sendData(uint8_t byte, uint8_t byte_);
   uint8_t readRegister(uint8_t byte);

  public:
   TCA9535(uint8_t address, TwoWire* wire = &Wire);
   ~TCA9535();

   //! begin_I2C() use Wire.begin() and setClock(50)
   void begin_I2C();
   //! end_I2C() use Wire.end()
   void end_I2C();

   /*
    * Use this function bellow to control 1 port only.
    * Port 0 to 15.
    * The remaining ports will be in the opposite mode from the installed mode.
    */
   void pinMode(uint8_t port, bool mode);
   void digitalWrite(uint8_t port, bool state);
   /*************************************************************/

   /*
    *  Use this function bellow to control more than 1 ports at the same time.
    *  Port 0 to 15.
    *  All ports must be in the same mode, the remaining ports will be in the
    *  opposite mode from the installed mode.
    */
   void pinMode(vector<int>& ports, bool mode);
   void digitalWrite(vector<int>& ports, bool state);
   /*************************************************************/

   /*
    * Use this function bellow to set the same mode for all port.
    * Port 0 to 15.
    * Can control port using digitalWrite(uint8_t port, bool state) for only 1
    * port. Or use digitalWrite(bool state) to set state to all port.
    */
   void pinMode(bool mode);
   void digitalWrite(bool state);
};

#endif  // TCA9535_H