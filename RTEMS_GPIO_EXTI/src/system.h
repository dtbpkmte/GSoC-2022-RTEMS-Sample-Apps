#ifndef SYSTEM_H
#define SYSTEM_H

#include <rtems.h>
#include <stdint.h>
#include <bsp/stm32f4_gpio.h>

/***** TODO: configure this!! ********/
#define LED_VPIN 		((uint32_t) (16*3 + 12)) // STM32F4 PD12
#define BUTTON_VPIN		((uint32_t) (16*0 + 0))  // STM32F4 PA0

/* functions */

rtems_task Init(
	rtems_task_argument argument
);

void Error_Handler(void);

void button_isr(
	void *arg
);

extern rtems_gpio *led, *button;
extern volatile rtems_gpio_pin_state led_state;

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
