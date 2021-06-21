#!/usr/bin/env python3

import socket

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 5001        # The port used by the server

def main() -> None:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((HOST, PORT))
        sock.sendall(b'what')
        data = sock.recv(1024)
        print('Received: ', repr(data))
        print('END of python program')

if __name__ == "__main__":
    main()
