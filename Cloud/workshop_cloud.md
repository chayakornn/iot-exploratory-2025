**IoT Workshop Part 2: Google Cloud Platform Integration**

Welcome to Part 2 of the IoT Workshop! In this part, you'll integrate your ESP32 sensor data into Google Cloud Platform (GCP), clean and store the data, analyze it with ML, and visualize insights through a dashboard. Each group will create its own GCP resources within a shared project.

---

### 🔌 Task 1: MQTT to Google Pub/Sub

**Objective:** Forward sensor data from the MQTT broker to your group’s Google Pub/Sub topic.

**Step-by-Step Instructions:**
1. **Install Required Libraries:**
   ```bash
   pip install -r requirements.txt
   ```
2. **Set Up Service Account:**
   ```bash
   gcloud iam service-accounts create mqtt-pubsub-forwarder --display-name="MQTT to Pub/Sub Forwarder"
   ```
3. **Grant Permission:**
   ```bash
   gcloud projects add-iam-policy-binding iot-exploratory-2025 --member="serviceAccount:mqtt-pubsub-forwarder@iot-exploratory-2025.iam.gserviceaccount.com" --role="roles/pubsub.publisher"
   ```
4. **Create Credentials Key:**
   On your terminal, change directory to a working directory that will save the generated key file.
   ```bash
   gcloud iam service-accounts keys create credentials.json --iam-account=mqtt-pubsub-forwarder@iot-exploratory-2025.iam.gserviceaccount.com
   ```
   This will save a file a `credentials.json` file into current directory.
5. **Create a Pub/Sub Topic**:
   ```bash
   gcloud pubsub topics create group_42-weather-sensor
   ```
6. **Create a Pub/Sub Subscription**:
   ```bash
   gcloud pubsub subscriptions create sub-group_42-weather-sensor --topic group_42-weather-sensor
   ```
7. **Write Python Script:**
   - Import libraries:
     ```python
     import json
     from paho.mqtt.client import Client
     from google.cloud import pubsub_v1
     ```
   - Set up MQTT client and Pub/Sub publisher.
   - On MQTT message received, convert to JSON and publish to Pub/Sub.
8. **Test the Script:**
   - Use `print()` statements to debug.
   - Verify message appearance in Pub/Sub console.

**Deliverable:** Working script that forwards live MQTT messages to Pub/Sub.

---

### 📊 Task 2: Pub/Sub to BigQuery with Data Cleaning

**Objective:** Store clean sensor data in BigQuery for analysis.

**Step-by-Step Instructions:**
1. **Create BigQuery Dataset and Table:**

   **a. Create Dataset:**
   ```bash
   gcloud alpha bq datasets create group_42_dataset
   ```

   **b. Create Table with Schema:**
   ```bash
   bq mk \
     --table group_42_dataset.sensor_data \
     device_id:STRING,group_id:STRING,timestamp:TIMESTAMP,temperature:FLOAT,humidity:FLOAT,pressure:FLOAT,light:INTEGER
   ```
   - Adjust field names and types based on your sensor data.

2. **Create Pub/Sub Subscription Connected to BigQuery (Using CLI):**

   **a. Grant Permission to BigQuery Table:**
   ```bash
   bq add-iam-policy-binding \
     --member="serviceAccount:service-832214016786@gcp-sa-pubsub.iam.gserviceaccount.com" \
     --role=roles/bigquery.dataEditor \
     -t "group_42_dataset.sensor_data"
   ```

   **b. Create Pub/Sub Subscription:**
   ```bash
   gcloud pubsub subscriptions create group_42-sub-bq \
     --topic=projects/iot-exploratory-2025/topics/group_42-weather-sensor \
     --bigquery-table=iot-exploratory-2025:group_42_dataset.sensor_data \
     --use-table-schema
   ```
   - Ensure the BigQuery table schema matches the JSON structure published to the topic.

3. **Clean the Data:**
   - Ensure all values are valid and complete
   - Normalize formats (e.g., timestamps, decimals)

**Deliverable:** BigQuery table that receives cleaned data in real time.

---

### ☁️ Task 3: Cloud Function for External Air Quality API

**Objective:** Collect air quality data from a public API and store it in BigQuery.

**Step-by-Step Instructions:**
1. **Create BigQuery Table:**
   ```bash
   bq mk --table iot-exploratory-2025:group_42_dataset.air_quality \
     location:STRING,timestamp:TIMESTAMP,us_aqi:INTEGER,co:FLOAT,no2:FLOAT,so2:FLOAT,o3:FLOAT,pm2_5:FLOAT,pm10:FLOAT
   ```

2. **Write Cloud Function (Python):**
   - Use `requests` to fetch data
   - Parse and extract necessary fields (AQI, PM2.5, location, timestamp)
   - Format the result as JSON
   - Use BigQuery API to insert row into your group's table

3. **Deploy the Function:**
   Change directory into `functions` folder.
   ```base
   gcloud functions deploy fetch_and_store_air_quality \
     --runtime python311 \
     --trigger-http \
     --allow-unauthenticated \
     --entry-point fetch_and_store_air_quality \
     --source .
   ```

4. **Schedule Using Cloud Scheduler:**
   - Create a job to trigger your function every 5–10 minutes.
   ```bash
   gcloud scheduler jobs create http get-air-quality-job \
     --schedule="*/10 * * * *" \
     --http-method=GET \
     --uri=https://us-central1-iot-exploratory-2025.cloudfunctions.net/fetch_and_store_air_quality \
     --time-zone="Asia/Bangkok"
     --location="us-central1"
   ```

**Deliverable:** BigQuery table with updated air quality data.

---

### 🧰 Task 4: Train an ML Model to Predict Air Quality

**Objective:** Use AutoML (Vertex AI) to build a model that predicts air quality levels using sensor data.

**Step-by-Step Instructions (Using GCP Web Interface):**

1. **Prepare Training Data in BigQuery:**
   - In BigQuery Console, run the following SQL to join sensor and air quality data:
     ```sql
     CREATE OR REPLACE TABLE group_42_dataset.training_data AS
     SELECT
       s.timestamp,
       s.temperature,
       s.humidity,
       s.gas,
       a.pm2_5 AS target_pm2_5
     FROM
       group_42_dataset.sensor_data s
     JOIN
       group_42_dataset.air_quality a
     ON FORMAT_TIMESTAMP('%Y-%m-%d %H:00:00', s.timestamp) = FORMAT_TIMESTAMP('%Y-%m-%d %H:00:00', a.timestamp)
     ```

2. **Go to Vertex AI in GCP Console:**
   - Navigate to **Vertex AI > Datasets**.
   - Click **Create** and select **Tabular Dataset**.
   - Choose your region (e.g., `us-central1`).
   - Give it a name (e.g., `air_quality_dataset`).
   - Select **BigQuery Table** as the data source.
   - Use the table path: `project_id.group_42_dataset.training_data`

3. **Create AutoML Model:**
   - After the dataset is created, click on it, select **Train new model** and select **AutoML on Pipelines**.
   - Choose **AutoML for Tabular Classification / Regression** as Template Gallery pipeline.
   - On `Run detailes`, add group name to Run name (e.g., `group42-automl-tabular-yyyymmddhhmmss`), select `us-central` as Region, and, `One-off` as Run schedule. Click `Continue`.
   - On `Runtime configuration`, browse into `cloud-ai-platform-xxxx-xxxxx`, then create a folder with group name, then select it. Click `Continue`.
   - On `Training method`, select `Regression` as Objective, set `target_pm2_5` as the target column, set `group_42_regression_model` as Model name. Click `Continue`.
   - On `Training options`, review the setting and choose to `Automatic` as Transformation on all feature columns. Click `Continue`.
   - On `Compute and pricing`, configure training budget (e.g., 1 hour) and click `Submit` to start training.

4. **Review Results:**
   - After training, review metrics like RMSE.
   - Test the model using sample input to verify it makes predictions.

5. **(Optional) Deploy the Model:**
   - You can deploy the model to an endpoint to receive real-time predictions or use it in batch prediction.

**Deliverable:** A trained AutoML model predicting PM2.5 levels using sensor data.

---

### 📈 Task 5: Build a Dashboard in Looker Studio

**Objective:** Visualize your sensor data and ML predictions.

**Step-by-Step Instructions (Using Looker Studio Web Interface):**

1. **Open Looker Studio:**
   - Visit [https://lookerstudio.google.com](https://lookerstudio.google.com)

2. **Create a New Report:**
   - Click **Blank Report** and **Add Data**.
   - Choose **BigQuery** as the connector.
   - Select your project, then the dataset `group_42_dataset`, and choose tables like `sensor_data`, `air_quality`, or `training_data`.

3. **Build Visualizations:**
   - Add **Time Series Chart** for sensor values (e.g., temperature, humidity, gas).
   - Add charts or scorecards for air quality (e.g., PM2.5).
   - Optionally show model predictions if stored in BigQuery.

4. **Customize the Dashboard:**
   - Rename your charts, add filters (e.g., date range).
   - Use formatting options to enhance clarity.

5. **Share Your Dashboard:**
   - Use the **Share** button to invite your instructor or teammates.
   - Set permissions to allow viewing or editing.

**Deliverable:** A live Looker Studio dashboard displaying real-time sensor trends and predicted air quality values.

--- Build a Dashboard in Looker Studio

**Objective:** Visualize your sensor data and ML predictions.

**Step-by-Step Instructions:**
1. **Open Looker Studio:**
   - Go to [https://lookerstudio.google.com](https://lookerstudio.google.com)
2. **Connect to BigQuery:**
   - Select your group’s dataset and tables
3. **Build Dashboard:**
   - Add time-series charts for temperature, humidity, and AQI
   - Include table or card widgets for real-time values
   - Add predicted AQI using your ML model output
4. **Customize and Share:**
   - Add titles and group logo (optional)
   - Share with instructor (set access rights)

**Deliverable:** Live dashboard showing key data trends and ML results.

---

### 🔄 Task 6: Plan Control Feedback Loop

**Objective:** Prepare for Part 3 by designing how control commands (e.g., fan ON/OFF) will flow from dashboard to ESP32.

**Step-by-Step Instructions:**
1. **Decide on Control Use Case:**
   - E.g., fan ON if temp > 30°C, LED ON if AQI > 100
2. **Add Dummy Control to Dashboard:**
   - Use Boolean toggle/button in Looker Studio
   - Bind it to a BigQuery table or simulate with mock data
3. **Design Flow:**
   - Document flow: Dashboard → Pub/Sub → MQTT → ESP32
4. **Discuss with Instructor:**
   - Present your flow plan and get feedback

**Deliverable:** Documented plan ready for implementation in Part 3.

---

Let your instructor know when each task is complete to unlock the next one. Good luck and have fun!

