# anchor8

It is yet another bootloader for the STM8 platform that implements IAP principles. Although it probably falls into
the "toy" bootloader category, it can still serve as a solid reference point for education. This project emphasizes
simplicity over optimizing for size and efficiency.

## References

[AN2659](https://www.st.com/en/embedded-software/stsw-stm8006.html) - STMicroelectronics application note. At its core,
the anchor8 bootloader design is based on this document.

[UM0560](https://www.st.com/en/embedded-software/stsw-stm8068.html) – STMicroelectronics user manual. This document also
serves as a foundational reference for the core bootloader implementation.

[stm8-bootloader](https://github.com/lujji/stm8-bootloader) – An STM8 bootloader implementation by [@lujji](https://github.com/lujji). This project was a valuable learning resource for understanding general bootloader mechanics, though its architecture
differs significantly from anchor8.

## License
This project is licensed under the MIT License - see the [LICENSE](/LICENSE) file for details.