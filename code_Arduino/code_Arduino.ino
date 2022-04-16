// Bluetooth _____________
#include <SoftwareSerial.h>
#define rxPin 10
#define txPin 11
#define baudrate 9600
SoftwareSerial mySerial(rxPin,txPin);

const int Vadc=A0;

// _________ OLED __________________
#include <Adafruit_SSD1306.h>
#define nombreDePixelsEnLargeur 128
#define nombreDePixelsEnHauteur 64
#define brocheResetOLED -1
#define adresseI2CecranOLED 0x3C

Adafruit_SSD1306 ecranOLED (nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);

// _________ Encodeur rotatoire ___________
#define encoder0PinA 2
#define encoder0PinB 4
#define Switch 3
volatile unsigned int encoder0Pos=0;
volatile unsigned int Encoder_memo=0;
volatile unsigned int switch0=0;
volatile unsigned int Switch_memo=0;
int line = 0;

void setup() {
  // put your setup code here, to run once:
  // _______ Bluetooth _____________
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(baudrate);
  
  Serial.begin(baudrate);
  Serial.print("Demarrage de programme");
  // ________ OLED __________________
  if (!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED))
    while(1);
  byte tailleDeCaractere=2; 
  ecranOLED.clearDisplay();
  ecranOLED.setTextSize(tailleDeCaractere);
  ecranOLED.setCursor(0,0);
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.println("Menu :");
  ecranOLED.println("Resistance");
  ecranOLED.println("Encoder");
  ecranOLED.println("Authors");
  ecranOLED.display();
  // ________ Encodeur rotatoire _____________
  pinMode (encoder0PinA, INPUT);
  digitalWrite(encoder0PinA, HIGH);
  pinMode(encoder0PinB,INPUT);
  digitalWrite(encoder0PinB,HIGH);
  attachInterrupt(0, doEncoder, RISING);
  pinMode(Switch,INPUT);
  digitalWrite(Switch,HIGH);
  attachInterrupt(1, doSwitch, RISING);
}

void loop() {
  Serial.println("");
  // ________ Lecture de la résistance ___________________
  double Voltage=analogRead(Vadc)*5.0/1023.0;
  delay(1800);
  Serial.print(Voltage);
  Serial.println(" Volts");
  double Rs=(1+(100000/1000))*100000*(5/Voltage)-100000-10000;
  mySerial.println(Rs/4);
  Serial.print("Sensor resistance : ");
  Serial.print(Rs/1000000);
  Serial.println(" Mohms");
  
  // __________ Encodeur rotatoire _________________________
  Serial.print("Position:");
  Serial.println(encoder0Pos, DEC);
  if (Encoder_memo!=encoder0Pos) {
      // surligne la ligne en dessous
     line = OLEDunderline(line);
  }
  Encoder_memo = encoder0Pos;
  Serial.print("switch0: ");
  Serial.println(switch0);
  if (Switch_memo!=switch0) { // entrer dans un menu
    if (((line-1)%3)==0) {
      MenuAuthors();
      Serial.println("---------Switch a marché");
    }
    else {
      if (((line-1)%2)==1){
        if (encoder0Pos>65500){ // if the value is too high OLED screen can not display the number
          MenuEncoder(encoder0Pos-65500);         
        }
        else {
          MenuEncoder(encoder0Pos);
        }
        Serial.println("---------Switch a marché");
      }
      if (((line-1)%2)==0){
        MenuResistance(Rs/(double)1000);
        Serial.println("---------Switch a marché");
      }
    }
  }
  Switch_memo=switch0;
}

// _________ Interrupts: Encodeur rotatoire ___________
void doEncoder(){
  if (digitalRead(encoder0PinB)==HIGH){
    encoder0Pos++;
  }else{
    encoder0Pos--;
  }
}

void doSwitch(){
  if (digitalRead(Switch)==HIGH){
    switch0++;
  }
}

// __________ OLED functions _____________
int OLEDunderline(int line) {
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 1);
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.println("Menu :");
    if ((line%3)==0) {
     ecranOLED.println("Resistance");
     ecranOLED.println("Encoder");
     ecranOLED.setTextColor(SSD1306_BLACK,SSD1306_WHITE);
     ecranOLED.println("Authors");
    }
    else {
      if ((line%2)==0){
         ecranOLED.setTextColor(SSD1306_BLACK,SSD1306_WHITE);
         ecranOLED.println("Resistance");
         ecranOLED.setTextColor(SSD1306_WHITE);
         ecranOLED.println("Encoder");
         ecranOLED.println("Authors");
      }     
      if ((line%2)==1) {
         ecranOLED.println("Resistance");
         ecranOLED.setTextColor(SSD1306_BLACK,SSD1306_WHITE);
         ecranOLED.println("Encoder");
         ecranOLED.setTextColor(SSD1306_WHITE);
         ecranOLED.println("Authors");
      }
    }
  ecranOLED.display();
  return line+1;
}

void MenuResistance(double res){
  Serial.println(res);
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 1);
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.println(" ");
  ecranOLED.println("Resistance");
  ecranOLED.print("R:");
  ecranOLED.print(res);
  ecranOLED.print(" kOhm");
  ecranOLED.display();
  delay(500);
}

void MenuEncoder(int pos) {
  Serial.println(pos);
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 1);
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.println(" ");
  ecranOLED.println("Encoder");
  ecranOLED.println("position:");
  ecranOLED.print(pos);
  ecranOLED.display();
}

void MenuAuthors() {
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 1);
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.println("Louise ");
  ecranOLED.println(" Coussen");
  ecranOLED.println("Sarah");
  ecranOLED.println(" Barnova");
  ecranOLED.display();
}
