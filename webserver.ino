#include <ESP8266WiFi.h>

const char* ssid = "kelompok3"; // Adjust to your network SSID
const char* password = "harusbahagia"; // Adjust to your network password

#define ON HIGH
#define OFF LOW

int led1 = D0;
int led2= D7;

int value1 = OFF;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, OFF);
  digitalWrite(led2, OFF);
  Serial.print("Connecting to ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: http://");
  Serial.println(WiFi.localIP());
}












void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("New client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/led1=ON") != -1) {
    digitalWrite(led1, ON);
    value1 = ON;
  }
  if (request.indexOf("/led1=OFF") != -1) {
    digitalWrite(led1, OFF);
    value1 = OFF;
  }

    if (request.indexOf("/led2=ON") != -1) {
    digitalWrite(led2, ON);
    value1 = ON;
  }
  if (request.indexOf("/led2=OFF") != -1) {
    digitalWrite(led2, OFF);
    value1 = OFF;
  }

  // Send the HTML page with Bootstrap styling
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta charset='utf-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  client.println("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css' integrity='sha384-rwoIResjU2yc3z8GV/NPeZWAv56rSmLldC3R/AZzGRnGxQQKnKkoFVhFQhNUwEyJ' crossorigin='anonymous'>");
  client.println("</head>");
  client.println("<body>");
  client.println("<br><br>");
  client.println("<div class='container'>");
  client.println("<div class='row'>");
  client.println("<div class='col-md-6'>");
  client.println("<div class='card mb-3'>");
  client.println("<div class='card-header'>");
  client.println("<h3>BOOTSTRAP NODEMCU</h3>");
  client.println("</div>");
  client.println("<div class='card-body'>");
  client.println("<h4>Menyalakan dan mematikan LED</h4>");
  client.println("<h4>Lampu1</h4>");
  client.println("<a href=\"/led1=ON\" class='btn btn-danger btn-block'>ON</a>");
  client.println("<a href=\"/led1=OFF\" class='btn btn-primary btn-block'>OFF</a>");
  
  client.println("</div>");

  client.println("<div class='card-body'>");
  client.println("<h4>lampu2</h4>");
  client.println("<a href=\"/led2=ON\" class='btn btn-danger btn-block'>ON</a>");
  client.println("<a href=\"/led2=OFF\" class='btn btn-primary btn-block'>OFF</a>");
  
  client.println("</div>");
  client.println("<p>Created by : Finan Erlandung & Agusti");
  client.println("<table>");
  client.println("<tr>");
  client.println("<td>");
  client.println("<a href='https://ibb.co/mtJQZGp'><img src='https://i.ibb.co/CvBxCzL/finan.jpg' alt='finan' border='0' width='200px'></a>");
  client.println("</td>");
  client.println("<td>");
  client.println("<a href='https://ibb.co/smVPWrB'><img src='https://i.ibb.co/5MR9KV7/agus.jpg' alt='agus' border='0' width='200px'></a>");
  client.println("</td>");
  client.println("</tr>");
  client.println("</table>");
  client.println("</div>");
  client.println("</div>");
  client.println("</div>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");

  // Close the connection
  client.stop();
  Serial.println("client disconnected");
  Serial.println("");
}