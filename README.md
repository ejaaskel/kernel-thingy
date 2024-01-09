# kernel-thingy
Example kernel module project. The project consists of an Arduino device and accompanying Linux kernel module.

## Arduino device Thingy
Arduino device (named Thingy) is a device that simply sends a string over I2C if data is requested from it.
The I2C address of Thingy is hardcoded to be 0x55.
The string sent by Thingy is pseudorandomly chosen from a list of strings, and the maximum length of the string is 16 characters.
