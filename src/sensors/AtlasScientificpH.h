/*
 * @file AtlasScientificpH.h
 * @brief This file contains the AtlasScientificRTD subclass of the AtlasParent
 * sensor class along with the variable subclass AtlasScientificpH_pH.  These
 * are used for any sensor attached to an Atlas EZO pH circuit.
 *
 * The output from the Atlas Scientifc pH is the temperature in degrees C.
 *     Accuracy is ± 0.002
 *     Range is 0.001 − 14.000
 *     Resolution is 0.001
 *
 * Part of the EnviroDIY ModularSensors library for Arduino
 * @copyright 2020 Stroud Water Research Center
 * @author Initial developement for Atlas Sensors was done by Adam Gold
 * Files were edited by Sara Damiano <sdamiano@stroudcenter.org>
 */

// Header Guards
#ifndef SRC_SENSORS_ATLASSCIENTIFICPH_H_
#define SRC_SENSORS_ATLASSCIENTIFICPH_H_

// Included Dependencies
#include "sensors/AtlasParent.h"

// I2C address
#define ATLAS_PH_I2C_ADDR 0x63  // 99

// Sensor Specific Defines
#define ATLAS_PH_NUM_VARIABLES 1

#define ATLAS_PH_WARM_UP_TIME_MS 850  // 846 in SRGD Tests
#define ATLAS_PH_STABILIZATION_TIME_MS 0
// NOTE:  Manual says measurement takes 900 ms, but in SRGD tests, no result was
// available until 1656 ms
#define ATLAS_PH_MEASUREMENT_TIME_MS 1660

#define ATLAS_PH_RESOLUTION 3
#define ATLAS_PH_VAR_NUM 0

// The main class for the Atlas Scientific pH temperature sensor
class AtlasScientificpH : public AtlasParent {
 public:
    explicit AtlasScientificpH(int8_t  powerPin,
                               uint8_t i2cAddressHex = ATLAS_PH_I2C_ADDR,
                               uint8_t measurementsToAverage = 1)
        : AtlasParent(powerPin, i2cAddressHex, measurementsToAverage,
                      "AtlasScientificpH", ATLAS_PH_NUM_VARIABLES,
                      ATLAS_PH_WARM_UP_TIME_MS, ATLAS_PH_STABILIZATION_TIME_MS,
                      ATLAS_PH_MEASUREMENT_TIME_MS) {}
    ~AtlasScientificpH() {}
};

// The class for the pH variable
class AtlasScientificpH_pH : public Variable {
 public:
    explicit AtlasScientificpH_pH(AtlasScientificpH* parentSense,
                                  const char*        uuid    = "",
                                  const char*        varCode = "AtlaspH")
        : Variable(parentSense, (const uint8_t)ATLAS_PH_VAR_NUM,
                   (uint8_t)ATLAS_PH_RESOLUTION, "pH", "pH", varCode, uuid) {}
    AtlasScientificpH_pH()
        : Variable((const uint8_t)ATLAS_PH_VAR_NUM,
                   (uint8_t)ATLAS_PH_RESOLUTION, "pH", "pH", "AtlaspH") {}
    ~AtlasScientificpH_pH() {}
};

#endif  // SRC_SENSORS_ATLASSCIENTIFICPH_H_
