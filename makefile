CC = gcc
TARGET = ccalculator

PREF_SRC = ./src/
PREF_OBJ = ./obj/

SRC = $(wildcard $(PREF_SRC)*.c)
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))
CFLAGS = -Wall -o

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(TARGET)

$(PREF_OBJ)%.o : $(PREF_SRC)%.c
	$(CC) -c $< $(CFLAGS) $@

clean : 
	rm $(TARGET) $(OBJ)