# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)

target_sources(app PRIVATE src/main.c)



## 2022-03-30
## - STEP - noting build time error when adding CONFIG_NRF_MODEM_LIB=y in hello_world prj.conf:

# /home/ted/projects/zephyr-based/nrf/lib/nrf_modem_lib/nrf91_sockets.c:21:10: fatal error: sockets_internal.h: No such file or directory
#    21 | #include <sockets_internal.h>


## - STEP - searching for not found header file:

# ted@dev-host-2:~/projects/zephyr-based$ find . -name sockets_internal.h
# ./zephyr/subsys/net/lib/sockets/sockets_internal.h



## - STEP - adapting stanza from aws-iot-stand-along project - TMH:

# 2021-11-16 - attempt to utilize Zephyr kernel timing reporting:
# include_directories(../zephyr/include)
#include_directories(../zephyr/subsys/net/lib/sockets)
#include_directories(../zephyr/subsys)


include_directories(../rfxlib/nrf_modem/include)


