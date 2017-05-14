#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/mcc.h"
#include "hp_ltc5851.h"
#include "tick.h"
#include "string.h"
#include "pushbutton_device.h"
#include "dht11_device.h"


uint8_t displayMode = TEMP_HUMIDITY;

void PushButtonTask(void) {
  static uint32_t dur = 0;
  static uint32_t start = 0;

  static enum uint8_t {
    ST_HIGH = 0,
    ST_LOW,
  } pbA = ST_HIGH;

  switch (pbA) {
    case ST_HIGH:
      if (!PB_A_GetValue()) {
        start = TickGet();
        pbA = ST_LOW;
      }
      break;

    case ST_LOW:
      if (!PB_A_GetValue()) {
        break;
      }
      dur = TickGet() - start;

      if (dur / TICK_MILLISECOND > 200) {
        switch (displayMode) {
          case TEMP_ONLY:
            displayMode = HUMIDITY_ONLY;
            break;
          case HUMIDITY_ONLY:
            displayMode = TEMP_HUMIDITY;
            break;
          case TEMP_HUMIDITY:
            displayMode = TEMP_ONLY;
            break;
        }
      }

      pbA = ST_HIGH;
      break;
  }
}

void DisplayTask(void) {
  static uint32_t last = 0;
  static char bSwitch = 0;
  int8_t temp = 0, humidity = 0, err = 0;
  char disp[5] = "\0\0\0\0\0";

  uint32_t now = TickGet();
  if ((now - last) / (TICK_MILLISECOND) >= 1000) {
    last = now;
    err = GetError();
    temp = GetTemp();
    humidity = GetHumidity();
    if (err < 0) {
      DisplayError(err);
    } else {
      switch (displayMode) {
        case TEMP_HUMIDITY:
          if (bSwitch) {
            sprintf(disp, "T%03d", temp);
            bSwitch = 0;
          } else {
            sprintf(disp, "H%03d", humidity);
            bSwitch = 1;
          }
          Display(disp);
          break;
        case TEMP_ONLY:
          sprintf(disp, "T%03d", temp);
          Display(disp);
          break;
        case HUMIDITY_ONLY:
          sprintf(disp, "H%03d", humidity);
          Display(disp);
          break;
      }
    }
  }
}

void DisplayError(int8_t errorCode) {
  switch (errorCode) {
    case ERR_DHT11_TIMEOUT_RESPONSE:
      Display("E-01");
      break;
    case ERR_DHT11_CHECKSUM_FAILURE:
      Display("E-02");
      break;
    case ERR_DHT11_TIMEOUT_DATA:
      Display("E-03");
      break;
    default:
      Display("E-00");
      break;
  }
}
