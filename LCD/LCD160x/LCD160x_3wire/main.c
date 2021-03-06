#include <string.h>							//we use strcpy()
#include "gpio.h"
#include "delay.h"							//we use software delays
#include "lcd_3wi.h"						//we use lcd1602, 3-wire mode

//hardware configuration
//end hardware configuration

//global defines

//global variables
const char str0[]="LCD1602 Demo1234";
const char str1[]="count =        *";
char vRAM[17];								//display buffer
uint8_t count=0;							//counter

int main(void) {
	uint8_t tmp;

	mcu_init();								//reset the mcu
	lcd_init();								//initialize the lcd
	strcpy(vRAM, str0); lcd_display(LCD_Line0, vRAM);	//display str0 on line 0

	while(1) {
		count+=1;							//increment count

		//display count
		tmp = count;
		strcpy(vRAM, str1);					//form vRAM
		vRAM[14]=(tmp % 10) + '0'; tmp /= 10;
		vRAM[13]=(tmp % 10) + '0'; tmp /= 10;
		vRAM[12]=(tmp % 10) + '0'; tmp /= 10;
		vRAM[11]=(tmp % 10) + '0'; tmp /= 10;
		lcd_display(LCD_Line1, vRAM);

		//waste some time
		delay_ms(10);
	}

	return 0;
}
