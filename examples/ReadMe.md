[//]: # ( @page page_the_examples Examples )
# Examples Using ModularSensors

These example programs demonstrate how to use the modular sensors library.
Each example has slightly different functionality.

___

[//]: # ( @tableofcontents )

[//]: # ( @section examples_basic Basic Functionality )
## Basic Functionality

[//]: # ( @subsection examples_single_sensor Single Sensor )
## Single Sensor

The [single_sensor](https://github.com/EnviroDIY/ModularSensors/tree/master/examples/single_sensor) example shows making use of the unified set of commands to print data from a MaxBotix ultrasonic range finder to the serial port.
It also shows creating a calculated variable which is the water depth.

[//]: # ( @ref single_sensor.ino )

[//]: # ( @subsection examples_simple_logging Simple Logging )
## Simple Logging

The [simple_logging](https://github.com/EnviroDIY/ModularSensors/tree/master/examples/simple_logging) example shows how to create multiple sensors, create variables for the sensors in a variable array, and log the data from the sensors to an SD card.

[//]: # ( @ref simple_logging.ino )

[//]: # ( @subsection examples_learn_envirodiy Simple Logging for LearnEnviroDIY )
## Simple Logging for LearnEnviroDIY

The [simple_logging_LearnEnviroDIY](https://github.com/EnviroDIY/ModularSensors/tree/master/examples/simple_logging_LearnEnviroDIY) example shows how to create multiple sensors, create variables for the sensors in a variable array, and log the data from the sensors to an SD card.

[//]: # ( @ref simple_logging_LearnEnviroDIY.ino )


___

[//]: # ( @section examples_publishing Publishing Data )
## Publishing Data

[//]: # ( @subsection examples_mmw Publishing to Monitor My Watershed )
## Publishing to Monitor My Watershed

The [logging_to_MMW](https://github.com/EnviroDIY/ModularSensors/tree/master/examples/logging_to_MMW/logging_to_MMW.ino) example uses a Digi XBee in transparent mode to publish data live from a BME280 and Maxim DS18 to the Monitor My Watershed data portal.

[//]: # ( @ref logging_to_MMW.ino )


[//]: # ( @subsection examples_thingspeak Publishing to ThingSpeak )
## Publishing to ThingSpeak

The [logging_to_ThingSpeak](https://github.com/EnviroDIY/ModularSensors/tree/master/examples/logging_to_ThingSpeak) example uses an ESP8266 to send data to ThingSpeak.
It also includes a Meter Hydros 21 (formerly know as a Decagon CTD) and a Campbell OBS3+.

[//]: # ( @ref logging_to_ThingSpeak.ino )

___

[//]: # ( @section examples_complex Calculations and Complex Logging )
## Calculations and Complex Logging

[//]: # ( @subsection examples_baro_rho Barometric Pressure Correction )
## Barometric Pressure Correction

The [baro_rho_correction](https://github.com/EnviroDIY/ModularSensors/tree/master/examples/baro_rho_correction) example demonstrates how to work with calculated variables and calculates water depth by correcting the total pressure measured by a MeaSpec MS5803 with the atmospheric pressure measured by a Bosch BME280 environmental sensor and the temperature measured by a Maxim DS18 temperature probe.

[//]: # ( @ref baro_rho_correction.ino )


[//]: # ( @subsection examples_double_log Multiple Logging Intervals )
## Multiple Logging Intervals

The more complicated [double_logger](https://github.com/EnviroDIY/ModularSensors/tree/master/examples/double_logger) example using two different logger instances to log data at two different intervals, in this case, an AM3215 logging every minute, while checking the battery voltage only every 5 minutes.
This showcases both how to use two different logging instances and how to use some of the functions to set up your own logging loop rather than using the logData() function.

[//]: # ( @ref double_logger.ino )


[//]: # ( @subsection examples_data_saving Minimizing Cell Data Usage )
##  Minimizing Cell Data Usage

The [data_saving](https://github.com/EnviroDIY/ModularSensors/tree/master/examples/data_saving) example is another double logger example, but in this case, both loggers are going at the same interval and the only difference between the loggers is the list of variables.
There are two sets of variables, all coming from Yosemitech sensors.
Because each sensor outputs temperature and we don't want to waste cellular data sending out multiple nearly identical temperature values, we have one logger that logs every possible variable result to the SD card and another logger that sends only unique results to the EnviroDIY data portal.
This example also shows how to stop power draw from an RS485 adapter with automatic flow detection.

[//]: # ( @ref data_saving.ino )


___

[//]: # ( @section examples_drwi DRWI Citizen Science )
## DRWI Citizen Science

[//]: # ( @subsection examples_drwi_2g DRWI CitSci (2G) )
## DRWI CitSci (2G)

The [DRWI_CitSci](https://github.com/EnviroDIY/ModularSensors/tree/master/examples/DRWI_CitSci) example uses the sensors and equipment standard groups participating in the DWRI Citizen Science project with the Stroud Water Research Center.
It includes a Meter Hydros 21 (formerly know as a Decagon CTD), a Campbell OBS3+, and a Sodaq GPRSBee for communication.
The results are saved to the SD card and posted to the Monitor My Watershed data portal.

[//]: # ( @ref DRWI_CitSci.ino )


[//]: # ( @subsection examples_drwi_lte DRWI LTE )
## DRWI LTE

The [DRWI_LTE](https://github.com/EnviroDIY/ModularSensors/tree/master/examples/DRWI_LTE) example uses the sensors and equipment standard groups participating in the DWRI Citizen Science project with the Stroud Water Research Center.
It includes a Meter Hydros 21 (formerly know as a Decagon CTD), a Campbell OBS3+, and a Digi XBee3 LTE-M for communication.
The results are saved to the SD card and posted to the Monitor My Watershed data portal.

[//]: # ( @ref DRWI_LTE.ino )


[//]: # ( @subsection examples_drwi_no_cell DRWI CitSci No Cellular )
## DRWI CitSci No Cellular

The [DRWI_NoCellular](https://github.com/EnviroDIY/ModularSensors/tree/master/examples/DRWI_NoCellular) example uses the sensors and equipment standard to the DWRI Citizen Science grant but omits the data publisher for circumstances where there is no cellular signal.

[//]: # ( @ref DRWI_NoCellular.ino )


___

[//]: # ( @section examples_everything Everything at Once - a la carte )
## Everything at Once - a la carte

[//]: # ( @subsection examples_menu Menu a la carte )
## Menu a la carte

The [menu_a_la_carte](https://github.com/EnviroDIY/ModularSensors/tree/master/examples/menu_a_la_carte) example shows most of the functions of the library at once.
It has code in it for every possible sensor and modem and for both AVR and SAMD boards.
It is also over 1500 lines long.
This examples is intended to be used like an a la carte menu of all possible options where you selected only the portions of code pertenent to you and delete everything else.

[//]: # ( @ref menu_a_la_carte.ino )
