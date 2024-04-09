// Ivan Q
// EE-14 Embedded Systems
// Program demonstrates a working example of the Beep Generator on the Audio Chip CS43L22
// Uses I2C driver for communication between STM32L4 processor and Audio Chip

// Use function generate_beep() to write to the chip's 8-bit registers:
// CS43L22_REG_BEEP_FREQ_ON_TIME(0x1C), CS43L22_REG_BEEP_VOL_OFF_TIME(0x1D), and
// CS43L22_REG_BEEP_TONE_CFG(0x1E). This will set the beep frequency, on time, beep
// volume, off time, and tone configuration. Refer to these registers 0x1C, 0x1D, 0x1E
// in the datasheet

// Additional Notes:
// I2C module is used to write to the Audio Chip's registers
// SAI clock is needed to drive chip