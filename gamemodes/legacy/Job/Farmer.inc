#include <YSI_Coding\y_hooks>

#define                     MAX_PLANT                       1000
#define                     MAX_PLANT_GROW                  25
new FARMER_RATE = 100;

new Float:Field_1[] =
{
	-1429.82, -1524.52,
	-1433.42, -1451.37,
	-1467.88, -1453.18,
	-1466.70, -1472.83,
	-1470.86, -1494.25,
	-1472.03, -1511.06,
	-1471.12, -1525.99,
	-1467.40, -1526.38
};


new
    STREAMER_TAG_AREA:fieldArea;

enum E_PLANT_DATA
{
	plantID,
	plantDelayWater,
	bool:plantNeedWater,
	plantProgress,
	Float:plantPos[3],
	STREAMER_TAG_OBJECT:plantObject,
	bool:plantWatered,
	bool:plantHarvested,
	plantStatus,
    Float:plant_realZ
};
new
    PlantData[MAX_PLANT][E_PLANT_DATA],
    Iterator:Plant<MAX_PLANT>,
    bool:IsPlanting[MAX_PLAYERS],
	bool:IsWatering[MAX_PLAYERS],
	bool:IsHarvesting[MAX_PLAYERS],
	bool:IsDigging[MAX_PLAYERS],
	STREAMER_TAG_AREA:digArea[MAX_PLAYERS],
	Float:g_digArea[MAX_PLAYERS][3];


enum
{
	PLANT_STATUS_GROWING,
	PLANT_STATUS_NEEDWATER,
	PLANT_STATUS_READY
};
enum
{
	PLANT_SPAWN = 1,
	PLANT_GROW
};
Plant_Create(Float:x, Float:y, Float:z)
{
	new pid;
	if((pid = Iter_Free(Plant)) != INVALID_ITERATOR_SLOT)
	{
		Iter_Add(Plant, pid);

		PlantData[pid][plantWatered] = false;
		PlantData[pid][plantProgress] = 0;
		PlantData[pid][plantNeedWater] = true;
		PlantData[pid][plantDelayWater] = 0;
		PlantData[pid][plantPos][0] = x;
		PlantData[pid][plantPos][1] = y;
		PlantData[pid][plantPos][2] = z;
		PlantData[pid][plantHarvested] = false;
		PlantData[pid][plantStatus] = PLANT_STATUS_NEEDWATER;
        PlantData[pid][plant_realZ] = z;
		Plant_Sync(pid, PLANT_SPAWN);
		return pid;
	}
	return INVALID_ITERATOR_SLOT;
}

Plant_Sync(idx, type)
{
	if(!Iter_Contains(Plant, idx))
		return 0;

	switch(type)
	{
		case PLANT_SPAWN:
		{
			if(!IsValidDynamicObject(PlantData[idx][plantObject]))
				PlantData[idx][plantObject] = CreateDynamicObject(19473, PlantData[idx][plantPos][0], PlantData[idx][plantPos][1], PlantData[idx][plantPos][2] - 2.5, 0.0, 0.0, 0.0, -1, -1);

		}
		case PLANT_GROW:
		{
			new Float:z;
			if(IsValidDynamicObject(PlantData[idx][plantObject]) && Streamer_GetIntData(STREAMER_TYPE_OBJECT, PlantData[idx][plantObject], E_STREAMER_MODEL_ID) == 19473)
			{
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT, PlantData[idx][plantObject], E_STREAMER_Z, z);
				
				PlantData[idx][plantPos][2] = z + 0.057;
                Streamer_SetFloatData(STREAMER_TYPE_OBJECT, PlantData[idx][plantObject], E_STREAMER_Z, PlantData[idx][plantPos][2]);
			}
		}
	}
	return 1;
}
bool:IsPlayerInFieldArea(playerid)
{
    if(IsPlayerInDynamicArea(playerid, fieldArea))
		return true;
    return false;
}

Plant_GetNearest(playerid)
{
    new idx = -1;
	foreach(new i : Plant) if(IsPlayerInRangeOfPoint(playerid, 3.5, PlantData[i][plantPos][0], PlantData[i][plantPos][1], PlantData[i][plant_realZ])) {
        idx = i;
        break;
    }
	return idx;
}

Plant_Reset(idx)
{
	PlantData[idx][plantDelayWater] = 0;
	PlantData[idx][plantHarvested] = false;
	PlantData[idx][plantProgress] = 0;
	PlantData[idx][plantWatered] = false;
}
Plant_Destroy(idx)
{
	if(!Iter_Contains(Plant, idx))
		return 0;

	if(IsValidDynamicObject(PlantData[idx][plantObject]))
		DestroyDynamicObject(PlantData[idx][plantObject]);

	Plant_Reset(idx);
	Iter_Remove(Plant, idx);
	return 1;
}

function Plant_Watering(playerid)
{
	new idx = Plant_GetNearest(playerid);

	IsWatering[playerid] = false;
	PlantData[idx][plantDelayWater] = 60;
	PlantData[idx][plantNeedWater] = false;
	PlantData[idx][plantStatus] = PLANT_STATUS_GROWING;
	PlantData[idx][plantWatered] = false;
	ClearAnimations(playerid, 1);
	RemovePlayerAttachedObject(playerid, 8);
	RemovePlayerAttachedObject(playerid, 9);
	return 1;
}

function Plant_Harvest(playerid)
{
	new idx = Plant_GetNearest(playerid);
    ClearAnimations(playerid, 1);
    IsHarvesting[playerid] = false;

	if(!Iter_Contains(Plant, idx))
	{
		SendErrorMessage(playerid, "Tanaman yang akan kamu panen tidak lagi valid.");
		IsHarvesting[playerid] = false;
		return 0;
	}
	Inventory_Add(playerid, "Plant", 2203, 1);
	Plant_Destroy(idx);
	ShowMessage(playerid, "~g~Plant ~w~was added to your inventory (+1)", 2000, 1);
	return 1;
}

function Plant_Plant(playerid)
{
	new idx, Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x,y,z);
    ClearAnimations(playerid, 1);
	idx = Plant_Create(x,y,z);
    IsPlanting[playerid] = false;
    
	if(!IsPlayerInDynamicArea(playerid, digArea[playerid]))
		return SendErrorMessage(playerid, "Kamu tidak berada pada area yang kamu gali.");

	if(idx == INVALID_ITERATOR_SLOT)
		SendErrorMessage(playerid, "Server tidak dapat membuat lebih banyak tanaman.");

	if(IsValidDynamicArea(digArea[playerid]))
		DestroyDynamicArea(digArea[playerid]);

	Inventory_Remove(playerid, "Plant Seed", 1);
	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	return 1;
}

function Plant_CreateArea(playerid)
{
	GetPlayerPos(playerid, g_digArea[playerid][0], g_digArea[playerid][1], g_digArea[playerid][2]);
	ClearAnimations(playerid, 1);
	IsDigging[playerid] = false;
    ResetWeapon(playerid, WEAPON_SHOVEL);
	if(!IsPlayerInFieldArea(playerid))
		return SendErrorMessage(playerid, "Kamu tidak berada pada area ladang petani.");

	if(IsValidDynamicArea(digArea[playerid]))
		DestroyDynamicArea(digArea[playerid]);

	digArea[playerid] = CreateDynamicSphere(g_digArea[playerid][0], g_digArea[playerid][1], g_digArea[playerid][2], 1.7);
	Streamer_Update(playerid, STREAMER_TYPE_AREA);
	SendServerMessage(playerid, "Berhasil menggali! gunakan "YELLOW"/plant "WHITE"untuk mulai bertani.");

	return 1;
}

CMD:plant(playerid, params[])
{

    if(!CheckPlayerJob(playerid, JOB_FARMER))
        return SendErrorMessage(playerid, "Kamu tidak bekerja sebagai farmer!");

    if(!IsPlayerInFieldArea(playerid))
        return SendErrorMessage(playerid, "Kamu tidak berada di ladang farmer.");

    if(IsHungerOrThirst(playerid))
        return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");

    if(Plant_GetNearest(playerid) != -1)
        return SendErrorMessage(playerid, "Tidak dapat menanam terlalu dekat dengan tanaman lain.");

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");

	if(!IsPlayerInDynamicArea(playerid, digArea[playerid]))
		return SendErrorMessage(playerid, "Kamu tidak berada pada area yang kamu gali.");

    if(Inventory_Count(playerid, "Plant Seed") < 1)
        return SendErrorMessage(playerid, "You don't have any plant seeds left.");

    if(IsPlanting[playerid])
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");

    if(IsWatering[playerid])
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");

    if(IsHarvesting[playerid])
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");  
        
    if(IsDigging[playerid])
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");  

    if(Iter_Free(Plant) == INVALID_ITERATOR_SLOT)
        return SendErrorMessage(playerid, "Server tidak dapat membuat lebih banyak tanaman.");

    IsPlanting[playerid] = true;
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Loop", 4.1, 1, 0, 0, 1, 0, 1);
    StartPlayerLoadingBar(playerid, 200, "Planting....", 30, "Plant_Plant");
    return 1;
}

CMD:harvest(playerid, params[])
{
    if(!CheckPlayerJob(playerid, JOB_FARMER))
        return SendErrorMessage(playerid, "Kamu tidak bekerja sebagai farmer!");
        
    if(!IsPlayerInFieldArea(playerid))
        return SendErrorMessage(playerid, "Kamu tidak berada di ladang farmer.");

    if(IsHungerOrThirst(playerid))
        return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");
      
    if(IsPlanting[playerid])
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");

    if(IsWatering[playerid])
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");  

    if(IsHarvesting[playerid])
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");  

    if(IsDigging[playerid])
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");  

    if(Plant_GetNearest(playerid) == -1)
        return SendErrorMessage(playerid, "Kamu tidak berada didekat tanaman manapun.");

    if(PlantData[Plant_GetNearest(playerid)][plantProgress] < MAX_PLANT_GROW)
        return SendErrorMessage(playerid, "Tanaman ini belum siap untuk dipanen!");
        
    if(PlantData[Plant_GetNearest(playerid)][plantHarvested])
        return SendErrorMessage(playerid, "Tanaman ini sedang dipanen!");

    IsHarvesting[playerid] = true;
    PlantData[Plant_GetNearest(playerid)][plantHarvested] = true;
    StartPlayerLoadingBar(playerid, 100, "Harvesting....", 30, "Plant_Harvest");
    SetPlayerFace(playerid, PlantData[Plant_GetNearest(playerid)][plantPos][0],  PlantData[Plant_GetNearest(playerid)][plantPos][1]);
    ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 1, 0, 0, 1, 0, 1);
    SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s begins to harvesting a plant", ReturnName(playerid));
    return 1;
}

CMD:dig(playerid, params[])
{
    if(!CheckPlayerJob(playerid, JOB_FARMER))
        return SendErrorMessage(playerid, "Kamu tidak bekerja sebagai farmer!");
        
    if(!IsPlayerInFieldArea(playerid))
        return SendErrorMessage(playerid, "Kamu tidak berada di ladang farmer.");

    if(IsHungerOrThirst(playerid))
        return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");

    if(Plant_GetNearest(playerid) != -1)
        return SendErrorMessage(playerid, "You cannot plant near another plants.");

    if(IsPlanting[playerid])
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");

    if(IsWatering[playerid])
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");  

    if(IsHarvesting[playerid])
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");  

    if(IsDigging[playerid])
        return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");  

    GiveWeaponToPlayer(playerid, WEAPON_SHOVEL, 1, 1);
    SetPlayerArmedWeapon(playerid, WEAPON_SHOVEL);
    ApplyAnimation(playerid, "CHAINSAW", "WEAPON_csawlo", 4.1, 1, 0, 0, 0, 0, 1);
    StartPlayerLoadingBar(playerid, 250, "Digging....", 30, "Plant_CreateArea");
    IsDigging[playerid] = true;
    return 1;
}

CMD:buyseed(playerid, params[]) {
    if(!CheckPlayerJob(playerid, JOB_FARMER))
        return SendErrorMessage(playerid, "Kamu tidak bekerja sebagai farmer!");   

    if(!IsPlayerInRangeOfPoint(playerid, 3.0, -347.8450,-1045.6550,59.8125))
        return SendErrorMessage(playerid, "Kamu tidak berada pada farmer point!"); 

    new amount;
    if(sscanf(params, "d", amount))
        return SendSyntaxMessage(playerid, "/buyseed [amount] (1 seed = $1.50)");

    if(amount < 1 || amount > 100)
        return SendErrorMessage(playerid, "You have specified invalid amount of seeds.");

    if(GetMoney(playerid) < amount * 150)
        return SendErrorMessage(playerid, "Kamu tidak memiliki uang yang cukup.");

    if(Inventory_Add(playerid, "Plant Seed", 1577, amount) != -1) {
        GiveMoney(playerid, -amount * 150);
        SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Farmer) "WHITE"Kamu telah membeli %d bibit dengan harga "GREEN"$%s", amount, FormatNumber(amount * 150));
    }
    return 1;
}
CMD:sellplant(playerid, params[])
{
    if(!CheckPlayerJob(playerid, JOB_FARMER))
        return SendErrorMessage(playerid, "Kamu tidak bekerja sebagai farmer!");   

    if(!IsPlayerInRangeOfPoint(playerid, 3.0, -347.8450,-1045.6550,59.8125))
        return SendErrorMessage(playerid, "Kamu tidak berada pada farmer point!"); 

    if(isnull(params))   
        return SendSyntaxMessage(playerid, "/sellplant [confirm]");

    if(!strcmp(params, "confirm", true))
    {
        new plant_amount = Inventory_Count(playerid, "Plant"), plant_total_price;
        if(plant_amount < 1)
            return SendErrorMessage(playerid, "Kamu tidak memiliki tanaman untuk dijual.");

        plant_total_price = plant_amount * FARMER_RATE;

        AddSalary(playerid, "Farmer", plant_total_price);
        SendCustomMessage(playerid, X11_LIGHTBLUE, "Farmer", ""WHITE"Kamu menjual %d tanaman dan mendapatkan "GREEN"$%s "WHITE"pada salary.", plant_amount, FormatNumber(plant_total_price));
        Inventory_Remove(playerid, "Plant", -1);
    }
    else
        SendSyntaxMessage(playerid, "/sellplant [confirm]");

    return 1;
}

hook OnGameModeInit()
{
    Iter_Init(Plant);

    fieldArea = CreateDynamicPolygon(Field_1);

	CreateDynamicPickup(1239, 23, -1425.6475,-1529.3163,102.2322, -1);
	LabelData[labelFarmer] = CreateDynamic3DTextLabel(sprintf("[Farmer Store]\n{FFFFFF}/sellplant - to sell plants\nHarga jual: "GREEN"$%s", FormatNumber(FARMER_RATE)), X11_YELLOW, -1425.6475,-1529.3163,102.2322, 10.0);

	CreateDynamicPickup(1239, 23, -2144.2056,-2424.8894,30.6250, -1);
	CreateDynamic3DTextLabel(sprintf("[Farmer Seeds]\n{FFFFFF}/buyseed untuk membeli seeds", FormatNumber(FARMER_RATE)), X11_YELLOW, -2144.2056,-2424.8894,30.6250, 10.0);

	FARMER_RATE = RandomEx(1500, 3000);
	UpdateDynamic3DTextLabelText(LabelData[labelFarmer], X11_YELLOW, sprintf("[Farmer Point]\n{FFFFFF}/sellplant - to sell plants\nHarga jual: "GREEN"$%s", FormatNumber(FARMER_RATE)));
}

task Plant_updateProgress[15000]()
{
    foreach(new i : Plant)
    {
        if(PlantData[i][plantProgress] < MAX_PLANT_GROW) 
        {
            if(!PlantData[i][plantNeedWater])
            {
                PlantData[i][plantProgress]++;
                Plant_Sync(i, PLANT_GROW);
            }
        }
        else
        {
            PlantData[i][plantProgress] = MAX_PLANT_GROW;
            PlantData[i][plantNeedWater] = false;
            PlantData[i][plantDelayWater] = 0;
            PlantData[i][plantStatus] = PLANT_STATUS_READY;
        }
    }
    return 1;
}

task Plant_decreaseDelay[1000]()
{
    foreach(new i : Plant) if(PlantData[i][plantDelayWater] > 0 && PlantData[i][plantProgress] < MAX_PLANT_GROW)
    {
        if(--PlantData[i][plantDelayWater] == 0)
        {
            PlantData[i][plantDelayWater] = 0;
            PlantData[i][plantNeedWater] = true;
            PlantData[i][plantStatus] = PLANT_STATUS_NEEDWATER;
        }
    }
    return 1;
}

hook OnPlayerDisconnectEx(playerid) {
    if(IsValidDynamicArea(digArea[playerid])) {
        DestroyDynamicArea(digArea[playerid]);
    }

    IsHarvesting[playerid] = false;
    IsWatering[playerid] = false;
    IsPlanting[playerid] = false;
}
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_CTRL_BACK))
    {
        new idx = Plant_GetNearest(playerid);
        if(idx != -1 && CheckPlayerJob(playerid, JOB_FARMER))
        {
            if(!PlantData[idx][plantNeedWater])
                return SendErrorMessage(playerid, "Tanaman ini belum membutuhkan air.");

            if(PlantData[idx][plantWatered])
                return SendErrorMessage(playerid, "Tanaman ini sedang disiram.");

            if(IsWatering[playerid])
                return SendErrorMessage(playerid, "Kamu sedang menyiram tanaman.");

            if(IsDigging[playerid])
                return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");  

            if(IsHarvesting[playerid])
                return SendErrorMessage(playerid, "Tidak dapat melakukan ini sekarang.");  

            IsWatering[playerid] = true;
            PlantData[idx][plantWatered] = true;
            ApplyAnimation(playerid, "PED", "GUN_STAND", 4.1, 1, 1, 1, 1, 0, 1);
            SetPlayerAttachedObject(playerid, 8, 1650, 6, 0.13800, 0.01400, -0.00500, -27.2000, 0.00000, 0.00000);
            SetPlayerAttachedObject(playerid, 9, 18676, 6, -1.12999, 0.01600, -0.86800, 0.00000, 53.19995, 0.00000, 1.00000, 1.00000, 1.00000);
            StartPlayerLoadingBar(playerid, 150, "Watering....", 30, "Plant_Watering");
            SetPlayerFace(playerid, PlantData[idx][plantPos][0], PlantData[idx][plantPos][1]);
            SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s takes can of water and starts to watering the plant", ReturnName(playerid));
        }
    }
    return 1;
}

ptask OnFarmerPlayerUpdate[1000](playerid) {
    if(IsPlayerSpawned(playerid) && CheckPlayerJob(playerid, JOB_FARMER)) {
        if(IsWatering[playerid] && GetPlayerAnimationIndex(playerid) != 1167) {
            ApplyAnimation(playerid, "PED", "GUN_STAND", 4.1, 1, 1, 1, 1, 0, 1);
        }
        if(IsPlanting[playerid] && GetPlayerAnimationIndex(playerid) != 168) {
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Loop", 4.1, 1, 0, 0, 1, 0, 1);
        }
        if(IsHarvesting[playerid] && GetPlayerAnimationIndex(playerid) != 368) {
            ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 1, 0, 0, 1, 0, 1);
        }

        new idx = -1;

        if((idx = Plant_GetNearest(playerid)) != -1) {
            switch(PlantData[idx][plantStatus])
            {
                case PLANT_STATUS_GROWING:
                {
                    ShowMessage(playerid, sprintf("Status: ~y~Growing~n~~w~%d detik_hingga_membutuhkan_air.", PlantData[idx][plantDelayWater]), 1, 0);
                }
                case PLANT_STATUS_NEEDWATER: 
                {
                    ShowMessage(playerid, "Status: ~r~Membutuhkan_air~n~~w~Press ~b~H ~w~untuk_mulai_menyiram.", 1, 0);
                }
                case PLANT_STATUS_READY:
                {
                    ShowMessage(playerid, "Status: ~g~Ready harvest~n~~w~Type ~b~/harvest ~w~untuk_panen.", 1, 0);
                }
            }
        }
    }
    return 1;
}