/*
 *  @author:            Cao Tien Dat
 *  @board designer:    Nguyen Minh Duc
 *  @time:              22/6/2024
 *  @version:           v2.2
 *  @purpose: Arduino library for t302_workshop TCA9535 double mode board.
 *  Source file for TCA_9535 IC.
 *  Run on PlatformIo and Arduino IDE.
 *  This IC use I2C communnicate to read, write, set polarity to 16 ports.
 *  Use this library to control multi TCA9535 boards.
 *  Lowest port must be connect to the board with the lowest address.
 */

#if defined(ESP32)

#include "double_mode_tca.h"

double_mode_tca::double_mode_tca(uint8_t numberOfBoards) {
   _boardCount = numberOfBoards * 2;
}

void double_mode_tca::TCA_Init(bool isbegin_I2C) {
   if (isbegin_I2C) {
      begin_I2C();
   }
   delay(1000);
   if (!scanI2CAddress())
      return;
   for (int i = 0; i < _boardCount; i++) {
      TCA9535* tca = new TCA9535(boardsAddress.at(i));
      boards.push_back(tca);
   }
}

double_mode_tca::~double_mode_tca() {
   boardsAddress.clear();
   for (TCA9535* tca : boards) {
      delete tca;
      tca = nullptr;
   }
   boards.clear();
}

bool double_mode_tca::scanI2CAddress() {
   for (uint8_t address = TCA_MIN_ADDRESS; address <= TCA_MAX_ADDRESS;
        address++) {
      Wire.beginTransmission(address);
      int error = Wire.endTransmission();
      if (error == 0) {
         boardsAddress.push_back(address);
      }
   }
   if (boardsAddress.size() == _boardCount) {
      return true;
   } else {
      return false;
   }
}

void double_mode_tca::begin_I2C() {
   Wire.begin();
   Wire.setClock(50);
}

void double_mode_tca::end_I2C() {
   Wire.end();
}

void double_mode_tca::pinMode() {
   for (int i = 0; i < boards.size(); i++) {
      if ((i % 2) == 0)
         boards.at(i)->pinMode(WRITE);
      else
         boards.at(i)->pinMode(READ);
   }
}

void double_mode_tca::digitalWrite(int port, bool state) {
   int boardNumber = port / 16 * 2;
   int portOnBoard = port % 16;
   boards[boardNumber]->digitalWrite(portOnBoard, state);
}

void double_mode_tca::digitalWriteBoard(int board, bool state) {
   boards[board * 2]->digitalWrite(state);
}

void double_mode_tca::digitalWriteAllBoard(bool state) {
   for (int i = 0; i < boards.size(); i += 2) {
      boards[i]->digitalWrite(state);
   }
}

void double_mode_tca::digitalWrite(uint8_t board, uint8_t port, bool state) {
   boards.at(board * 2)->digitalWrite(port, state);
}

int double_mode_tca::digitalRead(int port) {
   int boardNumber = port / 16 * 2 + 1;
   int portOnBoard = port % 16;
   return boards[boardNumber]->digitalRead(portOnBoard);
}

vector<uint8_t> double_mode_tca::digitalReadBoard(uint8_t board) {
   vector<uint8_t> portState;
   if ((board % 2) == 0)
      return portState;
   for (uint8_t state : boards[board * 2 + 1]->digitalRead()) {
      portState.push_back(state + 16 * (board - 1) / 2);
   }
   return portState;
}

vector<uint8_t> double_mode_tca::digitalReadAllBoards() {
   vector<uint8_t> portState;
   for (int i = 1; i <= boards.size(); i += 2) {
      for (uint8_t state : boards[i]->digitalRead()) {
         portState.push_back(state + 16 * (i - 1) / 2);
      }
   }
   return portState;
}

#endif  // ESP32