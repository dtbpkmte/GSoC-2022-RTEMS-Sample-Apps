#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define CONFIGURE_INIT
#include "system.h"
#include <stdio.h>

rtems_gpio *analog1_pin, *analog2_pin;
rtems_adc *analog1, *analog2;
int i;

#define ARGUMENT 0

rtems_task Init(
  rtems_task_argument ignored
)
{
	rtems_status_code status;

	rtems_gpio_get(ANALOG1_VPIN, &analog1_pin);
	rtems_gpio_set_pin_mode(analog1_pin, RTEMS_GPIO_PINMODE_ANALOG);
	rtems_gpio_set_pull(analog1_pin, RTEMS_GPIO_NOPULL);

	rtems_adc_get(ANALOG1_ADC_ID, &analog1);
	rtems_adc_set_channel(analog1, ANALOG1_CHANNEL);
	rtems_adc_set_alignment(analog1, RTEMS_ADC_ALIGN_RIGHT);
	rtems_adc_set_resolution(analog1, 10);
	rtems_adc_init(analog1);

	rtems_gpio_get(ANALOG2_VPIN, &analog2_pin);
	rtems_gpio_set_pin_mode(analog2_pin, RTEMS_GPIO_PINMODE_ANALOG);
	rtems_gpio_set_pull(analog2_pin, RTEMS_GPIO_NOPULL);

	rtems_adc_get(ANALOG2_ADC_ID, &analog2);
	rtems_adc_set_channel(analog2, ANALOG2_CHANNEL);
	rtems_adc_set_alignment(analog2, RTEMS_ADC_ALIGN_RIGHT);
	rtems_adc_set_resolution(analog2, 12);
	rtems_adc_init(analog2);

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
