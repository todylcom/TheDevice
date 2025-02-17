#include <stdio.h>

#include "app.h"
#include "leds.h"
#include "main.h"

/*
  compiler was not recognizing the function prototype declaration within
  Core/Src/main.c, so I had to externalize the prototype to get the compiler to
  work
*/
extern void SystemClock_Config(void);

void app() {
  printf("App started!\r\n");
  uint32_t level = 10;

  while (1) {
    start_leds();

    morse_code_todyl(
        100, 200, 600,
        200); // Brightness = 100, dot = 200ms, dash = 600ms, space = 200ms
    back_and_forth(100, 15, level);
    running_lights(200, 20, 10, level);
    alternating_letters(200, 10, 5, level);
    breathing();

    // Flash letters in sequence
    flash_letters(level);
    // Make all letters flash at the same time, twice
    flash_multiple_times(level, 2);

    // new features on 02/17/2025
    random_flash(500, 5);
    random_brightness(level, 5, 5);
    fadeout(level);

    set_all_leds(0);
    stop_leds();

    // Sleep until button pressed
    HAL_PWREx_EnableUltraLowPower();
    HAL_PWREx_EnableFastWakeUp();
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
    // Wake up here //
    SystemClock_Config();
  }
}
