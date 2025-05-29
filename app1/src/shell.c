#include <zephyr/kernel.h>
#include "usr_fun.h"
#include <stdlib.h>
#include <zephyr/shell/shell.h>
#include <zephyr/logging/log.h>


LOG_MODULE_REGISTER(shell, LOG_LEVEL_DBG);


static int function1(const struct shell *sh, size_t argc, char **argv)
{
        ARG_UNUSED(argc);
        ARG_UNUSED(argv);
        shell_print(sh, "pong");
        return 0;
}

static int function2(const struct shell *sh, size_t argc, char **argv)
{
		ARG_UNUSED(argc);
        ARG_UNUSED(argv);
		ARG_UNUSED(sh);
        
        uint8_t dump[] = "This is a very stupid example demo dump";
        
        LOG_ERR("Error message has level  : %d", LOG_LEVEL_ERR);
	    LOG_WRN("Warning message has level: %d", LOG_LEVEL_WRN);
	    LOG_INF("Info message has level   : %d", LOG_LEVEL_INF);
	    LOG_DBG("Debug message has level  : %d and it always include the function name", LOG_LEVEL_DBG);
	    LOG_HEXDUMP_DBG(&dump, sizeof(dump), "Example dump = ");
        return 0;
}

static int function3(const struct shell *sh, size_t argc, char **argv)
{		
		uint8_t counter = atoi(argv[1]);
        for (size_t i = 0; i < counter; i++){
			shell_print(sh, "Love zephyr");
		}
        return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_demo,
	SHELL_CMD(demo1, NULL, "First demo function", function1),
	SHELL_CMD(demo2, NULL, "Second demo function", function2),
	SHELL_CMD_ARG(demo3, NULL, "Third demo function", function3, 2, 0),
	SHELL_SUBCMD_SET_END /* Array terminated. */
);

SHELL_CMD_REGISTER(demo, &sub_demo, "Log test", NULL);
