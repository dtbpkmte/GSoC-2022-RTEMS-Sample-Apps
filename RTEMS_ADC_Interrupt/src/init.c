#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define CONFIGURE_INIT
#include "system.h"
#include <bsp/stm32f4_gpio.h>

uint32_t LEDx_VPIN[4] = {
		LED1_VPIN,
		LED2_VPIN,
		LED3_VPIN,
		LED4_VPIN
};

rtems_gpio *led[4], *pot;
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
		rtems_gpio_init(led[i]);
		rtems_gpio_set_pin_mode(led[i], RTEMS_GPIO_PINMODE_OUTPUT_PP);
		rtems_gpio_set_pull(led[i], RTEMS_GPIO_NOPULL);
    }
	rtems_gpio_get(POT_VPIN, &pot);
	rtems_gpio_init(pot);
	rtems_gpio_set_pin_mode(pot, RTEMS_GPIO_PINMODE_ANALOG);
	rtems_gpio_set_pull(pot, RTEMS_GPIO_NOPULL);

	rtems_adc_configure_interrupt(pot, adc_isr, NULL);
	rtems_adc_enable_interrupt(pot);

//	rtems_adc_set_resolution(pot, ADC_RESOLUTION);

    while (1) {
    }
}

void adc_isr(
	void *arg
)
{
	uint32_t led_index = LL_ADC_REG_ReadConversionData32(((stm32f4_gpio *) pot)->adc_config->ADCx.ADCx) / (MAX_ADC_VALUE / 4);
	for (i = 0; i < 4; ++i) {
		rtems_gpio_write(led[i], RTEMS_GPIO_PIN_RESET);
	}
	rtems_gpio_write(led[led_index], RTEMS_GPIO_PIN_SET);
}

void Error_Handler(void) {
	rtems_interrupt_level level;
	rtems_interrupt_disable(level);
	while (1) {

	}
}
