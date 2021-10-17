#include <Wire.h>
#include <Keypad.h>
#include <Keypad_I2C.h>
#include <LiquidCrystal_I2C.h>

#define LCD_I2CADDR 0x20       // Connect via i2c, default address 0x20
                               // Set A0, A1, A2 to ground of 1st PCF8574
#define Keypad_I2CADDR 0x21    // connect pin A0 of 2nd PCF8574 to 5V for address 0x21
                               // A1, A2 to ground 
const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

//define the keymap
char keys [ROWS] [COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'X', '0', '=', '+'}
};

byte rowPins[ROWS] = {3, 2, 1, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

LiquidCrystal_I2C lcd(LCD_I2CADDR,20,4);  // using 20 x 4 LCD display
Keypad_I2C kpd( makeKeymap(keys), rowPins, colPins, ROWS, COLS, Keypad_I2CADDR );

//variables declaration
boolean valOnePresent = false;
boolean next = false;
boolean final = false;
String num1, num2;
int ans;
char op;


void setup(){
  lcd.init(); // initialize the lcd
  Wire.begin();
  kpd.begin( makeKeymap(keys) );
  lcd.setCursor(2,0);
  lcd.print("Hello World!");
  delay(2500); // 2.5 seconds warm-up time
  lcd.clear(); // clears the LCD screen and positions the cursor in the upper-left corner. 

 
}

void loop(){
  char key = kpd.getKey();

if (key != NO_KEY && (key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0')){
    if (valOnePresent != true){
      num1 = num1 + key;
      int numLength = num1.length();
      lcd.setCursor(19 - numLength, 0); //to adjust one whitespace for operator
      lcd.print(num1);
    }
    else {
      num2 = num2 + key;
      int numLength = num2.length();
      lcd.setCursor(19 - numLength, 1);
      lcd.print(num2);
      final = true;
    }
  }

  else if (valOnePresent == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+')){
    if (valOnePresent == false){
      valOnePresent = true;
      op = key;
      lcd.setCursor(19,0); //operator on right corner
      lcd.print(op);
    }
  }

  else if (final == true && key != NO_KEY && key == '='){
    if (op == '+'){
      ans = num1.toInt() + num2.toInt();
      //lcd.clear();
      lcd.setCursor(15,3);
      lcd.autoscroll();
      lcd.print(ans);
      lcd.noAutoscroll();
    }
    else if (op == '-'){
      ans = num1.toInt() - num2.toInt();
      //lcd.clear();
      lcd.setCursor(15,3);
      lcd.autoscroll();
      lcd.print(ans);
      lcd.noAutoscroll();
    }
    else if (op == '*'){
      ans = num1.toInt() * num2.toInt();
      //lcd.clear();
      lcd.setCursor(15,3);
      lcd.autoscroll();
      lcd.print(ans);
      lcd.noAutoscroll();
    }
    else if (op == '/'){
      ans = num1.toInt() / num2.toInt();
      //lcd.clear();
      lcd.setCursor(15,3);
      lcd.autoscroll();
      lcd.print(ans);
      lcd.noAutoscroll();
    }    
  }
  else if (key != NO_KEY && key == 'X'){
    lcd.clear();
    valOnePresent = false;
    final = false;
    num1 = "";
    num2 = "";
    ans = 0;
    op = ' ';
  }
}
