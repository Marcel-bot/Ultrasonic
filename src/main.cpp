#include<main.h>

bool received_confirmation = false;

bool should_send = false;

uint8_t buffer[12];

uint32_t measure(const int echo, const int trig) {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    return pulseIn(echo, HIGH) * SOUND_SPEED / 2;
}

void no_receive(const int size) {}

void on_request() {
    Wire.write(buffer, 12);
}

void send_up() {
    if (received_confirmation) {
        Wire.write(UP_MESSAGE);

        Wire.onRequest(on_request);
        Wire.onReceive(no_receive);

        // Serial.println("Switched to prod handlers");
    }
}

void await_confirmation(const int size) {
    while (Wire.available()) {
        char c = Wire.read();

        // Serial.print("Reading: ");
        // Serial.print(c);
        // Serial.println("");

        if (c == UP_CHAR) {
            // Serial.println("Received confirmation");
            received_confirmation = true;
        }
    }
}

void setup() {
    // Serial.begin(115200);

    pinMode(FRONT_LEFT_TRIG, OUTPUT);
    pinMode(FRONT_LEFT_ECHO, INPUT);

    pinMode(FRONT_MIDDLE_TRIG, OUTPUT);
    pinMode(FRONT_MIDDLE_ECHO, INPUT);

    pinMode(FRONT_RIGHT_TRIG, OUTPUT);
    pinMode(FRONT_RIGHT_ECHO, INPUT);

    Wire.begin(I2C_ADDRESS);

    Wire.onRequest(send_up);
    Wire.onReceive(await_confirmation);

    while (!received_confirmation) {
        delay(10);
    }
}

void loop() {
    const uint16_t front_left = measure(FRONT_LEFT_ECHO, FRONT_LEFT_TRIG),
                   front_middle = measure(FRONT_MIDDLE_ECHO, FRONT_MIDDLE_TRIG),
                   front_right = measure(FRONT_RIGHT_ECHO, FRONT_RIGHT_TRIG),
                   back_left = 0,
                   back_middle = 0,
                   back_right = 0;
        

    buffer[0] = (front_left >> 8) & 0xFF;
    buffer[1] = front_left & 0xFF;

    buffer[2] = (front_middle >> 8) & 0xFF;
    buffer[3] = front_middle & 0xFF;

    buffer[4] = (front_right >> 8) & 0xFF;
    buffer[5] = front_right & 0xFF;

    buffer[6] = (back_left >> 8) & 0xFF;
    buffer[7] = back_left & 0xFF;

    buffer[8] = (back_middle >> 8) & 0xFF;
    buffer[9] = back_middle & 0xFF;

    buffer[10] = (back_right >> 8) & 0xFF;
    buffer[11] = back_right & 0xFF;

    delay(10);
}
