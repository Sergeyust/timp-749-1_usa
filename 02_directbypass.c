#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct tree {
    int value;
    struct tree* right;
    struct tree* left;
} tree;


void init(tree** t)
{
    *t = malloc(sizeof(tree));
    (*t)->right = NULL;
    (*t)->left = NULL;
    (*t)->value = -2147483648;
}

void clean(tree* t)
{
    if (t != NULL)
    {
        if (t->right != NULL)
            clean(t->right);
        if (t->left != NULL)
            clean(t->left);
        free(t);
    }
}

tree* find(tree* t, int value)
{
    if (t->value == value)
        return t;
    else
    {
        if (value < t->value)
        {
            if (t->left != NULL)
                return (find(t->left, value));
            else
                return NULL;
        }
        else
        {
            if (t->right != NULL)
                return (find(t->right, value));
            else
                return NULL;
        }
    }
}

int find_no_out(tree* t, int value)
{
    if (t->value == value)
    {
        printf("_ ");
        if (t->left != NULL)
            printf("%d ", (int)t->left->value);
        else
            printf("_ ");
        if (t->right != NULL)
            printf("%d", (int)t->right->value);
        else
            printf("_");
    }
    else
    {
        if (value < t->value)
        {
            if (t->left != NULL)
            {
                if (t->left->value == value)
                {
                    printf("%d ", (int)t->value);
                    if ((t->left->left) != NULL)
                        printf("%d ", (int)t->left->left->value);
                    else
                        printf("_ ");
                    if ((t->left->right) != NULL)
                        printf("%d", (int)t->left->right->value);
                    else
                        printf("_");
                }
                else
                    return (find_no_out(t->left, value));
            }
            else
                return 1;
        }
        else
        {
            if (t->right != NULL)
            {
                if (t->right->value == value)
                {
                    printf("%d ", (int)t->value);
                    if ((t->right->left) != NULL)
                        printf("%d ", (int)t->right->left->value);
                    else
                        printf("_ ");
                    if ((t->right->right) != NULL)
                        printf("%d", (int)t->right->right->value);
                    else
                        printf("_");
                }
                else
                    return (find_no_out(t->right, value));
            }
            else
                return 1;
        }
    }
    return 0;
}

int insert(tree* t, int value)
{
    if (t->value == -2147483648)
    {
        t->value = value;
        return 0;
    }
    if (t->value == value)
        return 1;
    if (value > (t->value))
    {
        if ((t->right) != NULL)
            return (insert(t->right, value));
        else
        {
            t->right = malloc(sizeof(tree));
            t->right->right = NULL;
            t->right->left = NULL;
            t->right->value = value;
            return 0;
        }
    }
    else
    {
        if ((t->left) != NULL)
            return (insert(t->left, value));
        else
        {
            t->left = malloc(sizeof(tree));
            t->left->right = NULL;
            t->left->left = NULL;
            t->left->value = value;
            return 0;
        }
    }
}

int find_deep(tree* t)
{
    int r_leaf = 0, l_leaf = 0;
    if ((t->right) != NULL)
        r_leaf = find_deep(t->right);
    if ((t->left) != NULL)
        l_leaf = find_deep(t->left);
    if (r_leaf > l_leaf)
        return (r_leaf + 1);
    return (l_leaf + 1);
}

int remove_node(tree** t, int value)
{
    if ((*t)->value == value)
    {
        if ((*t)->right != NULL)
        {
            tree* temp = (*t)->right, * temp2;
            if (temp->left != NULL)
            {
                while (temp->left->left != NULL)
                    temp = temp->left;
                (*t)->value = temp->left->value;
                temp2 = temp->left;
                temp->left = temp2->right;
                free(temp2);
            }
            else
            {
                temp = NULL;
                (*t)->value = (*t)->right->value;
                temp = (*t)->right;
                (*t)->right = (*t)->right->right;
                free(temp);
            }
        }
        else
        {
            tree* temp;
            temp = (*t);
            (*t) = (*t)->left;
            free(temp);
            temp = NULL;
        }
        return 0;
    }
    else
    {
        if (value < ((*t)->value))
        {
            if ((*t)->left != NULL)
                return (remove_node(&((*t)->left), value));
            else
                return 1;
        }
        else
        {
            if (((*t)->right) != NULL)
                return (remove_node(&((*t)->right), value));
            else
                return 1;
        }
    }
}

int remove_min(tree* t)
{
    tree* temp = t, * temp2;
    int val;
    if (temp->left != NULL)
    {
        while (temp->left->left != NULL)
            temp = temp->left;
        val = temp->left->value;
        temp2 = temp->left;
        temp->left = temp2->right;
        free(temp2);
    }
    else
    {
        temp = t->right;
        val = t->value;
        free(t);
        t = temp;
    }
    return val;
}

int rotate_right(tree** t)
{
    if (*t == NULL)
        return 1;
    tree* y = (*t)->right, * x = (*t)->left, * temp = malloc(sizeof(tree));
    if (x != NULL)
    {
        temp->right = (*t);
        temp->left = x->left;
        temp->right->right = y;
        temp->right->left = x->right;
        temp->value = x->value;
        free(x);
        (*t) = temp;
        return 0;
    }
    return 1;
}

int rotate_left(tree** t)
{
    if (*t == NULL)
        return 1;
    tree* x = (*t)->left, * y = (*t)->right, * temp = malloc(sizeof(tree));
    if (y != NULL)
    {
        temp->right = y->right;
        temp->left = (*t);
        temp->left->right = y->left;
        temp->left->left = x;
        temp->value = y->value;
        free(y);
        (*t) = temp;
        return 0;
    }
    return 1;
}

int print_tree(tree* t)
{
    if (t == NULL)
    {
        printf("-\n");
        return 1;
    }
    tree* temp = t;
    int deep = 0, i, j, k, m;
    int* arr;
    deep = find_deep(t);
    arr = (int*)malloc(sizeof(int));
    for (i = 0; i < deep; i++)
    {
        if (i != 0)
        {
            arr = (int*)realloc(arr, i * sizeof(int));
            for (j = 0; j < i; j++)
                arr[j] = 0;
        }
        j = 1;
        m = i;
        while (m != 0)
        {
            j = j * 2;
            m--;
        }
        while (j != 0)
        {
            k = 0;
            temp = t;
            for (k = 0; k < i; k++)
            {
                if (arr[k] == 0)
                {
                    if ((temp->left) != NULL)
                        temp = temp->left;
                    else
                    {
                        k = -1;
                        break;
                    }
                }
                else
                {
                    if ((temp->right) != NULL)
                        temp = temp->right;
                    else
                    {
                        k = -1;
                        break;
                    }
                }
            }
            if (i != 0)
            {
                m = i - 1;
                arr[m]++;
                while (true)
                {
                    if (arr[m] == 2)
                    {
                        arr[m] = 0;
                        m--;
                        if (m < 0)
                            break;
                        else
                            arr[m]++;
                    }
                    else
                        break;
                }
            }
            if (k == -1)
                printf("_");
            else
                printf("%d", (int)temp->value);
            j--;
            if (j != 0)
                printf(" ");
        }
        printf("\n");
    }
    return 1;
}

int count_nodes(tree* t)
{
    if (t == NULL)
        return 0;
    int r_leaf = 0, l_leaf = 0;
    l_leaf = count_nodes(t->left);
    r_leaf = count_nodes(t->right);
    return (l_leaf + r_leaf + 1);
}

//obhod
void direct_tree_traversal(tree* t)
{
    tree* arr[15];
    int ai = 0;
    tree* show[15];
    int si = 0;
    tree* temp = t;

    while (si < count_nodes(t))
    {
        while (temp != NULL)
        {
            si++;
            if (temp->right != NULL)
            {
                ai++;
                arr[ai] = temp->right;
            }
            show[si] = temp;
            temp = temp->left;
        }
        temp = arr[ai];
        ai -= 1;

    }

    int check = 0;
    for (int i = 1; i <= si; i++)
    {
        if (check > 0)
        {
            printf(" ");
        }
        else
        {
            check++;
        }
        printf("%d", show[i]->value);
    }
}

int main()
{
    tree* t;
    int i, a;
    init(&t);

    for (i = 0; i < 7; i++)
    {
        scanf("%d", &a);
        insert(t, a);
    }

    direct_tree_traversal(t);
    printf("\n");

    clean(t);
    t = NULL;
    return 0;
}