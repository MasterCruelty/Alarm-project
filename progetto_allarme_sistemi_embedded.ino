
/*
  The circuit:
 * LCD RS pin to digital pin 41
 * LCD Enable pin to digital pin 39
 * LCD D4 pin to digital pin 37
 * LCD D5 pin to digital pin 35
 * LCD D6 pin to digital pin 33
 * LCD D7 pin to digital pin 31
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/
// include the library code:
#include <LiquidCrystal.h>
#include <SR04.h>
#include <pitches.h>
#include <Keypad.h>
// inizializzazione display lcd 
LiquidCrystal lcd(41,39,37,35,33,31);
//definizione pin per sensore di prossimità
#define echo_pin 53
#define trig_pin 51

//******
#define echo_pin2 52
#define trig_pin2 50
#define echo_pin3 48
#define trig_pin3 46
//******

//definizione pin per i 3 led
#define GREEN 42
#define RED 44
#define YELLOW 40
//istanza sensori di prossimità
SR04 sensore  = SR04(echo_pin,trig_pin);

//******
SR04 sensore2 = SR04(echo_pin2,trig_pin2);
SR04 sensore3 = SR04(echo_pin3,trig_pin3);
//******

//definizione variabili per la misurazione delle distanze e la durata del suono del buzzer
long distanza;

//******
long distanza2;
long distanza3;
//******

int durata_suono = 100;


//definizione keypad, impostazioni righe/colonne
const byte rows = 4; 
const byte cols = 4; 

char Keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte colPins[cols] = {6,7,8,9};
byte rowPins[rows] = {2,3,4,5}; 
//inizializzazione del keypad
Keypad key = Keypad(makeKeymap(Keys), rowPins, colPins, rows, cols); 
String s = "";
int cursorCurrentPosition = 0;

void setup() {
  Serial.begin(9600);
  // set up schermo LCD con numero di righe e colonne
  lcd.begin(16, 2);
  // prima stampa su schermo LCD una volta acceso il sistema.
  lcd.print("Sistema");
  lcd.setCursor(0,1);
  lcd.print("inizializzato");
  digitalWrite(GREEN,HIGH);
  digitalWrite(RED,HIGH);
  digitalWrite(YELLOW,HIGH);
  delay(2000);
  digitalWrite(GREEN,LOW);
  digitalWrite(RED,LOW);
  digitalWrite(YELLOW,LOW);
  lcd.clear();
}

void loop() {
  //assegnamento variabili che contengono la misurazione dei 3 sensori
  distanza  = sensore.Distance();

  //******
  distanza2 = sensore2.Distance();
  distanza3 = sensore3.Distance();
  //******
  
  digitalWrite(RED,LOW);
  digitalWrite(GREEN,LOW);
  digitalWrite(YELLOW,LOW);
  if(distanza <= 20){
    lcd.print("Area violata");
    lcd.setCursor(0,1);
    lcd.print(distanza);
    lcd.print("cm");
    digitalWrite(RED,HIGH);
    delay(1000);
    lcd.clear();
    lcd.print("codice sblocco:");
    lcd.setCursor(0,1);  
    while(true){
      tone(49, NOTE_C3, durata_suono);
      char input = key.getKey();
      cursorCurrentPosition += 1;
      if(input == 'C'){
         /*String new_s = "";
         for(int i = 0;i < s.length()-1;i++){
          new_s = s.charAt(i);
         }
         s = new_s;*/
         s="";
         lcd.clear();
         lcd.print(s);
        }
      else{
        s.concat(String(input));
      }
      if(input && !(input == 'C')){
        lcd.print(input);
        delay(500);
        if (s.startsWith("117") && s.endsWith("*")){
          lcd.clear();
          lcd.print("codice corretto");
          s = "";
          delay(1000);
          lcd.clear();
          break;
        }else if(s.endsWith("*")){
          lcd.clear();
          lcd.print("codice errato");
          s = "";
          delay(1000);
          lcd.clear();
          continue;
        }
      }
    }
  }
  else if(distanza > 400){
    lcd.print("Fuori range");
    lcd.setCursor(0,1);
    lcd.print("Distanza > 400cm");
    digitalWrite(GREEN,HIGH);
    digitalWrite(RED,HIGH);
    digitalWrite(YELLOW,HIGH);
  }
  else{
    lcd.print("Area sicura");
    lcd.setCursor(0,1);
    lcd.print(distanza);
    lcd.print("cm");
    if(distanza >=30){
      digitalWrite(GREEN,HIGH);
    }
    else{
      digitalWrite(YELLOW,HIGH);
    }
  }
  delay(1000);
  lcd.clear();
}
