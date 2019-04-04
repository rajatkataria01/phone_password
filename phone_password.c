#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void LCD_Init(void);
void dt(char data);
void loc(char com);
void str(char *str);
void num(int ch);
unsigned char keypad();
void main() 
{
DDRD=0xFF;
DDRB=0b11110000;
DDRC=0B11111111;
DDRA=0B11111111;

PORTB=0B11111111;
int i,j,k,l,x,y,z;
LCD_Init();
loc(0xc0);
str("Enter Password");
loc(0xcc);
str("to unlock:-");
_delay_ms(10);

x=keypad();
loc(0xcc);
str("*");
_delay_ms(5);

y=keypad();
str("*");
_delay_ms(5);

z=keypad();
str("*");
_delay_ms(5);

l=keypad();
str("*");
_delay_ms(50);
i=0;
while(((x!=1)|(y!=2)|(z!=3)|(l!=4))&&i<6)
{
if(i<=2)
{
loc(0x01);
_delay_ms(10);
loc(0x80);
str("Incorrect Pin");
loc(0xc0);
str("Try Again:-");
_delay_ms(5);
}
else if(i>2&&i<4)
{

for(j=29;j>=0;j--)
{

loc(0x80);
str("Try After 30sec");
loc(0xc0);
str("Time Left:-");

loc(0xcD);
num(j);
_delay_ms(80);
loc(0x01);
_delay_ms(5);}

loc(0x01);
_delay_ms(5);
str("Enter Password");
loc(0xc0);
str("to unlock:-");
_delay_ms(5);
}
else if(i>2&&i<5)
{

for(j=59;j>=0;j--)
{
loc(0x80);
str("Try After 60sec");
loc(0xc0);
str("Time Left:-");
loc(0xcD);
num(j);
_delay_ms(80);

loc(0x01);
_delay_ms(5);}
loc(0x01);
_delay_ms(5);
str("Enter Password");
loc(0xc0);
str("to unlock:-");
_delay_ms(5);
}

else if(i>4)
{
loc(0x01);
_delay_ms(5);
loc(0x80);
str("Your device is");
loc(0xc0);
str("Permanently Locked");
while(1);
{}
}
i++;
x=keypad();
loc(0xcc);
str("*");
_delay_ms(5);

y=keypad();
str("*");
_delay_ms(5);

z=keypad();
str("*");
_delay_ms(5);

l=keypad();
str("*");
_delay_ms(50);

loc(0x01);
_delay_ms(5);

}



loc(0x01);
_delay_ms(5);
loc(0x80);
str("Yo bro");
loc(0xb0);
str("Welcom back ;)");
/*LCD_Init();
x=keypad();
_delay_ms(10);
loc(0x85);
num(x);
_delay_ms(100);
loc(0x01);
_delay_ms(10);
*/
}








unsigned char keypad()
{
while(1)
{
PORTC=0B00000110;
_delay_ms(5);

if(PINB==0b11111110)
{
while(PINB==0b11111110);
return 1;
}
else if(PINB==0B11111101)
{
while(PINB==0b11111101);
return 4;
}
else if(PINB==0B11111011)
{
while(PINB==0B11111011);
return 7;
}
else if(PINB==0B11110111)
{
while(PINB==0B11110111);
return '#';
}



PORTC=0B00000101;
_delay_ms(5);

if(PINB==0b11111110)
{
while(PINB==0b11111110);
return 2;
}
else if(PINB==0B11111101)
{
while(PINB==0b11111101);
return 5;
}
else if(PINB==0B11111011)
{
while(PINB==0B11111011);
return '8';
}
else if(PINB==0B11110111)
{
while(PINB==0B11110111);
return 0;
}

PORTC=0B00000011;
_delay_ms(5);

if(PINB==0b11111110)
{
while(PINB==0b11111110);
return 3;
}
else if(PINB==0B11111101)
{
while(PINB==0b11111101);
return 6;
}
else if(PINB==0B11111011)
{
while(PINB==0B11111011);
return 9;
}
else if(PINB==0B11110111)
{
while(PINB==0B11110111);
return '*';
}

}
}


void LCD_Init(void)	/* LCD Initialize function */
{   loc(0x02);         /* to take lcd at home screen */
    loc(0x28);  	/* Initialization of 16X2 LCD in 8bit mode */
	loc(0x0C);	        /* Display ON Cursor OFF */
	   	/* Auto Increment cursor */
  }

void dt(char data)
     {
	  PORTA=((data&0xF0)|0x05);
	  _delay_us(10);
      PORTA=PORTA-0x04;
	  _delay_us(10);
	  PORTA=(((data<<4)&0xF0)|0x05);
	   _delay_us(10); 
	  PORTA=PORTA-0x04;
	  }
void loc(char com)
    {
	  PORTA=((com&0xF0)|0x04);
	  _delay_us(10);
      PORTA=PORTA-0x04;
	  _delay_us(10);
	  PORTA=(((com<<4)&0xF0)|0x04); 
	   _delay_us(10);
	  PORTA=PORTA-0x04;
	}
void str(char *str)
{int i=0;
while(str[i]!='\0')
{dt(str[i]);	
i++;
}
}

void num(int ch)
{
int x;
if(ch==0)
 dt(48);
  while(ch!=0)
   {loc(0x04);
     x=ch%10;
    dt(48+x);
	ch=ch/10;
}
}






