from flask import Flask, request, jsonify
from pymongo import MongoClient

app = Flask(__name__)

mongoURL = "mongodb://localhost:27017/"
client = MongoClient(mongoURL)

db = client['ESP_Sensor_data']
collection = db['readings']

@app.route("/addData", methods=["POST"])
def addData():
    try:
        sensorData = request.json
        collection.insert_one(sensorData)
        print(sensorData)
        return jsonify({"message": "Data saved successfully"}), 200
    
    except Exception as e:
        return jsonify({"message": "Error saving data", "error": str(e)}), 500
    
if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000, debug=True)