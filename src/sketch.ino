#include <DHT.h>

#define DHT_MODEL DHT22

#define LDR_PIN 4
#define DHT_PIN 42
#define BTN_N 12
#define BTN_P 13
#define BTN_K 14
#define RELAY_PIN 16

// Valores do tomate
#define TOMATO_HUMIDITY_MIN 40.0
#define TOMATO_PH_MIN 5.8
#define TOMATO_PH_MAX 7.2

// Valor máximo do ADC (Analog to Digital Converter - o pino do ldr é analógico
// :) ) disponível ou seja, 4095 = 100%
#define ADC_MAX 4095

DHT dht(DHT_PIN, DHT_MODEL);

// Retorna true, se os níveis de n p e k forem adequados para o tomate (simulado
// pelo on/off (low/high) do botão)
bool tomato_npk_ok(bool n, bool p, bool k) {
  return (n && p && k);
}

// Converte o valor do LDR para o pH, e retorna true caso esteja no aceitável
// para um tomate
bool tomato_ph_ok(int ldr_value) {
  float ph = (ldr_value * 14.0) / ADC_MAX;
  Serial.print("pH: ");
  Serial.println(ph);
  return (ph >= TOMATO_PH_MIN && ph <= TOMATO_PH_MAX);
}

// Returns true if soil humidity is below the minimum threshold (dry soil)
bool tomato_humidity_ok(float humidity) {
  return (humidity < TOMATO_HUMIDITY_MIN);
}

// Controla o relé (bomba de irrigação) baseado nas 3 condições:
// A irrigação só é acionada quando TODAS as condições forem favoráveis:
//  - o solo precisa de água (umidade abaixo do mínimo)
//  - o pH está na faixa aceitável (a água será aproveitada pela planta)
//  - os nutrientes estão adequados (a planta está saudável)
// Se qualquer condição não for atendida, o relé desliga e exibe o motivo com o Serial.println.
void turn_irrigation_on(bool dry_soil, bool ph_ok, bool npk_ok) {
  if (dry_soil && ph_ok && npk_ok) {
    // Todas as condições ok: liga a bomba
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Irrigation ON");
  } else {
    // Se alguma condição falhou, desliga a bomba e mostra o motivo com o Serial.println
    digitalWrite(RELAY_PIN, LOW);

    if (!dry_soil)
      Serial.println("Irrigation OFF - Soil moisture is sufficient");
    if (!ph_ok)
      Serial.println("Irrigation OFF - pH out of range");
    if (!npk_ok)
      Serial.println("Irrigation OFF - Insufficient nutrients");
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(BTN_N, INPUT_PULLUP);
  pinMode(BTN_P, INPUT_PULLUP);
  pinMode(BTN_K, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  // Lendo os sensores
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  // NPK iniciam adequados, e caso apertados, simulamos que um deles está inadequado
  bool n = (digitalRead(BTN_N) == HIGH);
  bool p = (digitalRead(BTN_P) == HIGH);
  bool k = (digitalRead(BTN_K) == HIGH);
  int ldr_value = analogRead(LDR_PIN);

  // Validando a leitura do DHT
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read DHT sensor!");
    delay(2000);
    return;
  }

  // Exibindo o nível dos sensores
  Serial.println("=============================");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("C");

  Serial.print("N: ");
  Serial.print(n ? "OK" : "LOW");
  Serial.print(" - P: ");
  Serial.print(p ? "OK" : "LOW");
  Serial.print(" - K: ");
  Serial.println(k ? "OK" : "LOW");

  // Ligar ou não a irrigação
  turn_irrigation_on(tomato_humidity_ok(humidity), tomato_ph_ok(ldr_value), tomato_npk_ok(n, p, k));

  delay(2000);
}
