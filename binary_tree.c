#include "binary_tree.h"

KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair *valor_par = (KeyValPair *)calloc(1,sizeof(KeyValPair));
    valor_par->key = key;
    valor_par->value = val;
    return valor_par; 
}

//só pode chamar essa função depois que destruir o valor e a chave
void key_val_pair_destroy(KeyValPair *kvp){
    free(kvp);
}


Node *node_construct(void *key, void *value, Node *left, Node *right){
    Node *no = (Node *)calloc(1,sizeof(Node));
    no->val = key_val_pair_construct(key,value);
    no->left = left;
    no->right = right;
    return no;
}

//só pode chamar essa função depois que destruir o valor e a chave
void node_destroy(Node *node){
    key_val_pair_destroy(node->val);
    free(node);
}

BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    BinaryTree *arvore = (BinaryTree *)calloc(1,sizeof(BinaryTree));
    arvore->root = NULL;
    arvore->cmp_fn = cmp_fn;
    arvore->key_destroy_fn = key_destroy_fn;
    arvore->val_destroy_fn = val_destroy_fn;
    return arvore;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value){
    if(binary_tree_empty(bt)){
        Node *novo = node_construct(key,value,NULL,NULL);
        bt->root = novo;
    }else{
        Node *pai = NULL, *atual = bt->root;
        while(atual != NULL){
            pai = atual;
            if(bt->cmp_fn(key,pai->val->key) > 0){
                //atualizar atual
            }else{
                //atualizar atual
            }
        }
        //criar um novo node
        //atualizar o left ou right do pai
    }
}

int binary_tree_empty(BinaryTree *bt){
    return bt->root == NULL;
}

void binary_tree_remove(BinaryTree *bt, void *key){

}

KeyValPair *binary_tree_min(BinaryTree *bt){

}

KeyValPair *binary_tree_max(BinaryTree *bt){

}

KeyValPair *binary_tree_pop_min(BinaryTree *bt){

}

KeyValPair *binary_tree_pop_max(BinaryTree *bt){

}

void *binary_tree_get(BinaryTree *bt, void *key){

}

void binary_tree_destroy(BinaryTree *bt){

}

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);

Vector *binary_tree_inorder_traversal(BinaryTree *bt){

}

Vector *binary_tree_preorder_traversal(BinaryTree *bt){

}

Vector *binary_tree_postorder_traversal(BinaryTree *bt){

}

Vector *binary_tree_levelorder_traversal(BinaryTree *bt){

}

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt){

}

Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt){

}

Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt){

}