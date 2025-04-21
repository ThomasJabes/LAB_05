/*
 * PWM2.c
 *
 * Created: 15/04/2024 17:28:04
 *  Author: thoma
 */ 
#include "PWM2.h"

void initPWM2FastA(uint8_t inverted, uint16_t prescaler){
	//Configurando el pin PD6 como salida 
	DDRB |= (1<<DDB3);
	
	TCCR2A = 0;
	if(inverted){
		//Configurando OC2A como invertido
		TCCR2A |= (1<<COM2A1)|(1<<COM2A0);
	}
	else{
		//Configurando OC0A como no invertido
		TCCR2A |= (1<<COM2A1);
	}
	
	
	//Configurando Modo PWM FAST TOP = 0xFF
	TCCR2A |= (1<<WGM21)|(1<<WGM20);
	//Prescaler de 32
	TCCR2B |= (1<<CS22)|(1<<CS21)|(1<<CS20);
}

void initPWM2FastB(uint8_t inverted, uint16_t prescaler){
	//Configurando el pin PD6 
	DDRD |= (1<<DDD3);
	
	TCCR2B = 0;
	if(inverted){
		//Configurando OC2A como invertido
		TCCR2B |= (1<<COM2B1)|(1<<COM2B0);
	}
	else{
		//Configurando OC0A como no invertido
		TCCR2B |= (1<<COM2B1);
	}
	
	
	//Configurando Modo PWM FAST TOP = 0xFF
	TCCR2A |= (1<<WGM21)|(1<<WGM20);
	//Prescaler de 1024
	TCCR2B |= (1<<CS22);
}

void updateDutyCicleA2(uint8_t duty){
	OCR2A = duty;
}

void updateDutyCicleB2(uint8_t duty){
	OCR2B = duty;
}