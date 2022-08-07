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

rtems_gpio *led[4], *pot_gpio;
rtems_adc *pot;
volatile rtems_gpio_pin_state led_state[4];
int i;

#define ARGUMENT 0

rtems_task Init(
  rtems_task_argument ignored
)
{
	rtems_status_code status;

    for (i = 0; i < 4; ++i) {
		rtems_gpio_get(LEDx_VPIN[i], &led[i]);
		rtems_gpio_set_pin_mode(led[i], RTEMS_GPIO_PINMODE_OUTPUT_PP);
		rtems_gpio_set_pull(led[i], RTEMS_GPIO_NOPULL);
    }
	rtems_gpio_get(POT_VPIN, &pot_gpio);
	rtems_gpio_set_pin_mode(pot_gpio, RTEMS_GPIO_PINMODE_ANALOG);
	rtems_gpio_set_pull(pot_gpio, RTEMS_GPIO_NOPULL);

	rtems_adc_get(ADC_ID, &pot);
	rtems_adc_set_channel(pot, ADC_CHANNEL);
	rtems_adc_set_alignment(pot, RTEMS_ADC_ALIGN_RIGHT);
	rtems_adc_set_resolution(pot, ADC_RESOLUTION);
	rtems_adc_init(pot);

//	rtems_adc_set_resolution(pot, ADC_RESOLUTION);

	uint32_t pot_value = 0;

    while (1) {
		rtems_adc_status adc_status = rtems_adc_read_raw_nb(pot, &pot_value);
    	if (adc_status == RTEMS_ADC_NOT_STARTED) {
    		rtems_adc_start_read_nb(pot);
    	} else if (adc_status == RTEMS_ADC_READY){
			uint32_t led_index = pot_value / (MAX_ADC_VALUE / 4);
			for (i = 0; i < 4; ++i) {
				rtems_gpio_write(led[i], RTEMS_GPIO_PIN_RESET);
			}
			rtems_gpio_write(led[led_index], RTEMS_GPIO_PIN_SET);
    	}
    }
}

void Error_Handler(void) {
	rtems_interrupt_level level;
	rtems_interrupt_disable(level);
	while (1) {

	}
}
