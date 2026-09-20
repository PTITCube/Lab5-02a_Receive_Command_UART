/**
 * VÍ DỤ 5-2a: NHẬN DỮ LIỆU TẦM XA TỪ LORA (UART THUẦN)
 */
#include <Arduino.h>

// Chân giao tiếp với module LoRa E32
#define LORA_RX 26
#define LORA_TX 27
#define LORA_M0 25
#define LORA_M1 35

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, LORA_RX, LORA_TX);
    
    // Cấu hình chân Mode (M0=0, M1=0: Chế độ hoạt động bình thường)
    pinMode(LORA_M0, OUTPUT);
    pinMode(LORA_M1, OUTPUT);
    digitalWrite(LORA_M0, LOW);
    digitalWrite(LORA_M1, LOW);

    Serial.println("\n[RAW] LoRa Receiver đang lắng nghe sóng vô tuyến...");
}

void loop() {
    // Kiểm tra xem có dữ liệu đến từ sóng không gian hay không
    if (Serial2.available() > 0) {
        String data = Serial2.readStringUntil('\n');
        Serial.print("[RX] Nhận được bản tin thô: ");
        Serial.println(data);
    }
}
