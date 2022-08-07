#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define CONFIGURE_INIT
#include "system.h"
#include <stdio.h>

rtems_gpio *pot_gpio;
rtems_adc *pot;
int i;

#define ARGUMENT 0

double to_voltage(void *param, uint32_t raw) {
	return (double) raw * 3.3 / MAX_ADC_VALUE;
}

rtems_task Init(
  rtems_task_argument ignored
)
{
	rtems_status_code status;

	rtems_gpio_get(POT_VPIN, &pot_gpio);
	rtems_gpio_set_pin_mode(pot_gpio, RTEMS_GPIO_PINMODE_ANALOG);
	rtems_gpio_set_pull(pot_gpio, RTEMS_GPIO_NOPULL);

	rtems_adc_get(ADC_ID, &pot);
	rtems_adc_set_channel(pot, ADC_CHANNEL);
	rtems_adc_set_alignment(pot, RTEMS_ADC_ALIGN_RIGHT);
	rtems_adc_set_resolution(pot, ADC_RESOLUTION);
	rtems_adc_assign_tf(pot, to_voltage, NULL);
	rtems_adc_init(pot);


//	rtems_adc_set_resolution(pot, ADC_RESOLUTION);

	double pot_voltage = 0;

    while (1) {
    	rtems_adc_read(pot, &pot_voltage);
    	printf("Voltage: %lf\n", pot_voltage);
    }
}

void Error_Handler(void) {
	rtems_interrupt_level level;
	rtems_interrupt_disable(level);
	while (1) {

	}
}
