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

#ifndef CONFIG_H
#define CONFIG_H

// TCA9535 ADDRESS & BOARDS COUNT
#define TCA_MIN_ADDRESS           0x20
#define TCA_MAX_ADDRESS           0x27

//* COMMAND BYTES
#define INPUT_PORT_0              0x00
#define INPUT_PORT_1              0x01
#define OUTPUT_PORT_0             0x02
#define OUTPUT_PORT_1             0x03
#define POLARITY_INVERSION_PORT_0 0x04
#define POLARITY_INVERSION_PORT_1 0x05
#define CONFIGURATION_PORT_0      0x06
#define CONFIGURATION_PORT_1      0x07

//* PINS
#define TCA_POO                   0
#define TCA_P01                   1
#define TCA_P02                   2
#define TCA_P03                   3
#define TCA_P04                   4
#define TCA_P05                   5
#define TCA_P06                   6
#define TCA_P07                   7
#define TCA_P10                   8
#define TCA_P11                   9
#define TCA_P12                   10
#define TCA_P13                   11
#define TCA_P14                   12
#define TCA_P15                   13
#define TCA_P16                   14
#define TCA_P17                   15

// BAUDRATE
#define BAUDRATE                  115200

/****** USE THIS VARIABLES BELLOW TO AVOID CONSFUSION  *******
**************************************************************/
//? ON OR OFF
#define ON                        true
#define OFF                       false

//? READ OR WRITES
#define READ                      1
#define WRITE                     0
/**************************************************************/

#endif  // CONFIG_H