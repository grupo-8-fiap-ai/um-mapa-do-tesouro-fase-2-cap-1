# TRABALHO - SIMULAÇÃO DE SISTEMA DE IRRIGAÇÃO INTELIGENTE - 1TIAOA - Fase 2 - Cap04

## CULTURA: TOMATE

Para a cultura do tomate, a irrigação automática será acionada somente quando a umidade do solo estiver abaixo do limite mínimo de umidade definido para a simulação, indicando necessidade de reposição hídrica. A umidade do solo, simulada pelo sensor DHT22, será o critério principal para o acionamento do sistema.

Além disso, a irrigação só ocorrerá se o pH do solo, simulado pelo LDR, estiver na faixa aceitável de 5,8 a 7,2, com desempenho ideal entre 6,2 e 6,8, e se houver condição nutricional mínima adequada, caracterizada por níveis satisfatórios de pelo menos dois dos três nutrientes monitorados: nitrogênio, fósforo e potássio.

A irrigação não será acionada quando a umidade do solo estiver adequada ou alta, devido ao risco de saturação e prejuízo às raízes, nem quando o pH estiver fora da faixa recomendada ou os nutrientes estiverem insuficientes, pois essas condições comprometem o aproveitamento da água e o desenvolvimento do tomateiro.