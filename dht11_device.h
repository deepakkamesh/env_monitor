/* 
 * File:   dht11_device.h
 * Author: dkg
 *
 * Created on April 29, 2017, 11:18 PM
 */

#ifndef DHT11_DEVICE_H
#define	DHT11_DEVICE_H

#ifdef	__cplusplus
extern "C" {
#endif

  void DHT11Task(void);
  void myTMR2ISR(void);
  void DHT11Init(void);
  int8_t GetTemp(void);
  int8_t GetHumidity(void);
  int8_t GetError(void);

#define  ERR_DHT11_CHECKSUM_FAILURE -1 
#define ERR_DHT11_TIMEOUT_RESPONSE -2 
#define ERR_DHT11_TIMEOUT_DATA -3 


#ifdef	__cplusplus
}
#endif

#endif	/* DHT11_DEVICE_H */

