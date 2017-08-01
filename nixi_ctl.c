#include <wiringPi.h>
#include <stdint.h>

#define OUTPUT_BIT_0 7
#define OUTPUT_BIT_1 0
#define OUTPUT_BIT_2 1
#define OUTPUT_BIT_3 2
#define OUTPUT_BIT_4 3
#define OUTPUT_BIT_5 4
#define OUTPUT_BIT_6 5
#define OUTPUT_BIT_7 6



#define CONTROL_BIT_0 21
#define CONTROL_BIT_1 22
#define CONTROL_BIT_2 23

#define MASK 1
#define BYTE 8
//gcc sudo -Wall -o nixi_ctl nixi_ctl.c -lwiringPi
uint8_t s;
uint8_t m;
uint8_t h;

uint8_t initialized = 0;

uint8_t output_pin [BYTE]=[OUTPUT_BIT_0, OUTPUT_BIT_1, OUTPUT_BIT_2, OUTPUT_BIT_3,
	OUTPUT_BIT_4, OUTPUT_BIT_5, OUTPUT_BIT_6, OUTPUT_BIT_7];

pinMode()

int init(){

	s = 0;
	m = 0;
	h = 0;

	pinMode(OUTPUT_BIT_0, OUTPUT);
	pinMode(OUTPUT_BIT_1, OUTPUT);
	pinMode(OUTPUT_BIT_2, OUTPUT);
	pinMode(OUTPUT_BIT_3, OUTPUT);
	pinMode(OUTPUT_BIT_4, OUTPUT);
	pinMode(OUTPUT_BIT_5, OUTPUT);
	pinMode(OUTPUT_BIT_6, OUTPUT);
	pinMode(OUTPUT_BIT_7, OUTPUT);
	initialized = 1;

	return(0);	
}


int set_output(uint8_t input){
	if(initialized != 0){
		int i = 0;
		for(i = 0; i < BYTE; i++){ 
			uint8_t bit = (input >> i) & MASK;
			if(bit == 0){
				digitalWrite(output_pin[i], LOW);
			}
			else{
				digitalWrite(output_pin[i], HIGH);	
			}
		}
	}
}


int main(void){

	init();

	while(1){
		printf("Please enter a 8-bit hex integer");
		uint8_t value = 0;
		scanf("%x\n", &value);

		
		set_output(value);
	}
	return(0);

}
