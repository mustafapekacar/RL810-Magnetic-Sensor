# 40kHz Magnetic Field Proximity Sensor System

Detecting 40kHz magnetic fields using an RL810 coil with a 1.1V ADC reference, signal inversion, and digital filtering on an ATmega328P (Arduino Nano).

## 📌 Project Overview
This project focuses on the hardware and software implementation of an inductive proximity sensor. By generating a precise 40kHz magnetic field through a main wire and detecting it with an RL810 coil, the system can accurately estimate distance. It utilizes advanced signal processing techniques, including a hardware "Noise Gate" and software-based exponential moving average (EMA) filters, to achieve high sensitivity and eliminate EMI (Electromagnetic Interference).

## ⚙️ System Architecture & Schematic

Below is the complete block diagram of the transmitter and receiver systems:

```mermaid
graph TD
    %% Transmitter Section
    subgraph Verici_Sistem [Transmitter System - 40kHz Generator]
        TX_MCU[Arduino Nano] -- Register PWM Pin 9 --> L298N[L298N Motor Driver]
        L298N -- Güçlendirilmiş 40kHz AC --> AnaTel((Ana İletken Tel))
    end

    %% Receiver Section
    subgraph Alici_Sistem [Receiver System - Magnetic Proximity Sensor]
        AnaTel -. Manyetik Alan Endüksiyonu .-> RL810[RL810 3-Pin Bobin]
        
        RL810 -- Uç 1 --> IN_PLUS(LM386 Modül: IN+)
        RL810 -- Uç 2 --> IN_MINUS(LM386 Modül: IN-)
        
        IN_PLUS --- LM386_MOD[LM386 Audio Amplifier Module]
        IN_MINUS --- LM386_MOD
        
        LM386_MOD -- OUT+ --> SR5100[SR5100 Schottky Diyot]
        
        SR5100 -- Doğrultulmuş AC --> RC_Filter[Zarf Dedektörü / RC Filtre]
        RC_Filter -- 0-1.1V Hassas DC Sinyal --> RX_MCU[Arduino Nano: Pin A0]
    end

    classDef note fill:#f9f9f9,stroke:#333,stroke-width:1px;
    class Verici_Sistem,Alici_Sistem note;
