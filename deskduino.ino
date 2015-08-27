#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

// Listen on default port 5555, the webserver on the Yun
// will forward there all the HTTP requests for us.
YunServer server;

void setup() {
  Serial.begin(9600);

  // Bridge startup
  Bridge.begin();


  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);

digitalWrite(12, HIGH);
digitalWrite(13, HIGH);


  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) {
    // Process request
    process(client);

    // Close connection and free resources.
    client.stop();
  }

  delay(50); // Poll every 50ms
}

void process(YunClient client) {
  // read the command
  String command = client.readStringUntil('/');

  // is "mode" command?
  if (command == "up") {
    upCommand(client);
  }

  // is "mode" command?
  if (command == "down") {
    downCommand(client);
  }

  if (command == "home") {
    zeroCommand(client);
  }
}

void upCommand(YunClient client) {
  int ttravel;
  // Read amount of time to travel
    ttravel = client.parseInt();
    client.print("Pin 13 Set to Output");
    digitalWrite(13, LOW);
    delay(ttravel);
    digitalWrite(13, HIGH);
    client.print("Travel Upward Complete");
}

void downCommand(YunClient client) {
    int ttravel;
    // Read amount of time to travel
    ttravel = client.parseInt();
    digitalWrite(12, LOW);
    delay(ttravel);
    digitalWrite(12, HIGH);
    client.print("Travel Downward Complete");
}

void zeroCommand(YunClient client) {
    int ttravel;
    // Read amount of time to travel
    ttravel = client.parseInt();
    digitalWrite(12, LOW);
    delay(9000);
    digitalWrite(12, HIGH);
    client.print("Travel to Zero Complete");
}
