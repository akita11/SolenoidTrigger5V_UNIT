#include <stdint.h>
#include "fw_reg_stc8g.h"

// STC8G1K08A-36I-DFN8
// Grove: RXD(P3.0)-TXD(P3.1)-VDD-GND / RXD for control (1=on / 0=off)

// for SolenoidTrigger5V

#define pinLOAD  P54 // P5.4
#define pinCHG   P55 // P5.5
#define pinRXD   P30 // P3.0 / Grove-p2
#define pinTXD   P31 // P3.1 / outside / mode
#define pinPMCEN P32 // P3.2
#define pinADC   P33 // P3.3 (ADC3)

#define FOSC 11059200UL

uint8_t readVoltage()
{
  // return ADC, 1/4 of Vdrive -> 1/4.9@R9=390k
  ADC_CONTR |= 0x40; // ADC_START=1
  while(ADC_CONTR & 0x40); // wait for ADC_START goes 0 (ADC complete)
  return(ADC_RES); // upper byte
}

void sendByte(unsigned char c)
{
  SBUF = c;
}


void delay100ms(void)	//@11.0592MHz, from STC-ISP
{
  unsigned char i, j, k;
  __asm__("nop");
  i = 6; j = 157; k = 59;
  do { do{ while (--k); } while (--j);} while (--i);
}

void enableCharge(unsigned char d)
{
  if (d == 1){
    P5M1 &= ~0x20; P5M0 |= 0x20; // P5.5=push-pull output
    pinCHG = 0;
  }
  else{
    P5M1 |= 0x20; P5M0 &= ~0x20; // P5.5=analogIN
    pinCHG = 1;
  }
}

void enableDCDC(unsigned char d)
{
  if (d == 1) pinPMCEN = 1;
  else pinPMCEN = 0;
}



void main()
{
  // M1=1/M0=0 : input
  // M1=0/M0=0 : quasi bidirectional
  // M1=0/M0=1 : push-pull output
  P3M1 = 0x09; P3M0 = 0x04; // set P3.1=quasi-bidirectional, P3.2=push-pull, P3.0&3.3=analogIN
  P5M1 = 0x20; P5M0 = 0x10; // set P5.4=push-pull output, P5.5=analogIN
  
  ADC_CONTR = 0x83; // ADC_POW=1, ADC_CHS=0011
  ADCCFG = 0x0f; // RESFMT=0(left align), SPEED=1111 (SYSCLK/2/16)

  /*
  // 9600bpsU(UART1)@11.0592MHz, from STC-ISP
  PCON &= 0x7F;	// Baudrate no doubled
  SCON = 0x50;  // 8 bits and variable baudrate (Mode1), RX enabled
  AUXR |= 0x40; // imer clock is 1T mode
  AUXR &= 0xFE;	// UART 1 use Timer1 as baudrate generator
  TMOD &= 0x0F;	// Set timer work mode
  TMOD |= 0x20;	// Set timer work mode
  TL1 = 0xDC;	// Initial timer value
  TH1 = 0xDC;	// Set reload value
  ET1 = 0;	// Disable Timer%d interrupt
  TR1 = 1;	// Timer1 start run
  */

  pinLOAD = 0;
  enableDCDC(0);
  enableCharge(0);

  //#define TH_CHARGED  197 // 197/255*5*4.9=19V
  //#define TH_TOCHARGE 156 // 156/255*5*4.9=15V
  //#define TH_CHARGED  229 // 229/255*5*4.9=22V
  //#define TH_TOCHARGE 187 // 187/255*5*4.9=18V
  //#define TH_CHARGED  156 // 156/255*5*4.9=15V
  //#define TH_TOCHARGE 104 // 104/255*5*4.9=10V
#define TH_CHARGED  177 // 156/255*5*4.9=17V
#define TH_TOCHARGE 156 // 104/255*5*4.9=15V

  P3 |= 0x02; // enable P3.1 pull-up
  __asm__("nop"); __asm__("nop");
  //  if (pinTXD == 1){

  unsigned char t;
  if (1){
    // JP1=open -> Operation Mode: charge after trigger
    while(1) {
      if (pinRXD == 1){
	enableDCDC(1);
	enableCharge(1);
	t = 0;
	while(readVoltage() < TH_CHARGED && t < 10){
	  delay100ms();
	  t++;
	}
	enableDCDC(0);
	enableCharge(0);
	pinLOAD = 1;
	// Drive Load for 200ms
	delay100ms();
	delay100ms();
	pinLOAD = 0;
	while(pinRXD == 1);
      }
    }
  }
  else{
    // JP1=short -> Operation Mode: charge during idle
    // ** currently disabled due to power charge concern
    while(1) {
      if (readVoltage() < TH_TOCHARGE){
	enableDCDC(1);
	enableCharge(1);
	while(readVoltage() < TH_CHARGED){
	  delay100ms();
	}
	enableDCDC(0);
	enableCharge(0);
      }
      if (pinRXD == 1){
	pinLOAD = 1;
	// Drive Load for 200ms
	delay100ms();
	delay100ms();
	pinLOAD = 0;
	
	while(pinRXD == 1);
      }
    }
  }      
}

