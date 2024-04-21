# Competitive-programming
Algoritmos e ideias de Programação Competitiva

Créditos para: [Tiagosf00](https://github.com/Tiagosf00), [Cebolinha](https://quirino.net/), [Kactl](https://github.com/kth-competitive-programming/kactl), [BrunoMonteiro](https://github.com/brunomaletta/Biblioteca)

## Linux Alias

```bash
alias comp='g++ -std=c++17 -O2 -g3 -ggdb3 -fsanitize=address,undefined -Wall -Wextra -Wshadow -Wconversion -o test'
```

*-Wall -Wextra -Wconversion -Wshadow* shows warnings

*-fsanitize=address,undefined* shows errors for memory access error and undefined behaviour (overflow)

*-g3 -ggdb3* shows more details for compilation errors (line that ocurred error)

## KACTL notebook

```bash

sudo apt-get install texlive-latex-base

sudo apt-get install texlive-latex-extra

```

## Checklist

**Thinking about solution:**

- Immediately play with the sample cases, you may have understood the problem wrong

- Pay close attention to the constraints

- Always consider doing Binary Search on the answer

- Consider Offline processing

**Before Submitting:**

- Even if the test cases pass, make sure your code is at least doing something

- If the test cases are too simple, come up with a couple extra ones

- Check if constants are big enough

- Check time and memory limits

- Submit the right file

**General:**

- #define int long long

- Fast IO & endl

- Consider negative and null values. Check if default values used, such as (-1 or INF) can be valid values for the problem

- Be very careful when copy pasting, check you've changed everything that needs changing

- Be wary of special cases, and when you do define one, be very sure you've correctly identified the full extent of their implications
STL

- Don't call .back(), .front(), .top() on empty containers

- Don't change a container as you iterate through it (Even accessing a map may change it)

- Always make sure your iterators are valid

**Graphs:**

- Add edges both ways if the graph is bidirectional