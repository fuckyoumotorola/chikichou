# ChikiChou
Payload for bootloader (lk) modification for Moto G24 Power (fogorow)

## Features
- Blocks ```fastboot flash preloader```
- Blocks ```fastboot flashing lock```
- Blocks ```fastboot flashing unlock```
- Blocks ```fastboot erase``` on critical partitions
- Adds ```fastboot oem help```
- Adds ```fastboot oem is-partition-protected```
- Adds ```fastboot oem ssm-enable-thinkshield```
- Adds ```fastboot oem ssm-enable-zerotouch```
- Adds ```fastboot oem download```
- Patches ```fastboot oem ssm-disable-thinkshield```
- Patches ```fastboot oem ssm-disable-zerotouch```
- Publishes ```membase```
- Publishes ```chokichou-version```
- Hides bootloader orange state warning

## Build
### Arch Linux
1. Install dependencies
    ```shell
    sudo pacman -S arm-none-eabi-newlib arm-none-eabi-gcc
    ```
2. Run build
    ```shell
    make clean; make
    ```

# Credits

# Victor Vasquez (Zangetsu) and Roger Ortiz (ChouChou)
