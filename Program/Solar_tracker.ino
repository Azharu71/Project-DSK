#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//inisiasi pin dll
const int ldrAtas = 32;
const int ldrBawah = 35;
const int servo = 15;
const int diff = 50;
const int solPan = 34;

//servo
LiquidCrystal_I2C lcd(0x27, 16, 2);  
int serPos = 120;
Servo myServo;

//Setup LCD
void Lcd(int A, int B, float Volt) {
  lcd.setCursor(0,0);
  lcd.print("LDR: ");
  lcd.print("A:");
  lcd.print(B);
  lcd.setCursor(6,0);
  lcd.print(" B:");
  lcd.print(A);

  lcd.setCursor(0,1);
  lcd.print("Tegangan: ");
  lcd.print(Volt);

}

//Fungsi untuk menghitung posisi center servo
void posisi(int A, int B){

  A += 67;
  int tengah = (A - B) ;
  if(tengah > diff && serPos < 120){
    serPos += 10;
  }else if(tengah < -diff && serPos > 20){
    serPos -= 10;
  }
  myServo.write(serPos);
  }


//Fungsi perhitungan arus pada solar panel
float volt(){
  int value = analogRead(solPan);
  float vSolpan = (value / 4095.0) * 5;
  return vSolpan;
}


void setup() {
//LCD
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  //SERVO
  myServo.attach(servo);
  myServo.write(serPos);

}


//Loop main program
void loop() {
  int atas = analogRead(ldrAtas);
  int bawah = analogRead(ldrBawah);
  float Voltage = volt();
  posisi(atas, bawah);
  Lcd(atas, bawah, Voltage);


  delay(200);
}
