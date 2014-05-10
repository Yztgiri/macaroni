#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include "Input.h"

int main(int argc, char** argv){
	instance_data *inst = new instance_data;
	lire_instance("input_bin.csv","input_items.csv","parameters.txt",inst);
	afficher_instance(inst);
	return 0;
}
