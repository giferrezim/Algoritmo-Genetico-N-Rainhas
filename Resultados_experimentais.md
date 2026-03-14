## Resultados Experimentais

O algoritmo genético foi executado para diferentes tamanhos de tabuleiro do Problema das N-Rainhas. Para cada instância, foram realizadas três execuções independentes, registrando-se o número de gerações necessárias até a convergência.  

A partir desses dados, foram calculadas as médias e os desvios padrão para cada instância, permitindo avaliar o desempenho e a estabilidade do algoritmo. Os resultados foram comparados com aqueles apresentados na pesquisa de Ribeiro.  

**Tabela — Comparação entre o número médio de gerações até a convergência obtido neste trabalho e os resultados reportados por Ribeiro.**

| N | Média (Ferrezim) | Média (Ribeiro) | Desvio padrão (Ferrezim) | Desvio padrão (Ribeiro) |
|---:|---:|---:|---:|---:|
| 25 | 51 | 717.00 | 9.71 | 669.01 |
| 24 | 37 | 298.67 | 7.77 | 221.41 |
| 23 | 38 | 220.33 | 1.53 | 122.81 |
| 22 | 34 | 119.33 | 9.45 | 92.64 |
| 21 | 29 | 1015.33 | 4.00 | 1510.10 |
| 20 | 18 | 315.33 | 11.79 | 364.70 |
| 19 | 19 | 1109.33 | 6.03 | 853.56 |
| 18 | 16 | 625.33 | 6.11 | 448.72 |
| 17 | 16 | 112.33 | 3.21 | 61.70 |
| 16 | 15 | 131.00 | 5.00 | 101.95 |
| 15 | 6 | 324.00 | 1.53 | 303.08 |
| 14 | 6 | 130.67 | 5.29 | 155.34 |
| 13 | 6 | 64.33 | 3.21 | 52.08 |
| 12 | 4 | 179.33 | 1.53 | 258.65 |
| 11 | 3 | 45.33 | 1.00 | 42.97 |
| 10 | 1 | 819.33 | 0.58 | 847.79 |

Os resultados indicam que o algoritmo genético proposto encontra soluções válidas com menor número de gerações em todas as instâncias avaliadas, evidenciando melhora de desempenho em relação à implementação de referência.
