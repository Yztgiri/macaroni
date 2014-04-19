/*
 * =====================================================================================
 *
 *       Filename:  Input.h
 *
 *    Description:  Lecteur d'instances
 *
 *        Version:  1.0
 *        Created:  19/04/2014 14:20:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <list>

using namespace std;

struct bin{
	string bin_type;
	int width;	
	int length;	
	int height;	
	double weight;
};

struct item{
	int item_code;
	int width;
	int length;	
	int height;	
	double weight;
	string material;
	string orientation;
	string product;
};

struct instance{
	list <bin *> list_bins;
	list <item *> list_item;
	double gamma;
	double alpha;
	int beta_L;
	int beta_R;
	double delta_S;
	double delta_L;
	double delta_R;
};

void lire_instance(const char* input_bin, const char* input_item, const char* parameters,instance * inst);

void afficher_instance(instance *inst);

void creer_LP(instance *inst);

#endif
