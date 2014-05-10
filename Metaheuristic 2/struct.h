#ifndef struct_H
#define struct_H

#include <stdlib.h>
#include <list>

using namespace std;

//Definition des structures de données représentant une solution du problème

class Row;

class Item {
public :
	Row *r; //Pointeur sur la Row où l'Item est rangé
	int width; //Largeur de l'Item
	int length; //Longueur de l'Item
	int height; //Hauteur de l'Item
	double weight; //Poids de l'Item

	//Constructeur
	Item(Row *r_, int width_, int length_, int height_, double weight_) {r = r_; width = width_; length = length_; height = height_; weight = weight_;}
};

class Row {
public :
	list < Item > l_item; // Liste d'objets appartenant à la Row
	int width; //Largeur de la Row
	int length; //Longueur de la Row
	double weight; //Poids de la Row
	bool pleine; //True si on ne peut plus mettre d'Item dans la Row, false sinon

	//Constructeur
	Row(int width_, int length_, bool pleine_, double weight_) {width = width_; length = length_; pleine = false; weight = weight_; l_item.clear();}
};

class Stack {
public :
	list < Row > l_row; //Liste de rows appartenant à la Stack
	int width; //Largeur de la Stack
	int length; //Longueur de la Stack
	double weight; //Poids de la Stack
	bool pleine; //True si on ne peut plus mettre de Row dans la Stack, false sinon	

	//Constructeur
	Stack(int width_, int length_, bool pleine_, double weight_) {width = width_; length = length_; pleine = false; weight = weight_; l_row.clear();}
};

class Bin {
public :
	list < Stack > l_stack; //Liste de rows appartenant à la Bin
	int width; //Largeur de la Bin
	int length; //Longueur de la Bin
	double weight; //Poids de la Bin
	bool pleine; //True si on ne peut plus mettre de Stack dans la Bin, false sinon	

	//Constructeur
	Bin(int width_, int length_, bool pleine_, double weight_) {width = width_; length = length_; pleine = false; weight = weight_; l_stack.clear();}
};
#endif
