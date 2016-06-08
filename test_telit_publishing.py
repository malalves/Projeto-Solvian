import paho.mqtt.client as mqtt

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, rc):
    print("Connected with result code "+str(rc))
	# Subscribing in on_connect() means that if we lose the connection and
	# reconnect then subscriptions will be renewed.
    client.subscribe("$SYS/#")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
	print(msg.topic+" "+str(msg.payload))

#The callback for disconnect
def on_disconnect(client, userdata, rc):
    print("Disonnected with result code "+str(rc))

client = mqtt.Client("Teste")
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect
client.username_pw_set("test", password="05LR95wG0vIEsO4e")

client.connect("api.devicewise.com", 1883, 60)

client.publish("thing/test/property/nabo",32,1)
print("ok")
client.publish("thing/test/alarm/finoto",0,1)
print("ok")
client.publish("thing/test/attribute/jd","I did it",1)
print("ok")
