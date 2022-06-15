#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define CONFIGURE_INIT
#include "system.h"
#include <stdio.h>
#include <stdint.h>

rtems_gpio_t port_d = {GPIOD};
rtems_gpio_pin_t led5_pin = {GPIO_PIN_14};

rtems_status_code rtems_gpio_initialize(void) {
	/* Enable the GPIO_LED Clock */
    __HAL_RCC_GPIOD_CLK_ENABLE();
    return RTEMS_SUCCESSFUL;
}

rtems_id sem_on_id, sem_off_id;

#define ARGUMENT 0

rtems_task Init(
  rtems_task_argument ignored
)
{
	//
    GPIO_InitTypeDef  GPIO_InitStruct = {
    		.Pin = GPIO_PIN_4,
			.Mode = GPIO_MODE_OUTPUT_PP,
			.Pull = GPIO_PULLUP,
			.Speed = GPIO_SPEED_FAST
    };
    rtems_gpio_config_t config = {&GPIO_InitStruct};
    rtems_gpio_configure(&port_d, &config);

    rtems_gpio_write_pin(&port_d, &led5_pin, RTEMS_GPIO_PIN_SET);

    rtems_name        sem_name, task_name_1, task_name_2;
    rtems_id          tid_1, tid_2;
    rtems_status_code volatile status;

    sem_name = rtems_build_name( 'S', 'O', 'N', ' ' );
    status = rtems_semaphore_create( 
            sem_name, 
            0, 
            RTEMS_SIMPLE_BINARY_SEMAPHORE,
            RTEMS_NO_INHERIT_PRIORITY + RTEMS_NO_MULTIPROCESSOR_RESOURCE_SHARING + RTEMS_NO_PRIORITY_CEILING,
            &sem_on_id
    );
    if (status != RTEMS_SUCCESSFUL) {
    	Error_Handler();
    }

    sem_name = rtems_build_name( 'S', 'O', 'F', 'F' );
    status = rtems_semaphore_create( 
            sem_name, 
            1, 
            RTEMS_SIMPLE_BINARY_SEMAPHORE,
            RTEMS_NO_INHERIT_PRIORITY + RTEMS_NO_MULTIPROCESSOR_RESOURCE_SHARING + RTEMS_NO_PRIORITY_CEILING,
            &sem_off_id
    );
    if (status != RTEMS_SUCCESSFUL) {
    	Error_Handler();
    }

    task_name_1 = rtems_build_name( 'L', 'O', 'N', ' ' );
    status = rtems_task_create( task_name_1, 1, RTEMS_MINIMUM_STACK_SIZE,
              RTEMS_DEFAULT_MODES, RTEMS_DEFAULT_ATTRIBUTES, &tid_1 );
    if (status != RTEMS_SUCCESSFUL) {
    	Error_Handler();
    }

    task_name_2 = rtems_build_name( 'L', 'O', 'F', 'F' );
    status = rtems_task_create( task_name_2, 1, RTEMS_MINIMUM_STACK_SIZE,
              RTEMS_DEFAULT_MODES, RTEMS_DEFAULT_ATTRIBUTES, &tid_2 );
    if (status != RTEMS_SUCCESSFUL) {
    	Error_Handler();
    }

    status = rtems_task_start( tid_1, LED_on_task, ARGUMENT );
    if (status != RTEMS_SUCCESSFUL) {
    	Error_Handler();
    }
    status = rtems_task_start( tid_2, LED_off_task, ARGUMENT );
    if (status != RTEMS_SUCCESSFUL) {
    	Error_Handler();
    }


    rtems_task_exit();
}


