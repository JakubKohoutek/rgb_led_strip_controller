// RGB LED Strip Controller

const int redPin = 5;
const int greenPin = 6;
const int bluePin = 3;
const int potPin = A0;
const int buttonPin = A1;

int mode = 0;
const int numModes = 8;

// Variables for button reading
const unsigned long debounceMs = 40;
const unsigned long longPressMs = 600;
unsigned long lastChangeMs = 0;
bool lastStable = HIGH;
bool lastReading = HIGH;
bool pressArmed = true;

int previousPotValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(potPin, INPUT);
}

/** Utility function that will return true if the button
 *  is pressed exactly once. It doesn't care if/how long
 *  the button is held.
 */
bool buttonPressed() {
  bool reading = digitalRead(buttonPin);

  // Start (re)debounce window on any transition
  if (reading != lastReading) {
    lastChangeMs = millis();
    lastReading = reading;
  }

  // When stable long enough, accept new state
  if ((millis() - lastChangeMs) > debounceMs && reading != lastStable) {
    lastStable = reading;

    // Falling edge = button pressed (active-low)
    if (lastStable == LOW && pressArmed) {
      pressArmed = false;             // consume this press; ignore while held
      return true;                    // signal single press event
    }

    // Rising edge = button released; re-arm for next press
    if (lastStable == HIGH) {
      pressArmed = true;
    }
  }

  return false; // no new press event
}


void loop() {
  if (buttonPressed()) {
    Serial.println("Button pressed");
    mode = (mode + 1) % numModes;
  }

  int potValue = analogRead(potPin);
  if (abs(previousPotValue - potValue) > 4) {
    Serial.println(potValue);
    previousPotValue = potValue;
  }

  // Determine color combination
  bool r = false, g = false, b = false;
  switch (mode) {
    case 0: break;                                 // off
    case 1: r = true; break;                       // Red
    case 2: g = true; break;                       // Green
    case 3: b = true; break;                       // Blue
    case 4: r = g = true; break;                   // Yellow
    case 5: r = b = true; break;                   // Magenta
    case 6: g = b = true; break;                   // Cyan
    case 7: r = g = b = true; break;               // White
    default: break;
  }

  // Set PWM outputs
  analogWrite(redPin,   r ? map(potValue, 0, 1023, 0, 200) : 0);
  analogWrite(greenPin, g ? map(potValue, 0, 1023, 0, 100) : 0);
  analogWrite(bluePin,  b ? map(potValue, 0, 1023, 0, 255) : 0);
}