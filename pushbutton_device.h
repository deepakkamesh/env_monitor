/* 
 * File:   pushbutton_device.h
 * Author: dkg
 *
 * Created on May 14, 2017, 2:21 PM
 */

#ifndef PUSHBUTTON_DEVICE_H
#define	PUSHBUTTON_DEVICE_H

#ifdef	__cplusplus
extern "C" {
#endif

  void PushButtonTask(void);
  void DisplayTask(void);
  void DisplayError(int8_t errorCode);
  void WriteMemoryTask(void);
  void PushButtonInit(void);

  // Display Modes.
#define TEMP_ONLY 0x1
#define HUMIDITY_ONLY 0x2
#define TEMP_HUMIDITY 0x3
#define ALT_TEMP_HUMIDITY 0x4

  // Modes
#define NORMAL 0x1
#define SELECT_INTERVAL 0x2
#define VIEW_STORED 0x3

  // PusbButtons
#define BUTTON_A 0x1
#define BUTTON_B 0x2

#ifdef	__cplusplus
}
#endif

#endif	/* PUSHBUTTON_DEVICE_H */

