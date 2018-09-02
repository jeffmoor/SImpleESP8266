/*
	The setup() function and two lines before it are the boilerplate for all ESP8266 sketches.
	It accomplishes the following:

		- Includes the ESP8266 library ESP8266WiFi.h.
		- Creates the instance "server" of the class "WiFiServer" listening on port 80. Notice "server" is a global instance.
		- Set the mode of our ESP8266 to be an Access Point (AP).
		- Provide the SSID and password. The password / passphrase has to be at least 8 characters long.

		- Fire-up our server by calling the begin() method.
*/


#include <ESP8266WiFi.h>

WiFiServer server(80); //Initialize the server on Port 80

const short int BUILTIN_LED2 = 16;//GPIO16

void setup()
 {

	WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint
	WiFi.softAP("Hello_IoT", "12345678"); // Provide the (SSID, password); .
	server.begin(); // Start the HTTP Server

					//Looking under the hood
	Serial.begin(115200); //Start communication between the ESP8266-12E and the monitor window
	IPAddress HTTPS_ServerIP = WiFi.softAPIP(); // Obtain the IP of the Server
	Serial.print("Server IP is: "); // Print the IP to the monitor window
	Serial.println(HTTPS_ServerIP);

	pinMode(BUILTIN_LED2, OUTPUT); //GPIO16 is an OUTPUT pin;
	digitalWrite(BUILTIN_LED2, LOW); //Initial state is ON
}


// the loop function runs over and over again until power down or reset
void loop() {

	/*
	digitalWrite(BUILTIN_LED2, LOW); // Turn the LED ON by making the voltage LOW
	delay(1000);
	digitalWrite(BUILTIN_LED2, HIGH);
	delay(1000);
	*/

	WiFiClient client = server.available();

	if (!client) {
		return;
	}

	//Looking under the hood
	Serial.println("Somebody has connected :)");

	//Read what the browser has sent into a String class and print the request to the monitor
	String request = client.readString();

	//Looking under the hood
	Serial.println(request);

	// Handle the Request

	if (request.indexOf("/OFF") != -1) {
		digitalWrite(BUILTIN_LED2, HIGH);
	}
	else if (request.indexOf("/ON") != -1) {
		digitalWrite(BUILTIN_LED2, LOW);
	}

	/*
	digitalWrite(BUILTIN_LED2, LOW); // Turn the LED ON by making the voltage LOW
	delay(100);
	digitalWrite(BUILTIN_LED2, HIGH);
	delay(100);
	digitalWrite(BUILTIN_LED2, LOW); // Turn the LED ON by making the voltage LOW
	delay(100);
	digitalWrite(BUILTIN_LED2, HIGH);
	delay(100);
	*/
}
