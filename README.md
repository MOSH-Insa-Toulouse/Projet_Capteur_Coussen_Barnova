# Projet_Capteur_Coussen_Barnova
 2021-2022
 Low-tech pencil drawn strain gauge sensor developed in 4th year Engineering Physics course MOSH (Microcontroller Open Source Hardware) at INSA (National Institute of Applied Sciences) Toulouse.

The project is inspired by Scientific Reports article "Pencil Drawn Strain Gauges and Chemiresistors on Paper" written by Cheng-Wei Lin, Zhibo Zhao, Jaemyung Kim & Jiaxing Huang. This article can be found in our repository.

The aim of this project is to fabricate a reliable strain gauge made of pencil drawn paper.

## Idea
Pencil carbon deposited on the paper is made of percolated graphite particles network where electrons move. Mechanism enabling electrons to move from grain to grain is tunnelling through potential barrier. However, tunnelling depends exponentially on the length of the barrier. When a mechanical stress is applied to the gauge, grains of percolated network spread away. Thus, when a tension is applied to gauge electrons move less => resistance increases. When gauge is compressed electrons move more => resistance decreases.

## Hardware implementation
A photo of our sensor can be found in the repository.

<img src="https://github.com/MOSH-Insa-Toulouse/Projet_Capteur_Coussen_Barnova/blob/main/Sensor.jpeg" width="130" height="210">

Supplying the sensor with 5V induces current in the sensor. However, this current has an order of magnitude of a nanoampere. Ordinary multimeter is not able to detect such a small current. We use LTC1050 amplifier which enables to convert current into a voltage that can be measured thanks to Arduino Uno board.
We dimensioned amplifier circuit in order to filter 50 Hz noise and cut off high frequencies. Further explanations are contained in Electronic_simulation_LTSpice document.
We designed this electrical circuit as a shield PCB (printed circuit board) using KiCad 6.0 software and printed it. KiCad files can be found in KiCad directory.

<img src="https://github.com/MOSH-Insa-Toulouse/Projet_Capteur_Coussen_Barnova/blob/main/Scheme_PCB.jpg?raw=true" width="410" height="260">

## Software implementation
With a focus on customized Arduino board we've written Arduino programs to run OLED screen, rotatory encoder and HC-O5 Bluetooth module enabling to send mesasured data to a smartphone. Finally, we designed a simple app on MIT App Inventor that receives and plots the data. It can be found in the directory "App".

## Tests and results

<img src="https://github.com/MOSH-Insa-Toulouse/Projet_Capteur_Coussen_Barnova/blob/main/Sensor_dimensions.jpg?raw=true" width="410" height="260">

Results can be found in the file Measures. We get linear slope of the calibration curve which confirms that resistance depends on strain. Even though, our sensor gives limited results, we measured how the resistance changes as a function of curvature and we are able to link it to applied strain. However, wires connection induced a lot of error because of lack of stability.

## Limits 
Firstly, PCB oxydized which lead to its malfunction. Most probably, certain pins were connected with the pins they were not supposed to which hindered correct supply and transit.
Furthermore, resistance depends clearly on amount of carbon deposited. This factor is quite difficult to evaluate and to control in our conditions.
Moreover, our measures are not repeatable because paper distorts when we measure relatively big strain. 
Finally, wire connections slip on the paper which alters the resistance. We would need a more reliable connection to get more solid results.

## Authors
Sarah Barnová : barnova@insa-toulouse.fr
Louise Coussen : coussen@insa-toulouse.fr
