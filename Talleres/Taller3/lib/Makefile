.PHONY: clean all


APP=liboperaciones
LIB=operaciones
OBJ=$(LIB).o
SRC=$(LIB).c
STATIC=$(APP).a
DYNAMIC=$(APP).so
INCLUDE=../include/operaciones.h
CC=gcc
MAKELIB=ar rv
LD=ld
RANLIB=ranlib
CFLAGS=-shared

all: $(STATIC) $(DYNAMIC) clean

$(STATIC): $(OBJ)
		$(MAKELIB) $(STATIC) $(OBJ) && $(RANLIB) $(STATIC)

$(DYNAMIC): $(OBJ)
		$(LD) -o $(DYNAMIC) $(OBJ) $(CFLAGS)

$(OBJ): $(SRC) $(INCLUDE)
		$(CC) -c $(SRC)




clean:
		rm  *.o
