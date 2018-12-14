// preprocessor directives: define constants (including pins) in the code
#define FLASH_RATE_HZ 2 //delay time = 1/(2 Hz) = 0.5 s = 500 ms 
#define BUTTON_IN 3
#define PWM_LED_OUT 11
#define PWM_MAX 255

// global variables: represent the "state" across all functions
// operating mode: 0 = off, 1 = bright, 2 = mid-bright, 3 = dim, 4 = flashing light 
int operating_mode = 0;
bool BUTTON_PUSHED = false;
int previous_button_state = 0; 
int PWM_OUT = 0;
int delay_time = 1000 / FLASH_RATE_HZ;

// setup loop: setup code executed one-time at device startup
void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_IN), button_pushed, RISING); //FALLING 
  
}

// void loop: continuously running loop, calls functions taht are named as "actions"
void loop() {

  check_for_button_press();

  set_pwm_based_on_operating_mode();

  shine_led();

}

void button_pushed() {
    BUTTON_PUSHED = true;
}

void check_for_button_press() {
  
    if ((BUTTON_PUSHED) && (previous_button_state !=4)) {
      operating_mode =operating_mode + 1;
      BUTTON_PUSHED = false;
    }
    else if ((BUTTON_PUSHED) && (previous_button_state ==4)) {
      operating_mode = 0;
      BUTTON_PUSHED = false;
    }
    previous_button_state = operating_mode;
    Serial.print(previous_button_state);
}


void set_pwm_based_on_operating_mode(){

    switch (operating_mode) {
        case 0:
            PWM_OUT = 0;
            break;
        case 1:
            PWM_OUT = PWM_MAX;
            break;
        case 2:
            PWM_OUT = int(PWM_MAX/2);
            break;
        case 3:
            PWM_OUT = int(PWM_MAX/4);
            break;
        case 4:
           flash_the_light();
    }
  
}

void shine_led() {
    analogWrite(PWM_LED_OUT, PWM_OUT);
}


void flash_the_light() {
    digitalWrite(PWM_LED_OUT, PWM_MAX);
    delay(delay_time);
    digitalWrite(PWM_LED_OUT, 0);
    delay(delay_time); 
}
