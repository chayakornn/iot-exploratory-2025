import paho.mqtt.client as mqtt
import json
import time
import random

DEVICE_IDS = ["weather_01"]  #, "weather_02", "weather_03", "weather_04", "weather_05"]
GROUP_ID = "<groupname>"
PUBLISH_INTERVAL = 5  # seconds

# === CONFIGURATION ===
MQTT_BROKER_IP = "192.168.0.0"   # Replace with your MQTT broker IP
MQTT_BROKER_PORT = 1883            # Replace with your MQTT broker port
MQTT_TOPIC = f"{GROUP_ID}/weather/sensor"

# === SIMULATION FUNCTION ===
def generate_sensor_data(device_id):
    return {
        "device_id": device_id,
        "group_id": GROUP_ID,
        "temperature": round(random.uniform(20.0, 35.0), 2),
        "humidity": round(random.uniform(40.0, 90.0), 2),
        "pressure": round(random.uniform(1000.0, 1025.0), 2),
        "light": random.randint(100, 1000),
        "timestamp": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
    }

# === MQTT SETUP ===
client = mqtt.Client()
client.connect(MQTT_BROKER_IP, MQTT_BROKER_PORT, 60)
client.loop_start()

print(f"Publishing weather sensor data to MQTT {MQTT_BROKER_IP}:{MQTT_BROKER_PORT} on topic '{MQTT_TOPIC}'")

try:
    while True:
        for device_id in DEVICE_IDS:
            data = generate_sensor_data(device_id)
            payload = json.dumps(data)
            client.publish(MQTT_TOPIC, payload)
            print("Published:", payload)
        time.sleep(PUBLISH_INTERVAL)
except KeyboardInterrupt:
    print("\nStopped by user.")
finally:
    client.loop_stop()
    client.disconnect()
