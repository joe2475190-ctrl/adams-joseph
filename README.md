# Joseph Woru Adams

Electrical/Electronics Engineering student in Nigeria, currently building hands-on experience with embedded systems, renewable energy circuits, and microcontroller programming as I work toward the power/energy sector.

## Projects

### Solar Charging Control System with Buzzer Alarm
A 5-state Arduino-based solar/battery monitoring system built and simulated in Wokwi.
- Reads simulated solar/battery voltage via a slide potentiometer on an analog input
- Displays live voltage and simulated output current on a 16x2 LCD
- Three-LED status indication (Full / Charging / Low), with an escalating buzzer alarm as charge drops (slow beep on Low, fast beep on Critical, long alarm on shutdown)
- Automatic power cutoff when charge is depleted, with automatic recovery once charge rises again
- Manual power switch and reset button for full system control
- Simulated inverter output stage indicating power delivery to a load
- **Files:** `solar-charging-control-with-buzzer.ino`

### Arduino Battery Voltage Indicator
A simpler standalone sketch reading analog voltage input and reflecting charge level through LED indicators.
- **Files:** `battery-voltage-indicator.ino`

### LED Blink Project
Foundational Arduino project practicing digital output control and timing with `millis()`/`delay()`.
- **Files:** `led-blink-project.ino`

### Coming Soon
- Solar-powered phone charger

## Technical Interests
- Embedded systems & microcontroller programming (Arduino, C/C++)
- Renewable energy systems — solar charge monitoring & power electronics
- Circuit design & simulation (Wokwi, Tinkered)
- Electrical/electronics engineering fundamentals
- Growing into PCB design and power systems engineering
