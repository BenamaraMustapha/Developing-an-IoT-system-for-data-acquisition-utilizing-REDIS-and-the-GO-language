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
<div style="display: flex; justify-content: center;"> <img src="https://github.com/BenamaraMustapha/Developing-an-IoT-system-for-data-acquisition-utilizing-REDIS-and-the-GO-language/assets/119163433/3422ac6d-418f-4eb8-9c13-2850327f6022" width="300" height="150"> </div>

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

