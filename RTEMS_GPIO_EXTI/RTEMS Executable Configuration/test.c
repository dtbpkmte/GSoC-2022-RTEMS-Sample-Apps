#ifndef CONFIGURE_GPIO_MAXIMUM_CONTROLLERS 

#ifndef BSP_GPIO_NUM_CONTROLLERS
#error "BSP_GPIO_NUM_CONTROLLERS is not defined by BSP"
#endif

#define CONFIGURE_GPIO_MAXIMUM_CONTROLLERS BSP_GPIO_NUM_CONTROLLERS

#endif

static rtems_gpio_ctrl_t *ctrl_table[CONFIGURE_GPIO_MAXIMUM_CONTROLLERS];
static uint32_t pin_map[CONFIGURE_GPIO_MAXIMUM_CONTROLLERS+1] = {0};
0 16 32
static uint32_t num_ctrl = 0;

register_controller(rtems_gpio_ctrl_t *ctrl, uint32_t max_pin) {
    ctrl_table[num_ctrl] = ctrl;
    pin_map[num_ctrl+1] = pin_map[num_ctrl] + max_pin;
    ++num_ctrl;
}

rtems_gpio_get_ctrl(uint32_t virt_pin) {
    uint32_t pin;
    for (i = 1; i <= num_ctrl; ++i) {
        if (virt_pin < pin_map[i]) {
            pin = virt_pin - pin_map[i-1];
            break;
        }
    }
    if (i > num_ctrl)
        return RTEMS_UNSATISFIED;

    ctrl_table[i]
}
