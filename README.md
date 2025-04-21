# Projeto de Revisão - BitDogLab (Sistemas Embarcados)

## 📌 Sumário  
- [📹 Demonstração](#-demonstração)  
- [🎯 Objetivo](#-objetivo)  
- [🛠️ Funcionalidades Obrigatórias](#️-funcionalidades-obrigatórias)  
- [✨ Funcionalidades Adicionais](#-funcionalidades-adicionais)  
- [📦 Componentes Utilizados](#-componentes-utilizados)  
- [⚙️ Compilação e Gravação](#️-compilação-e-gravação)  
- [📂 Estrutura do Código](#-estrutura-do-código)  
- [👨‍💻 Autor](#-autor)  

## 📹 Demonstração  
[clique aqui para acessar o vídeo](https://youtu.be/l4Crf1CP6mE)

Conteúdo do vídeo:  
- Apresentação pessoal do autor  
- Explicação das funcionalidades implementadas  
- Demonstração ao vivo na placa BitDogLab  

## 🎯 Objetivo  
Desenvolver um sistema embarcado de monitoramento utilizando a placa BitDogLab com o microcontrolador RP2040. O projeto simula o rastreamento de um agente (como um animal em uma área de preservação), utilizando um quadrado móvel em display OLED controlado por joystick, com alertas visuais e sonoros ao se aproximar das bordas da área monitorada.  

## 🛠️ Funcionalidades Obrigatórias  
✅ Display SSD1306: Exibe um quadrado de 8x8 pixels cuja posição é controlada pelo joystick.  
✅ Joystick: Leitura analógica dos eixos X e Y para movimentação do quadrado.  
✅ Botões: Com tratamento de debounce e interrupções para alternar estados (travamento do sistema).  
✅ UART: Impressão de logs de posição via terminal serial USB.  

## ✨ Funcionalidades Adicionais  
🔹 Matriz de LEDs WS2812B 5x5: Ativada em verde como alerta visual ao atingir as bordas.  
🔹 LED RGB: Acende em vermelho quando o quadrado atinge a borda.  
🔹 Buzzer: Emite alerta sonoro ao atingir a borda.  
🔹 Sistema de travamento: Um botão permite travar e destravar o sistema de monitoramento.  

## 📦 Componentes Utilizados  
- Microcontrolador: RP2040 (BitDogLab)  
- Display: OLED SSD1306 (128x64, I2C)  
- Joystick: Leitura analógica dos eixos  
- Botões: Com tratamento de interrupção  
- Matriz de LEDs: 5x5 (WS2812B, controlada por PIO)  
- LED RGB: Controlado por PWM  
- Buzzer: Ativado com PWM para alertas sonoros  

## ⚙️ Compilação e Gravação  
```bash
git clone 
cd projeto-integrador
```

**Gravação:**  
Pelo ambiente do VScode compile e execute na placa de desnvovimento BitDogLab

## 📂 Estrutura do Código  

```plaintext
Tarefa1-F2/  
├── lib/  
│   ├── font.h               # Fonte de caracteres do display  
│   ├── ssd1306.c, h         # Biblioteca do display OLED  
│   ├── buttons.c, h         # Configuração e debounce de botões  
│   ├── rgb.c, h             # Controle do LED RGB via PWM  
│   ├── display_init.c, h    # Inicialização e desenho no display  
│   ├── matrixws.c, h        # Controle da matriz WS2812B  
│   ├── ws2812b.pio.h        # Programa PIO da matriz WS2812B  
│   ├── buzzer.c, h          # Inicialização e controle do buzzer  
├── func/  
│   ├── funcionalidades.c, h # Funções principais do sistema  
│   └── quadrado.c, h        # Lógica da movimentação do quadrado  
├── CMakeLists.txt           # Arquivo de configuração da build  
├── Tarefa1-F2.c             # Código principal (main)  
├── README.md                # Documento de descrição do projeto  
```

## 👨‍💻 Autor  
**Nome:** Ronaldo César Santos Rocha  
**GitHub:** [Ronaldo8617]
