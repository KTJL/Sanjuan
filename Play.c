#include "Play.h"
#define Player if(player == 1)
#define Robot if(player != 1)

int32_t welcome()
{
	printf("歡迎遊玩聖胡安桌遊\n");
	printf("1)遊戲規則\n2)開始遊戲\n3)退出遊戲\n(請輸入數字進行選擇):");

	int8_t option = 0;
  scanf("%hhd", &option);

	switch(option)
	{
		case 1:
		  system("firefox gamerule.html");
		case 2:
			return 2;
		  break;
		case 3:
		  return 3;
		  break;
		default:
		  printf("無效輸入!\n");
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
		  return 1;
			break;
	}

}

void start(struct list_head *player_list_head_1, struct list_head *player_list_head_2, struct list_head *player_list_head_3, struct list_head *player_list_head_4, struct list_head *build_list_head_1, struct list_head *build_list_head_2, struct list_head *build_list_head_3, struct list_head *build_list_head_4)
{
	//發染料廠卡
  for(int32_t i = 0;i<4;i++)
	{
		_splayer_card *newcard = add_newcard(&building[0]);

		if(i == 0)
    list_add(&(newcard->list), build_list_head_1);
		else if(i == 1)
		list_add(&(newcard->list), build_list_head_2);
		else if(i == 2)
		list_add(&(newcard->list), build_list_head_3);
		else if(i == 3)
		list_add(&(newcard->list), build_list_head_4);

		(&building[0])->num --;
		//printf("%d\n", (&building[0])->num);
	}
  
	//各抽4張
  srand(time(0));
	for(int32_t i = 0;i<4;i++)
	{//printf("%d\n", i);
		for(int32_t j = 0;j<4;j++)
		{
			_sbuild *drawcard = draw_card();
      _splayer_card *newcard = add_newcard(drawcard);

			if(i == 0)
      list_add(&(newcard->list), player_list_head_1);
			else if(i == 1)
			list_add(&(newcard->list), player_list_head_2);
			else if(i == 2)
			list_add(&(newcard->list), player_list_head_3);
			else if(i == 3)
			list_add(&(newcard->list), player_list_head_4);

			drawcard->num --;
		}
	}

  return;
}

_splayer_card *add_newcard(_sbuild *building)//加卡
{
    _splayer_card *newcard = malloc(sizeof(_splayer_card));
		newcard->id = building->id;
		strncpy(newcard->name, building->name, strlen(building->name));
		newcard->fee = building->fee;
		newcard->score = building->score;
		strncpy(newcard->tip, building->tip, strlen(building->tip));

		if((building->id > 0 && building->id < 6) || building->id == 7)
		{
			newcard->commodity = 0;
		}
		else
		{
			newcard->commodity = -1;
		}

    return newcard;
}

_sbuild *draw_card()//抽卡
{
	int32_t draw = 1;
	int32_t lucky_num = 0;
	_sbuild *drawcard;

  while(draw == 1)
	{
		lucky_num = rand()%29;
    //printf("%d ", lucky_num);
    if((&building[lucky_num])->num == 0)
		continue;
		else if((&building[lucky_num])->num > 0)
		draw = 0;
	}
	drawcard = &building[lucky_num];
	//printf("抽卡測:%s\n", drawcard->name);
	return drawcard;
}

void gameround(int32_t roundnum, const int32_t playernum, struct list_head *player_list_head_1, struct list_head *player_list_head_2, struct list_head *player_list_head_3, struct list_head *player_list_head_4, struct list_head *build_list_head_1, struct list_head *build_list_head_2, struct list_head *build_list_head_3, struct list_head *build_list_head_4)
{
	printf("-----------------\nRound %d\n\n", roundnum);

	int32_t mayor = roundnum%4;
	if(mayor == 0)
	{
		mayor = 4;
    printf("總督: %d號\n", mayor);
		mayor = 0;
	}
	else
	printf("總督: %d號\n", mayor);
	//檢查牌數、禮拜堂
	if(roundnum >= 2)
	{
	}
	//印桌
	//選角、執行
	uint32_t player_role[4] = {0};
	uint32_t chose_role = 0;
	uint32_t *choseptr = &chose_role;
	for(int32_t i = roundnum;i<roundnum+4;i++)
	{ //選角(4號->i%4 = 0)
		printf(">>>>>\n");
		player_role[i%4] = choose_role(choseptr, playernum%4 == i%4);
		chose_role = chose_role | (1 << player_role[i%4]);
    print_table(build_list_head_1, build_list_head_2, build_list_head_3, build_list_head_4);
    if(player_role[i%4]-1 == Builder)
		{
			for(int32_t j = i%4;j < (i%4) + 4;j++)
			{
				if(j%4 == 0)printf("---\n 4 號玩家\n");
				else printf("---\n %d 號玩家\n", j%4);
				if(playernum%4 != j%4) sleep(5);

				if(j%4 == 0 && list_empty(player_list_head_4) == 0)
				Builder_func(j == i%4, playernum%4 == j%4,  player_list_head_4, build_list_head_4);
				else if(j%4 == 1 && list_empty(player_list_head_1) == 0)
        Builder_func(j == i%4, playernum%4 == j%4,  player_list_head_1, build_list_head_1);
				else if(j%4 == 2 && list_empty(player_list_head_2) == 0)
				Builder_func(j == i%4, playernum%4 == j%4,  player_list_head_2, build_list_head_2);
				else if(j%4 == 3 && list_empty(player_list_head_3) == 0)
				Builder_func(j == i%4, playernum%4 == j%4,  player_list_head_3, build_list_head_3);
			}
		}
		else if(player_role[i%4]-1 == Producer)
		{
			for(int32_t j = i%4;j < (i%4) + 4;j++)
			{
				if(j%4 == 0)printf("---\n 4 號玩家\n");
				else printf("---\n %d 號玩家\n", j%4);
				if(playernum%4 != j%4) sleep(5);

				int32_t facnum = 0;
				if(j %4 == 0){
					struct list_head *listptr = NULL;					
					list_for_each(listptr, build_list_head_4)//是否有工廠
					{
						_splayer_card *cptr =  list_entry(listptr, _splayer_card, list);
						if(cptr->id <= 5 && cptr->commodity == 0)
						facnum ++;
					}
					if(facnum != 0)
					Producer_func(j == i%4, playernum%4 == j%4,  player_list_head_4, build_list_head_4, facnum);
				}
				else if(j %4 == 1){
					struct list_head *listptr = NULL;					
					list_for_each(listptr, build_list_head_1)//是否有工廠
					{
						_splayer_card *cptr =  list_entry(listptr, _splayer_card, list);
						if(cptr->id <= 5 && cptr->commodity == 0)
						facnum ++;
					}
					if(facnum != 0)
					Producer_func(j == i%4, playernum%4 == j%4,  player_list_head_1, build_list_head_1, facnum);
				}
				else if(j %4 == 2){
					struct list_head *listptr = NULL;					
					list_for_each(listptr, build_list_head_2)//是否有工廠
					{
						_splayer_card *cptr =  list_entry(listptr, _splayer_card, list);
						if(cptr->id <= 5 && cptr->commodity == 0)
						facnum ++;
					}
					if(facnum != 0)
					Producer_func(j == i%4, playernum%4 == j%4,  player_list_head_2, build_list_head_2, facnum);
				}
				else if(j %4 == 3){
					struct list_head *listptr = NULL;					
					list_for_each(listptr, build_list_head_3)//是否有工廠
					{
						_splayer_card *cptr =  list_entry(listptr, _splayer_card, list);
						if(cptr->id <= 5 && cptr->commodity == 0)
						facnum ++;
					}
					if(facnum != 0)
					Producer_func(j == i%4, playernum%4 == j%4,  player_list_head_3, build_list_head_3, facnum);
				}
			}
		}
		else if(player_role[i%4]-1 == Trader)
		{
			//Trader_func();
		}
		else if(player_role[i%4]-1 == Counciler)
		{
			//Counciler_func();
		}
		else if(player_role[i%4]-1 == Prospector)
		{
			//Prospector_func();
		}
		
	}

	return;
}

uint32_t choose_role(uint32_t *choseptr, uint32_t player)//選角
{
	uint32_t role = 0;
	if(player == 1)
	{
		printf("\n請選擇職業:\n");
		if(((*choseptr >> (Builder+1)) & 1) == 0)
		printf("1) 建築師\n");
		if(((*choseptr >> (Producer+1)) & 1) == 0)
		printf("2) 生產者\n");
		if(((*choseptr >> (Trader+1)) & 1) == 0)
		printf("3) 商人\n");
		if(((*choseptr >> (Counciler+1)) & 1) == 0)
		printf("4) 市長\n");
		if(((*choseptr >> (Prospector+1)) & 1) == 0)
		printf("5) 淘金者\n");

		printf("(請輸入數字進行選擇):");//----------輸入無效
		while(scanf("%d", &role) != 1 || ((*choseptr >> role)&1) == 1 || role > 5 || role < 1)
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("選擇無效!請選擇職業:\n");
		  if(((*choseptr >> (Builder+1)) & 1) == 0)
		  printf("1) 建築師\n");
			if(((*choseptr >> (Producer+1)) & 1) == 0)
			printf("2) 生產者\n");
			if(((*choseptr >> (Trader+1)) & 1) == 0)
			printf("3) 商人\n");
			if(((*choseptr >> (Counciler+1)) & 1) == 0)
			printf("4) 市長\n");
			if(((*choseptr >> (Prospector+1)) & 1) == 0)
			printf("5) 淘金者\n");

			printf("(請輸入數字進行選擇):");
		}
	}
	else
	{
		while(role == 0 || ((*choseptr >> role) & 1) == 1 )
		{
			role = rand()%5 + 1;
		}
	}
  printf("職業: ");
	switch(role){
		case 1:
			printf("建築師\n");
			break;
		case 2:
			printf("生產者\n");
			break;
		case 3:
			printf("商人\n");
			break;
		case 4:
			printf("市長\n");
			break;
		case 5:
			printf("淘金者\n");
			break;
		default:
			break;
	}
	return role;
}
_splayer_card *choose_card(struct list_head *player_list_head, const int32_t player)//選卡
{
	int32_t cardnum = 0;
	int32_t count = print_handcard(player_list_head, player);
	Player{
		printf("\n(輸入卡片編號進行選擇):");
		while(scanf("%d", &cardnum) != 1 || cardnum <= 0|| cardnum > count)
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("輸入無效!(輸入卡片編號進行選擇):");
		}	
	}
	Robot{
		cardnum = rand()%count + 1;
	}
	
	struct list_head *listptr = NULL;
	count = 1;
	list_for_each(listptr, player_list_head)
	{
		if(count == cardnum)
		{
			_splayer_card *choosecard = list_entry(listptr, _splayer_card, list);
			return choosecard;
		}
		count ++;
	}
  
	return NULL;
}
void lost_card(struct list_head *player_list_head, struct list_head *choosecard, const int32_t player)
{
	printf("選擇欲丟出的手牌--\n");
	_splayer_card *lostcard = choose_card(player_list_head, player);

	while(lostcard == NULL || &(lostcard->list) == choosecard)
	{
		printf("選擇無效!選擇欲丟出的手牌--\n");
		lostcard = choose_card(player_list_head, player);
	}

	list_del(&(lostcard->list));
	free(lostcard);

	return;
}
void lost_commod(struct list_head *build_list_head, const int32_t player)
{
	_splayer_card *lostcommod = choose_card(build_list_head, player);
	while(lostcommod == NULL || lostcommod->commodity != 1)
	{
		lostcommod = choose_card(build_list_head, player);
	}

	lostcommod->commodity = 0;

	return;
}
//建築師
void Builder_func(const int32_t sp, const int32_t player,  struct list_head *player_list_head, struct list_head *build_list_head)
{
	int32_t sp_building = 0;//是否有特殊建築
	struct list_head *listptr = NULL;
	list_for_each(listptr, build_list_head)
	{
		_splayer_card *bptr = list_entry(listptr, _splayer_card, list);
		if((bptr->id >= 8 && bptr->id <= 13) || bptr->id == 22)
		{
			sp_building = sp_building | (1 << bptr->id);
		}
	}

  int8_t sp_option = 0;
	int8_t option = 0;
	printf("\n是否執行一般行動-建造1棟建築，根據建築卡上的所示費用，支付對應手牌張數?\n1)是 2)否\n(請輸入數字進行選擇):");
	
	Player{
		while(scanf("%hhd", &option) != 1 || option > 2 || option < 1)
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("選擇無效!是否執行一般行動-建造1棟建築，根據建築卡上的所示費用，支付對應手牌張數?\n1)是 2)否\n(請輸入數字進行選擇):");
		}
	}
	Robot{
		option = rand()%2 + 1;
		printf("%d\n", option);
	}


	if(sp == 1 && option == 1)//選擇特權
	{
		printf("\n是否執行特權行動-根據建築卡上的所示費用，支付對應手牌張數時，可減少支付1張手牌，但建築最後支付的費用不能少於0?\n1)是 2)否\n(請輸入數字進行選擇):");

		Player{
			while(scanf("%hhd", &sp_option) != 1 || sp_option > 2 || sp_option < 1)
			{
				char c;
	  		while (( c = getchar()) != EOF && c != '\n'){}
				printf("選擇無效!是否執行特權行動-根據建築卡上的所示費用，支付對應手牌張數時，可減少支付1張手牌，但建築最後支付的費用不能少於0?\n1)是 2)否\n(請輸入數字進行選擇):");
			}
		}
		Robot{
			sp_option = rand()%2 + 1;
			printf("%d\n", sp_option);
		}
	} 
    
	int32_t action = 2;
	while(option == 1 && action == 2)
	{
		_splayer_card *choosecard = choose_card(player_list_head, player);
		if(choosecard == NULL)
		{
			printf("選擇失敗!\n");
			break;
		}

		if((sp_building >> (choosecard->id) & 1 )== 1){//是否已有該特殊建築
			printf("\n已有一棟該特殊建築!\n1)重新選擇\n2)放棄執行\n(請輸入數字進行選擇):");
			
			Player{
				while(scanf("%hhd", &option) != 1 || option > 2 || option < 1)
				{
					char c;
	  			while (( c = getchar()) != EOF && c != '\n'){}
					printf("選擇無效!已有一棟該特殊建築!\n1)重新選擇\n2)放棄執行\n(請輸入數字進行選擇):");
				} 
			}
			Robot{
				option = 2;
				printf("%d\n", option);
			}

			if(option == 1)
			continue;
			else if(option == 2)
			break;
	  }
		
		int32_t cardfee = choosecard->fee;
		int32_t *feeptr = &cardfee;
		//特殊功能
		if(sp_option == 1)//特權
		cardfee --;
		if(((sp_building << 8) & 1 )== 1  && cardfee > 0 && choosecard -> id <= 5)
		Smithy(feeptr, player);//鐵匠
		if(((sp_building << 13) & 1 )== 1 && cardfee > 0 && choosecard->id > 5)
		Quarry(feeptr, player);//採石場
    if(((sp_building << 22) & 1 )== 1 && cardfee > 0)//圖書館
		{
			_splayer_card *librarycard = NULL;
			listptr = NULL;
			list_for_each(listptr, build_list_head)
			{
				librarycard = list_entry(listptr, _splayer_card, list);
				if(librarycard->id == 22)
				break;
			}
			build_Library(feeptr, librarycard, player);
		}
		if(((sp_building << 11) & 1 )== 1 && (list_empty(build_list_head) == 0))
		Crane(cardfee, feeptr, build_list_head, player);//起重機

		int32_t commod = 0;//是否有貨物
		listptr = NULL;
		list_for_each(listptr, build_list_head)
		{
			_splayer_card *cptr =  list_entry(listptr, _splayer_card, list);
			if(cptr->commodity == 1)
			{
				commod ++;
			}
  	}
		if(((sp_building << 10) & 1 )== 1 && commod != 0 )
		Black_market(build_list_head, feeptr, commod, player);//黑市
			
		if(((sp_building << 12) & 1 )== 1 && choosecard->id > 5)
		Carpenter(player_list_head, player);//木工場

		action = normal_build(cardfee, choosecard, player_list_head, build_list_head, player);//建造行動
      
		if(action == 1)
		{
			int32_t count = 0;//手牌不超過1張
			listptr = NULL;
			list_for_each(listptr, player_list_head)
			count++;
			if(((sp_building << 9) & 1 )== 1 && count <= 1)
			Poor_house(player_list_head, player);//救濟院
		}
	}

	return;
}
int32_t normal_build(int32_t cardfee, _splayer_card *choosecard, struct list_head *player_list_head, struct list_head *build_list_head, const int32_t player)
{	//printf("347\n");
	int32_t count = 0;
	struct list_head *lisptr = NULL;
	list_for_each(lisptr, player_list_head)
	count++;
  if(count <= cardfee)//判斷手牌是否足夠
	{
		int8_t option = 0;
		printf("\n沒有足夠手牌!\n1)重新選擇\n2)放棄執行\n(請輸入數字進行選擇):");

		Player{
			while(scanf("%hhd", &option) != 1 || option > 2 || option < 1)
			{
				char c;
	  		while (( c = getchar()) != EOF && c != '\n'){}
				printf("選擇無效!沒有足夠手牌!\n1)重新選擇\n2)放棄執行\n(請輸入數字進行選擇):");
			}	
		}
		Robot{
			option = 2;
			printf("%d\n", option);
		}
		
		if(option == 1)
		return 2;
		else
		return 0;
	}

	for(int32_t i =0;i<cardfee;i++)//丟卡
	lost_card(player_list_head, &(choosecard->list), player);

  _splayer_card *newbuild = add_newcard(&building[choosecard->id - 1]);			
	list_add(&(newbuild->list), build_list_head);
	list_del(&(choosecard->list));
	free(choosecard);
  //printf("401\n");
	return 1;
}
void Smithy(int32_t *feeptr, const int32_t player)
{
	int8_t option = 0;
	
	Player{
		printf("\n你有鐵匠鋪!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[7].tip);
		while(scanf("%hhd", &option) != 1 || option > 2 || option < 1)
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("無效選擇!你有鐵匠鋪!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[7].tip);
		}	
	}
	Robot{
		option = rand()%2 + 1;
	}
	
	if(option == 1)
	*feeptr -= 1;

	return;
}
void Poor_house(struct list_head *player_list_head, const int32_t player)
{
	int8_t option = 0;
	
	Player{
		printf("\n你有救濟院!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[8].tip);
		while(scanf("%hhd", &option) != 1 || option > 2 || option < 1)
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("無效選擇!你有救濟院!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[8].tip);
		}	
	}
	Robot{
		option = rand()%2 + 1;
	}
	
	if(option == 1)
	{
		_sbuild *drawcard = draw_card();
		_splayer_card *newcard = add_newcard(drawcard);
		list_add(&(newcard->list), player_list_head);

		drawcard->num --;
	}

	return;
}
void Black_market(struct list_head *build_list_head, int32_t *feeptr, int32_t commodnum, const int32_t player)
{
	int8_t option = 0;
	
	Player{
		printf("\n你有黑市!是否執行特殊行動-%s\n使用 0)0張 1)1張 2)2張\n(請輸入數字進行選擇):", building[9].tip);
		while(scanf("%hhd", &option) != 1 || option > commodnum)
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("無效選擇!你有黑市!是否執行特殊行動-%s\n使用 0)0張 1)1張 2)2張\n(請輸入數字進行選擇):", building[9].tip);
		}	
	}
	Robot{
		option = rand()%3;
		while(option > commodnum)
		{
			option = 0;
		}
	}
	
	for(int32_t i = 0;i<option;i++)
	{
		lost_commod(build_list_head, player);
	}
	*feeptr -= option;

	return;
}
void Crane(int32_t cardfee, int32_t *feeptr, struct list_head *build_list_head, const int32_t player)
{
	int8_t option = 0;

	Player{
		printf("\n你有起重機!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[10].tip);
		while(scanf("%hhd", &option) != 1 || option > 2 || option < 1)
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("無效選擇!你有起重機!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[10].tip);
		}	
	}
	Robot{
		option = rand()%2 + 1;
	}

	if(option == 1)
	{
		_splayer_card *lostbuild = choose_card(build_list_head, player);
		if(lostbuild == NULL || lostbuild->fee < cardfee)
		{
		  printf("\n使用失敗!\n");
			return;
		}

		*feeptr = lostbuild->fee - cardfee;
		list_del(&(lostbuild->list));
		free(lostbuild);
	}

	return;
}
void Carpenter(struct list_head *player_list_head, const int32_t player)
{
	int8_t option = 0;

	Player{
		printf("\n你有木工場!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[11].tip);
		while(scanf("%hhd", &option) != 1 || option > 2 || option < 1)
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("無效選擇!你有木工場!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[11].tip);
		}	
	}
	Robot{
		option = rand()%2 + 1;
	}

	if(option == 1)
	{
		_sbuild *drawcard = draw_card();
		_splayer_card *newcard = add_newcard(drawcard);
		list_add(&(newcard->list), player_list_head);

		drawcard->num --;
	}

	return;
}
void Quarry(int32_t *feeptr, const int32_t player)
{
	int8_t option = 0;

	Player{
		printf("\n你有採石場!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[12].tip);
		while(scanf("%hhd", &option) != 1 || option > 2 || option < 1)
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("無效選擇!你有採石場!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[12].tip);
		}	
	}
	Robot{
		option = rand()%2 + 1;
	}

	if(option == 1)
	*feeptr -= 1;

	return;
}
void build_Library(int32_t *feeptr, _splayer_card *librarycard, const int32_t player)
{
	int8_t option = 0;

	Player{
		printf("\n你有圖書館!是否執行特殊行動-建造建築物時可少支付2張手牌\n1)是 2)否\n(請輸入數字進行選擇):");
		while(scanf("%hhd", &option) != 1 || option > 2 || option < 1)
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("無效選擇!你有圖書館!是否執行特殊行動-建造建築物時可少支付2張手牌\n1)是 2)否\n(請輸入數字進行選擇):");
		}
	}
	Robot{
		option = rand()%2 + 1;
	}
	
	if(option == 1)
	{
		*feeptr -= 2;
		librarycard->id = 220;
	}
	
	return;
}
//生產者
void Producer_func(const int32_t sp, const int32_t player, struct list_head *player_list_head, struct list_head *build_list_head, int32_t facnum){

	int32_t sp_building = 0;//是否有特殊建築
	struct list_head *listptr = NULL;
	list_for_each(listptr, build_list_head)
	{
		_splayer_card *bptr = list_entry(listptr, _splayer_card, list);
		if((bptr->id >= 14 && bptr->id <= 15) || bptr->id == 22)
		{
			sp_building = sp_building | (1 << bptr->id);
		}
	}

  int8_t sp_option = 0;
	int8_t option = 0;
	printf("\n是否執行一般行動-生產1個貨品(即從卡牌堆上方抽取1張卡牌，正面朝下直接置於自家生產建築物下方，玩家不能偷看內容)?\n1)是 2)否\n(請輸入數字進行選擇):");
	
	Player{
		while(scanf("%hhd", &option) != 1 || option > 2 || option < 1)
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("選擇無效!是否執行一般行動-生產1個貨品(即從卡牌堆上方抽取1張卡牌，正面朝下直接置於自家生產建築物下方，玩家不能偷看內容)?\n1)是 2)否\n(請輸入數字進行選擇):");
		}
	}
	Robot{
		option = rand()%2 + 1;
		printf("%d\n", option);
	}


	if(sp == 1 && option == 1 && facnum > 1)//選擇特權
	{
		printf("\n是否執行特權行動-可生產2個貨品?\n1)是 2)否\n(請輸入數字進行選擇):");

		Player{
			while(scanf("%hhd", &sp_option) != 1 || sp_option > 2 || sp_option < 1)
			{
				char c;
	  		while (( c = getchar()) != EOF && c != '\n'){}
				printf("選擇無效!可生產2個貨品?\n1)是 2)否\n(請輸入數字進行選擇):");
			}
		}
		Robot{
			sp_option = rand()%2 + 1;
			printf("%d\n", sp_option);
		}
	} 
    
	int32_t action = 2;
	while(option == 1 && action == 2)
	{
		int32_t commodnum = 1;
		int32_t *comptr = &commodnum;
		//特殊功能
		if(sp_option == 1 && facnum > commodnum)//特權
		commodnum ++;
		if(((sp_building << 15) & 1 )== 1  && facnum > commodnum)
		Aqueduct(comptr, player);//溝渠
    if(((sp_building << 22) & 1 )== 1 && facnum > commodnum && commodnum < 3)//圖書館
		{
			_splayer_card *librarycard = NULL;
			listptr = NULL;
			list_for_each(listptr, build_list_head)
			{
				librarycard = list_entry(listptr, _splayer_card, list);
				if(librarycard->id == 22)
				break;
			}
			produce_Library(comptr, facnum, librarycard, player);
		}

		for(int32_t i = 0;i < commodnum;i++){//產貨

			_splayer_card *choosecard = choose_card(build_list_head, player);
			if(choosecard == NULL)
			{
				printf("選擇失敗!\n");
				break;
			}

			if(choosecard->id > 5 || choosecard-> commodity != 0){//無法產貨
				
				printf("\n該建築無法生產貨物!\n1)重新選擇\n2)放棄執行(會保留已生產貨物)\n(請輸入數字進行選擇):");
				
				Player{
					while(scanf("%hhd", &option) != 1 || option > 2 || option < 1)
					{
						char c;
	  				while (( c = getchar()) != EOF && c != '\n'){}
						printf("選擇無效!該建築無法生產貨物!\n1)重新選擇\n2)放棄執行(會保留已生產貨物)\n(請輸入數字進行選擇):");
					} 
				}
				Robot{
					option = rand()%2 + 1;
					printf("%d\n", option);
				}

				if(option == 1)
				{
					i--;
					continue;
				}
				else if(option == 2)
				break;
			}
			else
			action = normal_produce(choosecard, build_list_head, player);//生產行動
		}

		int32_t commod = 0;//是否有貨物
		listptr = NULL;
		list_for_each(listptr, build_list_head)
		{
			_splayer_card *cptr =  list_entry(listptr, _splayer_card, list);
			if(cptr->commodity == 1)
			{
				commod ++;
			}
  	}
		if(((sp_building << 14) & 1 )== 1 && commod >= 2 )
		Well(player_list_head, player);//水井
	}

	return;
}
int32_t normal_produce(_splayer_card *choosecard, struct list_head *build_list_head, int32_t player){
	choosecard->commodity = 1;
	_sbuild *commod = draw_card();
	commod->num --;
	return 1;
}
void Well(struct list_head *player_list_head, const int32_t player){
	int8_t option = 0;
	
	Player{
		printf("\n你有水井!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[13].tip);
		while(scanf("%hhd", &option) != 1 || option > 2 || option < 1)
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("無效選擇!你有水井!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[13].tip);
		}	
	}
	Robot{
		option = rand()%2 + 1;
	}
	
	if(option == 1)
	{
		_sbuild *drawcard = draw_card();
		_splayer_card *newcard = add_newcard(drawcard);
		list_add(&(newcard->list), player_list_head);

		drawcard->num --;
	}

	return;
}
void Aqueduct(int32_t *comptr, int32_t player){
	int8_t option = 0;

	Player{
		printf("\n你有溝渠!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[14].tip);
		while(scanf("%hhd", &option) != 1 || option > 2 || option < 1)
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("無效選擇!你有溝渠!是否執行特殊行動-%s\n1)是 2)否\n(請輸入數字進行選擇):", building[14].tip);
		}	
	}
	Robot{
		option = rand()%2 + 1;
	}

	if(option == 1)
	*comptr += 1;

	return;
}
void produce_Library(int32_t *comptr, int32_t facnum, _splayer_card *librarycard, const int32_t player){
	int8_t option = 0;

	Player{
		printf("\n你有圖書館!是否執行特殊行動-至多生產3個貨物\n生產 1)1個 2)2個 3)3個 4)否\n(請輸入數字進行選擇):");
		while(scanf("%hhd", &option) != 1 || option > 4 || option < 1 || (option != 4 &&(option > facnum || option <= *comptr)) )
		{
			char c;
	  	while (( c = getchar()) != EOF && c != '\n'){}
			printf("無效選擇!你有圖書館!是否執行特殊行動-至多生產3個貨物s\n生產 1)1個 2)2個 3)3個 4)否\n(請輸入數字進行選擇):");
		}
	}
	Robot{
		option = rand()%4 + 1;
		while(option != 4 && (option > facnum || option <= *comptr))
		option = rand()%4 + 1;
	}
	
	if(option <= 3 )
	{
		*comptr = option;
		librarycard->id = 220;
	}
	
	return;
}

void print_table(struct list_head *build_list_head_1, struct list_head *build_list_head_2, struct list_head *build_list_head_3, struct list_head *build_list_head_4)
{
	/*for(int32_t i = 0;i < 20;i++)
	{
		printf("-- ");
	}*/
  
	for(int32_t i = 0;i<4;i++){
		printf("%d\n", i+1);
		switch(i){
			case 0:
			print_build(build_list_head_1);
			break;
			case 1:
			print_build(build_list_head_2);
			break;
			case 2:
			print_build(build_list_head_3);
			break;
			case 3:
			print_build(build_list_head_4);
			break;
			default:
			break;
		}
	}
	printf("(0:0個貨物(卡片)/1:1個貨物(卡片)/-1:無法生產貨物)\n");
	return;
}
int32_t print_handcard(struct list_head *player_list_head, const int32_t player)
{
	Player{
		printf("\n編號 /名字\t/建設費用/得分\t/技能\n");
	}
  int32_t count = 1;
	struct list_head *lisptr = NULL;
	list_for_each(lisptr, player_list_head)
	{
		_splayer_card *card = list_entry(lisptr, _splayer_card, list);
		Player{
			printf("%d\t/%s\t/\t  %d/\t%d\t/%s\n", count, card->name, card->fee, card->score, card->tip);
		}
		count++;
	}
	Player printf("(得分0為視情況得分)\n");

	return count-1;
}
int32_t print_build(struct list_head *build_list_head)
{
	int32_t count = 1;
	struct list_head *lisptr = NULL;
	list_for_each(lisptr, build_list_head)
	{
		_splayer_card *card = list_entry(lisptr, _splayer_card, list);
		printf("\t%d)%s:\t%d\n", count, card->name, card->commodity);
		count++;
	}

	return count;
}
/*
int32_t end_game(struct list_head *build_list_head_1, struct list_head *build_list_head_2, struct list_head *build_list_head_3, struct list_head *build_list_head_4)
{
	int32_t game = 1;
	for(int32_t i = 0;i<4;i++)
	{
		int32_t count = 0;
		struct list_head *listptr = NULL;

		if(i == 0)
		{
			list_for_each(listptr, build_list_head_1);
			count++;
		}
		else if(i == 1)
		{
			list_for_each(listptr, build_list_head_2);
			count++;
		}
		else if(i == 2)
			{
			list_for_each(listptr, build_list_head_3);
			count++;
		}
		else if(i == 3)
		{
			list_for_each(listptr, build_list_head_4);
			count++;
		}

		if(count >= 12)
		{
			game = 0;
			break;
		}
	}
	return game;
}*/