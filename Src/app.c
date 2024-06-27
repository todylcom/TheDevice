#include <stdio.h>

#include "main.h"
#include "app.h"
#include "leds.h"

void app()
{
  printf("App started!\r\n");
  uint32_t level = 10;

  while (1) {
    start_leds();

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

    for (int32_t i = level; i >= 0; i--) {
      set_all_leds(i);
      HAL_Delay(20);
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
