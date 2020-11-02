# votacao

Software para leitura, decodificação e contagem do votos de uma botoeira com três botões físicos mas que utiliza apenas duas entradas do Arduino.

Este programa contém:

## 1) Leitura das entradas codificadas:
----------------------------------------------
Para diminuir a quantidade de entradas utilizadas, foi implementada uma codificação
para detectar o botão acionado:

Tabela:

D1 D0 Informação/Botão

0  0  OK

0  1  Calor

1  0  Frio

1  1  Saúde


*Objetivo*: Ler essas entradas codificadas

## 2) Decodificação das entradas usadas pelas botoeiras:
-------------------------------------------------------------------

*Objetivo*: Decodificar as entradas D0 e D1 e captar a informação de qual botão foi acionado.

Tabela:

D1 D0 Informação/Botão

0  0  OK

0  1  Calor

1  0  Frio

1  1  Saúde


### 3) Contabilizar os votos por X tempo e apresentar resultados
------------------------------------------------------------------
