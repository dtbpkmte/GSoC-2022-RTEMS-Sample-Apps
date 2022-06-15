#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define CONFIGURE_INIT
#include "system.h"
#include <stdio.h>
#include <stdint.h>

rtems_id sem_on_id, sem_off_id;

// /* forward declarations to avoid warnings */
// rtems_task Init(rtems_task_argument ignored);

#define ARGUMENT 0

rtems_task Init(
  rtems_task_argument ignored
)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

	/* Enable the GPIO_LED Clock */
    __HAL_RCC_GPIOD_CLK_ENABLE();

	/* Configure the GPIO_LED pin */
	GPIO_InitStruct.Pin = GPIO_PIN_14;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);

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

    sem_name = rtems_build_name( 'S', 'O', 'F', 'F' );
    status = rtems_semaphore_create( 
            sem_name, 
            1, 
            RTEMS_SIMPLE_BINARY_SEMAPHORE,
            RTEMS_NO_INHERIT_PRIORITY + RTEMS_NO_MULTIPROCESSOR_RESOURCE_SHARING + RTEMS_NO_PRIORITY_CEILING,
            &sem_off_id
    );

    task_name_1 = rtems_build_name( 'L', 'O', 'N', ' ' );
    status = rtems_task_create( task_name_1, 1, RTEMS_MINIMUM_STACK_SIZE,
              RTEMS_DEFAULT_MODES, RTEMS_DEFAULT_ATTRIBUTES, &tid_1 );

    task_name_2 = rtems_build_name( 'L', 'O', 'F', 'F' );
    status = rtems_task_create( task_name_2, 1, RTEMS_MINIMUM_STACK_SIZE,
              RTEMS_DEFAULT_MODES, RTEMS_DEFAULT_ATTRIBUTES, &tid_2 );

    status = rtems_task_start( tid_1, LED_on_task, ARGUMENT );
    status = rtems_task_start( tid_2, LED_off_task, ARGUMENT );


    rtems_task_exit();
}
