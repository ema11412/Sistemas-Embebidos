# avoid needing tabs
ifeq ($(origin .RECIPEPREFIX), undefined)
	$(error This Make does not support .RECIPEPREFIX. Please use GNu Make 4.0 or later)
endif
.RECIPEPREFIX = >
# end of avoid needing tabs

NAME := hello

default:
> @echo "use"
> @echo make ffi
> @echo make ipc

ipc: back-end/server
> echo "starting server"
> ./back-end/server &
> echo "starting python client (will make server end)"
> python test/ipc/client.py
> echo ""
> sh -c 'command -v node && ( echo "starting server for node client" && ./back-end/server & ) || echo "node not installed" '
> sh -c 'command -v node && ( echo "starting nodejs client (will make server end)" && node test/ipc/client.js ) '

.PHONY: ipc

ffi: lib/$(NAME).so
> cp lib/$(NAME).so .
> python test/ffi/main.py # here the pwd of the process will be in where the .so file is, not in test/ffi

.PHONY: ffi

$(NAME).so: lib/$(NAME).so
> cp lib/$(NAME).so .

lib/$(NAME).so:
> make -C lib

clean:
> rm -f $(NAME).so
> make -C lib clean
> make -C back-end clean

.PHONY: clean

run: $(NAME).so main.py
> python main.py
