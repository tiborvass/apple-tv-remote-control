# Apple TV Remote Control using Arduino

An Arduino-based remote control for your Apple TV (3. generation).

## Requirements
- Arduino UNO
- IR transmitter
- Breadboard
- Several jumper wires

## Build the circuit
- Connect the IR transmitter to GND, 5V and pin 3.

## Setup Arduino toolchain

I recommend installing [arduino-cli](https://github.com/arduino/arduino-cli#how-to-install) instead of the Arduino IDE which is too slow and buggy.

```
$ arduino-cli core install arduino:avr
$ arduino-cli lib install IRremote
$ arduino-cli board attach arduino:avr:uno
$ ARDUINO_PORT=$(arduino-cli board list | grep arduino:avr:uno | head -n 1 | awk '{print $1}')
$ ARDUINO_TTY=${ARDUINO_PORT/cu./tty.}
```

## Upload program to Arduino Uno

```
$ arduino-cli compile -u -p $ARDUINO_PORT
```

## Usage

Commands can be sent over USB, attaching via screen:

```
# screen $ARDUINO_TTY 9600       # To quit: Ctrl+A, Ctrl+K, Y
```

Keymapping:
- Arrows
- Enter or Space: OK / PLAY
- Delete: MENU

Make sure the IR diode is directed at the Apple TV.

## TODO

- Map Esc to MENU:
Implementation should detect delays between keys to determine if Esc (27) was hit on its own or if it is the beginning of an ANSI sequence.
