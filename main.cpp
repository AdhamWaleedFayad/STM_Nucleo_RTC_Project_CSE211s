#include "mbed.h"



// Shift register pins
DigitalOut latchPin(D4);  // ST_CP
DigitalOut clockPin(D7);  // SH_CP
DigitalOut dataPin(D8);   // DS

// Buttons (active LOW)
DigitalIn s1(A1), s3(A3);

// Potentiometer for voltage measurement
AnalogIn potentiometer(A0);

volatile int seconds = 0, minutes = 0;
Ticker timerTicker;

// Common ANODE patterns (INVERTED from common cathode)
const uint8_t digitPattern[10] = {
    static_cast<uint8_t>(~0b00111111), // 0
    static_cast<uint8_t>(~0b00000110), // 1
    static_cast<uint8_t>(~0b01011011), // 2
    static_cast<uint8_t>(~0b01001111), // 3
    static_cast<uint8_t>(~0b01100110), // 4
    static_cast<uint8_t>(~0b01101101), // 5
    static_cast<uint8_t>(~0b01111101), // 6
    static_cast<uint8_t>(~0b00000111), // 7
    static_cast<uint8_t>(~0b01111111), // 8
    static_cast<uint8_t>(~0b01101111)  // 9
};

// Digit positions (left to right, 1=enable)
const uint8_t digitPos[4] = {
    0x01, 0x02, 0x04, 0x08
};

void updateTime()
/*


This Function updates time with minutes incrementing each 60 seconds while the minute segments can reach up to 99 before reseting as there is no hours 


*/
 {
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
        if (minutes > 99) minutes = 0;
    }
}

void shiftOutMSBFirst(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        dataPin = (value >> i) & 0x01;
        clockPin = 1;
        clockPin = 0;
    }
}

void writeToShiftRegister(uint8_t segments, uint8_t digit) {
    /*
    This function writes data to the shift register responsible for controlling the four seven segment
    */
    latchPin = 0;
    shiftOutMSBFirst(segments);
    shiftOutMSBFirst(digit);
    latchPin = 1;
}

void displayNumber(int number, bool showDecimalPoint = false, int decimalPosition = 1) {
    int digits[4] = {
        (number / 1000) % 10,
        (number / 100) % 10,
        (number / 10) % 10,
        number % 10
    };

    for (int i = 0; i < 4; i++) {
        uint8_t segments = digitPattern[digits[i]];

        // Enable decimal point if needed (bit 7 = dot)
        if (showDecimalPoint && i == decimalPosition) {
            segments &= 0b01111111;
        }

        writeToShiftRegister(segments, digitPos[i]);
        ThisThread::sleep_for(2ms);
    }
}

int main() {
    latchPin = 0;
    clockPin = 0;
    dataPin = 0;

    s1.mode(PullUp);
    s3.mode(PullUp);

    timerTicker.attach(&updateTime, 1s);

    while (1) {
        if (!s1) {
            seconds = minutes = 0;
            ThisThread::sleep_for(200ms); // Debounce
        }

        if (!s3) {
            float adc = potentiometer.read();       // 0.0 to 1.0
            float voltage = adc * 3.3f;             // scale to 0-3.3V
            int voltageValue = voltage * 1000;      // e.g. 2.75V -> 2750

    

            displayNumber(voltageValue, true, 0);   // decimal after first digit
        } else {
            int timeValue = minutes * 100 + seconds;
            displayNumber(timeValue, true, 1);      // decimal after 2nd digit
        }
    }
}
