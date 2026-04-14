#include <DHTesp.h>

// ======================================
// PIN DEFINITIONS
// ======================================
const int LDR_PIN = 4;           // Analog input from the LDR sensor
const int DHT_PIN = 42;          // Digital pin connected to the DHT22 sensor
const int N_BUTTON_PIN = 12;     // Nitrogen button
const int P_BUTTON_PIN = 13;     // Phosphorus button
const int K_BUTTON_PIN = 14;     // Potassium button
const int RELAY_PIN = 16;        // Relay controlling the irrigation pump

// ======================================
// SIMULATION PARAMETERS
// ======================================
const float PH_MIN_ACCEPTABLE = 5.8;
const float PH_MAX_ACCEPTABLE = 7.2;
const float SOIL_MOISTURE_MIN = 40.0;
const float SOIL_MOISTURE_MAX = 70.0;
const int ADC_RESOLUTION = 4095;

// ======================================
// SENSOR OBJECTS
// ======================================
DHTesp dhtSensor;

// ======================================
// AUXILIARY FUNCTIONS
// ======================================

// Converts the raw LDR analog reading into a simulated pH scale from 0 to 14
float calculateSimulatedPH(int ldrRawReading) {
  return (ldrRawReading * 14.0) / ADC_RESOLUTION;
}

// Verifies whether the simulated pH is within the acceptable range for tomato cultivation
bool isPHWithinAcceptableRange(float simulatedPH) {
  return (simulatedPH >= PH_MIN_ACCEPTABLE && simulatedPH <= PH_MAX_ACCEPTABLE);
}

// Verifies whether at least two out of the three nutrients are in an adequate state
bool hasMinimumNutrientCondition(bool nitrogenAdequate, bool phosphorusAdequate, bool potassiumAdequate) {
  int adequateNutrientCount = 0;

  if (nitrogenAdequate) adequateNutrientCount++;
  if (phosphorusAdequate) adequateNutrientCount++;
  if (potassiumAdequate) adequateNutrientCount++;

  return (adequateNutrientCount >= 2);
}

// Prints the pH condition to the Serial Monitor
void printPHCondition(float simulatedPH) {
  if (simulatedPH < PH_MIN_ACCEPTABLE) {
    Serial.println("pH condition: Too acidic for tomato cultivation.");
  } else if (simulatedPH > PH_MAX_ACCEPTABLE) {
    Serial.println("pH condition: Too alkaline for tomato cultivation.");
  } else {
    Serial.println("pH condition: Acceptable for tomato cultivation.");
  }
}

// ======================================
// SETUP
// ======================================
void setup() {
  Serial.begin(115200);

  pinMode(N_BUTTON_PIN, INPUT_PULLUP);
  pinMode(P_BUTTON_PIN, INPUT_PULLUP);
  pinMode(K_BUTTON_PIN, INPUT_PULLUP);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Irrigation system starts turned off

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  Serial.println("==============================================");
  Serial.println("SMART IRRIGATION SYSTEM FOR TOMATO CULTIVATION");
  Serial.println("==============================================");
}

// ======================================
// MAIN PROGRAM LOOP
// ======================================
void loop() {
  // --------------------------------------
  // Nutrient button readings
  // Pressed button = adequate nutrient
  // INPUT_PULLUP logic:
  // LOW  = pressed
  // HIGH = not pressed
  // --------------------------------------
  bool nitrogenAdequate = (digitalRead(N_BUTTON_PIN) == LOW);
  bool phosphorusAdequate = (digitalRead(P_BUTTON_PIN) == LOW);
  bool potassiumAdequate = (digitalRead(K_BUTTON_PIN) == LOW);

  // --------------------------------------
  // DHT22 reading
  // In this simulation, humidity is used as soil moisture
  // Temperature is displayed only as supplementary information
  // --------------------------------------
  TempAndHumidity environmentalData = dhtSensor.getTempAndHumidity();

  if (isnan(environmentalData.temperature) || isnan(environmentalData.humidity)) {
    Serial.println("Error: Unable to read data from the DHT22 sensor.");
    delay(2000);
    return;
  }

  float simulatedSoilMoisture = environmentalData.humidity;
  float measuredTemperature = environmentalData.temperature;

  // --------------------------------------
  // LDR reading and pH simulation
  // --------------------------------------
  int ldrRawReading = analogRead(LDR_PIN);
  float simulatedPH = calculateSimulatedPH(ldrRawReading);

  // --------------------------------------
  // Decision conditions
  // --------------------------------------
  bool soilMoistureBelowMinimum = (simulatedSoilMoisture < SOIL_MOISTURE_MIN);
  bool soilMoistureAboveMaximum = (simulatedSoilMoisture > SOIL_MOISTURE_MAX);
  bool acceptablePH = isPHWithinAcceptableRange(simulatedPH);
  bool acceptableNutrientCondition = hasMinimumNutrientCondition(
    nitrogenAdequate,
    phosphorusAdequate,
    potassiumAdequate
  );

  // --------------------------------------
  // Serial monitor output
  // --------------------------------------
  Serial.println("\n============= SYSTEM MONITOR =============");
  Serial.print("Measured temperature: ");
  Serial.print(measuredTemperature);
  Serial.println(" °C");

  Serial.print("Simulated soil moisture: ");
  Serial.print(simulatedSoilMoisture);
  Serial.println(" %");

  Serial.print("Raw LDR reading: ");
  Serial.println(ldrRawReading);

  Serial.print("Simulated soil pH: ");
  Serial.println(simulatedPH, 2);

  printPHCondition(simulatedPH);

  Serial.print("Nitrogen (N): ");
  Serial.println(nitrogenAdequate ? "ADEQUATE" : "INADEQUATE");

  Serial.print("Phosphorus (P): ");
  Serial.println(phosphorusAdequate ? "ADEQUATE" : "INADEQUATE");

  Serial.print("Potassium (K): ");
  Serial.println(potassiumAdequate ? "ADEQUATE" : "INADEQUATE");

  // --------------------------------------
  // Irrigation control logic
  // --------------------------------------
  if (soilMoistureBelowMinimum) {
    if (acceptablePH) {
      if (acceptableNutrientCondition) {
        digitalWrite(RELAY_PIN, HIGH);
        Serial.println("System status: Irrigation activated.");
      } else {
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("System status: Irrigation blocked due to insufficient nutrient condition.");
      }
    } else {
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("System status: Irrigation blocked due to unacceptable pH range.");
    }
  } else if (soilMoistureAboveMaximum) {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("System status: Irrigation blocked because the soil is excessively moist.");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("System status: Irrigation not required because soil moisture is adequate.");
  }

  Serial.println("==========================================");

  delay(2000);
}
