#include <Key.h>
#include <Keypad.h>
#include <Servo.h>

#include <LiquidCrystal.h>
Servo myservo;  // create servo object to control a servo

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {6, 7, 18, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 13, 19, 9}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



//----------------------------------
//Constants
int detector1 = 0; // detector at Arduino analog pin A0
int detector2 = 1; // detector at arduni pin a1
int detector3 = 2;
int Servo1 = 3;
int pos = 0;

//Variables
char code[3];
int d1 = 550; 
int c1 = 0; 
int d0 = 0; // t-1 of c1 
int c0 = d1; // t-1 of d1 
int calculate = 0;
int coin = 0;

float balance;
float balance0;
char Key1;
char Key2;
int x;

float price1 = 1.50;
float price2 = .50;
float price3 = 1.00;
float price4 = 1.25;
bool LED1_1 = 0;
bool LED1_0 = 0;
bool LED2_1 = 0;
bool LED2_0 = 0;
//const int rs = 12, en = 13, d4 = 1, d5 = 0, d6 = 11, d7 = 10;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
  

unsigned long time = 0; 
unsigned long t0 = 0 ; 
unsigned long t1 = 0;
unsigned long t2 = 0;

float dt1 = 0;
float dt2 = 0;


float  speed1 ;
float  width;

void setup(){
// set up the LCD's number of columns and rows:
   lcd.begin(16, 2);
   pinMode(A3, OUTPUT);
  // Print a message to the LCD.
 Serial.begin(115200);
   myservo.attach(A3);  // attaches the servo on pin 3 to the servo object

  // lcd.print("Balance : $"); 
     lcd.print("Balance: $ 0.00"); 

}

void loop(){
analogWrite(Servo1, 80);
d1 = analogRead(A0);  //First LED
c1 = analogRead(A1);  // Second LED
//c0 = analogRead(A2);

//Serial.print("d1 =");
//Serial.print(d1);
//Serial.println("  ");

//****************************************************


//Check the first LED  status

if (d1 > 620)
{
   //analogWrite(A3, 250);
   LED1_1 = 1; 
}

if (d1 < 620)
{
  LED1_1 = 0;
}


//------------------------------------------------
// Check second LED  status

if (c1 > 620)  
{
LED2_1 = 1;
  //Serial.print(t1);
}

if (c1 < 620)
{
LED2_1 = 0;

}



if (LED1_1 == 1 && LED1_0 == 0)
{
  t0 = micros();
}

if (LED2_1 == 1 && LED2_0 == 0)
{
  t1 = micros();
}

if (LED2_0 == 1 && LED2_1 == 0)
{
 t2 = micros();

calculate = 1; // coin has passed through

}



LED1_0 = LED1_1; // record current state in LED1_0
LED2_0 = LED2_1; // record current state in LED2_0



//------------------------------------------------
// ***************************************************** MATH PORTION *****************************************************


if ((calculate==1))
{
dt1= (float) t1-t0; // time from LED1 to LED2 - leading edge of coin
dt2= (float) t2-t1; // time for coin to pass LED2


// average times
speed1 =  15/(dt1/1000); //15mm distance between LEDs distance/avgtime (mm/msec)

width =  (speed1 * dt2)/1000; // width = speed * time to pass LED2

//Serial.print("t0 = ");
//Serial.println(t0);
////Serial.println("\n");
//
//Serial.print("t1 = ");
//Serial.println(t1);
////Serial.println("\n");
//
//Serial.print("t2 = ");
//Serial.println(t2);
////Serial.println("\n");
//
//
//Serial.print("dt1 = ");
//Serial.println(dt1);
////Serial.print("\n");
//
//Serial.print("dt2 = ");
//Serial.println(dt2);
////Serial.print("\n");
//
//
//Serial.print("speed1 = ");
//Serial.println(speed1);
////Serial.println("\n");
//
//Serial.print("width = ");
//Serial.println(width);
////Serial.print("\n");
//Serial.println("************************************ ");
//Serial.print("\n");



}

if (width>= 18 && width<=20)
{ 
  coin = 1; // coin is a quarter
}

if (width>= 11.0 && width<=12.9)
{ 
  coin = 2; // coin is a dime
}


if (width>= 15.5 && width<=17.1)
{ 
  coin = 3; // coin is a nickel
}


if (width>= 12.89 && width<=14.8)
{ 
  coin = 4; // coin is a penny
}


if (calculate == 1)
  {
  switch (coin) 
  {
  case (1):
  balance = balance + .25;
  break;
  
  break;
  case (2):
  balance = balance + .10;
  break;
  
  case (3):
  balance = balance + .05;
  break;
  
  case (4):
  balance = balance + .01;
  break;
  }
}
coin = 0;



if (balance != balance0)  //if balance changes (not equal to previous amount)
{
  lcd.clear();
    lcd.setCursor(0,0);  

  lcd.print("Balance: $"); 
  lcd.setCursor(11,0);  
lcd.print(balance);
Serial.println(balance);
Serial.println(coin);

}

balance0 = balance;

//code = customKeypad.getKey();
//if (customKeypad.getState()==PRESSED);
//{
Key1 = customKeypad.getKey();
Serial.print(Key1);



//Serial.print("Key 1 =");
//Serial.println(Key1);
//
//while (Key2 == NO_KEY)
//{
//Key2 = customKeypad.getKey();
//Serial.print("Key 2 =");
//
//Serial.println(Key2);
//}
//}




if (Key1 != NO_KEY)
{
  lcd.clear();
      lcd.setCursor(0,0);  

  lcd.print("Balance: $"); 
  lcd.setCursor(11,0);  
lcd.print(balance);
  lcd.setCursor(0,1);
lcd.print(Key1);
  while (Key2 == NO_KEY)
    {
      Key2 = customKeypad.getKey();
      
      
    }
lcd.setCursor(1,1);
lcd.print(Key2);
    
}











calculate = 0;



if ((Key1 == 'A') and (Key2 == '1'))
{
  if (balance-price1>=-.1)
        {
         balance = balance - price1;
         if(balance<0)
            { 
              balance = 0;
            }
         Key1 = NO_KEY;
         Key2 = NO_KEY;
    for (pos = 0; pos <= 180; pos += 1) 
    
    {
   myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);        }
    // in steps of 1 degree
           }
    
        else 
        {
          lcd.clear();
          lcd.setCursor(0,0);  
          lcd.print("Insufficient");  
          lcd.setCursor(0,1);  
          lcd.print("Funds1"); 
          Key1 = NO_KEY;
          Key2 = NO_KEY;    
          }
}



if ((Key1 == 'A') and (Key2 == '2'))
{
//  Serial.println("*********************");
//  Serial.println(balance);
//  Serial.println(price2);
//  Serial.println(balance-price2);
//
//  Serial.print("Key 2 = ");
//  Serial.print(Key1);
//  Serial.println(Key2);


  if (balance-price2>=-.1)
        {
//          Serial.println(balance);
//          Serial.println(price2);
          balance = balance - price2;
          if(balance<0)
            { 
              balance = 0;
            }
          
          Key1 = NO_KEY;
          Key2 = NO_KEY;
//          Serial.print("working");
        // Dispense product 
        }
   else
      {
        Serial.println("Not working - 2");
        Serial.println(balance);
          Serial.println(price2);
          lcd.clear();
          lcd.setCursor(0,0);  
          lcd.print("Insufficient");  
          lcd.setCursor(0,1);  
          lcd.print("Funds");  
          Key1 = NO_KEY;
          Key2 = NO_KEY;
      }
}

if ((Key1 == 'B') and (Key2 == '1'))
{
  if (balance-price3 >= -.1)
   {
    balance = balance - price3;
    if(balance<0)
            { 
              balance = 0;
            }
    Key1 = NO_KEY;
     Key2 = NO_KEY;
    // Dispense product 
   }
   else 
   {
          lcd.clear();
          lcd.setCursor(0,0);  
          lcd.print("Insufficient");  
          lcd.setCursor(0,1);  
          lcd.print("Funds"); 
          Key1 = NO_KEY;
          Key2 = NO_KEY;
          }
}

if ((Key1 == 'B') and (Key2 == '2'))
{
if (balance-price4 >= -.1)
   {
    balance = balance - price4;
    if(balance<0)
            { 
              balance = 0;
            }
    Key1 = NO_KEY;
          Key2 = NO_KEY;
    // Dispense product 
   }
   else if (Key2 != NO_KEY) 
   {
          lcd.clear();
          lcd.setCursor(0,0);  
          lcd.print("Insufficient");  
          lcd.setCursor(0,1);  
          lcd.print("Funds"); 
          Key1 = NO_KEY;
          Key2 = NO_KEY;}}

//if ((Key1 == NO_KEY))
//{
//}
//
//if ((Key2 == NO_KEY))
//{
//}
else if (Key1 != NO_KEY or Key2 != NO_KEY)
{
  {
          lcd.clear();
          lcd.setCursor(0,0);  
          lcd.print("Invalid");  
          lcd.setCursor(0,1);  
          lcd.print("Selection"); 
          Key1 = NO_KEY;
          Key2 = NO_KEY;
          }
}  
}
