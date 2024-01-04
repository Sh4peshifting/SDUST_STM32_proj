import serial
import threading
from flask import Flask, render_template, request, jsonify
import time
import datetime

app = Flask(__name__)
ser = serial.Serial('/dev/ttyS4', 9600, timeout=1)


# Global variable to store the data
disp_data = {'lock': 1, 'light': 2, 'fan': 2, 'alarm': 2, 'auto': 2, 'people': 0}
air_data = {'temp': 0, 'hum': 0, 'CH': 0, 'CO2': 0, 'TVOC': 0, 'PM2': 0, 'PM10': 0}
warnings = {}
# Threshold values
thresholds = {'temp': 30, 'hum': 40, 'CH': 100, 'CO2': 4000, 'TVOC': 50, 'PM2': 300, 'PM10': 600}

def read_uart_data(serial_port):
    global disp_data, air_data

    last_byte = 0
    while True:
        response = serial_port.read(1)
        if last_byte == b'\xff' and response == b'\x55':
            break
        last_byte = response
         
    # Read response
    response = serial_port.read(1)
    
    if response == b'\x00':
        response = serial_port.read(14)
        # Parse response
        air_data = {'temp': response[0] + response[1] / 10,
                'hum': response[2] + response[3] / 10,
                'CH': int.from_bytes(response[4:6], byteorder='big'),
                'CO2': int.from_bytes(response[6:8], byteorder='big'),
                'TVOC': int.from_bytes(response[8:10], byteorder='big'),
                'PM2': int.from_bytes(response[10:12], byteorder='big'),
                'PM10': int.from_bytes(response[12:], byteorder='big')}

        return air_data
    
    elif response == b'\x01':
        response = serial_port.read(6)
        # Parse response
        disp_data = {'lock': response[0],
                'light': response[1],
                'fan': response[2],
                'alarm': response[3],
                'auto': response[4],
                'people': response[5]
                }

        return disp_data

def read_data():
    while True:
        read_uart_data(ser)
            
@app.route('/data', methods=['GET'])
def get_data():
    time_date = datetime.datetime.now()
    time_str = time_date.strftime('%Y年%m月%d日 %H:%M:%S')
    global disp_data, air_data, warnings, thresholds
    warnings = {key: value > thresholds[key] for key, value in air_data.items()}
    return jsonify(disp=disp_data, warnings=warnings, air=air_data, time=time_str)

@app.route('/unlock', methods=['GET'])
def unlock():
    ser.write(bytes([0xFF, 0x00, 0x01]))
    return jsonify(success=True, message='Unlocking...')

@app.route('/lock', methods=['GET'])
def lock():
    ser.write(bytes([0xFF, 0x00, 0x02]))
    return jsonify(success=True, message='Locking...')

@app.route('/alarm_off', methods=['GET'])
def alarm():
    ser.write(bytes([0xFF, 0x01, 0x01]))
    return jsonify(success=True, message='Alarm off...')

@app.route('/light_on', methods=['GET'])
def light_on():
    ser.write(bytes([0xFF, 0x02, 0x01]))
    return jsonify(success=True, message='Light on...')

@app.route('/light_off', methods=['GET'])
def light_off():
    ser.write(bytes([0xFF, 0x02, 0x02]))
    return jsonify(success=True, message='Light off...')

@app.route('/light_low', methods=['GET'])
def light_low():
    ser.write(bytes([0xFF, 0x02, 0x03]))
    return jsonify(success=True, message='Light low...')

@app.route('/light_mid', methods=['GET'])
def light_mid():
    ser.write(bytes([0xFF, 0x02, 0x04]))
    return jsonify(success=True, message='Light mid...')

@app.route('/light_high', methods=['GET'])
def light_high():
    ser.write(bytes([0xFF, 0x02, 0x05]))
    return jsonify(success=True, message='Light high...')


@app.route('/fan_on', methods=['GET'])
def fan_on():
    ser.write(bytes([0xFF, 0x03, 0x01]))
    return jsonify(success=True, message='Fan on...')

@app.route('/fan_off', methods=['GET'])
def fan_off():
    ser.write(bytes([0xFF, 0x03, 0x02]))
    return jsonify(success=True, message='Fan off...')


@app.route('/speed_low', methods=['GET'])
def speed_low():
    ser.write(bytes([0xFF, 0x03, 0x03]))
    return jsonify(success=True, message='Speed low...')

@app.route('/speed_mid', methods=['GET'])
def speed_mid():
    ser.write(bytes([0xFF, 0x03, 0x04]))
    return jsonify(success=True, message='Speed mid...')

@app.route('/speed_high', methods=['GET'])
def speed_high():
    ser.write(bytes([0xFF, 0x03, 0x05]))
    return jsonify(success=True, message='Speed high...')

@app.route('/auto_on', methods=['GET'])
def auto_on():
    ser.write(bytes([0xFF, 0x04, 0x01]))
    return jsonify(success=True, message='Auto on...')

@app.route('/auto_off', methods=['GET'])
def auto_off():
    ser.write(bytes([0xFF, 0x04, 0x02]))
    return jsonify(success=True, message='Auto off...')

@app.route('/', methods=['GET', 'POST'])
def home():
    return render_template('home.html')

def run_server():
    app.run(host='0.0.0.0', port=5000)

if __name__ == '__main__':
    # Start a new thread for data reading
    data_thread = threading.Thread(target=read_data)
    data_thread.start()

    # Start a new thread for the server
    server_thread = threading.Thread(target=run_server)
    server_thread.start()
