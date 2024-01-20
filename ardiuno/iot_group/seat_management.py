import serial
import requests
import json

ser = serial.Serial('COM5', 9600)

previous_is_used = {}

while True:
    arduino_data = ser.readline().decode('utf-8').strip()
    
    if arduino_data:
        data = arduino_data.split(',')
        chair_number = int(data[0].split(':')[1].strip())
        is_used = int(data[2].split(':')[1].strip())
        
        if chair_number in previous_is_used and is_used != previous_is_used[chair_number]:
        
            url = f"http://127.0.0.1:5000/chair?charNo={chair_number}&is_used={is_used}"
            
            try:
                response = requests.get(url)
                response.raise_for_status()
                print("HTTP GET requests successful")
                previous_is_used[chair_number] = is_used
            except requests.exceptions.RequestException as e:
                print(f"HTTP GET request failed: {e}")
        else:
            previous_is_used[chair_number] = is_used
