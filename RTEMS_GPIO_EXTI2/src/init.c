#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define CONFIGURE_INIT
#include "system.h"

uint32_t LEDx_VPIN[4] = {
		LED1_VPIN,
		LED2_VPIN,
		LED3_VPIN,
		LED4_VPIN
};
uint32_t BUTTONx_VPIN[4] = {
		BUTTON1_VPIN,
		BUTTON2_VPIN,
		BUTTON3_VPIN,
		BUTTON4_VPIN,
};

rtems_gpio *led[4], *button[4];
volatile rtems_gpio_pin_state led_state[4];
const uint32_t isr_arg[] = {0, 1, 2, 3};
int i;

#define ARGUMENT 0

rtems_task Init(
  rtems_task_argument ignored
)
{
	rtems_status_code status;

    rtems_gpio_begin();

    rtems_gpio_pull pull = RTEMS_GPIO_NOPULL; // not necessary if not using
    										  // F4 discovery
    for (i = 0; i < 4; ++i) {
		rtems_gpio_get(LEDx_VPIN[i], &led[i]);
		rtems_gpio_init(led[i]);
		rtems_gpio_set_pin_mode(led[i], RTEMS_GPIO_PINMODE_OUTPUT_PP);
		rtems_gpio_set_pull(led[i], RTEMS_GPIO_NOPULL);

		rtems_gpio_get(BUTTONx_VPIN[i], &button[i]);
		rtems_gpio_init(button[i]);
		rtems_gpio_configure_interrupt(
				button[i],
				button_isr,
				&isr_arg[i],
				RTEMS_GPIO_INT_TRIG_FALLING,
				pull
		);
		pull = RTEMS_GPIO_PULLUP;
    }
    for (i = 0; i < 4; ++i) {
		rtems_gpio_enable_interrupt(button[i]);
    }

    while (1) {
    	rtems_gpio_write(led[0], led_state[0]);
    	rtems_gpio_write(led[1], led_state[1]);
    	rtems_gpio_write(led[2], led_state[2]);
    	rtems_gpio_write(led[3], led_state[3]);
    }
}

void button_isr(
	void *arg
)
{
	uint32_t led_i = *(uint32_t *)arg;
	led_state[led_i] = !led_state[led_i];
}

void Error_Handler(void) {
	rtems_interrupt_level level;
	rtems_interrupt_disable(level);
	while (1) {

	}
}
