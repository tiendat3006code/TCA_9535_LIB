/*
 *  @author:            Cao Tien Dat
 *  @board designer:    Nguyen Minh Duc
 *  @time:              25/6/2024
 *  @version:           v2.1
 *  @purpose: Arduino library for t302_workshop TCA9535 board.
 *  Header file for TCA_9535 IC.
 *  Run on PlatformIo and Arduino IDE.
 *  This IC use I2C communnicate to read, write, set polarity to 16 ports.
 *  Use this library to control multi TCA9535 boards.
 *  Lowest port must be connect to the board with the lowest address.
 */

#if defined(ESP32)

#ifndef MULTI_TCA_9535_H
#define MULTI_TCA_9535_H

#include "tca_9535.h"

class multi_tca_9535 {
  private:
   uint8_t _boardCount;
   vector<TCA9535*> boards;
   vector<uint8_t> boardsAddress;
   uint8_t numberOfBoardFound;

  public:
   multi_tca_9535(uint8_t numberOfBoards);
   ~multi_tca_9535();
   bool scanI2CAddress();

   //* I2C begin with clock = 100000 by default
   void TCA_Init(bool isbegin_I2C = true);

   //! begin_I2C() use Wire.begin() and setClock(50)
   void begin_I2C();
   //! end_I2C() use Wire.end()
   void end_I2C();

   //! Return the actually number of boards found
   uint8_t getNumberOfBoardsFound() const;

   //* Config all boards at the same mode.
   void pinMode(bool mode);

   //* Set a specific state for a port
   void digitalWrite(int port, bool state);

   //* Set state for all ports int a specific board
   void digitalWriteBoard(int board, bool state);

   //* Set state for all ports
   void digitalWriteAllBoard(bool state);

   //* Set a state for a specific port on a specific board
   void digitalWrite(uint8_t board, uint8_t port, bool state);

   //* Config mode many ports on a specific board
   void pinMode(uint8_t board, vector<int>& ports, bool mode);

   //* Set state for many ports on a specific board
   void digitalWrite(uint8_t board, vector<int>& ports, bool state);
};

#endif  // MULTI_TCA_9535_H

#endif  // ESP32