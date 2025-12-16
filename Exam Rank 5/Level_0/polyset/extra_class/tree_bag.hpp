#pragma once

#include "bag.hpp"    // Incluye la definición de la clase base bag

class tree_bag : virtual public bag {

protected:
	struct node {
		node *l;
		node *r;
		int value;
	};
	node *tree;

public:
	tree_bag();
	tree_bag(const tree_bag &other);
	virtual ~tree_bag();
	tree_bag &operator=(const tree_bag &);
	
	node *extract_tree();							// Extrae el árbol actual
	void set_tree(node *);							// Establece el árbol actual

	virtual void insert(int);						// Inserta un elemento en el árbol
	virtual void insert(int *array, int size);		// Inserta un arreglo de elementos en el árbol
	virtual void print() const;						// Imprime los elementos del árbol
	virtual void clear();							// Limpia el árbol
	
private:
	static void destroy_tree(node *);				// Destruye el árbol
	static void print_node(node *);					// Imprime un nodo del árbol
	static node *copy_node(node *);					// Copia un nodo del árbol
};