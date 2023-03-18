#ifndef _FOPS_H_
#define _FOPS_H_
#include "variables.h"
void initTree(tree&);
void initNode(tree&,tree&);
int tree_height(tree);
void read(tree,FILE*);
#endif
