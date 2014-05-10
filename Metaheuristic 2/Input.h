#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <list>

using namespace std;

//Definition des structures de données représentant les données du problème

struct bin_data {
	string bin_type;
	int width;	
	int length;	
	int height;	
	double weight;
};

struct item_data {
	int item_code;
	int width;//Dimension 1
	int length;//Dimension 2
	int height;	
	double weight;
	string material;
	string orientation;
	string product;
};

struct instance_data {
	list <bin_data *> list_bins;
	list <item_data *> list_item;
	double gamma;
	double alpha;
	int beta_L;
	int beta_R;
	double delta_S;
	double delta_L;
	double delta_R;
};

void lire_instance(const char* input_bin, const char* input_item, const char* parameters,instance_data * inst);
void afficher_instance(instance_data *inst);
void creer_LP(instance_data *inst);

#endif
