
// Content of usr_fun.c
#include "usr_fun.h"
#include <zephyr/kernel.h>

	#ifdef CONFIG_USR_FUN
void usr_fun(void)
{
    printk("Message in a user function.\n");
}
#else
void usr_fun(void){}

#endif
