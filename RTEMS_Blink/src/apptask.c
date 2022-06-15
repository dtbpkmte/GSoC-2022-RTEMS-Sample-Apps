/* SPDX-License-Identifier: BSD-2-Clause */

/*  Application_task
 *
 *  This routine is as an example of an application task which
 *  prints a message including its RTEMS task id.  This task
 *  then invokes exit to return to the monitor.
 *
 *  Input parameters:  NONE
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989-2011.
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

#include "system.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Turns LED2 on
 */
rtems_task LED_on_task(
    rtems_task_argument argument
)
{
    rtems_id          tid;
    rtems_status_code status;
    unsigned int      a = (unsigned int) argument;

    while (1) {
        status = rtems_semaphore_obtain(sem_on_id, RTEMS_WAIT, RTEMS_NO_TIMEOUT);

        // LD2 is at PA5
        *GPIOA_BSRR = 1 << 5;

        status = rtems_task_wake_after(rtems_clock_get_ticks_per_second());

        status = rtems_semaphore_release(sem_off_id);
    }
    //exit( 0 );
}

/*
 * Turns LED2 off
 */
rtems_task LED_off_task(
    rtems_task_argument argument
)
{
    rtems_id          tid;
    rtems_status_code status;
    unsigned int      a = (unsigned int) argument;

    while (1) {
        status = rtems_semaphore_obtain(sem_off_id, RTEMS_WAIT, RTEMS_NO_TIMEOUT);

        *GPIOA_BSRR = 1 << 21;

        status = rtems_task_wake_after(rtems_clock_get_ticks_per_second());

        status = rtems_semaphore_release(sem_on_id);
  }
  //exit( 0 );
}
