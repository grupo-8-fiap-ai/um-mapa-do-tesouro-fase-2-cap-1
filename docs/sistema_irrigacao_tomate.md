# TRABALHO - SIMULAÇÃO DE SISTEMA DE IRRIGAÇÃO INTELIGENTE

## CULTURA: TOMATE

Para a cultura do tomate, a irrigação automática será acionada somente quando a umidade do solo estiver abaixo do limite mínimo de umidade definido para a simulação, indicando necessidade de reposição hídrica. A umidade do solo, simulada pelo sensor DHT22, será o critério principal para o acionamento do sistema.

Além disso, a irrigação só ocorrerá se o pH do solo, simulado pelo LDR, estiver na faixa aceitável de 5,8 a 7,2, com desempenho ideal entre 6,2 e 6,8, e se houver condição nutricional mínima adequada, caracterizada por níveis satisfatórios de pelo menos dois dos três nutrientes monitorados: nitrogênio, fósforo e potássio.

A irrigação não será acionada quando a umidade do solo estiver adequada ou alta, devido ao risco de saturação e prejuízo às raízes, nem quando o pH estiver fora da faixa recomendada ou os nutrientes estiverem insuficientes, pois essas condições comprometem o aproveitamento da água e o desenvolvimento do tomateiro.

## PSEUDOCÓDIGO DO SISTEMA

```text
Início

Ler N, P, K
Ler pH_simulado
Ler umidade_do_solo

nutrientes_adequados ← 0

Se N = adequado então nutrientes_adequados ← nutrientes_adequados + 1
Se P = adequado então nutrientes_adequados ← nutrientes_adequados + 1
Se K = adequado então nutrientes_adequados ← nutrientes_adequados + 1

Se umidade_do_solo < limite_minimo_solo então
    Se (pH_simulado >= limite_minimo_ph) E (pH_simulado <= limite_maximo_ph) então
        Se nutrientes_adequados >= 2 então
            ligar_relé
            status ← "Irrigação acionada"
        Senão
            desligar_relé
            status ← "Bloqueio por deficiência nutricional"
        FimSe
    Senão
        desligar_relé
        status ← "Bloqueio por pH inadequado"
    FimSe
Senão
    desligar_relé
    status ← "Solo com umidade suficiente"
FimSe

Exibir status

Fim
```

## INTERPRETAÇÃO DOS COMPONENTES E CRITÉRIOS DO SISTEMA

### Botão N (verde)
Representa o nível de Nitrogênio no solo.

- Pressionado = nutriente adequado
- Não pressionado = nutriente inadequado

### Botão P (amarelo)
Representa o nível de Fósforo no solo.

- Pressionado = nutriente adequado
- Não pressionado = nutriente inadequado

### Botão K (vermelho)
Representa o nível de Potássio no solo.

- Pressionado = nutriente adequado
- Não pressionado = nutriente inadequado

### Critério dos nutrientes
O solo será considerado com condição nutricional mínima adequada quando pelo menos dois dos três nutrientes monitorados, N, P e K, estiverem adequados.

### LDR
Representa o pH do solo de forma simulada. Sua leitura analógica será convertida para uma escala de 0 a 14, correspondente à escala de pH. Após essa conversão:

- abaixo de 5,8 = solo muito ácido, pH inadequado
- entre 5,8 e 7,2 = faixa aceitável para o tomate
- acima de 7,2 = solo alcalino, pH inadequado

**Obs.:** A faixa considerada ideal para o tomate será entre 6,2 e 6,8, embora o sistema aceite valores entre 5,8 e 7,2.

### DHT22
Representa a umidade do solo na simulação. Os valores serão interpretados da seguinte forma:

- abaixo de 40% = umidade baixa, solo seco, condição elegível para irrigação
- entre 40% e 70% = umidade adequada, sem necessidade de irrigação
- acima de 70% = umidade alta, solo muito úmido, irrigação bloqueada para evitar excesso de água

### Relé
Representa a bomba de irrigação e será ativado apenas quando todas as condições abaixo forem satisfeitas:

- a umidade estiver abaixo de 40%;
- o pH estiver na faixa aceitável de 5,8 a 7,2;
- pelo menos 2 dos 3 nutrientes, N, P e K, estiverem adequados.

**Obs.:** Se alguma dessas condições não for atendida, o relé permanecerá desligado.
