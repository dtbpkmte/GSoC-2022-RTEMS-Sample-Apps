#ifndef SYSTEM_H
#define SYSTEM_H

#include <rtems.h>
#include <stdint.h>
#include <bsp/gpio2.h>
#include <bsp/adc.h>

/***** TODO: configure this!! ********/
#define LED1_VPIN 		((uint32_t) (16*3 + 12)) 	// STM32F4 PD12
#define LED2_VPIN 		((uint32_t) (16*3 + 13)) 	// STM32F4 PD13
#define LED3_VPIN 		((uint32_t) (16*3 + 14)) 	// STM32F4 PD14
#define LED4_VPIN 		((uint32_t) (16*3 + 15)) 	// STM32F4 PD15
#define POT_VPIN		((uint32_t) (16*1 + 0))  	// STM32F4 PB0

// STM32F4 pin B0 (ADC1, channel 8)
#define ADC_ID			0
#define ADC_CHANNEL		8

#define ADC_RESOLUTION	10							// 10-bit
#define MAX_ADC_VALUE	(0x1U << ADC_RESOLUTION)

/* functions */

rtems_task Init(
	rtems_task_argument argument
);

void Error_Handler(void);

/* configuration information */

#include <bsp.h> /* for device driver prototypes */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS                 1
#define CONFIGURE_MAXIMUM_SEMAPHORES            2
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#include <rtems/confdefs.h>

#endif
/* end of include file */
