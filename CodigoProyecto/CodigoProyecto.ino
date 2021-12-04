#include <LiquidCrystal.h>

//---Definimos los pines de entrada de nuestra LCD---
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

//---Los mandamos a la libreria---
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//---Definimos pines y variables---
#define Flame A0
#define Gas A1
#define Pir A2
#define Vib A3
#define Ir A4
#define Buzzer A5
#define Switch 7
boolean Fuego, Humo, Intruso, Ventana, Puerta;
boolean Mode = false;

void setup() {

  // ---Establecemos entradas y salidas---
  pinMode(Flame, INPUT_PULLUP);
  pinMode(Gas, INPUT_PULLUP);
  pinMode(Pir, INPUT_PULLUP);
  pinMode(Vib, INPUT_PULLUP);
  pinMode(Ir, INPUT_PULLUP);
  pinMode(Switch, INPUT_PULLUP);
  pinMode(Buzzer, OUTPUT);

  //---Pantalla de inicio---

  //Establecemos tamaño de nuestra pantalla
  lcd.begin(20, 4);

  lcd.setCursor(2, 0);
  lcd.print("Sistema de Alarma");
  lcd.setCursor(8, 1);
  lcd.print(" USO");
  lcd.setCursor(3, 2);
  lcd.print("Arquitectura de ");
  lcd.setCursor(4, 3);
  lcd.print("Computadoras.");
  delay(700);
  lcd.clear();

  //---Llamamos nuestro display base de texto---
  Display_Base();
}

void loop()
{

  //---establecemos valor de variables---
  Fuego = digitalRead(Flame);
  Humo = digitalRead(Gas);
  Intruso = digitalRead(Pir);
  Ventana = digitalRead(Vib);
  Puerta = digitalRead(Ir);
  Mode = digitalRead(Switch);

  //---llamamos a mostrar valor de los sensores---
  Sensor_Valores();

  //---Aqui determinamos el tipo de sistema que usaremos---
  if (Mode == false) {

    /*El modo normal solo cambia texto de la primer linea y no activa el
      buzzer*/
    lcd.setCursor(3, 0);
    lcd.print("  Modo Normal   ");
  } else {

    /*El modo seguridad activa un buzzer cuando se obtiene valor HIGH
      en cualquier sensor*/
    lcd.setCursor(3, 0);
    lcd.print("Modo Seguridad");
    if ((Fuego == HIGH) || (Humo == HIGH) || (Intruso == HIGH) || (Ventana == HIGH) || (Puerta == HIGH)) {
      digitalWrite(Buzzer, HIGH);
    } else {
      digitalWrite(Buzzer, LOW);
    }
  }
}

//---Funcion para mostrar sensores, el texto---
void Display_Base() {
  lcd.setCursor(0, 1);
  lcd.print("Fuego:");
  lcd.setCursor(0, 2);
  lcd.print("Humo:");
  lcd.setCursor(10, 1);
  lcd.print("Puerta:");
  lcd.setCursor(10, 2);
  lcd.print("Ventana:");
  lcd.setCursor(5, 3);
  lcd.print("Intruso:");
}

//---Funcion para mostrar sensores, los valores---
void Sensor_Valores() {
  if (Fuego == true) {
    lcd.setCursor(6, 1); lcd.print("Si");
  } else {
    lcd.setCursor(6, 1); lcd.print("No");
  }
  if (Humo == true) {
    lcd.setCursor(5, 2); lcd.print("Si");
  } else {
    lcd.setCursor(5, 2); lcd.print("No ");
  }
  if (Puerta == true) {
    lcd.setCursor(17, 1); lcd.print("Si");
  } else {
    lcd.setCursor(17, 1); lcd.print("No ");
  }
  if (Ventana == true) {
    lcd.setCursor(18, 2); lcd.print("Si");
  } else {
    lcd.setCursor(18, 2); lcd.print("No ");
  }
  if (Intruso == true) {
    lcd.setCursor(13, 3); lcd.print("Si");
  } else {
    lcd.setCursor(13, 3); lcd.print("No ");
  }
}
