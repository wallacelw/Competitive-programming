# Classic Segtree

Data structure that creates parent vertices for a linear array to do faster computation with binary agregation. \

## Details

**0 or 1-indexed**, depends on the arguments passed on to the constructor \

Uses a **struct node** to define node/vertex properties. *Default:* psum \

Uses a **merge function** to define how to join nodes \

## Parameters

**left** and **right**: parameters that are the range limits for the range query \

**l** and **r**: are auxilary variables used for delimiting a vertex boundaries \

**idx**: index of the leaf node that will be updated \

**val**: value that will be inserted to the idx node \

## Atributes

**Tree**: node array \

**v**: vector that are used for leaf nodes \

## Methods

**build(l, r, i)**: From **v** vector, constructs Segtree \

**point_update(idx, l, r, i, val)**: updates leaf node with *idx* index to *val* value. No return value \

**range_query(left, right, l, r, i)**: does a range query from *left* to *right* (inclusive) and returns a node with the result \

## Requires
MAX variable \