# esp32-rpm-motor-indutivo-24v

# Leitura de RPM de Motor Trifásico com ESP32, Sensor Indutivo 24Vcc e Relé de Interface 24Vcc

Assista o video completo clicando aqui: https://youtu.be/jWMdfTTF_Tk

Projeto prático desenvolvido na bancada da PoularasTech demonstrando como realizar a leitura de rotação (RPM) de um motor de indução trifásico usando um sensor indutivo 24Vcc integrado ao ESP32, além do acionamento de um relé de interface 24Vcc via Monitor Serial e acompanhamento em tempo real alterando a frequência de giro do motor.

> Aprendizado na prática: Este repositório acompanha o vídeo prático do canal PoularasTech, cobrindo o diagrama eletroeletrônico, as ligações físicas, a análise do código na IDE do Arduino e os testes reais em bancada.

---

## O que foi abordado no projeto

> Leitura de RPM em tempo real: Captura de pulsos gerados pelo sensor indutivo 24Vcc a cada passagem do alvo metálico no eixo/acoplamento do motor e cálculo da rotação por minuto (RPM).
  
> Diagrama eletroeletrônico e ligações físicas: Condicionamento e compatibilização de sinais entre o barramento industrial de 24Vcc (sensor e bobina do relé de interface) e os pinos digitais de 3.3V do ESP32 (evitando sobretensão nas GPIOs).
  
> Código na IDE do Arduino: Estrutura clara para leitura de pulsos, atualização periódica do RPM e comandos pelo Monitor Serial para acionar/desligar o relé de interface 24Vcc.
  
> Testes em bancada: Alteração da frequência do motor na prática, observação do comportamento do RPM em tempo real e chaveamento do relé direto pelo Monitor Serial.

---

Aviso de Segurança (24Vcc e Circuitos Industriais)

As GPIOs do ESP32 operam em 3.3V. Nunca ligue diretamente um sinal de 24Vcc sem o circuito adequado de rebaixamento/isolamento/condicionamento de sinal.

Utilize sempre fonte adequada, proteções e atenção ao trabalhar próximo a partes giratórias de motores e circuitos energizados.

Conecte-se com a PoularasTech

Site: https://poularastech.com
Instagram: @poularastech
GitHub: https://github.com/poularastech-hash

Licença
Este projeto está distribuído sob a licença MIT. Veja o arquivo LICENSE para mais detalhes.
