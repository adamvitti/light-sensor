/**
 * @file
 * app.c
 * @author
 * Adam Vitti
 * @date
 * 10/16/21
 * @brief
 * This module calls all of our drivers and provides the logic we want for how our application operates.
 *
 */

//***********************************************************************************
// Include files
//***********************************************************************************
#include "app.h"



//***********************************************************************************
// defined files
//***********************************************************************************


//***********************************************************************************
// Private variables
//***********************************************************************************
static int RGB_COLOR;


//***********************************************************************************
// Private functions
//***********************************************************************************

static void app_letimer_pwm_open(float period, float act_period, uint32_t out0_route, uint32_t out1_route, uint32_t comp0_cb, uint32_t comp1_cb, uint32_t underflow_cb);

//***********************************************************************************
// Global functions
//***********************************************************************************

/***************************************************************************//**
 * @brief
 * This function initializes/opens all of our peripherals.
 *
 * @details
 * This function calls our drivers for the CMU, GPIO and letimer, in order to initialize each peripheral.
 * Additionally, this function will initialize our event scheduler and sleep driver.
 * It sets up LETIMER0 with a specified PWM, then starts the timer.
 *
 * @note
 * This function will be called in main.c in order to set everything up for operation before we start operation.
 *
 ******************************************************************************/

void app_peripheral_setup(void){
  cmu_open();
  sleep_open();
  gpio_open();
  Si1133_i2c_open();
  scheduler_open();
  rgb_led_open();
  app_letimer_pwm_open(PWM_PER, PWM_ACT_PER, PWM_ROUTE_0, PWM_ROUTE_1, LETIMER0_COMP0_CB, LETIMER0_COMP1_CB, LETIMER0_UF_CB);
  letimer_start(LETIMER0, true);  //This command will initiate the start of the LETIMER0

}

/***************************************************************************//**
 * @brief
 * Sets up LETIMER0 for specified PWM and interrupt operation.
 *
 * @details
 * This function uses aspects of the app_letimer_pwm_struct in order to specify specific
 * operations, like PWM period for the LETIMER0, as well as, interrupt functionallity that will only be used in this specific application.
 *
 * @note
 * This function is called once in app_peripheral_setup() in order to setup LETIMER0 in the operation mode
 * specific to this application.
 *
 * @param[in] period
 * Desired total period for PWM operation in seconds
 *
 * @param[in] act_period
 * Desired active period for PWM operation in seconds (how long signal should be on)
 *
 * @param[in] out0_route
 * Location 0 for the generated PWM to be routed to (ex. location 16 or 17 for LEDs)
 *
 * @param[in] out1_route
 * Location 1 for the generated PWM to be routed to (ex. location 16 or 17 for LEDs)
 *
 * @param[in] comp0_cb
 * Used to set the event scheduler when comp0 triggers a callback
 *
 * @param[in] comp1_cb
 * Used to set the event scheduler when comp1 triggers a callback
 *
 * @param[in] underflow_cb
 * Used to set the event scheduler when underflow triggers a callback
 ******************************************************************************/

void app_letimer_pwm_open(float period, float act_period, uint32_t out0_route, uint32_t out1_route, uint32_t comp0_cb, uint32_t comp1_cb, uint32_t underflow_cb){
  // Initializing LETIMER0 for PWM operation by creating the
  // letimer_pwm_struct and initializing all of its elements
  // APP_LETIMER_PWM_TypeDef is defined in letimer.h
  APP_LETIMER_PWM_TypeDef   app_letimer_pwm_struct;

  app_letimer_pwm_struct.active_period = act_period;
  app_letimer_pwm_struct.debugRun = false;
  app_letimer_pwm_struct.enable = false;
  app_letimer_pwm_struct.out_pin_0_en = false;
  app_letimer_pwm_struct.out_pin_1_en = false;
  app_letimer_pwm_struct.out_pin_route0 = out0_route;
  app_letimer_pwm_struct.out_pin_route1 = out1_route;
  app_letimer_pwm_struct.period = period;
  app_letimer_pwm_struct.comp0_cb = comp0_cb;
  app_letimer_pwm_struct.comp0_irq_enable = false;
  app_letimer_pwm_struct.comp1_cb = comp1_cb;
  app_letimer_pwm_struct.comp1_irq_enable = true;
  app_letimer_pwm_struct.uf_cb = underflow_cb;
  app_letimer_pwm_struct.uf_irq_enable = true;




  letimer_pwm_open(LETIMER0, &app_letimer_pwm_struct);
}


/***************************************************************************//**
 * @brief
 *  Initializes LED color and LEDs
 *
 *
 * @details
 * Sets our initial LED color to 0 and configures all LEDs.
 *
 *
 *
 *
 * @note
 * This should be called during peripheral setup
 *
 *
 *
 ******************************************************************************/
void rgb_led_open(void){
  RGB_COLOR = 0;
  rgb_init();
}

/***************************************************************************//**
 * @brief
 * Call back function that is called when LETIMER0 underflow triggers an interrupt
 *
 * @details
 * This function handles any operation that needs to be completed when LETIMER0 underflow event occurs.
 *
 * @note
 * This function calls for white light ADC data that has been collected
 *
 ******************************************************************************/
void scheduled_letimer0_uf_cb (void){
  //EFM_ASSERT(!(get_scheduled_events() & LETIMER0_UF_CB));
//  if(RGB_COLOR == 0){
//      leds_enabled(RGB_LED_1, COLOR_RED, false);
//      RGB_COLOR++;
//  }
//  else if(RGB_COLOR == 1){
//      leds_enabled(RGB_LED_1, COLOR_GREEN, false);
//      RGB_COLOR++;
//  }
//  else if(RGB_COLOR == 2){
//      leds_enabled(RGB_LED_1, COLOR_BLUE, false);
//      RGB_COLOR = 0;
//  }

  si1133_read_white_light(SI1133_LIGHT_CB);


}

/***************************************************************************//**
 * @brief
 * Call back function that is called when LETIMER0 comp0 triggers an interrupt
 *
 * @details
 * This function handles any operation that needs to be completed when LETIMER0 comp0 event occurs.
 *
 * @note
 * This function is called by the event scheduler after being set by an interrupt
 *
 ******************************************************************************/
void scheduled_letimer0_comp0_cb (void){
  //EFM_ASSERT(false); NOT USED IN THIS LAB
}

/***************************************************************************//**
 * @brief
 * Call back function that is called when LETIMER0 comp1 triggers an interrupt
 *
 * @details
 * This function handles any operation that needs to be completed when LETIMER0 comp1 event occurs.
 *
 * @note
 * This function initiates an i2c read cycle of the si1133 peripheral
 *
 ******************************************************************************/
void scheduled_letimer0_comp1_cb (void){
  //EFM_ASSERT(!(get_scheduled_events() & LETIMER0_COMP1_CB));
//  if(RGB_COLOR == 0){
//      leds_enabled(RGB_LED_1, COLOR_RED,true);
//  }
//
//  if(RGB_COLOR == 1){
//      leds_enabled(RGB_LED_1, COLOR_GREEN,true);
//  }
//
//  if(RGB_COLOR == 2){
//      leds_enabled(RGB_LED_1, COLOR_BLUE,true);
//  }

  si1133_force_cmd(); //send force command

}

/***************************************************************************//**
 * @brief
 * Call back function that is called once white light read operation is completed for si1133
 *
 * @details
 * This function handles operation that should occur after a successful i2c white light read operation of the si1133.
 *
 * @note
 * This function retrieves the value read from the si1133 peripheral and turns on BLUE LED if read value is less than expected value or
 * turns off if value is greater than or equal to expected value.
 *
 ******************************************************************************/
void scheduled_si1133_read_cb(){
  uint32_t si1133_data = si1133_read_result();

  if(si1133_data < EXPECTED_READ_DATA){
      leds_enabled(RGB_LED_1, COLOR_BLUE, true);
  }else{
      leds_enabled(RGB_LED_1, COLOR_BLUE, false);
  }

}



