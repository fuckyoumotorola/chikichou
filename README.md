# ChikiChou
Minimal payload for bootloader (lk) modification for Moto G24 Power (fogorow)

## Features
- Blocks ```fastboot flash``` on critical partitions
- Blocks ```fastboot flashing lock```
- Blocks ```fastboot flashing unlock```
- Blocks ```fastboot erase``` on critical partitions
- Adds ```fastboot oem help```
- Adds ```fastboot oem is-partition-protected```
- Adds ```fastboot oem ssm-enable-thinkshield```
- Adds ```fastboot oem ssm-enable-zerotouch```
- Adds alias ```fastboot oem download``` for ```fastboot download```
- Patches ```fastboot oem ssm-disable-thinkshield```
- Patches ```fastboot oem ssm-disable-zerotouch```
- Publishes ```membase```
- Publishes ```chikichou-version```
- Hides bootloader orange state warning
- Hides useless information from screen when is into bootloader mode

## Build
### Arch Linux
1. Install dependencies
    ```shell
    sudo pacman -S base-devel arm-none-eabi-gcc arm-none-eabi-newlib
    ```
2. Run build
    ```shell
    make
    ```

# Credits
 
## Roger Ortiz (ChouChou)
