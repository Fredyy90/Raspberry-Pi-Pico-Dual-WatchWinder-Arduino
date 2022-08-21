#if !defined(CONFIG_h)
#define CONFIG_h

#include <Arduino.h>

#define HAS_TURBO_BUTTONS 1      // add support for turbo buttons, connected to pins PIN_TURBO_BUTTON_W0 and PIN_TURBO_BUTTON_W1
//#define HAS_SOFT_POWER_SWITCH 1  // add support for "soft" power switch, connected to pin PIN_POWER_SWITCH and not directly to the power supply
//#define HAS_LED 1                // uncomment if you connect a LED to pin PIN_POWER_SWITCH_LED e.g. the LED in the power switch
//#define HAS_MODE_SWITCHES 1      // add support for mode switches, connected to pins PIN_MODE_SWITCH_W0 and PIN_MODE_SWITCH_W1
#define PERFORMANCE_OUTPUT 1     // add additional debug output about the loop performance every 25k runs

//#define DRIVER_ULN2003 1        // uncomment if you use a ULN2003 driver
#define DRIVER_TMC220x 1        // uncomment if you use a TMC220x driver

#if defined(DRIVER_ULN2003) && defined(DRIVER_TMC220x)
    #error "You can only use one driver!"
#endif

#if defined(DRIVER_ULN2003)
    // define pins used for first winder
    const int PIN_W0_A1 = 2;
    const int PIN_W0_A2 = 3;
    const int PIN_W0_B1 = 4;
    const int PIN_W0_B2 = 5;

    // define pins used for second winder
    const int PIN_W1_A1 = 6; 
    const int PIN_W1_A2 = 7;
    const int PIN_W1_B1 = 8;
    const int PIN_W1_B2 = 9;
#endif

#if defined(DRIVER_TMC220x)
    // define pins used for first winder
    const int PIN_W0_STP = 2;
    const int PIN_W0_DIR = 5;

    // define pins used for second winder
    const int PIN_W1_STP = 3; 
    const int PIN_W1_DIR = 6;
#endif

// define pins used for the turbo buttons if HAS_TURBO_BUTTONS is defined
#if defined(HAS_TURBO_BUTTONS)
    const int PIN_TURBO_BUTTON_W0 = 10;
    const int PIN_TURBO_BUTTON_W1 = 11;
#endif

// define pins used for the mode switch
#if defined(HAS_MODE_SWITCH)
    const int PIN_MODE_SWITCH_W0  = 12;
    const int PIN_MODE_SWITCH_W1  = 13;
#endif

#if defined(HAS_LED)
    const int PIN_POWER_SWITCH_LED = 14;
#endif

#if defined(HAS_SOFT_POWER_SWITCH)
    //define pins used for the power switch
    const int PIN_POWER_SWITCH     = 15;
#endif

/** 
 *  3600 / TIME_INTERVAL * 24 *  ROTATIONS_PER_INTERVAL = rotations per day
 * 
 *  TIME_INTERVAL | ROTATIONS_PER_INTERVAL | rotations per day
 *  1  * 60       |  1                     | 1140
 *  10 * 60       | 10                     | 1140
 *  2  * 60       |  1                     |  720
 *  20 * 60       | 10                     |  720
 *  5  * 60       |  3                     |  864
 *  5  * 60       |  2                     |  576
 * 
 */

const int ROTATIONS_PER_INTERVAL = 1;               // add 3 rotations every interval
const int TIME_INTERVAL          = 15;            // interval to add rotations in seconds, default value : 5*60 = 5 minutes
const int TURBO_BUTTON_ROTATIONS = 200;             // add 200 rotations everytime turbobutton is pressed


#if defined(DRIVER_ULN2003)
    const uint32_t STEPPER_STEPS_PER_ROTATION = 2038;  // steps needed for 1 rotation (https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/)
    const uint32_t STEPPER_MAX_STEPS_PER_SEC  = 600;   // max speed in steps per second
    const uint32_t STEPPER_ACCELERATION       = 2048;  // in steps*second²
#endif

#if defined(DRIVER_TMC220x)
    const uint32_t STEPPER_STEPS_PER_ROTATION = 3200;  // steps needed for 1 rotation | 360°/0,9° per step = 400 steps * microsteps = 400*8 = 3200 steps per rotation
    const uint32_t STEPPER_MAX_STEPS_PER_SEC  = STEPPER_STEPS_PER_ROTATION/3*2;   // max speed in steps per second
    const uint32_t STEPPER_ACCELERATION       = 2048;  // in steps*second²
#endif


#if !defined(HAS_LED) && defined(LED_BUILTIN)
    #define HAS_LED 1
    const int PIN_POWER_SWITCH_LED = LED_BUILTIN;
#endif

#endif // CONFIG_h