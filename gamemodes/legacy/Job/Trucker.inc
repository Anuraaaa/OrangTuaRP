new ListedCrate[MAX_PLAYERS][MAX_CRATES];

IsTruckerCar(vehicleid)
{
	new modelid = GetVehicleModel(vehicleid);

	if (GetVehicleTrailer(vehicleid))
	    modelid = GetVehicleModel(GetVehicleTrailer(vehicleid));

	switch (modelid)
	{
	    case 456, 499, 498: return 1;
	}
	return 0;
}

GetCrateLimit(modelid) {
	new limit = 0;
	switch(modelid) {
		case 456: limit = 15;
		case 498: limit = 10;
		case 499: limit = 5;
		default: limit = 5;
	}
	return limit;
}
CMD:cargo(playerid, params[])
{
	if(!CheckPlayerJob(playerid, JOB_TRUCKER))
		return SendErrorMessage(playerid, "Kamu bukan seorang Trucker!");

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/cargo [Type]"), SendClientMessage(playerid, COLOR_SERVER, "Type: {FFFFFF}list, place, buy, sell, remove, bizinfo");

	if(!strcmp(params, "list", true))
	{
		new pvid = Vehicle_Nearest(playerid, 5.0), count = 0;

		if(IsPlayerInAnyVehicle(playerid))
			return SendErrorMessage(playerid, "Keluar dari kendaraan terlebih dahulu!");

		if(pvid == -1)
			return SendErrorMessage(playerid, "Kamu tidak berada dibelakang Truck manapun!");

		if(!IsTruckerCar(pvid))
			return SendErrorMessage(playerid, "Kamu tidak berada dibelakang Truck manapun!");
		
		if(!IsPlayerNearBoot(playerid, pvid))
			return SendErrorMessage(playerid, "Kamu tidak berada dibelakang Truck manapun!");

		if(VehicleData[pvid][vLocked])	
			return SendErrorMessage(playerid, "Kendaraan ini masih terkunci!");

		if(!GetTrunkStatus(pvid))
			return SendErrorMessage(playerid, "Status trunk masih dalam keadaan tertutup!");
			
		new str[412], bool:found = false;
		foreach(new i : Crate) if(CrateData[i][crateVehicle] == VehicleData[pvid][vID])
		{
			format(str, sizeof(str), "%s%s Cargo\n", str, Crate_Name[CrateData[i][crateType]]);
			found = true;
			ListedCrate[playerid][count++] = i;
		}
		if(found)
			ShowPlayerDialog(playerid, DIALOG_CRATE, DIALOG_STYLE_LIST, sprintf("Crate List (%d/%d)", Crate_Count(pvid), GetCrateLimit(GetVehicleModel(pvid))), str, "Take", "Close");
		else
			SendErrorMessage(playerid, "Tidak ada Cargo pada Truck ini!");

		PlayerData[playerid][pVehicle] = pvid;
	}
	else if(!strcmp(params, "bizinfo", true)) {

		ShowPlayerDialog(playerid, DIALOG_BIZINFO, DIALOG_STYLE_LIST, "Business Info", "Fast Food\nMarket(24/7)\nClothes\nElectronic\nEquipment\nSpareparts", "Select", "Close");
	}
	else if(!strcmp(params, "sell", true))
	{

		new
			cid =  PlayerData[playerid][pCrate];

		if(IsPlayerInAnyVehicle(playerid))
			return SendErrorMessage(playerid, "Keluar dari kendaraan terlebih dahulu!");
			
		if(PlayerData[playerid][pHunger] < 15 || PlayerData[playerid][pThirst] < 15)
			return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");

		if(cid == -1)
			return SendErrorMessage(playerid, "Kamu sedang tidak mengangkat Cargo!");

		if(IsPlayerInRangeOfPoint(playerid, 3.0, -1862.1053,-145.7666,11.8984)) {

			if(CrateData[cid][crateType] != CARGO_TYPE_COMPONENT)
				return SendErrorMessage(playerid, "Tipe cargo tidak sesuai!");

			if(StockData[stockComponent] >= 10000)
				return SendErrorMessage(playerid, "Stock pada component warehouse sudah penuh!");

			if(StockData[stockComponent] + 50 >= 10000)
				return SendErrorMessage(playerid, "Jumlah total stock component tidak bisa lebih dari 10.000!");

			GiveMoney(playerid, 3000, "Sell cargo");
			SendClientMessageEx(playerid, COLOR_SERVER, "(Cargo) {FFFFFF}Kamu berhasil menjual {FFFF00}%s Cargo {FFFFFF}dan mendapat {00FF00}$30.00", Crate_Name[CrateData[cid][crateType]]);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);		
			ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 0, 0, 0, 0, 1);
			RemovePlayerAttachedObject(playerid, 9);
			Crate_Delete(cid);
			PlayerData[playerid][pCrate] = -1;

			StockData[stockComponent] += RandomEx(20, 50);
			UpdateServerStock(SERVER_STOCK_COMPONENT);
		}
		else {

			new id = Business_NearestDeliver(playerid);

			if(id == -1)
				return SendErrorMessage(playerid, "Kamu tidak berada di Delivery Point manapun!");

			if(PlayerData[playerid][pCrate] == -1)
				return SendErrorMessage(playerid, "Kamu tidak sedang mengangkat Cargo!");

			if(CrateData[PlayerData[playerid][pCrate]][crateType] != ReturnBizTypeToCargo(BizData[id][bizType]))
				return SendErrorMessage(playerid, "Tipe Cargo tidak sesuai dengan Tipe business!");

			if(!BizData[id][bizReq])
				return  SendErrorMessage(playerid, "Bisnis ini tidak meminta untuk pengisian produk!");
				
			if(BizData[id][bizStock] >= 100)
				return SendErrorMessage(playerid, "Stock pada business ini sudah penuh!");

			if(BizData[id][bizStock] + 20 >= 100)
				return SendErrorMessage(playerid, "Total stock business tidak bisa lebih dari 100!");
				
			new str[256];
			format(str, sizeof(str), "{FFFFFF}Business: %s\n{FFFFFF}Type: %s\nCargo Price: {00FF00}$%s\n\n{FFFFFF}Tekan {FFFF00}Confirm {FFFFFF}untuk menjual Cargo.", BizData[id][bizName], GetBizType(BizData[id][bizType]), FormatNumber(BizData[id][bizCargo]));
			ShowPlayerDialog(playerid, DIALOG_SELLCARGO, DIALOG_STYLE_MSGBOX, "Sell Cargo", str, "Confirm", "Close");
			PlayerData[playerid][pBusiness] = id;

		}

		PlayerData[playerid][pThirst] -= 1.1;
	}
	else if(!strcmp(params, "place", true))
	{
		new pvid = Vehicle_Nearest(playerid, 5.0);

		if(PlayerData[playerid][pCrate] == -1)
			return SendErrorMessage(playerid, "Kamu tidak sedang tidak mengangkat Cargo!");

		if(pvid == -1)
			return SendErrorMessage(playerid, "Kamu tidak berada dibelakang Truck manapun!");

		if(!IsTruckerCar(pvid))
			return SendErrorMessage(playerid, "Kamu tidak berada dibelakang Truck manapun!");

		if(!IsPlayerNearBoot(playerid, pvid))
			return SendErrorMessage(playerid, "Kamu tidak berada dibelakang Truck manapun!");

		if(Crate_Count(pvid) >= GetCrateLimit(GetVehicleModel(pvid)))
			return SendErrorMessage(playerid, "Truck ini tidak bisa menampung lebih banyak Cargo!");

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);		
		ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 0, 0, 0, 0, 1);
		RemovePlayerAttachedObject(playerid, 9);
		SendClientMessageEx(playerid, COLOR_SERVER, "(Cargo) {FFFFFF}Kamu menyimpan {FFFF00}%s Cargo {FFFFFF}kedalam %s!", Crate_Name[CrateData[PlayerData[playerid][pCrate]][crateType]], GetVehicleName(pvid));
		CrateData[PlayerData[playerid][pCrate]][crateVehicle] = VehicleData[pvid][vID];
		Crate_Save(PlayerData[playerid][pCrate]);
		PlayerData[playerid][pCrate] = -1;
	}
	else if(!strcmp(params, "remove", true))
	{
		if(PlayerData[playerid][pCrate] == -1)
			return SendErrorMessage(playerid, "Kamu tidak sedang tidak mengangkat Cargo!");

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);		
		ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 0, 0, 0, 0, 1);
		RemovePlayerAttachedObject(playerid, 9);
		Crate_Delete(PlayerData[playerid][pCrate]);
		SendClientMessage(playerid, COLOR_SERVER, "(Cargo) {FFFFFF}Kamu berhasil menghapus cargo.");		
		PlayerData[playerid][pCrate] = -1;
	}
	else if(!strcmp(params, "buy", true))
	{
		new id = -1;
		
		if(PlayerData[playerid][pCrate] != -1)
			return SendErrorMessage(playerid, "Kamu sedang mengangkat Cargo!");

		if(IsHungerOrThirst(playerid))
			return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja.");

		if(IsPlayerInRangeOfPoint(playerid, 3.0, -1875.0437, 1419.0042, 7.1797))
		{
			if(GetMoney(playerid) < 1500)
				return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang.");

			id = Crate_Create(playerid, CARGO_TYPE_ELECTRO);

			if(id == -1)
				return SendErrorMessage(playerid, "Server tidak dapat membuat lebih banyak cargo.");

			GiveMoney(playerid, -1500, "Membeli Cargo Electonic");
			SendClientMessage(playerid, COLOR_SERVER, "(Cargo) {FFFFFF}Kamu berhasil membeli Electronic Cargo seharga {00FF00}$15.0");
		}
		else if(IsPlayerInRangeOfPoint(playerid, 3.0, -1826.1199,1455.6929,7.1875))
		{
			if(GetMoney(playerid) < 1500)
				return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang.");

			id = Crate_Create(playerid, CARGO_TYPE_SPAREPARTS);
			
			if(id == -1)
				return SendErrorMessage(playerid, "Server tidak dapat membuat lebih banyak cargo.");

			GiveMoney(playerid, -1500, "Membeli Cargo Spare Parts");
			SendClientMessage(playerid, COLOR_SERVER, "(Cargo) {FFFFFF}Kamu berhasil membeli Spareparts Cargo seharga {00FF00}$15.0");			
		}	
		else if(IsPlayerInRangeOfPoint(playerid, 3.0, -1790.5422, 1429.7609, 7.1841))
		{
			if(GetMoney(playerid) < 1500)
				return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang.");

			id = Crate_Create(playerid, CARGO_TYPE_CLOTHES);
			
			if(id == -1)
				return SendErrorMessage(playerid, "Server tidak dapat membuat lebih banyak cargo.");

			GiveMoney(playerid, -1500, "Membeli Cargo Clothes");
			SendClientMessage(playerid, COLOR_SERVER, "(Cargo) {FFFFFF}Kamu berhasil membeli Clothes Cargo seharga {00FF00}$15.0");			
		}		
		else if(IsPlayerInRangeOfPoint(playerid, 3.0, -1835.1539, 1429.7806, 7.1841))
		{
			if(GetMoney(playerid) < 2000)
				return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang.");

			id = Crate_Create(playerid, CARGO_TYPE_247);
			
			if(id == -1)
				return SendErrorMessage(playerid, "Server tidak dapat membuat lebih banyak cargo.");

			GiveMoney(playerid, -2000, "Membeli Cargo 24/7");
			SendClientMessage(playerid, COLOR_SERVER, "(Cargo) {FFFFFF}Kamu berhasil membeli 24/7 Cargo seharga {00FF00}$20.0");			
		}
		else if(IsPlayerInRangeOfPoint(playerid, 3.0, -1741.8209, 1429.7811, 7.1875))
		{
			if(GetMoney(playerid) < 2000)
				return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang.");

			id = Crate_Create(playerid, CARGO_TYPE_FASTFOOD);

			if(id == -1)
				return SendErrorMessage(playerid, "Server tidak dapat membuat lebih banyak cargo.");

			GiveMoney(playerid, -2000, "Membeli Cargo Fast Food");
			SendClientMessage(playerid, COLOR_SERVER, "(Cargo) {FFFFFF}Kamu berhasil membeli Fast Food Cargo seharga {00FF00}$20.0");			
		}
		else if(IsPlayerInRangeOfPoint(playerid, 3.0, -1886.6575,1444.1444,7.1842))
		{
			if(GetMoney(playerid) < 2000)
				return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang.");

			id = Crate_Create(playerid, CARGO_TYPE_EQUIPMENT);

			if(id == -1)
				return SendErrorMessage(playerid, "Server tidak dapat membuat lebih banyak cargo.");

			GiveMoney(playerid, -2000, "Membeli Cargo Equipment");
			SendClientMessage(playerid, COLOR_SERVER, "(Cargo) {FFFFFF}Kamu berhasil membeli Equipment Cargo seharga {00FF00}$20.0");			
		}
		else if(IsPlayerInRangeOfPoint(playerid, 3.0, -1304.1875,2491.8530,87.1437)) {
			
			if(StockData[stockRock] < 1)
				return SendErrorMessage(playerid, "Tidak ada stok batu yang tersedia.");
				
			id = Crate_Create(playerid, CARGO_TYPE_COMPONENT);

			if(id == -1)
				return SendErrorMessage(playerid, "Server tidak dapat membuat lebih banyak cargo.");

			SendClientMessage(playerid, COLOR_SERVER, "(Cargo) {FFFFFF}Kamu berhasil mendapatkan Component Cargo!");		

			StockData[stockRock]--;
			UpdateServerStock(SERVER_STOCK_ROCK);
		}
	}
	return 1;
}
