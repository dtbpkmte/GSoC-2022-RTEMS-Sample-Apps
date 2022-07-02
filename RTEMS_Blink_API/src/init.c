#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define CONFIGURE_INIT
#include "system.h"

rtems_gpio *led;
rtems_id sem_on_id, sem_off_id;

#define ARGUMENT 0

rtems_task Init(
  rtems_task_argument ignored
)
{
    rtems_status_code volatile status;

    rtems_gpio_begin();

	status = rtems_gpio_get(LED_VPIN, &led);
	if (status != RTEMS_SUCCESSFUL) {
		Error_Handler();
	}
	rtems_gpio_init(led);

	rtems_gpio_set_pin_mode(led, RTEMS_GPIO_PINMODE_OUTPUT_PP);
	rtems_gpio_set_pull(led, RTEMS_GPIO_NOPULL);

    rtems_gpio_write(led, RTEMS_GPIO_PIN_RESET);

    rtems_name        sem_name, task_name_1, task_name_2;
    rtems_id          tid_1, tid_2;

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

void Error_Handler(void) {
	rtems_interrupt_level level;
	rtems_interrupt_disable(level);
	while (1) {

	}
}

