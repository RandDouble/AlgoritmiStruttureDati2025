---
author: Stefano Pilosio
---


# Costo computazionale in tempo per il problema dello zaino 1-0

## Formulazione Problema

Il problema è così formulato:

> Sia dato uno zaino con capacità di sopportare un peso $W$ e siano dati $N$ oggetti,
  ciascuno con un valore $Values[i]$ e un peso $Weights[i]$, $i \in {1,...,N}$.
  Si calcoli il valore massimo ottenibile sfruttando gli oggetti, senza eccedere il peso dello zaino.

## Algoritmo di risoluzione proposto

La soluzione adottata per risolvere il problema dello zaino ha la seguente forma:

```python
N : nr_of_objects
W : target_weight 
Memory[N , W] : Array # Assume all values of Memory initially equals to -1
Values[I] : Array # Values of each object in knapsack
Weigths[I] : Array # Weigth of each object in knapsack

def knapsack_solver(
    j : nr_of_considered_objects,
    w :  current_target_weight
):
    if j == 0 or w == 0:
        Memory[j, w] = 0
        return

    if Memory[j-1, w] == -1:
        knapsack_solver(j-1, w)

    if Weigths[j] > w:
        Memory[j, w] = Memory[j-1, w]
    else:
        if Memory[j-1, w-Weights[j]] == -1:
            knapsack_solver(j-1, w-Weights[j])
        Memory[j, w] = max(Memory[j-1, w], Memory[j-1, w-Weights[j]] + Values[j])

knapsack_solver(N, W)

# solution is Memory[N, W]
```

## Analisi del Costo temporale

Il problema dello zaino è un problema NP completo, pertanto qualunque soluzione esatta avrà un costo temporale esponenziale.
Tuttavia sfruttando la programmazione dinamica si riesce ad abbattere il costo temporale a quasi polinomiale,
acquisendo un corrispettivo costo in spazio.

La soluzione proposta sfrutta sia la ricorsione che la programmazione dinamica.

L'algoritmo proposto cerca la soluzione analizzando gli $N \times W$ sottoproblemi,
partendo nel caso base, in cui il peso sopportato dallo zaino è nullo, o non si stanno considerando oggetti.
Il problema di ordine successivo, in cui si considera un elemento aggiuntivo o si ha un peso sopportato non nullo,
è costruito considerando un elemento e valutando se questo rispetta i vincoli di peso, se la condizione non si verifica,
allora la soluzione al problema è uguale al caso di ordine inferiore, altrimenti si considera l'aggiunta dell'elemento.
Ma siccome l'elemento precedente è già stato calcolato, allora il numero di chiamate da effettuare della funzione si riduce a $O(NW)$.

Se non si fosse usata la programmazione dinamica, il numero di chiamate da effettuare sarebbe stata $O(2^N)$,
infatti sarebbe sempre necessario calcolare l'elemento precedente fino a raggiungere il caso base,
che nel caso peggiore richiede la valutazione della funzione due volte per livello.


