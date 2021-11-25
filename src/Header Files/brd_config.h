#ifndef BRD_CONFIG_HG
#define BRD_CONFIG_HG

//***********************************************************************************
// Include files
//***********************************************************************************
#include "em_gpio.h"
#include "em_cmu.h"

//***********************************************************************************
// defined files
//***********************************************************************************

// LED 0 pin is
#define LED_RED_PORT       gpioPortD
#define LED_RED_PIN        8
#define LED_RED_DEFAULT    false   // Default false (0) = off, true (1) = on
#define LED_RED_GPIOMODE   gpioModePushPull

// LED 1 pin is
#define LED_GREEN_PORT       gpioPortD
#define LED_GREEN_PIN        9
#define LED_GREEN_DEFAULT    false // Default false (0) = off, true (1) = on
#define LED_GREEN_GPIOMODE   gpioModePushPull

#define MCU_HFXO_FREQ			cmuHFRCOFreq_26M0Hz

// GPIO pin setup
//#define STRONG_DRIVE

#ifdef STRONG_DRIVE
	#define LED_RED_DRIVE_STRENGTH		gpioDriveStrengthStrongAlternateStrong
	#define LED_GREEN_DRIVE_STRENGTH	gpioDriveStrengthStrongAlternateStrong
#else
	#define LED_RED_DRIVE_STRENGTH		gpioDriveStrengthWeakAlternateWeak
	#define LED_GREEN_DRIVE_STRENGTH	gpioDriveStrengthWeakAlternateWeak
#endif

// LETIMER PWM Configuration

#define   PWM_ROUTE_0     LETIMER_ROUTELOC0_OUT0LOC_LOC17
#define   PWM_ROUTE_1     LETIMER_ROUTELOC0_OUT1LOC_LOC16


// RGB LED locations
#define RGB_ENABLE_PORT gpioPortJ
#define RGB_ENABLE_PIN 14
#define RGB0_PORT gpioPortI
#define RGB0_PIN 0
#define RGB1_PORT gpioPortI
#define RGB1_PIN 1
#define RGB2_PORT gpioPortI
#define RGB2_PIN 2
#define RGB3_PORT gpioPortI
#define RGB3_PIN 3
#define RGB_RED_PORT gpioPortD
#define RGB_RED_PIN 11
#define RGB_GREEN_PORT gpioPortD
#define RGB_GREEN_PIN 12
#define RGB_BLUE_PORT gpioPortD
#define RGB_BLUE_PIN 13
#define RGB_DEFAULT_OFF false
#define COLOR_DEFAULT_OFF false
#define RED_RGB_LOC TIMER_ROUTELOC0_CC0LOC_LOC19
#define GREEN_RGB_LOC TIMER_ROUTELOC0_CC1LOC_LOC19
#define BLUE_RGB_LOC TIMER_ROUTELOC0_CC2LOC_LOC19

// Si1133 Locations
#define SI1133_SCL_PORT gpioPortC
#define SI1133_SCL_PIN 5
#define SI1133_SCL_DEFAULT true
#define SI1133_SDA_PORT gpioPortC
#define SI1133_SDA_PIN 4
#define SI1133_SDA_DEFAULT true
#define SI1133_SENSOR_EN_PORT gpioPortF
#define SI1133_SENSOR_EN_PIN 9
#define SI1133_DRIVE_STRENGTH gpioDriveStrengthWeakAlternateWeak
#define SI1133_SENSOR_EN_DEFAULT true

// I2C Route Location
#define I2C_SCL_PC5   I2C_ROUTELOC0_SCLLOC_LOC17
#define I2C_SDA_PC4   I2C_ROUTELOC0_SDALOC_LOC17

//***********************************************************************************
// function prototypes
//***********************************************************************************

#endif
