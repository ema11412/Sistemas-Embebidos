# avoid needing tabs
ifeq ($(origin .RECIPEPREFIX), undefined)
	$(error This Make does not support .RECIPEPREFIX. Please use GNu Make 4.0 or later)
endif
.RECIPEPREFIX = >
# end of avoid needing tabs

NAME := hello

CC := gcc

CFLAGS := -Wall -Wextra -Werror -pedantic -std=c89 -fPIC -g
LDFLAGS := -g

INCLUDE := -I ../include

default: $(NAME).so
>

all: $(NAME).so
>

$(NAME).so: $(NAME).o
> gcc -shared -Wl,-soname,$(NAME).so -o $@ $<

$(NAME).o: $(NAME).c
> $(CC) $(CFLAGS) -c $< $(INCLUDE)

clean:
> rm -f $(NAME).so *.o

.PHONY: clean
