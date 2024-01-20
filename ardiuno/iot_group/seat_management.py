import serial
import requests
import json

ser = serial.Serial('COM5', 9600)

while True:
    arduino_data = ser.readline().decode('utf-8').strip()
    
    if arduino_data:
        data = arduino_data.split(',')
        chair_number = int(data[0].split(':')[1].strip())
        is_used = int(data[2].split(':')[1].strip())
        
        json_data = {"chair": chair_number, "is_used": is_used}
        
        print("Received JSON data:", json_data)