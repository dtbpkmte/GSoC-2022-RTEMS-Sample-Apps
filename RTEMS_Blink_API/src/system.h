#ifndef SYSTEM_H
#define SYSTEM_H

#include <rtems.h>
#include <stdint.h>
#include <bsp/gpio2.h>

/***** TODO: configure this!! ********/
#define LED_VPIN 		((uint32_t) (16*3 + 12)) // STM32F4 PD12
/**************************************/

/* functions */

rtems_task Init(
  rtems_task_argument argument
);

rtems_task LED_on_task(
  rtems_task_argument argument
);

rtems_task LED_off_task(
  rtems_task_argument argument
);

extern rtems_id sem_on_id, sem_off_id;
extern rtems_gpio *led;

void Error_Handler(void);

/* configuration information */

#include <bsp.h> /* for device driver prototypes */

#define CONFIGURE_APPLICATION_NEEDS_SIMPLE_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS                 3
#define CONFIGURE_MAXIMUM_SEMAPHORES            2
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#include <rtems/confdefs.h>

#endif
/* end of include file */
