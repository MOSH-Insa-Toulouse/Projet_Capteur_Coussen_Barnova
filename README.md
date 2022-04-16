# Projet_Capteur_Coussen_Barnova
 2021-2022
 Low-tech pencil drawn strain gauge sensor developed in 4th year Engineering Physics course MOSH (Microcontroller Open Source Hardware) at INSA (National Institute of Applied Sciences) Toulouse.

The project is inspired by Scientific Reports article "Pencil Drawn Strain Gauges and Chemiresistors on Paper" written by Cheng-Wei Lin, Zhibo Zhao, Jaemyung Kim & Jiaxing Huang. This article can be found in our repository.

The aim of this project is to fabricate a reliable strain gauge made of pencil drawn paper.

## Idea
Pencil carbon deposited on the paper contains percolated graphite particles network where electrons move. Mechanism enabling electrons to move from grain to grain is tunnelling through potential barrier. However, tunnelling depends exponentially on the length of the barrier. When a mechanical stress is applied to the gauge, grains of percolated network spread away. Thus, when a tension is applied to gauge electrons move less => resistance increases. When gauge is compressed electrons move more => resistance decreases.

## Hardware implementation
A photo of our sensor can be found in the repository.
![Sensor](/Sensor.jpeg)
With 5V voltage supply current in the sensor has an order of magnitude of a nanoampere. Ordinary multimeter is not able to detect such a small current. We use LTC1050 amplifier which enables to convert current into a voltage that can be measured thanks to Arduino Uno board.
We dimensioned amplifier circuit in order to filter 50 Hz noise and cut off high frequencies.
We designed and printed a printed circuit board corresponding to our circuit. 

## Software implementation
With a focus on customized Arduino board we've written Arduino programs to run OLED screen, rotatory encoder and Bluetooth module enabling to send mesasured data to a smartphone. Finally, we designed a simple app on MIT App Inventor that receives and plots the data. It can be found in "App" 
