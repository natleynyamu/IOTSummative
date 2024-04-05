
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x26, 16, 2); 

int trigPinFront = 5;    // Trigger
int echoPinFront = 4;    // Echo
int trigPinRear = 9;    // Trigger
int echoPinRear = 8;    // Echo
int redLED = 7;
int greenLED = 6;
int buzzerPin =13;
float duration_front, cm_front, duration_rear, cm_rear;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(trigPinRear, OUTPUT);
  pinMode(echoPinRear, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.setCursor (0,0);
  lcd.print("Home Security");
  
}
 

void loop()
{
  
  digitalWrite(trigPinFront, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFront, LOW);
  noTone(buzzerPin);
  
  pinMode(echoPinFront, INPUT);
  duration_front = pulseIn(echoPinFront, HIGH);
 
  // Convert the time into a distance
  cm_front = (duration_front/200)*0.0343;
 
 
  Serial.print(cm_front);
  Serial.print(" front cm");
  Serial.println();
  
  
  digitalWrite(trigPinRear, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinRear, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRear, LOW);
  
  pinMode(echoPinRear, INPUT);
  duration_rear = pulseIn(echoPinRear, HIGH);
 
  // Convert the time into a distance
  cm_rear = (duration_rear/200)*0.0343;
 
 
  Serial.print(cm_rear);
  Serial.print(" rear cm");
  Serial.println();
  
  delay(250);
  
  if(cm_front <= 2 && cm_rear <= 2){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Front: ");
    lcd.print(cm_front);
    lcd.setCursor(1,1);
    lcd.print("Rear: ");
    lcd.print(cm_rear);
    digitalWrite(greenLED, LOW);
    tone(buzzerPin, 250);
    digitalWrite(redLED, HIGH);
    delay(2000);
    noTone(buzzerPin);
    digitalWrite(redLED, LOW); 
  }
  else if (cm_front<=2 || cm_rear <=2){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Front: ");
    lcd.print(cm_front);
    lcd.setCursor(1,1);
    lcd.print("Rear: ");
    lcd.print(cm_rear);
    digitalWrite(greenLED, LOW);
    tone(buzzerPin, 250);
    digitalWrite(redLED, HIGH);
    delay(2000);
    noTone(buzzerPin);
    digitalWrite(redLED, LOW);
  }else{
    lcd.clear();
    lcd.setCursor (0,0);
    lcd.print("Front&Rear safe");
    digitalWrite(greenLED, HIGH); 
    noTone(buzzerPin);
    digitalWrite(redLED, LOW);
    
  }
}