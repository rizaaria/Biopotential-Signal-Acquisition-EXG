
#include <BlynkSimpleSerialBLE.h>

#define BLYNK_PRINT Serial
#define EMG_PIN A0

// Auth Token dari proyek Blynk Anda (dapatkan dari email atau aplikasi Blynk)
char auth[] = "YourAuthToken";

// Timer untuk mengirim data
BlynkTimer timer;

// Sampling rate
#define SAMPLE_RATE 500

// Fungsi untuk filter EMG
float EMGFilter(float input) {
  float output = input;

  // Filter biquad section 1
  static float z1_1, z2_1;
  float x1 = output - 0.05159732 * z1_1 - 0.36347401 * z2_1;
  output = 0.01856301 * x1 + 0.03712602 * z1_1 + 0.01856301 * z2_1;
  z2_1 = z1_1;
  z1_1 = x1;

  // Filter biquad section 2
  static float z1_2, z2_2;
  float x2 = output - (-0.53945795) * z1_2 - 0.39764934 * z2_2;
  output = 1.00000000 * x2 + (-2.00000000) * z1_2 + 1.00000000 * z2_2;
  z2_2 = z1_2;
  z1_2 = x2;

  // Filter biquad section 3
  static float z1_3, z2_3;
  float x3 = output - 0.47319594 * z1_3 - 0.70744137 * z2_3;
  output = 1.00000000 * x3 + 2.00000000 * z1_3 + 1.00000000 * z2_3;
  z2_3 = z1_3;
  z1_3 = x3;

  // Filter biquad section 4
  static float z1_4, z2_4;
  float x4 = output - (-1.00211112) * z1_4 - 0.74520226 * z2_4;
  output = 1.00000000 * x4 + (-2.00000000) * z1_4 + 1.00000000 * z2_4;
  z2_4 = z1_4;
  z1_4 = x4;

  return output;
}

// Fungsi untuk membaca dan mengirim data EMG
void sendEMGData() {
  static unsigned long past = 0;
  unsigned long present = micros();
  unsigned long interval = present - past;

  // Jika waktu interval sesuai dengan sampling rate
  if (interval >= (1000000 / SAMPLE_RATE)) {
    past = present;

    // Membaca nilai dari BioAmp EXG Pill
    int rawValue = analogRead(EMG_PIN);

    // Filter sinyal EMG
    float filteredValue = EMGFilter(rawValue);

    // Kirim data ke Blynk melalui pin virtual V1
    Blynk.virtualWrite(V1, filteredValue);

    // Debugging (opsional)
    Serial.print("Raw: ");
    Serial.print(rawValue);
    Serial.print(" | Filtered: ");
    Serial.println(filteredValue);
  }
}

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(9600);

  // Menunggu koneksi Bluetooth
  Serial.println("Waiting for Bluetooth connection...");
  Blynk.begin(Serial, auth);

  // Set timer untuk mengirim data
  timer.setInterval(10L, sendEMGData);
}

void loop() {
  // Menjalankan koneksi Blynk
  Blynk.run();

  // Menjalankan timer untuk mengirim data
  timer.run();
}
