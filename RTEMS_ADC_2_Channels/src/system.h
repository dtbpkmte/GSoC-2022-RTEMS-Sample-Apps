#ifndef SYSTEM_H
#define SYSTEM_H

#include <rtems.h>
#include <stdint.h>
#include <bsp/gpio2.h>
#include <bsp/adc.h>

/***** TODO: configure this!! ********/
#define ANALOG1_VPIN	((uint32_t) (16*1 + 0))  	// STM32F4 PB0
#define ANALOG2_VPIN	((uint32_t) (16*1 + 1))  	// STM32F4 PB1

// STM32F4 pin B0 (ADC1, channel 8), pin B1 (ADC1, channel 9)
#define ANALOG1_ADC_ID		0
#define ANALOG2_ADC_ID		0
#define ANALOG1_CHANNEL		8
#define ANALOG2_CHANNEL		9

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
