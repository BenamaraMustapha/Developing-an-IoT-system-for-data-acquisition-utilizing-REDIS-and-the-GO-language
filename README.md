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

    Sensor Network: The sensors are linked to microcontroller devices responsible for transmitting data to the concentrator. The choice of board models such as Arduino, ESP8266, ESP32, PIC, etc., is unrestricted. However, the selection should align with the preferred communication method.

    Communication Forms and Protocols: The system adheres to certain operating and software standards before device integration. Communication between devices and the concentrator is facilitated through various protocols, including:
        Wi-Fi / Ethernet (Websocket / HTTP / REST)
        RF / LoRa
        Serial / Bluetooth
        GSM / GPRS

    Receiving Routine: A GO routine is implemented to receive data from sensors, process it, and transmit it to the REDIS cache. Each communication protocol specified in step 2 has its dedicated routine.

    REDIS Cache: The REDIS cache serves to temporarily or permanently store sensor data. Optionally, the cache can be mirrored (replicated) for redundancy purposes.

## Comments:

    Additional Layers: Depending on the communication method and distance between components, there might be supplementary layers of hardware or software for interconnection. This overview provides a simplified description of the architecture.

    Server Distribution: While the architecture doesn't mandate specific decisions regarding server distribution, it's advisable to allocate a dedicated LINUX server for REDIS.

    Module Scope: This description exclusively focuses on the data acquisition module. Details about the control module will be provided separately.

## Technologies:

    REDIS: An in-memory data storage system renowned for its exceptional performance, serving as a NOSQL database, cache, or message broker. It employs key-value data structures like linked lists, strings, sets, etc., and offers options for temporary or persistent data storage. Noteworthy features include support for replication, stored procedures, partitioning, among others.

    GO (Golang): Developed by Google and released as open-source in November 2009, GO is a statically typed language compiled with a focus on productivity and concurrent programming. Its design caters to the multi-core nature of modern computers, making it a popular choice for programming large-scale network servers and distributed systems.

## Development Environment:

Let's delve into setting up the development environment for the Linux operating system.

Installing REDIS:

