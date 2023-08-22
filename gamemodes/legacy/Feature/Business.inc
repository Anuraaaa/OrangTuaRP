#include <YSI_Coding\y_hooks>

forward OnBusinessDeleted(bizid);
forward OnBusinessRefuel(bizid);

enum 
{
	TYPE_FASTFOOD = 1,
	TYPE_247,
	TYPE_CLOTHES,
	TYPE_ELECTRO,
	TYPE_EQUIPMENT,
	TYPE_SPAREPARTS
};

enum E_BUSINESS_DATA
{
	bizID,
	bizName[32],
	bizOwner,
	bizOwnerName[MAX_PLAYER_NAME],
	bool:bizExists,
	Float:bizInt[3],
	Float:bizExt[3],
	Float:bizDeliver[3],
	bizWorld,
	bizInterior,
	bizVault,
	bizPrice,
	bizLocked,
	bizFuel,
	bizProduct[8],
	bizType,
	bizStock,
	bizCargo,
	bizDiesel,
	bizLastLogin,
	bizSealed,
	bizTaxPaid,
	bizTaxState,
	bizTaxDate,
	bool:bizReq,
	Float:bizFuelPos[3],
	STREAMER_TAG_PICKUP:bizFuelPickup,
	Text3D:bizFuelText,
	STREAMER_TAG_PICKUP:bizDeliverPickup,
	Text3D:bizDeliverText,
	STREAMER_TAG_PICKUP:bizPickup,
	Text3D:bizText,
	STREAMER_TAG_CP:bizCP,
	STREAMER_TAG_MAP_ICON:bizIcon,
};

new BizData[MAX_BUSINESS][E_BUSINESS_DATA];
new ProductName[MAX_BUSINESS][8][24], ProductDescription[MAX_BUSINESS][8][42];

hook OnGameModeInit() {

	if (IsSQLConnected()) {
		mysql_tquery(sqlcon, "SELECT * FROM `business`", "Business_Load");
	}
}

hook OnGameModeExit() {

	if (IsSQLConnected()) {

		new time = GetTickCount();

		for(new i = 0; i < MAX_BUSINESS; i++) if(BizData[i][bizExists]) {
			Business_Save(i);
		}
		printf("** Saved business data in %dms", GetTickCount() - time);
	}
}

ShowNumberIndex(playerid)
{
	new str[256];

	forex(i, 5)
	{
		NumberIndex[playerid][i] = RandomEx(11211, 98888) + PlayerData[playerid][pID];
		format(str, sizeof(str), "%s{FFFF00}%d\n", str, NumberIndex[playerid][i]);
	}
	format(str, sizeof(str), "%s{FF0000}Refresh Number List", str);
	ShowPlayerDialog(playerid, DIALOG_NUMBERPHONE, DIALOG_STYLE_LIST, "Select Phone Number", str, "Select", "Close");
	return 1;
}

Business_IsOpen(id) {
	if(BizData[id][bizOwner] == -1)
		return 0;

	return 1;
}
ShowBizStats(playerid)
{
	new id = PlayerData[playerid][pInBiz], price;

	if(id == -1)
		return 0;

	new str[512];

	price = BizData[id][bizPrice] * 5/100;

	strcat(str, "Name\tInfo\n");
	strcat(str, sprintf("Business Name:\t%s\n", BizData[id][bizName]));
	strcat(str, sprintf("Business Type:\t%s\n", GetBizType(BizData[id][bizType])));
	strcat(str, sprintf("Available stock:\t%d left\n", BizData[id][bizStock]));
	strcat(str, sprintf("Cash Vault:\t$%s\t", FormatNumber(BizData[id][bizVault])));
	strcat(str, sprintf("Harga Pajak: $%s\n", FormatNumber(price)));
	strcat(str, sprintf("Status: %s\n", (BizData[id][bizTaxState] == TAX_STATE_COOLDOWN) ? ("belum bisa dibayar") : ("sudah bisa dibayar")));
	strcat(str, sprintf("%s: %s\n", (BizData[id][bizTaxState] == TAX_STATE_COOLDOWN) ? ("Bayar dalam") : ("Jatuh tempo"), ConvertTimestamp(Timestamp:BizData[id][bizTaxDate])));
	ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, "Business Stats", str, "Close", "");
	return 1;
}

Biz_GetCount(playerid)
{
	new count = 0;
	forex(i, MAX_BUSINESS) if(BizData[i][bizExists] && BizData[i][bizOwner] == PlayerData[playerid][pID])
	{
	    count++;
	}
	return count;
}

SetProductName(playerid)
{
	new bid = PlayerData[playerid][pInBiz], string[712];
	if(!BizData[bid][bizExists])
	    return 0;

	switch(BizData[bid][bizType])
	{
	    case 1:
	    {
	        format(string, sizeof(string), "Product\tPrice\n%s (Food +20)\t$%s\n%s (Food +40)\t$%s\n%s (Drink)\t$%s",
				ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
	            FormatNumber(BizData[bid][bizProduct][1]),
	            ProductName[bid][2],
	            FormatNumber(BizData[bid][bizProduct][2])
			);
		}
		case 2:
		{
		    format(string, sizeof(string), "Product\tPrice\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s",
                ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
	            FormatNumber(BizData[bid][bizProduct][1]),
	            ProductName[bid][2],
	            FormatNumber(BizData[bid][bizProduct][2]),
	            ProductName[bid][3],
	            FormatNumber(BizData[bid][bizProduct][3]),
	        	ProductName[bid][4],
	            FormatNumber(BizData[bid][bizProduct][4]),
	        	ProductName[bid][5],
	            FormatNumber(BizData[bid][bizProduct][5]),
	        	ProductName[bid][6],
	            FormatNumber(BizData[bid][bizProduct][6]),
	        	ProductName[bid][7],
	            FormatNumber(BizData[bid][bizProduct][7])
			);
		}
		case 3:
		{
		    format(string, sizeof(string), "Product\tPrice\n%s (Clothes)\t$%s\n%s (Accessory)\t$%s",
                ProductName[bid][0],
		        FormatNumber(BizData[bid][bizProduct][0]),
                ProductName[bid][1],
		        FormatNumber(BizData[bid][bizProduct][1])
			);
		}
		case 4:
		{
		    format(string, sizeof(string), "Product\tPrice\n%s (Cellphone)\t$%s\n%s (GPS)\t$%s\n%s (Radio)\t$%s\n%s (Phone Credit)\t$%s",
                ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
	            FormatNumber(BizData[bid][bizProduct][1]),
	            ProductName[bid][2],
	            FormatNumber(BizData[bid][bizProduct][2]),
	            ProductName[bid][3],
	            FormatNumber(BizData[bid][bizProduct][3])
			);
		}
		case 5: {
		    format(string, sizeof(string), "Product\tPrice\n%s (Bat)\t$%s\n%s (Flower)\t$%s\n%s (Pool Cue)\t$%s\n%s (Cigarettes)\t$%s",
                ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
	            FormatNumber(BizData[bid][bizProduct][1]),
	            ProductName[bid][2],
	            FormatNumber(BizData[bid][bizProduct][2]),
	            ProductName[bid][3],
	            FormatNumber(BizData[bid][bizProduct][3])
			);
		}
		case 6: {
		    format(string, sizeof(string), "Product\tPrice\n%s (Octane Saver Fluid)\t$%s\n%s (Reinforced Engine Block)\t$%s\n%s (Reinforced Body Panels)\t$%s",
                ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
	            FormatNumber(BizData[bid][bizProduct][1]),
	            ProductName[bid][2],
	            FormatNumber(BizData[bid][bizProduct][2])
			);
		}
	}
	ShowPlayerDialog(playerid, DIALOG_BIZPROD, DIALOG_STYLE_TABLIST_HEADERS, "Set Product Name", string, "Select", "Close");
	return 1;
}

Business_Create(playerid, type, price)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

	if (GetPlayerPos(playerid, x, y, z))
	{
		for(new i = 0; i < MAX_BUSINESS; i++)
		{
	    	if (!BizData[i][bizExists])
		    {
    	        BizData[i][bizExists] = true;
        	    BizData[i][bizOwner] = -1;
            	BizData[i][bizPrice] = price;
            	BizData[i][bizType] = type;
				BizData[i][bizLastLogin] = 0;
				format(BizData[i][bizName], 32, "None Business");
				format(BizData[i][bizOwnerName], MAX_PLAYER_NAME, "No Owner");
    	        BizData[i][bizExt][0] = x;
    	        BizData[i][bizExt][1] = y;
    	        BizData[i][bizExt][2] = z;
				BizData[i][bizSealed] = 0;
				BizData[i][bizTaxDate] = gettime() + (14 * 86400);
				BizData[i][bizTaxState] = TAX_STATE_COOLDOWN;
				BizData[i][bizTaxPaid] = true;

				if (type == 1)
				{
                	BizData[i][bizInt][0] = 363.22;
                	BizData[i][bizInt][1] = -74.86;
                	BizData[i][bizInt][2] = 1001.50;
					BizData[i][bizInterior] = 10;
					format(ProductName[i][0], 24, "French Fries");
					format(ProductName[i][1], 24, "Fried Chicken");
					format(ProductName[i][2], 24, "Sprunk");
				}
				else if (type == 2)
				{
                	BizData[i][bizInt][0] = 5.73;
                	BizData[i][bizInt][1] = -31.04;
                	BizData[i][bizInt][2] = 1003.54;
					BizData[i][bizInterior] = 10;
					format(ProductName[i][0], 24, "Snack");
					format(ProductName[i][1], 24, "Mineral Water");
					format(ProductName[i][2], 24, "Mask");
					format(ProductName[i][3], 24, "Rolling Paper");
					format(ProductName[i][4], 24, "Axe");
					format(ProductName[i][5], 24, "Fish Rod");
					format(ProductName[i][6], 24, "Fuel Can");
					format(ProductName[i][7], 24, "Bandage");
				}
				else if(type == 3)
				{
                	BizData[i][bizInt][0] = 207.55;
                	BizData[i][bizInt][1] = -110.67;
                	BizData[i][bizInt][2] = 1005.13;
					BizData[i][bizInterior] = 15;
					format(ProductName[i][0], 24, "Clothes");
					format(ProductName[i][1], 24, "Accessory");
				}
				else if(type == 4)
				{
                	BizData[i][bizInt][0] = -2240.7825;
                	BizData[i][bizInt][1] = 137.1855;
                	BizData[i][bizInt][2] = 1035.4141;
					BizData[i][bizInterior] = 6;
					format(ProductName[i][0], 24, "Huawei Mate");
					format(ProductName[i][1], 24, "GPS");
					format(ProductName[i][2], 24, "Walkie Talkie");
					format(ProductName[i][3], 24, "Phone Credit");
				}
				else if(type == 5) {
                	BizData[i][bizInt][0] = -2240.7825;
                	BizData[i][bizInt][1] = 137.1855;
                	BizData[i][bizInt][2] = 1035.4141;
					BizData[i][bizInterior] = 6;
					format(ProductName[i][0], 24, "Baseball Bat");
					format(ProductName[i][1], 24, "Flower");
					format(ProductName[i][2], 24, "Pool Cue");
					format(ProductName[i][3], 24, "Pack of Cigarettes");
				}
				else if(type == 6) {
                	BizData[i][bizInt][0] = 640.2902;
                	BizData[i][bizInt][1] = -1568.1744;
                	BizData[i][bizInt][2] = -20.7241;
					BizData[i][bizInterior] = 6;
					format(ProductName[i][0], 24, "Octane Saver Fluid");
					format(ProductName[i][1], 24, "Reinforced Engine Block");
					format(ProductName[i][2], 24, "Reinforced Body Panels");
				}
				for(new e = 0; e < 7; e++)
				{
					format(ProductDescription[i][e], 40, "No description");
				}
				BizData[i][bizVault] = 0;
				BizData[i][bizStock] = 100;
				BizData[i][bizCargo] = 10000;
				BizData[i][bizFuel] = 1000;
				BizData[i][bizDiesel] = 1000;
				BizData[i][bizLocked] = true;
				Business_Spawn(i);
				mysql_tquery(sqlcon, "INSERT INTO `business` (`bizOwner`) VALUES(0)", "OnBusinessCreated", "d", i);
				return i;
			}
		}
	}
	return -1;
}

Biz_IsOwner(playerid, id)
{
	if(!BizData[id][bizExists])
	    return 0;
	    
	if(BizData[id][bizOwner] == PlayerData[playerid][pID])
		return 1;
		
	return 0;
}

function OnBusinessCreated(bizid)
{
	if (bizid == -1 || !BizData[bizid][bizExists])
	    return 0;

	BizData[bizid][bizID] = cache_insert_id();
	BizData[bizid][bizWorld] = BizData[bizid][bizID]+1000;
	
	Business_Save(bizid);
	return 1;
}

function Business_Load()
{
	new rows = cache_num_rows(), str[128], desc[312];
 	if(rows)
  	{
		forex(i, rows)
		{
		    BizData[i][bizExists] = true;
		    cache_get_value_name(i, "bizName", BizData[i][bizName]);
		    cache_get_value_name_int(i, "bizOwner", BizData[i][bizOwner]);
		    cache_get_value_name_int(i, "bizID", BizData[i][bizID]);
		    cache_get_value_name_float(i, "bizExtX", BizData[i][bizExt][0]);
		    cache_get_value_name_float(i, "bizExtY", BizData[i][bizExt][1]);
		    cache_get_value_name_float(i, "bizExtZ", BizData[i][bizExt][2]);
		    cache_get_value_name_float(i, "bizIntX", BizData[i][bizInt][0]);
		    cache_get_value_name_float(i, "bizIntY", BizData[i][bizInt][1]);
		    cache_get_value_name_float(i, "bizIntZ", BizData[i][bizInt][2]);
			for(new j = 0; j < 8; j++)
			{
				format(str, 32, "bizProduct%d", j + 1);
				cache_get_value_name_int(i, str, BizData[i][bizProduct][j]);
				format(str, 32, "bizProdName%d", j + 1);
				cache_get_value_name(i, str, ProductName[i][j]);
				format(desc, 312, "bizDescription%d", j + 1);
				cache_get_value_name(i, desc, ProductDescription[i][j]);
			}

			cache_get_value_name_int(i, "bizSealed", BizData[i][bizSealed]);
			cache_get_value_name_int(i, "bizVault", BizData[i][bizVault]);
			cache_get_value_name_int(i, "bizPrice", BizData[i][bizPrice]);
			cache_get_value_name_int(i, "bizType", BizData[i][bizType]);
			cache_get_value_name_int(i, "bizWorld", BizData[i][bizWorld]);
			cache_get_value_name_int(i, "bizInterior", BizData[i][bizInterior]);
			cache_get_value_name_int(i, "bizType", BizData[i][bizType]);
			cache_get_value_name_int(i, "bizStock", BizData[i][bizStock]);
			cache_get_value_name_int(i, "bizFuel", BizData[i][bizFuel]);
			cache_get_value_name(i, "bizOwnerName", BizData[i][bizOwnerName]);
			cache_get_value_name_float(i, "bizDeliverX", BizData[i][bizDeliver][0]);
			cache_get_value_name_float(i, "bizDeliverY", BizData[i][bizDeliver][1]);
			cache_get_value_name_float(i, "bizDeliverZ", BizData[i][bizDeliver][2]);
			cache_get_value_name_int(i, "bizCargo", BizData[i][bizCargo]);
			cache_get_value_name_float(i, "bizFuelX", BizData[i][bizFuelPos][0]);
			cache_get_value_name_float(i, "bizFuelY", BizData[i][bizFuelPos][1]);
			cache_get_value_name_float(i, "bizFuelZ", BizData[i][bizFuelPos][2]);
			cache_get_value_name_int(i, "bizLocked", BizData[i][bizLocked]);
			cache_get_value_name_int(i, "bizDiesel", BizData[i][bizDiesel]);
			cache_get_value_name_int(i, "bizLastLogin", BizData[i][bizLastLogin]);
			cache_get_value_name_int(i, "TaxDate", BizData[i][bizTaxDate]);
			cache_get_value_name_int(i, "TaxPaid", BizData[i][bizTaxPaid]);
			cache_get_value_name_int(i, "TaxState", BizData[i][bizTaxState]);

			Business_Spawn(i);

			BizData[i][bizReq] = true;
		}
		printf("[BUSINESS] Loaded %d Business from database", rows);
	}
	return 1;
}

Business_Spawn(i)
{
	new
	    string[296], icon;

	switch(BizData[i][bizType])
	{
		case 1: icon = 50;
		case 2: icon = 48;
		case 3: icon = 45;
		case 4: icon = 25;
	}
	if(BizData[i][bizDeliver][0] != 0 && BizData[i][bizDeliver][1] != 0 && BizData[i][bizDeliver][2] != 0)
	{
		BizData[i][bizDeliverPickup] = CreateDynamicPickup(1239, 23, BizData[i][bizDeliver][0], BizData[i][bizDeliver][1], BizData[i][bizDeliver][2], -1, -1);
		BizData[i][bizDeliverText] = CreateDynamic3DTextLabel(sprintf("%s\n{C6E2FF}Delivery Point", BizData[i][bizName]), COLOR_SERVER, BizData[i][bizDeliver][0], BizData[i][bizDeliver][1], BizData[i][bizDeliver][2], 15.0);
	}
	if (BizData[i][bizOwner] == -1)
	{
		format(string, sizeof(string), "[ID: %d]\nType: {C6E2FF}%s\n{FFFFFF}Price: {C6E2FF}$%s\n{FFFFFF}This business for sell\n{FFFF00}/biz buy {FFFFFF}for purchase this business.", i, GetBizType(BizData[i][bizType]), FormatNumber(BizData[i][bizPrice]));
	}
	else
	{
		if(!BizData[i][bizSealed])
			format(string, sizeof(string), "[ID: %d]\n%s{FFFFFF}\nStatus: {C6E2FF}%s{FFFFFF}\nType: {C6E2FF}%s\n"WHITE"Owned by "YELLOW"%s", i, BizData[i][bizName], (!BizData[i][bizLocked]) ? ("{00FF00}Open{FFFFFF}") : ("{FF0000}Closed{FFFFFF}"), GetBizType(BizData[i][bizType]), BizData[i][bizOwnerName]);
		else
			format(string, sizeof(string), "[ID: %d]\n%s{FFFFFF}\nStatus: {C6E2FF}%s{FFFFFF}\nType: {C6E2FF}%s\n"WHITE"Owned by "YELLOW"%s\n"WHITE"This business is sealed by "RED"authority", i, BizData[i][bizName], (!BizData[i][bizLocked]) ? ("{00FF00}Open{FFFFFF}") : ("{FF0000}Closed{FFFFFF}"), GetBizType(BizData[i][bizType]), BizData[i][bizOwnerName]);
	}
	BizData[i][bizText] = CreateDynamic3DTextLabel(string, -1, BizData[i][bizExt][0], BizData[i][bizExt][1], BizData[i][bizExt][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);
	BizData[i][bizCP] = CreateDynamicCP(BizData[i][bizExt][0], BizData[i][bizExt][1], BizData[i][bizExt][2], 1.0, -1, -1, -1, 2.0);
	BizData[i][bizPickup] = CreateDynamicPickup(19130, 23, BizData[i][bizExt][0], BizData[i][bizExt][1], BizData[i][bizExt][2], -1, -1);
	BizData[i][bizIcon] = CreateDynamicMapIcon(BizData[i][bizExt][0], BizData[i][bizExt][1], BizData[i][bizExt][2], icon, -1, -1, -1, -1, 70.0);
	return 1;
}
Business_Save(bizid)
{
	new
	    query[2098];

	mysql_format(sqlcon, query, sizeof(query), "UPDATE `business` SET `bizName` = '%s', `bizOwner` = '%d', `bizExtX` = '%f', `bizExtY` = '%f', `bizExtZ` = '%f', `bizIntX` = '%f', `bizIntY` = '%f', `bizIntZ` = '%f', `bizDeliverX` = '%f', `bizDeliverY` = '%f', `bizDeliverZ` = '%f', `bizCargo` = '%d', `bizDiesel` = '%d', `bizLocked` = '%d', `TaxPaid` = '%d', `TaxDate` = '%d', `TaxState` = '%d'",
		BizData[bizid][bizName],
		BizData[bizid][bizOwner],
		BizData[bizid][bizExt][0],
		BizData[bizid][bizExt][1],
		BizData[bizid][bizExt][2],
		BizData[bizid][bizInt][0],
		BizData[bizid][bizInt][1],
		BizData[bizid][bizInt][2],
		BizData[bizid][bizDeliver][0],
		BizData[bizid][bizDeliver][1],
		BizData[bizid][bizDeliver][2],
		BizData[bizid][bizCargo],
		BizData[bizid][bizDiesel],
		BizData[bizid][bizLocked],
		BizData[bizid][bizTaxPaid],
		BizData[bizid][bizTaxDate],
		BizData[bizid][bizTaxState]
	);
	forex(i, 8)
	{
		mysql_format(sqlcon, query, sizeof(query), "%s, `bizProduct%d` = '%d'", query, i + 1, BizData[bizid][bizProduct][i]);
	}
	forex(i, 8)
	{
		mysql_format(sqlcon, query, sizeof(query), "%s, `bizProdName%d` = '%s', `bizDescription%d` = '%s'", query, i + 1, ProductName[bizid][i], i + 1, ProductDescription[bizid][i]);
	}
	mysql_format(sqlcon, query, sizeof(query), "%s, `bizWorld` = '%d', `bizInterior` = '%d', `bizVault` = '%d', `bizType` = '%d', `bizStock` = '%d', `bizPrice` = '%d', `bizFuel` = '%d', `bizOwnerName` = '%s', `bizFuelX` = '%f', `bizFuelY` = '%f', `bizFuelZ` = '%f', `bizLastLogin` = '%d', `bizSealed` = '%d' WHERE `bizID` = '%d'",
		query,
		BizData[bizid][bizWorld],
		BizData[bizid][bizInterior],
		BizData[bizid][bizVault],
		BizData[bizid][bizType],
		BizData[bizid][bizStock],
		BizData[bizid][bizPrice],
		BizData[bizid][bizFuel],
		BizData[bizid][bizOwnerName],
		BizData[bizid][bizFuelPos][0], 
		BizData[bizid][bizFuelPos][1], 
		BizData[bizid][bizFuelPos][2], 
		BizData[bizid][bizLastLogin],
		BizData[bizid][bizSealed],
		BizData[bizid][bizID]
	);
	return mysql_tquery(sqlcon, query);
}

GetBizType(type)
{
	new str[32];
	switch(type)
	{
	    case 1: str = "Fast Food";
	    case 2: str = "24/7";
	    case 3: str = "Clothes";
	    case 4: str = "Electronic";
		case 5: str = "Equipment";
		case 6: str = "Spareparts";
	}
	return str;
}

Business_Refresh(bizid)
{
	if (bizid != -1 && BizData[bizid][bizExists])
	{

		new
		    string[256];

		if(BizData[bizid][bizDeliver][0] != 0 && BizData[bizid][bizDeliver][1] != 0 && BizData[bizid][bizDeliver][2] != 0)
		{
			Streamer_SetFloatData(STREAMER_TYPE_PICKUP, BizData[bizid][bizDeliverPickup], E_STREAMER_X, BizData[bizid][bizDeliver][0]);
			Streamer_SetFloatData(STREAMER_TYPE_PICKUP, BizData[bizid][bizDeliverPickup], E_STREAMER_Y, BizData[bizid][bizDeliver][1]);
			Streamer_SetFloatData(STREAMER_TYPE_PICKUP, BizData[bizid][bizDeliverPickup], E_STREAMER_Z, BizData[bizid][bizDeliver][2]);

			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, BizData[bizid][bizDeliverText], E_STREAMER_X, BizData[bizid][bizDeliver][0]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, BizData[bizid][bizDeliverText], E_STREAMER_Y, BizData[bizid][bizDeliver][1]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, BizData[bizid][bizDeliverText], E_STREAMER_Z, BizData[bizid][bizDeliver][2]);

			UpdateDynamic3DTextLabelText(BizData[bizid][bizDeliverText], COLOR_SERVER, sprintf("%s\nDelivery Point", BizData[bizid][bizName]));
		}
		if (BizData[bizid][bizOwner] == -1)
		{
			format(string, sizeof(string), "[ID: %d]\nType: {C6E2FF}%s\n{FFFFFF}Price: {C6E2FF}$%s\n{FFFFFF}This business for sell\n{FFFF00}/biz buy {FFFFFF}for purchase this business.", bizid, GetBizType(BizData[bizid][bizType]), FormatNumber(BizData[bizid][bizPrice]));
		}
		else
		{
			if(!BizData[bizid][bizSealed])
  				format(string, sizeof(string), "[ID: %d]\n%s{FFFFFF}\nStatus: {C6E2FF}%s{FFFFFF}\nType: {C6E2FF}%s\n"WHITE"Owned by "YELLOW"%s", bizid, BizData[bizid][bizName], (!BizData[bizid][bizLocked]) ? ("{00FF00}Open{FFFFFF}") : ("{FF0000}Closed{FFFFFF}"), GetBizType(BizData[bizid][bizType]), BizData[bizid][bizOwnerName]);
			else
				format(string, sizeof(string), "[ID: %d]\n%s{FFFFFF}\nStatus: {C6E2FF}%s{FFFFFF}\nType: {C6E2FF}%s\n"WHITE"Owned by "YELLOW"%s\n"WHITE"This business is sealed by "RED"authority", bizid, BizData[bizid][bizName], (!BizData[bizid][bizLocked]) ? ("{00FF00}Open{FFFFFF}") : ("{FF0000}Closed{FFFFFF}"), GetBizType(BizData[bizid][bizType]), BizData[bizid][bizOwnerName]);
		}
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, BizData[bizid][bizText], E_STREAMER_X, BizData[bizid][bizExt][0]);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, BizData[bizid][bizText], E_STREAMER_Y, BizData[bizid][bizExt][1]);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, BizData[bizid][bizText], E_STREAMER_Z, BizData[bizid][bizExt][2]);

		Streamer_SetFloatData(STREAMER_TYPE_PICKUP, BizData[bizid][bizPickup], E_STREAMER_X, BizData[bizid][bizExt][0]);
		Streamer_SetFloatData(STREAMER_TYPE_PICKUP, BizData[bizid][bizPickup], E_STREAMER_Y, BizData[bizid][bizExt][1]);
		Streamer_SetFloatData(STREAMER_TYPE_PICKUP, BizData[bizid][bizPickup], E_STREAMER_Z, BizData[bizid][bizExt][2]);

		Streamer_SetFloatData(STREAMER_TYPE_CP, BizData[bizid][bizCP], E_STREAMER_X, BizData[bizid][bizExt][0]);
		Streamer_SetFloatData(STREAMER_TYPE_CP, BizData[bizid][bizCP], E_STREAMER_Y, BizData[bizid][bizExt][1]);
		Streamer_SetFloatData(STREAMER_TYPE_CP, BizData[bizid][bizCP], E_STREAMER_Z, BizData[bizid][bizExt][2]);
		UpdateDynamic3DTextLabelText(BizData[bizid][bizText], COLOR_SERVER, string);

		Streamer_SetPosition(STREAMER_TYPE_MAP_ICON, BizData[bizid][bizIcon], BizData[bizid][bizExt][0], BizData[bizid][bizExt][1], BizData[bizid][bizExt][2]);
	}
	return 1;
}

Business_Nearest(playerid, Float:range = 4.0)
{
	forex(i, MAX_BUSINESS) if(BizData[i][bizExists])
	{
		if(IsPlayerInRangeOfPoint(playerid, range, BizData[i][bizExt][0], BizData[i][bizExt][1], BizData[i][bizExt][2]))
		{
			return i;
		}
	}
	return -1;
}

Business_NearestDeliver(playerid, Float:range = 4.0)
{
	forex(i, MAX_BUSINESS) if(BizData[i][bizExists])
	{
		if(IsPlayerInRangeOfPoint(playerid, range, BizData[i][bizDeliver][0], BizData[i][bizDeliver][1], BizData[i][bizDeliver][2]))
		{
			return i;
		}
	}
	return -1;
}

Business_Delete(bizid)
{
	if(BizData[bizid][bizExists])
	{

		CallLocalFunction("OnBusinessDeleted", "d", bizid);
		new string[64];
		mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `business` WHERE `bizID` = '%d'", BizData[bizid][bizID]);
		mysql_tquery(sqlcon, string);

		if (IsValidDynamic3DTextLabel(BizData[bizid][bizText]))
		    DestroyDynamic3DTextLabel(BizData[bizid][bizText]);

		if (IsValidDynamicPickup(BizData[bizid][bizPickup]))
		    DestroyDynamicPickup(BizData[bizid][bizPickup]);

		if(IsValidDynamicCP(BizData[bizid][bizCP]))
		    DestroyDynamicCP(BizData[bizid][bizCP]);
		   
		if(IsValidDynamicPickup(BizData[bizid][bizDeliverPickup]))
			DestroyDynamicPickup(BizData[bizid][bizDeliverPickup]);

		if(IsValidDynamic3DTextLabel(BizData[bizid][bizDeliverText]))
			DestroyDynamic3DTextLabel(BizData[bizid][bizDeliverText]);

		if(IsValidDynamicPickup(BizData[bizid][bizFuelPickup]))
			DestroyDynamicPickup(BizData[bizid][bizFuelPickup]);

		if(IsValidDynamic3DTextLabel(BizData[bizid][bizFuelText]))
			DestroyDynamic3DTextLabel(BizData[bizid][bizFuelText]);

		if(IsValidDynamicMapIcon(BizData[bizid][bizIcon]))
			DestroyDynamicMapIcon(BizData[bizid][bizIcon]);

		BizData[bizid][bizID] = 0;
		BizData[bizid][bizExists] = false;
		BizData[bizid][bizOwner] = -1;
	}
	return 1;
}

SetProductPrice(playerid)
{
	new bid = PlayerData[playerid][pInBiz], string[712];
	if(!BizData[bid][bizExists])
	    return 0;

	switch(BizData[bid][bizType])
	{
	    case 1:
	    {
	        format(string, sizeof(string), "Product\tPrice\n%s\t$%s\n%s\t$%s\n%s\t$%s",
				ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
	            FormatNumber(BizData[bid][bizProduct][1]),
	            ProductName[bid][2],
	            FormatNumber(BizData[bid][bizProduct][2])
			);
		}
		case 2:
		{
		    format(string, sizeof(string), "Product\tPrice\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s",
                ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
	            FormatNumber(BizData[bid][bizProduct][1]),
	            ProductName[bid][2],
	            FormatNumber(BizData[bid][bizProduct][2]),
	            ProductName[bid][3],
	            FormatNumber(BizData[bid][bizProduct][3]),
	        	ProductName[bid][4],
	            FormatNumber(BizData[bid][bizProduct][4]),
	        	ProductName[bid][5],
	            FormatNumber(BizData[bid][bizProduct][5]),
	        	ProductName[bid][6],
	            FormatNumber(BizData[bid][bizProduct][6]),
	        	ProductName[bid][7],
	            FormatNumber(BizData[bid][bizProduct][7])
			);
		}
		case 3:
		{
		    format(string, sizeof(string), "Product\tPrice\n%s\t$%s\n%s\t$%s",
                ProductName[bid][0],
		        FormatNumber(BizData[bid][bizProduct][0]),
                ProductName[bid][1],
		        FormatNumber(BizData[bid][bizProduct][1]) 
			);
		}
		case 4:
		{
			format(string, sizeof(string), "Product\tPrice\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s",
				ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
				FormatNumber(BizData[bid][bizProduct][1]),
				ProductName[bid][2],
				FormatNumber(BizData[bid][bizProduct][2]),
				ProductName[bid][3],
				FormatNumber(BizData[bid][bizProduct][3])
			);
		}
		case 5: {
			format(string, sizeof(string), "Product\tPrice\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s",
				ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
				FormatNumber(BizData[bid][bizProduct][1]),
				ProductName[bid][2],
				FormatNumber(BizData[bid][bizProduct][2]),
				ProductName[bid][3],
				FormatNumber(BizData[bid][bizProduct][3])
			);
		}
		case 6: {
			format(string, sizeof(string), "Product\tPrice\n%s\t$%s\n%s\t$%s\n%s\t$%s",
				ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
				FormatNumber(BizData[bid][bizProduct][1]),
				ProductName[bid][2],
				FormatNumber(BizData[bid][bizProduct][2])
			);
		}
	}
	ShowPlayerDialog(playerid, DIALOG_BIZPRICE, DIALOG_STYLE_TABLIST_HEADERS, "Set Product Price", string, "Select", "Close");
	return 1;
}

ShowBusinessMenu(playerid)
{
	new bid = PlayerData[playerid][pInBiz], string[712];
	if(!BizData[bid][bizExists])
	    return 0;
	    
	switch(BizData[bid][bizType])
	{
	    case 1:
	    {
	        format(string, sizeof(string), "Product\tPrice\n%s\t$%s\n%s\t$%s\n%s\t$%s",
				ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
	            FormatNumber(BizData[bid][bizProduct][1]),
	            ProductName[bid][2],
	            FormatNumber(BizData[bid][bizProduct][2])
			);
		}
		case 2://anjime
		{
		    format(string, sizeof(string), "Product\tPrice\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s",
                ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
	            FormatNumber(BizData[bid][bizProduct][1]),
	            ProductName[bid][2],
	            FormatNumber(BizData[bid][bizProduct][2]),
	            ProductName[bid][3],
	            FormatNumber(BizData[bid][bizProduct][3]),
	        	ProductName[bid][4],
	            FormatNumber(BizData[bid][bizProduct][4]),
	        	ProductName[bid][5],
	            FormatNumber(BizData[bid][bizProduct][5]),
	        	ProductName[bid][6],
	            FormatNumber(BizData[bid][bizProduct][6]),
	        	ProductName[bid][7],
	            FormatNumber(BizData[bid][bizProduct][7])
			);
		}
		case 3:
		{
		    format(string, sizeof(string), "Product\tPrice\n%s\t$%s\n%s\t$%s",
                ProductName[bid][0],
		        FormatNumber(BizData[bid][bizProduct][0]),
                ProductName[bid][1],
		        FormatNumber(BizData[bid][bizProduct][1])
			);
		}
		case 4:
		{
			format(string, sizeof(string), "Product\tPrice\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s",
				ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
				FormatNumber(BizData[bid][bizProduct][1]),
				ProductName[bid][2],
				FormatNumber(BizData[bid][bizProduct][2]),
				ProductName[bid][3],
				FormatNumber(BizData[bid][bizProduct][3])
			);
		}
		case 5: {
			format(string, sizeof(string), "Product\tPrice\n%s\t$%s\n%s\t$%s\n%s\t$%s\n%s\t$%s",
				ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
				FormatNumber(BizData[bid][bizProduct][1]),
				ProductName[bid][2],
				FormatNumber(BizData[bid][bizProduct][2]),
				ProductName[bid][3],
				FormatNumber(BizData[bid][bizProduct][3])
			);
		}
		case 6: {
			format(string, sizeof(string), "Product\tPrice\n%s\t$%s\n%s\t$%s\n%s\t$%s",
				ProductName[bid][0],
				FormatNumber(BizData[bid][bizProduct][0]),
				ProductName[bid][1],
				FormatNumber(BizData[bid][bizProduct][1]),
				ProductName[bid][2],
				FormatNumber(BizData[bid][bizProduct][2])
			);
		}
	}
	ShowPlayerDialog(playerid, DIALOG_BIZBUY, DIALOG_STYLE_TABLIST_HEADERS, "Business Product", string, "Select", "Close");
	return 1;
}

CMD:biz(playerid, params[])
{
	new
	    type[24],
	    string[128];

	if (sscanf(params, "s[24]S()[128]", type, string))
	{
	    SendSyntaxMessage(playerid, "/biz [name]");
	    SendClientMessage(playerid, COLOR_SERVER, "(Names){FFFFFF} buy, convertfuel, reqstock, menu, lock");
	    return 1;
	}
	if(!strcmp(type, "buy", true))
	{
	    if(Biz_GetCount(playerid) >= CountPlayerBusinessSlot(playerid) && PlayerData[playerid][pAdmin] < 6)
	        return SendErrorMessage(playerid, "Kamu hanya bisa memiliki %d Bisnis!", CountPlayerBusinessSlot(playerid));
	        
		forex(i, MAX_BUSINESS)if(BizData[i][bizExists])
		{
      		if(IsPlayerInRangeOfPoint(playerid, 3.5, BizData[i][bizExt][0], BizData[i][bizExt][1], BizData[i][bizExt][2]))
			{
			    if(BizData[i][bizOwner] != -1)
			        return SendErrorMessage(playerid, "Bisnis ini sudah dimiliki seseorang!");
			        
				if(GetMoney(playerid) < BizData[i][bizPrice])
				    return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang untuk membeli Bisnis ini!");
				    
				BizData[i][bizOwner] = PlayerData[playerid][pID];
                format(BizData[i][bizOwnerName], MAX_PLAYER_NAME, GetName(playerid));
                SendServerMessage(playerid, "Kamu berhasil membeli Business ini seharga {00FF00}$%s", FormatNumber(BizData[i][bizPrice]));
				LogProperty_DCChannel(Str_Format("[%s]\nPROPERTY: %s (%s) [%s] has purchased business (ID: %d), name: %s, price: $%s, type: %s", ReturnDate(), GetName(playerid), GetUsername(playerid), ReturnIP(playerid), i, BizData[i][bizName], FormatNumber(BizData[i][bizPrice]), GetBizType(BizData[i][bizType])));
                GiveMoney(playerid, -BizData[i][bizPrice], "Membeli Business");
                Business_Refresh(i);
                Business_Save(i);

				BizData[i][bizTaxDate] = gettime() + (14 * 86400);
				BizData[i][bizTaxState] = TAX_STATE_COOLDOWN;
				BizData[i][bizTaxPaid] = true;

				notification.Show(playerid, "Property Info", "Property (Business) purchased successfully!", "hud:radar_propertyG");
			}
		}
	}
	else if(!strcmp(type, "convertfuel", true))
	{
		new bid = PlayerData[playerid][pInBiz];
		if(bid == -1)
			return SendErrorMessage(playerid, "You must be inside your own business!");

		if(BizData[bid][bizOwner] != PlayerData[playerid][pID])
			return SendErrorMessage(playerid, "You must be inside your own business!");

		if(BizData[bid][bizType] != 2)
			return SendErrorMessage(playerid, "The business type must be 24/7!");

		if(BizData[bid][bizStock] < 50)
			return SendErrorMessage(playerid, "Harus ada 50 product dalam business-mu!");

		SendClientMessage(playerid, COLOR_SERVER, "(Business) {FFFFFF}50 percent product converted successfully to Fuel stock!");
		BizData[bid][bizStock] -= 50;

		Business_Save(bid);
		CallLocalFunction("OnBusinessRefuel", "d", bid);
	}
	else if(!strcmp(type, "reqstock", true))
	{
		new bid = PlayerData[playerid][pInBiz];
		if(bid == -1)
			return SendErrorMessage(playerid, "You must be inside your own business!");

		if(BizData[bid][bizOwner] != PlayerData[playerid][pID])
			return SendErrorMessage(playerid, "You must be inside your own business!");

		if(!BizData[bid][bizReq])
		{
			BizData[bid][bizReq] = true;
			SendClientMessage(playerid, COLOR_SERVER, "(Business) {FFFFFF}Bisnismu telah meminta pengisian product pada trucker.");
			foreach(new i : Player) if(PlayerData[i][pSpawned] && PlayerData[i][pJob] == JOB_TRUCKER)
			{
				SendClientMessageEx(i, COLOR_SERVER, "(Restock) {FFFFFF}Bisnis %s {FFFFFF}meminta untuk pengisian stok produk | Tipe: {00FFFF}%s", BizData[bid][bizName], GetBizType(BizData[bid][bizType]));
			}
		}
		else
		{
			BizData[bid][bizReq] = false;
			SendClientMessage(playerid, COLOR_SERVER, "(Business) {FFFFFF}Bisnismu tidak lagi meminta pengisian kepada trucker.");
			foreach(new i : Player) if(PlayerData[i][pSpawned] && PlayerData[i][pJob] == JOB_TRUCKER)
			{
				SendClientMessageEx(i, COLOR_SERVER, "(Restock) {FFFFFF}Bisnis "COOL_GREEN"%s "WHITE"tidak lagi meminta untuk pengisian produk.", BizData[bid][bizName]);
			}			
		}
	}
	else if(!strcmp(type, "lock", true))
	{
		new inbiz = PlayerData[playerid][pInBiz];
		new bnear = Business_Nearest(playerid, 3.5);
		if(inbiz == -1)
		{
			if(bnear != -1)
			{
				if(Biz_IsOwner(playerid, bnear))
				{
					BizData[bnear][bizLocked] = (!BizData[bnear][bizLocked]);
					ShowMessage(playerid, sprintf("You have %s ~w~your business.", (BizData[bnear][bizLocked]) ? ("~r~Locked") : ("~g~Unlocked")), 3);
					Business_Refresh(bnear);
					Business_Save(bnear);	

				}
			}
		}
		else
		{
			if(Biz_IsOwner(playerid, inbiz))
			{
				BizData[inbiz][bizLocked] = (!BizData[inbiz][bizLocked]);
				ShowMessage(playerid, sprintf("You have %s ~w~your business.", (BizData[inbiz][bizLocked]) ? ("~r~Locked") : ("~g~Unlocked")), 3);
				Business_Refresh(inbiz);
				Business_Save(inbiz);	
			}
		}
	} 
	else if(!strcmp(type, "menu", true))
	{
		if(PlayerData[playerid][pInBiz] != -1 && GetPlayerInterior(playerid) == BizData[PlayerData[playerid][pInBiz]][bizInterior] && GetPlayerVirtualWorld(playerid) == BizData[PlayerData[playerid][pInBiz]][bizWorld] && Biz_IsOwner(playerid, PlayerData[playerid][pInBiz]))
		{
		    ShowPlayerDialog(playerid, DIALOG_BIZMENU, DIALOG_STYLE_LIST, "Business Menu", "Business Details\nSet Product Name\nSet Product Price\nSet Business Name\nSet Cargo Price\nWithdraw Vault\nDeposit Vault\nSet Product Description", "Select", "Close");
		}
		else
			SendErrorMessage(playerid, "Kamu tidak berada didalam bisnis milikmu!");
	}
	return 1;
}

CMD:buy(playerid, params[])
{
	if(PlayerData[playerid][pInBiz] != -1 && GetPlayerInterior(playerid) == BizData[PlayerData[playerid][pInBiz]][bizInterior] && GetPlayerVirtualWorld(playerid) == BizData[PlayerData[playerid][pInBiz]][bizWorld])
	{
		if(BizData[PlayerData[playerid][pInBiz]][bizOwner] == -1)
			return SendErrorMessage(playerid, "This busines is Closed!");

	    ShowBusinessMenu(playerid);
	}
	return 1;
}

CMD:createbiz(playerid, params[])
{
    new
		type,
	    price[32],
	    id;

    if (PlayerData[playerid][pAdmin] < 7)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ds[32]", type, price))
 	{
	 	SendSyntaxMessage(playerid, "/createbiz [type] [price]");
    	SendClientMessage(playerid, COLOR_SERVER, "(Type){FFFFFF} 1: Fast Food | 2: 24/7 | 3: Clothes | 4: Electronic | 5: Equipment | 6: Mechanic");
    	return 1;
	}
	if (type < 1 || type > 6)
	    return SendErrorMessage(playerid, "Invalid type specified. Types range from 1 to 5.");

	id = Business_Create(playerid, type, strcash(price));

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for businesses.");

	SendServerMessage(playerid, "You have successfully created business ID: %d.", id);
	return 1;
}

CMD:editbiz(playerid, params[])
{
    new
        id,
        type[24],
        string[256];

    if(PlayerData[playerid][pAdmin] < 6)
        return SendErrorMessage(playerid, "You don't have permission to use this command!");

    if(sscanf(params, "ds[24]S()[128]", id, type, string))
    {
        SendSyntaxMessage(playerid, "/editbiz [id] [name]");
        SendClientMessage(playerid, COLOR_SERVER, "(Names){FFFFFF} location, interior, fuelstock, price, stock, deliver, delete, asell");
        return 1;
    }
    if((id < 0 || id >= MAX_BUSINESS))
        return SendErrorMessage(playerid, "You have specified an invalid ID.");

	if(!BizData[id][bizExists])
        return SendErrorMessage(playerid, "You have specified an invalid ID.");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, BizData[id][bizExt][0], BizData[id][bizExt][1], BizData[id][bizExt][2]);
		Business_Save(id);
		Business_Refresh(id);

		SendClientMessageEx(playerid, COLOR_LIGHTRED, "AdmBiz: {FFFFFF}Kamu telah mengubah posisi Business ID: %d", id);
    }
    else if(!strcmp(type, "interior", true))
    {
    	BizData[id][bizInterior] = GetPlayerInterior(playerid);

		GetPlayerPos(playerid, BizData[id][bizInt][0], BizData[id][bizInt][1], BizData[id][bizInt][2]);
		Business_Save(id);
		Business_Refresh(id);

		SendClientMessageEx(playerid, COLOR_LIGHTRED, "AdmBiz: {FFFFFF}Kamu telah mengubah posisi Business ID: %d", id);
    }
    else if(!strcmp(type, "deliver", true))
    {
		if(BizData[id][bizDeliver][0] == 0 && BizData[id][bizDeliver][1] == 0 && BizData[id][bizDeliver][2] == 0)
		{
			BizData[id][bizDeliverPickup] = CreateDynamicPickup(1239, 23, BizData[id][bizDeliver][0], BizData[id][bizDeliver][1], BizData[id][bizDeliver][2], -1, -1);
			BizData[id][bizDeliverText] = CreateDynamic3DTextLabel(sprintf("%s\nDelivery Point", BizData[id][bizName]), COLOR_SERVER, BizData[id][bizDeliver][0], BizData[id][bizDeliver][1], BizData[id][bizDeliver][2], 15.0);
		}
 		GetPlayerPos(playerid, BizData[id][bizDeliver][0], BizData[id][bizDeliver][1], BizData[id][bizDeliver][2]);
		Business_Save(id);
		Business_Refresh(id);

		SendClientMessageEx(playerid, COLOR_LIGHTRED, "AdmBiz: {FFFFFF}Kamu telah mengubah posisi Deliver Point Business ID: %d", id);   	
    }
    else if(!strcmp(type, "price", true))
    {
    	new amount[32];

    	if(sscanf(string, "s[32]", amount))
    		return SendSyntaxMessage(playerid, "/editbiz [id] [price] [new price]");

    	BizData[id][bizPrice] = strcash(amount);
    	SendAdminMessage(COLOR_LIGHTRED, "AdmBiz: %s has set Business ID %d price to $%s", PlayerData[playerid][pUCP], id, FormatNumber(strcash(amount)));
    	Business_Save(id);
    	Business_Refresh(id);
    }
    else if(!strcmp(type, "stock", true))
    {
    	new amount;

    	if(sscanf(string, "d", amount))
    		return SendSyntaxMessage(playerid, "/editbiz [id] [stock] [amount]");

    	BizData[id][bizStock] = amount;
    	SendAdminMessage(COLOR_LIGHTRED, "AdmBiz: %s has set Business ID %d to %d", PlayerData[playerid][pUCP], id, amount);
    	Business_Save(id);
    }
    else if(!strcmp(type, "delete", true))
    {
    	Business_Delete(id);
    	SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: %s has deleted Business ID: %d", PlayerData[playerid][pUCP], id);
    }
    else if(!strcmp(type, "asell", true))
    {
    	BizData[id][bizOwner] = -1;
		BizData[id][bizSealed] = 0;
		
    	Business_Refresh(id);
    	Business_Save(id);
    	SendAdminMessage(COLOR_LIGHTRED, "AdmCmd: Business %d has aselled by %s", id, PlayerData[playerid][pUCP]);
    }
    return 1;
}

function OnBusinessQueue(playerid) {
	if(cache_num_rows()) {
		for(new i = 0; i < cache_num_rows(); i++) {
			new biz_id, message[144];

			cache_get_value_name(i, "Message", message);
			cache_get_value_name_int(i, "bizID", biz_id);
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Business) "WHITE"%s", biz_id, message);

		}
	}
	mysql_tquery(sqlcon, sprintf("DELETE FROM `business_queue` WHERE `Username` = '%s'", GetName(playerid)));

	return 1;
}
task OnBusinessAsellCheck[3600000]() {
	for(new i = 0; i < MAX_BUSINESS; i++) if(BizData[i][bizExists] && BizData[i][bizLastLogin] != 0) {
		if(BizData[i][bizLastLogin] < gettime()) {
			SendAdminMessage(X11_TOMATO, "BusinessWarn: Business %d (%s) has been automatically aselled by the system.", i, BizData[i][bizName]);

			new msge[128];
			format(msge, 128, "Bisnis mu (ID:%d) telah otomatis dijual karena tidak login selama 10 hari.", i);
			mysql_tquery(sqlcon, sprintf("INSERT INTO `business_queue` (`Username`, `bizID`, `Message`) VALUES('%s','%d','%d')", BizData[i][bizOwnerName], i, msge));
			BizData[i][bizLastLogin] = 0;

			BizData[i][bizSealed] = 0;
			BizData[i][bizOwner] = -1;
			format(BizData[i][bizOwnerName], MAX_PLAYER_NAME, "No Owner");

			Business_Save(i);
			Business_Refresh(i);
		}
	}
	return 1;
}//a

task biz_OnTaxUpdate[10000]() {

    for(new i = 0; i < MAX_BUSINESS; i++) if(BizData[i][bizExists] && BizData[i][bizTaxDate] != 0 && BizData[i][bizOwner] != -1) {
        if(BizData[i][bizTaxDate] <= gettime()) {
            if(BizData[i][bizTaxState] == TAX_STATE_COOLDOWN) {
                BizData[i][bizTaxState] = TAX_STATE_DEADLINE;
                BizData[i][bizTaxDate] = gettime() + (3 * 86400);
                BizData[i][bizTaxPaid] = false;
            }
            else {
                // SendAdminMessage(X11_TOMATO, "FlatWarn: Flat ID %d telah di asell karena tidak membayar pajak.", i);

                foreach(new id : Player) if(BizData[i][bizOwner] == PlayerData[id][pID] && IsPlayerSpawned(id)) {
                    SendClientMessageEx(id, X11_LIGHTBLUE, "(Tax) "WHITE"Bisnismu (ID:%d) telah otomatis dijual oleh pemerintah karena tidak membayar pajak.", i);
                    break;
                }

                new string[256], msge[128];
                format(msge, 128, "Bisnis mu (ID:%d) telah otomatis dijual oleh pemerintah karena tidak membayar pajak.", i);

                mysql_format(sqlcon, string, 256, "INSERT INTO `business_queue` (`Username`, `bizID`, `Message`) VALUES('%e','%d','%e')", BizData[i][bizOwnerName], i, msge);
                mysql_tquery(sqlcon,string);
                BizData[i][bizLastLogin] = 0;
            
                BizData[i][bizOwner] = -1;
                format(BizData[i][bizOwnerName], MAX_PLAYER_NAME, "No Owner");

                Business_Save(i);
                Business_Refresh(i);
            }
        }
    }
    return 1;
}

CMD:biztaxinit(playerid, params[]) {
	if(PlayerData[playerid][pAdmin] > 6) {
		for(new i = 0; i < MAX_BUSINESS; i++) if(BizData[i][bizExists] && BizData[i][bizOwner] != 0) {
			BizData[i][bizTaxDate] = gettime() + (14 * 86400);
			BizData[i][bizTaxState] = TAX_STATE_COOLDOWN;
			BizData[i][bizTaxPaid] = true;
		}
	}
	return 1;
}