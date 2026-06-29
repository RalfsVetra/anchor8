# anchor8

A bootloader for the STM8 platform that implements IAP principles. This project emphasizes simplicity over optimizing
for size and efficiency.

## Supported commands

Commands can be run with the verbosity enabled, for example `make V=1 ...`. By default, the verbosity is disabled. If you
are running make in a non-Linux environment, you should use `make WINE= ...`.

| Command | Description |
| --- | --- |
| make all | Initializes directories and builds the final image |
| make init | Creates the necessary directories |
| make clean | Purges all compiled object files, binaries, and build artifacts |
| make size | Displays the final flash memory footprint of the image |
| make inspect | Inspects the compiled executable structure |
| make flash | Flashes the image onto the target MCU |
| make flash-read | Reads the entire flash memory layout from the MCU |
| make opt-read | Reads the option bytes from the MCU |
| make opt-ubc | Establishes a 10-page IAP write-protected UBC area |
| make opt-reset | Resets the option bytes back to factory default values |
| make eeprom-read | Reads the onboard EEPROM data from the MCU |

## References

[AN2659](https://www.st.com/en/embedded-software/stsw-stm8006.html) - STMicroelectronics application note. At its core,
the anchor8 bootloader design is based on this document.

[UM0560](https://www.st.com/en/embedded-software/stsw-stm8068.html) – STMicroelectronics user manual. This document also
serves as a foundational reference for the core bootloader implementation.

[stm8-bootloader](https://github.com/lujji/stm8-bootloader) – An STM8 bootloader implementation by [@lujji](https://github.com/lujji). This project was a valuable learning resource for understanding general bootloader mechanics, though its architecture
differs significantly from anchor8.

## License
This project is licensed under the MIT License - see the [LICENSE](/LICENSE) file for details.