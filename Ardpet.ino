#include <DS3231.h>

DS3231 rtc(SDA, SCL);
Time t;

// Pin
int pinRed = 8;
int pinRele = 7;
int pinButton = 10;

// Time
int currentH, currentM;
String aux = "10:16";
int firstLunchH, firstLunchM;
int secondLunchH, secondLunchM;

// limit


void setup() {

  pinMode(pinRele, OUTPUT);
  pinMode(pinButton, INPUT);
  pinMode(pinRed, INPUT);

  rtc.begin();
  //    rtc.setDate(30, 11, 2022); // mm-dd-yy
  //    rtc.setDOW(WEDNESDAY); // Day of week
  //    rtc.setTime(10, 49, 00); // HH:mm:ss
  Serial.begin(9600);
}

void loop() {

  
  Serial.println(aux);
  String aux1 = aux.substring(0,2);
  String aux2 = aux.substring(3,5);
  firstLunchH = aux1.toInt();
  firstLunchM = aux2.toInt();  
  
  
  Serial.print("Hora refeicao = ");
  Serial.println(firstLunchH);
  Serial.print("Minuto refeicao = ");
  Serial.println(firstLunchM);
  
// ACIONAMENTO MANUAL DO MOTOR
//========================================================//========================================================//=======================================

  if (digitalRead(pinButton) == LOW) {
    digitalWrite(pinRele, HIGH);
    delay(1000);
  }
  digitalWrite(pinRele, LOW);

//========================================================//========================================================//=======================================

// Monitorar tempo
//========================================================//========================================================//=======================================

  t = rtc.getTime();
  currentH = t.hour;
  currentM = t.min;

  Serial.print("Hora ");
  Serial.println(currentH);
  Serial.print("Minuto ");
  Serial.println(currentM);
  Serial.println("");
  delay(1000);

//========================================================//========================================================//=======================================


// Condicao para iniciar com tempo
//========================================================//========================================================//=======================================

  if (currentH == firstLunchH && currentM == firstLunchM) {
    bool start = true;
    do {
      if (LOW == digitalRead(pinRed)) {
        Serial.println("encerrar");
        digitalWrite(pinRele, LOW);
        delay(60000);
        break;
      }
      digitalWrite(pinRele, HIGH);
      delay(1000);
      Serial.println("funcionando");
    } while (start);
  }
//========================================================//========================================================//=======================================
}
