#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "linuxlist.h"

//#include "Play.h"
//#include "Playn.h"
//#include "Card.h"

LIST_HEAD(player_list_head_1);
LIST_HEAD(player_list_head_2);
LIST_HEAD(player_list_head_3);
LIST_HEAD(player_list_head_4);

LIST_HEAD(build_list_head_1);
LIST_HEAD(build_list_head_2);
LIST_HEAD(build_list_head_3);
LIST_HEAD(build_list_head_4);

int8_t game = 1;
int32_t playernum = 0;
int32_t roundnum = 1;


int main(void) {
  
	int32_t w = welcome();
	while(w == 1){
		printf("----------\n");
		w = welcome();
	}
  //遊戲開啟
	int32_t tradecards[5] = {0};
	int8_t trademk = 0;
	if(w == 2)
	{
		printf("遊戲開始!( Ctrl+C 可隨時結束遊戲:) )\n\n");
  
		srand(time(0));

    playernum = rand()%4;
		if(playernum == 0)
    playernum = 4;
	  printf("你的號碼為: %d號\n\n", playernum);
		start(&player_list_head_1, &player_list_head_2, &player_list_head_3, &player_list_head_4, &build_list_head_1, &build_list_head_2, &build_list_head_3, &build_list_head_4);//開始
		
		for(int32_t i = 0;i<5;i++){//洗價物牌
			tradecards[i] = rand()%5;
			while(((trademk >> tradecards[i]) & 1) == 1){
				tradecards[i] = rand()%5;
			}
			trademk = trademk|(1 << tradecards[i]);
			//printf("tradetest: %d\n", tradecards[i]);
		}
		sleep(3);
	}
	
	else if(w == 3)
	return 0;//結束

  for(int32_t i = 0;i<5;i++)
	{
		gameround(roundnum, playernum, tradecards[roundnum%5], &player_list_head_1, &player_list_head_2, &player_list_head_3, &player_list_head_4, &build_list_head_1, &build_list_head_2, &build_list_head_3, &build_list_head_4);
		roundnum++;
	}
  
/*
	while(game)
	{
    gameround(roundnum);
		roundnum++;

    game = end_game();
	}*/
 

  return 0;
}