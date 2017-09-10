# My-MCU-Library
My library of code that works on various MCUs, to promote code re-usability and portability

Here is a set of routines that I often use in my personal projects on MCUs. The goal is to write code that can be used with no change, or little change, over a wide spectrum of devices.

They are published here for your personal use as well.

The goal is to update and expand it as time allows.

sample code:

```
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
```
