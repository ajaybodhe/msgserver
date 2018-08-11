import socket
import pyDes

def listen():
    connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connection.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    connection.bind(('0.0.0.0', 5555))
    connection.listen(10)
    while True:
        current_connection, address = connection.accept()
        data = current_connection.recv(2048)
        if data:
            print "received data : " + data
            k = pyDes.triple_des(key="abcdefghijklmnopqrstuvwx",
                mode=pyDes.CBC,
                IV="\0\0\0\0\0\0\0\0",
                pad=None, 
                padmode=pyDes.PAD_PKCS5
                )
            print "decrypted data : " + k.decrypt(data)
            print k.encrypt("ajay")
            ## just in case u need echo
            # current_connection.send(data)

if __name__ == "__main__":
    try:
        listen()
    except KeyboardInterrupt:
        pass