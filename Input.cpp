/*
 * =====================================================================================
 *
 *       Filename:  Input.cpp
 *
 *    Description:  Lecteur d'instances
 *
 *        Version:  1.0
 *        Created:  19/04/2014 14:14:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Input.h"
#include <cstdlib> 

using namespace std;

void lire_instance(const char* input_bin, const char* input_item, const char* parameters,instance * inst){
	
	//Lecture des bins
	ifstream fichier;
	fichier.open(input_bin, ifstream::in);
	if (!fichier){
		cerr << "Erreur à l'ouverture du fichier bin\n";
		exit(1);
	}
	
	string ligne,tmp;
	list <string> mots_lus;

	getline(fichier, ligne);
	
	while(getline(fichier, ligne)){
		for(string::iterator it = ligne.begin() ; it != ligne.end() ; it++){
			if(*it != ';'){
				tmp = tmp + *it;
			}else{
				mots_lus.push_back(tmp);
				tmp = "";
			}
		}
		bin *new_bin = new bin;
		new_bin->bin_type = mots_lus.front();
		mots_lus.pop_front();
		new_bin->length = atoi((mots_lus.front()).c_str());
		mots_lus.pop_front();
		new_bin->width = atoi((mots_lus.front()).c_str());
		mots_lus.pop_front();
		new_bin->height = atoi((mots_lus.front()).c_str());
		mots_lus.pop_front();
		new_bin->weight = atof((mots_lus.front()).c_str());
		inst->list_bins.push_back(new_bin);
	}
	fichier.close();
		
	//Lecture des items
	fichier.open(input_item, ifstream::in);
	if (!fichier){
		cerr << "Erreur à l'ouverture du fichier item\n";
		exit(1);
	}
	
	mots_lus.clear();
	tmp = "";

	getline(fichier, ligne);
	
	while(getline(fichier, ligne)){
		tmp = "";
		for(string::iterator it = ligne.begin() ; it != ligne.end() ; it++){
			if(*it != ';'){
				tmp = tmp + *it;
			}else{
				while((*it == ' ' || *it == ';')&&(it != ligne.end())){it++;}
				it--;
				mots_lus.push_back(tmp);
				tmp = "";
			}
		}
		item *new_item = new item;
		new_item->item_code = atoi((mots_lus.front()).c_str());
		mots_lus.pop_front();
		new_item->length = atoi((mots_lus.front()).c_str());
		mots_lus.pop_front();
		new_item->width = atoi((mots_lus.front()).c_str());
		mots_lus.pop_front();
		new_item->height = atoi((mots_lus.front()).c_str());
		mots_lus.pop_front();
		new_item->weight = atof((mots_lus.front()).c_str());
		mots_lus.pop_front();
		new_item->material = mots_lus.front();
		mots_lus.pop_front();
		
		if((mots_lus.front()).compare("WIDTHWISE") == 0 || (mots_lus.front()).compare("LENGTHWISE") == 0){ 
			new_item->orientation = mots_lus.front();
			mots_lus.pop_front();
		}else{
			new_item->orientation = "non";
		}
		new_item->product = mots_lus.front();
		inst->list_item.push_back(new_item);
	}
	fichier.close();


	//Lecture des parametres
	fichier.open(parameters, ifstream::in);
	if (!fichier){
		cerr << "Erreur à l'ouverture du fichier parameters\n";
		exit(1);
	}
	
	mots_lus.clear();
	tmp = "";
	bool lecture;

	while(getline(fichier, ligne)){
		lecture = false;
		for(string::iterator it = ligne.begin() ; it != ligne.end() ; it++){
			if(*it == '='){
				lecture = true;
				it++;
			}
			if(lecture){
				tmp = tmp + *it;
			}
		}
		mots_lus.push_back(tmp);
		tmp = "";
	}
	
	inst->gamma = atof((mots_lus.front()).c_str());
	mots_lus.pop_front();
	inst->alpha = atof((mots_lus.front()).c_str());
	mots_lus.pop_front();
	inst->beta_L = atoi((mots_lus.front()).c_str());
	mots_lus.pop_front();
	inst->beta_R = atoi((mots_lus.front()).c_str());
	mots_lus.pop_front();
	inst->delta_S = atof((mots_lus.front()).c_str());
	mots_lus.pop_front();
	inst->delta_L = atof((mots_lus.front()).c_str());
	mots_lus.pop_front();
	inst->delta_R = atof((mots_lus.front()).c_str());
	fichier.close();

	return;
}

void afficher_instance(instance *inst){
	cout<<"Bins\n";
	for(list<bin *>::iterator it = inst->list_bins.begin() ; it != inst->list_bins.end() ; it++){
		cout<<"Type "<<(*it)->bin_type<<"\n";
		cout<<"Width "<<-(*it)->width<<"\n";
		cout<<"Length "<<(*it)->length<<"\n";
		cout<<"Height "<<(*it)->height<<"\n";
		cout<<"Weight "<<(*it)->weight<<"\n";
	}
	cout<<"Items\n";
	for(list<item *>::iterator it = inst->list_item.begin() ; it != inst->list_item.end() ; it++){
		cout<<"ID "<<(*it)->item_code<<"\n";
		cout<<"Width "<<(*it)->width<<"\n";
		cout<<"Length "<<(*it)->length<<"\n";
		cout<<"Height "<<(*it)->height<<"\n";
		cout<<"Weight "<<(*it)->weight<<"\n";
		cout<<"Material "<<(*it)->material<<"\n";
		cout<<"Orientation "<<(*it)->orientation<<"\n";
		cout<<"Product "<<(*it)->product<<"\n";
	}
	cout<<inst->gamma<<"\n";
	cout<<inst->alpha<<"\n";
	cout<<inst->beta_L<<"\n";
	cout<<inst->beta_R<<"\n";
	cout<<inst->delta_S<<"\n";
	cout<<inst->delta_L<<"\n";
	cout<<inst->delta_R<<"\n";
	return;
}

void creer_LP(instance *inst){
	ofstream input("input_LP.lp");

	int objets = (int)inst->list_item.size();
	int bigM = 0;
	for(list<item *>::iterator it = inst->list_item.begin() ; it != inst->list_item.end() ; it++){
i		bigM = bigM + (*it)->width + (*it)->length + (*it)->height;
	}

	input<<"Minimize ";

	for(int r=1 ; r<=inst->beta_L ; r++){
		input<<"SO,2"<<r<<"+ ";
	}
	input<<" 0 \n";
	input<<"Subject To\n";

	//C1
	for(int o=1 ; o<=objets ; o++){
		for(int r=1 ; r <=inst->beta_L ; r++){
			input<<"x"<<o<<","<<r<<","<<1<<" + ";
		}
		input<<" 0 = 0\n";
	}

	//C22
	for(int o=1 ; o<=objets ; o++){
		for(int r=1 ; r <=inst->beta_L ; r++){
			input<<"x"<<o<<","<<r<<","<<1<<" + "<<"x_"<<o<<","<<r<<","<<2<<" + ";
		}
		input<<" 0 >= 1\n";
	}
	for(int r=1 ; r <=inst->beta_L ; r++){		
		for(int o=1 ; o<=objets ; o++){
			input<<"x"<<o<<","<<r<<","<<1<<" + "<<"x_"<<o<<","<<r<<","<<2<<" + ";
		}
		input<<" 0 <= "<<inst->beta_R<<"\n";
	}

	//C25
	list<item *>::iterator it;
	it = inst->list_item.begin();
	for(int o=1 ; o<=objets ; o++){
		for(int r=1 ; r <=inst->beta_L ; r++){
			input<<(*it)->width<<"x"<<o<<","<<r<<","<<1<<" + "<<"x"<<(*it)->length<<o<<""<<r<<","<<2<<" - o"<<r<<" <= SO,"<<r<<",1\n";
		}
		it++;
	}

	input<<"Bounds\n";
	for(int o=1 ; o<=objets ; o++){
		for(int r=1 ; r <=inst->beta_L ; r++){
			input<<" 0 <= "<<"x"<<o<<","<<r<<","<<1<<" <= 1\n";
			input<<" 0 <= "<<"x"<<o<<","<<r<<","<<2<<" <= 1\n";
		}
	}
	
	input<<"Binary\n";
	for(int o=1 ; o<=objets ; o++){
		for(int r=1 ; r <=inst->beta_L ; r++){
			input<<"x"<<o<<","<<r<<","<<1<<"\n";
			input<<"x"<<o<<","<<r<<","<<2<<"\n";
		}
	}

	input<<"End\n";
	
	ostringstream commande;
	commande.str("");
	commande<<"/home/ternier/PING/scip/scipoptsuite-3.1.0/scip-3.1.0/bin/scip -c \"read "<<"input_LP.lp"<< " opt write solution "<<"output_LP.sol"<<" quit \""<<endl;
	cout<<commande.str().c_str();
	if (system(commande.str().c_str()))
		cout<<"End of Scip"<<endl;

	return;
   }
