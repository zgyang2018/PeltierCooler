unsigned long lastTempRequest = 0;


/**
 * initialize temperature sensors
 */
void initTempSensors() {

  // set the resolution
  sensors.setResolution(blueTermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(brownTermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(waterTermometer, TEMPERATURE_PRECISION);

  sensors.setWaitForConversion(false);
  
  sensors.requestTemperatures();
  lastTempRequest = millis(); 
}

/**
 * print found (temperatur) devices
 * set flag, wether a termometer is found or not
 */
void locateTempSensors() {

  tftFoundDevices();
  
  // debug output if no sensors could be found
  if (!sensors.isConnected(blueTermometer)) {
    errorFlag.errorBlue = true;
  }
  if (!sensors.isConnected(brownTermometer)) {
    errorFlag.errorBrown = true;
  } 
  if (!sensors.isConnected(waterTermometer)) {
    errorFlag.errorWater = true; 
  }   
}

/**
 * save old temperature values
 * get new temperatur values
 */
void getTempData() {

  if ((millis() - lastTempRequest) >= DS18B20DELAY) // waited long enough??
  {
    
    // TODO: hier fehlerbehandlung einbauen wenn Werte nicht korrekt gelesen werden.
    // falsche werte garnicht ans system weiterreichen!

    oldInputData = inputData;

    // call sensors.requestTemperatures() to issue a global temperature 
    // request to all devices on the bus
    inputData.tempBlue = sensors.getTempC(blueTermometer);
    inputData.tempBrown = sensors.getTempC(brownTermometer);
    inputData.tempWater = sensors.getTempC(waterTermometer);


    sensors.requestTemperatures(); 
    lastTempRequest = millis();
  }
}

