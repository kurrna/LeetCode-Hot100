#ifndef RBTREE_H
#define RBTREE_H

#include <stdlib.h>
#include <string.h>

// 颜色定义
typedef enum {
    RBTREE_RED,
    RBTREE_BLACK
} rbtree_color_t;

// 红黑树节点结构
typedef struct rbtree_node {
    void *key;                  // 键
    void *value;                // 值
    rbtree_color_t color;       // 颜色
    struct rbtree_node *left;   // 左子树
    struct rbtree_node *right;  // 右子树
    struct rbtree_node *parent; // 父节点
} rbtree_node_t;

// 红黑树结构
typedef struct {
    rbtree_node_t *root;                // 根节点
    rbtree_node_t *nil;                 // 哨兵节点，代替NULL
    int (*compare)(const void *a, const void *b); // 比较函数
    void (*free_key)(void *key);        // 键的释放函数
    void (*free_value)(void *value);    // 值的释放函数
    size_t key_size;                    // 键的大小，用于复制
    size_t value_size;                  // 值的大小，用于复制
} rbtree_t;

// 创建红黑树
// compare: 比较函数，a < b返回负数，a == b返回0，a > b返回正数
// free_key: 键的释放函数，NULL表示不释放
// free_value: 值的释放函数，NULL表示不释放
// key_size: 键的大小，用于内存复制
// value_size: 值的大小，用于内存复制
rbtree_t *rbtree_create(
    int (*compare)(const void *a, const void *b),
    void (*free_key)(void *key),
    void (*free_value)(void *value),
    size_t key_size,
    size_t value_size
);

// 销毁红黑树
void rbtree_destroy(rbtree_t *tree);

// 插入键值对
// 返回0表示成功，1表示键已存在，-1表示失败
int rbtree_insert(rbtree_t *tree, const void *key, const void *value);

// 删除指定键
// 返回0表示成功，1表示键不存在，-1表示失败
int rbtree_delete(rbtree_t *tree, const void *key);

// 查找指定键的值
// 返回值的指针，NULL表示不存在
void *rbtree_search(rbtree_t *tree, const void *key);

// 遍历红黑树（中序遍历）
// callback: 回调函数，返回0继续遍历，非0停止遍历
void rbtree_traverse(rbtree_t *tree, int (*callback)(const void *key, const void *value, void *user_data), void *user_data);

// 获取树的大小（节点数量）
size_t rbtree_size(rbtree_t *tree);

#endif // RBTREE_H

// 实现部分
#ifdef RBTREE_IMPLEMENTATION

// 左旋操作
static void rbtree_left_rotate(rbtree_t *tree, rbtree_node_t *x) {
    rbtree_node_t *y = x->right;
    x->right = y->left;

    if (y->left != tree->nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

// 右旋操作
static void rbtree_right_rotate(rbtree_t *tree, rbtree_node_t *y) {
    rbtree_node_t *x = y->left;
    y->left = x->right;

    if (x->right != tree->nil) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == tree->nil) {
        tree->root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }

    x->right = y;
    y->parent = x;
}

// 插入修复
static void rbtree_insert_fixup(rbtree_t *tree, rbtree_node_t *z) {
    while (z->parent->color == RBTREE_RED) {
        if (z->parent == z->parent->parent->left) {
            rbtree_node_t *y = z->parent->parent->right;

            if (y->color == RBTREE_RED) {
                z->parent->color = RBTREE_BLACK;
                y->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rbtree_left_rotate(tree, z);
                }

                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                rbtree_right_rotate(tree, z->parent->parent);
            }
        } else {
            rbtree_node_t *y = z->parent->parent->left;

            if (y->color == RBTREE_RED) {
                z->parent->color = RBTREE_BLACK;
                y->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rbtree_right_rotate(tree, z);
                }

                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                rbtree_left_rotate(tree, z->parent->parent);
            }
        }
    }

    tree->root->color = RBTREE_BLACK;
}

// 查找节点
static rbtree_node_t *rbtree_find_node(rbtree_t *tree, const void *key) {
    rbtree_node_t *node = tree->root;

    while (node != tree->nil) {
        int cmp = tree->compare(key, node->key);
        if (cmp < 0) {
            node = node->left;
        } else if (cmp > 0) {
            node = node->right;
        } else {
            return node; // 找到节点
        }
    }

    return NULL; // 未找到
}

// 查找最小节点
static rbtree_node_t *rbtree_minimum(rbtree_t *tree, rbtree_node_t *node) {
    while (node->left != tree->nil) {
        node = node->left;
    }
    return node;
}

// 替换节点
static void rbtree_transplant(rbtree_t *tree, rbtree_node_t *u, rbtree_node_t *v) {
    if (u->parent == tree->nil) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// 删除修复
static void rbtree_delete_fixup(rbtree_t *tree, rbtree_node_t *x) {
    while (x != tree->root && x->color == RBTREE_BLACK) {
        if (x == x->parent->left) {
            rbtree_node_t *w = x->parent->right;

            if (w->color == RBTREE_RED) {
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                rbtree_left_rotate(tree, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
                w->color = RBTREE_RED;
                x = x->parent;
            } else {
                if (w->right->color == RBTREE_BLACK) {
                    w->left->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    rbtree_right_rotate(tree, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->right->color = RBTREE_BLACK;
                rbtree_left_rotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            rbtree_node_t *w = x->parent->left;

            if (w->color == RBTREE_RED) {
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                rbtree_right_rotate(tree, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
                w->color = RBTREE_RED;
                x = x->parent;
            } else {
                if (w->left->color == RBTREE_BLACK) {
                    w->right->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    rbtree_left_rotate(tree, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->left->color = RBTREE_BLACK;
                rbtree_right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }

    x->color = RBTREE_BLACK;
}

// 创建红黑树
rbtree_t *rbtree_create(
    int (*compare)(const void *a, const void *b),
    void (*free_key)(void *key),
    void (*free_value)(void *value),
    size_t key_size,
    size_t value_size
) {
    if (!compare || key_size == 0 || value_size == 0) {
        return NULL;
    }

    rbtree_t *tree = (rbtree_t *)malloc(sizeof(rbtree_t));
    if (!tree) {
        return NULL;
    }

    // 创建哨兵节点
    tree->nil = (rbtree_node_t *)malloc(sizeof(rbtree_node_t));
    if (!tree->nil) {
        free(tree);
        return NULL;
    }

    tree->nil->color = RBTREE_BLACK;
    tree->nil->left = tree->nil->right = tree->nil->parent = tree->nil;
    tree->nil->key = tree->nil->value = NULL;

    tree->root = tree->nil;
    tree->compare = compare;
    tree->free_key = free_key;
    tree->free_value = free_value;
    tree->key_size = key_size;
    tree->value_size = value_size;

    return tree;
}

// 销毁节点（递归）
static void rbtree_destroy_nodes(rbtree_t *tree, rbtree_node_t *node) {
    if (node == tree->nil) {
        return;
    }

    rbtree_destroy_nodes(tree, node->left);
    rbtree_destroy_nodes(tree, node->right);

    if (tree->free_key) {
        tree->free_key(node->key);
    } else {
        free(node->key);
    }

    if (tree->free_value) {
        tree->free_value(node->value);
    } else {
        free(node->value);
    }

    free(node);
}

// 销毁红黑树
void rbtree_destroy(rbtree_t *tree) {
    if (!tree) {
        return;
    }

    rbtree_destroy_nodes(tree, tree->root);
    free(tree->nil);
    free(tree);
}

// 插入键值对
int rbtree_insert(rbtree_t *tree, const void *key, const void *value) {
    if (!tree || !key || !value) {
        return -1;
    }

    // 检查键是否已存在
    if (rbtree_find_node(tree, key)) {
        return 1; // 键已存在
    }

    rbtree_node_t *z = (rbtree_node_t *)malloc(sizeof(rbtree_node_t));
    if (!z) {
        return -1;
    }

    // 分配并复制键
    z->key = malloc(tree->key_size);
    if (!z->key) {
        free(z);
        return -1;
    }
    memcpy(z->key, key, tree->key_size);

    // 分配并复制值
    z->value = malloc(tree->value_size);
    if (!z->value) {
        free(z->key);
        free(z);
        return -1;
    }
    memcpy(z->value, value, tree->value_size);

    rbtree_node_t *y = tree->nil;
    rbtree_node_t *x = tree->root;

    // 找到插入位置
    while (x != tree->nil) {
        y = x;
        if (tree->compare(z->key, x->key) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == tree->nil) {
        tree->root = z; // 树为空，z成为根节点
    } else if (tree->compare(z->key, y->key) < 0) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RBTREE_RED;

    // 修复红黑树性质
    rbtree_insert_fixup(tree, z);

    return 0;
}

// 删除指定键
int rbtree_delete(rbtree_t *tree, const void *key) {
    if (!tree || !key) {
        return -1;
    }

    rbtree_node_t *z = rbtree_find_node(tree, key);
    if (!z) {
        return 1; // 键不存在
    }

    rbtree_node_t *y = z;
    rbtree_node_t *x;
    rbtree_color_t y_original_color = y->color;

    if (z->left == tree->nil) {
        x = z->right;
        rbtree_transplant(tree, z, z->right);
    } else if (z->right == tree->nil) {
        x = z->left;
        rbtree_transplant(tree, z, z->left);
    } else {
        y = rbtree_minimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z) {
            x->parent = y;
        } else {
            rbtree_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbtree_transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    // 释放节点内存
    if (tree->free_key) {
        tree->free_key(z->key);
    } else {
        free(z->key);
    }

    if (tree->free_value) {
        tree->free_value(z->value);
    } else {
        free(z->value);
    }
    free(z);

    // 如果删除的是黑色节点，需要修复红黑树性质
    if (y_original_color == RBTREE_BLACK) {
        rbtree_delete_fixup(tree, x);
    }

    return 0;
}

// 查找指定键的值
void *rbtree_search(rbtree_t *tree, const void *key) {
    if (!tree || !key) {
        return NULL;
    }

    rbtree_node_t *node = rbtree_find_node(tree, key);
    return node ? node->value : NULL;
}

// 中序遍历（递归）
static int rbtree_inorder_traverse(rbtree_node_t *node, rbtree_node_t *nil,
                                  int (*callback)(const void *, const void *, void *),
                                  void *user_data) {
    if (node == nil) {
        return 0;
    }

    // 遍历左子树
    int ret = rbtree_inorder_traverse(node->left, nil, callback, user_data);
    if (ret != 0) {
        return ret;
    }

    // 调用回调函数
    ret = callback(node->key, node->value, user_data);
    if (ret != 0) {
        return ret;
    }

    // 遍历右子树
    return rbtree_inorder_traverse(node->right, nil, callback, user_data);
}

// 遍历红黑树
void rbtree_traverse(rbtree_t *tree, int (*callback)(const void *key, const void *value, void *user_data), void *user_data) {
    if (!tree || !callback) {
        return;
    }

    rbtree_inorder_traverse(tree->root, tree->nil, callback, user_data);
}

// 计算树的大小（递归）
static size_t rbtree_calculate_size(rbtree_node_t *node, rbtree_node_t *nil) {
    if (node == nil) {
        return 0;
    }
    return 1 + rbtree_calculate_size(node->left, nil) + rbtree_calculate_size(node->right, nil);
}

// 获取树的大小
size_t rbtree_size(rbtree_t *tree) {
    if (!tree) {
        return 0;
    }
    return rbtree_calculate_size(tree->root, tree->nil);
}

#endif // RBTREE_IMPLEMENTATION
