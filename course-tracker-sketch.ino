#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Library for LCD
using namespace std;

#define BUTTON_PIN 2

LiquidCrystal_I2C lcd(0x27,16,2);  // 16 chars and 2 line display


int CENTRE_OF_DISPLAY = 8;

int CATAGORY_SIZE = 5;
const String CATAGORIES[] = {"ENEL200", "ENEL220", "ENEL270", "ENEL280", "EMTH210"};
int selected_cat_i = 0;

int cat_times[5] = {0, 0, 0, 0, 0}; // time in seconds

// button variable
int prev_but_output;

// timer variables
unsigned long timer = 0; // timer for seconds
unsigned long start_time;

bool is_timer_running = false;

int getDisplaySpacing(String text) {
  // returns the amount of indentation required to centre the text

  return CENTRE_OF_DISPLAY - text.length() / 2;

}

String getFixedNumberLength(int num, int required_char_amnt) {
  // returns the same number with zeros in front to reach the required amount of characters

  if (String(num).length() >= required_char_amnt) { // error prevention with unsigned numbers
    return String(num);

  }

  String zeros = "";
  for (int i = 0; i < required_char_amnt - String(num).length(); i++) {
    zeros += "0";

  }

  return zeros + String(num);
   
}

String getTimerDisplayFormat(long timer) { // takes timer value in seconds and outputs time in hours:minutes

  int hours = timer / 3600;
  int minutes = (timer % 3600) / 60;
  int seconds = (timer % 3600) % 60;

  // Serial.print(hours);
  // Serial.print(" ");
  // Serial.print(minutes);
  // Serial.print(" ");
  // Serial.println(seconds);

  return getFixedNumberLength(hours, 2) + ":" + getFixedNumberLength(minutes, 2) + ":" + getFixedNumberLength(seconds, 2);
  
}


void setup() {

  pinMode(BUTTON_PIN, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  // TESTING

  Serial.begin(9600);
  Serial.println("Starting up");

}

void loop() {
  
  if (millis() > (timer + 1) * 1000) { // happens every second
    timer = (millis() - start_time) / 1000 * is_timer_running; // only have the timer working when is_timer_running is TRUE
    
  }

  // gets the time from the timer variable and makes it into a nice display format
  String timer_format = getTimerDisplayFormat(timer);

  // centers the catagory on the display
  lcd.setCursor(getDisplaySpacing(CATAGORIES[selected_cat_i]),0);
  lcd.print(CATAGORIES[selected_cat_i]);

  // centers the time on the display
  lcd.setCursor(getDisplaySpacing(timer_format), 1);
  lcd.print(timer_format);

  // determines if button is pressed or not
  if (digitalRead(BUTTON_PIN) == HIGH) {
    prev_but_output = digitalRead(BUTTON_PIN);
  }
  // determines whether to start or stop the timer
  else if (prev_but_output == HIGH && !is_timer_running) { // if the button was pressed and timer is NOT running
    start_time = millis();
    is_timer_running = true;
    prev_but_output = LOW;

  }
  else if (prev_but_output == HIGH) { // if the timer IS running and the button was pressed
    is_timer_running = false;
    prev_but_output = LOW;

  }

}
