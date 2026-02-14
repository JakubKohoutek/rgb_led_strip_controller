# RGB LED Strip Controller

An Arduino sketch that drives an RGB LED strip through 8 color modes using a button and a potentiometer.

## Hardware

| Component | Pin |
|---|---|
| Red channel | D5 (PWM) |
| Green channel | D6 (PWM) |
| Blue channel | D3 (PWM) |
| Potentiometer | A0 |
| Button | A1 (INPUT_PULLUP) |

## Color Modes

Cycle through modes by pressing the button:

| Mode | Color |
|---|---|
| 0 | Off |
| 1 | Red |
| 2 | Green |
| 3 | Blue |
| 4 | Yellow |
| 5 | Magenta |
| 6 | Cyan |
| 7 | White |

The potentiometer controls brightness across all active channels.

## Usage

1. Upload the sketch to your Arduino board.
2. Press the button to cycle through colors.
3. Turn the potentiometer to adjust brightness.
