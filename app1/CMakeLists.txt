cmake_minimum_required(VERSION 3.20.0)

set(ZEPHYR_TOOLCHAIN_VARIANT gnuarmemb)
#set(BOARD_FLASH_RUNNER jlink)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(
    app1
    VERSION 0.1
    DESCRIPTION "Blinky app1"
    LANGUAGES C
    )
    
target_sources(app PRIVATE src/main.c)

target_sources_ifdef(
    CONFIG_USR_FUN
    app
    PRIVATE
    src/usr_fun.c
)