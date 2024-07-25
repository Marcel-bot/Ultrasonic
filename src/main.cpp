#include<main.h>

bool received_confirmation = false;

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
  const uint16_t front_left = measure(FRONT_LEFT_ECHO, FRONT_LEFT_TRIG),
                 front_middle = measure(FRONT_MIDDLE_ECHO, FRONT_MIDDLE_TRIG),
                 front_right = measure(FRONT_RIGHT_ECHO, FRONT_RIGHT_TRIG),
                 back_left = 0,
                 back_middle = 0,
                 back_right = 0;
  

  Wire.write((front_left >> 8) & 0xFF);
  Wire.write(front_left & 0xFF);

  Wire.write((front_middle >> 8) & 0xFF);
  Wire.write(front_middle & 0xFF);

  Wire.write((front_right >> 8) & 0xFF);
  Wire.write(front_right & 0xFF);

  Wire.write((back_left >> 8) & 0xFF);
  Wire.write(back_left & 0xFF);

  Wire.write((back_middle >> 8) & 0xFF);
  Wire.write(back_middle & 0xFF);

  Wire.write((back_right >> 8) & 0xFF);
  Wire.write(back_right & 0xFF);
}

void send_up() {
  if (received_confirmation) {
    Wire.write(UP_MESSAGE);

    Wire.onRequest(on_request);
    Wire.onReceive(no_receive);
  }
}

void await_confirmation(const int size) {
  while (Wire.available()) {
    if (Wire.read() == UP_CHAR) {
      received_confirmation = true;
    }
  }
}

void setup() {
  pinMode(FRONT_LEFT_TRIG, OUTPUT);
  pinMode(FRONT_LEFT_ECHO, INPUT);

  pinMode(FRONT_MIDDLE_TRIG, OUTPUT);
  pinMode(FRONT_MIDDLE_ECHO, INPUT);

  pinMode(FRONT_RIGHT_TRIG, OUTPUT);
  pinMode(FRONT_RIGHT_ECHO, INPUT);

  Wire.begin(I2C_ADDRESS);

  Wire.onRequest(send_up);
  Wire.onReceive(await_confirmation);
}

void loop() {}
