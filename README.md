# 🔌 Digital Ohm Meter (Arduino + OLED)

This project is a **Digital Ohm Meter** built using **Arduino Uno**, an **OLED Display**, and **known resistors** as reference values.  
It measures unknown resistor values by applying the **voltage divider principle** and displays the measured resistance on the OLED screen (and Serial Monitor).

---

## 📸 Overview

The Digital Ohm Meter allows you to:
- Measure resistance from **220 Ω up to 10 kΩ**
- View real-time readings on a **0.96" OLED Display**
- Calibrate easily by using a **known resistor**
- Extend range by changing the reference resistor

This project is ideal for **students and hobbyists** to understand analog measurements, voltage dividers, and ADC operations on Arduino.

---

## ⚙️ Components Required

| Component | Quantity | Description |
|------------|-----------|-------------|
| Arduino Uno | 1 | Main controller |
| OLED Display (0.96", I2C, SSD1306) | 1 | For displaying resistance values |
| Known Resistor | 1 | Used as reference resistor (e.g., 1.6 kΩ ±0.02%) |
| Unknown Resistor | 1 | The resistor to be measured |
| Jumper Wires | As needed | For connections |
| Breadboard | 1 | For circuit assembly |

---

## 🔌 Circuit Connections

### 🧠 Working Principle
The circuit works using the **voltage divider rule**:

![Equation](https://latex.codecogs.com/png.image?\dpi{120}V_{out}=V_{in}\times\frac{R_{unknown}}{R_{ref}+R_{unknown}})


By measuring `Vout` using the Arduino’s ADC, we can calculate `R_unknown`.

---

### 📈 Wiring Diagram (Text Representation)

| Component | Pin | Arduino Pin |
|------------|-----|-------------|
| OLED Display | VCC | 5V |
| OLED Display | GND | GND |
| OLED Display | SDA | A4 |
| OLED Display | SCL | A5 |
| Known Resistor (Rref) | One end | 5V |
| Known Resistor (Rref) | Other end | Node between Rref and Runknown |
| Unknown Resistor (Runknown) | One end | Node between Rref and Runknown |
| Unknown Resistor (Runknown) | Other end | GND |
| Node (between resistors) | - | A0 |

📘 **Node Connection**:  
The node between the two resistors connects to **A0**, where Arduino reads the voltage.

---

## 🧮 Calculation Formula

\[
R_{unknown} = R_{ref} \times \left(\frac{V_{out}}{V_{in} - V_{out}}\right)
\]

- `Vout` is measured using `analogRead(A0)`
- `Vin` = 5V (Arduino supply)
- `Rref` is known (e.g., 1600 Ω)

---

## 🧠 Code Explanation

1. **Read analog value** from A0.
2. **Convert** ADC reading to voltage:
   \[
   Vout = (analogValue \times 5.0) / 1023.0
   \]
3. **Apply formula** to find `Runknown`.
4. **Display results** on OLED and Serial Monitor.

---

## 🪛 Calibration Tips

- Use a **precise reference resistor** for better accuracy.
- Ensure **stable power supply** (5V regulated).
- Keep **short jumper wires** to reduce noise.
- You can modify code to display resistance in **Ω or kΩ automatically**.

---

## 🧰 Future Improvements

- Auto-range detection (for wider resistance values)
- Add buzzer or LEDs for range indication
- Add EEPROM storage for calibration data

---

## 📜 License

This project is open-source under the **MIT License** — feel free to use and modify it.

---

## ✨ Author

**Basem Elsharkawy**  
Embedded Systems & Arduino Developer  
[Mansoura University, Egypt]  
GitHub: [@basem-elsharkawy](https://github.com/basem-elsharkawy)
