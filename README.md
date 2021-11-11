# FHICT-S3-demotica-dashboard/Arduino
In this project folder i am going to put all small applications/ developments made for my d1 mini esp8622

![test using blink](https://github.com/Rudolfisky/Demotica_Dashboard-POC-Esp8266/blob/main/Media/blink.gif?raw=true)

# app/WifiClient
This application i used to test making a my d1 mini connect to my router.
![connection](https://github.com/Rudolfisky/Demotica_Dashboard-POC-Esp8266/blob/main/Media/internet%20connection.png?raw=true)

# app/webserver_test
This application was used to see if i can host a webserver of of my d1 mini.

# app/TempSensor
This application i made to test my DS temperature sensor.

# app/tempWebserver
This application combines the webserver_test and TempSensor.

# app/DHT_sensor
This application i used to test my DHT sensor.

# soldering
![soldering](https://github.com/Rudolfisky/Demotica_Dashboard-POC-Esp8266/blob/main/Media/soldering.jpg?raw=true)

# conclusion/sensor
after having tried both DHT and DS sensors, i have concluded the following:
even though the DHT sensor has the capability to mesure temperature as wel as air moisture levels, it is only acurate to 2.5 degrees celcius.
the DS sensor is acurate to 0.5.
in conclusion, i am going to continue with the DS for now

# app/MQTT pub
the mqtt pub project connects to my local wifi network and my Mosquito mqtt server i have running on my laptop.
![connection](https://github.com/Rudolfisky/Demotica_Dashboard-POC-Esp8266/blob/main/Media/mqttpub.png?raw=true)

# app/MQTT pub temp
this project is a merge between MQTT pub and tempsensor




