#include <zephyr/init.h>
#include <zephyr/kernel.h>

static int board_customboard_init(void)
{
    

    printk("Board Initialized\n");

    return 0;
}

SYS_INIT(board_customboard_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);