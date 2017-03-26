#include <avr/io.h>

int main(void){

DDRC &= ~(1<<PC1); //adc1 input
DDRD=0xFF;//portd output 2 and 3

ADCSRA|=(1<<7);;//enabling the adc

ADMUX |=(1<<5);//left justified

ADCSRA|=(1<<0); //giving a pre scaler of 128 so out frequency is 125 KH
ADCSRA|=(1<<1);
ADCSRA|=(1<<2);

ADMUX &= ~(1<<7);//using avcc
ADMUX &= ~(1<<6);

ADMUX |= (1<<0); //selecting adc 1
ADMUX &= ~(1<<1);
ADMUX &= ~(1<<2);
ADMUX &= ~(1<<3);


while(1){
ADCSRA|=(1<<6);//start conversion
if(ADCSRA & (1<<4)){//checking adif bit
    if(ADCH==0)//0 v
    	PORTD=0;
    if(ADCH>100 && ADCH<200)//for 3.3 v adch should be 168
        PORTD=4;
    if(ADCH==255)
    	PORTD=255;

}
  ADCSRA &= ~(1<<4); //setting adif to 0
}

}