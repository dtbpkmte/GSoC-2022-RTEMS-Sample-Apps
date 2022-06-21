#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "system.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Turns LED5 on
 */
rtems_task LED_on_task(
    rtems_task_argument argument
)
{
    rtems_id          tid;
    rtems_status_code status;
    unsigned int      a = (unsigned int) argument;

    while (1) {
        status = rtems_semaphore_obtain(sem_on_id, RTEMS_WAIT, RTEMS_NO_TIMEOUT);

		rtems_gpio_write_pin(&led5, RTEMS_GPIO_PIN_SET);

        status = rtems_task_wake_after(rtems_clock_get_ticks_per_second());

        status = rtems_semaphore_release(sem_off_id);
    }
    //exit( 0 );
}

/*
 * Turns LED5 off
 */
rtems_task LED_off_task(
    rtems_task_argument argument
)
{
    rtems_id          tid;
    rtems_status_code status;
    unsigned int      a = (unsigned int) argument;

    while (1) {
        status = rtems_semaphore_obtain(sem_off_id, RTEMS_WAIT, RTEMS_NO_TIMEOUT);

		rtems_gpio_write_pin(&led5, RTEMS_GPIO_PIN_RESET);

        status = rtems_task_wake_after(rtems_clock_get_ticks_per_second());

        status = rtems_semaphore_release(sem_on_id);
  }
  //exit( 0 );
}
