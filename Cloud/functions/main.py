import functions_framework
import requests
import json
from google.cloud import bigquery
from datetime import datetime

 # Configuration
PROJECT_ID = "iot-exploratory-2025"
DATASET_ID = "group_42_dataset"
TABLE_ID = "air_quality"

# Open-Meteo Air Quality API (No API Key Required)
LAT, LON = 13.7563, 100.5018  # Bangkok coordinates
AIR_QUALITY_API_URL = f"https://air-quality-api.open-meteo.com/v1/air-quality?latitude={LAT}&longitude={LON}&hourly=pm10,pm2_5,carbon_monoxide,nitrogen_dioxide,sulphur_dioxide,ozone&current=us_aqi"

def fetch_air_quality_data():
    """Fetch air quality data from Open-Meteo API"""
    response = requests.get(AIR_QUALITY_API_URL)
    if response.status_code == 200:
        data = response.json()
        current_data = data["current"]
        current_time = current_data["time"]
        hourly_data = data["hourly"]
        time_index = hourly_data["time"].index(current_time)
        
        return {
            "location": "Bangkok",
            "timestamp": current_time,  # Last hourly data timestamp
            "us_aqi": current_data.get("us_aqi", None),  # US Air Quality Index
            "co": hourly_data["carbon_monoxide"][time_index],  # Carbon Monoxide
            "no2": hourly_data["nitrogen_dioxide"][time_index],  # Nitrogen Dioxide
            "so2": hourly_data["sulphur_dioxide"][time_index],  # Sulfur Dioxide
            "o3": hourly_data["ozone"][time_index],  # Ozone
            "pm2_5": hourly_data["pm2_5"][time_index],  # PM2.5 Particulate Matter
            "pm10": hourly_data["pm10"][time_index]  # PM10 Particulate Matter
        }
    else:
        raise Exception(f"Failed to fetch air quality data: {response.status_code} - {response.text}")

def store_in_bigquery(air_quality_data):
    """Store air quality data in BigQuery"""
    client = bigquery.Client()
    table_ref = f"{PROJECT_ID}.{DATASET_ID}.{TABLE_ID}"
    
    errors = client.insert_rows_json(table_ref, [air_quality_data])

    if errors:
        raise Exception(f"Failed to insert into BigQuery: {errors}")
    # print("Air quality data inserted into BigQuery:", air_quality_data)

@functions_framework.http
def fetch_and_store_air_quality(request):
    """Cloud Function triggered via HTTP to fetch and store air quality data"""
    try:
        air_quality_data = fetch_air_quality_data()
        store_in_bigquery(air_quality_data)
        return json.dumps({"message": "Air quality data stored successfully", "data": air_quality_data}), 200
    except Exception as e:
        return json.dumps({"error": str(e)}), 500
