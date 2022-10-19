#include <YSI_Coding\y_hooks>

#define MAX_FISH 10

new FishNames[11][11] =
{
	"Carp", "Cat Fish", "Cod", "Conger Eel", "Barracuda", "Herring",
	"Pollack", "Salmon", "Sardine", "Swordfish", "Trout"
};

new FishName[MAX_PLAYERS][10][12];
new Float:FishWeight[MAX_PLAYERS][10];
new STREAMER_TAG_AREA:fishPier,
	STREAMER_TAG_AREA:fishSea;


new Float:arr_fishPier[] =
{
	-2097.03, 1369.58,
	-2096.94, 1411.98,
	-2157.40, 1411.99,
	-2155.20, 1366.95
};

new Float:arr_fishSea[] =
{
	-2101.26, 1591.56,
	-2107.21, 1934.81,
	-2141.58, 2071.11,
	-2328.29, 2079.46,
	-2464.23, 2016.09,
	-2537.27, 1827.07,
	-2567.89, 1656.07,
	-2541.32, 1526.11
};

enum {
	FISHPLACE_NONE,
	FISHPLACE_PIER,
	FISHPLACE_SEA
};

hook OnGameModeInit() {
	fishPier = CreateDynamicPolygon(arr_fishPier);
	fishSea = CreateDynamicPolygon(arr_fishSea);
}

stock ReturnFishPlace(playerid)
{
	if(!IsPlayerConnected(playerid))
		return FISHPLACE_NONE;

	if(IsPlayerInDynamicArea(playerid, fishPier))
		return FISHPLACE_PIER;

	if(IsPlayerInDynamicArea(playerid, fishSea))
		return FISHPLACE_SEA;
		
	return FISHPLACE_NONE;
}

FUNC::TimeFishing(playerid)
{
	if(!PlayerData[playerid][pFishing])
		return 0;

	PlayerData[playerid][pFishing] = false;
	ClearAnimations(playerid, 1);
	RemovePlayerAttachedObject(playerid, 9);

	if(!ReturnFishPlace(playerid))
		return 0;

	new SlotToUse = -1, FishNameId = random(sizeof(FishNames));
	if(FishWeight[playerid][0] == 0) SlotToUse = 0;
	else if(FishWeight[playerid][1] == 0) SlotToUse = 1;
	else if(FishWeight[playerid][2] == 0) SlotToUse = 2;
	else if(FishWeight[playerid][3] == 0) SlotToUse = 3;
	else if(FishWeight[playerid][4] == 0) SlotToUse = 4;
	else if(FishWeight[playerid][5] == 0) SlotToUse = 5;
	else if(FishWeight[playerid][6] == 0) SlotToUse = 6;
	else if(FishWeight[playerid][7] == 0) SlotToUse = 7;
	else if(FishWeight[playerid][8] == 0) SlotToUse = 8;
	else if(FishWeight[playerid][9] == 0) SlotToUse = 9;

	new gacha = random(4) + 1;

	if(ReturnFishPlace(playerid) != FISHPLACE_NONE)
	{
		if(gacha == 1)
		{
		    new Float:fWeight; 

			switch(ReturnFishPlace(playerid)) {
				case FISHPLACE_PIER: {
					new random_fish = random(7);
					switch(random_fish) {
							case 0: fWeight = RandomFloat(5.0,15.0);
							case 1: fWeight = RandomFloat(10.0,20.0);
							case 2: fWeight = RandomFloat(10.0,20.0);
							case 3: fWeight = RandomFloat(5.0,15.0);
							case 4: fWeight = RandomFloat(5.0,15.0);
							case 5: fWeight = RandomFloat(10.0,20.0);
							case 6: fWeight = RandomFloat(5.0,15.0);
							case 7: fWeight = RandomFloat(10.0,20.0);
					}
				}
				case FISHPLACE_SEA: {
					 new random_fish = random(7);
					 switch(random_fish) {
							case 0: fWeight = RandomFloat(15.0,25.0);
							case 1: fWeight = RandomFloat(20.0,30.0);
							case 2: fWeight = RandomFloat(15.0,35.0);
							case 3: fWeight = RandomFloat(15.0,40.0);
							case 4: fWeight = RandomFloat(15.0,25.0);
							case 5: fWeight = RandomFloat(20.0,33.0);
							case 6: fWeight = RandomFloat(15.0,25.0);
							case 7: fWeight = RandomFloat(15.0,34.0);
					 }
				}
				default: fWeight = 0;
			}

	        FishWeight[playerid][SlotToUse] = fWeight;
	        format(FishName[playerid][SlotToUse], 12, FishNames[FishNameId]);
	        SendClientMessageEx(playerid, COLOR_SERVER, "FISH: {FFFFFF}Kamu mendapat {FF6347}%s {FFFFFF}dengan berat {FFFF00}%.2f lbs{FFFFFF}, /myfish untuk melihat semua ikan.", FishName[playerid][SlotToUse], FishWeight[playerid][SlotToUse]);
		}
		else if(gacha == 2)
		{
			SetTimerEx("HidePlayerBox", 500, false, "dd", playerid, _:ShowPlayerBox(playerid, 0xFF000066));
			SendClientMessageEx(playerid, COLOR_RED, "* Kamu mendapat ubur-ubur yang menyengatmu!");
			SetPlayerHealth(playerid, ReturnHealth(playerid)-1);
		}
		else if(gacha == 3)
		{
		    new Float:fWeight; 

			switch(ReturnFishPlace(playerid)) {
				case FISHPLACE_PIER: {
					new random_fish = random(7);
					switch(random_fish) {
							case 0: fWeight = RandomFloat(5.0,15.0);
							case 1: fWeight = RandomFloat(10.0,20.0);
							case 2: fWeight = RandomFloat(10.0,20.0);
							case 3: fWeight = RandomFloat(5.0,15.0);
							case 4: fWeight = RandomFloat(5.0,15.0);
							case 5: fWeight = RandomFloat(10.0,20.0);
							case 6: fWeight = RandomFloat(5.0,15.0);
							case 7: fWeight = RandomFloat(10.0,20.0);
					}
				}
				case FISHPLACE_SEA: {
					 new random_fish = random(7);
					 switch(random_fish) {
							case 0: fWeight = RandomFloat(15.0,25.0);
							case 1: fWeight = RandomFloat(20.0,30.0);
							case 2: fWeight = RandomFloat(15.0,35.0);
							case 3: fWeight = RandomFloat(15.0,40.0);
							case 4: fWeight = RandomFloat(15.0,25.0);
							case 5: fWeight = RandomFloat(20.0,33.0);
							case 6: fWeight = RandomFloat(15.0,25.0);
							case 7: fWeight = RandomFloat(15.0,34.0);
					 }
				}
				default: fWeight = 0.0;
			}

	        FishWeight[playerid][SlotToUse] = fWeight;
	        format(FishName[playerid][SlotToUse], 12, FishNames[FishNameId]);
	        SendClientMessageEx(playerid, COLOR_SERVER, "FISH: {FFFFFF}Kamu mendapat {FF6347}%s {FFFFFF}dengan berat {FFFF00}%.2f lbs{FFFFFF}, /myfish untuk melihat semua ikan.", FishName[playerid][SlotToUse], FishWeight[playerid][SlotToUse]);
		}
		else if(gacha == 4)
		{
			SendClientMessage(playerid, X11_RED, "* Kamu mendapatkan sampah dari laut!");
		}
	}
	return 1;
}
CMD:sellfish(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1333.7576,1582.0439,3001.0859))
	    return SendErrorMessage(playerid, "You are not inside Fish Factory!");

 	if(FishWeight[playerid][0] == 0 && FishWeight[playerid][1] == 0 && FishWeight[playerid][2] == 0 && FishWeight[playerid][3] == 0 && FishWeight[playerid][4] == 0 && FishWeight[playerid][5] == 0 && FishWeight[playerid][6] == 0 && FishWeight[playerid][7] == 0 && FishWeight[playerid][8] == 0 && FishWeight[playerid][9] == 0)
		return SendErrorMessage(playerid, "You don't have any fish!");
		
	if(PlayerData[playerid][pFishDelay] > 0 && PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "Please wait %d minute to sold your fishes.", PlayerData[playerid][pFishDelay]/60);

	new str[356], Float:count = 0.0;
    for(new i = 0; i < MAX_FISH; i++) if(FishWeight[playerid][i] > 0.0) {
        count += FishWeight[playerid][i];
    }

	if(count > 0.0) {

		new total_price = floatround(count * fishPrice),
			real_price;

		real_price = 30 * total_price;

		SetPVarInt(playerid, "FishPrice", real_price);

		format(str, sizeof(str), ""WHITE"Harga ikan: %.1f/lbs\nTotal berat ikan: "YELLOW"%.2flbs\n"WHITE"Total harga: "GREEN"$%s\n\n"WHITE"INFO: Kamu harus menunggu 20 menit untuk memancing kembali setelah menjual ikan.",
			fishPrice, count, FormatNumber(real_price));

		ShowPlayerDialog(playerid, DIALOG_SELLFISH, DIALOG_STYLE_MSGBOX, "Sell Fish", str, "Confirm", "Cancel");
	}
	return 1;
}

CMD:buybait(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1331.9070,1575.5684,3001.0859))
		return SendErrorMessage(playerid, "You are not inside Fish Factory!");

	new amount;
	if(sscanf(params, "d", amount))
		return SendSyntaxMessage(playerid, "/buybait [amount] | $0.5 per Bait");

	if(amount < 1 || amount > 25)
		return SendErrorMessage(playerid, "Invalid amount specified!");

	if(GetMoney(playerid) < amount * 50)
		return SendErrorMessage(playerid, "You don't have enough money! ($%s)", FormatNumber(amount * 5));
	
	new id = Inventory_Add(playerid, "Bait", 19566, amount);

	if(id == -1)
		return 1;

	SendServerMessage(playerid, "You have successfully purchase %d Bait for {00FF00}$%s", amount, FormatNumber(amount * 50));
	GiveMoney(playerid, -amount * 50);
	return 1;
}

CMD:fish(playerid, params[])
{	    
	if(Inventory_Count(playerid, "Bait") < 1)
	    return SendErrorMessage(playerid, "Kamu tidak memiliki Bait.");

	if(Inventory_Count(playerid, "Fish Rod") < 1)
	    return SendErrorMessage(playerid, "Kamu tidak memiliki Fish Rod.");
	    
	if(PlayerData[playerid][pFishDelay] && PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "Tunggu %d menit untuk bekerja kembali.", PlayerData[playerid][pFishDelay]/60);

	if(PlayerData[playerid][pInjured])
		return SendErrorMessage(playerid, "You are injured at the moment.");

	if(IsPlayerSwimming(playerid))
		return SendErrorMessage(playerid, "Tidak bisa memancing ketika berenang!");
		
	if(PlayerData[playerid][pFishing])
	    return SendErrorMessage(playerid, "Kamu sedang memancing, harap tunggu.");
	    
 	if(FishWeight[playerid][0] != 0 && FishWeight[playerid][1] != 0 && FishWeight[playerid][2] != 0 && FishWeight[playerid][3] != 0 && FishWeight[playerid][4] != 0 && FishWeight[playerid][5] != 0 && FishWeight[playerid][6] != 0 && FishWeight[playerid][7] != 0 && FishWeight[playerid][8] != 0 && FishWeight[playerid][9] != 0)
		return SendErrorMessage(playerid, "Kamu tidak bisa membawa lebih banyak ikan lagi.");

	if(!ReturnFishPlace(playerid))
		return SendErrorMessage(playerid, "Kamu tidak berada di area memancing manapun.");

	if(PlayerData[playerid][pThirst] < 20)
		return SendErrorMessage(playerid, "Kamu terlalu lelah untuk memancing.");

	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
		return SendErrorMessage(playerid, "Kamu harus on-foot untuk memancing.");

	PlayerData[playerid][pFishing] = true;
	SetTimerEx("TimeFishing", 35000, false, "i", playerid);
	SendClientMessage(playerid, COLOR_SERVER, "FISH: {FFFFFF}Kamu mulai memancing, harap tunggu beberapa saat.");
	Inventory_Remove(playerid, "Bait", 1);
	PlayerData[playerid][pThirst] -= RandomEx(1, 3);
 	ApplyAnimation(playerid, "SWORD", "SWORD_BLOCK", 4.1, 0, 0, 0, 1, 0);
	SetPlayerAttachedObject(playerid, 9, 18632, 6, 0.1, 0.05, 0, 0, 180, 180, 0);
	return 1;
}

CMD:myfish(playerid, params[])
{
	new str[512];
	format(str, sizeof(str), "Fish\tWeight\n");
	forex(i, 10)
	{
	    format(str, sizeof(str), "%s%s\t%.2f lbs\n", str, FishName[playerid][i], FishWeight[playerid][i]);
	}
	ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, "Fish List", str, "Close", "");
	return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid) {
	if(areaid == fishSea) {
		SendServerMessage(playerid, "Kamu memasuki area memancing, gunakan "YELLOW"/fish "WHITE"untuk mulai memancing.");
	}
}
