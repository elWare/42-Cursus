#include "tree_bag.hpp"			// Incluye la definición de la clase tree_bag
#include <iostream>				// Incluye la biblioteca iostream para operaciones de entrada/salida

tree_bag::tree_bag() {
	tree = nullptr;
}

tree_bag::tree_bag(const tree_bag &src) {
	tree = copy_node(src.tree);
}

tree_bag::~tree_bag() {
	destroy_tree(tree);
}

tree_bag &tree_bag::operator=(const tree_bag &src) {
	if (this != &src) {
		destroy_tree(tree);				// Destruye el árbol actual
		tree = copy_node(src.tree);		// Crea una copia del árbol fuente
	}
	return *this;						// Devuelve la referencia al objeto actual
}

tree_bag::node *tree_bag::extract_tree() {
	node *temp = tree;					// Guarda el árbol actual
	tree = nullptr;						// Establece el árbol actual como vacío
	return temp;						//
}

void tree_bag::set_tree(node *new_tree) {
	destroy_tree(tree);
	tree = new_tree;
}

void tree_bag::insert(int item) {
	node *new_node = new node;
	std::cout << "create node: " << item << std::endl;
	new_node->value = item;
	new_node->l = nullptr;
	new_node->r = nullptr;

	if (tree == nullptr) {
		tree = new_node;
	} else {
		node *current = tree;
		while (true) {
			if (item < current->value) {
				if (current->l == nullptr) {
					current->l = new_node;
					break;
				} else {
					current = current->l;
				}
			} else if (item > current->value) {
				if (current->r == nullptr) {
					current->r = new_node;
					break;
				} else {
					current = current->r;
				}
			} else {
				std::cout << "duplicate value: delete node" << std::endl;
				delete new_node;
				break;
			}
		}
	}
}
/*	Inserta un solo elemento en el árbol.	*/

void tree_bag::insert(int *items, int count) {
	for (int i = 0; i < count; i++) {
		insert(items[i]);
	}
}

void tree_bag::print() const {
	print_node(tree);
	std::cout << std::endl;
}

void tree_bag::clear() {
	destroy_tree(tree);
	tree = nullptr;
}

void tree_bag::destroy_tree(node *current) {
	if (current != nullptr) {
		std::cout << "destroying value: " << current->value << std::endl;
		destroy_tree(current->l);
		destroy_tree(current->r);
		delete current;
	}
}

void tree_bag::print_node(node *current) {
	if (current != nullptr) {
		print_node(current->l);
		if (current->value != 0)
			std::cout << current->value << " ";
		print_node(current->r);
	}
}

tree_bag::node *tree_bag::copy_node(node *current) {
	if (current == nullptr) {
		return nullptr;
	} else {
		node *new_node = new node;					// Crea un nuevo nodo// defined as static functions in the class
		new_node->value = current->value;			// Copia el valor del nodo actual
		new_node->l = copy_node(current->l);		// Copia el subárbol izquierdo
		new_node->r = copy_node(current->r);		// Copia el subárbol derecho
		return new_node;							// Devuelve el nuevo nodo copiado
	}
}
