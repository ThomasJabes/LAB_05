/*
 * PWM0.c
 *
 * Created: 6/04/2025 22:55:03
 *  Author: thoma
 */ 
#include "PWM1.h"

void initPWM1Fast_16bit(uint8_t inverted, uint16_t prescaler) {
	// Pin OC1A como salida (PB1 / D9)
	DDRB |= (1 << DDB1);

	// Limpiar registros de Timer1
	TCCR1A = 0;
	TCCR1B = 0;

	// Modo 14: Fast PWM con ICR1 como TOP
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);

	// Modo no invertido o invertido según parámetro
	if (inverted) {
		TCCR1A |= (1 << COM1A1) | (1 << COM1A0); // Invertido
		} else {
		TCCR1A |= (1 << COM1A1); // No invertido
	}

	//  50Hz con prescaler 8
	ICR1 = 39999;

	// Prescaler dinámico
	switch (prescaler) {
		case 1:    TCCR1B |= (1 << CS10); break;
		case 8:    TCCR1B |= (1 << CS11); break;
		case 64:   TCCR1B |= (1 << CS11) | (1 << CS10); break;
		case 256:  TCCR1B |= (1 << CS12); break;
		case 1024: TCCR1B |= (1 << CS12) | (1 << CS10); break;
		default:   TCCR1B |= (1 << CS11); break; // Por defecto prescaler 8
	}
}

void updateDutyCycle1A(uint16_t duty) {
	// duty: valor entre 1000 y 2000 para servo (1ms–2ms)
	if (duty < 1000) duty = 1000;
	if (duty > 2000) duty = 2000;
	OCR1A = duty * 2; // 1us = 2 ticks cuando prescaler = 8
}
