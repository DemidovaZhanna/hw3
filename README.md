## Assignment 3: study the approximation of NP-hard problem solutions
### Part 1

В качестве NP-полной задачи была выбрана задача выполнимости булевых формул 3-satisfiability
(3SAT.h). Приведем формальную постановку данной задачи. 

Дано:  
**Множество переменных** $X = \{x_1, x_2, ..., x_n\}$  
**Множество клауз** $C_1, C_2, ..., C_m : \quad C_i = (l_{i1} \vee l_{i2} \vee l_{i3}), \quad$ 
где $l_{ij} \in \{ x_j, &not;x_j\}$

Найти $\{x_1, x_2, ..., x_n\}: $ $$\forall i \in \{1, 2, ..., m\}: \quad (C_i = l_{i1} \vee l_{i2} \vee l_{i3}) \quad 
and \quad (C_i = true)$$
Другими словами, $F = C_1 \wedge C_2 \wedge \ ... \ \wedge C_m = true$

Стандартное решение задачи выполнимости булевых формул 3-SAT имеет сложность $\theta (2^n \cdot m)$.
Сложность решения 3-SAT с использованием MiniSat в худшем случае составляет  $\theta (2^n)$, т.е. SAT 
остаётся NP-полной задачей, даже с оптимизациями CDCL, однако реальная сложность ближе к $\theta (n \cdot m)$,
где $m -$ число клауз, $n -$ число переменных.




### Part 2