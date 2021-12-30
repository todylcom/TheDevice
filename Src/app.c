#include <stdio.h>

#include "main.h"
#include "app.h"

void app()
{
  printf("App started!r\n");
  while (1) {
    printf("on\r\n");
    HAL_GPIO_WritePin(LOGO_GPIO_Port, LOGO_Pin, 1);
    HAL_Delay(1000);
    printf("off\r\n");
    HAL_GPIO_WritePin(LOGO_GPIO_Port, LOGO_Pin, 0);
    HAL_Delay(1000);
  }
}
