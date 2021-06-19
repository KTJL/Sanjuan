#pragma once

#include <stdio.h>
#include <stdint.h>

enum role_card
{
	Builder,
	Producer,
	Trader,
  Councilor,
	Prospector,
};
/*
typedef struct produce_building
{
	int32_t id;
	char name[128];
  int32_t fee;
	int32_t score;
	int32_t num;

}_sfactory;
*/
typedef struct Building
{
	int32_t id;
	char name[128];
  int32_t fee;
	int32_t score;
	int32_t num;
	char tip[5096];

}_sbuild;

typedef struct _cost_card
{
	int32_t value[5];
}cost_card;

cost_card valuecards[5] = {{1,2,2,3,3}, {1,1,2,2,3}, {1,2,2,2,3}, {1,1,1,2,2}, {1,1,2,2,2}};

_sbuild building[29] = { 
	{1,"染料廠", 1, 1, 10, "可生產一份貨物"}, 
	{2,"蔗糖廠", 2, 1, 8, "可生產一份貨物"},
	{3,"菸草廠", 3, 2, 8, "可生產一份貨物"},
	{4,"咖啡廠", 4, 2, 8, "可生產一份貨物"},
	{5,"白銀廠", 5, 3, 8, "可生產一份貨物"},
	{6,"塔樓", 3, 2, 3, "各回合玩家計算手牌前，已打出此張卡牌的玩家手牌上限可增加至12張"},
	{7,"禮拜堂", 3, 2, 3, "各回合玩家計算手牌前，已打出此張卡牌的玩家可挑選其中1張手牌正面朝下置於此張卡牌底下"},
	{8,"鐵匠鋪", 1, 1, 3, "建築師階段時，已打出此張卡牌的玩家在建造生產建築物時可少支付1張手牌"},
	{9,"救濟院", 2, 1, 3, "建築師階段時，已打出此張卡牌的玩家在行動完成後，若玩家手牌張數不多於1張時，可從卡牌堆抽取1張卡牌加入手牌"},
	{10,"黑市", 2, 1, 3, "建築師階段時，已打出此張卡牌的玩家最多可用2個貨品(即置於自家生產建築下方的卡牌)取代支付費用(手牌)，1個貨品只能替代1張手牌"},
	{11,"起重機", 2, 1, 3, "建築師階段時，已打出此張卡牌的玩家可支付興建新建築物與原先擁有舊建築物的費用差額，將新建築物蓋在舊建築物的上方。被覆蓋的卡牌不計分亦無效能，被覆蓋的生產建築其上方貨品則須棄置，被覆蓋的禮拜堂其上方卡牌仍可保留計分"},
	{12,"木工場", 3, 2, 3, "建築師階段時，已打出此張卡牌的玩家在建造特殊建築物時可從卡牌堆上方抽取1張卡牌"},
	{13,"採石場", 4, 2, 3, "建築師階段時，已打出此張卡牌的玩家在建造特殊建築物時可少支付1張手牌"},
	{14,"水井", 2, 1, 3, "生產者階段時，已打出此張卡牌的玩家若生產2個以上貨品，可從卡牌堆上方抽取1張卡牌加入手牌"},
  {15,"溝渠", 3, 2, 3, "生產者階段時，已打出此張卡牌的玩家可多生產1個貨品"},
	{16,"攤販", 2, 1, 3, "商人階段時，已打出此張卡牌的玩家若賣出2個以上貨品，可從卡牌堆上方抽取1張卡牌加入手牌"},
	{17,"市場", 4, 2, 3, "商人階段時，已打出此張卡牌的玩家在行動完成後，可從卡牌堆上方抽取1張卡牌加入手牌"},
	{18,"交易所", 2, 1, 3, "商人階段時，已打出此張卡牌的玩家可多賣出1個貨品"},
	{19,"檔案館", 1, 1, 3, "市長階段時，已打出此張卡牌的玩家在挑選卡牌時，可將卡牌堆上方抽取的卡牌全數加入手牌後再進行挑選，並將挑選外的其餘卡牌丟棄"},
	{20,"辦公處", 3, 2, 3, "市長階段時，已打出此張卡牌的玩家從卡牌堆上抽取卡牌後，挑選其中2張加入手牌"},
	{21,"金礦坑", 1, 1, 3, "淘金者階段時，已打出此張卡牌的玩家可在行動完成後，從卡牌堆上方翻開4張卡牌，若4張卡牌的費用皆不相同，可挑選其中1張加入手牌。但只要任2張出現相同費用，則須全數棄置"},
	{22,"圖書館", 5, 3, 3, "\n已打出此張卡牌的玩家在下列各階段行使特殊行動時，可提升其特殊行動能力\n\n建築師階段時，已打出此張卡牌的玩家建造建築物時可少支付2張手牌\n\n生產者階段時，已打出此張卡牌的玩家最多可生產3個貨品(即從卡牌堆上方抽取3張卡牌置於自家生產建築下方)\n\n商人階段時，已打出此張卡牌的玩家最多可賣出3個貨品(即最多可丟棄3張置於自家生產建築下方的卡牌，並從卡牌堆上方抽取對應貨品價格數量張數的卡牌加入手牌)\n\n市長階段時，已打出此張卡牌的玩家可從卡牌堆上方抽取8張卡牌，挑選其中1張加入手牌\n\n淘金者階段時，已打出此張卡牌的玩家可從卡牌堆上方抽取2張卡牌加入手牌"},
	{23,"雕鑄像紀念碑", 3, 3, 3, "無特殊效能"},
	{24,"勝利柱紀念碑", 4, 4, 3, "無特殊效能"},
	{25,"英雄像紀念碑", 5, 5, 3, "無特殊效能"},
	{26,"同業會館", 6, 0, 2, "遊戲結束時，已打出此張卡牌的玩家每擁有1棟生產建築物可額外獲得2分"},
	{27,"市政廳", 6, 0, 2, "遊戲結束時，已打出此張卡牌的玩家每擁有1棟特殊建築物(包括此張卡牌)可額外獲得1分"},
	{28,"凱旋門", 6, 0, 2, "遊戲結束時，已打出此張卡牌的玩家若擁有1種紀念碑卡可額外獲得4分，擁有2種紀念碑卡可額外獲得6分，擁有3種紀念碑卡可額外獲得8分"},
	{29,"宮殿", 6, 0, 2, "遊戲結束時，已打出此張卡牌的玩家可額外獲得該玩家總分的四分之一分數(採無條件捨去)"}
	}; 
/*
building[0] = {1,"染料廠", 1, 1, 10, "可生產一份貨物"};
building[1] = {2,"蔗糖廠", 2, 1, 8, "可生產一份貨物"};
building[2] = {3,"菸草廠", 3, 2, 8, "可生產一份貨物"};
building[3] = {4,"咖啡廠", 4, 2, 8, "可生產一份貨物"};
building[4] = {5,"白銀廠", 5, 3, 8, "可生產一份貨物"};*/
/*
_spbuild spbuild[29];
spbuild Tower = {6,"塔樓", 3, 2, 3, "各回合玩家計算手牌前，已打出此張卡牌的玩家手牌上限可增加至12張"};
spbuild Chapel = {7,"禮拜堂", 3, 2, 3, "各回合玩家計算手牌前，已打出此張卡牌的玩家可挑選其中1張手牌正面朝下置於此張卡牌底下"};
spbuild Smithy = {8,"鐵匠鋪", 1, 1, 3, "建築師階段時，已打出此張卡牌的玩家在建造生產建築物時可少支付1張手牌"};
spbuild Poor_house = {9,"救濟院", 2, 1, 3, "建築師階段時，已打出此張卡牌的玩家在行動完成後，若玩家手牌張數不多於1張時，可從卡牌堆抽取1張卡牌加入手牌"};
spbuild Black_market = {10,"黑市", 2, 1, 3, "建築師階段時，已打出此張卡牌的玩家最多可用2個貨品(即置於自家生產建築下方的卡牌)取代支付費用(手牌)，1個貨品只能替代1張手牌"};
spbuild Crane = {11,"起重機", 2, 1, 3, "建築師階段時，已打出此張卡牌的玩家可支付興建新建築物與原先擁有舊建築物的費用差額，將新建築物蓋在舊建築物的上方。被覆蓋的卡牌不計分亦無效能，被覆蓋的生產建築其上方貨品則須棄置，被覆蓋的禮拜堂其上方卡牌仍可保留計分"};
spbuild Carpenter = {12,"木工場", 3, 2, 3, "建築師階段時，已打出此張卡牌的玩家在建造特殊建築物時可從卡牌堆上方抽取1張卡牌"};
spbuild Quarry = {13,"採石場", 4, 2, 3, "建築師階段時，已打出此張卡牌的玩家在建造特殊建築物時可少支付1張手牌"};
spbuild Well = {14,"水井", 2, 1, 3, "生產者階段時，已打出此張卡牌的玩家若生產2個以上貨品，可從卡牌堆上方抽取1張卡牌加入手牌"};
spbuild Aqueduct = {15,"溝渠", 3, 2, 3, "生產者階段時，已打出此張卡牌的玩家可多生產1個貨品"};
spbuild Market_stand = {16,"攤販", 2, 1, 3, "商人階段時，已打出此張卡牌的玩家若賣出2個以上貨品，可從卡牌堆上方抽取1張卡牌加入手牌"};
spbuild Market_hall = {17,"市場", 4, 2, 3, "商人階段時，已打出此張卡牌的玩家在行動完成後，可從卡牌堆上方抽取1張卡牌加入手牌"};
spbuild Trading_post = {18,"交易所", 2, 1, 3, "商人階段時，已打出此張卡牌的玩家可多賣出1個貨品"};
spbuild Archive = {19,"檔案館", 1, 1, 3, "市長階段時，已打出此張卡牌的玩家在挑選卡牌時，可將卡牌堆上方抽取的卡牌全數加入手牌後再進行挑選，並將挑選外的其餘卡牌丟棄"};
spbuild Prefecture = {20,"辦公處", 3, 2, 3, "市長階段時，已打出此張卡牌的玩家從卡牌堆上抽取卡牌後，挑選其中2張加入手牌"};
spbuild Gold_mine = {21,"金礦坑", 1, 1, 3, "淘金者階段時，已打出此張卡牌的玩家可在行動完成後，從卡牌堆上方翻開4張卡牌，若4張卡牌的費用皆不相同，可挑選其中1張加入手牌。但只要任2張出現相同費用，則須全數棄置"};
spbuild Library = {22,"圖書館", 5, 3, 3, "已打出此張卡牌的玩家在下列各階段行使特殊行動時，可提升其特殊行動能力\n\n建築師階段時，已打出此張卡牌的玩家建造建築物時可少支付2張手牌\n\n生產者階段時，已打出此張卡牌的玩家最多可生產3個貨品(即從卡牌堆上方抽取3張卡牌置於自家生產建築下方)\n\n商人階段時，已打出此張卡牌的玩家最多可賣出3個貨品(即最多可丟棄3張置於自家生產建築下方的卡牌，並從卡牌堆上方抽取對應貨品價格數量張數的卡牌加入手牌)\n\n市長階段時，已打出此張卡牌的玩家可從卡牌堆上方抽取8張卡牌，挑選其中1張加入手牌\n\n淘金者階段時，已打出此張卡牌的玩家可從卡牌堆上方抽取2張卡牌加入手牌"};
spbuild Statue = {23,"雕鑄像紀念碑", 3, 3, 3, "無特殊效能"};
spbuild Victory_column = {24,"勝利柱紀念碑", 4, 4, 3, "無特殊效能"};
spbuild Hero = {25,"英雄像紀念碑", 5, 5, 3, "無特殊效能"};
spbuild Guild_hall = {26,"同業會館", 6, 0, 2, "遊戲結束時，已打出此張卡牌的玩家每擁有1棟生產建築物可額外獲得2分"};
spbuild City_hall = {27,"市政廳", 6, 0, 2, "遊戲結束時，已打出此張卡牌的玩家每擁有1棟特殊建築物(包括此張卡牌)可額外獲得1分"};
spbuild Triumhal_arch = {28,"凱旋門", 6, 0, 2, "遊戲結束時，已打出此張卡牌的玩家若擁有1種紀念碑卡可額外獲得4分，擁有2種紀念碑卡可額外獲得6分，擁有3種紀念碑卡可額外獲得8分"};
spbuild Palace = {29,"宮殿", 6, 0, 2, "遊戲結束時，已打出此張卡牌的玩家可額外獲得該玩家總分的四分之一分數(採無條件捨去)"};
*/


void print_card_tip()
{
  return;
}

