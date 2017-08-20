#ifndef __TIMER_H
#define __TIMER_H


#include "sys.h"


void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_Init(void);
void TIM4_Int_Init(u16 arr,u16 psc);
void TIM4_Init(void);
void TIM3_ChangeTimer(u16 arr);
void TIM3_Enable(void);
void TIM3_Disenable(void);
void TIM4_ChangeTimer(u16 arr);
void TIM4_Enable(void);
void TIM4_Disenable(void);
void TIM2_Init(void);
void TIM2_ChangeTimer(u16 arr);
void TIM2_Enable(void);
void TIM2_Disenable(void);
void TIM5_PWM_Init(u16 arr, u16 psc);
#endif



