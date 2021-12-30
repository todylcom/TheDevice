#include <errno.h>
#include <sys/unistd.h>
#include <string.h>
#include "main.h"
#include "ring_buffer.h"

extern UART_HandleTypeDef DEBUG_UART;

static uint8_t     printf_buffer[512];
static uint8_t     initialized = 0;
static uint16_t    tail = 0;
static uint16_t    head = 0;
static uint16_t    transfer_in_progress = 0;


static void printf_dma_completed(UART_HandleTypeDef *huart)
{
  tail += transfer_in_progress;
  if (tail == head) {
    // All sent
    tail = 0;
    head = 0;
    transfer_in_progress = 0;
    return;
  }
  // More data needs to be sent
  transfer_in_progress = head - tail;
  HAL_UART_Transmit_DMA(&DEBUG_UART, &printf_buffer[tail], transfer_in_progress);
}

// These functions are implemented in the GCC C library as
// stub routines with "weak" linkage so just re-define it
// to write to UART1
int _write(int file, char *data, int len)
{
  if ((file != STDOUT_FILENO) && (file != STDERR_FILENO)) {
    errno = EBADF;
    return -1;
  }

  if (len == 0) {
    return 0;
  }

  if (!initialized) {
    DEBUG_UART.TxCpltCallback = printf_dma_completed;
    initialized = 1;
  }

  // buffer overflown
  if (len >= sizeof(printf_buffer) - head) {
    return 0;
  }

  memcpy(&printf_buffer[head], data, len);
  head += len;

  if (!transfer_in_progress) {
    transfer_in_progress = len;
    HAL_UART_Transmit_DMA(&DEBUG_UART, printf_buffer, len);
  }
  // else just wait until tx completed

  return len;
}
