#ifndef INFIXEXP_H
#define INFIXEXP_H


ExpTree treeInfixExpression(List *lp, ExpTree *tp);
ExpTree evalNumberOrBracket(List *lp);
void infExpTrees();

#endif