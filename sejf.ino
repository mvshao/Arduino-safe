#include <Keypad.h> //biblioteka od klawiatury
#include <LiquidCrystal_I2C.h>
#include <Password.h>
#include <Wire.h>

Password password = Password( "0119" );

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

const byte ROWS = 4; // ile wierszy
const byte COLS = 3; //ile kolumn
 
byte rowPins[ROWS] = {2, 3, 4, 5}; //piny wierszy
byte colPins[COLS] = {6, 7, 8}; //piny kolum

char keys[ROWS][COLS] = { //mapowanie klawiatury
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
 
Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //inicjalizacja klawiatury
 
void setup(){
  pinMode(A1, OUTPUT);
  lcd.begin(16,2);
  lcd.backlight(); // zalaczenie podwietlenia
  lcd.setCursor(0,0);
  lcd.home();
  lcd.print("Wprowadz haslo:");
  lcd.setCursor(0,1); 
  klawiatura.addEventListener(keypadEvent);
 }

void cls() {
  lcd.clear();
  lcd.home();
  lcd.print("Wprowadz haslo:");
  lcd.setCursor(0,1); }

  void keypadEvent(KeypadEvent eKey){
  switch (klawiatura.getState()){
    case PRESSED:
  Serial.print("Wprowadz haslo: ");
  Serial.println(eKey);
        lcd.print('*');
  switch (eKey){
    case '*': checkPassword(); break;
    case '#': password.reset(); cls(); break;
    default: password.append(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()){
    lcd.setCursor(0,0);
    cls();
    lcd.setCursor(0,1);
    cls();
    lcd.setCursor(0,0);
    lcd.print("Uzyskano dostep!");
    lcd.setCursor(0,1);
    lcd.print("---otwieranie---");
    digitalWrite(A1, HIGH);
    delay(2000);
    digitalWrite(A1, LOW);
    password.reset();
    setup();
    
    //Add code to run if it works
  }else{
    lcd.setCursor(0,0);
    cls();
    lcd.setCursor(0,1);
    cls();
    lcd.setCursor(1,0);
    password.reset();
    delay(2000);
    setup();
    //add code to run if it did not work
    }

}

void loop()
{
  klawiatura.getKey();
}


