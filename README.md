# Developing-an-IoT-system-for-data-acquisition-utilizing-REDIS-and-the-GO-language
## Basic Overview 
An IoT data acquisition system comprises a network of sensors transmitting data to central units for processing and storage. This facilitates monitoring and control of devices both locally and remotely.

This projet focuses on elucidating the architecture of the receptor module.
## Context:

The receptor module is designed to facilitate the reception and storage of data transmitted by a network of microcontrollers positioned locally or remotely.
    -Each microcontroller device is outfitted with a set of sensors, transmitting measurements to the central receiver through various communication protocols.
    -The data received is then directed through a concentrator, functioning akin to a broker or gateway.
    -Subsequently, this data is rapidly cached in memory, ready for processing by the supervisory application.

## Steps Explanation:
<img src="https://github.com/BenamaraMustapha/Developing-an-IoT-system-for-data-acquisition-utilizing-REDIS-and-the-GO-language/assets/119163433/3422ac6d-418f-4eb8-9c13-2850327f6022"> 

- Sensor Network: The sensors are linked to microcontroller devices responsible for transmitting data to the concentrator. The choice of board models such as Arduino, ESP8266, ESP32, PIC, etc., is unrestricted. However, the selection should align with the preferred communication method.

- Communication Forms and Protocols: The system adheres to certain operating and software standards before device integration. Communication between devices and the concentrator is facilitated through various protocols, including:
        Wi-Fi / Ethernet (Websocket / HTTP / REST)
        RF / LoRa
        Serial / Bluetooth
        GSM / GPRS

- Receiving Routine: A GO routine is implemented to receive data from sensors, process it, and transmit it to the REDIS cache. Each communication protocol specified in step 2 has its dedicated routine.

- REDIS Cache: The REDIS cache serves to temporarily or permanently store sensor data. Optionally, the cache can be mirrored (replicated) for redundancy purposes.

## Comments:

- Additional Layers: Depending on the communication method and distance between components, there might be supplementary layers of hardware or software for interconnection. This overview provides a simplified description of the architecture.

- Server Distribution: While the architecture doesn't mandate specific decisions regarding server distribution, it's advisable to allocate a dedicated LINUX server for REDIS.

- Module Scope: This description exclusively focuses on the data acquisition module. Details about the control module will be provided separately.

## Technologies:

- REDIS: An in-memory data storage system renowned for its exceptional performance, serving as a NOSQL database, cache, or message broker. It employs key-value data structures like linked lists, strings, sets, etc., and offers options for temporary or persistent data storage. Noteworthy features include support for replication, stored procedures, partitioning, among others.

- GO (Golang): Developed by Google and released as open-source in November 2009, GO is a statically typed language compiled with a focus on productivity and concurrent programming. Its design caters to the multi-core nature of modern computers, making it a popular choice for programming large-scale network servers and distributed systems.

## Development Environment:

Let's delve into setting up the development environment for the Linux operating system.

### Installing REDIS:
    Shell

    sudo apt update
    sudo apt install redis
To start the REDIS server as a service:
    Shell

    sudo systemctl start redis-server

To check the status of the server or stop the service:
    Shell

    sudo systemctl status redis
    sudo systemctl stop redis

The REDIS package comes with a client application, redis-cli, which can be used for maintenance and testing. To see if everything is working, run the commands:
    Shell

    redis-cli
    set hello world
    get hello

If the system answered “world”, it means that everything is ok and you have just created a String data structure with the key <span style="color:red;">“hello”</span>
and value <span style="color:red;">“world”</span>.

To exit the client, type: <span style="color:red;">quit</span>

Optionally, you can also install a client with more features and ease of use: [Redis Desktop Manager](https://redis.com/redis-enterprise/redis-insight/)
## GO Language Installation

The first step is to download the installation package from the official website of [Golang](https://golang.org/dl/)

Then unzip the file with the following command:
    Shell

    sudo tar -C /usr/local -xzf package_name

Where package_name is the name of the file you downloaded.

The subsequent step entails configuring the environment.

In our realm, the GO language holds authority across various aspects, a notion evident even during the setup of the development environment.

Preceding installation, it's imperative to strategize the organization of your Workspace, delineating the location of your source code files. While not obligatory, adhering to a prescribed pattern is advisable.

Let's assume your workspace resides in the /home/user/gocode directory. Within this directory, create three subdirectories at the same level:

    pkg: This directory houses packages and libraries downloaded or created for reference in your programs.
    src: Here lie your source code files.
    bin: This directory is designated for storing executable files created and installed from the src folder, akin to a deployment folder.

Furthermore, you'll need to establish three environment variables:

    GOPATH: The path to your workspace. Multiple paths can be defined, separated by a colon.
    GOROOT: The path where GO was installed, typically /usr/local/go.
    GOBIN: The directory where GO should generate executables. It can be the bin folder within your workspace, though the choice is yours.

It's highly recommended to adjust the PATH variable to point to the GO binaries, typically found at /usr/local/go/bin.

To create these environment variables, utilize the export command. Edit the ~/.profile file (sudo gedit ~/.profile) and append the export commands at the end.

In my case, it appeared as follows:
    Shell

    export PATH=$PATH:/usr/local/go/bin
    export GOROOT=/usr/local/go
    export GOPATH=/home/josecintra/code/go
    export GOBIN=/home/josecintra/code/go/bin
Golang underscores the significance of version control systems, notably GIT. You'll require one for installing third-party library packages.

In case you haven't installed a version control system on your Linux system yet, refer to the installation instructions available at this [link](https://git-scm.com/download/linux.)

Now that's done! The next step involves selecting an IDE.
## IDEs for the GO Language

This is a personal matter. I like Geany a lot. It is already configured to edit, compile and run GO programs.

To install, use the following commands:
    Shell

    sudo add-apt-repository ppa:geany-dev/ppa
    sudo apt-get update
    sudo apt-get install geany geany-plugins-common

if you don't want to use Geany, here's an extensive list of IDEs with support for the GO language:

    [Here](https://github.com/golang/go/wiki/IDEsAndTextEditorPlugins)

## Data Modeling:

Now, let's delve into the utilization of REDIS and its role within this project module.

REDIS serves as an auxiliary database for the primary DBMS of the supervisory system. Its primary function entails storing data from the sensor network, enabling real-time display and processing.

Given its exceptional performance, REDIS proves to be an optimal choice for such applications, thereby alleviating the burden on the system's main database.

In the supervisory system module, REDIS will assume additional functions beyond the scope of this discussion.

### The Scenario:

The scenario we aim to model is as follows: Multiple sensors deployed locally or remotely will periodically dispatch their measurement data to a server. The data collection routine (implemented in Golang) will store this data in REDIS, facilitating processing and presentation by the supervisory application on a dashboard.

The specific information we intend to store from the sensors includes:

Sensor identification: This comprises a unique sensor ID, represented as a string composed of three letters and a numerical sequence, joined by a pipe separator (“|”).
For instance:
A temperature sensor might have the ID “TMP | 1”.
A humidity sensor could have the ID “HMD | 100”, and so forth.
These IDs must be unique, akin to primary keys.

Date and time of transmission: For expediency, the date will be stored in Unix Time Stamp format.
Measurement value: This encompasses a numeric value stored as a string.

It's important to note that REDIS is oblivious to the specifics of sensor IDs and measurement values; its role is merely to expedite data reception, leaving the complexity to the supervisory system.

## Data Structures:

Given the peculiarities of REDIS in contrast to relational databases, let's directly focus on data storage and access.

Among the data structures provided by REDIS, we opt for linked lists due to their exceptional performance in insertion and removal operations at the end of the list.

Consider the following scenario: On “2020/01/01” at “01:00:05”, the temperature sensor with code “TMP | 5” dispatched the value “25.25”.

For each sensor, we maintain a separate list. The key to our list is the sensor ID. Hence, we have a list dedicated to each sensor.

Converting the date to Unix timestamp yields “1577840405”. The command to store this data at the end of the list would be as follows:
    RPUSH TMP|5 1577840405|25.25

To obtain the last value sent by the “TMP | 5” sensor, we use the following command:

    RPOP TMP|5
Note: For enhanced readability and ease of management, an alternative approach involves representing the values in JSON format. This is a widely adopted practice in the REDIS ecosystem and is supported by the platform. JSON offers a structured format for data storage, facilitating parsing and manipulation within REDIS.
## Developing a Test Application:

Our next step involves developing a test application (Proof of Concept) to facilitate the transmission and reception of sensor data using Golang and REDIS.

For this specific test, we'll utilize a NodeMCU board programmed within the Arduino IDE. This board will transmit data from an NTC temperature sensor via WebSockets every 30 seconds.

The Golang application, acting as the receiver, will be responsible for receiving, parsing, and storing the data in REDIS, thereby making it accessible for the web application.

We'll commence by detailing the NodeMCU application.

NodeMCU Application
Station NodeMCU
### Prototype
<img src="https://github.com/BenamaraMustapha/Developing-an-IoT-system-for-data-acquisition-utilizing-REDIS-and-the-GO-language/assets/119163433/1bd56852-c80d-4134-868a-c9c0ab162950">
## Components

- NodeMCU card. In fact, it can be any ESP *. * Family board compatible with the Arduino IDE (ESP8266, NodeMCU, Wemos, ESP32, etc.)
- 10K NTC thermistor type temperature sensor
- Jumper wires and, optionally, a protoboard
## Required Software

- To create the websocket server, we will need to install the [ArduinoWebsockets](https://github.com/gilmaimon/ArduinoWebsockets)
 which can be installed by the Arduino IDE itself through a library manager.
- The temperature data from the sensor will be sent every 3 minutes to the WEB server. To simplify our code, let's count the time with millis using the [NeoTimer](https://github.com/jrullan/neotimer), library, which is also available in the manager.
- The temperature reading and calculation will be done through the following routine available on the Internet: [Thermistor Interfacing with NodeMCU](https://www.electronicwings.com/nodemcu/thermistor-interfacing-with-nodemcu)
## Sketch
    C++
    /*
     This sketch:
            1. Connects to a WiFi network
            2. Connects to a Websockets server
            3. Periodically sends data from a temperature sensor to the server
            4. Receives return messages from the server
    */

    // From library Manager
    #include <arduinowebsockets.h> 
    #include <esp8266wifi.h>
    #include <neotimer.h>

    const char* ssid = "x";  //Enter your SSID
    const char* password = "y"; //Enter your Password
    const char* websockets_server_host = "192.168.0.0"; //Enter your server address
    const uint16_t websockets_server_port = 8080; // Enter server port

    Neotimer mytimer = Neotimer(10000); // Time interval for sending sensor data
    String tempString;
    String sensor = "TMP|5";
    using namespace websockets;

    WebsocketsClient client;
    void setup() {
        Serial.begin(9600);
    
        // Connect to wifi
        WiFi.begin(ssid, password);

        // Wait some time to connect to wifi
        for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
            Serial.print(".");
            delay(1000);
        }

        // Check if connected to wifi
        if(WiFi.status() != WL_CONNECTED) {
            Serial.println("No Wifi!");
            return;
        }

        Serial.println("Connected to Wifi, Connecting to server.");
        // try to connect to Websockets server
        bool connected = client.connect(websockets_server_host, websockets_server_port, "/");
        if(connected) {
            Serial.println("Connecetd!");
            //client.send("Hello Server");
        } else {
            Serial.println("Not Connected!");
        }
    
        // run callback when messages are received
        client.onMessage([&](WebsocketsMessage message) {
            Serial.print("Got Message: ");
            Serial.println(message.data());
        });
    }

    void loop() {
      // let the websockets client check for incoming messages
      if(client.available()) {
        client.poll();
      }
      // Periodic sending of temperature sensor data to the customer
      if (mytimer.repeat()) {
        tempString = readTemperature();
        Serial.println(tempString);
        client.send(sensor + "@" +tempString);
      }
    }

    // Temperature reading and calculation by the thermistor
    double readTemperature() {
      // Code extracted from the 'Thermistor Interfacing with NodeMCU' tutorial available at:
      // https://www.electronicwings.com/nodemcu/thermistor-interfacing-with-nodemcu

      const double VCC = 3.3; // NodeMCU on board 3.3v vcc
      const double R2 = 10000; // 10k ohm series resistor
      const double adc_resolution = 1023; // 10-bit adc
      const double A = 0.001129148; // thermistor equation parameters
      const double B = 0.000234125;
      const double C = 0.0000000876741;
      double Vout, Rth, temperature, adc_value;

      adc_value = analogRead(A0);
      Vout = (adc_value * VCC) / adc_resolution;
      Rth = (VCC * R2 / Vout) - R2;

      temperature = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)), 3))));  // Temperature in kelvin
      temperature = temperature - 273.15;  // Temperature in degree celsius
      delay(500);
      return (temperature);
    }
## Golang Receiving Station:
Required Software

While we've covered the installation of REDIS and the GO language previously, establishing a connection with REDIS and accepting WebSocket connections from the NodeMCU requires the installation of specific library packages:

- GORILLA: A Web Toolkit for the GO language.
- REDIGO: A Go Client for REDIS.

To install these packages, execute the following commands in your virtual terminal:
    Go

    go get github.com/gorilla/websocket
    go get github.com/gomodule/redigo/redis

## GO
    GO
    /*
     
	        This routine:
                1. Starts a Websockets server
                3. Waits for client messages with sensor data  
                4. Parses the data received
                5. Stores data in a REDIS database 
         */    

    package main

    import (
	    "fmt"
	    "strconv"
	    "strings"
	    "time"
	    "log"
	    "github.com/gomodule/redigo/redis" 
	    "github.com/gorilla/websocket"
	    "net/http"
    )

    // HTTP request handler
    var upgrader = websocket.Upgrader{
	    ReadBufferSize:  1024,
	    WriteBufferSize: 1024,
	    CheckOrigin:     func(r *http.Request) bool { return true },
    }

    func main() {

      // Starts the server connection 
	    http.HandleFunc("/", handler)
	    http.ListenAndServe(":8080", nil)
    }

    func handler(writer http.ResponseWriter, request *http.Request) {
	    socket, err := upgrader.Upgrade(writer, request, nil)
	    if err != nil {
		    fmt.Println(err)
	    }
	    for {
		    // reading the message received via Websocket
	    	msgType, msg, err := socket.ReadMessage() // Dados recebido do sensor
	    	if err != nil {
		    	fmt.Println(err)
		    	return
		    }

		    // Tratar a mensagem recebida
		    var msg_split []string = strings.Split(string(msg), "@")   // Splitted data
		    currentTime := strconv.FormatInt(time.Now().Unix(), 10)    // Current date and time
		    key := msg_split[0]                                        // Key to the linked list
                                                                   // on Redis
		    value := currentTime + "|" + msg_split[1]                  // Value to the linked 
                                                                   // list on Redis

		    // Send the data to REDIS
		    conn, err := redis.Dial("tcp", "localhost:6379")
		    if err != nil {
		    	log.Fatal(err)
		    }
		    defer conn.Close()
		    _, err = conn.Do("RPUSH", key, value)
		    if err != nil {
			    log.Fatal(err)
		    }

		    // Optional: Returning the received message back to the customer
		    err = socket.WriteMessage(msgType, msg)
		    if err != nil {
		    	fmt.Println(err)
		    	return
		    }
	    }
    }
## Wrap-up:

The amalgamation of the GO language and the REDIS database presents a potent combination for constructing robust and scalable applications, especially tailored for the IoT landscape.

The code snippets demonstrated here are instructional in nature. However, there are ample opportunities for refinement:

- Introduction of encryption and security measures to fortify data integrity.
- Implementation of concurrency via GO routines to enhance operational efficiency.
- Modularization of the application architecture to foster code maintainability and flexibility.

By iteratively enhancing these facets, developers can augment the prowess and resilience of their IoT solutions.
## References

- [REDIS Official Page](https://redis.io/)
- [Golang Official Page](https://go.dev/)
- [José Cintra Page](https://www.josecintra.com/)
