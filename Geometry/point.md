## Point Struct

```cpp
struct Point{
    int x, y;
    int ind; // idx

    Point(){
        this->x = 0;
        this->y = 0;
    }
    
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }

    Point operator -(const Point& b) const{
        return Point{x - b.x, y - b.y};
    }

    Point operator +(const Point& b) const{
        return Point{x + b.x, y + b.y};
    }

    int operator *(const Point& b) const{ // dot product
        return x*b.x + y*b.y;
    }
 
    int operator ^(const Point& b) const{ // cross product
        return x*b.y - y*b.x;
    }

    int dot(const Point& b, const Point&c) const{ // dot product with diferent base
        return (b - *this) * (c - *this);
    }

    int cross(const Point& b, const Point&c) const{ // cross product with diferent base
        return (b - *this) ^ (c - *this);
    }
 
    bool operator <(const Point& b) const{
        return make_pair(x,y) < make_pair(b.x,b.y);
    }

    bool operator ==(const Point &o) const{
        return (x == o.x) and (y == o.y);
    }

};
```

#### Teoria:

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
