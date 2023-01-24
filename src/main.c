/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(module_app);

#include <zephyr/kernel.h>
#include <zephyr/linker/sections.h>
#include <errno.h>
#include <zephyr/shell/shell.h>
#include <libsample.h>
#include <jansson.h>
#include <msgpack.h>

static struct k_sem quit_lock = {0};

static int cmd_sample_quit(const struct shell *shell,
                          size_t argc, char *argv[])
{
    shell_print(shell,"OK");
    shell_print(shell,"%.2f",(double)3.14159);
    k_sem_give(&quit_lock);
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sample_commands,
        SHELL_CMD(quit, NULL,
                  "Quit the sample application\n",
                  cmd_sample_quit),
        SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sample, &sample_commands,
                   "Sample application commands", NULL);

#define APP_BANNER "My first MCU program"

//LOG_LEVEL_SET(LOG_LEVEL_INF);

void main(void)
{
    static struct k_event init_event;

    msgpack_sbuffer sbuf = {0};

    printk("Hello libsample %s %s\n", LIBSAMPLE_VERSION, jansson_version_str());
    msgpack_sbuffer_init(&sbuf);
    msgpack_sbuffer_destroy(&sbuf);

    k_event_init(&init_event);
    LOG_INF(APP_BANNER);
    k_malloc(100);
    k_sem_init(&quit_lock, 0, UINT_MAX);
    LOG_INF("Starting! %s", CONFIG_BOARD);
    k_sem_take(&quit_lock, K_FOREVER);
    LOG_INF("Stopping...");
}
