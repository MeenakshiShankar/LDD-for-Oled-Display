# LDD-for-Oled-Display

This repository contains the code files for an Linux device Driver written for SSD1306 OLED display.

# Linux Device Driver for OLED Display

This project implements a Linux kernel device driver for controlling an OLED display using the SSD1306 controller via I2C.

## Features

- **I2C communication**: The driver communicates with the OLED display over I2C using the Linux kernel I2C subsystem.
- **OLED Initialization**: Initializes the SSD1306 OLED display and provides basic functionality such as writing text and displaying images.
- **Custom Logos**: The driver supports displaying pre-defined logos (e.g., `iisc_logo`, `india_logo`, and `smile_logo`).


## Requirements

- Linux kernel 4.x or higher
- I2C interface on your hardware (e.g., Raspberry Pi or other embedded systems)
- SSD1306 OLED display module

### Procedure

1. **Build the kernel module**:
   Make sure you have the Linux kernel headers installed. Then run:
   ```bash
   make
   ```

2. **Load the driver**:
   After successful compilation, load the driver into the kernel:
   ```bash
   sudo insmod oled_driver.ko
   ```

3. **Unload the driver**:
   To remove the driver from the kernel:
   ```bash
   sudo rmmod oled_driver
   ```

4. **Check the kernel logs**:
   View the kernel log to ensure that the driver was loaded and initialized properly:
   ```bash
   dmesg | tail
   ```

## File Structure

- `oled_driver.c`: Main source code for the OLED display driver.
- `oled.h`: Header file with OLED command definitions and helper functions.
- `Makefile`: Makefile to compile the driver.

## Driver Details

- The driver sets up an I2C client to communicate with the OLED display.
- The `probe` function initializes the display by sending the necessary initialization commands via I2C.
- The driver provides functions to display text and images, such as `SSD1306_String()` and `oled_print_logo()`.

## Example Logos

The driver includes pre-defined logos that can be displayed on the OLED:

- **iisc_logo**: Displays the IISc logo.
- **india_logo**: Displays the India logo.
- **smile_logo**: Displays a smiley logo.
## Result ans Setup
 <a>
    <img src="LDD setup.jpeg" alt="Logo" width="300" height="400">
    <img src="iisc logo.jpeg" alt="Logo" width="300" height="400">
  </a>




