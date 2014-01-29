/**
 * initialize temperature sensors
 */
void initTempSensors() {

  // set the resolution
  sensors.setResolution(blueTermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(brownTermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(waterTermometer, TEMPERATURE_PRECISION);
}

/**
 * print found (temperatur) devices
 * set flag, wether a termometer is found or not
 */
void locateTempSensors() {

  tftFoundDevices();

  // debug output if no sensors could be found
  if (!sensors.getAddress(blueTermometer, 0)) {
    errorFlag.errorBlue = true;
  }
  if (!sensors.getAddress(brownTermometer, 2)) {
    errorFlag.errorBrown = true;
  } 
  if (!sensors.getAddress(waterTermometer, 1)) {
    errorFlag.errorWater = true; 
  }   
}

/**
 * target temperature (tempTarget) is changable by potentiometer
 */
void setTempTarget(){


  // mapping [0,1023] to [minTemperature,maxTemperature] because 
  // the temperature should not go under minTemperature and not above maxTemperature
  int rawTarget = map(analogRead(poti), 0, 1023, minTemperature, maxTemperature);

  inputData.tempTarget =  (rawTarget) ;
  // TODO: want to get values in quarters, like 24.00, 24.25, 24.50 and 24.75 now from 24.01 to 24.99? 

}
/**
 * save old temperature values
 * get new temperatur values
 */
void getTempData() {

  // TODO: hier fehlerbehandlung einbauen wenn Werte nicht korrekt gelesen werden.
  // falsche werte garnicht ans system weiterreichen!

  oldInputData = inputData;

  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  sensors.requestTemperatures();
  inputData.tempBlue = sensors.getTempC(blueTermometer);
  inputData.tempBrown = sensors.getTempC(brownTermometer);
  inputData.tempWater = sensors.getTempC(waterTermometer);

}


