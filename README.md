# Ventilation Project

This project is designed for the **NXP LPCXpresso1549** board and implements a system to control a fan and monitor a pressure sensor. The system features an interactive menu navigable via buttons and allows for two operational modes:

## Features
- **LED & Button Interface**: Adjusts fan pressure settings.
- **Two Modes of Operation**:
  1. **Manual Mode** – Directly control the fan power.
  2. **Automatic Mode** – Set a target pressure (in bars), and the system calculates the required fan speed.
- **Pressure Sensor Handling**: Reads real-time pressure values.
- **Blinking LED Feedback**: Displays system status without affecting menu navigation.

## Hardware Requirements
- **Board**: NXP LPCXpresso1549
- **Components**:
  - Fan
  - Pressure Sensor
  - LEDs
  - Push Buttons

## Menu Controls
- **UP (B1)**: Move up in the menu / Increase values.
- **DOWN (B3)**: Move down in the menu / Decrease values.
- **OK (B2)**: Select menu item / Confirm action.
- **Timeout Handling**: If no button is pressed for 10 seconds, the system returns to the main menu.

## LED Behavior
- LED blinking is used to indicate system states.
- LED timing is controlled by:
  - **Time**: How long the LED stays ON (0-200ms, step 20ms)
  - **Blank**: How long the LED stays OFF (0-1s, step 0.1s)
  - **Light**: Selects which LED is controlled (0 = none, 1 = red, 2 = green, 3 = blue)

## Blinking & Menu Independence
The LED blinking process runs independently of the menu system to ensure uninterrupted navigation while the fan and pressure regulation operate smoothly.

## Getting Started
1. Clone the repository:
   ```sh
   git clone https://github.com/Biboulder/Ventilation_project.git
   ```
2. Build and flash the firmware onto the **NXP LPCXpresso1549** board.
3. Use the buttons to navigate and control the fan or pressure settings.

## License
This project follows the licensing terms defined in the repository.

