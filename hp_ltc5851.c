#include "mcc_generated_files/mcc.h"
#include "hp_ltc5851.h"
#include "tick.h"
#include "string.h"

char display[5] = "";

int Display(char* d) {
  if (strlen(d) > 4) {
    strcpy(display, "ERR");
    return -1;
  }
  strcpy(display, d);
  return 0;
}

void HPltc5851DisplayTask(void) {
  static char i = 0;
  static uint32_t last = 0;

  uint8_t len = strlen(display);
  uint32_t now = TickGet();
  if ((now - last) / (TICK_MILLISECOND) >= 2) {

    last = now;

    DIGIT1_PORT = 1;
    DIGIT2_PORT = 1;
    DIGIT3_PORT = 1;
    DIGIT4_PORT = 1;

    // Set the digit to be displayed.
    switch (display[len - 1 - i]) {
      case '0':
        MULTIPLEXER = NUM_0;
        break;
      case '1':
        MULTIPLEXER = NUM_1;
        break;
      case '2':
        MULTIPLEXER = NUM_2;
        break;
      case '3':
        MULTIPLEXER = NUM_3;
        break;
      case '4':
        MULTIPLEXER = NUM_4;
        break;
      case '5':
        MULTIPLEXER = NUM_5;
        break;
      case '6':
        MULTIPLEXER = NUM_6;
        break;
      case '7':
        MULTIPLEXER = NUM_7;
        break;
      case '8':
        MULTIPLEXER = NUM_8;
        break;
      case '9':
        MULTIPLEXER = NUM_9;
        break;
      case 'E':
        MULTIPLEXER = ALPHA_E;
        break;
      case 'R':
        MULTIPLEXER = ALPHA_R;
        break;
      case 'A':
        MULTIPLEXER = ALPHA_A;
        break;
      case 'H':
        MULTIPLEXER = ALPHA_H;
        break;
      case 'T':
        MULTIPLEXER = ALPHA_T;
        break;
    }

    // Turn on the digit.
    switch (i) {
      case 0:
        DIGIT1_PORT = 0;
        break;
      case 1:
        DIGIT2_PORT = 0;
        break;
      case 2:
        DIGIT3_PORT = 0;
        break;
      case 3:
        DIGIT4_PORT = 0;
        break;
    }
    i++;

    // Reset counter.
    if (i == len) {
      i = 0;
    }
  }

}


