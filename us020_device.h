/* 
 * File:   us020_device.h
 * Author: dkg
 *
 * Created on June 2, 2017, 11:52 PM
 */

#ifndef US020_DEVICE_H
#define	US020_DEVICE_H

#ifdef	__cplusplus
extern "C" {
#endif

void ultrasonicTask(void);
uint16_t GetDistance(void);


#ifdef	__cplusplus
}
#endif

#endif	/* US020_DEVICE_H */

