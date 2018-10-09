#include <Keypad.h>
int ldr =0;
int alarm =13;
int pb =9;
int led =10;

const byte rows = 4;
const byte cols = 3;


char hexakeys [rows] [cols]=
{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'} 
};

byte rowpins [rows] = {5, 4, 3, 2};
byte colpins [cols] = {6, 7, 8};

Keypad costomKeypad = Keypad (makeKeymap (hexakeys), rowpins, colpins, rows, cols);

char PIN[3] = {'2', '3', '4'};
char attempt[3] = {'0', '0', '0'};
int z=0;

void setup ()
{
  Serial.begin (9600);
   pinMode (alarm,OUTPUT);
  pinMode (pb,INPUT);
  pinMode (led, OUTPUT);
}

void correctPIN ()
{
  Serial.println ("pass");
  digitalWrite (alarm,LOW);
}
void incorrectPIN ()
{
  Serial.println ("Try again");
   digitalWrite (alarm,HIGH);
   delay (1000);
}

void checkPIN ()
{
  int correct=0;
  for (int i=0; i<3; i++)
  {
    if (attempt[i]==PIN[i])
    {
      correct++;
    }
  }
  if (correct==3)
  {
    correctPIN();
  }
  else 
  {
    incorrectPIN();
  }
  for (int a=0; a<3; a++)
  {
    attempt [a]= '0';
  }
}

void readKeypad ()
{
  char key = costomKeypad.getKey();
  if (key != NO_KEY)
  {
    attempt [z] = key;
    z++;
    switch (key)
    {
      case '*':
        z=0;
      break;
      case '#':
        z=0;
        delay(100);
        checkPIN ();
      break;
    }
  }
}

void loop ()
{
  readKeypad ();
   int x;
    x = analogRead (ldr);
    delay (10);
    Serial.println (x);
    if (analogRead (x)<=500)
    {
      digitalWrite (alarm,HIGH);
      delay (100000);
    }
    else 
    {
      digitalWrite (alarm,LOW);
    }
    if (digitalRead (pb)== HIGH)
    {
      digitalWrite (alarm,LOW);
      delay (100);
    }
    
} 
