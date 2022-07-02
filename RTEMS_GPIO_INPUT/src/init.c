#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define CONFIGURE_INIT
#include "system.h"
#include <stdio.h>
#include <stdint.h>

/******** TODO: CONFIGURE THIS *****************/
rtems_gpio *led, *button;

#define ARGUMENT 0

rtems_task Init(
  rtems_task_argument ignored
)
{
    rtems_gpio_begin();

    rtems_gpio_get(LED_VPIN, &led);
    rtems_gpio_get(BUTTON_VPIN, &button);

	rtems_gpio_init(led);
	rtems_gpio_set_pin_mode(led, RTEMS_GPIO_PINMODE_OUTPUT_PP);
	rtems_gpio_set_pull(led, RTEMS_GPIO_NOPULL);

	rtems_gpio_init(button);
	rtems_gpio_set_pin_mode(button, RTEMS_GPIO_PINMODE_INPUT);
	rtems_gpio_set_pull(button, RTEMS_GPIO_NOPULL);

    rtems_gpio_write(led, RTEMS_GPIO_PIN_RESET);

    rtems_gpio_pin_state button_state = RTEMS_GPIO_PIN_RESET;
    while (1) {
    	rtems_gpio_read(button, &button_state);
    	rtems_gpio_write(led, button_state);
    }
}


