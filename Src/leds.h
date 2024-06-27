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
