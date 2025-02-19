# Conversor analógico-digital (ADC) no RP2040

## Descrição e funcionalidades
O joystick fornecerá valores analógicos correspondentes aos eixos X e Y, que serão utilizados para: 

- Controlar a intensidade luminosa dos LEDs RGB, onde: 
1. O  LED  Azul  terá  seu  brilho  ajustado  conforme  o  valor  do  eixo  Y.  Quando  o  joystick  estiver  solto (posição central - valor 2048), o LED permanecerá apagado. À medida que o joystick for movido para cima (valores menores) ou para baixo (valores maiores), o LED aumentará seu brilho gradualmente, atingindo a intensidade máxima nos extremos (0 e 4095). 
2. O LED Vermelho seguirá o mesmo princípio, mas de acordo com o eixo X. Quando o joystick estiver 
solto  (posição  central  -  valor  2048),  o  LED  estará  apagado.  Movendo  o  joystick  para  a  esquerda  (valores menores) ou para a direita (valores maiores), o LED aumentará de brilho, sendo mais intenso nos extremos (0 e 4095). 
3. Os LEDs serão controlados via PWM para permitir variação suave da intensidade luminosa. 
 
- Exibir  no  display  SSD1306  um  quadrado  de  8x8  pixels,  inicialmente  centralizado,  que  se  moverá 
proporcionalmente aos valores capturados pelo joystick. 
 
- Adicionalmente, o botão do joystick terá as seguintes funcionalidades: 
1. Alternar o estado do LED Verde a cada acionamento. 
2. Modificar a borda do display para indicar quando foi pressionado, alternando entre diferentes estilos 
de borda a cada novo acionamento. 
Finalmente, o botão A terá a seguinte funcionalidade: 
3. Ativar ou desativar os LED PWM a cada acionamento

Neste projeto, você deverá utilizar os seguintes componentes conectados à placa BitDogLab: 
1. LED RGB, com os pinos conectados às GPIOs (11, 12 e 13). 
2. Botão do Joystick conectado à GPIO 22. 
3. Joystick conectado aos GPIOs 26 e 27. 
4. Botão A conectado à GPIO 5. 
5. Display SSD1306 conectado via I2C (GPIO 14 e GPIO15). 
 
 

## Vídeo de demonstração


[Vídeo de Demonstração](https://drive.google.com/file/d/1At4d4RVZQukb8eNHqhH98qISfBLrF9TI/view?usp=sharing)

## Como compilar
Para compilar o programa, utilize um compilador C, gerando os arquivos `.uf2` e `.elf`. Siga os passos abaixo:

1. Configure o ambiente de desenvolvimento para o Raspberry Pi Pico.
2. Compile o código utilizando um compilador compatível.


## Como executar
Após a compilação, execute o simulador Wokwi clicando no arquivo `diagram.json`:

Para testar, clique em "Play" no Wokwi e explore o circuito.

Para colocar na placa, clique em "compile" e em "run" com a placa conectada.

## Requisitos
- Compilador C (gcc ou equivalente).
- Sistema operacional compatível com programas C.
- Extensão Raspberry Pi Pico.
- Wokwi configurado no VS Code.
- Placa Raspberry Pi Pico - BitDogLab

## Desenvolvedora
- [Evelyn Suzarte](https://github.com/Evelynsuzarte)
