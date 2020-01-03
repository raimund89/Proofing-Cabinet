EESchema Schematic File Version 4
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x08_Female J?
U 1 1 5E0F272A
P 1650 1550
F 0 "J?" H 1678 1526 50  0000 L CNN
F 1 "Conn_01x08_Female" H 1678 1435 50  0000 L CNN
F 2 "" H 1650 1550 50  0001 C CNN
F 3 "~" H 1650 1550 50  0001 C CNN
	1    1650 1550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Female J?
U 1 1 5E0F33AF
P 2200 1550
F 0 "J?" H 2092 2035 50  0000 C CNN
F 1 "Conn_01x08_Female" H 2092 1944 50  0000 C CNN
F 2 "" H 2200 1550 50  0001 C CNN
F 3 "~" H 2200 1550 50  0001 C CNN
	1    2200 1550
	-1   0    0    -1  
$EndComp
Text GLabel 1450 1250 0    50   Input ~ 0
RST
Text GLabel 1450 1350 0    50   Input ~ 0
ADC0
Text GLabel 1450 1450 0    50   Input ~ 0
GPIO16
Text GLabel 1450 1550 0    50   Input ~ 0
GPIO14
Text GLabel 1450 1650 0    50   Input ~ 0
GPIO12
Text GLabel 1450 1750 0    50   Input ~ 0
GPIO13
Text GLabel 1450 1850 0    50   Input ~ 0
GPIO15
Text GLabel 1450 1950 0    50   Input ~ 0
3V3
Text GLabel 2400 1250 2    50   Input ~ 0
GPIO1
Text GLabel 2400 1350 2    50   Input ~ 0
GPIO3
Text GLabel 2400 1450 2    50   Input ~ 0
GPIO5
Text GLabel 2400 1550 2    50   Input ~ 0
GPIO4
Text GLabel 2400 1650 2    50   Input ~ 0
GPIO0
Text GLabel 2400 1750 2    50   Input ~ 0
GPIO2
Text GLabel 2400 1850 2    50   Input ~ 0
GND
Text GLabel 2400 1950 2    50   Input ~ 0
5V
$Comp
L Connector:Jack-DC J?
U 1 1 5E0F59C7
P 1250 3000
F 0 "J?" H 1307 3325 50  0000 C CNN
F 1 "Jack-DC" H 1307 3234 50  0000 C CNN
F 2 "" H 1300 2960 50  0001 C CNN
F 3 "~" H 1300 2960 50  0001 C CNN
	1    1250 3000
	1    0    0    -1  
$EndComp
Text GLabel 1550 3100 2    50   Input ~ 0
GND
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 5E0F64ED
P 1800 2700
F 0 "J?" V 1764 2512 50  0000 R CNN
F 1 "PWR_SW" V 1673 2512 50  0000 R CNN
F 2 "" H 1800 2700 50  0001 C CNN
F 3 "~" H 1800 2700 50  0001 C CNN
	1    1800 2700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1550 2900 1800 2900
Wire Wire Line
	1900 2900 2000 2900
Text GLabel 2000 2900 2    50   Input ~ 0
12V
$EndSCHEMATC
