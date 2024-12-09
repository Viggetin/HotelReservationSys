# Makefile #

CC = g++
TARGET = test.exe
OBJS = main.o functions.o

$(TARGET): main.o functions.o
	$(CC) -o $(TARGET) main.o functions.o

functions.o: functions.cpp header.h
	$(CC) -c functions.cpp

main.o: main.cpp header.h
	$(CC) -c main.cpp

clean:
	rm -f $(OBJS) $(TARGET)
