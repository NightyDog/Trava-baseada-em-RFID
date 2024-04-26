# Trava baseada em RFID

Este projeto foi feito no 4º Semestre de Ciência da Computação para a matéria de Microcontroladores e IOT, ministrada pelo professor Ivair Lima.
Este código é um exemplo de controle de acesso utilizando um leitor RFID (Radio-Frequency IDentification) e um teclado numérico. Logo abaixo, estará um resumo contendo todos os componentes e mais alguns detalhes.


## Componentes Utilizados:

Leitor RFID (MFRC522)

Tela LCD (com I2C)

Teclado Numérico

Servo Motor (SG90)

LEDs (Verde e Vermelho)

Buzzer

## Funcionalidades:
O sistema inicialmente está configurado para o modo RFID, onde um usuário pode acessar o sistema utilizando um cartão RFID.
Quando um cartão é detectado, o sistema verifica se a UID do cartão corresponde à UID armazenada no código.
Se o cartão for autenticado com sucesso, o sistema solicita a entrada de uma senha através do teclado numérico.
Após inserir a senha correta, o servo motor é acionado para abrir a porta por um breve período de tempo.
Se o cartão ou a senha forem inválidos, o sistema emite um alerta sonoro e visual.
Configuração:
Os pinos dos componentes são inicializados no método setup().
A tela LCD é inicializada e a comunicação SPI é configurada para o leitor RFID.
Loop Principal (loop()):
O sistema verifica se está no modo RFID ou no modo de inserção de senha e executa as respectivas operações.
No modo RFID, o sistema aguarda a detecção de um cartão e verifica sua autenticidade.
No modo de inserção de senha, o sistema espera a entrada de quatro dígitos pelo teclado numérico.
Após a entrada da senha, o sistema verifica se ela corresponde à senha inicial configurada e, em caso afirmativo, aciona o servo para abrir a porta.
Este código pode ser útil para implementações de controle de acesso simples, combinando a conveniência dos cartões RFID com a segurança adicional de uma senha. Certifique-se de adaptar as configurações e pinagens conforme necessário para o seu ambiente de aplicação.




Link do vídeo:

## Integrante do grupo
Igor Fernandes Couto | 1960172@fmu.edu.br

RA 1960172 

Turma BCC 191104A16

Dennys Soares de Oliveira | 1794853@fmu.edu.br

RA 1794853

Turma BCC 191104A16

Robert Espi Tavares | 1855709@fmu.edu.br

RA 1855709

Turma BCC 191104A16


## Imagens

### protoboard com as conexões
![protoboard](https://github.com/igorfernandescouto/Trava-baseada-em-RFID/assets/96797275/8e917f73-7292-4202-9552-54c63bc312b0)


### Keypad
![keypad](https://github.com/igorfernandescouto/Trava-baseada-em-RFID/assets/96797275/3c370ada-40ee-419e-8bc3-0b41ae9bf241)




### Servo Motor
![servo](https://github.com/igorfernandescouto/Trava-baseada-em-RFID/assets/96797275/f4d16cfb-92db-4ae1-ab55-af81de9dd2f9)


### leitor RFID
![rfid](https://github.com/igorfernandescouto/Trava-baseada-em-RFID/assets/96797275/27b90833-1ac0-4191-8f8e-bdb5a0ba8bc6)

### Display I2C LCD
![display](https://github.com/igorfernandescouto/Trava-baseada-em-RFID/assets/96797275/54807e2a-d0aa-4bc7-8f9e-b1b9c968fbdf)

### Arduino Uno R3 
![arduino](https://github.com/igorfernandescouto/Trava-baseada-em-RFID/assets/96797275/74e4ac68-1b1e-4561-b583-ff20da35200b)
