# piaq hat code

This is code for a PiAQ Hat to read sensors and output data
in a reasonable format for use with a Raspberry Pi

http://pages.cs.wisc.edu/~timc/e/piaq/

The PiAQ is developed by the National Association of REALTORS' CRT Labs.

https://crtlabs.org/

The empty v0.2 boards were ordered from OSHPark and tweaked a bit.

The 'piaq_v3' directory contains code for the ATMega328 on the
PiAQ hat

The 'python' directory contains python code to run on a Raspberry Pi
and consume the serial data provided by the hat, and shove those values
into carbon.
