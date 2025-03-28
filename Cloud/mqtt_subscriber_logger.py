import paho.mqtt.client as mqtt
import json
import os

GROUP_ID = "<groupname>"

# === CONFIGURATION ===
MQTT_BROKER_IP = "192.168.0.0"   # Replace with your MQTT broker IP
MQTT_BROKER_PORT = 1883            # Replace with your MQTT broker port
MQTT_TOPIC = f"{GROUP_ID}/weather/sensor"

OUTPUT_FILE = "received_data.json"

# === CALLBACKS ===
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
        client.subscribe(MQTT_TOPIC)
        print(f"Subscribed to topic: {MQTT_TOPIC}")
    else:
        print("Failed to connect, return code %d\n", rc)

def on_message(client, userdata, msg):
    try:
        payload = json.loads(msg.payload.decode())
        print("Received message:", payload)
        
        # Append to JSON file
        with open(OUTPUT_FILE, "a") as f:
            json.dump(payload, f)
            f.write("\n")
    except Exception as e:
        print("Error processing message:", e)

# === MQTT SETUP ===
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(MQTT_BROKER_IP, MQTT_BROKER_PORT, 60)

print(f"Waiting for messages from MQTT {MQTT_BROKER_IP}:{MQTT_BROKER_PORT} on topic '{MQTT_TOPIC}'")
client.loop_forever()
