#ifndef SYSTEM_H
#define SYSTEM_H

#include <rtems.h>
#include <stdint.h>
#include <bsp/gpio2.h>

/***** TODO: configure this!! ********/
#define LED1_VPIN 		((uint32_t) (16*3 + 12)) // STM32F4 PD12
#define LED2_VPIN 		((uint32_t) (16*3 + 13)) // STM32F4 PD13
#define LED3_VPIN 		((uint32_t) (16*3 + 14)) // STM32F4 PD14
#define LED4_VPIN 		((uint32_t) (16*3 + 15)) // STM32F4 PD15
#define BUTTON1_VPIN		((uint32_t) (16*0 + 0))  // STM32F4 PA0
#define BUTTON2_VPIN		((uint32_t) (16*1 + 3))  // STM32F4 PB3
#define BUTTON3_VPIN		((uint32_t) (16*1 + 5))  // STM32F4 PB5
#define BUTTON4_VPIN		((uint32_t) (16*1 + 7))  // STM32F4 PB7

/* functions */

rtems_task Init(
	rtems_task_argument argument
);

void Error_Handler(void);

void button_isr(
	void *arg
);

/* configuration information */

#include <bsp.h> /* for device driver prototypes */

#define CONFIGURE_APPLICATION_NEEDS_SIMPLE_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS                 1
#define CONFIGURE_MAXIMUM_SEMAPHORES            2
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#include <rtems/confdefs.h>

#endif
/* end of include file */
