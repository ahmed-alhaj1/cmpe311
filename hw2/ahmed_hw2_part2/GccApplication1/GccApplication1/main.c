/* 
 * CMPE 311
 * F19 Discussion 5
 * Created: 9/27/2019 1:17:11 PM
 */ 

#include "game.h"



const char PROGMEM menu[] ="----- MAIN MENU -----\n1.List Shows\n2.Play\n3.Create\n Choice: 0\n";
const char PROGMEM ply_menu[] = "----- Play by MENU -----\n1.Play by Number\n2.Search by Title\n#.Please Enter a Choice:\n";
//const EMPTY[] = "EMPTY"
 
char song_title_list[NUMBER_OF_SONGS][MAX_PASS_LENGTH] = {
	{"<EMPTY>"}, {"<EMPTY>"}, {"<EMPTY>"}, {"<EMPTY>"}};

	// empty arrays of songs corresponding to the song titles
char  song_list[NUMBER_OF_SONGS][SONG_LENGTH] = {
		{NULL_SONG}, {NULL_SONG}, {NULL_SONG}, {NULL_SONG}};


//#####################################################
//#####################################################
int extract_number(char *str){
	int i, digit , number;
	number = 0;
	char c ;
	for (int i = 0; i < strlen(str); i++){
		c = str[i];
		if(c >= '0' && c <= '9'){
			
			digit = c - '0';
			number = number * 10 + digit;
			
		}
	}
	return number;
}
uint8_t DisplayMenu(const char* menu){
	//char mess[4], mess1
	int user_num;
	//char buff[MAX_PASS_LENGTH];
	//print_menu(menu);
	//for(char * s = strtok(menu, "\n"); s != NULL; s= strtok(NULL, "\n")){
		
	//	printf("%s \n", s);
	//}2
	printf_P(menu);
	
	if(fgets(&user_line, MAX_PASS_LENGTH , stdin) != NULL) {
		
		//sscanf(user_line, " %d", &user_num);
		//user_num = atoi(user_line);
		//printf("line = %s ", user_line);
		
		//}
		
		sscanf_P(&user_line, "%d", &user_num);
	}

	printf(" user_num = %d \n", user_num);
	printf("buff = %s \n", user_line);


	//return r
	
	return (uint8_t) user_num;
}

//####################################################
//####################################################
void print_menu(const char menu[]){
	
	//char *menu_ptr = strdup(menu);
	//char * ptr = menu_ptr;
	//char *menu_ptr = strdup(menu);
	//char *ptr = menu_ptr;
	//char *str;

	// iterate through the main menu prompt and print at each newline char
	//while ((str = strtok_r(ptr, "\n", &ptr))) {
		
	//		printf("%s \n", str);
	//}
	for(char *s =strtok(menu, "\n") ; s != NULL; s =strtok(NULL,"\n")){
		
		printf("%s \n", s);
	}
	
	
}

void song_menu(char *song_titles){
	const char title[] = "title : ";
	//const char index_search[] = "please enter index number \n";
	//const char index_str [] = " index : \n";
	//const char note_msg [] = "song notes: \n";
	//const char song_stored_msg[] = " song add successfully";
	//const char database[] = "----data base------";
	printf(" ----data base------\n" );
	  for (int i = 0; i < NUMBER_OF_SONGS; i++) {
		  printf("%d: %s %s\n", i, title, song_titles[i]);
	  }
		
	
}

//####################################################
//
//####################################################
void play_menu(const char menu[], char * song_titles) {

	const char PROGMEM title_search[] = "enter title\n";
	const char PROGMEM index_search[] = "enter index \n";
    int play_choice, song_idx;
    int index = 0;
    // copy the const string main menu prompt to be tokenized
    

    play_choice = DisplayMenu(menu);

    

	// search by title
	if(play_choice == 1) {

            char user_query[MAX_PASS_LENGTH];
            printf_P("%s", title_search);
            if (fgets(user_line, TITLE_LENGTH, stdin) != NULL) {
                sscanf(user_line, "%[^\n]", user_query);
            }
            // index of the user's desired song title
            song_idx = best_match(user_query, song_titles);           

	}else if(play_choice == 2) {

            printf_P("%s", index_search);
            if (fgets(user_line, 3, stdin) != NULL) {
                sscanf(user_line, "%d", &song_idx);
            }

	}

       
}

	
	//##################################################
	//
	//##################################################
	
uint8_t make_menu(char *song_titles){
	const char title_search[] = "please enter title\n";
	const char index_search[] = "please enter index number \n";
	const char index_str [] = " index : \n";
	const char note_msg [] = "song notes: \n";
	const char song_stored_msg[] = " song add successfully";
		
	char song_ascii[MAX_PASS_LENGTH];
	char song_title[TITLE_LENGTH];
	
	
	int new_song_ix;
	char * song;
	
	printf("%s\n", title_search);
	if (fgets(user_line,MAX_PASS_LENGTH,stdin)!=NULL) {
		sscanf(user_line,"%s", song_title);
	}
	
	printf("%s ---> %s ", song_title, note_msg);
	if (fgets(user_line,MAX_PASS_LENGTH,stdin)!=NULL) {
		sscanf(user_line,"%s", song_ascii);
	}
	
	printf('\n');
	
	song = add_silence_char(song_ascii);
	
	uint8_t *packed_song[strlen(song)/2];
	memset(packed_song, 0, sizeof(packed_song));
	
	//StoreSong(packed_song, song);
	
	printf("%s\n", index_str);
	if(fgets(user_line, NUMBER_OF_SONGS-1, stdin) != NULL){
		sscanf(user_line, "%d",  &new_song_ix);
		
	}
	
	memcpy(song_titles[new_song_ix], song_title, SONG_LENGTH);
	memcpy(song_titles[new_song_ix], packed_song, SONG_LENGTH);
	
	printf("%s", song_stored_msg);	
	
		
		
	return new_song_ix;
	}
	
	int match_score(const char count_query_string[], const char database[]) {

		const char *count_query_ptr = count_query_string;
		const char *database_ptr = database;
		char *token_user, *token_stored;
		int total_matches = 0;

		// loop until the string does not contain any whitespace (' ') chars
		while ((token_stored = strtok_r(database_ptr, " ", &database_ptr))) {

			// loop until the string does not contain any whitespace (' ') chars
			while ((token_user = strtok_r(count_query_ptr, " ", &count_query_ptr))) {

				// case-insensitively compare the two tokens
				if (!strcasecmp(token_user, token_stored)) {
					total_matches++;
				}

			}

		}

		return total_matches;

	}
	int best_match(char user[], char *song_title_list) {

		int best_choice = 0, highest_score = 0, cursor = 0;

		// loop through each of the titles in the song title array and find their
		// match score
		for (int i = 0; i < NUMBER_OF_SONGS; i++) {

			// only compare song titles that are non-empty
			if (song_title_list[i] != '\0') {

				// current match score
				cursor = match_score(user, song_title_list[i]);

				// best_choice gets assigned the index at which the maximum match
				// score was achieved
				if (cursor > highest_score) {
					highest_score = cursor;
					best_choice = i;
				}
			}
		}

		return best_choice;

	}
int main()
{
	stderr = stdin = stdout = &uart_stream;
	
	UARTInit(); /* initialize the UART (set hardware specific configuration registers) */
	
	
	//uint8_t ssong[9] = "*A2**B2**R2";
	//PlaySong(ssong);
	
	//printf("%s \n", vall);
	
	uint8_t choice;
	int sentinel = 1;
	//choice = DisplayMenu(menu);
	printf("%d \n ", choice);
	
	while(!!sentinel){
		
		choice = DisplayMenu(menu);
		//printf("%d \n ", choice);
		switch(choice){
			
			case 1 : 
				{
					song_menu(song_title_list);
					break;
				
				}
			case 2:
				{
					printf("I am going to play menu \n");
					play_menu(ply_menu, song_title_list);
					break;	
				}
			
			case 3:
				{	
					make_menu(song_title_list);
					break;
				}
			case 4:
				{	
					sentinel = 0;
					break;
				}
			default:{break;}
				
		}
						
			
		}
	
	return 1;// EXIT_SUCCESS;
}