/*
 *  @author:            Cao Tien Dat
 *  @board designer:    Nguyen Minh Duc
 *  @time:              26/6/2024
 *  @version:           v2.2
 *  @purpose: Arduino library for t302_workshop TCA9535 double mode board.
 *  Header file for TCA_9535 IC.
 *  Run on PlatformIo and Arduino IDE.
 *  This IC use I2C communnicate to read, write, set polarity to 16 ports.
 *  Use this library to control multi TCA9535 boards.
 *  Lowest port must be connect to the board with the lowest address.
 */

#if defined(ESP32)
#ifndef DOUBLE_MODE_TCA_H
#define DOUBLE_MODE_TCA_H

#include "tca_9535.h"

class double_mode_tca {
  private:
   uint8_t _boardCount;
   vector<TCA9535*> boards;
   vector<uint8_t> boardsAddress;

  public:
   double_mode_tca(uint8_t numberOfBoards);
   ~double_mode_tca();
   bool scanI2CAddress();

   //* I2C begin with clock = 50 by default
   void TCA_Init(bool isbegin_I2C = true);

   //! begin_I2C() use Wire.begin() and setClock(50)
   void begin_I2C();
   //! end_I2C() use Wire.end()
   void end_I2C();

   //* Config all boards at the same mode.
   void pinMode();

   //* Set a specific state for a port
   void digitalWrite(int port, bool state);

   //* Read a specific port
   int digitalRead(int port);

   //* Set state for all ports int a specific board
   void digitalWriteBoard(int board, bool state);

   //* Read a specific board
   vector<uint8_t> digitalReadBoard(uint8_t board);

   //* Read all boards
   vector<uint8_t> digitalReadAllBoards();

   //* Set state for all ports
   void digitalWriteAllBoard(bool state);

   //* Set a state for a specific port on a specific board
   void digitalWrite(uint8_t board, uint8_t port, bool state);

};

#endif  // DOUBLE_MODE_TCA_H
#endif  // ESP32