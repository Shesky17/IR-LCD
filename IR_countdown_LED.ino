//commit

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include "IRremote.h"
//www.brilliantlyeasy.com/

int greenLED = 9;
int redLED = 10;
int receiver = 8;
IRrecv irrecv(receiver);
decode_results results;

int hours = 0; // start hours
int minutes = 0; //start min
int seconds = 20; //start seconds

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Pin Code
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //<--removed- Different LCD manufacture

void setup()
{
  pinMode(redLED, OUTPUT);
  irrecv.enableIRIn(); // start ir receive
}

void loop()
{
  greenLightOn();
  if (irrecv.decode(&results))
  {
    if (results.value == 0xE0E016E9 || results.value == 0x8AF13528)
    {
      lcd.begin(16, 2);
      lcd.print("Count Down Bomb");

      // lcd.scrollDisplayLeft();
      // wait a bit:
      delay(150);

      while (hours > 0 || minutes > 0 || seconds >= 0)
      {
        lcd.setCursor(4, 2);

        (hours < 10) ? lcd.print("0") : NULL;
        lcd.print(hours);
        lcd.print(":");
        (minutes < 10) ? lcd.print("0") : NULL;
        lcd.print(minutes);
        lcd.print(":");
        (seconds < 10) ? lcd.print("0") : NULL;
        lcd.print(seconds);
        lcd.display();
        stepDown();
        delay(900);//(1000);
      }
    }
    irrecv.resume();
  }

}

void stepDown()
{
  if (seconds > 0)
  {
    greenLightOn();
    delay(100);
    greenLightOff();
    seconds -= 1;
  }
  else
  {
    if (minutes > 0)
    {
      seconds = 59;
      minutes -= 1;
    }
    else
    {
      if (hours > 0)
      {
        seconds = 59;
        minutes = 59;
        hours -= 1;
      }
      else
      {
        redLight();
        trigger();
      }
    }
  }
}

void trigger()
{
  lcd.clear(); // clears the screen and buffer
  lcd.setCursor(5, 1); // set timer position on lcd for end.

  lcd.println("END");
  delay(1000);

  lcd.display();
}

void redLight()
{
  digitalWrite(redLED, HIGH);
}

void greenLightOn()
{
  digitalWrite(greenLED, HIGH);
}
void greenLightOff()
{
  digitalWrite(greenLED, LOW);
}


