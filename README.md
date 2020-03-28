# ArduinoLanSwitch

It's an example of how to build with and arduino nano and a ethernet module, a switch that can be controlled via lan.

![alt text](https://raw.githubusercontent.com/gsampallo/ArduinoLanSwitch/master/image/ArduinoLanSwitch1.jpg "Diagrama")

## Configuration

Default IP address of the device is http://192.168.5.2 and will return a JSON string with the uptime and relays' status.
There is no configuration process, just change the IP address for the one desired in the code.

## Operation

|URL|Action|
| ------ | ------ |
|http://192.168.5.2/?status1=ON| Activate Relay 1|
|http://192.168.5.2/?status1=OFF| Deactivate Relay 1|
|http://192.168.5.2/?status2=ON| Activate Relay 2|
|http://192.168.5.2/?status2=OFF| Deactivate Relay 2|

## JSON

The JSON return has the following format:


```sh
{ 
   'uptime':'1',
   's1':'ON',
   's2':'OFF'
}
```

uptime is in seconds. s1 and s2 can assume ON or OFF values, depend on the status of each relays.

You can read the article on my [blog](https://www.gsampallo.com/blog/?p=612) to more details.