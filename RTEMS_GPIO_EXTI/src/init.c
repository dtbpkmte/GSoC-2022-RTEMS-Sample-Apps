#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define CONFIGURE_INIT
#include "system.h"

rtems_gpio *led, *button;
volatile rtems_gpio_pin_state led_state = RTEMS_GPIO_PIN_RESET;

#define ARGUMENT 0

rtems_task Init(
  rtems_task_argument ignored
)
{
	rtems_status_code status;

	rtems_gpio_get(LED_VPIN, &led);
    rtems_gpio_get(BUTTON_VPIN, &button);

	rtems_gpio_set_pin_mode(led, RTEMS_GPIO_PINMODE_OUTPUT_PP);
	rtems_gpio_set_pull(led, RTEMS_GPIO_NOPULL);

	rtems_gpio_configure_interrupt(
			button,
			button_isr,
			NULL,
			RTEMS_GPIO_INT_TRIG_FALLING,
			RTEMS_GPIO_NOPULL
	);
	rtems_gpio_enable_interrupt(button);

    while (1) {
    	rtems_gpio_write(led, led_state);
    }
}

void button_isr(
	void *arg
)
{
	led_state = !led_state;
}

void Error_Handler(void) {
	rtems_interrupt_level level;
	rtems_interrupt_disable(level);
	while (1) {

	}
}
