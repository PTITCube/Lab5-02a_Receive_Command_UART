/**
 * VÍ DỤ 5-2a: NHẬN DỮ LIỆU TẦM XA TỪ LORA (UART THUẦN)
 * Các chân GPIO sử dụng trực tiếp từ định nghĩa chuẩn trong PTITCube.h
 */
#include <Arduino.h>
#include <PTITCube.h>

PTIT_CDH cdh;

void setup() {
    cdh.begin(115200);
    while (!cdh) { delay(10); }

    cdh.println("\n[VỆ TINH] Khởi tạo module LoRa chờ nhận lệnh...");
    
    // Cấu hình chân UART1 theo chuẩn phần cứng PTITCube.h
    Serial1.begin(9600, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);
    
    // Cấu hình chân Mode (M0=0, M1=0: Chế độ hoạt động bình thường)
    pinMode(LORA_M0_PIN, OUTPUT);
    pinMode(LORA_M1_PIN, OUTPUT);
    pinMode(LORA_AUX_PIN, INPUT);
    digitalWrite(LORA_M0_PIN, LOW);
    digitalWrite(LORA_M1_PIN, LOW);

    cdh.println("[VỆ TINH] Đang lắng nghe lệnh từ trạm mặt đất...");
}

void loop() {
    // Kiểm tra xem có dữ liệu đến từ sóng không gian hay không
    if (Serial1.available() > 0) {
        String data = Serial1.readStringUntil('\n');
        data.trim();
        cdh.print("[COM] Nhận được tin nhắn LoRa: ");
        cdh.println(data);
    }
}
