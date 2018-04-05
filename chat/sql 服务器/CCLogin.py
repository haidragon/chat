# -*-encoding:utf-8 -*-
import CCMysql
import CCSerSend
import socket
import threading
ccSerSocket=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
ccSerSocket.bind(('192.168.1.189',8989))
# ccSerSocket.bind(('192.168.43.80',8989))
ccSerSocket.listen()
def thadd():
    while True:
        ccCliSocket, adrr = ccSerSocket.accept()
        CCSerSend.ccClient(ccCliSocket, adrr)
        print(ccCliSocket)
def myaccpt():
    t=threading.Thread(target=thadd)
    t.start()


myaccpt()
if __name__ == '__main__':
    myaccpt()
