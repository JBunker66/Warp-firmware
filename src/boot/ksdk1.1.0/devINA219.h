void		initINA219(const uint8_t i2cAddress, uint16_t operatingVoltageMillivolts);
WarpStatus	readSensorRegisterINA219(uint8_t deviceRegister)
WarpStatus	writeSensorRegisterINA219(uint8_t deviceRegister, uint8_t payload)
WarpStatus	configureSensorINA219(uint16_t payload_Config, uint16_t payload_Calibration)
void		printSensorDataINA219(bool hexModeFlag);

// Might need to define a few enums for vars for data translation 