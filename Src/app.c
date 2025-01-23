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
    set_letter_t(level);
    HAL_Delay(500);
    set_letter_o(level);
    HAL_Delay(500);
    set_letter_d(level);
    HAL_Delay(500);
    set_letter_y(level);
    HAL_Delay(500);
    set_letter_l(level);
    HAL_Delay(500);
    set_logo(level);
    HAL_Delay(1000);

    // Make all letters flash at the same time, twice
    for (int i = 0; i < 2; i++) {
      set_letter_t(level);
      set_letter_o(level);
      set_letter_d(level);
      set_letter_y(level);
      set_letter_l(level);
      set_logo(level);
      HAL_Delay(500); // Hold for half a second

      set_all_leds(0); // Turn off all letters
      HAL_Delay(500);  // Small delay between flashes
    }

    // Gradually fade out all LEDs
    for (int32_t i = level; i >= 0; i--) {
      set_all_leds(i);
      HAL_Delay(200);
    }
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
