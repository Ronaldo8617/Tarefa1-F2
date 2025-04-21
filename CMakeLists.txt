cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")


include(pico_sdk_import.cmake)

project(Tarefa1-F2 C CXX ASM)

pico_sdk_init()

add_executable(Tarefa1-F2 Tarefa1-F2.c
                lib/rgb.c
                lib/ssd1306.c
                lib/buttons.c
                lib/display_init.c
                lib/matrixws.c
                lib/buzzer.c
                func/funcionalidades.c
                func/quadrado.c)

pico_set_program_name(Tarefa1-F2 "Tarefa1-F2")
pico_set_program_version(Tarefa1-F2 "0.1")

pico_enable_stdio_uart(Tarefa1-F2 1)
pico_enable_stdio_usb(Tarefa1-F2 1)

target_link_libraries(Tarefa1-F2
        pico_stdlib
        hardware_pwm
        hardware_i2c
        hardware_adc
        hardware_pio)

target_include_directories(Tarefa1-F2 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(Tarefa1-F2 
        
        )

pico_add_extra_outputs(Tarefa1-F2)

