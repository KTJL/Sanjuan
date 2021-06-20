#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "linuxlist.h"

#define NONE "\033[m"
#define RED "\033[0;32;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"

LIST_HEAD(player_list_head_1);
LIST_HEAD(player_list_head_2);
LIST_HEAD(player_list_head_3);
LIST_HEAD(player_list_head_4);

LIST_HEAD(build_list_head_1);
LIST_HEAD(build_list_head_2);
LIST_HEAD(build_list_head_3);
LIST_HEAD(build_list_head_4);

int32_t game = 1;
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
	int32_t level = 1;
	if(w == 2)
	{
		printf("遊戲開始!( Ctrl+C 可隨時結束遊戲:) )\n\n");

		printf(RED"請選擇遊戲難度:\n1) 普通版(無時間限制)\n2) 燒腦版(操作限時30秒)\n(請輸入數字進行選擇):"NONE);
		while(scanf("%d", &level) != 1 || level < 1 || level > 2){
			char c;
			while (( c = getchar()) != EOF && c != '\n'){}
			printf("無效選擇!(請輸入數字進行選擇):");
		}
  
		srand(time(0));

    playernum = rand()%4;
		if(playernum == 0)
    playernum = 4;
	  printf(YELLOW"\n\n你的號碼為: %d號\n\n"NONE, playernum);
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
/*test
  for(int32_t i = 0;i<4;i++)
	{
		gameround(roundnum, playernum, tradecards[roundnum%5], &player_list_head_1, &player_list_head_2, &player_list_head_3, &player_list_head_4, &build_list_head_1, &build_list_head_2, &build_list_head_3, &build_list_head_4);
		roundnum++;
	}
  
*/
	while(game)
	{
    game = gameround(roundnum, playernum, tradecards[roundnum%5], &player_list_head_1, &player_list_head_2, &player_list_head_3, &player_list_head_4, &build_list_head_1, &build_list_head_2, &build_list_head_3, &build_list_head_4, level);
		if(game == 1)
		roundnum++;
	}

	printf(RED"\n\n\n遊戲結束!結算分數!\n"NONE);
  int32_t score[4] = {0};
	int32_t commod[4] = {0};
	struct list_head *listptr = NULL;
	score[0] = score_count(&build_list_head_1, playernum == 1);
  commod[0] = commodcount(&build_list_head_1);
	printf("1 號玩家得分: %d分/ %d個貨物\n---\n", score[0], commod[0]);
	score[1] = score_count(&build_list_head_2, playernum == 2);
	commod[0] = commodcount(&build_list_head_2);
	printf("2 號玩家得分: %d分/ %d個貨物\n---\n", score[1], commod[1]);
	score[2] = score_count(&build_list_head_3, playernum == 3);
	commod[0] = commodcount(&build_list_head_3);
	printf("3 號玩家得分: %d分/ %d個貨物\n---\n", score[2], commod[2]);
	score[3] = score_count(&build_list_head_4, playernum == 4);
	commod[0] = commodcount(&build_list_head_4);
	printf("4 號玩家得分: %d分/ %d個貨物\n---\n", score[3], commod[3]);

	int32_t winner[4] = {1,2,3,4};
	for(int32_t i = 0;i<4;i++){
		for(int32_t j = i;j<4;j++){
			if(score[i] < score[j]){
				int32_t tmp = winner[i];
				winner[i] = winner[j];
				winner[j] = tmp;
			}
			else if(score[i] == score[j]){
				if(commod[i]<commod[j]){
					int32_t tmp = winner[i];
				  winner[i] = winner[j];
				  winner[j] = tmp;
				}
			}
		}
	} 

	printf(YELLOW"!!!!最終結果!!!!\n"NONE);
	for(int32_t i = 0;i<4;i++){
		printf("第 %d 名: %d 號玩家", i+1, winner[i]);
    for(int32_t j = i+1;j<4;j++){
			if(score[i] == score[j] && commod[i] == commod[j]){
				printf("、%d 號玩家", winner[j]);
				i++;
			}
			else{
				printf("\n");
				break;
			}
		}
	}

	delAllplayercard(&player_list_head_1);
	delAllplayercard(&build_list_head_1);
	delAllplayercard(&player_list_head_2);
	delAllplayercard(&build_list_head_2);
	delAllplayercard(&player_list_head_3);
	delAllplayercard(&build_list_head_3);
	delAllplayercard(&player_list_head_4);
	delAllplayercard(&build_list_head_4);

  return 0;
}