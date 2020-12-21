CC=gcc
INCLUDE=-I include

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME IF THEY DO NOT EXIST
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)


#TARGETS TO GENERATE THE OBJECT FILES
Parking_Lot.o: src/Parking_Lot.c 
	$(CC) -g $(INCLUDE) -c src/Parking_Lot.c -o build/Parking_Lot.o

Parking_test.o: test/Parking_test.c
	$(CC) -g $(INCLUDE) -c test/Parking_test.c -o build/Parking_test.o

#TARGET TO GENERATE THE EXECUTABLE OF THE PROGRAM (and the tests) - LINK OBJECT FILES
code: Parking_Lot.o 
	$(CC) -g -o bin/CODE.exe build/Parking_Lot.o 

#TARGET TO GENERATE THE EXECUTABLE OF THE PROGRAM (and the tests) - LINK OBJECT FILES
test: Parking_test.o
	$(CC) -g -o bin/TEST.exe build/Parking_test.o 

#TARGET TO RUN PARKINGLOT
launchcode:
		cd ./bin; ./CODE.exe


#TARGET TO RUN TEST
launchtest:
		cd ./bin; ./TEST.exe


#TARGET TO COMPILE/RUN PARKINGLOT
runcode: code launchcode


#TARGET TO COMPILE/RUN TEST
runtest: test launchtest



#CLEAN COMMANDS
clean: 
	rm -f bin/*.exe build/*.o