//LM35 ----> Temperatura
//LDR  ----> Luminosidade
//DHT22 ----> Umidade
//BMP280 ---->  Pressão

//DHT22
#include <Adafruit_Sensor.h> // importando as bibliotecas para os sensores
#include <DHT.h>

const int DHT_PIN = 2;

DHT dht(DHT_PIN, DHT22); // umidade, umidade corrigida

float umid, umid_corrigida;

//LCD
#include <LiquidCrystal_I2C.h>

// Declara um objeto LiquidCrystal_I2C
// Endereço: 0x3f (pode ser 0x27)
// Colunas : 16
// Linhas  : 2
LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte graus_symbol = 0;
const byte graus_bitmap[8] = {
    B11100,
    B10100,
    B11100,
    B00000,
    B00000,
    B00000,
    B00000,
};

//BMP280 ----> Pressão e Altitude
#include <Adafruit_Sensor.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_BMP280.h> //INCLUSÃO DE BIBLIOTECA

Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)


void setup() {
  Serial.begin(9600); // Comunicação Serial 9600 bps
//BMP280

//SE O SENSOR NÃO FOR INICIALIZADO NO ENDEREÇO I2C 0x76
  if(!bmp.begin(0x76)){ 
    //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.println("Sensor BMP280 não foi identificado! Verifique as conexões.");
    // Trava o arduino em um loop while que nunca termina... while(true)
    while(1==1) {};
  }
}


void loop() {
//LM35

  // Lê tensão Analógica na porta A0
  // O valor lido será um inteiro entre 0 e 1023
  int leitura_adc = analogRead(A0);
  // Converte o valor lido para um valor em volts
  // 1.1 ou 1.1f para forçar numero real
  float voltagem = leitura_adc * (1.1f / 1023); // transformação analógico em digital 
  // Calcula a temperatura
  // LM35: 10mV => 1 grau C
  float temperatura = voltagem * 100.0;// transforma de mv(mili Volts) para valores digitais em graus
  float temperatura_corrigida = (temperatura * (1 / 0.980109325)) - (0.023536109) / (0.980109325); // calculo da incerteza que "corrigi o valor lido pelo sensor"
 // DHT22
 
  umid = dht.readHumidity();// função do próprio sensor: Temperatura do próprio sensor 
  umid = 1.00 * umid + 0.00;
  umid_corrigida = (umid * 1.21) - 18.1; // // calculo da incerteza que "corrigi o valor lido pelo sensor"

//LDR

  int bin; // variável interna que ler a tensão analógica na porta escolhida 
  float tensao, res, lum; // defino as variáveis 

  bin = analogRead(A1);
  tensao = bin*1.1/1023.0; //transformação analógico em digital
  res = 330*(5.0/tensao+1); 
  lum = pow(10, 5-log10(res));// conversão em lux 
    
  

//imprime a "UMIDADE NO SERIAL":

  Serial.print("umidade corrigida= ");
  Serial.println(umid_corrigida);
 
 //imprime a "TEMPERATURA NO SERIAL":
 
  Serial.println("temperatura Corrigida");
  Serial.println(temperatura_corrigida, 3);
 

 //Imprime a "PRESSÃO NO SERIAL":
 
    Serial.println(F("Pressão: ")); 
    
    Serial.print(bmp.readPressure()); 
    Serial.println(" Pa (Pascal)"); 
    Serial.print(bmp.readPressure()*9.86923*0.000001); 
    Serial.println(" atm (Presão atmosférica)"); 
    
 //Imprime a "ALTURA APROX. NO SERIAL":
   
    Serial.print(F("Altitude aprox.: ")); 
    Serial.print(bmp.readAltitude(1020.6),0); 
    Serial.println(" m (Metros)"); 
 
//Imprime a "LUMINOSIDADE NO SERIAL":

  Serial.print("\nLuminosidade :");
  Serial.println(lum);
  Serial.println();
 
// COLUNA: 0 a 15; e LINHA: 0 a 1;

  lcd.setBacklight(1);// ligar o lcd e receber as informaçoes 

  delay(1500);
//Imprime a "ESTAÇÃO METEROLÓGICA":

  lcd.setBacklight(1);
  lcd.setCursor(0, 0); // coluna 0 e linha 0
  lcd.print("    Estacao         ");
  lcd.setCursor(0, 1); // coluna 0 e linha 0
  lcd.print("  Meterologica              ");
  delay(1500);
  
// Imprime o "GRUPO":

  lcd.setBacklight(1);
  lcd.setCursor(0, 0); 
  lcd.print("Grupo:          "); 
  lcd.setCursor(0, 1); 
  lcd.print("                 ");
  delay(1500);
  
// Imprime os "INTEGRANTES":

  lcd.setBacklight(1);
  lcd.setCursor(0, 1); // coluna 0 e linha 0
  lcd.print("Gabriel Araujo              ");
  delay(1500);

  lcd.setBacklight(1);
  lcd.setCursor(0, 1); // coluna 0 e linha 0
  lcd.print("Rodrigo Lima              ");
  delay(1500);

  lcd.setBacklight(1);
  lcd.setCursor(0, 1); // coluna 0 e linha 0
  lcd.print("Sarah Pimenta               ");
  delay(1500);
  
//Imprime a "TEMPERATURA":

  lcd.setBacklight(1);
  lcd.setCursor(0, 0); // coluna 0 e linha 0
  lcd.print("  Temperatura  ");
  lcd.setCursor(0, 1);
  lcd.print("                          ");
  lcd.setCursor(6, 1);
  lcd.write(graus_symbol);
  lcd.setCursor(0, 1);
  lcd.print(temperatura_corrigida);
  lcd.setCursor(7, 1);
  lcd.print("C");

  delay(1500);

// Imprime a "UMIDADE":

  lcd.setBacklight(1);
  lcd.setCursor(0, 0); // coluna 0 e linha 0
  lcd.print("    Umidade  ");
  lcd.setCursor(0, 1);
  lcd.print("                          ");
  lcd.setCursor(0, 1);
  lcd.print(umid_corrigida);
  lcd.print(" %  ");

  delay(1500);

// Imprime a "PRESSÃO":

  lcd.setBacklight(1);
  lcd.setCursor(0, 0); // coluna 0 e linha 0
  lcd.print("    Pressao  ");
  lcd.setCursor(0, 1);
  lcd.print("                          ");
  lcd.setCursor(0, 1);
  lcd.print((bmp.readPressure()*9.86923*0.000001));
  lcd.print(" atm  ");

  delay(1500);
  
// Imprime a "ALTITUDE":
  lcd.setCursor(0, 0); // coluna 0 e linha 0
  lcd.print("    Altitude  ");
  lcd.setCursor(0, 1);
  lcd.print("                          ");
  lcd.setCursor(0, 1);
  lcd.print(bmp.readAltitude(1020.6),0);
  lcd.print(" m  ");

  delay(1500);

  // Imprime a "LUMINOSIDADE":
  lcd.setBacklight(1);
  lcd.setCursor(0, 0); // coluna 0 e linha 0
  lcd.print("  Luminosidade  ");
  lcd.setCursor(0, 1);
  lcd.print("                          ");
  lcd.setCursor(0, 1);
  lcd.print(lum);
  lcd.print(" lux  ");

  delay(1500);
}
