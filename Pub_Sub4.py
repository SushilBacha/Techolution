import paho.mqtt.client as mqtt
from datetime import datetime
import pytz
import time


def on_connect(client, userdata, flags, rc):
    if rc == 0:
        client.connected_flag=True  # set flag
        print("connected OK")
        print("Subscribing...")
        client.subscribe("IoTAssignment_{sushil_bacha}")
        print("Subscribed")
    else:
        print("Bad connection Returned code=",rc)


def on_message(client, userdata, msg):  # The callback for when a PUBLISH message is received from the server.
    print("Message received-> " + msg.topic + " " + str(msg.payload))  # Print a received msg


IST = pytz.timezone('Asia/Kolkata')
# create flag in class
mqtt.Client.connected_flag=False

broker="broker.mqttdashboard.com"
client = mqtt.Client("python1")  # create new instance
client.on_connect=on_connect  #bind call back function
client.on_message = on_message  # Define callback function for receipt of a message
client.loop_start()
print("Connecting to broker ",broker)
client.connect(broker)      #connect to broker
while not client.connected_flag: #wait in loop
    print("In wait loop")
    time.sleep(1)
print("in Main Loop")

try:
    while True:
        time = datetime.now(IST)
        value = " now : " + str(time) + ", name : Sushil BACHA"
        print("Publishing...")
        client.publish("IoTAssignment_{sushil_bacha}", value)
        print("Published")
        while True:{}
except KeyboardInterrupt:
    client.loop_stop()  # Stop loop
    client.disconnect()  # disconnect
