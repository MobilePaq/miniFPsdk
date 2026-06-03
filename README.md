# miniFPsdk
Some sort of SDK for feature phones, mostly SC6531. Based of fpdoom.

## Supported HW:
- Any SC6531 based phone

## TODO:
- Make unattended boot:
  - Does not require a PC to start
  - Does not need a config file (means all config is stored in the binary and it can run standalone without original firmware/PC)
  - Screen and keymap params stored **in the binary**, not required to scan original FW every boot
- Make UART work
- Integrate FreeRTOS
- *If somebody has nothing to do after all that: FM radio, BT, etc*

## What already works:
- SC6531:RTC (see 6531RTCdemo)
- Full HAGL graphics stack
- Screen (with fpdoom stock FW scanning - fix that!)
- Buttons (with fpdoom stock FW scanning - fix that!)

## What is where:
- 6531RTCdemo: RTC demo
- 6531UARTdemo: non-working UART demo
- fpdoom: ~~stolen~~ code from fpdoom
- fpbuild: ~~stolen~~ code from fpdoom
- sdklib: basically all libs/headers added here
- SDKApi_src.txt: GREPed list of all functions for use
- docs: PDFs, Datasheets

## How to build:
- Make a new 'project': copy for example 6531UARTdemo, change name in Makefile and builddeploy.sh
- Write your code and then use builddeploy.sh to build it and then instantly deploy to a target over USB (you might need to build spd_dump)

## Contributions:
They are very welcome.
**Please** verify your code works. Recommended that variables have understandable names and where needed code is commented.
Vibe-coding? Feel-free, just dont make a mess, oke?

## Thanks to:
- **ilyakurdyukov for fpdoom** https://github.com/ilyakurdyukov/fpdoom
- **tuupola for hagl** https://github.com/tuupola/hagl


