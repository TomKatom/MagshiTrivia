import socket
import time 

def printAsciiArt():
    print('''
████████ ██████  ██ ██    ██ ██  █████      
   ██    ██   ██ ██ ██    ██ ██ ██   ██     
   ██    ██████  ██ ██    ██ ██ ███████     
   ██    ██   ██ ██  ██  ██  ██ ██   ██     
   ██    ██   ██ ██   ████   ██ ██   ██                                                                           
    ''')

printAsciiArt()
print("* Connect to server ...")

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 5000        # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    try:
        s.connect((HOST, PORT))
    except Exception as e:
        print("* Connection failed.")
        exit()
    
    time.sleep(2)
    print("* Connection succeeded \n")

    print("* sign up: (username: \"user1\",password: \"1234\", email:user1@gmail.com )")
    time.sleep(2)
    x =  '''{"username" : "user1", "password" : "1234", "email" : "user1@gmail.com"}'''
    data = b = bytes([21,0x0,0x0,0x0,len(x)]) + x.encode()
    s.sendall(data)
    data = s.recv(1024)
    print("recived: ", repr(data), "\n")

    print("* log in: (username: \"user1\", password: \"1234\")")
    time.sleep(2)
    x =  '''{"username" : "user1", "password" : "1234"}'''
    data  =  b = bytes([20,0x0,0x0,0x0,len(x)]) + x.encode()
    s.sendall(data) 
    data = s.recv(1024)
    print("recived: ", repr(data), "\n")


