# Smart Irrigation System for Tomato Cultivation

Smart irrigation simulation for **tomato cultivation** using an **ESP32** on
the **Wokwi** platform. The system reads simulated soil conditions and
automatically controls the water pump (relay).

---

## 1. Components

| Component      | Role in the simulation            |
|----------------|-----------------------------------|
| ESP32          | Microcontroller                   |
| DHT22          | Simulates **soil moisture (%)**   |
| LDR            | Simulates **soil pH (0–14)**      |
| 3 Push buttons | Simulate **N**, **P**, **K**      |
| Relay module   | Represents the **water pump**     |

---

## 2. Input Interpretation

### 2.1 Nutrient buttons (INPUT_PULLUP)

| Button state   | Digital read | Nutrient status |
|----------------|--------------|-----------------|
| Not pressed    | HIGH         | Adequate        |
| Pressed        | LOW          | Inadequate      |

- Green = Nitrogen (N), Yellow = Phosphorus (P), Red = Potassium (K)
- Nutrients are considered OK only when **all three** are adequate
  (`n && p && k`).

### 2.2 LDR as pH

The analog reading (0–4095) is linearly mapped to the pH scale (0–14):

`pH = (ldr_value * 14.0) / 4095`

Acceptable range for tomato: **5.8 ≤ pH ≤ 7.2**.

### 2.3 DHT22 as soil moisture

Soil is considered **dry** (irrigation allowed) when humidity is
**below 40%**. Any value ≥ 40% keeps irrigation off.

---

## 3. Irrigation Logic

The relay turns **ON** only when **all** three conditions are true:

1. Soil moisture < 40% (dry soil)
2. pH between 5.8 and 7.2
3. All three nutrients (N, P, K) adequate

If any condition fails, the relay stays **OFF** and the reason is printed
to the Serial Monitor.

---

## 4. Code Structure (`src/sketch.ino`)

| Function                 | Responsibility                                       |
|--------------------------|------------------------------------------------------|
| `tomato_npk_ok`          | Returns true if N, P and K are all adequate          |
| `tomato_ph_ok`           | Converts LDR reading to pH and checks range          |
| `tomato_humidity_ok`     | Returns true if humidity < 40% (soil needs water)    |
| `turn_irrigation_on`     | Drives the relay based on the three checks above     |
| `setup` / `loop`         | Sensor init and main sampling cycle (2 s interval)   |

Thresholds are defined as macros at the top of the file
(`TOMATO_HUMIDITY_MIN`, `TOMATO_PH_MIN`, `TOMATO_PH_MAX`).

---

## 5. Test Cases

| ID   | Scenario                                                   | Relay |
|------|------------------------------------------------------------|-------|
| TC01 | Humidity < 40%, pH in range, all N/P/K adequate            | ON    |
| TC02 | Humidity < 40%, pH out of range                            | OFF   |
| TC03 | Humidity < 40%, at least one nutrient inadequate           | OFF   |
| TC04 | Humidity ≥ 40%                                             | OFF   |

---

## 6. Wokwi Simulation

[Wokwi Project](https://wokwi.com/projects/461118638641414145)

---

## 7. Source Code

ESP32 sketch: [`src/sketch.ino`](src/sketch.ino)

---

## 8. Demonstration Video

[Demonstration Video](https://youtu.be/wGBh59Y1jwg)

---

## 9. Circuit Images and Test Evidence

All circuit screenshots and visual test evidence for this project are stored in the following folder:

[`docs/images/`](docs/images/)

This folder contains the Wokwi circuit image and the screenshots used to validate the main irrigation scenarios.

## 10. Group Members

- Lucas Carvalho Cordeiro
- Abner Henrique Dias Rosa Sanches
- Iago dos Santos Medeiros
- Breno Leardini
- Elton Dias
