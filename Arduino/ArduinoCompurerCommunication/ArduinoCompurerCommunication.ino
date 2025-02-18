//first part is to include all the liberaries  that we need for now we need LCD lib..
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//declaration of variables that we will to store communication data
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String commandString = "";

//declaration NAMES of pins (ports) that we will use for LEDs , alarm , and sensors ...
int led1Pin = 13;
int led2Pin = 12;
int led3Pin = 10;

boolean isConnected = false;

//connection string that has the pin adresse of the LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

setups ports (pins)
void setup() {
  
  Serial.begin(9600);
  pinMode(led1Pin,OUTPUT);
  pinMode(led2Pin,OUTPUT);
  pinMode(led3Pin,OUTPUT);
  initDisplay();
}


// la boucle princibale de Arduino contien les charctaire de connection qu'on recois depuis le logiciel windows, ce sont des condition sur les quelles l'qrduino demqre une serie d'action (ex: start the alarm take the scren shhot...)
  
void loop() {

if(stringComplete)
{
  //we check if we got any characters recieved from tha windows app 
  
  stringComplete = false;
  getCommand();
  
  if(commandString.equals("STAR"))
  {
    lcd.clear();
  }
  if(commandString.equals("STOP"))
  {
    turnLedOff(led1Pin);
    turnLedOff(led2Pin);
    turnLedOff(led3Pin);
    lcd.clear();
    lcd.print("Ready to connect");    
  }
  else if(commandString.equals("TEXT"))
  {
    String text = getTextToPrint();
    printText(text);
  }
  else if(commandString.equals("LED1"))
  {
    boolean LedState = getLedState();
    if(LedState == true)
    {
      turnLedOn(led1Pin);
    }else
    {
      turnLedOff(led1Pin);
    } 

      
  }
    else if(commandString.equals("LED2"))
  {
    boolean LedState = getLedState();
    if(LedState == true)
    {
      turnLedOn(led2Pin);
    }else
    {
      turnLedOff(led2Pin);
    }   
  }
    else if(commandString.equals("LED3"))
  {
    boolean LedState = getLedState();
    if(LedState == true)
    {
      turnLedOn(led3Pin);
    }else
    {
      turnLedOff(led3Pin);
    }   
  }
  
  inputString = "";
}

}

void initDisplay()
{
  lcd.begin(16, 2);
  lcd.print("Ready to connect");
}

boolean getLedState()
{
  boolean state = false;
  if(inputString.substring(5,7).equals("ON"))
  {
    state = true;
  }else
  {
    state = false;
  }
  return state;
}

void getCommand()
{
  if(inputString.length()>0)
  {
     commandString = inputString.substring(1,5);
  }
}

void turnLedOn(int pin)
{
  digitalWrite(pin,HIGH);
}

void turnLedOff(int pin)
{
  digitalWrite(pin,LOW);
}


String getTextToPrint()
{
  String value = inputString.substring(5,inputString.length()-2);
  return value;
}

void printText(String text)
{
  lcd.clear();
  lcd.setCursor(0,0);
    if(text.length()<16)
    {
      lcd.print(text);
    }else
    {
      lcd.print(text.substring(0,16));
      lcd.setCursor(0,1);
      lcd.print(text.substring(16,32));
    }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

