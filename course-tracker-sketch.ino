#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Library for LCD
using namespace std;


LiquidCrystal_I2C lcd(0x27,16,2);  // 16 chars and 2 line display


int CENTRE_OF_DISPLAY = 8;

int CATAGORY_SIZE = 5;
const char CATAGORIES[5] = {'ENEL200', 'ENEL220', 'ENEL270', 'ENEL280', 'EMTH210'};
int cat_times[5] = {0, 0, 0, 0, 0}; // time in seconds

unsigned long timer = 1559990; // timer for seconds

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
  
  // Serial.print("Number ");
  // Serial.print(num);
  // Serial.print(" Length ");
  // Serial.print(String(num).length());
  // Serial.print(" Req ");
  // Serial.print(required_char_amnt);
  // Serial.print(" diff ");
  // Serial.println(required_char_amnt - String(num).length());

  return zeros + String(num);
   
}

String getTimerDisplayFormat(long timer) {
  // takes timer value in seconds and outputs time in hours:minutes

  int hours = timer / 3600;
  int minutes = (timer % 3600) / 60;
  int seconds = (timer % 3600) % 60;

  Serial.print(hours);
  Serial.print(" ");
  Serial.print(minutes);
  Serial.print(" ");
  Serial.println(seconds);

  return getFixedNumberLength(hours, 2) + ":" + getFixedNumberLength(minutes, 2) + ":" + getFixedNumberLength(seconds, 2);
  
}

void setup() {

  lcd.init();
  lcd.backlight();


  // TESTING

  Serial.begin(9600);
  Serial.println("Starting up");


}

void loop() {

  String timer_format = getTimerDisplayFormat(timer);

  lcd.clear();

  lcd.setCursor(getDisplaySpacing("ENEL220"),0);
  lcd.print("ENEL220");

  lcd.setCursor(getDisplaySpacing(timer_format), 1);
  lcd.print(timer_format);

  delay(1000); // loop every second
  timer += 1;

}
