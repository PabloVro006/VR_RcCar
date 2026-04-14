#ifndef CONFIG_H
#define CONFIG_H

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "status.h"

#define LED_ON_CODE 89
#define LED_OFF_CODE 78

typedef uint8_t u8;
typedef int8_t i8;
typedef int16_t i16;

Status run_program(void);

#endif /* CONFIG_H */