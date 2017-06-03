

#include "mcc_generated_files/mcc.h"
#include "us020_device.h"
#include "tick.h"

#define TIMEOUT 25

uint16_t Dist = 0;

uint16_t GetDistance(void) {
  return Dist;
}

void ultrasonicTask(void) {
  static uint32_t ticks = 0;
  static uint16_t dist = 0;

  static enum {
    SEND_TRIGGER = 0,
    WAIT_HIGH,
    MEASURE_ECHO,
    SEND_RESPONSE,
    RESET,
    READY,
  } state = SEND_TRIGGER;

  // State Machine.
  switch (state) {
    case SEND_TRIGGER:
      US_TRIG_SetHigh();
      __delay_us(10);
      US_TRIG_SetLow();
      ticks = TickGet();
      state = WAIT_HIGH;
      break;

    case WAIT_HIGH:
      if ((TickGet() - ticks) / TICK_MILLISECOND > TIMEOUT) {
        state = RESET;
        break;
      }
      if (!US_ECHO_GetValue()) {
        break;
      }
      ticks = TickGet();
      state = MEASURE_ECHO;
      break;

    case MEASURE_ECHO:
      if ((TickGet() - ticks) / TICK_MILLISECOND > TIMEOUT) {
        state = RESET;
        break;
      }
      if (US_ECHO_GetValue()) {
        break;
      }
      dist = (TickGet() - ticks)*1000 / TICK_MILLISECOND / 58.3;
      state = SEND_RESPONSE;
      break;

    case SEND_RESPONSE:
      Dist = dist;
      state = RESET;
      break;

    case RESET:
      ticks = TickGet();
      state = READY;
      break;

    case READY:
      if ((TickGet() - ticks)/TICK_MILLISECOND < 400) {
        return;
      }
      state = SEND_TRIGGER;
      break;
  }

}