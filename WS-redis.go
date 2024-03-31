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
		var msg_split []string = strings.Split(string(msg), "@") 	// Splitted data
		currentTime := strconv.FormatInt(time.Now().Unix(), 10) 	// Current date and time
		key := msg_split[0]                                     	// Key to the linked list on Redis
		value := currentTime + "|" + msg_split[1]               	// Value to the linked list on Redis

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
