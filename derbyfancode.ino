#include <Adafruit_SoftServo.h>

// -------------------- Pins & Speeds --------------------
#define SERVOPIN  0
#define LEDPIN    1
#define IRBEAMPIN 2

#define OFFSPEED       0
#define STAGEDSPEED    60
#define RACINGSPEED    180

#define MINIMUMSTAGEDDURATION 2000UL  // ms
#define MAXIMUMRACEDURATION    1500UL // ms

// ---- Debounce (adjust or set to 0 to disable) ----
#define IR_DEBOUNCE_MS 10UL

Adafruit_SoftServo esc;

enum RaceState { OFF, STAGED, RACING, DONE };
RaceState currentState = OFF;

volatile uint8_t counter = 0;  // for servo refresh ISR

unsigned long stagedTime = 0;
unsigned long racingTime = 0;

// Auto-detected baseline level when BEAM IS UNBROKEN at power-up
int idleLevel = HIGH;   // set in setup()

// Return true if beam is BLOCKED
bool beamIsBlockedRaw() {
  // Blocked is "not idle"
  return (digitalRead(IRBEAMPIN) != idleLevel);
}

// Simple debounce: returns a stable, debounced blocked value
bool beamIsBlocked() {
  bool first = beamIsBlockedRaw();
  if (IR_DEBOUNCE_MS == 0) return first;
  unsigned long t0 = millis();
  while (millis() - t0 < IR_DEBOUNCE_MS) {
    if (beamIsBlockedRaw() != first) {
      // restart debounce window if it changed
      first = beamIsBlockedRaw();
      t0 = millis();
    }
  }
  return first;
}

void setup() {
  // ESC
  pinMode(SERVOPIN, OUTPUT);
  esc.attach(SERVOPIN);

  // LED
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);

  // ---- IR input mode ----
  // If your sensor board already outputs a clean HIGH/LOW (has its own pull-up),
  // you can switch this to INPUT instead of INPUT_PULLUP.
  pinMode(IRBEAMPIN, INPUT_PULLUP);

  // Give sensor a moment to settle, assuming beam is UNBROKEN at power-up.
  delay(50);
  idleLevel = digitalRead(IRBEAMPIN);

  // Timer interrupt ~2ms for Adafruit_SoftServo refresh
  OCR0A = 0xAF;
  TIMSK |= _BV(OCIE0A);
}

void loop() {
  static bool lastBlocked = false;

  bool blocked = beamIsBlocked();
  unsigned long now = millis();

  // Edge detection (based on debounced value)
  bool risingEdge  = (blocked && !lastBlocked);  // just became BLOCKED
  bool fallingEdge = (!blocked && lastBlocked);  // just became UNBLOCKED
  lastBlocked = blocked;

  switch (currentState) {
    case OFF:
      if (risingEdge) {                // Enter STAGED when beam becomes blocked
        stagedTime = now;
        currentState = STAGED;
      }
      break;

    case STAGED:
      if (!blocked) {                  // Beam released
        unsigned long stagedDuration = now - stagedTime;
        if (stagedDuration >= MINIMUMSTAGEDDURATION) {
          racingTime = now;
          currentState = RACING;
        } else {
          currentState = OFF;          // Too short -> not a valid start
        }
      }
      break;

    case RACING:
      if ((now - racingTime) >= MAXIMUMRACEDURATION) {
        currentState = DONE;
      }
      break;

    case DONE:
      // stay here until power-cycle
      break;
  }

  // Outputs by state
  switch (currentState) {
    case STAGED:
      esc.write(STAGEDSPEED);
      digitalWrite(LEDPIN, HIGH);
      break;

    case RACING:
      esc.write(RACINGSPEED);
      digitalWrite(LEDPIN, HIGH);
      break;

    case OFF:
    case DONE:
    default:
      esc.write(OFFSPEED);
      digitalWrite(LEDPIN, LOW);
      break;
  }

  delay(1);
}

// Refresh the software servo every ~20ms
SIGNAL(TIMER0_COMPA_vect) {
  counter += 2;               // +2 ms
  if (counter >= 20) {        // ~20 ms
    counter = 0;
    esc.refresh();
  }
}
