/*
 *KellerParent.cpp
 *This file is part of the EnviroDIY modular sensors library for Arduino
 *
 *Initial library developement done by Anthony Aufdenkampe <aaufdenkampe@limno.com>
 *
 *This file is for Modbus communication to  Keller pressure and water level sensors
 *of Series 30, Class 5, Group 20 (such as the KellerAcculevel)
 *that are Software version 5.20-12.28 and later (i.e. made after the 2012 in the 28th week)
 *Only tested the Acculevel
*
 *Documentation for the Keller Protocol commands and responses, along with
 *information about the various variables, can be found
 *in the EnviroDIY KellerModbus library at:
 * https://github.com/EnviroDIY/KellerModbus
*/

#include "KellerParent.h"

// The constructor - need the sensor type, modbus address, power pin, stream for data, and number of readings to average
KellerParent::KellerParent(byte modbusAddress, Stream* stream,
               int8_t powerPin, int8_t powerPin2, int8_t enablePin, uint8_t measurementsToAverage,
               kellerModel model, const char *sensName, int numVariables,
               uint32_t warmUpTime_ms, uint32_t stabilizationTime_ms, uint32_t measurementTime_ms)
    : Sensor(sensName, numVariables,
             warmUpTime_ms, stabilizationTime_ms, measurementTime_ms,
             powerPin, -1, measurementsToAverage)
{
    _model = model;
    _modbusAddress = modbusAddress;
    _stream = stream;
    _RS485EnablePin = enablePin;
    _powerPin2 = powerPin2;
}
KellerParent::KellerParent(byte modbusAddress, Stream& stream,
               int8_t powerPin, int8_t powerPin2, int8_t enablePin, uint8_t measurementsToAverage,
               kellerModel model, const char *sensName, int numVariables,
               uint32_t warmUpTime_ms, uint32_t stabilizationTime_ms, uint32_t measurementTime_ms)
    : Sensor(sensName, numVariables,
             warmUpTime_ms, stabilizationTime_ms, measurementTime_ms,
             powerPin, -1, measurementsToAverage)
{
    _model = model;
    _modbusAddress = modbusAddress;
    _stream = &stream;
    _RS485EnablePin = enablePin;
    _powerPin2 = powerPin2;
}


// The sensor installation location on the Mayfly
String KellerParent::getSensorLocation(void)
{
    String sensorLocation = F("modbus_0x");
    if (_modbusAddress< 16) sensorLocation += "0";
    sensorLocation += String(_modbusAddress, HEX);
    return sensorLocation;
}


bool KellerParent::setup(void)
{
    bool retVal = Sensor::setup();  // this will set pin modes and the setup status bit
    if (_RS485EnablePin >= 0) pinMode(_RS485EnablePin, OUTPUT);
    if (_powerPin2 >= 0) pinMode(_powerPin2, OUTPUT);

    #if defined(DEEP_DEBUGGING_SERIAL_OUTPUT)
        sensor.setDebugStream(&DEEP_DEBUGGING_SERIAL_OUTPUT);
    #endif

    // This sensor begin is just setting more pin modes, etc, no sensor power required
    // This realy can't fail so adding the return value is just for show
    retVal &= sensor.begin(_modbusAddress, _stream, _RS485EnablePin);

    return retVal;
}


// This turns on sensor power
void KellerParent::powerUp(void)
{
    if (_powerPin >= 0)
    {
        MS_DBG(F("Powering "), getSensorName(), F(" at "), getSensorLocation(),
               F(" with pin "), _powerPin, '\n');
        digitalWrite(_powerPin, HIGH);
        // Mark the time that the sensor was powered
        _millisPowerOn = millis();
    }
    if (_powerPin2 >= 0)
    {
        MS_DBG(F("Applying secondary power to "), getSensorName(), F(" at "), getSensorLocation(),
               F(" with pin "), _powerPin2, '\n');
        digitalWrite(_powerPin2, HIGH);
    }
    if (_powerPin < 0 && _powerPin2 < 0)
    {
        MS_DBG(F("Power to "), getSensorName(), F(" at "), getSensorLocation(),
               F(" is not controlled by this library.\n"));
    }
    // Set the status bit for sensor power attempt (bit 1) and success (bit 2)
    _sensorStatus |= 0b00000110;
}


// This turns off sensor power
void KellerParent::powerDown(void)
{
    if (_powerPin >= 0)
    {
        MS_DBG(F("Turning off power to "), getSensorName(), F(" at "),
               getSensorLocation(), F(" with pin "), _powerPin, '\n');
        digitalWrite(_powerPin, LOW);
        // Unset the power-on time
        _millisPowerOn = 0;
    }
    if (_powerPin2 >= 0)
    {
        MS_DBG(F("Turning off secondary power to "), getSensorName(), F(" at "),
               getSensorLocation(), F(" with pin "), _powerPin2, '\n');
        digitalWrite(_powerPin2, LOW);
    }
    if (_powerPin < 0 && _powerPin2 < 0)
    {
        MS_DBG(F("Power to "), getSensorName(), F(" at "), getSensorLocation(),
               F(" is not controlled by this library.\n"));
    }
    // Unset the status bits for sensor power (bits 1 & 2),
    // activation (bits 3 & 4), and measurement request (bits 5 & 6)
    _sensorStatus &= 0b10000001;
}


bool KellerParent::addSingleMeasurementResult(void)
{
    bool success = false;

    // Initialize float variables
    float waterPressureBar = -9999;
    float waterTempertureC = -9999;
    float waterDepthM = -9999;
    float waterPressure_mBar = -9999;

    // Check if BOTH a measurement start attempt was made (status bit 5 set)
    // AND that attempt was successful (bit 6 set, _millisMeasurementRequested > 0)
    // Only go on to get a result if it is
    if (bitRead(_sensorStatus, 5) && bitRead(_sensorStatus, 6) && _millisMeasurementRequested > 0)
    {
        // Get Values
        MS_DBG(F("Get Values from"), getSensorName(), F(" at "),
               getSensorLocation(), F(":\n"));
        success = sensor.getValues(waterPressureBar, waterTempertureC);
        waterDepthM = sensor.calcWaterDepthM(waterPressureBar, waterTempertureC);  // float calcWaterDepthM(float waterPressureBar, float waterTempertureC)

        // Fix not-a-number values
        if (!success or isnan(waterPressureBar)) waterPressureBar = -9999;
        if (!success or isnan(waterTempertureC)) waterTempertureC = -9999;
        if (!success or isnan(waterDepthM)) waterDepthM = -9999;

        // For waterPressureBar, convert bar to millibar
        if (waterPressureBar != -9999) waterPressure_mBar = 1000*waterPressureBar;

        MS_DBG(F("    Pressure_mbar:"), waterPressure_mBar, '\n');
        MS_DBG(F("    Temp_C: "), waterTempertureC, '\n');
        MS_DBG(F("    Height_m:"), waterDepthM, '\n');
    }
    else MS_DBG(getSensorName(), F(" at "), getSensorLocation(),
         F(" is not currently measuring!\n"));

    // Put values into the array
    verifyAndAddMeasurementResult(KELLER_PRESSURE_VAR_NUM, waterPressure_mBar);
    verifyAndAddMeasurementResult(KELLER_TEMP_VAR_NUM, waterTempertureC);
    verifyAndAddMeasurementResult(KELLER_HEIGHT_VAR_NUM, waterDepthM);

    // Unset the time stamp for the beginning of this measurement
    _millisMeasurementRequested = 0;
    // Unset the status bits for a measurement request (bits 5 & 6)
    _sensorStatus &= 0b10011111;

    // Return true when finished
    return success;
}
