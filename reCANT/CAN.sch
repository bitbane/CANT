EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 6
Title "reCANT"
Date "2021-08-12"
Rev "0.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CANT-rescue:GND-power #PWR?
U 1 1 611CDDC9
P 3650 4400
AR Path="/611CDDC9" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDDC9" Ref="#PWR035"  Part="1" 
F 0 "#PWR035" H 3650 4400 30  0001 C CNN
F 1 "GND" H 3650 4330 30  0001 C CNN
F 2 "" H 3650 4400 60  0000 C CNN
F 3 "" H 3650 4400 60  0000 C CNN
	1    3650 4400
	0    1    1    0   
$EndComp
$Comp
L CANT-rescue:GND-power #PWR?
U 1 1 611CDDCF
P 4950 3800
AR Path="/611CDDCF" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDDCF" Ref="#PWR038"  Part="1" 
F 0 "#PWR038" H 4950 3800 30  0001 C CNN
F 1 "GND" H 4950 3730 30  0001 C CNN
F 2 "" H 4950 3800 60  0000 C CNN
F 3 "" H 4950 3800 60  0000 C CNN
	1    4950 3800
	0    -1   -1   0   
$EndComp
$Comp
L CANT-rescue:R-pspice R?
U 1 1 611CDDD6
P 3000 6250
AR Path="/611CDDD6" Ref="R?"  Part="1" 
AR Path="/611BBF4E/611CDDD6" Ref="R9"  Part="1" 
F 0 "R9" V 3080 6250 40  0000 C CNN
F 1 "120" V 3007 6251 40  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2930 6250 30  0001 C CNN
F 3 "" H 3000 6250 30  0000 C CNN
F 4 "MCR03ERTF1200" H 3000 6250 60  0001 C CNN "MPN"
	1    3000 6250
	0    1    1    0   
$EndComp
$Comp
L CANT-rescue:GND-power #PWR?
U 1 1 611CDDDC
P 3300 4700
AR Path="/611CDDDC" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDDDC" Ref="#PWR034"  Part="1" 
F 0 "#PWR034" H 3300 4700 30  0001 C CNN
F 1 "GND" H 3300 4630 30  0001 C CNN
F 2 "" H 3300 4700 60  0000 C CNN
F 3 "" H 3300 4700 60  0000 C CNN
	1    3300 4700
	1    0    0    -1  
$EndComp
Text GLabel 1100 1300 0    50   Input ~ 0
CAN1_L
Text GLabel 1100 1400 0    50   Input ~ 0
CAN1_H
Text GLabel 4650 4300 2    50   Input ~ 0
CAN1_L
Text GLabel 4650 4100 2    50   Input ~ 0
CAN1_H
$Comp
L CANT-rescue:Jumper_NC_Dual-Device JP?
U 1 1 611CDDE6
P 3350 6500
AR Path="/611CDDE6" Ref="JP?"  Part="1" 
AR Path="/611BBF4E/611CDDE6" Ref="JP3"  Part="1" 
F 0 "JP3" H 3400 6400 50  0000 L CNN
F 1 "Jumper_NC_Dual" H 3350 6600 50  0000 C BNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3350 6500 50  0001 C CNN
F 3 "" H 3350 6500 50  0001 C CNN
	1    3350 6500
	0    1    -1   0   
$EndComp
NoConn ~ 3350 6750
Text GLabel 2700 6250 0    60   Input ~ 0
CAN1_H
Text GLabel 2700 6500 0    60   Input ~ 0
CAN1_L
Text Notes 700  900  0    197  ~ 39
Connectors
Text Notes 700  5850 0    197  ~ 39
Jumpers
Text Notes 750  3250 0    197  ~ 39
CAN Transceiver
Text Notes 2500 6900 0    39   ~ 0
Termination resistor selection
Wire Wire Line
	2700 6500 3250 6500
Wire Wire Line
	2700 6250 2750 6250
Wire Wire Line
	3350 6250 3250 6250
Text GLabel 9400 1300 0    50   Input ~ 0
CAN1_L
Text GLabel 9900 1300 2    50   Input ~ 0
CAN1_H
Text GLabel 9300 1450 0    50   Input ~ 0
CAN1_SHORT
$Comp
L CANT-rescue:74LVC1G66-74xGxx U?
U 1 1 611CDDF9
P 9650 1300
AR Path="/611CDDF9" Ref="U?"  Part="1" 
AR Path="/611BBF4E/611CDDF9" Ref="U7"  Part="1" 
F 0 "U7" H 9650 1616 50  0000 C CNN
F 1 "74LVC1G66" H 9650 1525 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-353_SC-70-5_Handsoldering" H 9650 1300 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 9650 1300 50  0001 C CNN
	1    9650 1300
	1    0    0    -1  
$EndComp
$Comp
L CANT-rescue:GND-power #PWR?
U 1 1 611CDDFF
P 9400 2100
AR Path="/611CDDFF" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDDFF" Ref="#PWR040"  Part="1" 
F 0 "#PWR040" H 9400 2100 30  0001 C CNN
F 1 "GND" H 9400 2030 30  0001 C CNN
F 2 "" H 9400 2100 60  0000 C CNN
F 3 "" H 9400 2100 60  0000 C CNN
	1    9400 2100
	1    0    0    -1  
$EndComp
$Comp
L CANT-rescue:R-pspice R?
U 1 1 611CDE06
P 9400 1850
AR Path="/611CDE06" Ref="R?"  Part="1" 
AR Path="/611BBF4E/611CDE06" Ref="R11"  Part="1" 
F 0 "R11" V 9480 1850 40  0000 C CNN
F 1 "4.7K" V 9407 1851 40  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9330 1850 30  0001 C CNN
F 3 "" H 9400 1850 30  0000 C CNN
F 4 "MCR03ERTF5100" H 9400 1850 60  0001 C CNN "MPN"
	1    9400 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 1450 9400 1450
Wire Wire Line
	9400 1600 9400 1450
Connection ~ 9400 1450
$Comp
L CANT-rescue:Screw_Terminal_01x04-Connector J?
U 1 1 611CDE0F
P 1300 1200
AR Path="/611CDE0F" Ref="J?"  Part="1" 
AR Path="/611BBF4E/611CDE0F" Ref="J3"  Part="1" 
F 0 "J3" H 1380 1192 50  0000 L CNN
F 1 "Screw_Terminal_01x04" H 1380 1101 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_PT-1,5-4-3.5-H_1x04_P3.50mm_Horizontal" H 1300 1200 50  0001 C CNN
F 3 "~" H 1300 1200 50  0001 C CNN
	1    1300 1200
	1    0    0    -1  
$EndComp
$Comp
L CANT-rescue:R-pspice R?
U 1 1 611CDE16
P 1500 6200
AR Path="/611CDE16" Ref="R?"  Part="1" 
AR Path="/611BBF4E/611CDE16" Ref="R8"  Part="1" 
F 0 "R8" V 1580 6200 40  0000 C CNN
F 1 "120" V 1507 6201 40  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1430 6200 30  0001 C CNN
F 3 "" H 1500 6200 30  0000 C CNN
F 4 "MCR03ERTF1200" H 1500 6200 60  0001 C CNN "MPN"
	1    1500 6200
	0    1    1    0   
$EndComp
$Comp
L CANT-rescue:Jumper_NC_Dual-Device JP?
U 1 1 611CDE1C
P 1850 6450
AR Path="/611CDE1C" Ref="JP?"  Part="1" 
AR Path="/611BBF4E/611CDE1C" Ref="JP2"  Part="1" 
F 0 "JP2" H 1900 6350 50  0000 L CNN
F 1 "Jumper_NC_Dual" H 1850 6550 50  0000 C BNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1850 6450 50  0001 C CNN
F 3 "" H 1850 6450 50  0001 C CNN
	1    1850 6450
	0    1    -1   0   
$EndComp
NoConn ~ 1850 6700
Text GLabel 1200 6200 0    60   Input ~ 0
CAN3_H
Text GLabel 1200 6450 0    60   Input ~ 0
CAN3_L
Text Notes 1000 6850 0    39   ~ 0
Termination resistor selection
Wire Wire Line
	1200 6450 1750 6450
Wire Wire Line
	1200 6200 1250 6200
Wire Wire Line
	1850 6200 1750 6200
$Comp
L CANT-rescue:VBUS-power #PWR?
U 1 1 611CDE29
P 4600 3800
AR Path="/611CDE29" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDE29" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 4600 3650 50  0001 C CNN
F 1 "VBUS" H 4615 3973 50  0000 C CNN
F 2 "" H 4600 3800 50  0001 C CNN
F 3 "" H 4600 3800 50  0001 C CNN
	1    4600 3800
	1    0    0    -1  
$EndComp
Text GLabel 2300 4050 2    50   Input ~ 0
CAN3_H
Text GLabel 2300 4250 2    50   Input ~ 0
CAN3_L
$Comp
L CANT-rescue:GND-power #PWR?
U 1 1 611CDE31
P 4150 4600
AR Path="/611CDE31" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDE31" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 4150 4600 30  0001 C CNN
F 1 "GND" H 4150 4530 30  0001 C CNN
F 2 "" H 4150 4600 60  0000 C CNN
F 3 "" H 4150 4600 60  0000 C CNN
	1    4150 4600
	1    0    0    -1  
$EndComp
$Comp
L CANT-rescue:MCP2558FD-xSN-Interface_CAN_LIN U?
U 1 1 611CDE37
P 4150 4200
AR Path="/611CDE37" Ref="U?"  Part="1" 
AR Path="/611BBF4E/611CDE37" Ref="U5"  Part="1" 
F 0 "U5" H 4150 4781 50  0000 C CNN
F 1 "MCP2558FD-xSN" H 4150 4690 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4150 3600 50  0001 C CNN
F 3 "https://ww1.microchip.com/downloads/en/DeviceDoc/20005533A.pdf" H 4150 4200 50  0001 C CNN
	1    4150 4200
	1    0    0    -1  
$EndComp
$Comp
L CANT-rescue:VCC-power #PWR?
U 1 1 611CDE3D
P 3300 4300
AR Path="/611CDE3D" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDE3D" Ref="#PWR033"  Part="1" 
F 0 "#PWR033" H 3300 4150 50  0001 C CNN
F 1 "VCC" H 3317 4473 50  0000 C CNN
F 2 "" H 3300 4300 50  0001 C CNN
F 3 "" H 3300 4300 50  0001 C CNN
	1    3300 4300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3300 4300 3650 4300
Text GLabel 1100 1200 0    50   Input ~ 0
CAN3_H
Text GLabel 1100 1100 0    50   Input ~ 0
CAN3_L
$Comp
L CANT-rescue:MCP2558FD-xSN-Interface_CAN_LIN U?
U 1 1 611CDE46
P 1800 4150
AR Path="/611CDE46" Ref="U?"  Part="1" 
AR Path="/611BBF4E/611CDE46" Ref="U4"  Part="1" 
F 0 "U4" H 1800 4731 50  0000 C CNN
F 1 "MCP2558FD-xSN" H 1800 4640 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 1800 3550 50  0001 C CNN
F 3 "https://ww1.microchip.com/downloads/en/DeviceDoc/20005533A.pdf" H 1800 4150 50  0001 C CNN
	1    1800 4150
	1    0    0    -1  
$EndComp
$Comp
L CANT-rescue:VCC-power #PWR?
U 1 1 611CDE4C
P 1050 4250
AR Path="/611CDE4C" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDE4C" Ref="#PWR027"  Part="1" 
F 0 "#PWR027" H 1050 4100 50  0001 C CNN
F 1 "VCC" H 1067 4423 50  0000 C CNN
F 2 "" H 1050 4250 50  0001 C CNN
F 3 "" H 1050 4250 50  0001 C CNN
	1    1050 4250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1050 4250 1300 4250
$Comp
L CANT-rescue:GND-power #PWR?
U 1 1 611CDE53
P 1300 4350
AR Path="/611CDE53" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDE53" Ref="#PWR029"  Part="1" 
F 0 "#PWR029" H 1300 4350 30  0001 C CNN
F 1 "GND" H 1300 4280 30  0001 C CNN
F 2 "" H 1300 4350 60  0000 C CNN
F 3 "" H 1300 4350 60  0000 C CNN
	1    1300 4350
	0    1    1    0   
$EndComp
$Comp
L CANT-rescue:GND-power #PWR?
U 1 1 611CDE59
P 1800 4550
AR Path="/611CDE59" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDE59" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 1800 4550 30  0001 C CNN
F 1 "GND" H 1800 4480 30  0001 C CNN
F 2 "" H 1800 4550 60  0000 C CNN
F 3 "" H 1800 4550 60  0000 C CNN
	1    1800 4550
	1    0    0    -1  
$EndComp
$Comp
L CANT-rescue:GND-power #PWR?
U 1 1 611CDE5F
P 1050 4650
AR Path="/611CDE5F" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDE5F" Ref="#PWR028"  Part="1" 
F 0 "#PWR028" H 1050 4650 30  0001 C CNN
F 1 "GND" H 1050 4580 30  0001 C CNN
F 2 "" H 1050 4650 60  0000 C CNN
F 3 "" H 1050 4650 60  0000 C CNN
	1    1050 4650
	1    0    0    -1  
$EndComp
$Comp
L CANT-rescue:VBUS-power #PWR?
U 1 1 611CDE65
P 2250 3750
AR Path="/611CDE65" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDE65" Ref="#PWR031"  Part="1" 
F 0 "#PWR031" H 2250 3600 50  0001 C CNN
F 1 "VBUS" H 2265 3923 50  0000 C CNN
F 2 "" H 2250 3750 50  0001 C CNN
F 3 "" H 2250 3750 50  0001 C CNN
	1    2250 3750
	1    0    0    -1  
$EndComp
$Comp
L CANT-rescue:GND-power #PWR?
U 1 1 611CDE6B
P 2650 3750
AR Path="/611CDE6B" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDE6B" Ref="#PWR032"  Part="1" 
F 0 "#PWR032" H 2650 3750 30  0001 C CNN
F 1 "GND" H 2650 3680 30  0001 C CNN
F 2 "" H 2650 3750 60  0000 C CNN
F 3 "" H 2650 3750 60  0000 C CNN
	1    2650 3750
	0    -1   -1   0   
$EndComp
Text GLabel 7500 1350 0    50   Input ~ 0
CAN3_L
Text GLabel 8000 1350 2    50   Input ~ 0
CAN3_H
Text GLabel 7400 1500 0    50   Input ~ 0
CAN3_SHORT
$Comp
L CANT-rescue:74LVC1G66-74xGxx U?
U 1 1 611CDE74
P 7750 1350
AR Path="/611CDE74" Ref="U?"  Part="1" 
AR Path="/611BBF4E/611CDE74" Ref="U6"  Part="1" 
F 0 "U6" H 7750 1666 50  0000 C CNN
F 1 "74LVC1G66" H 7750 1575 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-353_SC-70-5_Handsoldering" H 7750 1350 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 7750 1350 50  0001 C CNN
	1    7750 1350
	1    0    0    -1  
$EndComp
$Comp
L CANT-rescue:GND-power #PWR?
U 1 1 611CDE7A
P 7500 2150
AR Path="/611CDE7A" Ref="#PWR?"  Part="1" 
AR Path="/611BBF4E/611CDE7A" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 7500 2150 30  0001 C CNN
F 1 "GND" H 7500 2080 30  0001 C CNN
F 2 "" H 7500 2150 60  0000 C CNN
F 3 "" H 7500 2150 60  0000 C CNN
	1    7500 2150
	1    0    0    -1  
$EndComp
$Comp
L CANT-rescue:R-pspice R?
U 1 1 611CDE81
P 7500 1900
AR Path="/611CDE81" Ref="R?"  Part="1" 
AR Path="/611BBF4E/611CDE81" Ref="R10"  Part="1" 
F 0 "R10" V 7580 1900 40  0000 C CNN
F 1 "4.7K" V 7507 1901 40  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7430 1900 30  0001 C CNN
F 3 "" H 7500 1900 30  0000 C CNN
F 4 "MCR03ERTF5100" H 7500 1900 60  0001 C CNN "MPN"
	1    7500 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 1500 7500 1500
Wire Wire Line
	7500 1650 7500 1500
Connection ~ 7500 1500
Wire Wire Line
	4150 3800 4600 3800
Connection ~ 4600 3800
Wire Wire Line
	4600 3800 4750 3800
Wire Wire Line
	1050 4450 1050 4250
Connection ~ 1050 4250
Wire Wire Line
	3300 4500 3300 4300
Connection ~ 3300 4300
Wire Wire Line
	1800 3750 2250 3750
Wire Wire Line
	2450 3750 2250 3750
Connection ~ 2250 3750
Text GLabel 1300 3950 0    50   Input ~ 0
CAN3_TX
Text GLabel 1300 4050 0    50   Input ~ 0
CAN3_RX
Text GLabel 3650 4000 0    50   Input ~ 0
CAN1_TX
Text GLabel 3650 4100 0    50   Input ~ 0
CAN1_RX
Text Notes 6750 850  0    197  ~ 39
Switches
$Comp
L CANT-rescue:C_Small-Device C16
U 1 1 61334A14
P 1050 4550
F 0 "C16" H 1142 4596 50  0000 L CNN
F 1 "100nF" H 1142 4505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1050 4550 50  0001 C CNN
F 3 "~" H 1050 4550 50  0001 C CNN
	1    1050 4550
	1    0    0    -1  
$EndComp
$Comp
L CANT-rescue:C_Small-Device C17
U 1 1 613359EE
P 2550 3750
F 0 "C17" V 2321 3750 50  0000 C CNN
F 1 "100nF" V 2412 3750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2550 3750 50  0001 C CNN
F 3 "~" H 2550 3750 50  0001 C CNN
	1    2550 3750
	0    1    1    0   
$EndComp
$Comp
L CANT-rescue:C_Small-Device C19
U 1 1 613361C8
P 4850 3800
F 0 "C19" V 4621 3800 50  0000 C CNN
F 1 "100nF" V 4712 3800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4850 3800 50  0001 C CNN
F 3 "~" H 4850 3800 50  0001 C CNN
	1    4850 3800
	0    1    1    0   
$EndComp
$Comp
L CANT-rescue:C_Small-Device C18
U 1 1 61336920
P 3300 4600
F 0 "C18" H 3392 4646 50  0000 L CNN
F 1 "100nF" H 3392 4555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3300 4600 50  0001 C CNN
F 3 "~" H 3300 4600 50  0001 C CNN
	1    3300 4600
	1    0    0    -1  
$EndComp
$EndSCHEMATC
