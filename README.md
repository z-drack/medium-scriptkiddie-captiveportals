# Captive Portal WiFi - README

## Descrição

Este projeto consiste em um Captive Portal WiFi usando um módulo ESP8266. Ele permite que os dispositivos se conectem a uma rede WiFi simulada e, ao tentar acessar a internet, são redirecionados para uma página de login.

## `Aviso: Este projeto foi desenvolvido exclusivamente para fins educacionais no estudo do módulo ESP8266. Não o utilize com a intenção de obter informações confidenciais de terceiros. A utilização e as consequências decorrentes são de total responsabilidade do usuário.`

#

## Configuração do Ambiente

1.  **Configurando as Credenciais da Rede WiFi:**
    
    -   No código do Arduino, configure o nome (SSID) da sua rede WiFi.

`WiFi.softAP("Wifi-Clientes");` 

2.  **Configurando as Credenciais de Admin:**
    
    -   Defina um nome de usuário e senha para a página de administração (admin).

`const char *adminUsername = "admin";`
`const char *adminPassword = "admin123";`

3. **Configurando o IP do captive portal**
	- Defina o IP que o Arduino irá utilizar para você acessar o portal admin.
`IPAddress  apIP(172, 217, 28, 1);`

### Bibliotecas Necessárias

Recomendo a utilização do **Arduino IDE** na versão **1.8.19**. As versões mais novas não suportam a biblioteca **FS**.

Certifique-se de ter as seguintes bibliotecas instaladas no seu ambiente de desenvolvimento Arduino:

-   `ESP8266WiFi`
-   `DNSServer`
-   `ESP8266WebServer`
-   `FS` (Sistema de Arquivos SPIFFS)

### Upload dos Arquivos para o SPIFFS

#### Pré-requisitos

Antes de começar, certifique-se de ter as bibliotecas necessárias instaladas no seu ambiente de desenvolvimento Arduino, conforme mencionado anteriormente.

#### Ferramenta de Upload do Arduino IDE

A ferramenta de upload do Arduino IDE permite que você envie arquivos para o sistema de arquivos SPIFFS do ESP8266.

### Upload dos Arquivos para o SPIFFS
1. Os arquivos HTML( `home.html`, `login-page.html`, `post-login.html`) deverão ficar dentro da pasta `data`. Você pode utilizar a função `ctrl+k` para verificar a localização dos arquivos.

2. Instale a Ferramenta de Upload do SPIFFS:
   - No Arduino IDE, vá para **Sketch -> Incluir Biblioteca -> Gerenciar Bibliotecas...**
   - Pesquise por "ESP8266FS" e instale.

3. Carregue os Arquivos:
   - Após instalar a biblioteca, vá para **Ferramentas -> ESP8266 Sketch Data Upload.**
   - A IDE começará a compilar e, em seguida, carregará os arquivos para o sistema de arquivos SPIFFS do ESP8266.

4. Verifique o Status:
   - Verifique a janela de saída para garantir que o upload foi bem-sucedido.
   - O status do upload e o tamanho total usado no SPIFFS serão exibidos na parte inferior da janela da IDE.

5. Reinicie o ESP8266:
   - Após o upload dos arquivos, reinicie o ESP8266 para aplicar as alterações.

## Páginas e Funcionalidades

1.  **Página Inicial (`/`):** Exibe uma mensagem de boas-vindas e um botão para redirecionar para a página de login.

2.  **Página de Login (`/login`):** Formulário de login para os usuários inserirem suas credenciais.

3.  **Página pós-login (`/post-login`):** Página exibida após o login bem-sucedido.

4.  **Página de Administração (`/admin`):** Página protegida por senha para visualizar as credenciais salvas.

## Arquivos HTML

Os arquivos HTML são armazenados no sistema de arquivos SPIFFS do ESP8266. Certifique-se de incluir os seguintes arquivos:

-  **home.html:** Página inicial.

-  **login-page.html:** Página de login.

-  **post-login.html:** Página pós-login.

## Compilar e Carregar

- Certifique-se de ter as bibliotecas necessárias instaladas.

- Configure as credenciais do administrador no código.

- Compile e carregue o código para o módulo ESP8266.

## Notas Adicionais

- Lembre-se de personalizar as mensagens, estilos e lógica conforme necessário.

- Consulte a documentação da ESP8266 para obter informações detalhadas sobre o uso do sistema de arquivos SPIFFS.
