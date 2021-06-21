"""
wrapper for the dynamic library (.so in GNU/Linux)
"""

import sys
import ctypes

from typing import Optional


def bring_lib_into_scope(lib: ctypes.CDLL) -> tuple:
    """
    rewrite the signatures to be used outside this python module
    so they call the C code in the <lib> ctypes.CDLL instance
    """
    hello = lib.hello
    hello.argtypes = [ctypes.c_char_p]
    hello.restype = None

    floater = lib.floater
    floater.restype = ctypes.c_float

    fadd = lib.fadd
    fadd.argtypes = [ctypes.c_float, ctypes.c_float]
    fadd.restype = ctypes.c_float

    test_padding_array = lib.test_padding_array
    test_padding_array.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int]
    test_padding_array.restype = None

    # return tuple with the four functions
    return hello, floater, fadd, test_padding_array


def load_lib(name: str = "./hello.so") -> Optional[ctypes.CDLL]:
    """
    load and return shared library <name> or return None if <name> doesn't exist
    """
    lib = None
    try:
        lib = ctypes.cdll.LoadLibrary(name)
    except OSError as error:
        print(f"error:{error}")
    return lib


def print_data(data, data_len: int) -> None:
    """
    print <data_len> elements in <data> in the same line
    """
    for i in range(data_len):
        print(data[i], end=" ")
    # just print a newline
    print("")


def main() -> None:
    """
    main test for loading the dynamic library
    """
    # load the library, we MUST, if we wish to call its code
    lib = load_lib()
    if not lib:
        print("couldn't load lib")
        sys.exit()
    hello, floater, fadd, test_padding_array = bring_lib_into_scope(lib)

    num_el = 25
    # this is how a C array is initialized from a python list for the 'int' type
    data = (ctypes.c_int * num_el)(*[x for x in range(num_el)])

    # the b is important here, Python uses unicode code-points in str, so we have to use bytes to send to C code
    hello(b"Cinthia")
    # call function that returns float (ctypes.c_float in Python) and receives ( void ) in C
    print(f"f:{floater()}")
    # call function that returns float (ctypes.c_float in Python) and receives 2 floats (ctypes.c_float) arguments
    print(f"fadd:{fadd(1.25, 2.5)}")
    # call helper function to show the data in Python
    print_data(data, num_el)
    # it is important to send the size here, if we didn't C wouldn't "know" when to stop, because arrays decay
    # to pointers, and don't have a size, and Python doesn't know about structs, so we would have to declare
    # structs here anyway, if we meant to use the typedef struct "trick" to be able to pass arrays (and that may
    # be wasteful of memory anyway)
    test_padding_array(data, num_el)
    # call helper function to show the data in Python
    print_data(data, num_el)


if __name__ == "__main__":
    main()
