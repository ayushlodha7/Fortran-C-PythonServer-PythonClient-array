from flask import Flask, request
import struct

app = Flask(__name__)

message_store = None
float_array_store = []

@app.route('/receive_message', methods=['POST'])
def receive_message():
    global message_store
    message_store = request.form.get('message')
    print(f"Received: {message_store}")
    return "Message received", 200

@app.route('/receive_float_array', methods=['POST'])
def receive_float_array():
    global float_array_store
    # Unpack the binary data into float values
    float_array_store = list(struct.unpack('f' * (len(request.data) // 4), request.data))
    print(f"Received float array: {float_array_store}")
    return "Array received", 200

@app.route('/retrieve_message', methods=['GET'])
def retrieve_message():
    return message_store if message_store else "No message yet", 200

@app.route('/retrieve_array', methods=['GET'])
def retrieve_array():
    # Convert the stored float array back to binary format
    binary_data = struct.pack('f' * len(float_array_store), *float_array_store)
    return binary_data, 200


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
