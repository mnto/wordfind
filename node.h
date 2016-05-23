#include <cstdlib>

#ifndef NODE
#define NODE

typedef int elem;

struct node {
  elem data;
  node *left;
  node *right;
  node(const elem & data, node *left=NULL, node *right=NULL);
};

#endif
