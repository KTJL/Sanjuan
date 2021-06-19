#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "linuxlist.h"
#include "Card.h"

typedef struct Player_card
{
	int32_t id;
	char name[128];
	int32_t fee;
	int32_t score;
  char tip[5096];
	int32_t commodity;

	struct list_head list;
	
}_splayer_card;

int32_t welcome();
void start(struct list_head *player_list_head_1, struct list_head *player_list_head_2, struct list_head *player_list_head_3, struct list_head *player_list_head_4, struct list_head *build_list_head_1, struct list_head *build_list_head_2, struct list_head *build_list_head_3, struct list_head *build_list_head_4);

_splayer_card *add_newcard(_sbuild *building);
_sbuild *draw_card();
void gameround(int32_t roundnum, const int32_t playernum, const int32_t tradecardnum, struct list_head *player_list_head_1, struct list_head *player_list_head_2, struct list_head *player_list_head_3, struct list_head *player_list_head_4, struct list_head *build_list_head_1, struct list_head *build_list_head_2, struct list_head *build_list_head_3, struct list_head *build_list_head_4);

void print_table(struct list_head *player_list_head_1, struct list_head *player_list_head_2, struct list_head *player_list_head_3, struct list_head *player_list_head_4,struct list_head *build_list_head_1, struct list_head *build_list_head_2, struct list_head *build_list_head_3, struct list_head *build_list_head_4, const int32_t player);//畫面
int32_t print_handcard(struct list_head *player_list_head, const int32_t player);//印手牌、計算卡數
int32_t print_build(struct list_head *build_list_head);

uint32_t choose_role(uint32_t *choseptr, uint32_t player);
_splayer_card *choose_card(struct list_head *player_list_head, const int32_t player);
void lost_card(struct list_head *player_list_head, struct list_head *choosecard, const int32_t player);//丟牌
void lost_commod(struct list_head *build_list_head, const int32_t player);//丟貨
//建築師
void Builder_func(const int32_t sp, const int32_t player, struct list_head *player_list_head, struct list_head *build_list_head);
int32_t normal_build(int32_t cardfee, _splayer_card *choosecard, struct list_head *player_list_head, struct list_head *build_list_head, const int32_t player);
void Smithy(int32_t *feeptr, const int32_t player);
void Poor_house(struct list_head *player_list_head, const int32_t player);
void Black_market(struct list_head *build_list_head, int32_t *feeptr, int32_t commodnum, const int32_t player);
void Crane(int32_t cardfee, int32_t *feeptr, struct list_head *build_list_head, const int32_t player);
void Carpenter(struct list_head *player_list_head, const int32_t player);
void Quarry(int32_t *feeptr, const int32_t player);
void build_Library(int32_t *feeptr, const int32_t player);
//生產者
void Producer_func(const int32_t sp, const int32_t player, struct list_head *player_list_head, struct list_head *build_list_head, int32_t facnum);
int32_t normal_produce(_splayer_card *choosecard, struct list_head *build_list_head,const int32_t player);
void Well(struct list_head *player_list_head, const int32_t player);
void Aqueduct(int32_t *comptr, const int32_t player);
void produce_Library(int32_t *comptr, int32_t facnum, const int32_t player);
//商人
void Trader_func(const int32_t sp, const int32_t player, const int32_t tradecardnum, struct list_head *player_list_head, struct list_head *build_list_head, int32_t commodnum);
int32_t normal_trade(_splayer_card *choosecard, struct list_head *player_list_head,const int32_t player, const int32_t tradecardnum);
void Market_stand(struct list_head *player_list_head, const int32_t player);
void Market_hall(struct list_head *player_list_head, const int32_t player);
void Trading_post(int32_t *soldptr, const int32_t player);
void trade_Library(int32_t *soldptr, int32_t commodnum, const int32_t player);
//市長
void Councilor_func(const int32_t sp, const int32_t player, struct list_head *player_list_head, struct list_head *build_list_head);
int32_t normal_council(const int32_t chosenum, const int32_t drawnum, struct list_head *player_list_head, const int32_t player, const int32_t ar); 
int32_t Archive(const int32_t player);
void Prefecture(int32_t *choseptr, const int32_t player);
void council_Library(int32_t *drawptr, const int32_t player);
//淘金者
void Prospector_func(const int32_t player, struct list_head *player_list_head, struct list_head *build_list_head);
int32_t normal_prospect(int32_t drawnum, struct list_head *player_list_head);
void Gold_mine(struct list_head *player_list_head, const int32_t player);
void prospect_Library(int32_t *drawptr, struct list_head *player_list_head,  const int32_t player);

void delAllplayercard(struct list_head *player_list_head);
/*
int32_t end_game(struct list_head *player_list_head_1, struct list_head *player_list_head_2, struct list_head *player_list_head_3, struct list_head *player_list_head_4);
*/