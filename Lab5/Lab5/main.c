//*********************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Author : Thomas Solis
// Proyecto: Laboratorio 5
// Descripción: PWM manual + 2 servos
// Hardware: ATmega328p
//*********************************************************************

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "PWM1/PWM1.h"
#include "PWM2/PWM2.h"
#include "PWM_Manual/PWM_Manual.h"

// Variables globales
volatile uint8_t valorADC_servo1 = 0;  // ADC7
volatile uint8_t valorADC_servo2 = 0;  // ADC6
volatile uint16_t valorADC_led = 0;    // ADC5
volatile uint8_t canal_actual = 0;     // Canal actual del ADC

// Inicializa ADC con interrupciones para ADC7, ADC6 y ADC5
void ADC_init_triple(void) {
	ADMUX = (1 << REFS0) | (1 << ADLAR) | 0x07; // Empieza con ADC7
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1); // Prescaler 64
	#ifdef ADC6D
	DIDR0 |= (1 << ADC6D);
	#endif
	#ifdef ADC7D
	DIDR0 |= (1 << ADC7D);
	#endif
	sei(); // Habilita interrupciones globales
	ADCSRA |= (1 << ADSC); // Inicia conversión
}

int main(void) {
	PWM_Manual_init();                          // PWM manual en PB5 (D13)
	initPWM1Fast_16bit(no_invertido, 8);        // Servo 1 en D9 
	initPWM2FastA(no_invertido, 32);            // Servo 2 en PB3 
	ADC_init_triple();                         

	while (1) {
		// LED en D13 
		uint8_t dutyLED = (valorADC_led * 255UL) / 1023;
		PWM_Manual_setDuty(dutyLED);

		// Servo 1 
		uint16_t pulso1 = 1000 + ((valorADC_servo1 * 1000UL) / 255);
		updateDutyCycle1A(pulso1);

		// Servo 2 
		uint8_t duty2 = 20 + ((valorADC_servo2 * 20UL) / 255);
		updateDutyCicleA2(duty2);

		_delay_ms(20);
	}
}

// ISR del ADC para ADC7, ADC6, ADC5
ISR(ADC_vect) {
	switch (canal_actual) {
		case 0:
			valorADC_servo1 = ADCH;                // ADC7
			ADMUX = (ADMUX & 0xF0) | 0x06;         // ADC6
			canal_actual = 1;
			break;
		case 1:
			valorADC_servo2 = ADCH;                // ADC6
			ADMUX = (ADMUX & 0xF0) | 0x05;         // ADC5
			canal_actual = 2;
			break;
		case 2:
			ADMUX &= ~(1 << ADLAR);                // Habilita lectura de 10 bits
			valorADC_led = ADC;                    // ADC5
			ADMUX |= (1 << ADLAR);                 // Vuelve a justificación izquierda
			ADMUX = (ADMUX & 0xF0) | 0x07;         // ADC7
			canal_actual = 0;
			break;
	}
	ADCSRA |= (1 << ADSC); // Inicia siguiente conversión
}
