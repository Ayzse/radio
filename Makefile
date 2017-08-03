
nixie_ctl: nixi_ctl.o
	gcc nixi_ctl.o -o nixie_ctl -lwiringPi

nixi_ctl.o: nixi_ctl.c nixi_ctl.h
	gcc -Wall -c nixi_ctl.c -lwiringPi
