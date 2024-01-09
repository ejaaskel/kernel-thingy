# kernel-thingy
Example kernel module project. The project consists of an Arduino device and accompanying Linux kernel module.

## Arduino device Thingy
Arduino device (named Thingy) is a device that simply sends a string over I2C if data is requested from it.
The I2C address of Thingy is hardcoded to be 0x55.
The string sent by Thingy is pseudorandomly chosen from a list of strings, and the maximum length of the string is 16 characters.

## Thingy kernel module
The kernel module for Thingy is an I2C device driver that provides `randomstring` sysfs attribute file for receiving a random string.
The module performs an I2C receive when the sysfs attribute is read. The file cannot be written into.

The kernel module does not perform any automatic detection, so Thingy device has to be manually added to I2C bus.
In practice, this means that the following command should be run after the module is loaded:

```
echo thingy 0x55 > /sys/<path>/<to>/<i2c>/<bus>/new_device
```

The module has been tested on Linux Kernel 6.1.21 on Raspberry Pi OS running on Raspberry Pi 2.
