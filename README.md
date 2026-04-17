# Smart Irrigation System for Tomato Cultivation

## 1. Project Overview

This project simulates a smart irrigation system for **tomato cultivation** using an **ESP32** on the **Wokwi** platform.

The system monitors simulated soil conditions and automatically decides whether irrigation should be activated.

The solution uses:

- **3 push buttons** to simulate the nutrients **Nitrogen (N)**, **Phosphorus (P)**, and **Potassium (K)**
- **LDR sensor** to simulate **soil pH**
- **DHT22 sensor** to simulate **soil moisture**
- **Relay module** to represent the **water pump**

The irrigation system is activated only when soil moisture is below the defined minimum threshold, the simulated pH is within the acceptable range for tomato cultivation, and at least two of the three nutrients are in an adequate condition.

---

## 2. Selected Crop

**Tomato**

Tomato plants require controlled irrigation and appropriate soil conditions for healthy development. For this reason, the system was designed to activate irrigation only under specific conditions related to soil moisture, soil pH, and nutrient availability.

---

## 3. Components Used

- ESP32
- 3 Push Buttons
- LDR Sensor
- DHT22 Sensor
- Relay Module
- Resistor
- Wokwi simulation platform

---

## 4. Component Interpretation

### 4.1 Nutrient Buttons

The three buttons simulate the nutrient condition of the soil:

- **Green button** = Nitrogen (N)
- **Yellow button** = Phosphorus (P)
- **Red button** = Potassium (K)

Interpretation:
- **Pressed** = adequate nutrient
- **Not pressed** = inadequate nutrient

The soil is considered to have a minimum acceptable nutrient condition when **at least 2 out of the 3 nutrients** are adequate.

### 4.2 LDR as Simulated pH

The **LDR** is used to simulate **soil pH**. Its analog reading is converted into a scale from **0 to 14**, corresponding to the pH scale.

pH interpretation:
- **Below 5.8** = excessively acidic soil
- **Between 5.8 and 7.2** = acceptable range for tomato cultivation
- **Above 7.2** = excessively alkaline soil

The **ideal pH range** for tomato cultivation is between **6.2 and 6.8**, although the system accepts values from **5.8 to 7.2**.

### 4.3 DHT22 as Simulated Soil Moisture

The **DHT22** is used in this simulation to represent **soil moisture**.

Moisture interpretation:
- **Below 40%** = low moisture, dry soil, irrigation may be activated
- **Between 40% and 70%** = adequate moisture, irrigation not required
- **Above 70%** = excessive moisture, irrigation blocked

### 4.4 Relay Module

The **relay** represents the **irrigation pump**.

It is activated only when all required conditions are satisfied.

---

## 5. Irrigation Logic

The irrigation system is activated only when:

- soil moisture is **below 40%**
- simulated soil pH is **between 5.8 and 7.2**
- at least **2 of the 3 nutrients** are adequate

If any of these conditions is not satisfied, irrigation remains turned off.

---

## 6. System Pseudocode

Start

Read N, P, K  
Read simulated pH  
Read soil moisture

adequate nutrients = 0

If N is adequate, add 1  
If P is adequate, add 1  
If K is adequate, add 1

If soil moisture is below the minimum limit:
- If pH is between 5.8 and 7.2:
  - If at least 2 nutrients are adequate:
    - Turn relay ON
    - Status = "Irrigation activated"
  - Else:
    - Turn relay OFF
    - Status = "Blocked due to nutrient deficiency"
- Else:
  - Turn relay OFF
  - Status = "Blocked due to unacceptable pH"
Else:
- Turn relay OFF
- Status = "Soil moisture is sufficient"

Display status

End

---

## 7. Test Cases

| Test Case | Scenario | Expected Result |
|----------|----------|----------------|
| TC01 | Soil moisture below 40%, pH acceptable, 2 or 3 nutrients adequate | Relay ON |
| TC02 | Soil moisture below 40%, pH outside acceptable range | Relay OFF |
| TC03 | Soil moisture below 40%, fewer than 2 nutrients adequate | Relay OFF |
| TC04 | Soil moisture between 40% and 70% | Relay OFF |
| TC05 | Soil moisture above 70% | Relay OFF |

---

## 8. Wokwi Simulation

[Wokwi Project](https://wokwi.com/projects/461143183395151873)

---

## 9. Source Code

The ESP32 source code should be available in the repository in the file:

`src/sketch.ino`

---

## 10. Demonstration Video

[Demonstration Video](COLE_AQUI_O_LINK_DO_VIDEO)

---

## 11. Optional Extensions

This repository may also include optional files related to:

- Python integration with public API
- R-based statistical analysis

---

## 12. Repository Structure

- `README.md`
- `src/sketch.ino`
- `imagens/circuito-wokwi.png`
- `imagens/teste-irrigacao-acionada.png`
- `imagens/teste-ph-inadequado.png`
- `imagens/teste-deficiencia-nutricional.png`
- `imagens/teste-umidade-suficiente.png`
- `docs/logica-do-sistema.md`
- `docs/casos-de-teste.md`
- `opcionais/main.py`
- `opcionais/Tomate.R`

---

## 13. Group Members

- Lucas Carvalho Cordeiro
- Abner Henrique Dias Rosa Sanches
- Iago dos Santos Medeiros
- Breno Leardini
- Elton Dias

---

## 14. Final Considerations

This project demonstrates how IoT concepts can be applied to agriculture through simulation, combining environmental monitoring, decision logic, and automation to optimize irrigation control in tomato cultivation.
