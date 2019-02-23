# GNARL is Not A RileyLink

![TTGO LoRa OLED v1](images/ttgo.png)

## Warning

This repository contains **very preliminary** code, intended for
collaboration among developers. It **is not ready** for end users
and may be subject to rebasing without notice.

## Hardware

This project has been developed and tested on
a TTGO ESP32 868/915 MHz LoRa OLED module *(version 1 only, see below!),*
which contains an ESP32 SoC, an RFM95 LoRa radio,
a 128x64 pixel SSD1306 OLED display, and a LiPo battery charger.

The module has two push-buttons.
One is hard-wired to reset the board;
the other is available as an input or interrupt source.

They are available from [AliExpress,](https://www.aliexpress.com/item/2pcs-TTGO-LORA32-Lora-868Mhz-ESP32-LoRa-OLED-0-96-Inch-Blue-Display-Bluetooth-WIFI-ESP/32839249834.html)
[Banggood,](https://www.banggood.com/2Pcs-Wemos-TTGO-LORA32-868915Mhz-ESP32-LoRa-OLED-0_96-Inch-Blue-Display-p-1239769.html)
and numerous others.

### *TTGO version 2 module is not supported*

The current code does not work on the TTGO version 2 module due to
different pin assignments.

## Radios

The ESP32 SoC contains both WiFi and Bluetooth radios.
This project currently uses only the Bluetooth LE support.

The radio chip ([HopeRF RFM95](https://www.hoperf.com/modules/lora/RFM95.html) /
[Semtech SX1276](https://www.semtech.com/products/wireless-rf/lora-transceivers/sx1276))
is marketed for LoRa applications, but also supports OOK and FSK modulation.
The OOK capability is used by this project to communicate with Medtronic insulin pumps.
It may also be possible to use the FSK support and a 433 MHz version
of the module to communicate with OmniPod insulin pumps:
if anyone pursues that, please let me know.

## Hardware Setup

### Antenna

Attach an appropriate antenna to the U.FL connector on the module
before using this software.

### Power

The module can be powered via the micro-USB connector or with a 3.7V
LiPo battery.

The battery connects to a 2-pin female JST 1.25mm connector.
Note that this is smaller than the 2.0mm connectors used on Adafruit and
SparkFun LiPo batteries.

## Software Setup

### Initialize git submodules

This repository contains two git submodules (in the `components` subdirectory),
and one of them (`arduino-esp32`) itself contains two git submodules.
Unless you cloned this repository with the `--recursive` option,
those submodules won't be initialized yet.
Use this command to initialize them:
```
git submodule update --init --recursive
```

and this command to check their status:
```
git submodule status --recursive
```

### Set up the ESP32 environment

1. [Follow these instructions to set up the ESP32 development environment.](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html)
Make sure to install both the toolchain and the ESP-IDF framework,
and set the `IDF_PATH` variable in your environment appropriately.

1. Build and flash one of the example applications to make sure you have a working setup.

## Building GNARL

1. Type `make` in the top level of this repository

1. Change to the `project` subdirectory

1. Build the project by running `make -j`

1. Flash the project to your ESP32 module by running `make flash`

## Running GNARL

Run the experimental [Medtronic branch of AndroidAPS](https://github.com/andyrozman/AndroidAPS)
on your Android phone.
In the setup wizard, GNARL should show up when you scan for a RileyLink.

GNARL will show messages on the OLED display when your phone
connects and disconnects. Pushing the button will display the current
status. GNARL may not respond to the button press immediately if it is
communicating with the pump, due to scheduling priorities.

## Building the other applications

This repository contains a few applications ("projects" in ESP-IDF terminology) besides GNARL:

* `blink` blinks the onboard LED

* `sleep` uses the ESP32 "lightweight sleep" mode and wakes up when a
  timer goes off or the button is pressed

* `hello` draws "Hello" on the OLED display

* `regtest` reads the RFM69 registers and prints them on the serial console

* `sniffer` receives Medtronic packets and prints them on the serial console

* `pumpstat` displays the status of a Medtronic insulin pump when you press the button.
  You must first define the pump serial number as a string constant `PUMP_ID` in the file `pump.h`,
  or by editing `main.c`

To build the `blink` project, for example:

1. In the top level of this repository, type `make blink`

1. Change to the `project` directory and follow the same steps as above
   for building and flashing GNARL

After flashing applications that print information on the serial console,
run `make monitor` to see the output.


## TTGO V2

Device Link: [Link on Ali Express](https://www.aliexpress.com/item/1-Pcs-TTGO-LORA32-V2-0-433-868-915Mhz-ESP32-LoRa-OLED-0-96-Inch-SD/32847471775.html?spm=2114.search0104.3.10.2beb15725I8Qik&ws_ab_test=searchweb0_0,searchweb201602_10_10065_10068_319_317_10696_10084_453_10083_454_10618_10304_10307_10820_10821_537_10302_536_10902_10059_10884_10887_321_322_10103,searchweb201603_6,ppcSwitch_0&algo_expid=445593bd-79d1-42c9-952f-a9c25a0a78a0-1&algo_pvid=445593bd-79d1-42c9-952f-a9c25a0a78a0&transAbTest=ae803_4)
Git Link: [Link to GIT repository](https://github.com/LilyGO/TTGO-LORA32-V2.0/)
Specification: [TTGO LoRa32 V2.0 Pinout v3.0.pdf](https://www.thethingsnetwork.org/forum/uploads/default/original/2X/4/4eb4d5846cf0a7fbaeabbad3c0b0cdde2faecb23.pdf)

To get V2 working, you will need to do some changes in code, and also some hardware changes:
    You need to wire: (look at specification)
       - DIO1 to 33
       - DIO2 to 32


1. Set XTAL Frequency to 40 Mhz:
    make menuconfig
       Component config -> ESP32-Specific -> Main XTAL Frequency
       Set to 40 Mhz

    cp sdkconfig ../mk/

    This will keep your configuration for all the projects.

2. Set device in config.h

     #define TTGO_V2

     and comment all other device configurations (we only had TTGO_V2 and TTGO_V1 at time of this changes)


