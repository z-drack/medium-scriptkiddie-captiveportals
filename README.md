# Captive Portal WiFi - README

## Descrição
Este projeto consiste em um Captive Portal WiFi usando um módulo ESP8266. Ele permite que os dispositivos se conectem a uma rede WiFi simulada e, ao tentar acessar a internet, são redirecionados para uma página de login.

## Configurações Iniciais
- **Endereço IP do Portal Cativo:** 172.217.28.1

## Páginas e Funcionalidades
1. **Página Inicial (`/`):** Exibe uma mensagem de boas-vindas e um botão para redirecionar para a página de login.

2. **Página de Login (`/login`):** Formulário de login para os usuários inserirem suas credenciais.

3. **Página pós-login (`/post-login`):** Página exibida após o login bem-sucedido.

4. **Página de Administração (`/admin`):** Página protegida por senha para visualizar as credenciais salvas.

## Arquivos HTML
Os arquivos HTML são armazenados no sistema de arquivos SPIFFS do ESP8266. Certifique-se de incluir os seguintes arquivos:
- **home.html:** Página inicial.
- **login-page.html:** Página de login.
- **post-login.html:** Página pós-login.

## Compilar e Carregar
- Certifique-se de ter as bibliotecas necessárias instaladas.
- Configure as credenciais do administrador no código.
- Compile e carregue o código para o módulo ESP8266.

## Notas Adicionais
- Lembre-se de personalizar as mensagens, estilos e lógica conforme necessário.
- Consulte a documentação da ESP8266 para obter informações detalhadas sobre o uso do sistema de arquivos SPIFFS.

## Autores
[Seu Nome]

---
