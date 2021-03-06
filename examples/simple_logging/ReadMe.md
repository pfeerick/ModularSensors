[//]: # ( @page example_simple_logging Simple Logging Example )
# Using ModularSensors to save data to an SD card

This shows the simplest use of a "logger" object.
That is, creating an array of variable objects and then creating a logger object that utilizes those variables to update all of the variable results together and save the data to a SD card.
The processor then goes to sleep between readings.
This example has a placeholder to show users where to insert sensors, which can be found in menu_a_la_carte.ino.

This is the example you should use to deploy a logger somewhere where you don't want or have access to a way of streaming live data and you won't want to upload data to the Monitor My Watershed data portal.
Those lines should be removed when using the example on your own board.

_______

[//]: # ( @section example_simple_logging_walk Walking Through the Code )
# Walking Through the Code

_NOTE:  The code snippets in this walkthrough will not appear on GitHub._

[//]: # ( @tableofcontents )

[//]: # ( Start GitHub Only )
- [Using ModularSensors to save data to an SD card](#using-modularsensors-to-save-data-to-an-sd-card)
- [Walking Through the Code](#walking-through-the-code)
  - [PlatformIO Configuration](#platformio-configuration)
  - [The Complete Code](#the-complete-code)

[//]: # ( End GitHub Only )


[//]: # ( @section example_simple_logging_pio PlatformIO Configuration )
## PlatformIO Configuration

[//]: # ( @include{lineno} simple_logging/platformio.ini )

[//]: # ( @section example_simple_logging_code The Complete Code )
## The Complete Code
