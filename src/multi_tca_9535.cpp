/*
 *  @author:            Cao Tien Dat
 *  @board designer:    Nguyen Minh Duc
 *  @time:              10/1/2024
 *  @version:           v1.1
 *  @purpose: Arduino library for t302_workshop TCA9535 board.
 *  Header file for TCA_9535 IC.
 *  Run on PlatformIo and Arduino IDE.
 *  This IC use I2C communnicate to read, write, set polarity to 16 ports.
 *  Use this library to control multi TCA9535 boards.
 *  Lowest port must be connect to the board with the lowest address.
 */

#if defined(ESP32)

#include "multi_tca_9535.h"

multi_tca_9535::multi_tca_9535(uint8_t numberOfBoards) {
   _boardCount = numberOfBoards;
}

void multi_tca_9535::TCA_Init(bool isbegin_I2C) {
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

multi_tca_9535::~multi_tca_9535() {
   boardsAddress.clear();
   for (TCA9535* tca : boards) {
      delete tca;
      tca = nullptr;
   }
   boards.clear();
}

bool multi_tca_9535::scanI2CAddress() {
   for (uint8_t address = TCA_MIN_ADDRESS; address <= TCA_MAX_ADDRESS;
        address++) {
      Wire.beginTransmission(address);
      int error = Wire.endTransmission();
      if (error == 0) {
#if DEBUG_MODE
         Serial.print("address: ");
         Serial.println(address, HEX);
#endif
         boardsAddress.push_back(address);
      }
   }
   if (boardsAddress.size() == _boardCount) {
#if DEBUG_MODE
      Serial.println("Boards correct");
#endif
      return true;
   } else {
#if DEBUG_MODE
      Serial.println("Boards not correct or duplicate address");
#endif
      return false;
   }
}

void multi_tca_9535::begin_I2C() {
#if DEBUG_MODE
   Serial.println("Begin I2C transmission and TCA9535");
#endif
   Wire.begin();
   Wire.setClock(50);
}

void multi_tca_9535::end_I2C() {
   Wire.end();
}

void multi_tca_9535::pinMode(bool mode) {
   for (TCA9535* tca : boards) {
      tca->pinMode(mode);
   }
}

void multi_tca_9535::digitalWrite(int port, bool state) {
   int boardNumber = port / 16;
   int portOnBoard = port % 16;
   boards.at(boardNumber)->digitalWrite(portOnBoard, state);
}

void multi_tca_9535::digitalWriteBoard(int board, bool state) {
   boards.at(board)->digitalWrite(state);
}

void multi_tca_9535::digitalWriteAllBoard(bool state) {
   for (TCA9535* tca : boards) {
      tca->digitalWrite(state);
   }
}

void multi_tca_9535::digitalWrite(uint8_t board, uint8_t port, bool state) {
   boards.at(board)->digitalWrite(port, state);
}

void multi_tca_9535::pinMode(uint8_t board, vector<int>& ports, bool mode) {
   for (int port : ports) {
      if ((port < 0) || (port > 15))
         return;
   }
   boards.at(board)->pinMode(ports, mode);
}

void multi_tca_9535::digitalWrite(uint8_t board,
                                  vector<int>& ports,
                                  bool state) {
   for (int port : ports) {
      if ((port < 0) || (port > 15))
         return;
   }
   boards.at(board)->digitalWrite(ports, state);
}

#endif  // ESP32
