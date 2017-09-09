4-bit or 8-bit user-configurable driver for LCD160x character LCDs.

connection specified in lcd_4bit.h:
LCD_EN/LCD_RS on one port, LCD_DATA0..7 on another port. For a total of 6 or 10 pins

typical usage:

lcd_init(); //initialize the lcd
lcd_display(LCD_Line0, vRAM); //display vRAM data on LCD_Line0
