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

```
nr_of_objects N
target_weight W
Array Memory[N , W] ; Assume all values of Memory initially equals to -1
Array Values[I] ; Values of each object in knapsack
Array Weigths[I] ; Weigth of each object in knapsack

def knapsack_solver(nr_of_considered_objects j, current_target_weight w):
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

solution is Memory[N, W]
```

## Dimostrazione correttezza

La dimostrazione procede con ragionamento induttivo:

- Caso in cui il numero di oggetti considerati sia zero, o il peso limite sia nullo, in questo caso il valore contenuto nello zaino è nullo.
- Nello step ennesimo, in cui il peso limite non sia nullo, si valuta il peso dell'oggetto ennesimo, se questo supera il peso limite, non può essere aggiunto,
  pertanto la soluzione al sottoproblema è uguale al risultato del sottoproblema in cui non viene considerato l'oggetto attuale.
  Nel caso opposto la soluzione al sottoproblema è il massimo tra il sottoproblema senza considerare l'oggetto attuale,
  o il sottoproblema in cui si ha un peso limite pari al peso limite attuale meno il peso dell'oggetto considerato, e a cui viene aggiunto il valore del primo oggetto.
- Per ipotesi induttiva i sottoproblemi sono calcolati correttamente usando la medesima procedura, pertanto anche per il problema posto la soluzione è ottimale.

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

Si immagini il problema come un albero, per cui alla radice (livello i = 1) si ha la soluzione ricercata, ovvero la funzione con argomento $(N,W)$,
ad ogni livello inferiore dell'albero si considera un elemento in meno, pare chiaro fin da subito che il numero massimo di livelli pertanto sia $N$,
il numero di nodi presenti al livello i è pari alle possibili distinte combinazioni di peso ottenute prendendo $W$ e sottraendogli il peso degli oggetti dall'indice $N$
fino all'oggetto $ N - i $, avendo però peso non negativo, soluzione con peso limite congruente costruiscono un problema analogo.
Nel caso peggiore, ovvero in cui tutti gli oggetti abbiano peso unitario, i nodi di un livello sono proprio $ i $,
fintanto che il peso risultante è positivo, dopodichè è $W$. Questa condizione di saturazione si raggiunge quando $i = W$.
Quindi il numero totale dei nodi da valutare è:

$$
\sum_{i=1}^{W-1} (i) + \sum_{i = W}^N W\\
\frac{1}{2} W (W - 1) + (N - W) W\\
N W - \frac{1}{2}W(W - 1)
$$

Pertanto si dimostra che il costo temporale è $O(NW)$

Se non si fosse usata la programmazione dinamica, il numero di chiamate da effettuare sarebbe stata $O(2^N)$,
infatti sarebbe sempre necessario calcolare l'elemento precedente fino a raggiungere il caso base,
che nel caso peggiore richiede la valutazione della funzione due volte per livello.


