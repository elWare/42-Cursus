#pragma once

class bag {
public:
	virtual void insert (int) = 0;			// Inserta un elemento en el conjunto
	virtual void insert (int *, int) = 0;	// Inserta un arreglo de elementos en el conjunto
	virtual void print() const = 0;			// Imprime los elementos del conjunto
	virtual void clear() = 0;				// Limpia el conjunto
};
