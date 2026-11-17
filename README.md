# Lab 5-02a: Nhận Lệnh Điều Khiển LoRa Qua UART1 (Receive Command Native)

> **Phân hệ:** COM (Communication System)  
> **Thư viện yêu cầu:** `PTITCube Library v1.1.0`  
> **Nền tảng:** PlatformIO / ESP32-WROOM-32 (OBC)

---

## 📖 1. Mục Tiêu & Mô Tả Bài Thực Hành

Lắng nghe sóng LoRa qua Serial1 (UART1), nhận bản tin điều khiển từ trạm mặt đất, kiểm tra mã toàn vẹn và thực thi lệnh.

---

## 🔌 2. Sơ Đồ Chân Phần Cứng (Hardware Pinout chuẩn PTITCube.h)

| Tín hiệu LoRa | Chân ESP32 | Mô tả |
| :--- | :--- | :--- |
| LoRa RX | GPIO 25 (TX1) | ESP32 xuất dữ liệu sang module LoRa |
| LoRa TX | GPIO 26 (RX1) | ESP32 nhận dữ liệu từ module LoRa |
| LoRa AUX | GPIO 27 | Chân báo trạng thái bận/rảnh (Busy/Idle) |
| LoRa M0 | GPIO 32 | Chân cấu hình chế độ (M0=0: Normal) |
| LoRa M1 | GPIO 33 | Chân cấu hình chế độ (M1=0: Normal) |

---

## 🛠️ 3. Cấu Hình Phần Mềm & Thư Viện

- **Thư viện cốt lõi:** Thư mục `lib/PTITCube` tích hợp sẵn bộ thư viện phiên bản mới nhất `v1.1.0` với các phân hệ phân lớp:
  - `CDH`: Quản lý luồng xuất nhập dữ liệu `cdh` (Stream inheritance) và hệ thống tệp FAT32 trên thẻ nhớ MicroSD.
  - `EPS`: Quản lý năng lượng, đọc IC MAX17048 qua I2C.
  - `Sensor`: Đọc cụm cảm biến môi trường BMP280, cảm biến quán tính 6-DoF MPU6500, từ kế QMC5883L và định vị GNSS L76X.
  - `COM`: Quản lý module vô tuyến LoRa Ebyte E32 qua giao tiếp UART1.
- **Kênh giám sát Console:**
  - **Công cụ:** `cdh (UART0 console) + Serial1 (LoRa RF link)`
  - **Tốc độ Baud:** `115200 bps` (Console) / `9600 bps` (LoRa E32)
  - **Lưu ý chuẩn hóa:** Kể từ Lab 3, mọi luồng in debug console được chuẩn hóa qua đối tượng `cdh` (`PTIT_CDH cdh;`) kế thừa trực tiếp từ lớp `Stream`/`Print` của Arduino, thay thế hoàn toàn cho `Serial` thông thường.

---

## 🚀 4. Hướng Dẫn Biên Dịch & Nạp Firmware

Sử dụng **PlatformIO CLI** hoặc giao diện **VSCode / PlatformIO IDE**:

```bash
# 1. Di chuyển vào thư mục dự án
cd Lab5-02a_Receive_Command_UART

# 2. Biên dịch mã nguồn
pio run

# 3. Nạp firmware vào vi điều khiển vệ tinh
pio run -t upload

# 4. Mở cửa sổ giám sát Serial Monitor
pio device monitor -b 115200
```

---

## 📝 5. Lưu Ý Kỹ Thuật

- Lệnh điều khiển được mã hóa dạng chuỗi ASCII hoặc nhị phân chuẩn.
- Không chèn các lệnh in `println()` trang trí dư thừa làm nghẽn bộ đệm UART khi vệ tinh vận hành ở tần số cao.
- Kiểm tra kết nối cáp USB-UART và nguồn pin trước khi thực hiện nạp code.
