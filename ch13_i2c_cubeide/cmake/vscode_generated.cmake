# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Compiler options
target_compile_options(${BUILD_UNIT_0_NAME} PRIVATE
    $<$<COMPILE_LANGUAGE:C>: ${CUBE_CMAKE_C_FLAGS}>
    $<$<COMPILE_LANGUAGE:CXX>: ${CUBE_CMAKE_CXX_FLAGS}>
    $<$<COMPILE_LANGUAGE:ASM>: ${CUBE_CMAKE_ASM_FLAGS}>
)

# Linker options
target_link_options(${BUILD_UNIT_0_NAME} PRIVATE ${CUBE_CMAKE_EXE_LINKER_FLAGS})

# Add sources to executable/library
target_sources(${BUILD_UNIT_0_NAME} PRIVATE
    "Src/i2c.c"
    "Src/main.c"
    "Src/syscalls.c"
    "Src/sysmem.c"
    "Src/uart.c"
    "Startup/startup_stm32g071rbtx.s"
)

target_include_directories(${BUILD_UNIT_0_NAME} PRIVATE
    "Inc"
    "chip_headers/CMSIS/Include"
    "chip_headers/CMSIS/Device/ST/STM32G0xx/Include"
)

configure_file("${CMAKE_SOURCE_DIR}/STM32G071RBTX_FLASH.ld" "${CMAKE_BINARY_DIR}" COPYONLY)

set_target_properties(${BUILD_UNIT_0_NAME} PROPERTIES LINK_DEPENDS "STM32G071RBTX_FLASH.ld")

