/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15.1
        Device            :  PIC18F26K22
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set DHT11 aliases
#define DHT11_TRIS               TRISAbits.TRISA0
#define DHT11_LAT                LATAbits.LATA0
#define DHT11_PORT               PORTAbits.RA0
#define DHT11_ANS                ANSELAbits.ANSA0
#define DHT11_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define DHT11_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define DHT11_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define DHT11_GetValue()           PORTAbits.RA0
#define DHT11_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define DHT11_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define DHT11_SetAnalogMode()  do { ANSELAbits.ANSA0 = 1; } while(0)
#define DHT11_SetDigitalMode() do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set US_TRIG aliases
#define US_TRIG_TRIS               TRISAbits.TRISA1
#define US_TRIG_LAT                LATAbits.LATA1
#define US_TRIG_PORT               PORTAbits.RA1
#define US_TRIG_ANS                ANSELAbits.ANSA1
#define US_TRIG_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define US_TRIG_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define US_TRIG_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define US_TRIG_GetValue()           PORTAbits.RA1
#define US_TRIG_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define US_TRIG_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define US_TRIG_SetAnalogMode()  do { ANSELAbits.ANSA1 = 1; } while(0)
#define US_TRIG_SetDigitalMode() do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set US_ECHO aliases
#define US_ECHO_TRIS               TRISAbits.TRISA2
#define US_ECHO_LAT                LATAbits.LATA2
#define US_ECHO_PORT               PORTAbits.RA2
#define US_ECHO_ANS                ANSELAbits.ANSA2
#define US_ECHO_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define US_ECHO_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define US_ECHO_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define US_ECHO_GetValue()           PORTAbits.RA2
#define US_ECHO_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define US_ECHO_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define US_ECHO_SetAnalogMode()  do { ANSELAbits.ANSA2 = 1; } while(0)
#define US_ECHO_SetDigitalMode() do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set IO_RA4 aliases
#define IO_RA4_TRIS               TRISAbits.TRISA4
#define IO_RA4_LAT                LATAbits.LATA4
#define IO_RA4_PORT               PORTAbits.RA4
#define IO_RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define IO_RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define IO_RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define IO_RA4_GetValue()           PORTAbits.RA4
#define IO_RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define IO_RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)

// get/set IO_RA5 aliases
#define IO_RA5_TRIS               TRISAbits.TRISA5
#define IO_RA5_LAT                LATAbits.LATA5
#define IO_RA5_PORT               PORTAbits.RA5
#define IO_RA5_ANS                ANSELAbits.ANSA5
#define IO_RA5_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define IO_RA5_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define IO_RA5_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define IO_RA5_GetValue()           PORTAbits.RA5
#define IO_RA5_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define IO_RA5_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define IO_RA5_SetAnalogMode()  do { ANSELAbits.ANSA5 = 1; } while(0)
#define IO_RA5_SetDigitalMode() do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set IO_RA6 aliases
#define IO_RA6_TRIS               TRISAbits.TRISA6
#define IO_RA6_LAT                LATAbits.LATA6
#define IO_RA6_PORT               PORTAbits.RA6
#define IO_RA6_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define IO_RA6_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define IO_RA6_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define IO_RA6_GetValue()           PORTAbits.RA6
#define IO_RA6_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define IO_RA6_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)

// get/set IO_RA7 aliases
#define IO_RA7_TRIS               TRISAbits.TRISA7
#define IO_RA7_LAT                LATAbits.LATA7
#define IO_RA7_PORT               PORTAbits.RA7
#define IO_RA7_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define IO_RA7_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define IO_RA7_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define IO_RA7_GetValue()           PORTAbits.RA7
#define IO_RA7_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define IO_RA7_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)

// get/set PB_A aliases
#define PB_A_TRIS               TRISBbits.TRISB0
#define PB_A_LAT                LATBbits.LATB0
#define PB_A_PORT               PORTBbits.RB0
#define PB_A_WPU                WPUBbits.WPUB0
#define PB_A_ANS                ANSELBbits.ANSB0
#define PB_A_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define PB_A_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define PB_A_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define PB_A_GetValue()           PORTBbits.RB0
#define PB_A_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define PB_A_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define PB_A_SetPullup()      do { WPUBbits.WPUB0 = 1; } while(0)
#define PB_A_ResetPullup()    do { WPUBbits.WPUB0 = 0; } while(0)
#define PB_A_SetAnalogMode()  do { ANSELBbits.ANSB0 = 1; } while(0)
#define PB_A_SetDigitalMode() do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set PB_B aliases
#define PB_B_TRIS               TRISBbits.TRISB1
#define PB_B_LAT                LATBbits.LATB1
#define PB_B_PORT               PORTBbits.RB1
#define PB_B_WPU                WPUBbits.WPUB1
#define PB_B_ANS                ANSELBbits.ANSB1
#define PB_B_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define PB_B_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define PB_B_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define PB_B_GetValue()           PORTBbits.RB1
#define PB_B_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define PB_B_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define PB_B_SetPullup()      do { WPUBbits.WPUB1 = 1; } while(0)
#define PB_B_ResetPullup()    do { WPUBbits.WPUB1 = 0; } while(0)
#define PB_B_SetAnalogMode()  do { ANSELBbits.ANSB1 = 1; } while(0)
#define PB_B_SetDigitalMode() do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set SEL aliases
#define SEL_TRIS               TRISBbits.TRISB2
#define SEL_LAT                LATBbits.LATB2
#define SEL_PORT               PORTBbits.RB2
#define SEL_WPU                WPUBbits.WPUB2
#define SEL_ANS                ANSELBbits.ANSB2
#define SEL_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define SEL_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define SEL_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define SEL_GetValue()           PORTBbits.RB2
#define SEL_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define SEL_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define SEL_SetPullup()      do { WPUBbits.WPUB2 = 1; } while(0)
#define SEL_ResetPullup()    do { WPUBbits.WPUB2 = 0; } while(0)
#define SEL_SetAnalogMode()  do { ANSELBbits.ANSB2 = 1; } while(0)
#define SEL_SetDigitalMode() do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set IO_RC0 aliases
#define IO_RC0_TRIS               TRISCbits.TRISC0
#define IO_RC0_LAT                LATCbits.LATC0
#define IO_RC0_PORT               PORTCbits.RC0
#define IO_RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define IO_RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define IO_RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define IO_RC0_GetValue()           PORTCbits.RC0
#define IO_RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define IO_RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set IO_RC1 aliases
#define IO_RC1_TRIS               TRISCbits.TRISC1
#define IO_RC1_LAT                LATCbits.LATC1
#define IO_RC1_PORT               PORTCbits.RC1
#define IO_RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define IO_RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define IO_RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define IO_RC1_GetValue()           PORTCbits.RC1
#define IO_RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define IO_RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set IO_RC2 aliases
#define IO_RC2_TRIS               TRISCbits.TRISC2
#define IO_RC2_LAT                LATCbits.LATC2
#define IO_RC2_PORT               PORTCbits.RC2
#define IO_RC2_ANS                ANSELCbits.ANSC2
#define IO_RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define IO_RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define IO_RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define IO_RC2_GetValue()           PORTCbits.RC2
#define IO_RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define IO_RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define IO_RC2_SetAnalogMode()  do { ANSELCbits.ANSC2 = 1; } while(0)
#define IO_RC2_SetDigitalMode() do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set IO_RC3 aliases
#define IO_RC3_TRIS               TRISCbits.TRISC3
#define IO_RC3_LAT                LATCbits.LATC3
#define IO_RC3_PORT               PORTCbits.RC3
#define IO_RC3_ANS                ANSELCbits.ANSC3
#define IO_RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_RC3_GetValue()           PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_RC3_SetAnalogMode()  do { ANSELCbits.ANSC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode() do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set IO_RC4 aliases
#define IO_RC4_TRIS               TRISCbits.TRISC4
#define IO_RC4_LAT                LATCbits.LATC4
#define IO_RC4_PORT               PORTCbits.RC4
#define IO_RC4_ANS                ANSELCbits.ANSC4
#define IO_RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define IO_RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define IO_RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define IO_RC4_GetValue()           PORTCbits.RC4
#define IO_RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define IO_RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define IO_RC4_SetAnalogMode()  do { ANSELCbits.ANSC4 = 1; } while(0)
#define IO_RC4_SetDigitalMode() do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set IO_RC5 aliases
#define IO_RC5_TRIS               TRISCbits.TRISC5
#define IO_RC5_LAT                LATCbits.LATC5
#define IO_RC5_PORT               PORTCbits.RC5
#define IO_RC5_ANS                ANSELCbits.ANSC5
#define IO_RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define IO_RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define IO_RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define IO_RC5_GetValue()           PORTCbits.RC5
#define IO_RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define IO_RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define IO_RC5_SetAnalogMode()  do { ANSELCbits.ANSC5 = 1; } while(0)
#define IO_RC5_SetDigitalMode() do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set IO_RC6 aliases
#define IO_RC6_TRIS               TRISCbits.TRISC6
#define IO_RC6_LAT                LATCbits.LATC6
#define IO_RC6_PORT               PORTCbits.RC6
#define IO_RC6_ANS                ANSELCbits.ANSC6
#define IO_RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define IO_RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define IO_RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define IO_RC6_GetValue()           PORTCbits.RC6
#define IO_RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define IO_RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define IO_RC6_SetAnalogMode()  do { ANSELCbits.ANSC6 = 1; } while(0)
#define IO_RC6_SetDigitalMode() do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set IO_RC7 aliases
#define IO_RC7_TRIS               TRISCbits.TRISC7
#define IO_RC7_LAT                LATCbits.LATC7
#define IO_RC7_PORT               PORTCbits.RC7
#define IO_RC7_ANS                ANSELCbits.ANSC7
#define IO_RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define IO_RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define IO_RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define IO_RC7_GetValue()           PORTCbits.RC7
#define IO_RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define IO_RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define IO_RC7_SetAnalogMode()  do { ANSELCbits.ANSC7 = 1; } while(0)
#define IO_RC7_SetDigitalMode() do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/