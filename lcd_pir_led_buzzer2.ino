#include <LiquidCrystal.h>     


int ledPin = 13;                // choose the pin for the LED
int inputPin = 7;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int pinSpeaker = 10;           //Set up a speaker on a PWM pin (digital 9, 10, or 11)

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);                          // initialize the library with the numbers of the interface pins



void setup() {  pinMode(ledPin, OUTPUT);      // declare LED as output  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(pinSpeaker, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2); 
  lcd.setCursor(2, 0);                                            // Set LCD cursor position (column, row)
  lcd.print("Hareket");                                      // Print text to LCD
  lcd.setCursor(5, 1);                                            // Set LCD cursor position (column,row) 
  lcd.print("Algilama");                                            // Print text to LCD
  delay(2000); // wait 2s                                      // Delay to read text
  lcd.clear(); // clear LCD display                               // Clear the display
  lcd.setCursor(2, 0);                                            // Set LCD cursor position (column, row)
  lcd.print("Gelistiren");                                     // Print text to LCD
  lcd.setCursor(2, 1);                                            // Set LCD cursor position (column, row) 
  lcd.print("Mira KUCUK");                                         // Print text to LCD                                                                                                                                                                                                                                                                                                                                                                                                                       
delay(3000);                                                      // Delay to read text
lcd.clear();                                                    // Clear LCD    
lcd.setCursor(0, 0); 
      lcd.print("Bilgi Bekleniyor");
      delay(3000);
      lcd.clear(); 
      lcd.setCursor(3, 0);
      lcd.print("Asayis");
      lcd.setCursor(3, 1);
      lcd.print("Berkemal");      

  
}

void loop(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    playTone(300, 300);
    delay(500);

    
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("hirsiz var");
      lcd.clear() ;
      lcd.setCursor(0, 0);                                           // Set LCD cursor position (column 0, row 0)
      lcd.print("hirsiz var");   
      
      
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
      digitalWrite(ledPin, LOW); // turn LED OFF
      playTone(0, 0);
      delay(3000);    
      if (pirState == HIGH){
      // we have just turned of
      Serial.println("tehlike gecti");
      lcd.clear() ;
      lcd.setCursor(3, 0); 
      lcd.print("Tehlike"); 
      lcd.setCursor(3, 1);
      lcd.print("Gecti...");      // We only want to print on the output change, not state 
     pirState = LOW;
    }
  }
}
// duration in mSecs, frequency in hertz
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 100000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}
