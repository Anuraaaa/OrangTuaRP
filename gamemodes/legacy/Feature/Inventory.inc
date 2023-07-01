#include <YSI_Coding\y_hooks>

enum inventoryData
{
	invExists,
	invID,
	invItem[32 char],
	invModel,
	invQuantity
};

new InventoryData[MAX_PLAYERS][MAX_INVENTORY][inventoryData],
	g_ListedInventory[MAX_PLAYERS][MAX_INVENTORY];

	
enum e_InventoryItems
{
	e_InventoryItem[32],
	e_InventoryModel,
	e_InventoryMax,
};


new const g_aInventoryItems[][e_InventoryItems] =
{
	{"Nitrous Oxide", 1010, 10},
	{"Spraycan", 365, 10},
	{"GPS", 18875, 1},
	{"Cellphone", 18867, 1},
	{"Medkit", 1580, 15},
	{"Bandage", 1580, 5},
	{"Portable Radio", 19942, 1},
	{"Boombox", 2103, 1},
	{"Mask", 19036, 1},
	{"Snack", 2768, 5},
	{"Water", 2958, 5},
	{"Rolling Paper", 19873, 100},
	{"Rolled Weed", 3027, 100},
	{"Weed", 1578, 100},
	{"Component", 19627, 5000},
	{"Weed Seed", 1279, 100},
	{"9mm Luger", 19995, 20},
	{"12 Gauge", 19995, 20},
	{".44 Magnum", 19995, 20},
	{"7.62mm Caliber", 19995, 20},
	{"9mm Silenced HV Schematic", 3111, 1},
	{"Shotgun HV Schematic", 3111, 1},
	{"Desert Eagle HV Schematic", 3111, 1},
	{"Rifle HV Schematic", 3111, 1},
	{"AK-47 HV Schematic", 3111, 1},
	{"9mm Silenced Schematic", 3111, 1},
	{"Shotgun Schematic", 3111, 1},
	{"Desert Eagle Schematic", 3111, 1},
	{"Rifle Schematic", 3111, 1},
	{"AK-47 Schematic", 3111, 1},
	{"Desert Eagle Material", 3052, 20},
	{"9mm Silenced Material", 3052, 20},
	{"Shotgun Material", 3052, 20},
	{"Rifle Material", 3052, 20},
	{"AK-47 Material", 3052, 20},
	{"Axe", 19631, 1},
	{"Fish Rod", 18632, 1},
	{"Bait", 19566, 25},
	{"Fuel Can", 1650, 3},
	{"Acetaminophen", 2709, 10},
	{"Promethazine", 2709, 10},
	{"Cigarettes", 19896, 20}
};

hook OnPlayerRedeemVIP(playerid) {

	Inventory_Add(playerid, "Boombox", 2103, 1);
}

hook OnPlayerExpireVIP(playerid) {

	Inventory_Remove(playerid, "Boombox", -1);
}
stock Inventory_Clear(playerid)
{
	static
	    string[64];

	forex(i, MAX_INVENTORY)
	{
	    if (InventoryData[playerid][i][invExists])
	    {
	        InventoryData[playerid][i][invExists] = 0;
	        InventoryData[playerid][i][invModel] = 0;
	        InventoryData[playerid][i][invQuantity] = 0;
		}
	}
	mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `inventory` WHERE `ID` = '%d'", PlayerData[playerid][pID]);
	return mysql_tquery(sqlcon, string);
}

stock Inventory_GetItemID(playerid, item[])
{

	if(playerid == INVALID_PLAYER_ID)
		return 0;

	forex(i, MAX_INVENTORY)
	{
	    if (!InventoryData[playerid][i][invExists])
	        continue;

		if (!strcmp(InventoryData[playerid][i][invItem], item)) return i;
	}
	return -1;
}

stock Inventory_GetFreeID(playerid)
{
	if (Inventory_Items(playerid) >= 20)
		return -1;

	forex(i, MAX_INVENTORY)
	{
	    if (!InventoryData[playerid][i][invExists])
	        return i;
	}
	return -1;
}

stock Inventory_Items(playerid)
{
    new count;

    forex(i, MAX_INVENTORY) if (InventoryData[playerid][i][invExists]) {
        count++;
	}
	return count;
}

stock Inventory_Count(playerid, item[])
{
	new itemid = Inventory_GetItemID(playerid, item);

	if (itemid != -1)
	    return InventoryData[playerid][itemid][invQuantity];

	return 0;
}

stock PlayerHasItem(playerid, item[])
{
	return (Inventory_GetItemID(playerid, item) != -1);
}

stock Inventory_Set(playerid, item[], model, amount)
{
	new itemid = Inventory_GetItemID(playerid, item);

	if (itemid == -1 && amount > 0)
		Inventory_Add(playerid, item, model, amount);

	else if (amount > 0 && itemid != -1)
	    Inventory_SetQuantity(playerid, item, amount);

	else if (amount < 1 && itemid != -1)
	    Inventory_Remove(playerid, item, -1);

	return 1;
}

stock Inventory_SetQuantity(playerid, item[], quantity)
{
	new
	    itemid = Inventory_GetItemID(playerid, item),
	    string[128];

	if (itemid != -1)
	{
	    format(string, sizeof(string), "UPDATE `inventory` SET `invQuantity` = %d WHERE `ID` = '%d' AND `invID` = '%d'", quantity, PlayerData[playerid][pID], InventoryData[playerid][itemid][invID]);
	    mysql_tquery(sqlcon, string);

	    InventoryData[playerid][itemid][invQuantity] = quantity;
	}
	return 1;
}

stock Inventory_Remove(playerid, item[], quantity = 1)
{
	new
		itemid = Inventory_GetItemID(playerid, item),
		string[128];

	if (itemid != -1)
	{
	    if (InventoryData[playerid][itemid][invQuantity] > 0)
	    {
	        InventoryData[playerid][itemid][invQuantity] -= quantity;
		}
		if (quantity == -1 || InventoryData[playerid][itemid][invQuantity] < 1)
		{
		    InventoryData[playerid][itemid][invExists] = false;
		    InventoryData[playerid][itemid][invModel] = 0;
		    InventoryData[playerid][itemid][invQuantity] = 0;
		    strpack(InventoryData[playerid][itemid][invItem], "", 32 char);

		    mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `inventory` WHERE `ID` = '%d' AND `invID` = '%d'", PlayerData[playerid][pID], InventoryData[playerid][itemid][invID]);
	        mysql_tquery(sqlcon, string);

			/*forex(i, MAX_INVENTORY)
			{
			    InventoryData[playerid][i][invExists] = false;
			    InventoryData[playerid][i][invModel] = 0;
			    InventoryData[playerid][i][invQuantity] = 0;
			}
			new invQuery[256];

		    mysql_format(sqlcon,invQuery, sizeof(invQuery), "SELECT * FROM `inventory` WHERE `ID` = '%d'", PlayerData[playerid][pID]);
			mysql_tquery(sqlcon, invQuery, "LoadPlayerItems", "d", playerid);*/
		}
		else if (quantity != -1 && InventoryData[playerid][itemid][invQuantity] > 0)
		{
			mysql_format(sqlcon, string, sizeof(string), "UPDATE `inventory` SET `invQuantity` = `invQuantity` - %d WHERE `ID` = '%d' AND `invID` = '%d'", quantity, PlayerData[playerid][pID], InventoryData[playerid][itemid][invID]);
            mysql_tquery(sqlcon, string);
		}
		return 1;
	}
	return 0;
}

stock Inventory_Add(playerid, item[], model, quantity = 1)
{
	new
		itemid = Inventory_GetItemID(playerid, item),
		string[128];

    for (new i = 0; i < sizeof(g_aInventoryItems); i ++) if(!strcmp(g_aInventoryItems[i][e_InventoryItem], item, true))
    {
        if((Inventory_Count(playerid, g_aInventoryItems[i][e_InventoryItem]) + quantity) > g_aInventoryItems[i][e_InventoryMax])
        {
            SendErrorMessage(playerid, "Kamu tidak bisa memiliki lebih banyak dari %d untuk item ini.", g_aInventoryItems[i][e_InventoryMax], item);
            return -1;
        }
    }
	if (itemid == -1)
	{
	    itemid = Inventory_GetFreeID(playerid);

	    if (itemid != -1)
	    {
	        InventoryData[playerid][itemid][invExists] = true;
	        InventoryData[playerid][itemid][invModel] = model;
	        InventoryData[playerid][itemid][invQuantity] = quantity;

	        strpack(InventoryData[playerid][itemid][invItem], item, 32 char);

			format(string, sizeof(string), "INSERT INTO `inventory` (`ID`, `invItem`, `invModel`, `invQuantity`) VALUES('%d', '%s', '%d', '%d')", PlayerData[playerid][pID], item, model, quantity);
			mysql_tquery(sqlcon, string, "OnInventoryAdd", "dd", playerid, itemid);
	        return itemid;
		}
		SendErrorMessage(playerid, "Kamu tidak bisa membawa lebih banyak item lagi!");
		return -1;
	}
	else
	{
	    format(string, sizeof(string), "UPDATE `inventory` SET `invQuantity` = `invQuantity` + %d WHERE `ID` = '%d' AND `invID` = '%d'", quantity, PlayerData[playerid][pID], InventoryData[playerid][itemid][invID]);
	    mysql_tquery(sqlcon, string);

	    InventoryData[playerid][itemid][invQuantity] += quantity;
	}
	return itemid;
}

function OnInventoryAdd(playerid, itemid)
{
	InventoryData[playerid][itemid][invID] = cache_insert_id();
	return 1;
}

function ShowInventory(playerid, targetid)
{
    if (!IsPlayerConnected(playerid))
	    return 0;

	new
	    items[MAX_INVENTORY],
		amounts[MAX_INVENTORY],
		str[812],
		string[352],
		count = 0;

	format(str, sizeof(str), "Name\tAmount\n");
	format(str, sizeof(str), "%s\nMoney\t$%s", str, FormatNumber(GetMoney(targetid)));
    for(new i = 0; i < MAX_INVENTORY; i++)
	{
 		if (InventoryData[targetid][i][invExists])
        {
            count++;
   			items[i] = InventoryData[targetid][i][invModel];
   			amounts[i] = InventoryData[targetid][i][invQuantity];
   			strunpack(string, InventoryData[targetid][i][invItem]);
   			format(str, sizeof(str), "%s\n%s\t%d", str, string, amounts[i]);
		}
	}
	for(new i = 0; i < 13; i ++)
    {
        if(PlayerData[targetid][pGuns][i] > 0)
			format(str, sizeof(str), "%s\n"RED"%s "WHITE"(Ammo: %d)", str, ReturnWeaponName(PlayerData[targetid][pGuns][i]), PlayerData[targetid][pAmmo][i]);
    }
	ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, sprintf("%s Inventory", ReturnName(targetid)), str,  "Close", "");
	return 1;

}

stock OpenInventory(playerid)
{
    if (!IsPlayerConnected(playerid))
	    return 0;

	new
		amounts[MAX_INVENTORY],
		str[512],
		string[256],
		count = 0;

	format(str, sizeof(str), "Item Name\tItem Amount\n");
    for(new i = 0; i < MAX_INVENTORY; i++)
	{
	    if (InventoryData[playerid][i][invExists])
		{
			amounts[i] = InventoryData[playerid][i][invQuantity];
			strunpack(string, InventoryData[playerid][i][invItem]);
			format(str, sizeof(str), "%s{FFFFFF}%s\t%d\n", str, string, amounts[i]);
			g_ListedInventory[playerid][count++] = i;
		}
	}
	if(count)
		ShowPlayerDialog(playerid, DIALOG_INVENTORY, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Items Data (%d/%d)", Inventory_Items(playerid), MAX_INVENTORY), str, "Select", "Close");
	else
		SendErrorMessage(playerid, "Kamu tidak memiliki item satupun.");

	return 1;
}

function LoadPlayerItems(playerid)
{
	new name[128];
	new count = cache_num_rows();
	if(count > 0)
	{
	    forex(i, count)
	    {
	        InventoryData[playerid][i][invExists] = true;

	        cache_get_value_name_int(i, "invID", InventoryData[playerid][i][invID]);
	        cache_get_value_name_int(i, "invModel", InventoryData[playerid][i][invModel]);
	        cache_get_value_name_int(i, "invQuantity", InventoryData[playerid][i][invQuantity]);

	        cache_get_value_name(i, "invItem", name);

			strpack(InventoryData[playerid][i][invItem], name, 32 char);
		}
	}
	return 1;
}

function OnPlayerUseItem(playerid, itemid, name[])
{
	if(!strcmp(name, "Snack"))
	{
		if(PlayerData[playerid][pInjured])
			return SendErrorMessage(playerid, "Karakter-mu sedang injured!");

        if (PlayerData[playerid][pHunger] > 90)
            return SendErrorMessage(playerid, "Kamu tidak membutuhkan makanan saat ini.");

        PlayerData[playerid][pHunger] += 10;
		Inventory_Remove(playerid, "Snack", 1);
		ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s takes a snack and eats it.", ReturnName(playerid));
	}
	else if(!strcmp(name, "Cigarettes")) {

		if(PlayerData[playerid][pCough] >= 10)
			return SendErrorMessage(playerid, "Karaktermu sedang batuk level extreme!");

		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY)
			return SendErrorMessage(playerid, "Kamu sedang merokok!");

		if(PlayerData[playerid][pInjured])
			return SendErrorMessage(playerid, "Tidak dapat melakukan ini ketika injured.");

		if(PlayerData[playerid][pCuffed])
			return SendErrorMessage(playerid, "Tidak dapat melakukan ini ketika diborgol.");

		Inventory_Remove(playerid, "Cigarettes", 1);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);

		SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s takes out a Cigarette and lights it...", ReturnName(playerid));

		if(PlayerData[playerid][pCough] < 10)
			PlayerData[playerid][pCough]++;

		SendClientMessage(playerid, -1, "INFO: Gunakan "YELLOW"ENTER "WHITE"untuk membuang rokok.");
	}
	else if(!strcmp(name, "Acetaminophen")) {

		if(PlayerData[playerid][pUsePill])
			return SendErrorMessage(playerid, "Tunggu %d detik untuk menggunakan obat.", PlayerData[playerid][pUsePill]);

		if(!PlayerData[playerid][pFever])
			return SendErrorMessage(playerid, "Kamu tidak dapat mengkonsumsi pil ini.");

		PlayerData[playerid][pFever]--;
		Inventory_Remove(playerid, "Acetaminophen", 1);
		PlayerData[playerid][pUsePill] = 60;
		cmd_me(playerid, sprintf("take's out %s and eat it.", name));
		SetPlayerDrunkLevelEx(playerid, 0);
	}
	else if(!strcmp(name, "Promethazine")) {

		if(PlayerData[playerid][pUsePill])
			return SendErrorMessage(playerid, "Tunggu %d detik untuk menggunakan obat.", PlayerData[playerid][pUsePill]);

		if(!PlayerData[playerid][pCough])
			return SendErrorMessage(playerid, "Kamu tidak dapat mengkonsumsi pil ini.");

		PlayerData[playerid][pCough]--;
		Inventory_Remove(playerid, "Promethazine", 1);
		PlayerData[playerid][pUsePill] = 60;
		cmd_me(playerid, sprintf("take's out %s and eat it.", name));  
		SetPlayerDrunkLevelEx(playerid, 0);
	}
	else if(!strcmp(name, "Fuel Can")) {

		new vehicleid = INVALID_VEHICLE_ID;

		vehicleid = GetNearestVehicle(playerid, 5.0);

		if(IsPlayerInAnyVehicle(playerid))
			return SendErrorMessage(playerid, "Turun dari kendaraan terlebih dahulu.");

		if(vehicleid == INVALID_VEHICLE_ID)
			return SendErrorMessage(playerid, "Tidak ada kendaraan didekatmu.");

		if(!IsEngineVehicle(vehicleid))
			return SendErrorMessage(playerid, "Kendaraan ini tidak memiliki mesin.");


		if(Vehicle_GetFuel(vehicleid) >= 100)
			return SendErrorMessage(playerid, "Kendaraan ini tidak memerlukan bahan bakar lagi.");

		if(VehicleData[vehicleid][vFuel] + 15 >= 100)
			VehicleData[vehicleid][vFuel] = 100;
		else
			VehicleData[vehicleid][vFuel] += 15;

		SendServerMessage(playerid, "Kamu berhasil mengisi bensin kendaraan %s.", GetVehicleName(vehicleid));

		Inventory_Remove(playerid, "Fuel Can", 1);
	}
	else if(!strcmp(name, "Rolled Weed")) {


		if(PlayerData[playerid][pInjured])
			return SendErrorMessage(playerid, "Karakter-mu sedang injured!");

		if(PlayerData[playerid][pCough] >= 10)//s
			return SendErrorMessage(playerid, "Karaktermu sedang batuk level extreme!");

		new Float:armour;

		GetPlayerArmour(playerid, armour);

		if(PlayerData[playerid][pLevel] < 3)
			return SendErrorMessage(playerid, "Minimal level 3 untuk melakukan ini!");
			
		if(armour >= 100.0)
			return SendErrorMessage(playerid, "Kamu sudah memiliki armour yang penuh.");


		if(PlayerData[playerid][pDrugCondition])
			return SendErrorMessage(playerid, "Kamu masih dalam pengaruh efek drug.");


		PlayerData[playerid][pDrugCondition] = true;
		PlayerData[playerid][pDrugTime] = 15;

		ApplyAnimation(playerid, "SMOKING", "M_smk_in", 4.1, 0, 0, 0, 0, 0, 1);
		SendNearbyMessage(playerid, 10.0, X11_PLUM, "** %s takes a Rolled Weed and snorts it.", ReturnName(playerid));

		if(armour+10.0 >= 100.0)
			SetPlayerArmour(playerid, 100.0);
		else
			SetPlayerArmour(playerid, armour+10.0);

		Inventory_Remove(playerid, "Rolled Weed", 1);
		SetPlayerDrunkLevelEx(playerid, 50000, 15000);

		if(PlayerData[playerid][pCough] < 10) {

			new chance_cough = random(5);

			if(chance_cough == 1)
				PlayerData[playerid][pCough]++;
		}
	}
	else if(!strcmp(name, "Water"))
	{
        if (PlayerData[playerid][pThirst] > 90)
            return SendErrorMessage(playerid, "Kamu tidak membutuhkan minum saat ini.");

        PlayerData[playerid][pThirst] += 10;
		Inventory_Remove(playerid, "Water", 1);
		ApplyAnimation(playerid, "VENDING", "VEND_DRINK2_P", 4.1, 0, 0, 0, 0, 0, 1);
        SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s takes a water mineral and drinks it.", ReturnName(playerid));
	}
	else if(!strcmp(name, "Cellphone"))
	{
		cmd_phone(playerid, "");
	}
	else if(!strcmp(name, "GPS"))
	{
		cmd_gps(playerid, "");
	}
	else if(!strcmp(name, "Boombox"))
	{
		cmd_boombox(playerid, "");
	}
	else if(!strcmp(name, "Axe"))
	{
		if(GetEquipedItem(playerid) == EQUIP_ITEM_AXE) {
			EquipItem(playerid, EQUIP_ITEM_NONE);
		}
		else {
			EquipItem(playerid, EQUIP_ITEM_AXE);
		}
	}
	else if(!strcmp(name, "Fish Rod"))
	{
		if(GetEquipedItem(playerid) == EQUIP_ITEM_ROD) {
			EquipItem(playerid, EQUIP_ITEM_NONE);
		}
		else {
			EquipItem(playerid, EQUIP_ITEM_ROD);
		}
	}
	else if(!strcmp(name, "Rifle Schematic"))
	{
		if(Inventory_Count(playerid, "Rifle Material") < 1)
			return SendErrorMessage(playerid, "Kamu tidak memiliki Rifle Material!");

		if(PlayerHasWeapon(playerid, 33))
			return SendErrorMessage(playerid, "Kamu masih membawa Rifle!");

		if(PlayerHasWeapon(playerid, 34))
			return SendErrorMessage(playerid, "Kamu masih membawa senjata dengan jenis yang sama! (Sniper)");

		if(PlayerData[playerid][pLevel] < 3)
			return SendErrorMessage(playerid, "Tidak bisa membuat senjata ketika dibawah level 3!");

		if(GetFactionType(playerid) != FACTION_FAMILY) 
			return SendErrorMessage(playerid, "Hanya Official Family yang dapat merakit Rifle!");

		Inventory_Remove(playerid, "Rifle Material", 1);
		GiveWeaponToPlayer(playerid, 33, 10, 500);
		SendClientMessage(playerid, X11_LIGHTBLUE, "(Crafting) "WHITE"Kamu berhasil merakit {FF0000}Rifle");
	}
	else if(!strcmp(name, "Desert Eagle Schematic"))
	{
		if(Inventory_Count(playerid, "Desert Eagle Material") < 1)
			return SendErrorMessage(playerid, "Kamu tidak memiliki Desert Eagle Material!");

		if(PlayerHasWeapon(playerid, 24))
			return SendErrorMessage(playerid, "Kamu masih membawa Desert Eagle!");

		if(PlayerHasWeapon(playerid, 23))
			return SendErrorMessage(playerid, "Kamu masih membawa senjata dengan jenis yang sama! (Pistol)");

		if(PlayerHasWeapon(playerid, 22))
			return SendErrorMessage(playerid, "Kamu masih membawa senjata dengan jenis yang sama! (Pistol)");

		if(PlayerData[playerid][pLevel] < 3)
			return SendErrorMessage(playerid, "Tidak bisa membuat senjata ketika dibawah level 3!");

		if(GetFactionType(playerid) != FACTION_FAMILY) 
			return SendErrorMessage(playerid, "Hanya Official Family yang dapat merakit Desert Eagle!");

		Inventory_Remove(playerid, "Desert Eagle Material", 1);
		GiveWeaponToPlayer(playerid, 24, 21, 500);
		SendClientMessage(playerid, X11_LIGHTBLUE, "(Crafting) "WHITE"Kamu berhasil merakit {FF0000}Desert Eagle");
	}
	else if(!strcmp(name, "9mm Silenced Schematic"))
	{
		if(Inventory_Count(playerid, "9mm Silenced Material") < 1)
			return SendErrorMessage(playerid, "Kamu tidak memiliki 9mm Silenced Material!");

		if(PlayerHasWeapon(playerid, 23))
			return SendErrorMessage(playerid, "Kamu masih membawa 9mm Silenced!");

		if(PlayerHasWeapon(playerid, 24))
			return SendErrorMessage(playerid, "Kamu masih membawa senjata dengan jenis yang sama! (Pistol)");

		if(PlayerHasWeapon(playerid, 22))
			return SendErrorMessage(playerid, "Kamu masih membawa senjata dengan jenis yang sama! (Pistol)");

		if(PlayerData[playerid][pLevel] < 3)
			return SendErrorMessage(playerid, "Tidak bisa membuat senjata ketika dibawah level 3!");

		Inventory_Remove(playerid, "9mm Silenced Material", 1);
		GiveWeaponToPlayer(playerid, 23, 34, 500);
		SendClientMessage(playerid, X11_LIGHTBLUE, "(Crafting) "WHITE"Kamu berhasil merakit {FF0000}9mm Silenced");
	}
	else if(!strcmp(name, "Shotgun Schematic"))
	{
		if(Inventory_Count(playerid, "Shotgun Material") < 1)
			return SendErrorMessage(playerid, "Kamu tidak memiliki Shotgun Material!");

		if(PlayerHasWeapon(playerid, 25))
			return SendErrorMessage(playerid, "Kamu masih membawa Shotgun!");

		if(PlayerData[playerid][pLevel] < 3)
			return SendErrorMessage(playerid, "Tidak bisa membuat senjata ketika dibawah level 3!");
			
		Inventory_Remove(playerid, "Shotgun Material", 1);
		GiveWeaponToPlayer(playerid, 25, 12, 500);
		SendClientMessage(playerid, X11_LIGHTBLUE, "(Crafting) "WHITE"Kamu berhasil merakit {FF0000}Shotgun");
	}
	else if(!strcmp(name, "AK-47 Schematic")) {
		if(Inventory_Count(playerid, "AK-47 Material") < 1)
			return SendErrorMessage(playerid, "Kamu tidak memiliki AK-47 Material!");

		if(PlayerHasWeapon(playerid, 30))
			return SendErrorMessage(playerid, "Kamu masih membawa AK-47!");

		if(PlayerHasWeapon(playerid, 31))
			return SendErrorMessage(playerid, "Kamu masih membawa senjata dengan jenis yang sama! (M4)");

		if(PlayerData[playerid][pLevel] < 3)
			return SendErrorMessage(playerid, "Tidak bisa membuat senjata ketika dibawah level 3!");

		Inventory_Remove(playerid, "AK-47 Material", 1);
		GiveWeaponToPlayer(playerid, 30, 30, 500);
		SendClientMessage(playerid, X11_LIGHTBLUE, "(Crafting) "WHITE"Kamu berhasil merakit {FF0000}AK-47");	
	}
	else if(!strcmp(name, "Rifle HV Schematic")) //HV
	{
		if(Inventory_Count(playerid, "Rifle Material") < 1)
			return SendErrorMessage(playerid, "Kamu tidak memiliki Rifle Material!");

		if(PlayerHasWeapon(playerid, 33))
			return SendErrorMessage(playerid, "Kamu masih membawa Rifle!");

		if(PlayerHasWeapon(playerid, 34))
			return SendErrorMessage(playerid, "Kamu masih membawa senjata dengan jenis yang sama! (Sniper)");

		if(PlayerData[playerid][pLevel] < 3)
			return SendErrorMessage(playerid, "Tidak bisa membuat senjata ketika dibawah level 3!");

		if(GetFactionType(playerid) != FACTION_FAMILY) 
			return SendErrorMessage(playerid, "Hanya Official Family yang dapat merakit Rifle!");

		Inventory_Remove(playerid, "Rifle Material", 1);
		GiveWeaponToPlayer(playerid, 33, 10, 500, 1);
		SendClientMessage(playerid, X11_LIGHTBLUE, "(Crafting) "WHITE"Kamu berhasil merakit {FF0000}Rifle (High Velocity)");
	}
	else if(!strcmp(name, "Desert Eagle HV Schematic"))
	{
		if(Inventory_Count(playerid, "Desert Eagle Material") < 1)
			return SendErrorMessage(playerid, "Kamu tidak memiliki Desert Eagle Material!");

		if(PlayerHasWeapon(playerid, 24))
			return SendErrorMessage(playerid, "Kamu masih membawa Desert Eagle!");

		if(PlayerHasWeapon(playerid, 23))
			return SendErrorMessage(playerid, "Kamu masih membawa senjata dengan jenis yang sama! (Pistol)");

		if(PlayerHasWeapon(playerid, 22))
			return SendErrorMessage(playerid, "Kamu masih membawa senjata dengan jenis yang sama! (Pistol)");

		if(PlayerData[playerid][pLevel] < 3)
			return SendErrorMessage(playerid, "Tidak bisa membuat senjata ketika dibawah level 3!");

		if(GetFactionType(playerid) != FACTION_FAMILY) 
			return SendErrorMessage(playerid, "Hanya Official Family yang dapat merakit Desert Eagle!");

		Inventory_Remove(playerid, "Desert Eagle Material", 1);
		GiveWeaponToPlayer(playerid, 24, 21, 500, 1);
		SendClientMessage(playerid, X11_LIGHTBLUE, "(Crafting) "WHITE"Kamu berhasil merakit {FF0000}Desert Eagle (High Velocity)");
	}
	else if(!strcmp(name, "AK-47 HV Schematic")) {
		if(Inventory_Count(playerid, "AK-47 Material") < 1)
			return SendErrorMessage(playerid, "Kamu tidak memiliki AK-47 Material!");

		if(PlayerHasWeapon(playerid, 30))
			return SendErrorMessage(playerid, "Kamu masih membawa AK-47!");

		if(PlayerHasWeapon(playerid, 31))
			return SendErrorMessage(playerid, "Kamu masih membawa senjata dengan jenis yang sama! (M4)");

		if(PlayerData[playerid][pLevel] < 3)
			return SendErrorMessage(playerid, "Tidak bisa membuat senjata ketika dibawah level 3!");

		Inventory_Remove(playerid, "AK-47 Material", 1);
		GiveWeaponToPlayer(playerid, 30, 30, 500, 1);
		SendClientMessage(playerid, X11_LIGHTBLUE, "(Crafting) "WHITE"Kamu berhasil merakit {FF0000}AK-47 (High Velocity)");	
	}
	else if(!strcmp(name, "9mm Silenced HV Schematic"))
	{
		if(Inventory_Count(playerid, "9mm Silenced Material") < 1)
			return SendErrorMessage(playerid, "Kamu tidak memiliki 9mm Silenced Material!");

		if(PlayerHasWeapon(playerid, 23))
			return SendErrorMessage(playerid, "Kamu masih membawa 9mm Silenced!");

		if(PlayerHasWeapon(playerid, 24))
			return SendErrorMessage(playerid, "Kamu masih membawa senjata dengan jenis yang sama! (Pistol)");

		if(PlayerHasWeapon(playerid, 22))
			return SendErrorMessage(playerid, "Kamu masih membawa senjata dengan jenis yang sama! (Pistol)");

		if(PlayerData[playerid][pLevel] < 3)
			return SendErrorMessage(playerid, "Tidak bisa membuat senjata ketika dibawah level 3!");

		Inventory_Remove(playerid, "9mm Silenced Material", 1);
		GiveWeaponToPlayer(playerid, 23, 34, 500, 1);
		SendClientMessage(playerid, X11_LIGHTBLUE, "(Crafting) "WHITE"Kamu berhasil merakit {FF0000}9mm Silenced (High Velocity)");
	}
	else if(!strcmp(name, "Shotgun HV Schematic"))
	{
		if(Inventory_Count(playerid, "Shotgun Material") < 1)
			return SendErrorMessage(playerid, "Kamu tidak memiliki Shotgun Material!");

		if(PlayerHasWeapon(playerid, 25))
			return SendErrorMessage(playerid, "Kamu masih membawa Shotgun!");

		if(PlayerData[playerid][pLevel] < 3)
			return SendErrorMessage(playerid, "Tidak bisa membuat senjata ketika dibawah level 3!");
			
		Inventory_Remove(playerid, "Shotgun Material", 1);
		GiveWeaponToPlayer(playerid, 25, 12, 500, 1);
		SendClientMessage(playerid, X11_LIGHTBLUE, "(Crafting) "WHITE"Kamu berhasil merakit {FF0000}Shotgun (High Velocity)");
	}
	else if(!strcmp(name, "7.62mm Caliber"))
	{
		new wep = GetWeapon(playerid);
		if(wep == 33) {

			if(PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] >= 50)
				return SendErrorMessage(playerid, "Total peluru tidak bisa lebih dari 50!");

			PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] += 5;
			PlayReloadAnimation(playerid, 33);
			PlayerPlayNearbySound(playerid, 36401);
			Inventory_Remove(playerid, "7.62mm Caliber", 1);

			if(PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] > 50) {
				PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] = 50;
			}
		}
		else if(wep == 30) {
			if(PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] >= 300)
				return SendErrorMessage(playerid, "Total peluru tidak bisa lebih dari 300!");

			PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] += 30;
			PlayReloadAnimation(playerid, 30);
			PlayerPlayNearbySound(playerid, 36401);
			Inventory_Remove(playerid, "7.62mm Caliber", 1);

			if(PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] > 300) {
				PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] = 300;
			}	
		}
		else SendErrorMessage(playerid, "Kamu harus membawa AK-47/Rifle.");
	}
	else if(!strcmp(name, ".44 Magnum"))
	{
		new wep = GetWeapon(playerid);
		if(wep != 24)
			return SendErrorMessage(playerid, "You must holding Desert Eagle!");

		if(PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] >= 70)
			return SendErrorMessage(playerid, "Total peluru tidak bisa lebih dari 70!");

		PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] += 7;
		PlayReloadAnimation(playerid, 24);
		PlayerPlayNearbySound(playerid, 36401);
		Inventory_Remove(playerid, ".44 Magnum", 1);

		if(PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] > 70) {
			PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] = 70;
		}
	}
	else if(!strcmp(name, "9mm Luger"))
	{
		new wep = GetWeapon(playerid);
		if(wep != 23)
			return SendErrorMessage(playerid, "You must holding 9mm Silenced!");

		if(PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] >= 170)
			return SendErrorMessage(playerid, "Total peluru tidak bisa lebih dari 170!");

		PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] += 17;
		PlayReloadAnimation(playerid, 23);
		PlayerPlayNearbySound(playerid, 36401);
		Inventory_Remove(playerid, "9mm Luger", 1);

		if(PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] > 170) {
			PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] = 170;
		}
	}
	else if(!strcmp(name, "12 Gauge"))
	{
		new wep = GetWeapon(playerid);
		if(wep != 25)
			return SendErrorMessage(playerid, "You must holding Shotgun!");

		if(PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] >= 120)
			return SendErrorMessage(playerid, "Total peluru tidak bisa lebih dari 120!");

		PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] += 12;
		PlayReloadAnimation(playerid, 25);
		PlayerPlayNearbySound(playerid, 36401);
		Inventory_Remove(playerid, "12 Gauge", 1);

		if(PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] > 120) {
			PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] = 120;
		}
	}
	else if(!strcmp(name, "Rolling Paper"))
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
			return SendErrorMessage(playerid, "You must be on-foot!");

		if(Inventory_Count(playerid, "Weed") < 1)
			return SendErrorMessage(playerid, "Kamu membutuhkan 1 weed untuk membuat Rolled Weed!");

		if(IsValidLoadingBar(playerid))
			return SendErrorMessage(playerid, "You can't do this at the moment.");

		StartPlayerLoadingBar(playerid, 15, "Combining_Weed", 1000);
		SetTimerEx("Combined", 15000, false, "d", playerid);
		ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 1, 0, 0, 0, 0, 1);
		Inventory_Remove(playerid, "Weed", 1);
		Inventory_Remove(playerid, "Rolling Paper", 1);
	}
	else if(!strcmp(name, "Weed Seed"))
	{
		new wid = Weed_Nearest(playerid);

		if(!IsAtDrugField(playerid))
			return SendErrorMessage(playerid, "You only can plant weed at Weed Field!");

		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
			return SendErrorMessage(playerid, "You must be on-foot!");

		if(IsValidLoadingBar(playerid))
			return SendErrorMessage(playerid, "You can't do this at the moment.");

		if(wid != -1)
			return SendErrorMessage(playerid, "Kamu terlalu dekat dengan tanaman lain!");

		if(Weed_Count() >= MAX_WEED)
			return SendErrorMessage(playerid, "The server cannot create more Weeds!");

		new
			Float:x, Float:y, Float:z;

		GetPlayerPos(playerid, x, y, z);
		
		Inventory_Remove(playerid, "Weed Seed", 1);
		SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s plants some weed seeds into the ground.", ReturnName(playerid));
		StartPlayerLoadingBar(playerid, 5, "Planting_weed", 1000);
		SetTimerEx("PlantWeed", 5000, false, "dfff", playerid, x, y, z);
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Loop", 4.1, 1, 0, 0, 1, 0, 1);
	}
	else if(!strcmp(name, "Bandage"))
	{
		if(PlayerData[playerid][pBandage])
			return SendErrorMessage(playerid, "You already using a Bandage");

		if(PlayerData[playerid][pFirstAid])
			return SendErrorMessage(playerid, "You already using a Medkit");

		if (ReturnHealth(playerid) > 99)
		    return SendErrorMessage(playerid, "You don't need to use a bandage right now.");

		if (!IsPlayerInAnyVehicle(playerid))
		    ApplyAnimation(playerid, "SWAT", "gnstwall_injurd", 4.0, 1, 0, 0, 0, 0);

	    PlayerData[playerid][pBandage] = true;
	    PlayerData[playerid][pAidTimer] = SetTimerEx("BandageUpdate", 5000, false, "d", playerid);

	    SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s opens a bandage kit and uses it.", ReturnName(playerid));
	    Inventory_Remove(playerid, "Bandage", 1);
	}
	else if(!strcmp(name, "Medkit"))
	{
		if(PlayerData[playerid][pBandage])
			return SendErrorMessage(playerid, "You already using a Bandage.");

		if(PlayerData[playerid][pFirstAid])
			return SendErrorMessage(playerid, "You already using a Medkit");

		if (ReturnHealth(playerid) > 99)
		    return SendErrorMessage(playerid, "You don't need to use a medkit right now.");

		if (!IsPlayerInAnyVehicle(playerid))
		    ApplyAnimation(playerid, "SWAT", "gnstwall_injurd", 4.0, 1, 0, 0, 0, 0);

	    PlayerData[playerid][pFirstAid] = true;
	    PlayerData[playerid][pAidTimer] = SetTimerEx("FirstAidUpdate", 1000, true, "d", playerid);

	    SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s opens a medkit kit and uses it.", ReturnName(playerid));
	    Inventory_Remove(playerid, "Medkit");
	}
	return 1;
}

CMD:inventory(playerid, params[])
{
	PlayerData[playerid][pStorageSelect] = 0;
	OpenInventory(playerid);
	return 1;
}

CMD:setitem(playerid, params[])
{
	new
	    userid,
		item[32],
		amount;

	if (PlayerData[playerid][pAdmin] < 6)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "uds[32]", userid, amount, item))
	    return SendSyntaxMessage(playerid, "/setitem [playerid/PartOfName] [amount] [item name]");

	if(userid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "You have specified invalid player!");
		
	for (new i = 0; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], item, true))
	{
        Inventory_Set(userid, g_aInventoryItems[i][e_InventoryItem], g_aInventoryItems[i][e_InventoryModel], amount);
		SendServerMessage(playerid, "You have set %s's \"%s\" to %d.", ReturnName(userid), item, amount);
		SendClientMessageEx(userid, X11_LIGHTBLUE, "(Inventory) "WHITE"Admin "RED"%s "WHITE"has set your "YELLOW"%s "WHITE"to "YELLOW"%d", GetUsername(playerid), item, amount);
		return 1;
	}
	SendErrorMessage(playerid, "Invalid item name (use /itemlist for a list).");
	return 1;
}

CMD:itemlist(playerid, params[])
{
	new
	    string[1024];

	if (!strlen(string)) {
		for (new i = 0; i < sizeof(g_aInventoryItems); i ++) {
			format(string, sizeof(string), "%s%s\n", string, g_aInventoryItems[i][e_InventoryItem]);
		}
	}
	return ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_LIST, "List of Items", string, "Select", "Cancel");
}
