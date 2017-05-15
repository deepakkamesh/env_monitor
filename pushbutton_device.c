#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/mcc.h"
#include "hp_ltc5851.h"
#include "tick.h"
#include "string.h"
#include "pushbutton_device.h"
#include "dht11_device.h"

#define SHORT_CLICK 200
#define LONG_CLICK 3000
#define MODE_TIMEOUT 5000
#define DELTA_INTERVAL 5

uint8_t mode = NORMAL;
uint8_t displayMode = TEMP_HUMIDITY;
uint8_t interval = 0; // Frequency to log data in minutes.
uint32_t modeTimeout = 0;
uint16_t readPtr = 0; // Pointer to the next address to be written.
uint16_t writePtr = 0; // Pointer to the next address to be read.


void ModeHandler(uint16_t dur, uint8_t button);

void PushButtonTask(void) {
  static uint16_t dur = 0;
  static uint32_t startA = 0, startB = 0;

  // Automatically restore mode to Normal.
  if (mode != NORMAL && (TickGet() - modeTimeout) / TICK_MILLISECOND > MODE_TIMEOUT) {
    mode = NORMAL;
  }

  static enum uint8_t {
    ST_HIGH = 0,
    ST_LOW,
  } pbA = ST_HIGH, pbB = ST_HIGH;

  switch (pbA) {
    case ST_HIGH:
      if (!PB_A_GetValue()) {
        startA = TickGet();
        pbA = ST_LOW;
      }
      break;

    case ST_LOW:
      if (!PB_A_GetValue()) {
        break;
      }
      dur = (TickGet() - startA) / TICK_MILLISECOND;
      ModeHandler(dur, BUTTON_A);
      pbA = ST_HIGH;
      break;
  }

  switch (pbB) {
    case ST_HIGH:
      if (!PB_B_GetValue()) {
        startB = TickGet();
        pbB = ST_LOW;
      }
      break;

    case ST_LOW:
      if (!PB_B_GetValue()) {
        break;
      }
      dur = (TickGet() - startB) / TICK_MILLISECOND;
      ModeHandler(dur, BUTTON_B);
      pbB = ST_HIGH;
      break;
  }
}

// modeHandler handles the switches between different modes.

void ModeHandler(uint16_t dur, uint8_t button) {
  char disp[5] = "";

  if (mode == NORMAL) {

    // Change Display Mode.
    if (dur >= SHORT_CLICK && dur < LONG_CLICK && button == BUTTON_A) {
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

    // Switch to interval select screen.
    if (dur >= LONG_CLICK && button == BUTTON_A) {
      mode = SELECT_INTERVAL;
      //TODO: Read from stored value.
      Display("I000");
      modeTimeout = TickGet();
    }

    // Switch to Data View mode.
    if (dur >= LONG_CLICK && button ==  BUTTON_B) {
      mode = VIEW_STORED;
      Display("AAA");
      modeTimeout = TickGet();
    }

    return;
  }


  if (mode == VIEW_STORED) {
    modeTimeout = TickGet();

    if (dur > SHORT_CLICK && button == BUTTON_A) {
      readPtr += 1;
      sprintf(disp, "A%03d", readPtr);
      Display(disp);
    }
    if (dur > SHORT_CLICK && button == BUTTON_B) {
      readPtr -= 1;
      sprintf(disp, "A%03d", readPtr);
      Display(disp);
    }
    return;
  }

  // Select record interval.
  if (mode == SELECT_INTERVAL) {

    modeTimeout = TickGet();
    if (dur > SHORT_CLICK && button == BUTTON_A) {
      if (interval < 5) {
        interval += 1;
      } else if (interval >= 5 && interval <= 200) {
        interval += DELTA_INTERVAL;
      } else if (interval > 200) {
        interval = 0;
      }
      sprintf(disp, "I%03d", interval);
      Display(disp);
    }
    return;
  }
}

void DisplayTask(void) {
  static uint32_t last = 0;
  static char bSwitch = 0;
  int8_t temp = 0, humidity = 0, err = 0;
  char disp[5] = "\0\0\0\0\0";

  uint32_t now = TickGet();
  if ((now - last) / (TICK_MILLISECOND) >= 1000 && mode == NORMAL) {
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

void WriteMemoryTask(void) {
  static uint32_t last = 0;
  int8_t temp = 0, humidity = 0, err = 0;

  if (!interval) {
    return;
  }

  uint32_t now = TickGet();
  if ((now - last) / TICK_MINUTE > interval) {
    last = now;

    err = GetError();
    temp = GetTemp();
    humidity = GetHumidity();

  }

}