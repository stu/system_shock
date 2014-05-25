# DipTrace Auto-Generated DO File
bestsave off
grid via 0.0039
grid wire 0.0039
define (class Dip_Net_Class_0 CLOCK GND LATCH Net@0 Net@1 Net@2 Net@3 Net@4 Net@5 Net@6 Net@7 Net@16 Net@17 Net@18 Net@19 Net@20 Net@21 Net@22 Net@23 Net@32 Net@33 Net@34 Net@35 Net@36 Net@37 Net@38 Net@39 Net@47 Net@48 Net@49 Net@50 Net@51 Net@52 Net@53 Net@54 NEXT_DATA1 NEXT_DATA2 NEXT_DATA3 VCC ~SOL_DISABLED)
circuit class Dip_Net_Class_0 (use_via DipViaStyle_0)
rule class Dip_Net_Class_0 (width 8)
rule class Dip_Net_Class_0 (clearance 8)
define (class Dip_Net_Class_1 Net@8 Net@9 Net@10 Net@11 Net@12 Net@13 Net@14 Net@15 Net@24 Net@25 Net@26 Net@27 Net@28 Net@29 Net@30 Net@31 Net@40 Net@41 Net@42 Net@43 Net@44 Net@45 Net@46 Net@55 Net@56 Net@57 Net@58 Net@59 Net@60 Net@61 Net@62 Net@63 VCC12)
circuit class Dip_Net_Class_1 (use_via DipViaStyle_0)
rule class Dip_Net_Class_1 (width 30)
rule class Dip_Net_Class_1 (clearance 20)
define (class Dip_Net_Class_2 SOL_01 SOL_02 SOL_03 SOL_04 SOL_05 SOL_06 SOL_07 SOL_08 SOL_09 SOL_10 SOL_11 SOL_12 SOL_13 SOL_14 SOL_15 SOL_16 SOL_17 SOL_18 SOL_19 SOL_20 SOL_21 SOL_22 SOL_23 SOL_24 SOL_25 SOL_26 SOL_27 SOL_28 SOL_29 SOL_30 SOL_31 SOL_32)
circuit class Dip_Net_Class_2 (use_via DipViaStyle_0)
rule class Dip_Net_Class_2 (width 70)
rule class Dip_Net_Class_2 (clearance 30)
set pad_wire_necking on
select all nets
unselect net GND
bus diagonal
route 20
clean 2
route 25 16
clean 2
filter 5
recorner diagonal
