#include <DHT.h>

#define DHT_MODEL DHT22

#define LDR_PIN 4
#define DHT_PIN 42
#define BTN_N 12
#define BTN_P 13
#define BTN_K 14
#define RELAY_PIN 16

// Tomato Thresholds
#define TOMATO_HUMIDITY_MIN 40.0
#define TOMATO_PH_MIN 5.8
#define TOMATO_PH_MAX 7.2

// Maxium value of ADC PIN
#define ADC_MAX 4095

DHT dht(DHT_PIN, DHT_MODEL);

// Returns true if n p k levels are adequate for the tomato (simulated by the
// on/off (low/high) of the button)
bool tomato_npk_ok(bool n, bool p, bool k) { return (n && p && k); }

// Converts LDR value to pH and returns true if it is within the acceptable
// range for pre defined tomato thresholds
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

// Function that turns the relay on based in 3 conditions:
//  - humity: the soil needs water (humidity below the minimum)
//  - ph: the pH is in the acceptable range
//  - npk: the nutrients are adequate (the plant is healthy)
// If any condition is not met, the relay turns off and the reason is displayed
// with Serial.println
void turn_irrigation_on(bool dry_soil, bool ph_ok, bool npk_ok) {
  if (dry_soil && ph_ok && npk_ok) {
    // if all conditions are true, we turn on the relay
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Irrigation ON");
  } else {
    // if any condition is not met, we turn off the relay and display the reason
    // with Serial.println
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
  // Reading sensors
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  // NPK start adequate, and if pressed, we simulate that one of them is
  // inadequate
  bool n = (digitalRead(BTN_N) == HIGH);
  bool p = (digitalRead(BTN_P) == HIGH);
  bool k = (digitalRead(BTN_K) == HIGH);
  int ldr_value = analogRead(LDR_PIN);

  // Validating DHT sensor reading
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read DHT sensor!");
    delay(2000);
    return;
  }

  // Displaying sensor levels
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

  // Turn on or off irrigation
  turn_irrigation_on(tomato_humidity_ok(humidity), tomato_ph_ok(ldr_value),
                     tomato_npk_ok(n, p, k));

  delay(2000);
}
