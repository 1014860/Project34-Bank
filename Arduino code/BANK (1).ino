#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <Wire.h>
#include <String.h>


#define motorPin1 8
#define motorPin2 9
#define motorPin3 10
#define motorPin4 11
#define TX_PIN 6
#define RX_PIN 5
  String card_uid = ""; 
typedef enum {
  State_Card,
  State_Pin
}
current_state;
current_state state;

#define SS_PIN 10
#define RST_PIN 9 

MFRC522 mfrc522(SS_PIN, RST_PIN);

int keypad_pressed = 0;
int OK_button_pressed = 0;
int CANCEL_button_pressed = 0;
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {A2, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

         int a = 0;

int motor1 = 0;
const String password;
String input_password;
int wrong = 0;
int counter = 0;
String pin_code;
void setup() {
  Wire.begin(4);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  input_password.reserve(32);                                         //Maximale input van 32 characters voordat je niks meer kan invullen.
}

void loop() {
  static unsigned long EUR10 = millis();
  static unsigned long EUR20 = millis();

if (motor1 == 1) {
    if (millis() - EUR10 < 1000) {
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
    }
  }
  else if (motor1 == 2) {
    if (millis() - EUR20 < 1000) {
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW); 
    }
  }
  else if (motor1 == 3) {
    if (millis() - EUR10 < 1000 & millis() - EUR20 < 1000) {
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW); 
    }
  }
  else if (motor1 == 0) {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
  }
  
  int ok_button = digitalRead(A0);
  int cancel_button = digitalRead(A1);

  int Y = digitalRead(A0);
  int N = digitalRead(A1); 
  char userinput;
  char compare = 'a';
  char transfer_uid = 'T';
  char print_bon = 'P';
  char print_30 = 'O';
  char print_50 = 'M';
  char print_100 = 'S';
  char biljet_10 = 'X';
  char biljet_20 = 'B';
  char delay_ = 'D'; 
  char transactiebon_ja = 'L';
  char transactiebon_nee = 'K';
  
  if(Serial.available() > 0)
  {
    userinput = Serial.read();
    if(userinput == compare)
    {
      Serial.println("P"); 
    } 
    else if(userinput == transfer_uid)
    {
      Serial.println(card_uid);
    }
     else if(userinput == print_bon)
    {
      Serial.println("Q");
    }
      else if(userinput == delay_)
    {
      delay(5000);
      Serial.println("P");
    }
     else if(userinput == print_30)
    {
      Serial.println("W");
      motor1=1;
      delay(1200);
      motor1=2;
      delay(1200);
    }
     else if(userinput == print_50)
    {
      Serial.println("C");
      motor1=2;
      delay(1200);
      motor1=2;
      delay(1200);
      motor1=1;
      delay(1200);
    }
     else if(userinput == print_100)
    {
      Serial.println("V");
      motor1=2;
      delay(1200);
      motor1=2;
      delay(1200);
      motor1=2;
      delay(1200);
      motor1=2;
      delay(1200);
      motor1=2;
      delay(1200);
    }
     else if(userinput == biljet_10)
    {
      Serial.println("V");
    }
     else if(userinput == biljet_20)
    {
      Serial.println("V");
    }
    
  }


int i = 0;
char customKey = customKeypad.getKey();
  if(customKey)
  {
   Serial.println(customKey);
  }
  if(Y == 0)
  {
     Serial.println("Y");
     delay(200);
  }
   if(N == 0)
  {
     Serial.println("N");
     delay(200);
  }
  
  switch (state) {
  
    case State_Card: {
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;
      }
      if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
      }
      Serial.println("M");
      /*
       * Ik haal de Serial.println statements even weg, die interferen met de GUI
       */
      
    //  Serial.print("UID tag:");
      String content = "";
      byte letter;
      for (byte i = 0; i < mfrc522.uid.size; i++) {
       //  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       //  Serial.print(mfrc522.uid.uidByte[i], HEX);
         content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
         content.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
   //   Serial.println();
      content.toUpperCase();
      card_uid =  content.substring(1);
      //Serial.println(card_uid);
      if (content.substring(1) == "E4 0D 2E 2A" || content.substring(1) == "14 F1 D4 2B" || content.substring(1) == "C9 0C 72 C2" || content.substring(1) == "99 4A D1 B9") { // Marouan || Connor || Frank
        if (content.substring(1) == "E4 0D 2E 2A") {
          password = "1234";                                          //Wanneer deze pas wordt herkend geeft moet de wachtwoord 1234 worden ingevuld.
        }
        else if (content.substring(1) == "14 F1 D4 2B") {
          password = "2468";                                          //Wanneer deze pas wordt herkend geeft moet de wachtwoord 0000 worden ingevuld.
        }
       // Serial.println("Authorized access");
       // Serial.println("Enter password: ");
        state = State_Pin;                                            //Als de pas wordt geaccepteerd mag die zijn pincode invullen.
      }
      else {
        //Serial.println("Access denied");                              //Bij een verkeerde pas geeft die dit aan. (Er kan geen pincode ingevoerd worden.) 
      }
    }
    break;
    case State_Pin: {
     /*
    compare = 'H';
    while(userinput != compare)
    {
      if(Serial.available() > 0)
      {
        userinput = Serial.read();
        pin_code = pin_code + userinput;
        if(userinput == compare)
        {
          Serial.println("P"); 
        } 
      }
    }
    Serial.println(pin_code);
    pin_code = "";*/
      
      
      
      
      
      /* Dit haal ik even weg, kan later weer toegevoegd worden.
      char pin = customKeypad.getKey();
      if (pin) {
        if (pin != '#' && pin != '*') {
          Serial.println("*");                                        //Als er een pin wordt ingetoets komt er een * in zijn plaats te staan. Verander ("*") naar (pin) om de getallen te kunnen zien.
        }
        if (pin == '*') {
          input_password = "";
        }
        else if (pin == '#') {
          counter++;                                                  //Telt hoevaak er is geprobeerd om in te loggen.
          //Serial.print("COUNT: ");
          //Serial.println(counter);
          if (password == input_password) {
            Serial.println("Correct password");
            wrong = 0;                                                //Als het wachtwoord klopt wordt de teller van foute wachtwoorden terug naar 0 gezet.
            state = State_Card;
          }
          else if (password != input_password) {
            wrong++;                                                  //Telt hoevaak het wachtwoord verkeerd is ingevuld.
          }
          if (wrong == 1) {
            Serial.println("Incorrect password, 2 tries left!");
          }
          else if (wrong == 2) {
            Serial.println("Incorrect password, 1 try left!");
          }
          else if (wrong == 3) {
            Serial.println("Card is blocked");                         //Bij 3 foutmeldingen wordt de pas 'geblokkeerd'. (Nu wordt je alleen uitgelogd.)
            state = State_Card;
          }
          input_password = "";
        }
        else {
          input_password += pin;
        }
      }*/
    }
    break;
    default: {
      break;
    }
  }
/*void printer() {
  pinMode(7, OUTPUT); digitalWrite(7, LOW);

  mySerial.begin(9600);
  printer.begin();

  printer.justify('C');
  printer.setSize('L');
  printer.boldOn();
  printer.println("MoneyMakers");
  printer.println("________________");

  printer.justify('L');
  printer.setSize('S');
  printer.setLineHeight(30);
  printer.println("Terminal: 3");
  printer.println("Account: XXXX XXXX XXXX ..");
  printer.println("Transactie: 00000001");

  printer.setSize('M');
  printer.println("BETALING");
  printer.boldOff();
  printer.setSize('S');
  printer.println("'Datum & Tijd'");

  printer.setSize('M');
  printer.boldOn();
  printer.println("Totaal: 'Prijs' EUR");
  printer.justify('C');
  printer.setSize('L');
  printer.println("SUCCES");
  printer.boldOff();
  printer.feed(3);
  
  printer.sleep();
  delay(3000L);
  printer.wake();
  printer.setDefault();
}*/  
}
