// Ivan Q
// EE-14 Embedded Systems
// Program demonstrates a working example of the Beep Generator on the Audio Chip CS43L22
// Use function generate_beep() to write to the chip's 8-bit registers:
// CS43L22_REG_BEEP_FREQ_ON_TIME(0x1C), CS43L22_REG_BEEP_VOL_OFF_TIME(0x1D), and
// CS43L22_REG_BEEP_TONE_CFG(0x1E). This will set the beep frequency, on time, beep
// volume, off time, and tone configuration. Refer to these registers 0x1C, 0x1D, 0x1E
// in the datasheet

// Notes:
// I2C module is used to write to the Audio Chip's registers
// SAI clock is needed to drive chip

#include "stm32l476xx.h"
#include "SysClock.h"
#include "I2C.h"
#include "AudioChip.h"

#include <string.h>
#include <stdio.h>

// void blocking_delay(void);
volatile int TimingDelay;		// variable for delay
void delay(int ms);
void SysTick_Initialize(int ticks);

void sound_sequence_1();
void sound_sequence_2();

int main(void) {
	System_Clock_Init(); // Switch System Clock = 80 MHz
	SysTick_Initialize(999); // for delay function
	
	I2C_GPIO_Init();
	I2C_Init();
	
	SAI1_GPIO_Init();
	SAI1_Init();
	
	Audio_DAC_Init();
	Set_Default_Audio_Registers();
	
	while(1) {
		sound_sequence_1();
	}
}

void sound_sequence_1(void) {
	// Generate beeps by setting the register values
		
	// 0001 (freq) 0000 (on time) --> 0x10
	// 000 (off time) 11100 (beep volume) --> 0x1C
	// 11 (beep occurance) 0 (beepmixdis) 00000 (bass/treble) --> 0xC0
	generate_beep(0x10, 0x1C, 0xC0);
	delay(4000);
	generate_beep(0x20, 0x1C, 0xC0);
	delay(2000);
	generate_beep(0x50, 0x1C, 0xC0);
	delay(4000);
	generate_beep(0x80, 0x1C, 0xC0);
	delay(2000);
}

void SysTick_Handler(void){
	if(TimingDelay>0)
		TimingDelay = TimingDelay - 1;
}

void SysTick_Initialize(int ticks){
	//Turn on MSI clock
	RCC->CR |= RCC_CR_MSIRGSEL;
	RCC->CR &= ~RCC_CR_MSIRANGE;
	RCC->CR |= RCC_CR_MSIRANGE_7;
	
	RCC->CR |= RCC_CR_MSION;
	while(!(RCC->CR & RCC_CR_MSIRDY));

	//Set status and control register
	SysTick->CTRL = 0;
	//Set reload value register
	SysTick->LOAD |= ticks-1;
	//Set interrupt priority
	NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS)-1);
	//Reset counter value
	SysTick->VAL=0;
	//Select processor clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Pos;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Pos;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Pos;
	
}

void delay(int count){
	TimingDelay = count;
	while(TimingDelay!=0);
}
