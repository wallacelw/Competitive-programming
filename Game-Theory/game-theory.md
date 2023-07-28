## Nim Game

**Reference:** https://cp-algorithms.com/game_theory/sprague-grundy-nim.html

- There are *n* piles (heaps), each one with *x_i* stones. 

- Each turn, a players must remove *t* stones (non-zero) from a pile, turning *x_i* into *y_i*. 

- The game ends when it's impossible to make any more moves and the player without moves left lose.

## Bouton's Theorem

"Let *s* be the *xor-sum* value of all the piles sizes, a state **s=0** is a losing position and a **state s!=0** is a winnig position".

#### Proof

- When *s=0*, a move reduces a pile with size x to y (y < x). 

        t = s xor x xor y = 0 xor x xor y = x xor y
    
        (y < x) 
        => t = (x xor y) != 0 (valid move)
        => s' != s 
        => s' != 0. 
        => becomes a wining state
        => was a losing state

- When *s!=0*, there is at least one pile x, with the *d* bit set. d is the msb bit of s.

        reduce this pile x to y, consider y = x xor s

        (x xor s <= x) and (s != 0)
        => y = (x xor s) < x
        => valid move

        t = s xor x xor y = s xor x xor (x xor s) = 0

## Interpretation as a DAG

States of the game are Vertices

Moves are the transition between States, therefore, the Edges

If a State has no outgoing edges, it's a dead end and a losing state

## Nim with Increases

Consider a modification of the classical nim game: a player can now add stones to a chosen pile. This extra rule needs to keep the game acyclic (finite game).

**Lemma:** This move is not used in a winnig strategy and can be ignored when computing if a state is winning.

**Proof:** If a player adds *t* stones in a pile, the next player just needs to remove *t* stones from this pile. Considering that the game is finite and ends sooner or later.

## Sprague-Grundy Theorem

Let's consider a state *v* of a two-player impartial game and let *v_i* be the states reachable from it (where $i \in \{ 1, 2, \dots, k \} , k \ge 0$ ). 

To this state, we can assign a fully equivalent game of Nim with one pile of size *x*. The number *x* is called the Grundy value or nim-value of state *v*.

Moreover, this number can be found in the following recursive way:

$$ x = \text{mex}\ \{ x_1, \ldots, x_k \}, $$ 

where *x_i* is the Grundy value for state *v_i* and the function MEX is the smallest non-negative integer not found in the given set.

Viewing the game as a graph, we can gradually calculate the Grundy values starting from vertices without outgoing edges. Grundy value being equal to zero means a state is losing.

### Application

To calculate the Grundy value of a given state you need to:

    Get all possible transitions from this state

    Each transition can lead to a sum of independent games (one game in the degenerate case). Calculate the Grundy value for each independent game and xor-sum them. Of course xor does nothing if there is just one game.

    After we calculated Grundy values for each transition we find the state's value as the MEX of these numbers.

    If the value is zero, then the current state is losing, otherwise it is winning.

### Example

**Grundy's Game:**

Initially there is only one pile with *x* stones. Each turn, a player must divide a pile into two non-zero piles with different sizes. The player who can't do any more moves loses.

**Degenerate (Base) States:**

*x = 1* (nim-val = 0) (losing)

*x = 2* (nim-val = 0) (losing)

**Other States:**

nim-val = MEX (all transitions)

*(x = 3):*

    {2, 1} -> (0) xor (0) -> 0

    nim-val = MEX({0}) = 1

*(x = 4):*

    {3, 1} -> (1) xor (0) -> 1

    nim-val = MEX({1}) = 0

*(x = 5):*

    {4, 1} -> (0) xor (0) -> 0
    {3, 2} -> (1) xor (0) -> 1

    nim-val = MEX({0, 1}) = 2

*(x = 6):*

    {5, 1} -> (2) xor (0) -> 2
    {4, 2} -> (0) xor (0) -> 0

    nim-val = MEX({0, 2}) = 1