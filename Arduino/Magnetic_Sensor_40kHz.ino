/**
 * @file    Magnetic_Field_Sensor_40kHz.ino
 * @brief   40kHz Magnetic Field Proximity Sensor using RL810 Coil, LM386, and SR5100
 */

#define SENSOR_PIN A0

const float ALPHA_FILTER = 0.05; // Digital smoothing coefficient (EMA filter)
float filteredValue = 0.0;
float baseline = 0.0;

void setup() {
  Serial.begin(115200);
  
  // 1. HARDWARE HACK: Set ADC Reference to 1.1V for 5x sensitivity
  // WARNING: The voltage on the A0 pin must not exceed 1.1V in this mode.
  analogReference(INTERNAL);
  
  // 2. AUTO-TARE (Calibration)
  Serial.println("System starting... Please keep the coil AWAY from the wire.");
  delay(1000); // Wait for the LM386 and Schottky diode to stabilize
  
  long sum = 0;
  for(int i = 0; i < 100; i++) {
    sum += analogRead(SENSOR_PIN);
    delay(10);
  }
  baseline = sum / 100.0;
  filteredValue = baseline; // Initialize filter from the baseline
  
  Serial.print("Calibration Complete. Baseline (Noise Floor): ");
  Serial.println(baseline);
}

void loop() {
  // 3. OVERSAMPLING (Noise Reduction)
  long oversampleSum = 0;
  for(int i = 0; i < 64; i++) {
    oversampleSum += analogRead(SENSOR_PIN);
  }
  float currentAvg = oversampleSum / 64.0; // Average of 64 readings
  
  // 4. DIGITAL FILTERING
  filteredValue = (ALPHA_FILTER * currentAvg) + ((1.0 - ALPHA_FILTER) * filteredValue);
  
  // 5. SIGNAL INVERSION LOGIC
  // Since the LM386 output drops as the 40kHz AC signal increases,
  // we subtract the current value from the baseline to get a positive rising signal.
  float netSignal = baseline - filteredValue;
  
  // Clamp negative fluctuations to zero
  if (netSignal < 0) {
    netSignal = 0; 
  }
  
  // 6. SOFTWARE GAIN
  float displayValue = netSignal * 2.0; 
  
  // Print output for Serial Plotter
  Serial.print("Net_Signal_Strength:");
  Serial.println(displayValue);
  
  delay(10);
}
