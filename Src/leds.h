#pragma once

#include <stdint.h>

void start_leds();
void stop_leds();

void set_logo(uint8_t level);
void set_letter_t(uint8_t level);
void set_letter_o(uint8_t level);
void set_letter_d(uint8_t level);
void set_letter_y(uint8_t level);
void set_letter_l(uint8_t level);
void set_all_letters(uint8_t level);
void set_all_leds(uint8_t level);

void back_and_forth(int initial_delay, int delay_step, int level);
void running_lights(int initial_delay, int delay_step, int repetitions,
                    int level);
void alternating_letters(int initial_delay, int delay_step, int repetitions,
                         int level);
void morse_code_todyl(int brightness, int dot_delay, int dash_delay,
                      int space_delay);
void breathing();

void flash_letters(int level);
void flash_multiple_times(int level, int num_strikes);
void random_flash(int delay_time, int num_strikes);
void random_brightness(int max_brightness, int min_brightness, int num_strikes);
void fadeout(int level);