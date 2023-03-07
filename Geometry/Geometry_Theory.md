## Basics

Por definição, o produto escalar define o cosseno entre dois vetores:

cos(a, b) = ( a * b ) / ( ||a|| * ||b|| )

a * b =  cos(a, b) * ( ||a|| * ||b|| )

O sinal do produto vetorial de A com B indica a relação espacial entre os vetores A e B.

cross(a, b) > 0 -> ***B*** está a esquerda de ***A***.

cross(a, b) = 0 -> ***B*** é colinear ao ***A***.

cross(a, b) > 0 -> ***B*** está a direita de ***A***.

A magnitude do produto vetorial de A com B é a área do paralelogramo formado por A e B. Logo, a metade é a área do triângulo formado por A e B.

#### Área de qualquer polígono, convexo ou não.

Definindo um vértice como 0, e enumerando os demais de [1 a N), calcula-se a área do polígono como o somatório da metade de todos os produtos vetorias entre o 0 e os demais.

```
For i in [1, N) :
    Area += v0 ^ vi
Area = abs(Area)
```

*Lembre-se* de pegar o módulo da área para ignorar o sentido escolhido.

## Lattice Points

*Boundary points:* Use gcd( abs(a.x, b.x), abs(a.y, b.y) ) for each pair of adjacent points.  

*Interior points:* Use Pick's Theorem: 
```
Area_of_polygon = interior_points + boundary_points/2 - 1
```