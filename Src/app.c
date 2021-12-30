#include "main.h"
#include "app.h"

void app()
{
  while (1) {
    HAL_GPIO_WritePin(LOGO_GPIO_Port, LOGO_Pin, 1);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(LOGO_GPIO_Port, LOGO_Pin, 0);
    HAL_Delay(1000);
  }
}
