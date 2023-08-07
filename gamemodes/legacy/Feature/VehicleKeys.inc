#include <YSI_Coding\y_hooks>

#define INVALID_VEHICLE_KEY_ID (-1)
#define PLAYER_MAX_VEHICLE_SHARE_KEYS	(100)

enum E_P_VEHICLE_KEYS
{
	playerID, //Untuk menampung ID SQL Player
	vehicleID, //Untuk menampung ID SQL Vehicle
	vehicleKeyExists, // Untuk menampung kosong atau tidak
	vehicleModel // untuk menampung model kendaraan
};

new VehicleKeyData[MAX_PLAYERS][PLAYER_MAX_VEHICLE_SHARE_KEYS][E_P_VEHICLE_KEYS];

CMD:sharekey(playerid, params[])
{
	new 
		userid, //Nyimpen taget id nya
		vehicleid = GetPlayerVehicleID(playerid), // Nyimpen vehicle id
		count
	;
	if(sscanf(params, "u", userid)) 
		return SendSyntaxMessage(playerid, "/sharekey [playerid/PartOfName]");

	if(userid == playerid)  // Ketika target id nya adalah player id dia , output error
		return SendErrorMessage(playerid, "You can't give or share your own vehicle to yourself!");

    if(!IsPlayerConnected(userid) || !IsPlayerNearPlayer(playerid, userid, 5.0)) // Ketika target tidak deket atau invalid, output error
		return SendErrorMessage(playerid, "The player is disconnected or not near you.");

	if(!IsPlayerInAnyVehicle(playerid)) // Ketika player tidak di dalam kendaraan, output error.
		return SendErrorMessage(playerid, "You're not inside any vehicle!");

	if(Iter_Contains(Vehicle, vehicleid))
	{
		if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER && Vehicle_IsOwner(playerid, vehicleid)) // Jika tipe kendaraannya di milikin player dan dia ownernya
		{
			for(new i = 0; i < PLAYER_MAX_VEHICLE_SHARE_KEYS; i++) // looping untuk mencari slot kunci yang tersedia dari si target
			{	
				if(VehicleKeyData[userid][i][vehicleID] == VehicleData[vehicleid][vID]) // Kalau si target udah punya SQL id di kendaraan udah gak boleh.
					return SendErrorMessage(playerid, "This player already have the key to this vehicle!");
				
				if(VehicleKeyData[userid][i][vehicleKeyExists])
				{
					count++;
				}

				if(count >= PLAYER_MAX_VEHICLE_SHARE_KEYS-1)
					return SendErrorMessage(playerid, "This player's vehicle key slot already full!");

				if(!VehicleKeyData[userid][i][vehicleKeyExists]) // kalau slotnya kosong, di jalanin
				{
					VehicleKeyData[userid][i][vehicleKeyExists] = 1; // isi slotnya dengan kondisi kalau slot ini sudah terisi.
					VehicleKeyData[userid][i][playerID] = PlayerData[userid][pID]; // mengisi variable VehicleKeyData target dengan SQL id si target
					VehicleKeyData[userid][i][vehicleID] = VehicleData[vehicleid][vID]; // mengisi variable VehicleKetDaya vehicleid dengan SQL ID kendaraan si owner
					VehicleKeyData[userid][i][vehicleModel] = VehicleData[vehicleid][vModel];
					CreateVehicleKey(userid, i); // Function untuk jalaninnya untuk ngeinsert ke database (query)
					SendServerMessage(playerid, "You shared your vehicle's key to %s", ReturnName(userid));
					SendServerMessage(userid, "%s shared their vehicle's key to You", ReturnName(playerid));
					break; // Ketika udah ketemu slotnya dan kosong brarti di stop.
				}
			}
		}
	}
	return 1;
}

CMD:removekey(playerid, params[])
{
	new 
		userid,
		vehicleid = GetPlayerVehicleID(playerid),
		count
	;
	if(sscanf(params, "u", userid)) 
		return SendSyntaxMessage(playerid, "/removekey [playerid/PartOfName]");

	if(userid == playerid) 
		return SendErrorMessage(playerid, "You can't remove your own vehicle key from yourself!");

    if(!IsPlayerConnected(userid) || !IsPlayerNearPlayer(playerid, userid, 5.0)) 
		return SendErrorMessage(playerid, "The player is disconnected or not near you.");

	if(!IsPlayerInAnyVehicle(playerid))
		return SendErrorMessage(playerid, "You're not inside any vehicle!");

	if(Iter_Contains(Vehicle, vehicleid))
	{
		if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER && Vehicle_IsOwner(playerid, vehicleid))
		{
			for(new i = 0; i < PLAYER_MAX_VEHICLE_SHARE_KEYS; i++)
			{
				if(VehicleKeyData[userid][i][vehicleKeyExists] && VehicleKeyData[userid][i][vehicleID] == VehicleData[vehicleid][vID])
				{
					VehicleKeyData[userid][i][vehicleKeyExists] = 0;
					VehicleKeyData[userid][i][playerID] = INVALID_VEHICLE_KEY_ID;
					VehicleKeyData[userid][i][vehicleID] = INVALID_VEHICLE_KEY_ID;
					VehicleKeyData[userid][i][vehicleModel] = 0;
					RemoveVehicleKey(userid, vehicleid);
					SendServerMessage(playerid, "You remove your vehicle's key from %s", ReturnName(userid));
					SendServerMessage(userid, "%s remove their vehicle's key from You", ReturnName(playerid));
					break;
				}
				else
				{
					count++;
				}
			}
			if(count >= PLAYER_MAX_VEHICLE_SHARE_KEYS) 
				return SendErrorMessage(playerid, "Player tersebut tidak memiliki kunci kendaraan ini.");
		}
	}
	return 1;
}

CMD:removeallkeys(playerid, params[])
{
	new 
		vehicleid = GetPlayerVehicleID(playerid);

	if(!IsPlayerInAnyVehicle(playerid))
		return SendErrorMessage(playerid, "You're not inside any vehicle!");

	if(Iter_Contains(Vehicle, vehicleid))
	{
		if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER && Vehicle_IsOwner(playerid, vehicleid))
		{
			for(new i = 0; i < PLAYER_MAX_VEHICLE_SHARE_KEYS; i++)
			{
				foreach(new x : Player)
				{
					if(VehicleKeyData[x][i][vehicleKeyExists] && VehicleKeyData[x][i][vehicleID] == VehicleData[vehicleid][vID])
					{	//Ini akan di jalanin ketika ada player yang ingame dengan kunci dan variable yang sama dengan kendaraan , maka akan di reset variable player tsb dan di remove dari db
						VehicleKeyData[x][i][vehicleKeyExists] = 0;
						VehicleKeyData[x][i][playerID] = INVALID_VEHICLE_KEY_ID;
						VehicleKeyData[x][i][vehicleID] = INVALID_VEHICLE_KEY_ID;
						VehicleKeyData[x][i][vehicleModel] = 0;
						RemoveAllVehicleKey(vehicleid);
					}
					else
					{
						RemoveAllVehicleKey(vehicleid);
					}
				}
			}
			SendServerMessage(playerid, "Kamu menghapus semua player yang memiliki kunci kendaraan ini.");
		}
	}
	return 1;
}

CreateVehicleKey(playerid, slot)
{
	new query[255];
	mysql_format(sqlcon, query, sizeof(query), "INSERT INTO `vehiclekeys` (`playerID`, `vehicleID`, `vehicleModel`, `vehicleKeyExists`) VALUES('%d', '%d', '%d', '1')", VehicleKeyData[playerid][slot][playerID], VehicleKeyData[playerid][slot][vehicleID], VehicleKeyData[playerid][slot][vehicleModel]);
	mysql_tquery(sqlcon, query);
	return 1;
}

RemoveVehicleKey(playerid, vehicleid)
{   
	new query[255];
	mysql_format(sqlcon, query, sizeof(query), "DELETE FROM `vehiclekeys` WHERE playerID = '%d' AND vehicleID = '%d'", PlayerData[playerid][pID], VehicleData[vehicleid][vID]);
	mysql_tquery(sqlcon, query);
	return 1;	
}

RemoveAllVehicleKey(vehicleid)
{   
	new query[255];
	mysql_format(sqlcon, query, sizeof(query), "DELETE FROM `vehiclekeys` WHERE vehicleID = '%d'", VehicleData[vehicleid][vID]);
	mysql_tquery(sqlcon, query);
	return 1;	
}

hook OnPlayerConnect(playerid) {

	for(new i = 0; i < PLAYER_MAX_VEHICLE_SHARE_KEYS; i++) {

		VehicleKeyData[playerid][i][vehicleKeyExists] = 0;
		VehicleKeyData[playerid][i][playerID] = INVALID_VEHICLE_KEY_ID;
		VehicleKeyData[playerid][i][vehicleID] = INVALID_VEHICLE_KEY_ID;
		VehicleKeyData[playerid][i][vehicleModel] = 0;
	}
}
hook OnPlayerLogin(playerid)
{
	mysql_tquery(sqlcon, sprintf("SELECT * FROM `vehiclekeys` WHERE `playerID` = '%d' ORDER BY `playerID` DESC LIMIT %d", PlayerData[playerid][pID], PLAYER_MAX_VEHICLE_SHARE_KEYS), "LoadVehicleKey", "d", playerid);
}

function LoadVehicleKey(playerid) {
	static
		rows;

    rows = cache_num_rows();

	for (new i = 0; i != rows; i ++) 
	{
		VehicleKeyData[playerid][i][vehicleKeyExists] = cache_get_field_int(i, "vehicleKeyExists");
		VehicleKeyData[playerid][i][playerID] = cache_get_field_int(i, "playerID");
		VehicleKeyData[playerid][i][vehicleID] = cache_get_field_int(i, "vehicleID");
		VehicleKeyData[playerid][i][vehicleModel] = cache_get_field_int(i, "vehicleModel");
	}
	return 1;
}
Vehicle_IsShared(playerid, vehicleid) {
	for(new i; i < PLAYER_MAX_VEHICLE_SHARE_KEYS; i++) 
	if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER && VehicleKeyData[playerid][i][vehicleID] == VehicleData[vehicleid][vID])
		return 1;

	return 0;
}