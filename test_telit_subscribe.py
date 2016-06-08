import paho.mqtt.client as mqtt

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, rc):
    print("Connected with result code "+str(rc))
	# Subscribing in on_connect() means that if we lose the connection and
	# reconnect then subscriptions will be renewed.
    #client.subscribe("thing/test/property/nabo",1)
    client.subscribe("thing/test/alarm/finoto",1)
    client.subscribe("thing/test/attribute/jd",1)

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
	print(msg.topic+" "+str(msg.payload))

#The callback for disconnect
def on_disconnect(client, userdata, rc):
    print("Disonnected with result code "+str(rc))

client = mqtt.Client("bla")
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect
client.username_pw_set("malacrida01@gmail.com", password="Fisica123.")

client.connect("api.devicewise.com", 1883, 60)

client.loop_forever()
