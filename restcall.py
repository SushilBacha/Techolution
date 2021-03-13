import requests
import json

response = requests.get("https://smart-reminder-web-app-ztisgbssmq-el.a.run.app/schedule")
print(response.json())

with open('content.json', 'w') as outfile:
    json.dump(response.json(), outfile)