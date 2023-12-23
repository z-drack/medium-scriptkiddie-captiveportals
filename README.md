
Captive Portal WiFi - README
Descrição
Este projeto implementa um portal cativo WiFi usando um módulo ESP8266 (NodeMCU) e fornece uma maneira simples de conectar dispositivos à rede WiFi por meio de um portal de login.

Configuração do Ambiente
Bibliotecas Necessárias
Certifique-se de ter as seguintes bibliotecas instaladas no seu ambiente de desenvolvimento Arduino:

ESP8266WiFi
DNSServer
ESP8266WebServer
FS (Sistema de Arquivos SPIFFS)
Upload dos Arquivos para o SPIFFS
Pré-requisitos
Antes de começar, certifique-se de ter as bibliotecas necessárias instaladas no seu ambiente de desenvolvimento Arduino, conforme mencionado anteriormente.

Ferramenta de Upload do Arduino IDE
A ferramenta de upload do Arduino IDE permite que você envie arquivos para o sistema de arquivos SPIFFS do ESP8266.

Preparando os Arquivos:

Coloque todos os arquivos HTML que deseja incluir (por exemplo, home.html, login-page.html, post-login.html) em um diretório.
Instalando a Ferramenta de Upload do SPIFFS:

No Arduino IDE, vá para Sketch -> Incluir Biblioteca -> Gerenciar Bibliotecas...
Pesquise por "ESP8266FS" e instale.
Carregando os Arquivos:

Após instalar a biblioteca, vá para Ferramentas -> ESP8266 Sketch Data Upload.
A IDE começará a compilar e, em seguida, carregará os arquivos para o sistema de arquivos SPIFFS do ESP8266.
Verificando o Status:

Verifique a janela de saída para garantir que o upload foi bem-sucedido.
O status do upload e o tamanho total usado no SPIFFS serão exibidos na parte inferior da janela da IDE.
Reiniciando o ESP8266:

Após o upload dos arquivos, reinicie o ESP8266 para aplicar as alterações.
Configuração do Portal Cativo
Configurando as Credenciais da Rede WiFi:
No código do Arduino, configure o nome (SSID) e a senha da sua rede WiFi.

cpp
Copy code
WiFi.softAP("Wifi-Clientes", "sua_senha_wifi");
Configurando as Credenciais de Admin:
Defina um nome de usuário e senha para a página de administração (admin).

cpp
Copy code
const char *adminUsername = "admin";
const char *adminPassword = "admin123";
Funcionalidades Principais
Página Home:
Acesse o portal inicial em http://esp8266.local/.
Permite redirecionamento para a página de login.
Página de Login:
Acesse a página de login em http://esp8266.local/login.
Simula um formulário de login básico.
Página Pós-Login (Admin):
Acesse a página após o login bem-sucedido em http://esp8266.local/admin.
Exibe um histórico de credenciais inseridas.




