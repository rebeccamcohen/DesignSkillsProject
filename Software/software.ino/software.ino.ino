// preprocessor directives: define constants (including pins) in the code
#define FLASH_RATE_HZ 2
#define BUTTON_IN D1
#define PWN_LED_OUT D11
#define PWM_MAX 255

// global variables: represent the "state" across all functions
// operating mode: 0 = off, 1 = bright, 2 = mid-bright, 3 = dim, 4 = flashing light 
int operating_mode = 0;
bool BUTTON_PUSHED = false;
int previous_button_state = 0 
int PWM_OUT = 0

// setup loop: setup code executed one-time at device startup
void setup() {

  attachInterrupt(BUTTON_IN, button_pushed, FALLING);
  

}

// void loop: continuously running loop, calls functions taht are named as "actions"
void loop() {

  check_for_button_press();

  set_pwm_based_on_operating_mode();

  shine_led();

}

void check_for_button_press() {
    if (BUTTON_PUSHED == true) {
        operating_mode = operating_mode + 1;
        if (operating_mode == 5) {
            operating_mode = 0;
        }
     }
 }


void set_pwm_based_on_operating_mode(){

    switch (operating_mode) {
        case 0:
            PWM_OUT = 0;
        case 1:
            PWM_OUT = PWM_MAX;
        case 2:
            PWM_OUT = int(PWM_MAX/2);
        case 3:
            PWM_OUT = int(PWM_MAX/4);
        case 4:
            flash_the_light()
     }
  
  }
