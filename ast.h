#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct AST
{
    struct AST *left;
    struct AST *right;
    char OP[100];
    int op;
} AST;

struct AST *buildAST(int op, struct AST *left, struct AST *right, char OP[100])
{
    struct AST *ast_node = (AST *)malloc(sizeof(struct AST));

    ast_node->op = op;
    strcpy(ast_node->OP, OP);

    ast_node->left = left;
    ast_node->right = right;

    return ast_node;
}

int evalAST(struct AST *root)
{
    if (root->left == 0 && root->right == 0)
    {
        if (strstr(root->OP, "NUMBER"))
        {
            return root->op;
        }
        else
        {
            return 0;
        }
    }

    if (strstr(root->OP, "PLUS"))
    {
        return evalAST(root->left) + evalAST(root->right);
    }

    if (strstr(root->OP, "MINUS"))
    {
        return evalAST(root->left) - evalAST(root->right);
    }

    if (strstr(root->OP, "MULTIPLY"))
    {
        return evalAST(root->left) * evalAST(root->right);
    }

    if (strstr(root->OP, "DIVIDE"))
    {
        return evalAST(root->left) / evalAST(root->right);
    }
}

#endif