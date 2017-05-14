#include "tick.h"
#include "mcc_generated_files/mcc.h"


unsigned short t2OF = 0; // Timer 2 Overflow.
int8_t temp = 0, humidity = 0;

// myTMR2ISR is the callback function for Timer2 Interrupt.

int8_t GetTemp(void) {
  return temp;
}

int8_t GetHumidity(void) {
  return humidity;
}

void myTMR2ISR(void) {
  t2OF = 1;
}

// DHT11Init handles any initialization for DHT11.

void DHT11Init(void) {
  TMR2_SetInterruptHandler(myTMR2ISR);
}

// ReadByte reads 1 byte from DHT11 sensor. It returns -1 on failure.

int16_t ReadByte() {
  uint8_t data, dur;

  for (uint8_t i = 0; i < 8; i++) {
    t2OF = 0;
    TMR2_WriteTimer(0);
    while (!DHT11_GetValue() && !t2OF); // 50us low preamble.
    if (t2OF) {
      return -1;
    }

    TMR2_WriteTimer(0);
    while (DHT11_GetValue() && !t2OF); // Read bit type.
    if (t2OF) {
      return -1;
    }
    dur = TMR2_ReadTimer();
    if (dur < 40) {
      data = data << 1;
    } else {
      data = data << 1 | 0x1;
    }
  }
  return data;
}

// DHT11Task handles requests for Temp and Humidity.

void DHT11Task(void) {
  static uint32_t last = 0;
  uint8_t packet[5];



  uint32_t now = TickGet();
  if ((now - last) / (TICK_MILLISECOND) >= 1000) {
    last = now;

    // Send start signal.
    DHT11_SetDigitalOutput();
    DHT11_SetLow();
    __delay_ms(25);
    DHT11_SetHigh();
    __delay_us(30);
    DHT11_SetLow();
    DHT11_SetDigitalInput();

    // Check response sequence from sensor.
    TMR2_WriteTimer(0);
    while (1) { // 80us low.
      if (DHT11_GetValue()) {
        break;
      }
      if (TMR2_ReadTimer() > 150) {
        temp = -1;
        humidity = -1;
        return;
      }
    }

    while (DHT11_GetValue()); // 80us high.

    // Read data from sensor.
    for (uint8_t i = 0; i <= 4; i++) {
      int16_t data = ReadByte();
      if (data == -1) {
        temp = -1;
        humidity = -1;
        return;
      }
      packet[i] = data;
    }

    // Verify checksum.
    if (packet[4] != (packet[0] + packet[1] + packet[2] + packet[3])& 0xFF) {
      temp = -1;
      humidity = -1;
      return;
    }

    humidity = packet[0];
    temp = packet[2]*1.8 + 32; // Convert to Farenheit.
    return;
  }


}

