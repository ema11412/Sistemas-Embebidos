# avoid needing tabs
ifeq ($(origin .RECIPEPREFIX), undefined)
	$(error This Make does not support .RECIPEPREFIX. Please use GNu Make 4.0 or later)
endif
.RECIPEPREFIX = >
# end of avoid needing tabs

CC := gcc
NAME := server

CFLAGS := -Wall -Wextra -Werror -pedantic -std=c90 -g -ftrack-macro-expansion=0
LDFLAGS := -g

default: $(NAME)
>

all: $(NAME)
>

$(NAME): $(NAME).o rpi_server.o gpio.o
> gcc -o $@ $^

$(NAME).o: $(NAME).c
> $(CC) $(CFLAGS) -c -o $@ $< -I../include

rpi_server.o: rpi_server.c
> $(CC) $(CFLAGS) -c -o $@ $< -I../include

gpio.o: gpio.c
> $(CC) $(CFLAGS) -c -o $@ $< -I../include

clean:
> rm -f $(NAME) *.o

.PHONY: clean

run: $(NAME)
> ./$(NAME)
