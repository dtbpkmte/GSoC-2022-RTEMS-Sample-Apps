/* SPDX-License-Identifier: BSD-2-Clause */

/*
 *  COPYRIGHT (c) 1989-2012.
 *  On-Line Applications Research Corporation (OAR).
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define CONFIGURE_INIT
#include "system.h"
#include <stdio.h>
#include <stdint.h>

uint32_t *const RCC_BASE = (uint32_t*) 0x40023800;
uint32_t *const GPIOA_BASE = (uint32_t*) 0x40020000;
uint32_t *const RCC_AHB1RSTR = (uint32_t *) ((uint32_t) RCC_BASE + 0x30);
uint32_t *const GPIOA_MODER = GPIOA_BASE;
uint32_t *const GPIOA_BSRR = (uint32_t *) ((uint32_t) GPIOA_BASE + 0x18);

rtems_id sem_on_id, sem_off_id;

// /* forward declarations to avoid warnings */
// rtems_task Init(rtems_task_argument ignored);

#define ARGUMENT 0

rtems_task Init(
  rtems_task_argument ignored
)
{
    // enable peripheral clock for GPIOA
    *RCC_AHB1RSTR |= 1;
    // set output mode
    *GPIOA_MODER &= ~(3 << 10); // first clear 2 bits
    *GPIOA_MODER |= 1 << 10;
    // turn off LED initially
    *GPIOA_BSRR = 1 << 21;

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
