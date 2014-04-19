/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Main
 *
 *        Version:  1.0
 *        Created:  19/04/2014 14:16:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Input.h"

int main(){
	instance *inst = new instance;
	lire_instance("input_bin.csv","input_items.csv","parameters.txt",inst);
	afficher_instance(inst);
	creer_LP(inst);
	return 0;
}
