# TCA_9535 LIBRARY
> This library is specific for 2 boards: tca_9535 one mode and tca_9535 double mode by T302 WORKSHOP.
> This boards are designed by _Nguyen Minh Duc_ for control 12-24V output.

## FOR TCA_9535 SINGLE BOARD
**Use tca_9535 library**
> This library require Wire.h so you should init it first.
> You can init it using `begin_I2C()` .
> And end I2C with `end_i2c()`.
```
pinMode(): to setup mode for board
digitalWrite(): set state for a port
digitalRead(): read state in a port
pinMode(bool mode): is for setup all port in one mode.
digitalWrite(bool state): is for set all port in one state
 ```
 ___

## FOR MUILTi TCA_9535 ONE MODE BOARDS
**Use muiti_tca_9535 library**
> This Library will automatic start I2C 
> Contructor require number of boards
```
TCA_9535Init(): This function will automatic start I2C. If you don't want to use this, just use TCA_9535Init(false).
pinMode(): set up
digitalWrite(): set state for a specific port
digitalWriteBoard(): set state for a board
digitalWriteAllBoards(): set state for all boards
```
___

## FOR MUILTi TCA_9535 DOUBLE MODE BOARDS
**Use double_tca_9535 library**
> This library is similar to multi_tca_9535 library.
> This board use two TCA_9535, one for read and one for write.
> Contructor require number of boards.

```
TCA_9535Init(): This function will automatic start I2C. If you don't want to use this, just use TCA_9535Init(false).
pinMode(): set up
digitalWrite(): set state for a specific port
digitalWriteBoard(): set state for a board
digitalWriteAllBoards(): set state for all boards
digitalRead(): return a specific port state
digitalReadBoard(): return all ports at state 0 in a specific board
digitalReadAllBoard(): return all ports at state 0 in all boards
```
___




 