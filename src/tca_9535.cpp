/*
 *  @author:            Cao Tien Dat
 *  @board designer:    Nguyen Minh Duc
 *  @time:              10/1/2024
 *  @version:           v1.1
 *  @purpose: Arduino library for t302_workshop TCA9535 board.
 *  Source file for tca_9535.h.
 *  Run on PlatformIo and Arduino IDE.
 *  This IC use I2C communnicate to read, write, set polarity to 16 ports.
 */

#include "../include/tca_9535.h"

TCA9535::TCA9535(uint8_t address, TwoWire* wire) {
   _address = address;
   _wire = wire;
}

TCA9535::~TCA9535() {}

void TCA9535::begin_I2C() {
#if DEBUG_MODE
   Serial.println("Begin I2C transmission and TCA9535");
#endif
   Wire.begin();
   Wire.setClock(50);
}

void TCA9535::end_I2C() {
   Wire.end();
}

void TCA9535::pinMode(uint8_t port, bool mode) {
   if (port > 15 || port < 0) {
#if DEBUG_MODE
      Serial.println("PIN error");
#endif
      _status = TCA9535_PORT_ERROR;
      return;
   }
   if (port < 8) {
      _mode = CONFIGURATION_PORT_0;
   }
   if ((port > 7)) {
      port = port - 8;
      _mode = CONFIGURATION_PORT_1;
   }
   uint8_t statePort = readRegister(_mode);
   if (statePort != 0)
      return;
   if (mode == READ)
      statePort = 1 << port;
   else if (mode == WRITE) {
      statePort = 254 << port;
   }
   sendData(_mode, statePort);
   _status = TCA9535_OK;
}

void TCA9535::sendData(uint8_t byte, uint8_t byte_) {
   _wire->beginTransmission(_address);
   _wire->write(byte);
   _wire->write(byte_);
   int state = _wire->endTransmission();
   if (state != 0) {
      switch (state) {
         case 1:
#if DEBUG_MODE
            Serial.println("Data too long to fit in transmit buffer.");
#endif
            _status = TCA9535_I2C_ERROR;
            break;
         case 2:
#if DEBUG_MODE
            Serial.println("Received NACK on transmit of address.");
#endif
            _status = TCA9535_I2C_ERROR;
            break;
         case 3:
#if DEBUG_MODE
            Serial.println("Received NACK on transmit of data.");
#endif
            _status = TCA9535_I2C_ERROR;
            break;
         case 4:
#if DEBUG_MODE
            Serial.println("Other error.");
#endif
            _status = TCA9535_I2C_ERROR;
            break;
         case 5:
#if DEBUG_MODE
            Serial.println("Timeout");
#endif
            _status = TCA9535_I2C_ERROR;
            break;
      }
      return;
   }
#if DEBUG_MODE
   Serial.println("Correct in sendData");
#endif
   _status = TCA9535_OK;
}

uint8_t TCA9535::readRegister(uint8_t byte) {
   _wire->beginTransmission(_address);
   _wire->write(byte);
   uint16_t state = _wire->endTransmission();
   if (state != 0) {
      switch (state) {
         case 1:
#if DEBUG_MODE
            Serial.println("Data too long to fit in transmit buffer.");
#endif
            _status = TCA9535_I2C_ERROR;
            break;
         case 2:
#if DEBUG_MODE
            Serial.println("Received NACK on transmit of address.");
#endif
            _status = TCA9535_I2C_ERROR;
            break;
         case 3:
#if DEBUG_MODE
            Serial.println("Received NACK on transmit of data.");
#endif
            _status = TCA9535_I2C_ERROR;
            break;
         case 4:
#if DEBUG_MODE
            Serial.println("Other error.");
#endif
            _status = TCA9535_I2C_ERROR;
            break;
         case 5:
#if DEBUG_MODE
            Serial.println("Timeout");
#endif
            _status = TCA9535_I2C_ERROR;
            break;
      }
   }
#if DEBUG_MODE
   Serial.println("Correct in readRegister");
#endif
   _wire->requestFrom(_address, static_cast<uint8_t>(1));
#if DEBUG_MODE
   Serial.print("Data receive: ");
   Serial.println(_wire->read(), HEX);
#endif
   _status = TCA9535_OK;
   return state;
}

void TCA9535::digitalWrite(uint8_t port, bool state) {
   if (port > 15 || port < 0) {
#if DEBUG_MODE
      Serial.println("PIN error");
#endif
      _status = TCA9535_PORT_ERROR;
      return;
   }
   if (port < 8) {
      _mode = OUTPUT_PORT_0;
   }
   if ((port > 7)) {
      port = port - 8;
      _mode = OUTPUT_PORT_1;
   }
   uint8_t statePort = readRegister(_mode);
   if (statePort != 0)
      return;
   if (state == ON)
      statePort = ~(1 << port);
   else if (state == OFF) {
      statePort = 0xFF;
   }
   sendData(_mode, statePort);
   _status = TCA9535_OK;
}

void TCA9535::pinMode(vector<int>& ports, bool mode) {
   uint8_t dataToSend_0 = 0b00000000;
   uint8_t dataToSend_1 = 0b00000000;
   for (int value : ports) {
      if (value < 8)
         dataToSend_0 |= (1 << value);
      if (value >= 8)
         dataToSend_1 |= (1 << (value - 8));
   }
   if (mode == WRITE) {
      if (dataToSend_0 != 0) {
         dataToSend_0 = ~dataToSend_0;
         _mode = CONFIGURATION_PORT_0;
         sendData(_mode, dataToSend_0);
      }
      if (dataToSend_1 != 0) {
         dataToSend_1 = ~dataToSend_1;
         _mode = CONFIGURATION_PORT_1;
         sendData(_mode, dataToSend_1);
      }
   } else if (mode == READ) {
      if (dataToSend_0 != 0) {
         _mode = CONFIGURATION_PORT_0;
         sendData(_mode, dataToSend_0);
      }
      if (dataToSend_1 != 0) {
         _mode = CONFIGURATION_PORT_1;
         sendData(_mode, dataToSend_1);
      }
   }
#if DEBUG_MODE
   Serial.print("Data to send port_0: ");
   Serial.println(dataToSend_0, BIN);
   Serial.print("Data to send port_1: ");
   Serial.println(dataToSend_1, BIN);
#endif
}

void TCA9535::digitalWrite(vector<int>& ports, bool state) {
   uint8_t dataToSend_0 = 0b00000000;
   uint8_t dataToSend_1 = 0b00000000;
   for (int value : ports) {
      if (value < 8)
         dataToSend_0 |= (1 << value);
      if (value >= 8)
         dataToSend_1 |= (1 << (value - 8));
   }
   if (state == ON) {
      if (dataToSend_0 != 0) {
         dataToSend_0 = ~dataToSend_0;
         _mode = CONFIGURATION_PORT_0;
         sendData(_mode, dataToSend_0);
      }
      if (dataToSend_1 != 0) {
         dataToSend_1 = ~dataToSend_1;
         _mode = CONFIGURATION_PORT_1;
         sendData(_mode, dataToSend_1);
      }
   } else if (state == OFF) {
      if (dataToSend_0 != 0) {
         _mode = CONFIGURATION_PORT_0;
         sendData(_mode, 0xFF);
      }
      if (dataToSend_1 != 0) {
         _mode = CONFIGURATION_PORT_1;
         sendData(_mode, 0xFF);
      }
   }
#if DEBUG_MODE
   Serial.print("Data to send port_0: ");
   Serial.println(dataToSend_0, BIN);
   Serial.print("Data to send port_1: ");
   Serial.println(dataToSend_1, BIN);
#endif
}

void TCA9535::pinMode(bool mode) {
   if (mode == READ) {
      sendData(CONFIGURATION_PORT_0, 0xFF);
      sendData(CONFIGURATION_PORT_1, 0xFF);
   }
   if (mode == WRITE) {
      sendData(CONFIGURATION_PORT_0, 0x00);
      sendData(CONFIGURATION_PORT_1, 0x00);
   }
}

void TCA9535::digitalWrite(bool state) {
   if (state == ON) {
      sendData(OUTPUT_PORT_0, 0x00);
      sendData(OUTPUT_PORT_1, 0x00);
   }
   if (state == OFF) {
      sendData(OUTPUT_PORT_0, 0xFF);
      sendData(OUTPUT_PORT_1, 0xFF);
   }
}