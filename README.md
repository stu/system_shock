System Shock
============
System Shock is an Open Source Pinball controller system consisting of hardware schematics and source code to drive the system.

The design goal is a board set capable of;

* 128 switches
* 32 solenoids / flashers
* LCD display
* Stero Sound

The last two can be achieved by utilising a Raspberry PI or some other small embedded computer.


Current Status
==============
*This is a very early work in progress that requires a lot more testing and design review.*


Licenses
========
### Software
All software and documentation is licensed under the GNU GPL v2
(see ./gpl-v2.txt)

### Hardware
All hardware schematics are licensed under the CERN Open Hardware License v1.2
(see cern_ohl_v_1_2.txt)


Revision History
================
### 20140805
* Tagged revision 1 of the solenoid board as I sent it to the fab to get made

### 20140605
* Rerouted solenoid driver board
* Exported gerbers + Excellon drill file for solenoid driver

### 20140524

* Expose to github
* Copy solenoid driver code and schematics over
* Hack up parts of master document into solenoid documentation

