#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

const char* ssid = "NOME_DA_SUA_REDE";
const char* password = "SENHA_DA_REDE";

DHT dht(DHTPIN, DHTTYPE);

const char* serverName = "http://192.168.0.100:3001/meteo/"; // Substitua pelo IP da sua máquina

void setup() {
    Serial.begin(115200);
    dht.begin();
  
    WiFi.begin(ssid, password);
    Serial.print("Conectando ao Wi-Fi");
  
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
  
    Serial.println("\nConectado ao Wi-Fi.");
  }
  void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
  
    if (isnan(h) || isnan(t)) {
      Serial.println("Erro: Falha na leitura do sensor DHT11!");
      delay(5000);
      return;
    }
  
    int leituraAnalogica = analogRead(pinSensorAnalogico);
    float ppmEstimado = map(leituraAnalogica, 0, 1023, 400, 10000);
    float tensaoUV = leituraAnalogica * (3.3 / 1023.0);
  
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");
  
      // Criando o JSON
      StaticJsonDocument<200> jsonDoc;
      jsonDoc["temperatura"] = t;
      jsonDoc["umidade"] = h;
      jsonDoc["co2"] = ppmEstimado;
      jsonDoc["uv"] = tensaoUV;
  
      String requestBody;
      serializeJson(jsonDoc, requestBody);
  
      int httpResponseCode = http.POST(requestBody);
  
      Serial.print("Código de resposta HTTP: ");
      Serial.println(httpResponseCode);
  
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Resposta da API:");
        Serial.println(response);
      } else {
        Serial.print("Erro na requisição: ");
        Serial.println(http.errorToString(httpResponseCode));
      }
  
      http.end();
    } else {
      Serial.println("Wi-Fi desconectado.");
    }
  
    delay(5000); // Aguarda 5 segundos
  }
    