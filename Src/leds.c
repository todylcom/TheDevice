#include "leds.h"
#include "main.h"
#include <stdlib.h> 

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

static uint16_t port_pins[NUM_LEDS] = {LOGO_Pin,   LETT_T_Pin, LETT_O_Pin,
                                       LETT_D_Pin, LETT_Y_Pin, LETT_L_Pin};
static volatile uint8_t dutys[NUM_LEDS] = {0, 0, 0, 0, 0, 0};

extern TIM_HandleTypeDef htim22;

static void tim22_elapsed_cb(TIM_HandleTypeDef *htim) {
  // This callback is being executed around 10Khz (10000 times per second) when
  // timer enabled
  counter++;
  if (counter > 100) {
    counter = 0;
  }
  for (uint32_t i = 0; i < NUM_LEDS; i++) {
    HAL_GPIO_WritePin(GPIOA, port_pins[i], counter < dutys[i] ? 1 : 0);
  }
}

void start_leds() {
  counter = 0;
  htim22.PeriodElapsedCallback = tim22_elapsed_cb;
  HAL_TIM_Base_Start_IT(&htim22);
}

void stop_leds() {
  HAL_TIM_Base_Stop_IT(&htim22);
  for (uint32_t i = 0; i < NUM_LEDS; i++) {
    HAL_GPIO_WritePin(GPIOA, port_pins[i], 0);
  }
}

void set_logo(uint8_t level) { dutys[LOGO] = level; }

void set_letter_t(uint8_t level) { dutys[LETT_T] = level; }

void set_letter_o(uint8_t level) { dutys[LETT_O] = level; }

void set_letter_d(uint8_t level) { dutys[LETT_D] = level; }

void set_letter_y(uint8_t level) { dutys[LETT_Y] = level; }

void set_letter_l(uint8_t level) { dutys[LETT_L] = level; }

void set_all_letters(uint8_t level) {
  for (uint32_t i = LETT_T; i < NUM_LEDS; i++) {
    dutys[i] = level;
  }
}

void set_all_leds(uint8_t level) {
  for (uint32_t i = 0; i < NUM_LEDS; i++) {
    dutys[i] = level;
  }
}

void alternating_letters(int initial_delay, int delay_step, int repetitions,
                         int level) {
  int delay = initial_delay;

  for (int i = 0; i < repetitions; i++) {
    // First set
    set_logo(level);
    set_letter_o(level);
    set_letter_y(level);
    HAL_Delay(delay);

    set_logo(0);
    set_letter_o(0);
    set_letter_y(0);
    HAL_Delay(delay);

    // Adjust delay for the second set
    delay += delay_step;

    // Second set
    set_letter_t(level);
    set_letter_d(level);
    set_letter_l(level);
    HAL_Delay(delay);

    set_letter_t(0);
    set_letter_d(0);
    set_letter_l(0);
    HAL_Delay(delay);

    // Reset delay after each repetition
    delay = initial_delay;
  }
}

void back_and_forth(int initial_delay, int delay_step, int level) {
  int delay = initial_delay;

  // left to right
  set_logo(level);
  HAL_Delay(delay);
  delay -= delay_step;

  set_letter_t(level);
  HAL_Delay(delay);
  delay -= delay_step;

  set_letter_o(level);
  HAL_Delay(delay);
  delay -= delay_step;

  set_letter_d(level);
  HAL_Delay(delay);
  delay -= delay_step;

  set_letter_y(level);
  HAL_Delay(delay);
  delay -= delay_step;

  set_letter_l(level);
  HAL_Delay(delay);
  delay -= delay_step;

  // Right to left
  set_letter_l(0);
  HAL_Delay(delay);
  delay += delay_step;

  set_letter_y(0);
  HAL_Delay(delay);
  delay += delay_step;

  set_letter_d(0);
  HAL_Delay(delay);
  delay += delay_step;

  set_letter_o(0);
  HAL_Delay(delay);
  delay += delay_step;

  set_letter_t(0);
  HAL_Delay(delay);
  delay += delay_step;

  set_logo(0);
  HAL_Delay(delay);
}

void running_lights(int initial_delay, int delay_step, int repetitions,
                    int level) {
  int delay = initial_delay;

  for (int i = 0; i < repetitions; i++) {
    set_logo(level);
    HAL_Delay(delay);
    set_logo(0);

    set_letter_t(level);
    HAL_Delay(delay);
    set_letter_t(0);

    set_letter_o(level);
    HAL_Delay(delay);
    set_letter_o(0);

    set_letter_d(level);
    HAL_Delay(delay);
    set_letter_d(0);

    set_letter_y(level);
    HAL_Delay(delay);
    set_letter_y(0);

    set_letter_l(level);
    HAL_Delay(delay);
    set_letter_l(0);

    if (delay > delay_step) {
      delay -= delay_step; // Decrease delay for faster chasing
    }
  }
}

void morse_code_todyl(int brightness, int dot_delay, int dash_delay,
                      int space_delay) {
  // Define Morse code for TODYL
  const char *morse_todyl[] = {
      "-",    // T
      "---",  // O
      "-..",  // D
      "-.--", // Y
      ".-.."  // L
  };

  // declare array of function pointers
  void (*set_letter[])(uint8_t) = {set_letter_t, set_letter_o, set_letter_d,
                                   set_letter_y, set_letter_l};

  // Animate each letter
  for (int i = 0; i < 5; i++) {
    const char *code = morse_todyl[i];
    for (int j = 0; code[j] != '\0'; j++) {
      set_letter[i](brightness);
      HAL_Delay(code[j] == '.' ? dot_delay : dash_delay);
      set_letter[i](0);
      HAL_Delay(space_delay); // Pause between symbols
    }
    HAL_Delay(3 * space_delay); // Pause between letters
  }
}

void breathing() {
  int max_brightness = 10;
  int step = 5;
  int delay = 250;

  // Fade in
  for (int brightness = 0; brightness <= max_brightness; brightness += step) {
    set_logo(brightness);
    set_letter_t(brightness);
    set_letter_o(brightness);
    set_letter_d(brightness);
    set_letter_y(brightness);
    set_letter_l(brightness);
    HAL_Delay(delay);
  }

  // Fade out
  for (int brightness = max_brightness; brightness >= 0; brightness -= step) {
    set_logo(brightness);
    set_letter_t(brightness);
    set_letter_o(brightness);
    set_letter_d(brightness);
    set_letter_y(brightness);
    set_letter_l(brightness);
    HAL_Delay(delay);
  }
}

void flash_letters(int level) {
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
}

void flash_multiple_times(int level, int num_strikes) {
  for (int i = 0; i < num_strikes; i++) {
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
}

void random_flash(int delay_time, int num_strikes) {
  for (int i = 0; i < num_strikes; i++) {
    for (int i = 0; i < NUM_LEDS; i++) {
        int rand_state = rand() % 2;
        int brightness = (rand() % 10) + 1;
        if (rand_state) {
            dutys[i] = brightness;
        } else {
            dutys[i] = 0;
        }
    }
    HAL_Delay(delay_time);
  }
}

void random_brightness(int max_brightness, int min_brightness, int num_strikes) {
  for (int i = 0; i < num_strikes; i++) {
    int brightness = rand() % (max_brightness - min_brightness + 1) + min_brightness;
    for (int i = 0; i < NUM_LEDS; i++) {
      dutys[i] = brightness;
    }
    HAL_Delay(500);
  }
}

void fadeout(int level) {
  for (int32_t i = level; i >= 0; i--) {
    set_all_leds(i);
    HAL_Delay(200);
  }
}


