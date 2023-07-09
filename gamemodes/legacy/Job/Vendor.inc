#include <YSI_Coding\y_hooks>

new const FoodName[][] = {
	"None",
	"Burger",
	"Pizza"
};

new const DrinkName[][] = {
	"None",
	"Cola",
	"Sprunk"
};

enum 
{
	FOOD_NONE,
	FOOD_BURGER,
	FOOD_PIZZA
};

enum 
{
	DRINK_NONE,
	DRINK_COLA,
	DRINK_SPRUNK
};


enum vendor_data
{
	STREAMER_TAG_CP:vendorCP,
	STREAMER_TAG_ACTOR:vendorActor,
	vendorFood,
	vendorDrink,
	vendorReqFood,
	vendorReqDrink,
};
new VendorData[MAX_VENDOR][vendor_data];

SetupVendor()
{
	VendorData[0][vendorCP] = CreateDynamicCP(-1978.8419,174.9800,27.6875, 1.0, -1, -1, -1, 2.0);
	VendorData[1][vendorCP] = CreateDynamicCP(-1978.9037,179.9693,27.6875, 1.0, -1, -1, -1, 2.0);
	VendorData[2][vendorCP] = CreateDynamicCP(-1978.9030,185.0620,27.6875, 1.0, -1, -1, -1, 2.0);
	forex(i, MAX_VENDOR)
	{
		VendorData[i][vendorFood] = FOOD_NONE;
		VendorData[i][vendorDrink] = DRINK_NONE;
	}
}

function MakeDrink(playerid, drink, id)
{
	VendorData[id][vendorDrink] = drink;
	SendClientMessageEx(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu berhasil membuat {FFFF00}%s", DrinkName[VendorData[id][vendorDrink]]);
	PlayerTextDrawSetString(playerid, DONEDRINK[playerid], sprintf("-_%s", DrinkName[VendorData[id][vendorDrink]]));
	return 1;
}


function CookFood(playerid, food, id)
{
	VendorData[id][vendorFood] = food;
	SendClientMessageEx(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu berhasil memasak {FFFF00}%s", FoodName[VendorData[id][vendorFood]]);
	PlayerTextDrawSetString(playerid, DONEFOOD[playerid], sprintf("-_%s", FoodName[VendorData[id][vendorFood]]));
	return 1;
}

IsVendorUsed(id)
{
	foreach(new i : Player) if(PlayerData[i][pVendor] == id)
	{
		return 1;
	}
	return 0;
}
SetupPlayerVendor(playerid)
{
	switch(PlayerData[playerid][pVendor])
	{
		case 0: VendorData[PlayerData[playerid][pVendor]][vendorActor] = CreateDynamicActor(g_aMaleSkins[random(sizeof(g_aMaleSkins))], -1981.9326, 174.9760, 27.6799, 269.1324, _, 100.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 20.0);
		case 1: VendorData[PlayerData[playerid][pVendor]][vendorActor] = CreateDynamicActor(g_aMaleSkins[random(sizeof(g_aMaleSkins))], -1982.0510,180.0440,27.6875,268.8190, 1, 100.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 20.0);
		case 2: VendorData[PlayerData[playerid][pVendor]][vendorActor] = CreateDynamicActor(g_aMaleSkins[random(sizeof(g_aMaleSkins))], -1982.0667,184.9321,27.6875,271.0125, 1, 100.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 20.0);
	}
	forex(i, 18)
	{
		PlayerTextDrawShow(playerid, VENDORTD[playerid][i]);
	}
	PlayerTextDrawShow(playerid, DONEJOB[playerid]);
	PlayerTextDrawShow(playerid, BURGERTD[playerid]);
	PlayerTextDrawShow(playerid, PIZZATD[playerid]);
	PlayerTextDrawShow(playerid, COLATD[playerid]);
	PlayerTextDrawShow(playerid, SPRUNKTD[playerid]);
	PlayerTextDrawShow(playerid, FOODTD[playerid]);
	PlayerTextDrawShow(playerid, DRINKTD[playerid]);
	PlayerTextDrawShow(playerid, RESETJOB[playerid]);
	PlayerTextDrawShow(playerid, EXITJOB[playerid]);
	PlayerTextDrawShow(playerid, DONEFOOD[playerid]);
	PlayerTextDrawShow(playerid, DONEDRINK[playerid]);
	SelectTextDraw(playerid, COLOR_YELLOW);

	VendorData[PlayerData[playerid][pVendor]][vendorReqFood] = random(2)+1;
	VendorData[PlayerData[playerid][pVendor]][vendorReqDrink] = random(2)+1;

	PlayerTextDrawSetString(playerid, DRINKTD[playerid], sprintf("-_%s", DrinkName[VendorData[PlayerData[playerid][pVendor]][vendorReqDrink]]));
	PlayerTextDrawSetString(playerid, FOODTD[playerid], sprintf("-_%s", FoodName[VendorData[PlayerData[playerid][pVendor]][vendorReqFood]]));
	TogglePlayerControllable(playerid, 0);
	SetPlayerFacingAngle(playerid, 91.5255);
	SetCameraBehindPlayer(playerid);
	Streamer_Update(playerid, STREAMER_TYPE_ACTOR);
	
	SendNearbyMessage(playerid, 5.0, COLOR_WHITE, "Buyer %d says: Hello, i want to order %s and %s.", PlayerData[playerid][pVendor] + 1, FoodName[VendorData[PlayerData[playerid][pVendor]][vendorReqFood]], DrinkName[VendorData[PlayerData[playerid][pVendor]][vendorReqDrink]]);
	return 1;
}

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid) {

	new vendorid = PlayerData[playerid][pVendor];
	if(playertextid == DONEJOB[playerid])
	{
		if(IsValidLoadingBar(playerid))
			return SendErrorMessage(playerid, "Kamu tidak dapat melakukan ini sekarang.");

		if(VendorData[vendorid][vendorFood] != VendorData[vendorid][vendorReqFood])
			return SendErrorMessage(playerid, "Makanan tidak sesuai dengan yang dipesan!");

		if(VendorData[vendorid][vendorDrink] != VendorData[vendorid][vendorReqDrink])
			return SendErrorMessage(playerid, "Minuman tidak sesuai dengan yang dipesan!");

		new cash = RandomEx(300, 600);
		GiveMoney(playerid, cash);
		SendClientMessageEx(playerid, COLOR_SERVER, "(Sidejob) {FFFFFF}Kamu mendapatkan {00FF00}$%s {FFFFFF}dari menjual {FFFF00}%s {FFFFFF}dan {FFFF00}%s", FormatNumber(cash), FoodName[VendorData[vendorid][vendorFood]], DrinkName[VendorData[vendorid][vendorDrink]]);
		
		Streamer_SetIntData(STREAMER_TYPE_ACTOR, VendorData[vendorid][vendorActor], E_STREAMER_MODEL_ID, g_aMaleSkins[random(sizeof(g_aMaleSkins))]);
		VendorData[vendorid][vendorReqFood] = random(2)+1;
		VendorData[vendorid][vendorReqDrink] = random(2)+1;
		VendorData[vendorid][vendorFood] = FOOD_NONE;
		VendorData[vendorid][vendorDrink] = DRINK_NONE;

		PlayerTextDrawSetString(playerid, DRINKTD[playerid], sprintf("-_%s", DrinkName[VendorData[vendorid][vendorReqDrink]]));
		PlayerTextDrawSetString(playerid, FOODTD[playerid], sprintf("-_%s", FoodName[VendorData[vendorid][vendorReqFood]]));

		PlayerTextDrawSetString(playerid, DONEFOOD[playerid], "");
		PlayerTextDrawSetString(playerid, DONEDRINK[playerid], "");

		SendNearbyMessage(playerid, 5.0, COLOR_WHITE, "Buyer %d says: Hello, i want to order %s and %s.", PlayerData[playerid][pVendor] + 1, FoodName[VendorData[PlayerData[playerid][pVendor]][vendorReqFood]], DrinkName[VendorData[PlayerData[playerid][pVendor]][vendorReqDrink]]);
	}
	if(playertextid == EXITJOB[playerid])
	{
		if(IsValidLoadingBar(playerid))
			return SendErrorMessage(playerid, "You can't do this at the moment.");

		if(IsValidDynamicActor(VendorData[vendorid][vendorActor]))
			DestroyDynamicActor(VendorData[vendorid][vendorActor]);

		VendorData[vendorid][vendorReqFood] = FOOD_NONE;
		VendorData[vendorid][vendorReqDrink] = DRINK_NONE;
		VendorData[vendorid][vendorFood] = FOOD_NONE;
		VendorData[vendorid][vendorDrink] = DRINK_NONE;

		forex(i, 18)
		{
			PlayerTextDrawHide(playerid, VENDORTD[playerid][i]);
		}
		PlayerTextDrawHide(playerid, DONEJOB[playerid]);
		PlayerTextDrawHide(playerid, BURGERTD[playerid]);
		PlayerTextDrawHide(playerid, PIZZATD[playerid]);
		PlayerTextDrawHide(playerid, COLATD[playerid]);
		PlayerTextDrawHide(playerid, SPRUNKTD[playerid]);
		PlayerTextDrawHide(playerid, FOODTD[playerid]);
		PlayerTextDrawHide(playerid, DRINKTD[playerid]);
		PlayerTextDrawHide(playerid, RESETJOB[playerid]);
		PlayerTextDrawHide(playerid, EXITJOB[playerid]);
		PlayerTextDrawHide(playerid, DONEFOOD[playerid]);
		PlayerTextDrawHide(playerid, DONEDRINK[playerid]);
		CancelSelectTextDraw(playerid);
		PlayerData[playerid][pVendor] = -1;
		SetCameraBehindPlayer(playerid);
		TogglePlayerControllable(playerid, 1);
	}
	if(playertextid == RESETJOB[playerid])
	{
		if(IsValidLoadingBar(playerid))
			return SendErrorMessage(playerid, "Kamu tidak dapat melakukan ini sekarang.");

		PlayerTextDrawSetString(playerid, DONEFOOD[playerid], "");
		PlayerTextDrawSetString(playerid, DONEDRINK[playerid], "");

		VendorData[vendorid][vendorFood] = FOOD_NONE;
		VendorData[vendorid][vendorDrink] = DRINK_NONE;

	}
	if(playertextid == COLATD[playerid])
	{
		if(PlayerData[playerid][pHunger] > 15 && PlayerData[playerid][pThirst] > 15) {
			if(VendorData[vendorid][vendorDrink] != DRINK_NONE)
				return SendErrorMessage(playerid, "Kamu sudah membuat Drink! (%s)", DrinkName[VendorData[vendorid][vendorDrink]]);

			if(IsValidLoadingBar(playerid))
				return SendErrorMessage(playerid, "Kamu tidak dapat melakukan ini sekarang.");

			StartPlayerLoadingBar(playerid, 10, "Filling_Cola", 1000);
			SetTimerEx("MakeDrink", 10000, false, "ddd", playerid, DRINK_COLA, vendorid);
			PlayerData[playerid][pHunger] -= RandomEx(1, 4);
			PlayerData[playerid][pThirst] -= RandomEx(1, 4);
		}
		else SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");
	}
	if(playertextid == SPRUNKTD[playerid])
	{
		if(PlayerData[playerid][pHunger] > 15 && PlayerData[playerid][pThirst] > 15) {
			if(VendorData[vendorid][vendorDrink] != DRINK_NONE)
				return SendErrorMessage(playerid, "Kamu sudah membuat Drink! (%s)", DrinkName[VendorData[vendorid][vendorDrink]]);

			if(IsValidLoadingBar(playerid))
				return SendErrorMessage(playerid, "Kamu tidak dapat melakukan ini sekarang.");

			StartPlayerLoadingBar(playerid, 10, "Filling_Sprunk", 1000);
			SetTimerEx("MakeDrink", 10000, false, "ddd", playerid, DRINK_SPRUNK, vendorid);
			PlayerData[playerid][pHunger] -= RandomEx(1, 4);
			PlayerData[playerid][pThirst] -= RandomEx(1, 4);
		}
		else SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");
	}
	if(playertextid == PIZZATD[playerid])
	{
		if(PlayerData[playerid][pHunger] > 15 && PlayerData[playerid][pThirst] > 15) { 
			if(VendorData[vendorid][vendorFood] != FOOD_NONE)
				return SendErrorMessage(playerid, "Kamu sudah membuat Food! (%s)", FoodName[VendorData[vendorid][vendorFood]]);

			if(IsValidLoadingBar(playerid))
				return SendErrorMessage(playerid, "Kamu tidak dapat melakukan ini sekarang.");

			StartPlayerLoadingBar(playerid, 10, "Cooking_Pizza", 1000);
			SetTimerEx("CookFood", 10000, false, "ddd", playerid, FOOD_PIZZA, vendorid);
			PlayerData[playerid][pHunger] -= RandomEx(1, 4);
			PlayerData[playerid][pThirst] -= RandomEx(1, 4);
		}
		else SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");
	}
	if(playertextid == BURGERTD[playerid])
	{
		if(PlayerData[playerid][pHunger] > 15 && PlayerData[playerid][pThirst] > 15) {
			if(VendorData[vendorid][vendorFood] != FOOD_NONE)
				return SendErrorMessage(playerid, "Kamu sudah membuat Food! (%s)", FoodName[VendorData[vendorid][vendorFood]]);

			if(IsValidLoadingBar(playerid))
				return SendErrorMessage(playerid, "Kamu tidak dapat melakukan ini sekarang.");

			StartPlayerLoadingBar(playerid, 10, "Cooking_Burger", 1000);
			SetTimerEx("CookFood", 10000, false, "ddd", playerid, FOOD_BURGER, vendorid);
			PlayerData[playerid][pHunger] -= RandomEx(1, 4);
			PlayerData[playerid][pThirst] -= RandomEx(1, 4);
		}
		else SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}