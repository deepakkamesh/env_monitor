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

#define TEMP_ONLY 0x1
#define HUMIDITY_ONLY 0x2
#define TEMP_HUMIDITY 0x3

#ifdef	__cplusplus
}
#endif

#endif	/* PUSHBUTTON_DEVICE_H */

