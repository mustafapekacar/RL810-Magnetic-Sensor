# 40kHz Magnetic Field Proximity Sensor System

Detecting 40kHz magnetic fields using an RL810 coil with a 1.1V ADC reference, signal inversion, and digital filtering on an ATmega328P (Arduino Nano).

## 📌 Project Overview
This project focuses on the hardware and software implementation of an inductive proximity sensor. By generating a precise 40kHz magnetic field through a main wire and detecting it with an RL810 coil, the system can accurately estimate distance. It utilizes advanced signal processing techniques, including a hardware "Noise Gate" and software-based exponential moving average (EMA) filters, to achieve high sensitivity and eliminate EMI (Electromagnetic Interference).

## ⚙️ System Architecture & Schematic

Below is the complete block diagram of the transmitter and receiver systems:

```mermaid
graph TD
    %% Transmitter Section
    subgraph Transmitter_System [Transmitter System - 40kHz Generator]
        TX_MCU[Arduino Nano] -- Register PWM Pin 9 --> L298N[L298N Motor Driver]
        L298N -- Amplified 40kHz AC --> MainWire((Main Conductor Wire))
    end

    %% Receiver Section
    subgraph Receiver_System [Receiver System - Magnetic Proximity Sensor]
        MainWire -. Magnetic Field Induction .-> RL810[RL810 3-Pin Coil]
        
        RL810 -- Pin 1 --> IN_PLUS(LM386 Module: IN+)
        RL810 -- Pin 2 --> IN_MINUS(LM386 Module: IN-)
        
        IN_PLUS --- LM386_MOD[LM386 Audio Amplifier Module]
        IN_MINUS --- LM386_MOD
        
        LM386_MOD -- OUT+ --> SR5100[SR5100 Schottky Diode]
        
        SR5100 -- Rectified AC --> RC_Filter[Envelope Detector / RC Filter]
        RC_Filter -- 0-1.1V Sensitive DC Signal --> RX_MCU[Arduino Nano: Pin A0]
    end

    %% Power Connections (Hidden for clarity, but noted)
    classDef note fill:#f9f9f9,stroke:#333,stroke-width:1px;
    class Transmitter_System,Receiver_System note;
