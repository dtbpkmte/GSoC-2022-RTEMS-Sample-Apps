#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define CONFIGURE_INIT
#include "system.h"
#include <stdio.h>

rtems_gpio *analog1, *analog2;
int i;

#define ARGUMENT 0

rtems_task Init(
  rtems_task_argument ignored
)
{
	rtems_status_code status;

	rtems_gpio_get(ANALOG1_VPIN, &analog1);
	rtems_gpio_set_pin_mode(analog1, RTEMS_GPIO_PINMODE_ANALOG);
	rtems_gpio_set_pull(analog1, RTEMS_GPIO_NOPULL);
	rtems_periph_api_set_api(analog1, RTEMS_PERIPH_API_TYPE_ADC);

	rtems_gpio_get(ANALOG2_VPIN, &analog2);
	rtems_gpio_set_pin_mode(analog2, RTEMS_GPIO_PINMODE_ANALOG);
	rtems_gpio_set_pull(analog2, RTEMS_GPIO_NOPULL);
	rtems_periph_api_set_api(analog2, RTEMS_PERIPH_API_TYPE_ADC);

	rtems_adc_set_resolution(analog1, 10);
	rtems_adc_set_resolution(analog2, 12);

	uint32_t a1_value = 0, a2_value = 0;

    while (1) {
    	rtems_adc_read_raw(analog1, &a1_value);
    	rtems_adc_read_raw(analog2, &a2_value);
    	printf("Pin1: %u\tPin2: %u\n", a1_value, a2_value);
    }
}

void Error_Handler(void) {
	rtems_interrupt_level level;
	rtems_interrupt_disable(level);
	while (1) {

	}
}
