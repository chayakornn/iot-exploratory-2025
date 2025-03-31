import paho.mqtt.client as mqtt
import json
from google.cloud import pubsub_v1
import os

GROUP_ID = "<groupname>"

# === CONFIGURATION ===
MQTT_BROKER_IP = "192.168.0.0"  # Replace with your MQTT broker IP
MQTT_BROKER_PORT = 1883         # Replace with your MQTT broker port
MQTT_TOPIC = f"{GROUP_ID}/weather/sensor"

GCP_PROJECT_ID = "<project_name>"
PUBSUB_TOPIC_ID = f"{GROUP_ID}-weather-sensor"

# Set the path to your Google service account credentials JSON
os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = "./credentials.json"

# === Pub/Sub SETUP ===
publisher = pubsub_v1.PublisherClient()
topic_path = publisher.topic_path(GCP_PROJECT_ID, PUBSUB_TOPIC_ID)

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
        payload = msg.payload.decode()
        print("Received MQTT message:", payload)

        # Publish to Google Cloud Pub/Sub
        future = publisher.publish(topic_path, payload.encode("utf-8"))
        print(f"Forwarded to Pub/Sub: {future.result()}")

    except Exception as e:
        print("Error handling message:", e)

# === MQTT CLIENT SETUP ===
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(MQTT_BROKER_IP, MQTT_BROKER_PORT, 60)

print(f"Listening to MQTT {MQTT_BROKER_IP}:{MQTT_BROKER_PORT} and forwarding to Pub/Sub topic '{PUBSUB_TOPIC_ID}'")
client.loop_forever()
