/**
 * VÍ DỤ 5-2a: NHẬN DỮ LIỆU TẦM XA TỪ LORA (UART THUẦN)
 */
#include <Arduino.h>
#include <PTITCube.h>

PTIT_CDH cdh;
PTIT_EPS eps;

void setup() {
    cdh.begin(115200);

    // Kích hoạt hạ áp cấp nguồn ngoại vi trên PCB vệ tinh qua thư viện EPS
    eps.setBuckState(true);

    Serial1.begin(9600, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);

    pinMode(LORA_M0_PIN, OUTPUT);
    pinMode(LORA_M1_PIN, OUTPUT);
    pinMode(LORA_AUX_PIN, INPUT);
    digitalWrite(LORA_M0_PIN, LOW);
    digitalWrite(LORA_M1_PIN, LOW);

}

void loop() {
    if (Serial1.available() > 0) {
        String data = Serial1.readStringUntil('\n');
        data.trim();
        cdh.println("RX: " + data);
    }
}
