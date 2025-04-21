/*
 * PWM0.c
 *
 * Created: 6/04/2025 22:55:03
 *  Author: thoma
 */ 
#include "PWM_Manual.h"                
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t pwm_manual_duty = 0;
volatile uint8_t pwm_manual_counter = 0;

void PWM_Manual_init(void) {
	DDRB |= (1 << PB5); // D13 como salida
	TCCR0A = 0;
	TCCR0B = (1 << CS00); //
	TIMSK0 |= (1 << TOIE0); // 
	TCNT0 = 0;
}

void PWM_Manual_setDuty(uint8_t dc) {
	pwm_manual_duty = dc;
}

ISR(TIMER0_OVF_vect) {
	if (pwm_manual_counter < pwm_manual_duty)
	PORTB |= (1 << PB5); // LED encendido
	else
	PORTB &= ~(1 << PB5); // LED apagado

	pwm_manual_counter++;
	if (pwm_manual_counter >= 255)
	pwm_manual_counter = 0;
}
