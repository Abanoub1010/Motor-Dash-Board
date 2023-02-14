/*
 * mGPIO_Private.h
 *
 *  Created on: Jan 22, 2023
 *      Author: Abanoub
 */

#ifndef MGPIO_PRIVATE_H_
#define MGPIO_PRIVATE_H_

#include "LSTD_TYPES.h"
#include "LERROR_STATES.h"
#include "LBIT_MATH.h"



typedef struct
{
	u32 volatile MODER;
	u32 volatile OTYPER;
	u32 volatile OSPEEDR;
	u32 volatile PUPDR;
	u32 volatile IDR;
	u32 volatile ODR;
	u32 volatile BSRR;
	u32 volatile LCKR;
	u32 volatile AFBL;
	u32 volatile AFBH;
}MGPIO_t;

#define MGPIOA_BASE_ADDRESS (0x40020000)
#define MGPIOB_BASE_ADDRESS (0x40020400)
#define MGPIOC_BASE_ADDRESS (0x40020800)

#define MGPIOA ((MGPIO_t*) (MGPIOA_BASE_ADDRESS))
#define MGPIOB ((MGPIO_t*) (MGPIOB_BASE_ADDRESS))
#define MGPIOC ((MGPIO_t*) (MGPIOC_BASE_ADDRESS))


#endif /* MGPIO_PRIVATE_H_ */
