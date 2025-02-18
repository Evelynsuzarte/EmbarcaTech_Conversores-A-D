# Uso de interrupções no microcontrolador RP2040

## Descrição
Compreender o funcionamento e a aplicação de interrupções em microcontroladores. 
- Identificar e corrigir o fenômeno do bouncing em botões por meio de debouncing via software. 
- Manipular e controlar LEDs comuns e LEDs endereçáveis WS2812. 
- Fixar o estudo do uso de resistores de pull-up internos em botões de acionamento. 
- Desenvolver um projeto funcional que combine hardware e software.

Neste projeto, você deverá utilizar os seguintes componentes conectados à placa BitDogLab: 
1. Matriz 5x5 de LEDs (endereçáveis) WS2812, conectada à GPIO 7. 
2. LED RGB, com os pinos conectados às GPIOs (11, 12 e 13). 
3. Botão A conectado à GPIO 5. 
4. Botão B conectado à GPIO 6.


## Funcionalidades
1. O LED vermelho do LED RGB deve piscar continuamente 5 vezes por segundo. 
2. O botão A deve incrementar o número exibido na matriz de LEDs cada vez que for pressionado. 
3. O botão B deve decrementar o número exibido na matriz de LEDs cada vez que for pressionado. 
4. Os LEDs WS2812 devem ser usados para criar efeitos visuais representando números de 0 a 9.  
    - Formatação fixa: Cada número deve ser exibido na matriz em um formato fixo, como caracteres em estilo digital (ex.: segmentos iluminados que formem o número). 
    - Alternativamente, é permitido utilizar um estilo criativo desde que o número seja claramente identificável.

[Vídeo de Demonstração](https://drive.google.com/file/d/12hUX5_5979x8y5ZJ_spFAq-Id_dmuH3v/view?usp=sharing)

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
