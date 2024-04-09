// Ivan Q
// EE-14 Embedded Systems
// Program demonstrates a working example of the Beep Generator on the Audio Chip CS43L22
// Use function generate_beep() to write to the chip's 8-bit registers:
// CS43L22_REG_BEEP_FREQ_ON_TIME(0x1C), CS43L22_REG_BEEP_VOL_OFF_TIME(0x1D), and
// CS43L22_REG_BEEP_TONE_CFG(0x1E). This will set the beep frequency, on time, beep
// volume, off time, and tone configuration. Refer to these registers 0x1C, 0x1D, 0x1E
// in the datasheet

// WARNING/CAUTION: Volume can be loud, so be careful about your ears when you plug in
// speakers/headphones into the STM32 Discovery Kit's audio jack!

// Notes:
// I2C module is used to write to the Audio Chip's registers
// SAI clock is needed to drive chip

#include "stm32l476xx.h"
#include "SysClock.h"
#include "I2C.h"
#include "AudioChip.h"

#include <string.h>
#include <stdio.h>

void SysTick_Initialize(int ticks);

int main(void) {
	System_Clock_Init(); // Switch System Clock = 80 MHz
	
	I2C_GPIO_Init();
	I2C_Init();
	
	SAI1_GPIO_Init();
	SAI1_Init();
	
	Audio_DAC_Init();
	Set_Default_Audio_Registers();
	
	while(1) {
		my_audio_fun();
	}
}
