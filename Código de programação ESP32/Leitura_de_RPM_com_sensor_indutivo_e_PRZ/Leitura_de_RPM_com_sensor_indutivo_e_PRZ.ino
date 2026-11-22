/*
MIT License

Copyright (c) 2026 PoularasTech Mecatronica

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

String comando;

const uint pinoRele = 21;  // Saída digital GPIO 21 no ESP32 (ESSE É O RELÉ DE INTERFACE)
const uint pinoInterrupcao = 5; // Entrada digital GPIO 5 no ESP32 (ESSE É O SENSOR INDUTIVO)
volatile unsigned long pulsos = 0; // Alterada pela ISR: sempre 'volatile'

unsigned long tempoAnterior = 0;
const unsigned long intervalo = 1000000; // 1 segundo em microssegundos (1.000.000 us)
const float pulsosPorVolta = 1.0;      // 1 pulso = 1 rotação completa

volatile unsigned long ultimoPulsoUs = 0;
const unsigned long minIntervaloUs = 100; // Ajuste conforme a rotação máxima

void IRAM_ATTR contarPulso() {
  unsigned long agora = micros();
  if (agora - ultimoPulsoUs >= minIntervaloUs) {
    pulsos++;
    ultimoPulsoUs = agora;
  }
}


void setup() {
  pinMode(pinoRele, OUTPUT);
  digitalWrite(pinoRele, LOW);
  pinMode(pinoInterrupcao, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinoInterrupcao), contarPulso, FALLING);
  Serial.begin(115200); // Mais rápido para não atrasar o loop em frequências maiores
  tempoAnterior = micros();
}

void loop() {
  unsigned long tempoAtual = micros();
  unsigned long deltaTempoUs = tempoAtual - tempoAnterior;

  if (deltaTempoUs >= intervalo) {
    // 1. Copia os pulsos do intervalo e zera o contador dentro da seção crítica
    // Isso evita que um pulso chegue exatamente entre a leitura e o reset
    noInterrupts();
    unsigned long copiaPulsos = pulsos;
    pulsos = 0;
    interrupts();

    // 2. Atualiza a referência de tempo para o próximo ciclo
    tempoAnterior = tempoAtual;

    // 3. Converte o tempo real decorrido de microssegundos para segundos
    float deltaTempoSeg = deltaTempoUs / 1000000.0;

//A frequencia pode ser calcula dessa forma:

    // 4. Calcula frequência (Hz = pulsos por segundo)

    //float frequencia = (deltaTempoSeg > 0.0) ? (copiaPulsos / deltaTempoSeg) : 0.0;

//Ou dessa forma:

    // 4. Calcula frequência (Hz = pulsos por segundo) e RPM (rotações por minuto)

    float frequencia = 0.0;
    float copiafreq = 0.0;
    
    if (deltaTempoSeg > 0.0) {
      frequencia = copiaPulsos / deltaTempoSeg;
      copiafreq = frequencia*2;
    } else {
      frequencia = 0.0;
      copiafreq = 0.0;
    }

    float rpm = (frequencia / pulsosPorVolta) * 60.0;



    Serial.print("Tempo decorrido (s): ");
    Serial.println(deltaTempoSeg, 3);
    Serial.print("Pulsos no intervalo: ");
    Serial.println(copiaPulsos);
    Serial.print("Frequencia eletrica (motor 4 polos): ");
    Serial.print(copiafreq, 2);
    Serial.println(" Hz");
    Serial.print("RPM: ");
    Serial.println(rpm, 1);
    Serial.println("-------------------------");

    if (Serial.available() > 0) {
    comando = Serial.readStringUntil('\n');
    comando.trim(); // Remove espaços em branco

    if (comando == "ligar") {
      digitalWrite(pinoRele, HIGH); // Liga o relé
      Serial.println("Relé Ligado");
    } else if (comando == "desligar") {
      digitalWrite(pinoRele, LOW); // Desliga o relé
      Serial.println("Relé Desligado");
    }
    }
  }
}