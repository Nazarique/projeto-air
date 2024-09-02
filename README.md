# Air-One

---------
Este repositório tem como objetivo, apresentar o [firmware](https://bitbucket.org/Nazarique/projeto-air/src/master/) para o protótipo de respirador mecânico **AIR-ONE**.

![](https://github.com/jakojakson/Air-one/blob/master/Midia/WhatsApp%20Image%202021-04-07%20at%2021.13.27.jpeg)
---------
O [COLLAB](https://linktr.ee/collabutfpr) em parceria com a DAF - Ponta Grossa, que propôs o desafio, a equipe que pertence ao COLLAB aceitou o mesmo. Em 26 dias o protótipo estava pronto e em abril de 2020 foi apresentado para a comunidade empresarial, secretários e autoridades da saúde, com a ilustre presença do nosso prefeito.

O sistema eletrônico do ventilador é composto de:

* Válvula Solenóide 2/2 X 3/8 NPT 3,2MM, com bobina de 24VCC) VALVULA SOLENOIDE 2/2 X 3/8 NPT 3,2MM LT 7KGF C/BOB 24VCC EPDM MULTICOIL
* Encoder (As5040)
* TIP122
* sensor de pressão (Mpx2050dp)
* driver (BTS7960)
* Módulo regulador de tensão step down LM2596
* sensor indutivo (Pnp Lj12a3-4-z/by)
* display LCD 20x4 Backlight Azul (PF)
* buzzer
* leds, cores (Azul, Vermelho, Amarelo e Verde)
* Módulo Arduino Mega 2560 R3
* Módulo Raspberry Pi 3
* Fonte de alimentação

O sistema é controlado por um módulo microprocessado Arduino© Mega 2560 R3, o qual possui 16 portas de entrada analógicas e 54 digitais, das quais 15 podem ser utilizadas para 
PWM. Tais portas foram necessárias devido a gama de sensores e atuadores utilizados no equipamento. O arduino foi acoplado em uma espécie de “cama” impressa em 3D para atender 
melhor às necessidades do grupo. 
As funções do módulo microprocessado foram divididas em: processamento de alarmes, interface homem-máquina (IHM) e acionamento do motor (respiração). O equipamento dispõe de um 
segundo módulo microprocessado, responsável pela interface gráfica (dashboard) que exibe as curvas de monitoramento respiratório do paciente, bem como, mensagens de status e 
alarmes. Para essa função foi escolhido o Raspberry Pi 3, pois possibilita conectar o sistema a um monitor convencional externo através de sua saída HDMI. O controlador foi 
inserido juntamente à estrutura do Arduino Mega.
  
![](https://github.com/jakojakson/Air-one/blob/master/Midia/arduinomontado.jfif)
 
Através da Interface Homem-Máquina (IHM) é possível realizar a parametrização das funcionalidades e modos de operação do equipamento, possibilitando assim os ajustes dos c
controles internos, para regulagem e adaptação dos mesmos, de acordo com quadro clínico do paciente. O menu é  exibido em uma display de cristal líquido (LCD) matricial de 20 
colunas por 4 linhas, escolhida para facilitar a configuração e comunicação entre os parâmetros setados no microprocessador e aqueles dos quais o operador deseja introduzir. 
Além do display, há um conjunto de 6 botões sendo 4 desses direcionais (cima, baixo, esquerda e direita) e os outros dois, sendo um para confirmação (verde) e outro para 
anulação (vermelho) de parâmetros. A navegação foi planejada para ser simples e intuitiva
Em um equipamento de ventilação pulmonar, é de suma importância a exteriorização de alarmes e a apresentação de mensagens de status, para que o profissional que está operando o 
mesmo possa intervir quando necessário.  Para o projeto do AIR ONE foi escolhido um conjunto de 4 LEDs de cores diferentes para indicar visualmente condições de alarme e modos 
de operação, quando ligados. O sistema conta também com um dispositivo buzzer para alarme sonoro. Ao optar pelo acoplamento do equipamento a um monitor, também se pode 
visualizar alarmes e mensagens de status na interface gráfica

<p align="center">
  <img src="https://user-images.githubusercontent.com/82101091/114220690-af210480-9942-11eb-8541-2726d2ea9ad3.png" />
</p>

Para a alimentação do Aparelho de Interface Respiratória foi utilizada uma fonte chaveada de 24 Volts de tensão contínua e 14 Amperes, em função das características do motor 
utilizado no projeto. Para alimentar o Arduino© e o Raspberry, cujas tensões de alimentação são 12 e 5 Volts respectivamente, foi utilizado um regulador de tensão LM7812 para o 
Arduino© e um conversor buck step down (módulo regulador LM2596) para o Raspberry. Para o controle do posicionamento do eixo do motor, que está diretamente relacionado à 
compressão do AMBU e consequentemente ao volume de ar fornecido ao paciente, foi acoplado a este um encoder angular (As5040), como pode-se observar na Figura 5. O transdutor 
escolhido foi um encoder magnético de 12 bits, que usa a direção e o sentido das linhas de campo geradas pelo imã acoplado ao eixo do motor, como base de coleta de informações. 
Por ser magnético há a vantagem de não ser essencial o contato direto entre transdutor e motor.

<p align="center">
  <img src="https://user-images.githubusercontent.com/82101091/114220993-0fb04180-9943-11eb-92c4-75b3e8ffb525.png" />
</p>

Além do encoder, foi acrescentado o sensor indutivo de modelo “Pnp Lj12a3-4-z/by”, o qual indica o fim do curso do braço mecânico, para que ocorra a movimentação na extensão angular correta, evitando assim um possível travamento do motor. 

<p align="center">
  <img src="https://user-images.githubusercontent.com/82101091/114221091-3c645900-9943-11eb-81cc-514caf2a6271.png" />
</p>

Em função dos requisitos do projeto, foi selecionado o sensor de pressão MPX5010DP da NXP, que é próprio para utilização em equipamentos médicos. O sensor é capaz de medir a pressão diferencial entre o ambiente e o pulmão do paciente. A utilização da medida de pressão diferencial é adequada, pois possibilita a operação do equipamento independentemente da pressão atmosférica local (altitude). A escala de pressão vai de 0 a 102 cmH2O, que engloba a faixa de pressão necessária para monitorar o ciclo respiratório de um humano.
A respiração do paciente é controlada por meio do aperto do AMBU, através de um braço mecânico que é acoplado ao eixo do motor. O volume de ar enviado ao paciente por meio de um circuito respiratório, é proporcional à compressão do AMBU. Enquanto a inspiração do paciente depende do volume de ar entregue pelo AMBU, a expiração ocorre de forma passiva a partir da abertura da válvula exalatória, ou seja, sem interferência do equipamento, sendo apenas monitorada a pressão para o fechamento da válvula exalatória, com a finalidade de manter a PEEP. O AMBU dispõe de uma  válvula “bico de pato”, que foi mantida com o intuito de evitar o retorno de ar do paciente para o mesmo. Durante a inspiração a válvula exalatória é fechada para que o volume de ar deslocado pelo AMBU chegue totalmente ao paciente e durante o ciclo de expiração a válvula é aberta, permitindo a saída do ar para fora do circuito respiratório. Para acionar a válvula exalatória foi utilizado um transistor TIP122, que é controlado pelo módulo Arduino
