#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/mcc.h"
#include "hp_ltc5851.h"
#include "tick.h"
#include "string.h"
#include "pushbutton_device.h"
#include "dht11_device.h"
#include "us020_device.h"

#define SHORT_CLICK 100 // Time in ms for a short click recognition.
#define LONG_CLICK 3000 // Time in ms for a long click recognition.
#define DISPLAY_ALT 700 // Switch time for alternating display in ms.
#define MODE_TIMEOUT 10000  // Timeout in ms before going back to mode normal.

#define MAX_DATA_ADDR 1000 // Should be an even number. Max readings is MAX_ADDR/2
#define CONFIG_ADDR 1020

uint8_t mode = NORMAL;
uint8_t displayMode = ALT_TEMP_HUMIDITY;
uint8_t interval = 0; // Frequency to log data in minutes.
uint32_t modeTimeout = 0;
int16_t readPtr = 0; // Pointer to the next address to be written.
uint8_t writeOF = 0; // Overflow bit.
uint16_t writePtr = 0; // Pointer to the next address to be read.
char mdisp[5][5] = {'\0'}; // Display variable.
uint8_t mdispLen = 0, mdispDot[5] = 0; // Number of Alt displays and dot.


void modeHandler(uint16_t dur, uint8_t button);
void writeData(uint8_t temp, uint8_t humidity);
void resetData(void);
void AltDisplay(const char[5][5], uint8_t len, uint8_t dots[]);

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
      modeHandler(dur, BUTTON_A);
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
      modeHandler(dur, BUTTON_B);
      pbB = ST_HIGH;
      break;
  }
}

// modeHandler handles the switches between different modes.

void modeHandler(uint16_t dur, uint8_t button) {
  char disp[5] = "";
  uint16_t nReadings = 0;

  if (mode == NORMAL) {
    // Change display mode.
    if (dur >= SHORT_CLICK && dur < LONG_CLICK && button == BUTTON_A) {
      switch (displayMode) {
        case TEMP_ONLY:
          displayMode = HUMIDITY_ONLY;
          break;
        case HUMIDITY_ONLY:
          displayMode = TEMP_HUMIDITY;
          break;
        case TEMP_HUMIDITY:
          displayMode = ALT_TEMP_HUMIDITY;
          break;
        case ALT_TEMP_HUMIDITY:
          displayMode = TEMP_ONLY;
          break;
      }
    }
    // Interval select screen.
    if (dur >= LONG_CLICK && button == BUTTON_A) {
      modeTimeout = TickGet();
      mode = SELECT_INTERVAL;
      sprintf(disp, "I%03d", interval);
      Display(disp, 0);
    }
    // Switch to Data View mode.
    if (dur >= SHORT_CLICK && button == BUTTON_B) {
      modeTimeout = TickGet();
      if (writeOF) {
        nReadings = MAX_DATA_ADDR / 2;
      } else {
        nReadings = writePtr / 2;
      }
      if (nReadings <= 0) {
        Display("----", 0);
        return;
      }
      readPtr = -999; // -999 indicates mode change to data view.
      mode = VIEW_STORED;
      mdispLen = 1;
      sprintf(mdisp[0], "A%03d", nReadings);
      mdispDot[0] = 0;
    }
    return;
  }


  if (mode == VIEW_STORED) {
    modeTimeout = TickGet();
    uint8_t cnt = 0;

    if (dur > SHORT_CLICK && button == BUTTON_A) { // + +
      // Initialize read pointer to the latest data point.
      if (readPtr == -999) {
        readPtr = writePtr - 2;
        if (readPtr < 0 && writeOF) {
          readPtr = MAX_DATA_ADDR - 2;
        }
      } else if (writeOF && readPtr == MAX_DATA_ADDR - 2) {
        readPtr = 0;
      } else {
        readPtr += 2;
      }
    }
    if (dur > SHORT_CLICK && button == BUTTON_B) { // - -
      if (readPtr == -999) {// Initialize read pointer to the oldest data point.
        if (writeOF) {
          readPtr = writePtr;
        } else {
          readPtr = 0;
        }
      } else if (writeOF && readPtr == 0) {
        readPtr = MAX_DATA_ADDR - 2;
      } else {
        readPtr -= 2;
      }
    }

    mdispLen = 2;
    sprintf(mdisp[0], "R%03d", readPtr/2);
    sprintf(mdisp[1], "%02d%02d", DATAEE_ReadByte(readPtr + 1), DATAEE_ReadByte(readPtr));
    mdispDot[0] = 1;
    mdispDot[1] = 6;
  }

  if (mode == SELECT_INTERVAL) {
    modeTimeout = TickGet();
    if (dur > SHORT_CLICK && button == BUTTON_A) {
      if (interval < 5) {
        interval += 1;
      } else if (interval >= 5 && interval <= 200) {
        interval += 5;
      } else if (interval > 200) {
        interval = 0;
      }
      resetData();
      DATAEE_WriteByte(CONFIG_ADDR + 3, interval);
      sprintf(disp, "I%03d", interval);
      Display(disp, 0);
    }
    return;
  }
}

void DisplayTask(void) {
  static uint32_t last = 0;
  int8_t err = 0;
  char disp[3][5] = {'\0'};

  uint32_t now = TickGet();
  if ((now - last) / (TICK_MILLISECOND) >= DISPLAY_ALT) {
    last = now;
 
    if (!SEL_GetValue()) {
      sprintf(disp[0], "%03dc", GetDistance());
      Display(disp[0], 0);
      return;
    }

    if (mode == NORMAL) {
      err = GetError();
      if (err < 0) {
        DisplayError(err);
      } else {
        uint8_t temp = GetTemp();
        uint8_t humidity = GetHumidity();
        uint8_t dots[] = {0, 0, 0};
        sprintf(disp[0], "T%03d", temp);
        sprintf(disp[1], "H%03d", humidity);
        sprintf(disp[2], "%02d%02d", temp, humidity);
        switch (displayMode) {
          case ALT_TEMP_HUMIDITY:
            AltDisplay(disp, 2, dots);
            break;
          case TEMP_ONLY:
            Display(disp[0], 0);
            break;
          case HUMIDITY_ONLY:
            Display(disp[1], 0);
            break;
          case TEMP_HUMIDITY:
            Display(disp[2], 6);
        }
      }
    }

    if (mode == VIEW_STORED) {
      AltDisplay(mdisp, mdispLen, mdispDot);
    }

  }
}

//AltDisplay alternates between the strings in d[][] upto len. 

void AltDisplay(const char d[5][5], uint8_t len, uint8_t dots[]) {
  static char bSwitch = 0;
  Display(d[bSwitch], dots[bSwitch]);
  bSwitch++;
  if (bSwitch >= len) {
    bSwitch = 0;
  }
}

void DisplayError(int8_t errorCode) {
  switch (errorCode) {
    case ERR_DHT11_TIMEOUT_RESPONSE:
      Display("E-01", 0);
      break;
    case ERR_DHT11_CHECKSUM_FAILURE:
      Display("E-02", 0);
      break;
    case ERR_DHT11_TIMEOUT_DATA:
      Display("E-03", 0);
      break;
    default:
      Display("E-00", 0);
      break;
  }
}

void WriteMemoryTask(void) {
  static uint32_t last = 0;
  static uint8_t i = 1;
  int8_t temp = 0, humidity = 0, err = 0;

   if (!interval) {
     return;
   }

  uint32_t now = TickGet();
   if ((now - last) / TICK_MINUTE > interval) { 
 // if ((now - last) / TICK_SECOND > 5) {
    last = now;
    err = GetError();
    temp = GetTemp();
    humidity = GetHumidity();
    if (err < 0) {
      writeData(0, 0);
    }
    writeData(temp, humidity);
    //writeData(i, i);
    i += 1;
  }
}

// writeData writes data to EEPROM using the first 1000 bytes.

void writeData(uint8_t temp, uint8_t humidity) {
  uint8_t wrLSB = 0, wrMSB = 0;

  DATAEE_WriteByte(writePtr, humidity);
  DATAEE_WriteByte(writePtr + 1, temp);
  writePtr += 2;

  if (writePtr >= MAX_DATA_ADDR) {
    writePtr = 0;
    writeOF = 1;
  }

  // Store write pointer in case of power loss.
  wrMSB = writeOF;
  wrLSB = writePtr & 0xFF;
  wrMSB = wrMSB << 2 | writePtr >> 8;

  DATAEE_WriteByte(CONFIG_ADDR, 189); // Write magic number.
  DATAEE_WriteByte(CONFIG_ADDR + 1, wrMSB);
  DATAEE_WriteByte(CONFIG_ADDR + 2, wrLSB);
}

void resetData(void) {
  writePtr = 0;
  writeOF = 0;
}

void PushButtonInit(void) {
  uint8_t wrLSB = 0, wrMSB = 0;

  // Load config from eeprom if was initialized by checking for magic number
  // 189 at CONFIG_ADDR. 
  if (DATAEE_ReadByte(CONFIG_ADDR) != 189) {
    return;
  }
  wrMSB = DATAEE_ReadByte(CONFIG_ADDR + 1);
  wrLSB = DATAEE_ReadByte(CONFIG_ADDR + 2);
  interval = DATAEE_ReadByte(CONFIG_ADDR + 3);

  writeOF = wrMSB >> 2;
  writePtr = wrMSB & 0x3;
  writePtr = writePtr << 8 | wrLSB;
}