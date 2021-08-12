


//#include "linklist.h"
#include "game.h"


int disp_menu(){
	int choice;
	do{
		printf(" 1-start game\n2-display instruction\n3-Quit \n");
		scanf(" %d", &choice);
		printf("choice  = %d \n", choice);

	}while(choice < 1 && choice < 3);

	return choice;

}
void disp_instructions(){
	printf(" the goal of the this oregon trail is to traverse the map from strart to end without runnin out of food .\n obstraction will deplete or increase your food stockpile depending on the given obstrcution\nAnimal: Gizzly[G] [-10 food], Bear B-[5 food] , Elk E [0 food] Hare H [+5] food\nDisease/weather: cold[-5food] , Thuunder[-10 food] ,Dynsentary[-15 food]\nRiver R = [20 food to ford] \n");

}

int main(int argc, char*  argv[]){
	
	
	char **board;
	m_map = NULL;
	File_Container holder ;
	//holder = malloc(sizeof(File_Container));
	holder.m_size;
	holder.m_food;
	holder.m_ports;
	FILE *file = NULL;

	//if(argc == 2){
		file = fopen(argv[1], "r");
		parse_file(file, &holder, &board);
		printf("things are okay \n");
		fclose(file);
	//}else {
	//	fprintf(stderr, "error: wrong number of arguments\n" "usage: %s textfile\n", argv[0]);
	//	return EXIT_FAILURE;
	//}



	printf("size = %d, ports = %d , food = %d \n ", holder.m_size, holder.m_ports, holder.m_food);
	for (int i =0 ; i < holder.m_size; i++){
		printf("%s \n ", board[i]);

		}





	create_map(board, &m_map, holder.m_size);
	
	printf("I am look in the m_map \n");
	QNode* tcols = m_map;
	while(tcols){
		QNode* trows = tcols;
		while(trows){
			printf("%c", trows->m_data);
			trows = trows-> m_left;
		}
		printf("\n");
		tcols = tcols -> m_up;
	}





	//for(int j = 0 ; j < holder.m_size; j++){
	//	if(board[j]!=NULL) free(board[j]);
	//	}
	//free(board);
	//
	int choice, sentinel ;
	sentinel= 1;
	
	while(!!sentinel){
		choice = disp_menu();
		printf(" disop_menu choice = %d \n ", choice);
		if(choice == 1){
			navigate_map(&m_map, holder.m_ports, holder.m_food , holder.m_size, strlen(board[0]));

		}else if(choice == 2){
			disp_instructions();
		}else if( choice ==3 ){ 
			sentinel = 0;
		}
	}

	destroy(board, holder.m_size);
	Point pt;
	pt.m_x = 0;
	pt.m_y = 0;

	if(pt1_equals_pt2(m_map->m_pos, pt) == False){
		reset_map_head_to_delete(&m_map);
		
	}
	burn_map();
	

	
	return 0;	
}
