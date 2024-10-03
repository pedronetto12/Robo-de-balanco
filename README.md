# Robô de Balanço com Controlador PID

Este projeto implementa um **robô de balanço** (self-balancing robot) que utiliza um controlador PID para manter seu equilíbrio. O sistema é composto por um sensor giroscópio, dois motores de passo e dois drivers de motor de passo. A combinação desses componentes permite que o robô se mantenha estável e corrige sua inclinação automaticamente.

## Componentes Utilizados

- **Controlador PID**: Responsável por ajustar a posição do robô de maneira precisa, corrigindo variações de inclinação com base nas leituras do giroscópio.
  
- **Sensor Giroscópio**: Mede o ângulo de inclinação do robô e envia essas informações ao controlador PID para que ele possa tomar decisões de correção.

- **Motores de Passo**: Dois motores de passo controlam o movimento do robô, permitindo que ele ajuste sua posição com precisão.

- **Drivers dos Motores de Passo**: Controlam os motores de passo, garantindo que eles recebam os sinais e a potência corretos para movimentar o robô de forma estável.

## Funcionamento

O robô de balanço utiliza o **sensor giroscópio** para medir constantemente o ângulo de inclinação. Com base nessas medições, o **controlador PID** ajusta a velocidade e a direção dos **motores de passo**, a fim de corrigir a inclinação e manter o equilíbrio do robô.

### O controlador PID ajusta três parâmetros:
- **Proporcional (P)**: Corrige a inclinação atual.
- **Integral (I)**: Ajusta com base no acúmulo de erros passados.
- **Derivativo (D)**: Antecipação de inclinações futuras com base na taxa de mudança atual.

Os dois **motores de passo** trabalham em conjunto para realizar os ajustes necessários e manter o robô equilibrado, evitando quedas.


