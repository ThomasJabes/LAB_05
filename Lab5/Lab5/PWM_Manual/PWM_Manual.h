/*
 * PWM0.c
 *
 * Created: 6/04/2025 22:55:03
 *  Author: thoma
 */ 
#ifndef PWM_MANUAL_H_
#define PWM_MANUAL_H_

#include <stdint.h>

// Inicializa el PWM manual en el pin PB5 (D13)
void PWM_Manual_init(void);

// Actualiza el duty cycle (valor entre 0 y 255)
void PWM_Manual_setDuty(uint8_t dc);

#endif
