/*
 * PWM1.h
 *
 * Created: 7/04/2025 17:12:07
 *  Author: thoma
 */ 


#ifndef PWM1_H_
#define PWM1_H_

#include <avr/io.h>
#include <stdint.h>

#define invertido     1
#define no_invertido  0

// Inicializar PWM1 en modo Fast PWM de 16 bits
void initPWM1Fast_16bit(uint8_t inverted, uint16_t prescaler);

// Cambiar ciclo de trabajo para canal OC1A (pin PB1 / D9)
void updateDutyCycle1A(uint16_t duty);  // versión mejorada: 16 bits enteros

#endif