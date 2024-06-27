#include "main.h"
#include "leds.h"

static uint32_t counter = 0;

#define NUM_LEDS 6

enum leds {
  LOGO = 0,
  LETT_T,
  LETT_O,
  LETT_D,
  LETT_Y,
  LETT_L,
};

static uint16_t port_pins[NUM_LEDS] = {
  LOGO_Pin,
  LETT_T_Pin,
  LETT_O_Pin,
  LETT_D_Pin,
  LETT_Y_Pin,
  LETT_L_Pin
};
static volatile uint8_t dutys[NUM_LEDS] = {0, 0, 0, 0, 0, 0};

extern TIM_HandleTypeDef htim22;

static void tim22_elapsed_cb(TIM_HandleTypeDef* htim)
{
  // This callback is being executed around 10Khz (10000 times per second) when timer enabled
  counter++;
  if (counter > 100) {
    counter = 0;
  }
  for (uint32_t i = 0; i < NUM_LEDS; i++) {
    HAL_GPIO_WritePin(GPIOA, port_pins[i], counter < dutys[i] ? 1: 0);
  }
}

void start_leds()
{
  counter = 0;
  htim22.PeriodElapsedCallback = tim22_elapsed_cb;
  HAL_TIM_Base_Start_IT(&htim22);
}

void stop_leds()
{
  HAL_TIM_Base_Stop_IT(&htim22);
  for (uint32_t i = 0; i < NUM_LEDS; i++) {
    HAL_GPIO_WritePin(GPIOA, port_pins[i], 0);
  }
}

void set_logo(uint8_t level)
{
  dutys[LOGO] = level;
}

void set_letter_t(uint8_t level)
{
  dutys[LETT_T] = level;
}

void set_letter_o(uint8_t level)
{
  dutys[LETT_O] = level;

}

void set_letter_d(uint8_t level)
{
  dutys[LETT_D] = level;

}

void set_letter_y(uint8_t level)
{
  dutys[LETT_Y] = level;

}

void set_letter_l(uint8_t level)
{
  dutys[LETT_L] = level;

}

void set_all_letters(uint8_t level)
{
  for (uint32_t i = LETT_T; i < NUM_LEDS; i++) {
    dutys[i] = level;
  }
}

void set_all_leds(uint8_t level)
{
  for (uint32_t i = 0; i < NUM_LEDS; i++) {
    dutys[i] = level;
  }
}

