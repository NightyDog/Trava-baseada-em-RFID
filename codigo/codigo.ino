#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>
#include <SPI.h>

#define SERVO_PIN 8 // Pino Digital 8 (PWM)

// Criando instancias
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(10, 9); // MFRC522 mfrc522(SS_PIN, RST_PIN)
Servo sg90;

//Inicializa pinos para os LEDs, servo e buzzer
constexpr uint8_t greenLed = 7;
constexpr uint8_t redLed = 6;
constexpr uint8_t buzzerPin = 5;

char initial_password[4] = {'4', '4', '4', '4'};  // Variavel para guardar a senha correta
String tagUID = "73 57 68 09";  // String para guardar a UID da tag correta, cada autênticador tem uma UID diferente, mudê para a sua se for necessário
char password[4];   // Variavel para guardar as senhas dos usuários
boolean RFIDMode = true; // boolean para mudar os modos
char key_pressed = 0; // Variavel para guardar as chaves de entrada
uint8_t i = 0;  // Variável usada para o contador
int pos; // posição do servo

// Definindo quantas linhas e colunas o nosso keypad possuí
const byte rows = 4;
const byte columns = 4;

// mapa do keypad
char hexaKeys[rows][columns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// inicializando os pinos do keypad
byte row_pins[rows] = {A0, A1, A2, A3};
byte column_pins[columns] = {2, 1, 0};

// Criando uma instância para o keypad
Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);

void setup() {
  // COnfiguração dos pinos do Arduino
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  sg90.attach(SERVO_PIN);  //Declara o pino 8 para o Servo
  sg90.write(0); // Define a posição zero como a inicial

  lcd.init();   // Tela LCD
  lcd.backlight();
  SPI.begin();      // Inicia SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522

  lcd.clear(); // Limpa a tela LCD
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  // O sistema procurará primeiro o modo
  if (RFIDMode == true) {
    lcd.setCursor(0, 0);
    lcd.print("   Door Locked");
    lcd.setCursor(0, 1);
    lcd.print(" Scan Your Tag ");

    // Procurando novos cartões
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }

    // Seleciona um dos cartões
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }

    //Lendo  através do cartão
    String tag = "";
    for (byte j = 0; j < mfrc522.uid.size; j++)
    {
      tag.concat(String(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " "));
      tag.concat(String(mfrc522.uid.uidByte[j], HEX));
    }
    tag.toUpperCase();

    //Checando o cartão
    if (tag.substring(1) == tagUID)
    {
      // Se a UID corresponde corretamente:
      lcd.clear();
      lcd.print("Tag Matched");
      digitalWrite(greenLed, HIGH);
      delay(3000);
      digitalWrite(greenLed, LOW);

      Serial.println("enter");
      lcd.clear();
      lcd.print("Enter Password:");
      lcd.setCursor(0, 1);
      RFIDMode = false; // RFID False
    }

    else
    {
      // Se a UID não corresponder
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Wrong Tag Shown");
      lcd.setCursor(0, 1);
      lcd.print("Access Denied");
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(redLed, HIGH);
      delay(3000);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(redLed, LOW);
      lcd.clear();
    }
  }

  // Se o modo RFID for falso, ele procurará teclas do teclado
  if (RFIDMode == false) {
    key_pressed = keypad_key.getKey(); // armazenando chaves
    if (key_pressed)
    {
      password[i++] = key_pressed; // armazenando a variável da senha
      lcd.print("*");
      Serial.println("*");

    }
    if (i == 4) // Se os 4 digitos for digitado
    {
      delay(200);
      if (!(strncmp(password, initial_password, 4))) // Se a senha esta correta
      {
        lcd.clear();
        lcd.print("Pass Accepted");
        Serial.println("Pass Accepted");
        // Abre a porta
        for(pos = 0; pos < 90; pos++)
        {
          sg90.write(pos);
          delay(15);
        }
        digitalWrite(greenLed, HIGH);
        delay(3000);
        digitalWrite(greenLed, LOW);
        // Fecha a porta
        for(pos = 90; pos >= 0; pos--)
        {
          sg90.write(pos);
          delay(15);
        }
        i = 0;
        RFIDMode = true; // Faz o RFID True
        Serial.println("A porta deveria ja ter fechado.");
      }
      else    // Se a senha estiver errada:
      {
        lcd.clear();
        lcd.print("Wrong Password");
        digitalWrite(buzzerPin, HIGH);
        digitalWrite(redLed, HIGH);
        delay(3000);
        digitalWrite(buzzerPin, LOW);
        digitalWrite(redLed, LOW);
        lcd.clear();
        i = 0;
        RFIDMode = true;  //
      }
    }
  }
}
