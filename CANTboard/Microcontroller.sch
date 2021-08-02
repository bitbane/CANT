EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 6
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 6300 6100 2    50   Input ~ 0
LED_ACT1
Text GLabel 6300 4200 2    50   Input ~ 0
LED_PWR1
Text GLabel 6300 4700 2    50   Input ~ 0
CAN1_SHORT
Text Label 4250 2300 0    60   ~ 0
NRST
Text GLabel 4500 2500 0    60   Input ~ 0
BOOT0
$Comp
L power:GND #PWR?
U 1 1 61181305
P 5900 800
AR Path="/61181305" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/61181305" Ref="#PWR021"  Part="1" 
F 0 "#PWR021" H 5900 550 50  0001 C CNN
F 1 "GND" V 5905 672 50  0000 R CNN
F 2 "" H 5900 800 50  0001 C CNN
F 3 "" H 5900 800 50  0001 C CNN
	1    5900 800 
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 6118130E
P 5600 1450
AR Path="/6118130E" Ref="C?"  Part="1" 
AR Path="/6115D60F/6118130E" Ref="C9"  Part="1" 
F 0 "C9" H 5692 1496 50  0000 L CNN
F 1 "100nF" H 5692 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5600 1450 50  0001 C CNN
F 3 "~" H 5600 1450 50  0001 C CNN
	1    5600 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 61181314
P 8300 1450
AR Path="/61181314" Ref="C?"  Part="1" 
AR Path="/6115D60F/61181314" Ref="C15"  Part="1" 
F 0 "C15" H 8392 1496 50  0000 L CNN
F 1 "1uF" H 8392 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8300 1450 50  0001 C CNN
F 3 "~" H 8300 1450 50  0001 C CNN
	1    8300 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61181321
P 4850 7550
AR Path="/61181321" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/61181321" Ref="#PWR020"  Part="1" 
F 0 "#PWR020" H 4850 7550 30  0001 C CNN
F 1 "GND" H 4850 7480 30  0001 C CNN
F 2 "" H 4850 7550 60  0000 C CNN
F 3 "" H 4850 7550 60  0000 C CNN
	1    4850 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 7550 5100 7550
Wire Wire Line
	5100 7550 5100 7500
Wire Wire Line
	5100 7550 5200 7550
Wire Wire Line
	5200 7550 5200 7500
Connection ~ 5100 7550
Wire Wire Line
	5200 7550 5300 7550
Wire Wire Line
	5300 7550 5300 7500
Connection ~ 5200 7550
Wire Wire Line
	5300 7550 5400 7550
Wire Wire Line
	5400 7550 5400 7500
Connection ~ 5300 7550
Wire Wire Line
	5400 7550 5500 7550
Wire Wire Line
	5500 7550 5500 7500
Connection ~ 5400 7550
Wire Wire Line
	5500 7550 5600 7550
Wire Wire Line
	5600 7550 5600 7500
Connection ~ 5500 7550
NoConn ~ 4500 4000
NoConn ~ 4500 4100
NoConn ~ 4500 4200
NoConn ~ 4500 4300
NoConn ~ 4500 4400
NoConn ~ 4500 4500
NoConn ~ 4500 4600
NoConn ~ 4500 4700
NoConn ~ 4500 6400
NoConn ~ 4500 6300
NoConn ~ 4500 6200
NoConn ~ 4500 6100
NoConn ~ 4500 6000
NoConn ~ 4500 5900
NoConn ~ 6300 7000
NoConn ~ 6300 6900
NoConn ~ 6300 6600
NoConn ~ 6300 6500
NoConn ~ 6300 6400
NoConn ~ 6300 6300
NoConn ~ 6300 5800
NoConn ~ 6300 5500
NoConn ~ 6300 5400
NoConn ~ 6300 3800
NoConn ~ 6300 3300
NoConn ~ 6300 3200
NoConn ~ 6300 3100
NoConn ~ 6300 3000
NoConn ~ 6300 2900
NoConn ~ 6300 2700
NoConn ~ 6300 2500
$Comp
L power:VCC #PWR?
U 1 1 61181369
P 4500 2900
AR Path="/61181369" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/61181369" Ref="#PWR019"  Part="1" 
F 0 "#PWR019" H 4500 2750 50  0001 C CNN
F 1 "VCC" H 4517 3073 50  0000 C CNN
F 2 "" H 4500 2900 50  0001 C CNN
F 3 "" H 4500 2900 50  0001 C CNN
	1    4500 2900
	0    -1   -1   0   
$EndComp
Text GLabel 6300 4600 2    50   Input ~ 0
CAN3_SHORT
Wire Wire Line
	4500 2700 4050 2700
Wire Wire Line
	4050 2700 4050 2600
Wire Wire Line
	4500 2800 4050 2800
Wire Wire Line
	4050 2800 4050 3000
$Comp
L Device:C C?
U 1 1 6118137A
P 3900 3000
AR Path="/6118137A" Ref="C?"  Part="1" 
AR Path="/6115D60F/6118137A" Ref="C5"  Part="1" 
F 0 "C5" V 3648 3000 50  0000 C CNN
F 1 "2.2uF" V 3739 3000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3938 2850 50  0001 C CNN
F 3 "~" H 3900 3000 50  0001 C CNN
	1    3900 3000
	0    1    1    0   
$EndComp
Text GLabel 6300 6200 2    50   Input ~ 0
LED_ACT2
NoConn ~ 6300 4300
$Comp
L Device:C C?
U 1 1 61181382
P 3900 2600
AR Path="/61181382" Ref="C?"  Part="1" 
AR Path="/6115D60F/61181382" Ref="C4"  Part="1" 
F 0 "C4" V 3648 2600 50  0000 C CNN
F 1 "2.2uF" V 3739 2600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3938 2450 50  0001 C CNN
F 3 "~" H 3900 2600 50  0001 C CNN
	1    3900 2600
	0    1    1    0   
$EndComp
NoConn ~ 6300 7100
NoConn ~ 6300 7200
$Comp
L Device:C_Small C?
U 1 1 6118138A
P 4200 2050
AR Path="/6118138A" Ref="C?"  Part="1" 
AR Path="/6115D60F/6118138A" Ref="C6"  Part="1" 
F 0 "C6" H 4292 2096 50  0000 L CNN
F 1 "100nF" H 4292 2005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4200 2050 50  0001 C CNN
F 3 "~" H 4200 2050 50  0001 C CNN
	1    4200 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 2300 4200 2150
$Comp
L Switch:SW_SPST SW?
U 1 1 61181391
P 3950 1800
AR Path="/61181391" Ref="SW?"  Part="1" 
AR Path="/6115D60F/61181391" Ref="SW1"  Part="1" 
F 0 "SW1" V 3904 1898 50  0000 L CNN
F 1 "SW_SPST" V 3995 1898 50  0000 L CNN
F 2 "Button_Switch_SMD:SW_SPST_PTS645" H 3950 1800 50  0001 C CNN
F 3 "~" H 3950 1800 50  0001 C CNN
	1    3950 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	4200 2300 3950 2300
Wire Wire Line
	3950 2300 3950 2000
Connection ~ 4200 2300
$Comp
L Device:R R?
U 1 1 6118139A
P 3600 2050
AR Path="/6118139A" Ref="R?"  Part="1" 
AR Path="/6115D60F/6118139A" Ref="R6"  Part="1" 
F 0 "R6" H 3670 2096 50  0000 L CNN
F 1 "100K" H 3670 2005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3530 2050 50  0001 C CNN
F 3 "~" H 3600 2050 50  0001 C CNN
	1    3600 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 2300 3600 2300
Connection ~ 3950 2300
$Comp
L power:VCC #PWR?
U 1 1 611813A2
P 3600 1900
AR Path="/611813A2" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/611813A2" Ref="#PWR014"  Part="1" 
F 0 "#PWR014" H 3600 1750 50  0001 C CNN
F 1 "VCC" H 3615 2073 50  0000 C CNN
F 2 "" H 3600 1900 50  0001 C CNN
F 3 "" H 3600 1900 50  0001 C CNN
	1    3600 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 2200 3600 2300
Text GLabel 6300 4800 2    50   Input ~ 0
CAN1_RX
Text GLabel 6300 4900 2    50   Input ~ 0
CAN1_TX
NoConn ~ 4500 5700
NoConn ~ 4500 5800
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J?
U 1 1 611813B1
P 4100 5200
AR Path="/611813B1" Ref="J?"  Part="1" 
AR Path="/6115D60F/611813B1" Ref="J2"  Part="1" 
F 0 "J2" H 4150 4575 50  0000 C CNN
F 1 "Conn_02x08_Odd_Even" H 4150 4666 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x08_P2.54mm_Vertical" H 4100 5200 50  0001 C CNN
F 3 "~" H 4100 5200 50  0001 C CNN
	1    4100 5200
	-1   0    0    1   
$EndComp
Wire Wire Line
	4300 4800 4500 4800
Wire Wire Line
	4500 4900 4300 4900
Wire Wire Line
	4300 5000 4500 5000
Wire Wire Line
	4500 5100 4300 5100
Wire Wire Line
	4300 5200 4500 5200
Wire Wire Line
	4500 5300 4300 5300
Wire Wire Line
	4300 5400 4500 5400
Wire Wire Line
	4500 5500 4300 5500
$Comp
L power:VCC #PWR?
U 1 1 611813BF
P 3800 5500
AR Path="/611813BF" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/611813BF" Ref="#PWR017"  Part="1" 
F 0 "#PWR017" H 3800 5350 50  0001 C CNN
F 1 "VCC" H 3815 5673 50  0000 C CNN
F 2 "" H 3800 5500 50  0001 C CNN
F 3 "" H 3800 5500 50  0001 C CNN
	1    3800 5500
	-1   0    0    1   
$EndComp
Wire Wire Line
	4200 2300 4500 2300
Wire Wire Line
	4500 2300 4550 2300
Connection ~ 4500 2300
$Comp
L MCU_ST_STM32H7:STM32H743VITx U?
U 1 1 611813C9
P 5400 4700
AR Path="/611813C9" Ref="U?"  Part="1" 
AR Path="/6115D60F/611813C9" Ref="U3"  Part="1" 
F 0 "U3" H 5400 1811 50  0000 C CNN
F 1 "STM32H743VITx" H 5400 1720 50  0000 C CNN
F 2 "Package_QFP:LQFP-100_14x14mm_P0.5mm" H 4700 2100 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00387108.pdf" H 5400 4700 50  0001 C CNN
	1    5400 4700
	1    0    0    -1  
$EndComp
NoConn ~ 4500 7200
NoConn ~ 4500 7100
NoConn ~ 4500 6800
NoConn ~ 4500 6700
NoConn ~ 4500 6600
NoConn ~ 4500 6500
Wire Wire Line
	3800 4800 3800 4900
Wire Wire Line
	3800 5400 3800 5500
Connection ~ 3800 5500
Wire Wire Line
	3800 5400 3800 5300
Connection ~ 3800 5400
Connection ~ 3800 4900
Connection ~ 3800 5000
Wire Wire Line
	3800 5000 3800 4900
Connection ~ 3800 5100
Wire Wire Line
	3800 5100 3800 5000
Connection ~ 3800 5200
Wire Wire Line
	3800 5200 3800 5100
Connection ~ 3800 5300
Wire Wire Line
	3800 5300 3800 5200
Wire Wire Line
	4200 1950 4200 1600
Wire Wire Line
	4200 1600 3950 1600
Connection ~ 4200 1950
Text GLabel 6300 6700 2    50   Input ~ 0
J1708_TX
Text GLabel 6300 6800 2    50   Input ~ 0
J1708_RX
NoConn ~ 3600 2050
NoConn ~ 4500 3700
NoConn ~ 4500 3800
NoConn ~ 6300 3500
NoConn ~ 6300 3400
$Comp
L Regulator_Linear:LD1117S33TR_SOT223 U?
U 1 1 611A4AFA
P 1450 3350
AR Path="/611A4AFA" Ref="U?"  Part="1" 
AR Path="/6115D60F/611A4AFA" Ref="U2"  Part="1" 
F 0 "U2" H 1450 3600 50  0000 C CNN
F 1 "LD1117S33TR" H 1450 3550 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 1450 3450 50  0001 C CNN
F 3 "" H 1450 3350 50  0001 C CNN
	1    1450 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 611A4B00
P 1450 3650
AR Path="/611A4B00" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/611A4B00" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 1450 3400 50  0001 C CNN
F 1 "GND" H 1450 3500 50  0000 C CNN
F 2 "" H 1450 3650 50  0001 C CNN
F 3 "" H 1450 3650 50  0001 C CNN
	1    1450 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 611A4B0C
P 2050 3850
AR Path="/611A4B0C" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/611A4B0C" Ref="#PWR013"  Part="1" 
F 0 "#PWR013" H 2050 3600 50  0001 C CNN
F 1 "GND" H 2055 3677 50  0000 C CNN
F 2 "" H 2050 3850 50  0001 C CNN
F 3 "" H 2050 3850 50  0001 C CNN
	1    2050 3850
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 611A4B12
P 2050 3350
AR Path="/611A4B12" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/611A4B12" Ref="#PWR012"  Part="1" 
F 0 "#PWR012" H 2050 3200 50  0001 C CNN
F 1 "VCC" H 2067 3523 50  0000 C CNN
F 2 "" H 2050 3350 50  0001 C CNN
F 3 "" H 2050 3350 50  0001 C CNN
	1    2050 3350
	1    0    0    -1  
$EndComp
$Comp
L power:VBUS #PWR?
U 1 1 611A4B2A
P 900 3350
AR Path="/611A4B2A" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/611A4B2A" Ref="#PWR09"  Part="1" 
F 0 "#PWR09" H 900 3200 50  0001 C CNN
F 1 "VBUS" H 915 3523 50  0000 C CNN
F 2 "" H 900 3350 50  0001 C CNN
F 3 "" H 900 3350 50  0001 C CNN
	1    900  3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 3450 2050 3350
Wire Wire Line
	1150 3350 900  3350
Wire Wire Line
	900  3350 900  3450
Connection ~ 900  3350
$Comp
L Device:C_Small C?
U 1 1 611A4B6F
P 5150 1450
AR Path="/611A4B6F" Ref="C?"  Part="1" 
AR Path="/6115D60F/611A4B6F" Ref="C8"  Part="1" 
F 0 "C8" H 5242 1496 50  0000 L CNN
F 1 "100nF" H 5242 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5150 1450 50  0001 C CNN
F 3 "~" H 5150 1450 50  0001 C CNN
	1    5150 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 611A4B75
P 4700 1450
AR Path="/611A4B75" Ref="C?"  Part="1" 
AR Path="/6115D60F/611A4B75" Ref="C7"  Part="1" 
F 0 "C7" H 4792 1496 50  0000 L CNN
F 1 "100nF" H 4792 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4700 1450 50  0001 C CNN
F 3 "~" H 4700 1450 50  0001 C CNN
	1    4700 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 611A4B7B
P 6950 1450
AR Path="/611A4B7B" Ref="C?"  Part="1" 
AR Path="/6115D60F/611A4B7B" Ref="C12"  Part="1" 
F 0 "C12" H 7042 1496 50  0000 L CNN
F 1 "100nF" H 7042 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6950 1450 50  0001 C CNN
F 3 "~" H 6950 1450 50  0001 C CNN
	1    6950 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 611A4B81
P 7400 1450
AR Path="/611A4B81" Ref="C?"  Part="1" 
AR Path="/6115D60F/611A4B81" Ref="C13"  Part="1" 
F 0 "C13" H 7492 1496 50  0000 L CNN
F 1 "100nF" H 7492 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7400 1450 50  0001 C CNN
F 3 "~" H 7400 1450 50  0001 C CNN
	1    7400 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 611A4B87
P 6050 1450
AR Path="/611A4B87" Ref="C?"  Part="1" 
AR Path="/6115D60F/611A4B87" Ref="C10"  Part="1" 
F 0 "C10" H 6142 1496 50  0000 L CNN
F 1 "100nF" H 6142 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6050 1450 50  0001 C CNN
F 3 "~" H 6050 1450 50  0001 C CNN
	1    6050 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 611A4B8D
P 7850 1450
AR Path="/611A4B8D" Ref="C?"  Part="1" 
AR Path="/6115D60F/611A4B8D" Ref="C14"  Part="1" 
F 0 "C14" H 7942 1496 50  0000 L CNN
F 1 "100nF" H 7942 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7850 1450 50  0001 C CNN
F 3 "~" H 7850 1450 50  0001 C CNN
	1    7850 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 611A4B93
P 6500 1450
AR Path="/611A4B93" Ref="C?"  Part="1" 
AR Path="/6115D60F/611A4B93" Ref="C11"  Part="1" 
F 0 "C11" H 6592 1496 50  0000 L CNN
F 1 "4.7uF" H 6592 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6500 1450 50  0001 C CNN
F 3 "~" H 6500 1450 50  0001 C CNN
	1    6500 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 611A4B9F
P 900 3850
AR Path="/611A4B9F" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/611A4B9F" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 900 3600 50  0001 C CNN
F 1 "GND" H 900 3700 50  0000 C CNN
F 2 "" H 900 3850 50  0001 C CNN
F 3 "" H 900 3850 50  0001 C CNN
	1    900  3850
	1    0    0    -1  
$EndComp
Text GLabel 6300 3600 2    50   Input ~ 0
SWDIO
Text GLabel 6300 3700 2    50   Input ~ 0
SWCLK
$Comp
L power:GND #PWR?
U 1 1 611B93DD
P 9100 3400
AR Path="/611B93DD" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/611B93DD" Ref="#PWR023"  Part="1" 
F 0 "#PWR023" H 9100 3400 30  0001 C CNN
F 1 "GND" H 9100 3330 30  0001 C CNN
F 2 "" H 9100 3400 60  0000 C CNN
F 3 "" H 9100 3400 60  0000 C CNN
	1    9100 3400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x05 P?
U 1 1 611B93E3
P 9700 3250
AR Path="/611B93E3" Ref="P?"  Part="1" 
AR Path="/6115D60F/611B93E3" Ref="P1"  Part="1" 
F 0 "P1" H 9700 3550 50  0000 C CNN
F 1 "SWD" V 9800 3250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 9700 3250 60  0001 C CNN
F 3 "" H 9700 3250 60  0000 C CNN
	1    9700 3250
	1    0    0    -1  
$EndComp
Text Label 9200 3450 0    60   ~ 0
NRST
Wire Wire Line
	9200 3450 9500 3450
Wire Wire Line
	9100 3250 9500 3250
Wire Wire Line
	9100 3250 9100 3400
Wire Wire Line
	9350 3050 9350 2950
Wire Wire Line
	9500 3050 9350 3050
$Comp
L power:VCC #PWR?
U 1 1 611B93F1
P 9350 2950
AR Path="/611B93F1" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/611B93F1" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 9350 2800 50  0001 C CNN
F 1 "VCC" H 9367 3123 50  0000 C CNN
F 2 "" H 9350 2950 50  0001 C CNN
F 3 "" H 9350 2950 50  0001 C CNN
	1    9350 2950
	1    0    0    -1  
$EndComp
Text GLabel 9500 3350 0    50   Input ~ 0
SWDIO
Text GLabel 9500 3150 0    50   Input ~ 0
SWCLK
$Comp
L pspice:R R?
U 1 1 611C049A
P 9450 1350
AR Path="/611C049A" Ref="R?"  Part="1" 
AR Path="/6115D60F/611C049A" Ref="R7"  Part="1" 
F 0 "R7" V 9530 1350 40  0000 C CNN
F 1 "10k" V 9457 1351 40  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9380 1350 30  0001 C CNN
F 3 "" H 9450 1350 30  0000 C CNN
F 4 "MCR03ERTF5100" H 9450 1350 60  0001 C CNN "MPN"
	1    9450 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper_NC_Dual JP?
U 1 1 611C04A0
P 9950 1100
AR Path="/611C04A0" Ref="JP?"  Part="1" 
AR Path="/6115D60F/611C04A0" Ref="JP1"  Part="1" 
F 0 "JP1" H 10000 1000 50  0000 L CNN
F 1 "Jumper_NC_Dual" H 9950 1200 50  0000 C BNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 9950 1100 50  0001 C CNN
F 3 "" H 9950 1100 50  0001 C CNN
	1    9950 1100
	0    1    -1   0   
$EndComp
Text GLabel 9300 1100 0    60   Input ~ 0
BOOT0
$Comp
L power:GND #PWR?
U 1 1 611C04A7
P 9450 1600
AR Path="/611C04A7" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/611C04A7" Ref="#PWR025"  Part="1" 
F 0 "#PWR025" H 9450 1350 50  0001 C CNN
F 1 "GND" H 9450 1450 50  0000 C CNN
F 2 "" H 9450 1600 50  0001 C CNN
F 3 "" H 9450 1600 50  0001 C CNN
	1    9450 1600
	1    0    0    -1  
$EndComp
NoConn ~ 9950 1350
Text Notes 9550 1550 0    39   ~ 0
Boot selection
Wire Wire Line
	9300 1100 9450 1100
$Comp
L power:VCC #PWR?
U 1 1 611C04B0
P 9950 850
AR Path="/611C04B0" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/611C04B0" Ref="#PWR026"  Part="1" 
F 0 "#PWR026" H 9950 700 50  0001 C CNN
F 1 "VCC" H 9967 1023 50  0000 C CNN
F 2 "" H 9950 850 50  0001 C CNN
F 3 "" H 9950 850 50  0001 C CNN
	1    9950 850 
	1    0    0    -1  
$EndComp
Connection ~ 9450 1100
Wire Wire Line
	9450 1100 9850 1100
Connection ~ 5900 800 
$Comp
L power:VCC #PWR?
U 1 1 6121FA02
P 5900 1950
AR Path="/6121FA02" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/6121FA02" Ref="#PWR022"  Part="1" 
F 0 "#PWR022" H 5900 1800 50  0001 C CNN
F 1 "VCC" H 5917 2123 50  0000 C CNN
F 2 "" H 5900 1950 50  0001 C CNN
F 3 "" H 5900 1950 50  0001 C CNN
	1    5900 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 800  5150 800 
Wire Wire Line
	5100 1800 4700 1800
Wire Wire Line
	4700 1800 4700 1550
Wire Wire Line
	4700 1350 4700 800 
Wire Wire Line
	5200 1550 5150 1550
Wire Wire Line
	5300 2000 5300 1950
Wire Wire Line
	8300 1350 8300 800 
Wire Wire Line
	5900 800  6050 800 
Wire Wire Line
	7850 1350 7850 800 
Connection ~ 7850 800 
Wire Wire Line
	7850 800  8300 800 
Wire Wire Line
	7400 1350 7400 800 
Connection ~ 7400 800 
Wire Wire Line
	7400 800  7850 800 
Wire Wire Line
	6950 1350 6950 800 
Connection ~ 6950 800 
Wire Wire Line
	6950 800  7400 800 
Wire Wire Line
	6500 1350 6500 800 
Connection ~ 6500 800 
Wire Wire Line
	6500 800  6950 800 
Wire Wire Line
	6050 1350 6050 800 
Connection ~ 6050 800 
Wire Wire Line
	6050 800  6500 800 
Wire Wire Line
	5600 1350 5600 800 
Connection ~ 5600 800 
Wire Wire Line
	5600 800  5900 800 
Wire Wire Line
	5150 1350 5150 800 
Connection ~ 5150 800 
Wire Wire Line
	5150 800  5600 800 
Wire Wire Line
	5400 2000 5400 1950
Wire Wire Line
	5400 1600 6050 1600
Wire Wire Line
	6050 1600 6050 1550
Wire Wire Line
	6050 1600 6500 1600
Wire Wire Line
	6500 1600 6500 1550
Connection ~ 6050 1600
Wire Wire Line
	5500 2000 5500 1950
Wire Wire Line
	5500 1650 6950 1650
Wire Wire Line
	5600 2000 5600 1950
Wire Wire Line
	5600 1700 7400 1700
Wire Wire Line
	5700 2000 5700 1950
Wire Wire Line
	5700 1750 7850 1750
Wire Wire Line
	7850 1750 7850 1550
Wire Wire Line
	7850 1750 8300 1750
Wire Wire Line
	8300 1750 8300 1550
Connection ~ 7850 1750
Wire Wire Line
	5200 1550 5200 1950
Wire Wire Line
	5300 1550 5600 1550
Wire Wire Line
	6950 1550 6950 1650
Wire Wire Line
	7400 1550 7400 1700
Wire Wire Line
	5100 2000 5100 1950
Wire Wire Line
	5900 1950 5700 1950
Connection ~ 5700 1950
Wire Wire Line
	5700 1950 5700 1750
Wire Wire Line
	5600 1950 5700 1950
Connection ~ 5600 1950
Wire Wire Line
	5600 1950 5600 1700
Wire Wire Line
	5600 1950 5500 1950
Connection ~ 5500 1950
Wire Wire Line
	5500 1950 5500 1650
Wire Wire Line
	5500 1950 5400 1950
Connection ~ 5400 1950
Wire Wire Line
	5400 1950 5400 1600
Wire Wire Line
	5400 1950 5300 1950
Connection ~ 5300 1950
Wire Wire Line
	5300 1950 5300 1550
Wire Wire Line
	5300 1950 5200 1950
Connection ~ 5200 1950
Wire Wire Line
	5200 1950 5200 2000
Wire Wire Line
	5200 1950 5100 1950
Connection ~ 5100 1950
Wire Wire Line
	5100 1950 5100 1800
Text GLabel 6300 5700 2    50   Input ~ 0
USB_STP
Text GLabel 6300 5900 2    50   Input ~ 0
USB_DIR
Text GLabel 6300 6000 2    50   Input ~ 0
USB_NXT
Text GLabel 6300 2600 2    50   Input ~ 0
USB_D0
Text GLabel 6300 2800 2    50   Input ~ 0
USB_CK
Text GLabel 6300 4000 2    50   Input ~ 0
USB_D1
Text GLabel 6300 4100 2    50   Input ~ 0
USB_D2
Text GLabel 6300 5000 2    50   Input ~ 0
USB_D3
Text GLabel 6300 5100 2    50   Input ~ 0
USB_D4
Text GLabel 6300 5200 2    50   Input ~ 0
USB_D5
Text GLabel 6300 5300 2    50   Input ~ 0
USB_D6
Text GLabel 4500 6900 0    50   Input ~ 0
CAN3_RX
Text GLabel 4500 7000 0    50   Input ~ 0
CAN3_TX
Text GLabel 6300 4500 2    50   Input ~ 0
USB_D7
$Comp
L power:GND #PWR?
U 1 1 612D8FC0
P 3750 2600
AR Path="/612D8FC0" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/612D8FC0" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0115" H 3750 2350 50  0001 C CNN
F 1 "GND" V 3755 2472 50  0000 R CNN
F 2 "" H 3750 2600 50  0001 C CNN
F 3 "" H 3750 2600 50  0001 C CNN
	1    3750 2600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 611813E5
P 4200 1950
AR Path="/611813E5" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/611813E5" Ref="#PWR018"  Part="1" 
F 0 "#PWR018" H 4200 1700 50  0001 C CNN
F 1 "GND" V 4205 1822 50  0000 R CNN
F 2 "" H 4200 1950 50  0001 C CNN
F 3 "" H 4200 1950 50  0001 C CNN
	1    4200 1950
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 612DC779
P 3750 3000
AR Path="/612DC779" Ref="#PWR?"  Part="1" 
AR Path="/6115D60F/612DC779" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 3750 2750 50  0001 C CNN
F 1 "GND" V 3755 2872 50  0000 R CNN
F 2 "" H 3750 3000 50  0001 C CNN
F 3 "" H 3750 3000 50  0001 C CNN
	1    3750 3000
	0    1    1    0   
$EndComp
NoConn ~ 6300 4400
Wire Wire Line
	1750 3350 2050 3350
Connection ~ 2050 3350
$Comp
L Device:C_Small C?
U 1 1 613280F6
P 900 3550
AR Path="/613280F6" Ref="C?"  Part="1" 
AR Path="/6115D60F/613280F6" Ref="C2"  Part="1" 
F 0 "C2" H 992 3596 50  0000 L CNN
F 1 "100nF" H 992 3505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 900 3550 50  0001 C CNN
F 3 "~" H 900 3550 50  0001 C CNN
	1    900  3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  3650 900  3850
$Comp
L Device:C_Small C?
U 1 1 6132FB0C
P 2050 3550
AR Path="/6132FB0C" Ref="C?"  Part="1" 
AR Path="/6115D60F/6132FB0C" Ref="C3"  Part="1" 
F 0 "C3" H 2142 3596 50  0000 L CNN
F 1 "10uF" H 2142 3505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2050 3550 50  0001 C CNN
F 3 "~" H 2050 3550 50  0001 C CNN
	1    2050 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 3650 2050 3850
NoConn ~ 6300 2400
NoConn ~ 6300 2300
$EndSCHEMATC
