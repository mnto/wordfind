#include <iostream>
#include <cstdlib>
#include <cmath>
#include "node.h"

using namespace std;

node::node(const elem & data, node *left, node *right) : 
  data(data), left(left), right(right) {}

node * btree_copy(node * tree) 
{
  if (tree == NULL)
    return NULL;
  else
    return new node(tree->data, 
		btree_copy(tree->left),
		btree_copy(tree->right));
}

void destroy_tree(node * tree)
{
  // delete all nodes dominated by tree.
  // without loss of generality (tree might be NULL)
  if (tree) {
    destroy_tree(tree->left);    
    destroy_tree(tree->right);
    delete tree;
  }
}


void prune(node * & tree)
{
  // pre: tree points to a node.  (tree isn't NULL)
  // pre: one or both of tree->left and tree->right is NULL.
  // post:  the node (that tree points to)  is deleted
  // post: tree is either NULL or points to the node formerly to the left or right.
  
  node *xp = tree;
  if (xp->left) 
    tree = xp->left;
  else
    tree = xp->right;
  delete xp;
}


node * &  bst_search(int target, node * & tree)
{
  if (!tree or tree->data == target)
    return tree;
  if (target < tree->data)
    return bst_search(target, tree->left);
  else
    return bst_search(target, tree->right);
}

bool prunable(node * tree)
{
  return tree->left == NULL or tree->right == NULL;
}


node * & find_smallest(node * & tree)
{
  // tree is not null
  if (tree->left == NULL)
    return tree;
  return find_smallest(tree->left);
}

void bst_remove(int target, node * & tree)
{
  node * & the_node = bst_search(target, tree);
  if (not the_node)
    return;
  if (prunable(the_node))
    prune(the_node);
  else {
    node * & smallest = find_smallest(the_node->right);
    the_node->data = smallest->data;
    prune(smallest);
  }
}




size_t max(size_t a, size_t b)
{
  return a > b ? a : b;
}

size_t height2(node *tree)
{
  // Drew's more elegant solution
  if (tree == NULL)
    return 0;
  return 1 + max(height2(tree->left), height2(tree->right));
}

size_t height(node *tree)
{
  // Prof. Campbell's cool demo of embedding assignments.  (A very C-like thing
  // to do.
  size_t lh, rh;
  if (tree == NULL)
    return 0;
  if ((lh = height(tree->left)) > (rh = height(tree->right)))
    return 1 + lh;
  else
    return 1 + rh;
}

void print_tree(node *tree, size_t depth)
{
  // print tree, sideways on the screen.

  if (tree==NULL) 
    return;
  print_tree(tree->right, depth + 1);
  for (size_t i=0;i < depth; i++)
    cout << "   ";
  cout << tree->data << endl;
  print_tree(tree->left, depth + 1);
}

size_t count_nodes(node *tree)
{
  // return number of nodes in a binary tree
  return (!tree) ? 0 : 1 + count_nodes(tree->left) + count_nodes(tree->right);
}

node * random_tree(size_t k)
{
  // rand() % 100 gives [0 .. 99]
  // rand() % n   gives [0 .. n-1]

  size_t kp; //  that's k'  (!)

  if (k == 0)
    return NULL;
  kp = rand() % k;
  return new node(rand() % 100,
		  random_tree(kp),
		  random_tree(k - kp - 1));
}


int main()  // just for testing
{
  srand(time(NULL));
  node *mytree = new node(83, 
			  new node(20, 
				   new node(38),
				   new node(0)),
			  new node(7,
				   new node(99,
					    NULL,
					    new node(17,
						     NULL,
						     new node(38))),
				   new node(57)));

  //cout << height(mytree) << endl;
  cout << endl << endl << endl;
  //  print_tree(mytree, 0);

  size_t total_heights = 0;
  const size_t N = 500;
  const size_t M = 50000;
  for (size_t i = 0; i < N; i++) {
    cout << i << endl;
    mytree = random_tree(M);
    total_heights += height(mytree);
  }
  cout << "Avg. height: " << total_heights / N << endl;
  cout << "Ideal answer = " << log(M) / log(2.0) << endl;
  

}
