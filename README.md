# TheDevice

TheDevice is a Peer Award Trophy that evolves with each person who wins the Peer Award. Each winner adds new functionality to the device, creating a growing legacy of contributions.

## Current Functionality

- Flashes "TODYL" in Morse Code.
- Flashes lights back and forth.
- Increasingly speeds up lights from left to right.
- Flashes alternating letters.
- Has a breathing effect.
- Lights up each letter of **t-o-d-y-l**, followed by the logo.
- The logo flashes twice.

## Technologies

- Written in **C**.
- Programmed onto a microcontroller.

## Setup Instructions **Note:**

This project **does not support Windows**. Use macOS or Linux.

### Installation

1. **For macOS:**

   brew install picocom stlink
   brew install --cask gcc-arm-embedded

1. **For Linux:**

   sudo apt-get install build-essential stlink-tools gcc-arm-none-eabi picocom

1. Connect the provided SWD programmer via USB to your machine.
1. Attach the programmer to the trophy using the JST jumper 4.
1. Ensure light is on on the SWD programmer, indicating it's connected.
1. To compile: `bash make `
1. Power on the trophy by pressing the mode button.
1. To install the compiled code: `bash make install `

## Debugging & Development

**Probe the device to check if it's connected:** (device must be powered on by pressing the mode button) `bash st-info --probe `
**Reset the device** `bash st-flash reset `
**Hard reset (if needed)** Remove the battery for approximately 5 seconds and reinsert it (ensure the correct polarity to avoid damage). **Warning:** Inserting the battery the wrong way will fry the device.

For active development, comment out the following line in Src/app.c to prevent the device from entering low-power mode (note: this will quickly drain the battery): `HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);`

## Usage

- Press the **mode button** on the trophy to view the current animation.

## Known Issues

- Battery drains quickly when low-power mode is disabled during active development.
- Handle the battery carefully to avoid damaging the device.
- The device often stops working after installation and needs to be hard reset.

## Contributing

Please make a development branch and make a PR request
Please add to **Current Functionality** in README.md
