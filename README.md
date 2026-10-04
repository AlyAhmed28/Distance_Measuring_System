# Distance Measuring System

An embedded C project for an AVR microcontroller that measures distance with an ultrasonic sensor (HC-SR04 type) and shows the result in centimeters on a character LCD.

**Author:** Aly Ahmed
**Created:** March 2024

---

## Overview

The system triggers the ultrasonic sensor, measures the echo pulse width using the microcontroller's Input Capture Unit (ICU), converts it to a distance, and prints the value on an LCD in real time. The firmware is split into small, reusable drivers (GPIO, ICU, LCD, Ultrasonic) layered under a simple application in `source.c`.

## Features

- Real-time distance measurement in **cm**
- Timer-based pulse measurement using the **ICU** driver (no busy-wait on the echo pin)
- Clean LCD output that handles changing digit counts (e.g. `100` → `99`) without leftover characters
- Modular, layered driver architecture
- Proteus simulation included

## Hardware Requirements

| Component | Notes |
|-----------|-------|
| AVR microcontroller | e.g. ATmega32 *(update to your target)* |
| Ultrasonic sensor | HC-SR04 or compatible |
| Character LCD | 16x2, HD44780-compatible |
| Power supply / clock | *(add your clock frequency, e.g. 8 MHz)* |

### Pin Connections

> Fill these in to match your `ultrasonic.h` and `lcd.h` configuration.

| Peripheral | Signal | MCU Pin |
|------------|--------|---------|
| Ultrasonic | Trigger | `Pxn` |
| Ultrasonic | Echo | `PD6 (ICP1)` *(if using Timer1 ICU)* |
| LCD | RS / E | `Pxn` |
| LCD | Data (4-bit / 8-bit) | `Pxn` |

## Project Structure

```
Distance Measuring System/
├── Code/
│   └── Distance Measuring System/
│       ├── source.c          # Application entry point (main loop)
│       ├── ultrasonic.c/.h   # Ultrasonic sensor driver (trigger + distance calculation)
│       ├── icu.c/.h          # Input Capture Unit driver
│       ├── lcd.c/.h          # LCD driver
│       ├── gpio.c/.h         # GPIO driver
│       ├── common_macros.h   # Bit manipulation macros
│       └── std_types.h       # Standard type definitions
└── Simulation/               # Proteus simulation files
```

## How It Works

1. Global interrupts are enabled (`SREG |= (1<<7)`), required by the ICU.
2. `Ultrasonic_init()` and `LCD_init()` initialize the peripherals.
3. The LCD displays the static label `distance =`.
4. In an infinite loop:
   - `Ultrasonic_readDistance()` sends a trigger pulse and measures the echo time.
   - The result is written to the LCD at column 11 of the first row, followed by `Cm`.
   - For values below 100, an extra space is printed to erase the leftover digit from a previous 3-digit reading.

### Main Loop (simplified)

```c
ENABLE_INTERRUPTS();
Ultrasonic_init();
LCD_init();
LCD_displayString("distance =");

while (1)
{
    Ultrasonic_readDistance();

    LCD_moveCursor(0, 11);
    LCD_integerToString(distance);
    if (distance < 100)
        LCD_displayCharacter(' ');
    LCD_displayString("Cm");
}
```

## Getting Started

### Prerequisites

- An AVR toolchain (`avr-gcc`) with an Eclipse-based IDE (project files `.cproject` / `.project` included)
- Proteus (optional, for simulation)
- A programmer such as USBasp (for real hardware)

### Build

1. Clone the repository:
   ```bash
   git clone https://github.com/AlyAhmed28/Distance_Measuring_System.git
   ```
2. Import the project into your IDE (**File → Import → Existing Projects into Workspace**).
3. Set the target MCU and clock frequency (`F_CPU`) in the project settings.
4. Build the project to generate the `.hex` file in `Debug/`.

### Run

- **Simulation:** open the project in `Simulation/` with Proteus, load the generated `.hex` into the microcontroller, and run.
- **Hardware:** flash the `.hex` onto the MCU, wire the sensor and LCD as per the pin table above, and power the board.

## Possible Improvements

- Add an out-of-range / sensor-timeout message
- Add a buzzer or LED alert when an object is closer than a threshold
- Average multiple readings for a steadier display
- Support for unit switching (cm / inch)

## License

Add a license of your choice (e.g. MIT) here.
