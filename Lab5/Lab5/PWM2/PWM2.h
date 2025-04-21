/*
 * PWM2.h
 *
 * Created: 15/04/2024 17:04:38
 *  Author: thoma
 */ 


#ifndef PWM2_H_
#define PWM2_H_

#include <stdint.h>
#include <avr/io.h>

#define invertido 1
#define no_invertido 0

//Funcion para configurar PWM2 Modo Fast Canal A
void initPWM2FastA(uint8_t inverted, uint16_t prescaler);

//Funcion para configurar PWM2 Modo Fast Canal B
void initPWM2FastB(uint8_t inverted, uint16_t prescaler);

//Funci?n para configurar el DutyCicle de A para PWM2
void updateDutyCicleA2(uint8_t duty);

//Funci?n para congfigurar el DutyCicle de B para PWM2
void updateDutyCicleB2(uint8_t duty);




#endif /* PWM2_H_ */