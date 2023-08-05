#include <YSI_Coding\y_hooks>

new
	g_Selected_Vehicle_ID[MAX_PLAYERS][MAX_VEHICLES],
	g_Selected_Vehicle_Time[MAX_PLAYERS][MAX_VEHICLES],
	g_ListedVehicle[MAX_PLAYERS][MAX_VEHICLES],
	g_Selected_Vehicle_Model[MAX_PLAYERS][MAX_VEHICLES],
	g_Selected_Vehicle_Price[MAX_PLAYERS][MAX_VEHICLES];


Vehicle_ShowRegistration(showto, vehicleid) {

	if(!IsPlayerConnected(showto))
		return 0;


	new string[512], bool:have_up = false;
	strcat(string, sprintf(""WHITE"Registration: "YELLOW"%09d\n", VehicleData[vehicleid][vID]));
	strcat(string, sprintf(""WHITE"Model: "CYAN"%s\n", GetVehicleName(vehicleid)));
	strcat(string, sprintf(""WHITE"Plate: "GREEN"%s\n", VehicleData[vehicleid][vPlate]));
	strcat(string, sprintf(""WHITE"Insurance: "YELLOW"%d year(s)\n", VehicleData[vehicleid][vInsurance]));
	strcat(string, ""WHITE"Upgrades:\n\n");
	if(VehicleData[vehicleid][vEngineUpgrade]) {
		strcat(string, ""WHITE"- "GREEN"Engine\n");
		have_up = true;
	}
	if(VehicleData[vehicleid][vBodyUpgrade]) {
		strcat(string, ""WHITE"- "GREEN"Body");
		have_up = true;
	}
	if(VehicleData[vehicleid][vOctaneSaver]) {
		strcat(string, ""WHITE"- "GREEN"Octane Saver");
		have_up = true;
	}

	if(!have_up)
		strcat(string, ""WHITE"(No Upgrades)");

	ShowPlayerDialog(showto, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "Vehicle Details", string, "Close", "");
	return 1;
}
Vehicle_ReturnState(veh_state) {
	new str[56];

	new const veh_state_str[][] = {
		"Spawned",
		"Death",
		"Insurance",
		"House Parked",
		"Public Garage",
		"Impounded",
		"Despawned"
	};
	format(str, sizeof(str), "%s", veh_state_str[veh_state]);
	return str;
}

Vehicle_Nearest(playerid, Float:range = 4.5)
{
	new index = -1;
	foreach(new i : Vehicle) if(IsValidVehicle(i) && IsVehicleStreamedIn(i, playerid)) {

		new Float:x, Float:y, Float:z;
		GetVehiclePos(i, x, y, z);
		if(IsPlayerInRangeOfPoint(playerid, range, x, y, z)) {
			index = i;
			break;
		}
	}
	return index;
}

RespawnVehicle(vehicleid)
{
	if(!Iter_Contains(Vehicle, vehicleid))
		return 0;

	SetVehicleToRespawn(vehicleid);
	return 1;
}

Vehicle_SyncText(vehicleid, idx) {


	if(!IsValidDynamicObject(VehicleData[vehicleid][vToy][idx]))
		return 0;

	print("Sync Text called");
	SetDynamicObjectMaterial(VehicleData[vehicleid][vToy][idx], 0, VehicleData[vehicleid][vToyID][idx], "none", "none", RGBAToARGB(ColorList[VehicleData[vehicleid][vToyColor][idx]]));
	SetDynamicObjectMaterialText(VehicleData[vehicleid][vToy][idx], 0, "ANJING", 130, "Arial", VehicleData[vehicleid][vToySize][idx], 1, RGBAToARGB(VehicleData[vehicleid][vToyColor][idx]), 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	return 1;
}
Vehicle_ObjectEdit(playerid, vehicleid, slot, bool:text = false)
{
	if(Iter_Contains(Vehicle, vehicleid))
	{
        if(IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
            DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);

		SetVehicleZAngle(vehicleid, 0.0);
		
        new 
            Float:x,
            Float:y,
            Float:z,
            Float:rx = VehicleObjects[vehicleid][slot][vehObjectPosRX],
            Float:ry = VehicleObjects[vehicleid][slot][vehObjectPosRY],
            Float:rz = VehicleObjects[vehicleid][slot][vehObjectPosRZ]
        ;

        GetVehiclePos(vehicleid, x, y, z);
        VehicleObjects[vehicleid][slot][vehObject] = INVALID_OBJECT_ID;
        VehicleObjects[vehicleid][slot][vehObject] = CreateDynamicObject(VehicleObjects[vehicleid][slot][vehObjectModel], x, y, z, rx, ry, rz);   
        
        PlayerData[playerid][pEditing] = vehicleid;
        PlayerData[playerid][pListitem] = slot;
        PlayerData[playerid][pEditType] = EDIT_VEHICLE;
        if(text) 
        {
            Vehicle_ObjectTextSync(vehicleid, slot);
        }
        EditDynamicObject(playerid, VehicleObjects[vehicleid][slot][vehObject]);
        return 1;
    }
    return 0;
}

function Vehicle_ObjectDB(vehicleid, slot)
{
	if(VehicleObjects[vehicleid][slot][vehObjectExists] == false)
		return 0;

	VehicleObjects[vehicleid][slot][vehObjectID] = cache_insert_id();


	Vehicle_ObjectSave(vehicleid, slot);
	return 1;
}

GetVehObjectNameByModel(model)
{
    new
        name[32];

    for (new i = 0; i < sizeof(BodyWork); i ++) if(BodyWork[i][Model] == model) {
        strcat(name, BodyWork[i][Name]);

        break;
    }
    return name;
}

Vehicle_RemoveObject(vehicleid) {

	for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot++)
	{
		if(IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
			DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);

		VehicleObjects[vehicleid][slot][vehObject] = INVALID_OBJECT_ID;

		VehicleObjects[vehicleid][slot][vehObjectModel] = 0;
		VehicleObjects[vehicleid][slot][vehObjectExists] = false;

		
		VehicleObjects[vehicleid][slot][vehObjectColor] = 1;

		VehicleObjects[vehicleid][slot][vehObjectPosX] = VehicleObjects[vehicleid][slot][vehObjectPosY] = VehicleObjects[vehicleid][slot][vehObjectPosZ] = 0.0;
		VehicleObjects[vehicleid][slot][vehObjectPosRX] = VehicleObjects[vehicleid][slot][vehObjectPosRY] = VehicleObjects[vehicleid][slot][vehObjectPosRZ] = 0.0;
	}
	for(new idx = 0; idx < 3; idx++) {

		for(new i = 0; i < 2; i++) {
			if(IsValidDynamicObject(NeonObject[vehicleid][idx][i])) {
				DestroyDynamicObject(NeonObject[vehicleid][idx][i]);
				NeonObject[vehicleid][idx][i] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
			}
		}
	}
	return 1;
}

Vehicle_Delete(vid, bool:database = false)
{
	if(!Iter_Contains(Vehicle, vid))
		return 0;

	Vehicle_RemoveObject(vid);

	if(VehicleData[vid][vTireLock]) {
		stop VehicleData[vid][vTireLockTimer];

		if(IsValidDynamic3DTextLabel(VehicleData[vid][vTireLockText]))
			DestroyDynamic3DTextLabel(VehicleData[vid][vTireLockText]);
	}

	if(IsValidDynamicObject(VehicleData[vid][vCrateObject])) {
		DestroyDynamicObject(VehicleData[vid][vCrateObject]);
		VehicleData[vid][vCrateObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	}

	if(vehiclecallsign[vid]) {
		if(IsValidDynamic3DTextLabel(vehicle3Dtext[vid]))
			DestroyDynamic3DTextLabel(vehicle3Dtext[vid]);
			
		vehiclecallsign[vid] = 0;
	}

	CallLocalFunction("OnVehicleDeleted", "d", vid);
	
	for(new i = 0; i < MAX_CAR_STORAGE; i++) {
		CarStorage[vid][i][cItemExists] = false;
		CarStorage[vid][i][cItemModel] = 0;
		CarStorage[vid][i][cItemQuantity] = 0;
	}

	if(database) {

		Car_RemoveAllItems(vid);
		mysql_tquery(sqlcon, sprintf("DELETE FROM `crates` WHERE `Vehicle` = '%d'", VehicleData[vid][vID]));
		mysql_tquery(sqlcon, sprintf("DELETE FROM vehicle WHERE vehID = '%d'", VehicleData[vid][vID]));
	}

	if(IsValidVehicle(vid)) {

		DestroyVehicleEx(vid);
	}
	return 1;
}

ShowVehicleAttachmentMenu(playerid, vehicleid) {

	new string[512];
	for (new i = 0; i < MAX_VEHICLE_OBJECT; i++)
	{
		if(VehicleObjects[vehicleid][i][vehObjectExists])
		{
			if(VehicleObjects[vehicleid][i][vehObjectType] == OBJECT_TYPE_BODY) {
				
				format(string, sizeof(string), "%s"WHITE"%d). %s\n", string, i + 1, GetVehObjectNameByModel(VehicleObjects[vehicleid][i][vehObjectModel]), VehicleObjects[vehicleid][i][vehObjectModel]);
			}
			else {
				format(string, sizeof(string), "%s"WHITE"%d). %s\n", string, i + 1, VehicleObjects[vehicleid][i][vehObjectText]);
			}
		}
		else  {
			format(string, sizeof(string), "%s"GREY"Empty slot\n", string);
		}
	}
	ShowPlayerDialog(playerid, DIALOG_MODSHOP, DIALOG_STYLE_LIST, "Vehicle Attachment", string, "Select", "Close");
	return 1;
}
Vehicle_Count(playerid)
{
	new Cache:execute, total = 0;

	execute = mysql_query(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehExtraID`='%d' AND `vehType`='%d';", PlayerData[playerid][pID], VEHICLE_TYPE_PLAYER));

	if(cache_num_rows())
		total = cache_num_rows();

	cache_delete(execute);
	return total;
}

Vehicle_RemoveOwner(vehicleid) {

	if(!Iter_Contains(Vehicle, vehicleid))
		return 0;

	VehicleData[vehicleid][vExtraID] = -1;
	return 1;
}
Vehicle_SetOwner(vehicleid, playerid, bool:extraid_change = false)
{
	if(Iter_Contains(Vehicle, vehicleid))
	{
		VehicleData[vehicleid][vExtraID] = PlayerData[playerid][pID];

		if(extraid_change)
			defer Vehicle_SaveExtraID[2000](vehicleid);
	}
	return 1;
}

timer Vehicle_SaveExtraID[2000](vehicleid) {

	Vehicle_Save(vehicleid, true);
	return 1;
}
Vehicle_Inside(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid);

	if(!Iter_Contains(Vehicle, vehicleid))
		return -1;

	return vehicleid;
}

function Vehicle_OnVehicleCreated(carid)
{
	if(!Iter_Contains(Vehicle, carid))
		return 0;

	VehicleData[carid][vID] = cache_insert_id();
	SetVehicleNumberPlate(carid, VehicleData[carid][vPlate]);
	Vehicle_Save(carid);
	return 1;
}

SetVehicleInterior(vehicleid, interiorid) {

	if(!IsValidVehicle(vehicleid))
		return 0;

	LinkVehicleToInterior(vehicleid, interiorid);
	VehicleData[vehicleid][vInterior] = interiorid;
	return 1;
}
function Vehicle_GetStatus(carid)
{
	if(IsValidVehicle(carid) && Iter_Contains(Vehicle, carid))
	{
		GetVehicleDamageStatus(carid, VehicleData[carid][vDamage][0], VehicleData[carid][vDamage][1], VehicleData[carid][vDamage][2], VehicleData[carid][vDamage][3]);
		GetVehicleHealth(carid, VehicleData[carid][vHealth]);
		VehicleData[carid][vWorld] = GetVehicleVirtualWorld(carid);

		GetVehiclePos(carid, VehicleData[carid][vPos][0], VehicleData[carid][vPos][1], VehicleData[carid][vPos][2]);
		GetVehicleZAngle(carid,VehicleData[carid][vPos][3]);
	}
	return 1;
}

Vehicle_IsOwner(playerid, carid)
{
	if(PlayerData[playerid][pID] == -1)
		return 0;

	if(Vehicle_GetType(carid) != VEHICLE_TYPE_PLAYER && Vehicle_GetType(carid) != VEHICLE_TYPE_RENTAL)
		return 0;

	if(Iter_Contains(Vehicle, carid) && VehicleData[carid][vExtraID] == PlayerData[playerid][pID])
		return 1;

	return 0;
}

Crate_Count(vid)
{
	if(!Iter_Contains(Vehicle, vid))
		return 0;

	new count = 0;
	foreach(new i : Crate) if(CrateData[i][crateVehicle] == VehicleData[vid][vID])
	{
		count++;
	}
	return count;
}

function OnLoadCrate(carid)
{
	new rows = cache_num_rows();
	if(rows)
	{
		for(new i = 0; i < rows; i++)
		{
			new crate_id = Crate_GetFreeID();

			if(crate_id == -1) {
				printf("** Unable to load crate for vehicle %d.", VehicleData[carid][vID]);
				break;
			}

			cache_get_value_name_int(i, "ID", CrateData[crate_id][crateID]);
			cache_get_value_name_int(i, "Vehicle", CrateData[crate_id][crateVehicle]);
			cache_get_value_name_int(i, "Type", CrateData[crate_id][crateType]);

			Iter_Add(Crate, crate_id);

		}
		printf("[CRATE] Loaded %d crate for Vehicle SQLID %d", rows, VehicleData[carid][vID]);
	}
	return 1;
}

Vehicle_SetType(vehicleid, veh_type = VEHICLE_TYPE_ADMIN) {

	if(!Iter_Contains(Vehicle, vehicleid))
		return 0;

	VehicleData[vehicleid][vType] = veh_type;
	return 1;
}

Vehicle_SetState(vehicleid, veh_state = VEHICLE_STATE_SPAWNED) {

	if(!Iter_Contains(Vehicle, vehicleid))
		return 0;

	VehicleData[vehicleid][vState] = veh_state;
	return 1;
}

UnloadRentalVehicle(playerid) {

	if(!IsPlayerSpawned(playerid))
		return 0;

	foreach(new vehicleid : Vehicle) if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_RENTAL && VehicleData[vehicleid][vExtraID] == PlayerData[playerid][pID])
	{
		Vehicle_Save(vehicleid, false);

		defer Vehicle_SafeUnload[2000](vehicleid);
	}
	return 1;
}

UnloadPlayerVehicle(playerid) {

	if(!IsPlayerSpawned(playerid))
		return 0;

	foreach(new vehicleid : Vehicle) if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER && VehicleData[vehicleid][vExtraID] == PlayerData[playerid][pID])
	{
		Vehicle_Save(vehicleid, false);

		new Float:health;
		GetVehicleHealth(vehicleid, health);

		if(IsVehicleUpsideDown(vehicleid) && health <= 800.0) {
			SendAdminMessage(X11_TOMATO, "VehWarn: %s kemungkinan disconnect dari server ketika kendaraan %s miliknya terbalik.", GetName(playerid, false), GetVehicleName(vehicleid));
		}
		defer Vehicle_SafeUnload[2000](vehicleid);
	}
	return 1;
}

timer Vehicle_SafeUnload[2000](vehicleid) {

	if(Iter_Contains(Vehicle, vehicleid)) {

		foreach(new c : Crate) if(CrateData[c][crateVehicle] == VehicleData[vehicleid][vID])
		{
			CrateData[c][crateExists] = false;
			CrateData[c][crateVehicle] = -1;
			CrateData[c][crateType] = 0;

			new next_js = c;

			Iter_SafeRemove(Crate, next_js,c);
		}

		Vehicle_RemoveObject(vehicleid);

		if(VehicleData[vehicleid][vTireLock]) {
			stop VehicleData[vehicleid][vTireLockTimer];

			if(IsValidDynamic3DTextLabel(VehicleData[vehicleid][vTireLockText]))
				DestroyDynamic3DTextLabel(VehicleData[vehicleid][vTireLockText]);
		}

	
		for(new i = 0; i < MAX_CAR_STORAGE; i++) {
			CarStorage[vehicleid][i][cItemExists] = false;
			CarStorage[vehicleid][i][cItemModel] = 0;
			CarStorage[vehicleid][i][cItemQuantity] = 0;
		}

		VehicleData[vehicleid][vExtraID] = -1;
		
		if(IsValidVehicle(vehicleid))
			DestroyVehicleEx(vehicleid);

		printf("[PLAYER_VEH] Unloading player vehicleid %d.", vehicleid);
	}
	return 1;
}
Vehicle_Create(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, siren = 0, database = true, plate[] = "NONE")
{

	new vehicleid = INVALID_VEHICLE_ID;
	if((vehicleid = CreateVehicle(modelid, x, y, z, angle, color1, color2, -1, siren)) != INVALID_VEHICLE_ID) {

		format(VehicleData[vehicleid][vPlate], 16, plate);

		VehicleData[vehicleid][vModel] = modelid;
		VehicleData[vehicleid][vExtraID] = -1;
		VehicleData[vehicleid][vPos][0] = x;
		VehicleData[vehicleid][vPos][1] = y;
		VehicleData[vehicleid][vPos][2] = z;
		VehicleData[vehicleid][vPos][3] = angle;
		VehicleData[vehicleid][vInsurance] = 3;
		VehicleData[vehicleid][vInsuTime] = 0;
		VehicleData[vehicleid][vColor][0] = color1;
		VehicleData[vehicleid][vColor][1] = color2;
		VehicleData[vehicleid][vLocked] = false;
		VehicleData[vehicleid][vInsuranced] = false;
		VehicleData[vehicleid][vFuel] = 10.0;
		VehicleData[vehicleid][vHealth] = 1000.0;
		VehicleData[vehicleid][vDeathTime] = 0;
		VehicleData[vehicleid][vRentTime] = 0;
		VehicleData[vehicleid][vRental] = -1;
		VehicleData[vehicleid][vHouse] = -1;
		VehicleData[vehicleid][vOctaneSaver] = 0;
		VehicleData[vehicleid][vWood] = 0;
		VehicleData[vehicleid][vPizza] = 0;
		VehicleData[vehicleid][vFactionType] = FACTION_NONE;
		VehicleData[vehicleid][vPrice] = 5000;
		VehicleData[vehicleid][vGarage] = -1;
		VehicleData[vehicleid][vLoadedCrate] = 0;
		VehicleData[vehicleid][vHaveCrate] = false;
		VehicleData[vehicleid][vImpound] = 0;
		VehicleData[vehicleid][vImpoundPrice] = 0;
		VehicleData[vehicleid][vNeonColor] = VEHICLE_NEON_NONE;
		VehicleData[vehicleid][vHandbrake] = false;
		VehicleData[vehicleid][vTireLock] = false;
		VehicleData[vehicleid][vPaintjob] = -1;
		VehicleData[vehicleid][vEngineUpgrade] = 0;
		VehicleData[vehicleid][vBodyUpgrade] = 0;
		VehicleData[vehicleid][vGarageID] = -1;
		VehicleData[vehicleid][vNeonStatus] = false;
		VehicleData[vehicleid][vELM] = false;
		
		Vehicle_SetState(vehicleid, VEHICLE_STATE_SPAWNED);
		Vehicle_SetType(vehicleid, VEHICLE_TYPE_ADMIN);

		for(new v = 0; v < 5; v++) {
			VehicleData[vehicleid][vToyID][v] = 0;
		}

		for(new i = 0; i < 3; i++) {
			VehicleData[vehicleid][vAmmo][i] = 0;
			VehicleData[vehicleid][vWeapon][i] = 0;
		}	

		for(new i = 0; i < MAX_CAR_STORAGE; i++) {
	        CarStorage[vehicleid][i][cItemExists] = false;
	        CarStorage[vehicleid][i][cItemModel] = 0;
	        CarStorage[vehicleid][i][cItemQuantity] = 0;
		}
		for(new j = 0; j < 17; j++)
			VehicleData[vehicleid][vMod][j] = 0;

		if(database)
			mysql_tquery(sqlcon, sprintf("INSERT INTO `vehicle` (`vehModel`) VALUES('%d')", VehicleData[vehicleid][vModel]), "Vehicle_OnVehicleCreated", "d", vehicleid);
	
		foreach(new i : Vehicle) if(IsVehicleInRangeOfVehicle(i, vehicleid, 3.0, false) && (Vehicle_GetType(i) == VEHICLE_TYPE_PLAYER || Vehicle_GetType(i) == VEHICLE_TYPE_RENTAL)) {

			if(vehicleid == i)
				continue;

			Vehicle_Save(i);

			mysql_tquery(sqlcon, sprintf("UPDATE `vehicle` SET `vehState` = '%d' WHERE `vehID` = '%d'", VEHICLE_STATE_STUCK, VehicleData[i][vID]));
					
			new v_str[256];
			format(v_str, 256, ""RED"(Vehicle) "YELLOW"Your vehicle "LIGHTBLUE"(%s) "YELLOW"has been despawned due to collide with other vehicle.", GetVehicleName(i));
			NotifyVehicleOwner(i, v_str);
			format(v_str, 256, ""RED"(Vehicle) "YELLOW"Use "LIGHTBLUE"\"/v spawn\" "YELLOW"to spawn vehicle back.");
			NotifyVehicleOwner(i, v_str);

			defer Vehicle_SafeUnload[1000](i);
		}
		CallLocalFunction("OnVehicleCreated", "d", vehicleid);
	}
	return vehicleid;
}

Vehicle_GetFaction(vehicleid) 
	return VehicleData[vehicleid][vFactionType];

SaveVehicleComponent(vehicleid, componentid)
{
	if(IsValidVehicle(vehicleid) && Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER)
	{
		for(new s = 0; s < 20; s++)
		{
			if(componentid == pv_spoiler[s][0])
			{
				VehicleData[vehicleid][vMod][0] = componentid;
			}
		}

		for(new s = 0; s < 3; s++)
		{
			if(componentid == pv_nitro[s][0])
			{
				VehicleData[vehicleid][vMod][1] = componentid;
			}
		}

		for(new s = 0; s < 23; s++)
		{
			if(componentid == pv_fbumper[s][0])
			{
				VehicleData[vehicleid][vMod][2] = componentid;
			}
		}

		for(new s = 0; s < 22; s++)
		{
			if(componentid == pv_rbumper[s][0])
			{
				VehicleData[vehicleid][vMod][3] = componentid;
			}
		}

		for(new s = 0; s < 28; s++)
		{
			if(componentid == pv_exhaust[s][0])
			{
				VehicleData[vehicleid][vMod][4] = componentid;
			}
		}

		for(new s = 0; s < 2; s++)
		{
			if(componentid == pv_bventr[s][0])
			{
				VehicleData[vehicleid][vMod][5] = componentid;
			}
		}

		for(new s = 0; s < 2; s++)
		{
			if(componentid == pv_bventl[s][0])
			{
				VehicleData[vehicleid][vMod][6] = componentid;
			}
		}

		for(new s = 0; s < 4; s++)
		{
			if(componentid == pv_bscoop[s][0])
			{
				VehicleData[vehicleid][vMod][7] = componentid;
			}
		}

		for(new s = 0; s < 17; s++)
		{
			if(componentid == pv_roof[s][0])
			{
				VehicleData[vehicleid][vMod][8] = componentid;
			}
		}

		for(new s = 0; s < 21; s++)
		{
			if(componentid == pv_lskirt[s][0])
			{
				VehicleData[vehicleid][vMod][9] = componentid;
			}
		}

		for(new s = 0; s < 21; s++)
		{
			if(componentid == pv_rskirt[s][0])
			{
				VehicleData[vehicleid][vMod][10] = componentid;
			}
		}

		for(new s = 0; s < 1; s++)
		{
			if(componentid == pv_hydraulics[s][0])
			{
				VehicleData[vehicleid][vMod][11] = componentid;
			}
		}

		for(new s = 0; s < 1; s++)
		{
			if(componentid == pv_base[s][0])
			{
				VehicleData[vehicleid][vMod][12] = componentid;
			}
		}

		for(new s = 0; s < 4; s++)
		{
			if(componentid == pv_rbbars[s][0])
			{
				VehicleData[vehicleid][vMod][13] = componentid;
			}
		}

		for(new s = 0; s < 2; s++)
		{
			if(componentid == pv_fbbars[s][0])
			{
				VehicleData[vehicleid][vMod][14] = componentid;
			}
		}

		for(new s = 0; s < 17; s++)
		{
			if(componentid == pv_wheels[s][0])
			{
				VehicleData[vehicleid][vMod][15] = componentid;
			}
		}

		for(new s = 0; s < 2; s++)
		{
			if(componentid == pv_lights[s][0])
			{
				VehicleData[vehicleid][vMod][16] = componentid;
			}
		}
	}
	return 1;
}

Vehicle_WeaponStorage(playerid, carid)
{
	if(!IsValidVehicle(carid))
		return SendErrorMessage(playerid, "Vehicle no longer valid.");

	if(!GetTrunkStatus(carid))
		return SendErrorMessage(playerid, "Buka trunk terlebih dahulu!");

    static
	    string[264];

	string[0] = 0;

	for (new i = 0; i < 3; i ++)
	{
	    if (22 <= VehicleData[carid][vWeapon][i] <= 38)
	        format(string, sizeof(string), "%s%s - Ammo: %d - Durability: %d\n", string, ReturnWeaponName(VehicleData[carid][vWeapon][i]), VehicleData[carid][vAmmo][i], VehicleData[carid][vDurability][i]);

		else
		    format(string, sizeof(string), "%s%s\n", string, (VehicleData[carid][vWeapon][i]) ? (ReturnWeaponName(VehicleData[carid][vWeapon][i])) : ("Empty Slot"));
	}
	ShowPlayerDialog(playerid, DIALOG_TRUNKWEAPON, DIALOG_STYLE_LIST, "Vehicle Trunk", string, "Select", "Cancel");
	return 1;
}

Vehicle_ShowTrunk(playerid, vehicleid)
{

	if(!GetTrunkStatus(vehicleid))
		return SendErrorMessage(playerid, "Buka trunk terlebih dahulu!");

	new
	    string[512], name[32];

	string[0] = 0;

	for (new i = 0; i != MAX_CAR_STORAGE; i ++)
	{
	    if (!CarStorage[vehicleid][i][cItemExists])//peler
	        format(string, sizeof(string), "%s"GREY"Empty Slot\n", string);

		else {
			strunpack(name, CarStorage[vehicleid][i][cItemName]);

			if (CarStorage[vehicleid][i][cItemQuantity] == 1) {
                format(string, sizeof(string), "%s"WHITE"%s\n", string, name);
			}
			else format(string, sizeof(string), "%s"WHITE"%s (%d)\n", string, name, CarStorage[vehicleid][i][cItemQuantity]);
		}
	}
	strcat(string, "Weapon Storage");

	PlayerData[playerid][pStorageSelect] = 3;
	ShowPlayerDialog(playerid, DIALOG_TRUNK, DIALOG_STYLE_LIST, "Vehicle Storage", string, "Select", "Cancel");
	return 1;
}

function Vehicle_ShowList(playerid) {

	new bool:have = false;

	new str[512];
	strcat(str,  "Model\tPlate\tState\tInsurance\n");
	if(cache_num_rows()) {

		for(new i = 0; i < cache_num_rows(); i++) {

			new model_id, plate[16], veh_state, insu, veh_garage;
			cache_get_value_name_int(i, "vehModel", model_id);
			cache_get_value_name(i, "vehPlate", plate, sizeof(plate));
			cache_get_value_name_int(i, "vehState", veh_state);
			cache_get_value_name_int(i, "vehInsurance", insu);
			cache_get_value_name_int(i, "vehGarage", veh_garage);

			if(veh_garage == -1) 
				strcat(str, sprintf("%s\t%s\t%s\t%d\n", ReturnVehicleModelName(model_id), plate, Vehicle_ReturnState(veh_state), insu));
			else
				strcat(str, sprintf("%s\t%s\t%s (Garage: %d)\t%d\n", ReturnVehicleModelName(model_id), plate, Vehicle_ReturnState(veh_state), Garage_ReturnID(veh_garage), insu));
			
			have = true;
		}
	}
	foreach(new i : Vehicle) if(Vehicle_IsOwner(playerid, i)) {

		if(Vehicle_GetType(i) == VEHICLE_TYPE_RENTAL) 
			strcat(str, sprintf("%s(ID:%d)\t%s\tSpawned\t(-)\n", GetVehicleName(i), i, VehicleData[i][vPlate]));
		else 
			strcat(str, sprintf("%s(ID:%d)\t%s\tSpawned\t%d\n", GetVehicleName(i), i, VehicleData[i][vPlate], VehicleData[i][vInsurance]));

		have = true;
	}
	if(!have)  
		SendErrorMessage(playerid, "Kamu tidak memiliki kendaraan satupun!");

	else ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Vehicle List | %s", ReturnDate()), str, "Close", "");
	return 1;
}

function Vehicle_OnUnimpound(playerid) {
	if(!cache_num_rows()) {
		SendErrorMessage(playerid, "Kendaraanmu tidak ada pada impound lot.");
		return 1;
	}

	new str[512];
	for(new i = 0; i < cache_num_rows(); i++) {
		new sql_id,
			veh_model,
			price;

		cache_get_value_name_int(i, "vehImpoundPrice", price);
		cache_get_value_name_int(i, "vehID", sql_id);
		cache_get_value_name_int(i, "vehModel", veh_model);

		strcat(str, sprintf("%s | Impound Price: $%s\n", ReturnVehicleModelName(veh_model), FormatNumber(price)));

		g_Selected_Vehicle_ID[playerid][i] = sql_id;
		g_Selected_Vehicle_Price[playerid][i] = price;
	}
	ShowPlayerDialog(playerid, DIALOG_UNIMPOUND, DIALOG_STYLE_LIST, "Impounded Vehicles", str, "Select", "Close");
	return 1;
}
function Vehicle_AdminShowList(playerid, targetid) {

	if(!cache_num_rows())
		return SendErrorMessage(playerid, "%s tidak memiliki kendaraan.", GetName(targetid));

	new str[912];
	strcat(str,  "Model\tPlate\tState\tInsurance\n");
	for(new i = 0; i < cache_num_rows(); i++) {

		new model_id, plate[16], veh_state, insu, sqlid, veh_garage;
		cache_get_value_name_int(i, "vehModel", model_id);
		cache_get_value_name(i, "vehPlate", plate, sizeof(plate));
		cache_get_value_name_int(i, "vehID", sqlid);
		cache_get_value_name_int(i, "vehState", veh_state);
		cache_get_value_name_int(i, "vehInsurance", insu);
		cache_get_value_name_int(i, "vehID", sqlid);
		cache_get_value_name_int(i, "vehGarage", veh_garage);

		if(veh_garage == -1) 
			strcat(str, sprintf("%s(SQLID:%d)\t%s\t%s\t%d\n", ReturnVehicleModelName(model_id), sqlid, plate, Vehicle_ReturnState(veh_state), insu));
		else
			strcat(str, sprintf("%s(SQLID:%d)\t%s\t%s (Garage: %d)\t%d\n", ReturnVehicleModelName(model_id), sqlid, plate, Vehicle_ReturnState(veh_state), Garage_ReturnID(veh_garage), insu));
	}
	foreach(new i : Vehicle)  if(IsValidVehicle(i) && Vehicle_IsOwner(targetid, i)) {

		strcat(str, sprintf("%s(ID:%d)\t%s\tSpawned\t%d\n", GetVehicleName(i), i, VehicleData[i][vPlate], VehicleData[i][vInsurance]));
	}
	return ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, sprintf("%s Vehicle List", GetName(targetid)), str, "Close", "");
}

LoadRentalVehicle(playerid) {

	new query[128];
	mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `vehicle` WHERE `vehExtraID` = %d AND `vehState` = %d AND `vehType` = %d ORDER BY `vehID` ASC", PlayerData[playerid][pID], VEHICLE_STATE_SPAWNED, VEHICLE_TYPE_RENTAL);
	mysql_tquery(sqlcon, query, "OnVehicleLoaded", "");

	return 1;

}
LoadPlayerVehicle(playerid)
{
	new query[128];
	mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `vehicle` WHERE `vehExtraID` = %d AND `vehState` = %d AND `vehType` = %d ORDER BY `vehID` ASC", PlayerData[playerid][pID], VEHICLE_STATE_SPAWNED, VEHICLE_TYPE_PLAYER);
	mysql_tquery(sqlcon, query, "OnVehicleLoaded", "");

	return 1;
}

Vehicle_GetOwnerName(vehicleid) {

	new owner[MAX_PLAYER_NAME];
	owner = "Unknown";

	if(Iter_Contains(Vehicle, vehicleid)) {

		foreach(new i : Player) if(Vehicle_IsOwner(i, vehicleid)) {
			format(owner, sizeof(owner), "%s", GetName(i, false));
			break;
		}
	}
	return owner;
}

Vehicle_SyncObject(vehicleid, slot)
{
    if(Iter_Contains(Vehicle, vehicleid))
	{
        new
            model       = VehicleData[vehicleid][vToyID][slot],
            Float:x     = VehicleData[vehicleid][vToyPosX][slot],
            Float:y     = VehicleData[vehicleid][vToyPosY][slot],
            Float:z     = VehicleData[vehicleid][vToyPosZ][slot],
            Float:rx    = VehicleData[vehicleid][vToyRotX][slot],
            Float:ry    = VehicleData[vehicleid][vToyRotY][slot],
            Float:rz    = VehicleData[vehicleid][vToyRotZ][slot],
            Float:vposx,
            Float:vposy,
            Float:vposz
        ;

        if(IsValidDynamicObject(VehicleData[vehicleid][vToy][slot]))
            DestroyDynamicObject(VehicleData[vehicleid][vToy][slot]);

        VehicleData[vehicleid][vToy][slot] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;

        GetVehiclePos(vehicleid, vposx, vposy, vposz);

        VehicleData[vehicleid][vToy][slot] = CreateDynamicObject(model, vposx, vposy, vposz, rx, ry, rz);

		if(VehicleData[vehicleid][vToyType][slot] == VEHICLE_TOY_TEXT) {
			Vehicle_SyncText(vehicleid, slot);
		}

        AttachDynamicObjectToVehicle(VehicleData[vehicleid][vToy][slot], vehicleid, x, y, z, rx, ry, rz);
        return 1;
    }
    return 0;
}

function OnVehicleLoaded() {

	new count = cache_num_rows(), str[156];

	if(count) {

		for(new z = 0; z < count; z++)
		{
		    new i = INVALID_ITERATOR_SLOT, modelid, color[2], Float:pos[4];

			cache_get_value_name_int(z, "vehModel", modelid);
			cache_get_value_name_int(z, "vehColor1", color[0]);
			cache_get_value_name_int(z, "vehColor2", color[1]);
			cache_get_value_name_float(z, "vehX", pos[0]);
			cache_get_value_name_float(z, "vehY", pos[1]);
			cache_get_value_name_float(z, "vehZ", pos[2]);
			cache_get_value_name_float(z, "vehA", pos[3]);

			if((i = CreateVehicle(modelid, pos[0], pos[1], pos[2], pos[3], color[0], color[1], -1, false)) != INVALID_VEHICLE_ID) 
			{

				cache_get_value_name_int(z, "vehID", VehicleData[i][vID]);
				cache_get_value_name_int(z, "vehExtraID", VehicleData[i][vExtraID]);
				cache_get_value_name_int(z, "vehLocked", VehicleData[i][vLocked]);
				cache_get_value_name_float(z, "vehX", VehicleData[i][vPos][0]);
				cache_get_value_name_float(z, "vehY", VehicleData[i][vPos][1]);
				cache_get_value_name_float(z, "vehZ", VehicleData[i][vPos][2]);
				cache_get_value_name_float(z, "vehA", VehicleData[i][vPos][3]);
				cache_get_value_name_float(z, "vehHealth", VehicleData[i][vHealth]);
				cache_get_value_name_int(z, "vehModel", VehicleData[i][vModel]);
				cache_get_value_name_int(z, "vehDamage1", VehicleData[i][vDamage][0]);
				cache_get_value_name_int(z, "vehDamage2", VehicleData[i][vDamage][1]);
				cache_get_value_name_int(z, "vehDamage3", VehicleData[i][vDamage][2]);
				cache_get_value_name_int(z, "vehDamage4", VehicleData[i][vDamage][3]);
				cache_get_value_name_int(z, "vehInterior", VehicleData[i][vInterior]);
				cache_get_value_name_int(z, "vehWorld", VehicleData[i][vWorld]);
				cache_get_value_name_int(z, "vehColor1", VehicleData[i][vColor][0]);
				cache_get_value_name_int(z, "vehColor2", VehicleData[i][vColor][1]);
				cache_get_value_name_float(z, "vehFuel", VehicleData[i][vFuel]);
				cache_get_value_name_int(z, "vehInsurance", VehicleData[i][vInsurance]);
				cache_get_value_name_int(z, "vehInsuTime", VehicleData[i][vInsuTime]);
				cache_get_value_name(z, "vehPlate", VehicleData[i][vPlate]);
				cache_get_value_name_int(z, "vehRental", VehicleData[i][vRental]);
				cache_get_value_name_int(z, "vehRentalTime", VehicleData[i][vRentTime]);
				cache_get_value_name_int(z, "vehInsuranced", VehicleData[i][vInsuranced]);
				cache_get_value_name_int(z, "vehHouse", VehicleData[i][vHouse]);
				cache_get_value_name_int(z, "vehGarage", VehicleData[i][vGarage]);
				cache_get_value_name_int(z, "vehPark", VehicleData[i][vPark]);
				cache_get_value_name_int(z, "vehState", VehicleData[i][vState]);
				cache_get_value_name_int(z, "vehType", VehicleData[i][vType]);
				cache_get_value_name_int(z, "vehPrice", VehicleData[i][vPrice]);

				cache_get_value_name_int(z, "vehWeapon1", VehicleData[i][vWeapon][0]);
				cache_get_value_name_int(z, "vehWeapon2", VehicleData[i][vWeapon][1]);
				cache_get_value_name_int(z, "vehWeapon3", VehicleData[i][vWeapon][2]);
				cache_get_value_name_int(z, "vehAmmo1", VehicleData[i][vAmmo][0]);
				cache_get_value_name_int(z, "vehAmmo2", VehicleData[i][vAmmo][1]);
				cache_get_value_name_int(z, "vehAmmo3", VehicleData[i][vAmmo][2]);
				cache_get_value_name_int(z, "vehDurability1", VehicleData[i][vDurability][0]);
				cache_get_value_name_int(z, "vehDurability2", VehicleData[i][vDurability][1]);
				cache_get_value_name_int(z, "vehDurability3", VehicleData[i][vDurability][2]);
				cache_get_value_name_int(z, "vehHighVelocity1", VehicleData[i][vHighVelocity][0]);
				cache_get_value_name_int(z, "vehHighVelocity2", VehicleData[i][vHighVelocity][1]);
				cache_get_value_name_int(z, "vehHighVelocity3", VehicleData[i][vHighVelocity][2]);

				cache_get_value_name_int(z, "vehImpound", VehicleData[i][vImpound]);
				cache_get_value_name_int(z, "vehImpoundPrice", VehicleData[i][vImpoundPrice]);

				cache_get_value_name_int(z, "vehFactionType", VehicleData[i][vFactionType]);
				cache_get_value_name_int(z, "vehWood", VehicleData[i][vWood]);
				cache_get_value_name_int(z, "mod0", VehicleData[i][vMod][0]);
				cache_get_value_name_int(z, "mod1", VehicleData[i][vMod][1]);
				cache_get_value_name_int(z, "mod2", VehicleData[i][vMod][2]);
				cache_get_value_name_int(z, "mod3", VehicleData[i][vMod][3]);
				cache_get_value_name_int(z, "mod4", VehicleData[i][vMod][4]);
				cache_get_value_name_int(z, "mod5", VehicleData[i][vMod][5]);
				cache_get_value_name_int(z, "mod6", VehicleData[i][vMod][6]);
				cache_get_value_name_int(z, "mod7", VehicleData[i][vMod][7]);
				cache_get_value_name_int(z, "mod8", VehicleData[i][vMod][8]);
				cache_get_value_name_int(z, "mod9", VehicleData[i][vMod][9]);
				cache_get_value_name_int(z, "mod10", VehicleData[i][vMod][10]);
				cache_get_value_name_int(z, "mod11", VehicleData[i][vMod][11]);
				cache_get_value_name_int(z, "mod12", VehicleData[i][vMod][12]);
				cache_get_value_name_int(z, "mod13", VehicleData[i][vMod][13]);
				cache_get_value_name_int(z, "mod14", VehicleData[i][vMod][14]);
				cache_get_value_name_int(z, "mod15", VehicleData[i][vMod][15]);
				cache_get_value_name_int(z, "mod16", VehicleData[i][vMod][16]);

				cache_get_value_name_int(z, "toyid0", VehicleData[i][vToyID][0]);
				cache_get_value_name_int(z, "toyid1", VehicleData[i][vToyID][1]);
				cache_get_value_name_int(z, "toyid2", VehicleData[i][vToyID][2]);
				cache_get_value_name_int(z, "toyid3", VehicleData[i][vToyID][3]);
				cache_get_value_name_int(z, "toyid4", VehicleData[i][vToyID][4]);
				
				cache_get_value_name_float(z, "toyposx0", VehicleData[i][vToyPosX][0]);
				cache_get_value_name_float(z, "toyposy0", VehicleData[i][vToyPosY][0]);
				cache_get_value_name_float(z, "toyposz0", VehicleData[i][vToyPosZ][0]);
				
				cache_get_value_name_float(z, "toyposx1", VehicleData[i][vToyPosX][1]);
				cache_get_value_name_float(z, "toyposy1", VehicleData[i][vToyPosY][1]);
				cache_get_value_name_float(z, "toyposz1", VehicleData[i][vToyPosZ][1]);
				
				cache_get_value_name_float(z, "toyposx2", VehicleData[i][vToyPosX][2]);
				cache_get_value_name_float(z, "toyposy2", VehicleData[i][vToyPosY][2]);
				cache_get_value_name_float(z, "toyposz2", VehicleData[i][vToyPosZ][2]);
				
				cache_get_value_name_float(z, "toyposx3", VehicleData[i][vToyPosX][3]);
				cache_get_value_name_float(z, "toyposy3", VehicleData[i][vToyPosY][3]);
				cache_get_value_name_float(z, "toyposz3", VehicleData[i][vToyPosZ][3]);
				
				cache_get_value_name_float(z, "toyposx4", VehicleData[i][vToyPosX][4]);
				cache_get_value_name_float(z, "toyposy4", VehicleData[i][vToyPosY][4]);
				cache_get_value_name_float(z, "toyposz4", VehicleData[i][vToyPosZ][4]);
				
				cache_get_value_name_float(z, "toyrotx0", VehicleData[i][vToyRotX][0]);
				cache_get_value_name_float(z, "toyroty0", VehicleData[i][vToyRotY][0]);
				cache_get_value_name_float(z, "toyrotz0", VehicleData[i][vToyRotZ][0]);

				cache_get_value_name_float(z, "toyrotx1", VehicleData[i][vToyRotX][1]);
				cache_get_value_name_float(z, "toyroty1", VehicleData[i][vToyRotY][1]);
				cache_get_value_name_float(z, "toyrotz1", VehicleData[i][vToyRotZ][1]);

				cache_get_value_name_float(z, "toyrotx2", VehicleData[i][vToyRotX][2]);
				cache_get_value_name_float(z, "toyroty2", VehicleData[i][vToyRotY][2]);
				cache_get_value_name_float(z, "toyrotz2", VehicleData[i][vToyRotZ][2]);

				cache_get_value_name_float(z, "toyrotx3", VehicleData[i][vToyRotX][3]);
				cache_get_value_name_float(z, "toyroty3", VehicleData[i][vToyRotY][3]);
				cache_get_value_name_float(z, "toyrotz3", VehicleData[i][vToyRotZ][3]);

				cache_get_value_name_float(z, "toyrotx4", VehicleData[i][vToyRotX][4]);
				cache_get_value_name_float(z, "toyroty4", VehicleData[i][vToyRotY][4]);
				cache_get_value_name_float(z, "toyrotz4", VehicleData[i][vToyRotZ][4]);

				cache_get_value_name_int(z, "vehPaintjob", VehicleData[i][vPaintjob]);

				cache_get_value_name_int(z, "vehTireLock", VehicleData[i][vTireLock]);

				cache_get_value_name_int(z, "vehBodyUpgrade", VehicleData[i][vBodyUpgrade]);
				cache_get_value_name_int(z, "vehEngineUpgrade", VehicleData[i][vEngineUpgrade]);

				cache_get_value_name_int(z, "vehNeon", VehicleData[i][vNeonColor]);
				cache_get_value_name_int(z, "vehOctaneSaver", VehicleData[i][vOctaneSaver]);

				mysql_tquery(sqlcon, sprintf("SELECT * FROM `crates` WHERE `Vehicle` = '%d'", VehicleData[i][vID]), "OnLoadCrate", "d", i);

				SetVehicleNumberPlate(i, VehicleData[i][vPlate]);
				SetVehicleVirtualWorld(i, VehicleData[i][vWorld]);
				LinkVehicleToInterior(i, VehicleData[i][vInterior]);

				if(VehicleData[i][vHealth] < 350.0)
					SetVehicleHealth(i, 350.0);
				else
					SetVehicleHealth(i, VehicleData[i][vHealth]);

				UpdateVehicleDamageStatus(i, VehicleData[i][vDamage][0], VehicleData[i][vDamage][1], VehicleData[i][vDamage][2], VehicleData[i][vDamage][3]);
				LockVehicle(i, VehicleData[i][vLocked]);

				VehicleData[i][vKillerID] = INVALID_PLAYER_ID;

				for(new m = 0; m < 17; m++)
				{
					if(VehicleData[i][vMod][m]) AddVehicleComponent(i, VehicleData[i][vMod][m]);
				}

				if(VehicleData[i][vPaintjob] != -1) {
					ChangeVehiclePaintjob(i, VehicleData[i][vPaintjob]);
				}

				if(VehicleData[i][vTireLock])
				{
					if(!IsValidDynamic3DTextLabel(VehicleData[i][vTireLockText]))
						VehicleData[i][vTireLockText] = CreateDynamic3DTextLabel("** Vehicle Tire locked **", -1, VehicleData[i][vPos][0], VehicleData[i][vPos][1], VehicleData[i][vPos][2], 15, INVALID_PLAYER_ID, i, 1);
					
					VehicleData[i][vTireLockTimer] = repeat OnVehicleTireLock[3000](i);
				}

				VehicleData[i][vHandbrake] = false;
				VehicleData[i][vRepair] = false;

				mysql_format(sqlcon, str, sizeof(str), "SELECT * FROM `carstorage` WHERE `ID` = '%d' LIMIT 7", VehicleData[i][vID]);
				mysql_tquery(sqlcon, str, "OnLoadCarStorage", "d", i);

				mysql_tquery(sqlcon, sprintf("SELECT * FROM `vehicle_object` WHERE `vehicle`='%d' ORDER BY `id` DESC LIMIT 5", VehicleData[i][vID]), "Vehicle_ObjectLoad", "d", i);

				foreach(new vehicleid : Vehicle) if(IsVehicleInRangeOfVehicle(vehicleid, i, 3.0, false) && (Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER || Vehicle_GetType(vehicleid) == VEHICLE_TYPE_RENTAL)) {

					if(vehicleid == i)
						continue;

					Vehicle_Save(vehicleid);
					
					mysql_tquery(sqlcon, sprintf("UPDATE `vehicle` SET `vehState` = '%d' WHERE `vehID` = '%d'", VEHICLE_STATE_STUCK, VehicleData[vehicleid][vID]));
							
					new v_str[256];
					format(v_str, 256, ""RED"(Vehicle) "YELLOW"Your vehicle "CYAN"(%s) "YELLOW"has been despawned due to collide with other vehicle.", GetVehicleName(vehicleid));
					NotifyVehicleOwner(vehicleid, v_str);
					format(v_str, 256, ""RED"(Vehicle) "YELLOW"Use "CYAN"\"/v spawn\" "YELLOW"to spawn vehicle back.");
					NotifyVehicleOwner(vehicleid, v_str);

					

					defer Vehicle_SafeUnload[1000](vehicleid);
				}
			}
		}
	}
	return 1;
}

NotifyVehicleOwner(vehicleid, text[], color = -1) { 
	foreach(new i : Player) if(Vehicle_IsOwner(i, vehicleid)) {
		SendClientMessage(i, color, text);
		break;
	}
	return 1;
} 
forward OnLoadCarStorage(carid);
public OnLoadCarStorage(carid)
{
	new rows = cache_num_rows(), str[32];

	if(rows) {

		for(new i = 0; i < rows; i++) {
			CarStorage[carid][i][cItemExists] = true;
			cache_get_value_name_int(i, "itemID", CarStorage[carid][i][cItemID]);
			cache_get_value_name_int(i, "itemModel", CarStorage[carid][i][cItemModel]);
			cache_get_value_name_int(i, "itemQuantity", CarStorage[carid][i][cItemQuantity]);
			
			cache_get_value_name(i, "itemName", str, sizeof(str));
			strpack(CarStorage[carid][i][cItemName], str, 32 char);
		}
	}
	return 1;
}
Vehicle_Save(vehicleid, bool:extraid = false)
{
	if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER || Vehicle_GetType(vehicleid)  ==  VEHICLE_TYPE_RENTAL && IsValidVehicle(vehicleid)) 
	{
		Vehicle_GetStatus(vehicleid);

		if(VehicleData[vehicleid][vState] == VEHICLE_STATE_DEATH) {
			VehicleData[vehicleid][vState] = VEHICLE_STATE_INSURANCE;
			VehicleData[vehicleid][vInsuTime] = gettime() + (1 * 10800);
		}
			
		new cQuery[2756];
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "UPDATE `vehicle` SET ");
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehX`='%f', ", cQuery, VehicleData[vehicleid][vPos][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehY`='%f', ", cQuery, VehicleData[vehicleid][vPos][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehZ`='%f', ", cQuery, VehicleData[vehicleid][vPos][2]+0.1);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehA`='%f', ", cQuery, VehicleData[vehicleid][vPos][3]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehColor1`='%d', ", cQuery, VehicleData[vehicleid][vColor][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehColor2`='%d', ", cQuery, VehicleData[vehicleid][vColor][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehModel`='%d', ", cQuery, VehicleData[vehicleid][vModel]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehHealth`='%f', ", cQuery, VehicleData[vehicleid][vHealth]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehDamage1`='%d', ", cQuery, VehicleData[vehicleid][vDamage][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehDamage2`='%d', ", cQuery, VehicleData[vehicleid][vDamage][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehDamage3`='%d', ", cQuery, VehicleData[vehicleid][vDamage][2]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehDamage4`='%d', ", cQuery, VehicleData[vehicleid][vDamage][3]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehInterior`='%d', ", cQuery, VehicleData[vehicleid][vInterior]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehWorld`='%d', ", cQuery, VehicleData[vehicleid][vWorld]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehFuel`='%f', ", cQuery, VehicleData[vehicleid][vFuel]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehLocked`='%d', ", cQuery, VehicleData[vehicleid][vLocked]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehPlate`='%s', ", cQuery, VehicleData[vehicleid][vPlate]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehRental`='%d', ", cQuery, VehicleData[vehicleid][vRental]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehHouse`='%d', ", cQuery, VehicleData[vehicleid][vHouse]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehGarage`='%d', ", cQuery, VehicleData[vehicleid][vGarage]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehPark`='%d', ", cQuery, VehicleData[vehicleid][vPark]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehWood`='%d', ", cQuery, VehicleData[vehicleid][vWood]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehType`='%d', ", cQuery, VehicleData[vehicleid][vType]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehState`='%d', ", cQuery, VehicleData[vehicleid][vState]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehFactionType`='%d', ", cQuery, VehicleData[vehicleid][vFactionType]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehPrice`='%d', ", cQuery, VehicleData[vehicleid][vPrice]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehBodyUpgrade`='%d', ", cQuery, VehicleData[vehicleid][vBodyUpgrade]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehEngineUpgrade`='%d', ", cQuery, VehicleData[vehicleid][vEngineUpgrade]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehImpound`='%d', ", cQuery, VehicleData[vehicleid][vImpound]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehImpoundPrice`='%d', ", cQuery, VehicleData[vehicleid][vImpoundPrice]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehWeapon1`='%d', ", cQuery, VehicleData[vehicleid][vWeapon][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehWeapon2`='%d', ", cQuery, VehicleData[vehicleid][vWeapon][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehWeapon3`='%d', ", cQuery, VehicleData[vehicleid][vWeapon][2]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehAmmo1`='%d', ", cQuery, VehicleData[vehicleid][vAmmo][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehAmmo2`='%d', ", cQuery, VehicleData[vehicleid][vAmmo][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehAmmo3`='%d', ", cQuery, VehicleData[vehicleid][vAmmo][2]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehDurability1`='%d', ", cQuery, VehicleData[vehicleid][vDurability][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehDurability2`='%d', ", cQuery, VehicleData[vehicleid][vDurability][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehDurability3`='%d', ", cQuery, VehicleData[vehicleid][vDurability][2]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehHighVelocity1`='%d', ", cQuery, VehicleData[vehicleid][vHighVelocity][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehHighVelocity2`='%d', ", cQuery, VehicleData[vehicleid][vHighVelocity][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehHighVelocity3`='%d', ", cQuery, VehicleData[vehicleid][vHighVelocity][2]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehOctaneSaver`='%d', ", cQuery, VehicleData[vehicleid][vOctaneSaver]);

		if(extraid)
			mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehExtraID`='%d', ", cQuery, VehicleData[vehicleid][vExtraID]);

		new tempString[56];
		for(new z = 0; z < 17; z++)
		{
			format(tempString, sizeof(tempString), "mod%d", z);
			mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`%s`='%d', ", cQuery, tempString, VehicleData[vehicleid][vMod][z]);
		}

		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyid0` = '%d', ", cQuery, VehicleData[vehicleid][vToyID][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyid1` = '%d', ", cQuery, VehicleData[vehicleid][vToyID][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyid2` = '%d', ", cQuery, VehicleData[vehicleid][vToyID][2]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyid3` = '%d', ", cQuery, VehicleData[vehicleid][vToyID][3]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyid4` = '%d', ", cQuery, VehicleData[vehicleid][vToyID][4]);

		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposx0` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosX][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposx1` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosX][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposx2` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosX][2]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposx3` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosX][3]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposx4` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosX][4]);

		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposy0` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosY][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposy1` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosY][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposy2` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosY][2]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposy3` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosY][3]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposy4` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosY][4]);

		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposz0` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosZ][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposz1` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosZ][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposz2` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosZ][2]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposz3` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosZ][3]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyposz4` = '%f', ", cQuery, VehicleData[vehicleid][vToyPosZ][4]);

		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyrotx0` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotX][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyrotx1` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotX][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyrotx2` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotX][2]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyrotx3` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotX][3]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyrotx4` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotX][4]);

		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyroty0` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotY][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyroty1` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotY][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyroty2` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotY][2]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyroty3` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotY][3]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyroty4` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotY][4]);

		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyrotz0` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotZ][0]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyrotz1` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotZ][1]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyrotz2` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotZ][2]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyrotz3` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotZ][3]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`toyrotz4` = '%f', ", cQuery, VehicleData[vehicleid][vToyRotZ][4]);
		
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehPaintjob`='%d', ", cQuery, VehicleData[vehicleid][vPaintjob]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehTireLock`='%d', ", cQuery, VehicleData[vehicleid][vTireLock]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehRentalTime`='%d', ", cQuery, VehicleData[vehicleid][vRentTime]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehInsurance`='%d', ", cQuery, VehicleData[vehicleid][vInsurance]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehInsuranced`='%d', ", cQuery, VehicleData[vehicleid][vInsuranced]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehInsuTime`='%d', ", cQuery, VehicleData[vehicleid][vInsuTime]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%s`vehNeon`='%d' ", cQuery, VehicleData[vehicleid][vNeonColor]);
		mysql_format(sqlcon, cQuery, sizeof(cQuery), "%sWHERE `vehID` = '%d' LIMIT 1;", cQuery, VehicleData[vehicleid][vID]);
		mysql_tquery(sqlcon, cQuery);
	}
	return 1;
}

Vehicle_GetFromID(sql_id) {

	new index = -1;
	foreach(new i : Vehicle) if(IsValidVehicle(i) && VehicleData[i][vID] == sql_id) {
		index = i;
		break;
	}
	return index;
}

Vehicle_SetEngineLevel(vehicleid, level) {
	if(Iter_Contains(Vehicle, vehicleid)) {
		VehicleData[vehicleid][vEngineUpgrade] = level;
		SetVehicleHealth(vehicleid, (level + 1) * 1000);
	}
	return 1;
}

Vehicle_SetBodyLevel(vehicleid, level) {
	if(Iter_Contains(Vehicle, vehicleid)) {
		VehicleData[vehicleid][vBodyUpgrade] = level;
	}
	return 1;
}
function EngineStatus(playerid, vehicleid)
{
	if(!GetEngineStatus(vehicleid))
	{
		new Float: f_vHealth;
		GetVehicleHealth(vehicleid, f_vHealth);
		if(f_vHealth < 350.0)
			return SendErrorMessage(playerid, "This vehicle is damaged!");

		if(Vehicle_GetFuel(vehicleid) <= 0)
			return SendErrorMessage(playerid, "There is no fuel on this vehicle!");

		SwitchVehicleEngine(vehicleid, true);
		ShowMessage(playerid, "Engine turned ~g~ON", 3);
		SwitchVehicleLight(vehicleid, true);
	}
	else
	{
		SwitchVehicleEngine(vehicleid, false);
		ShowMessage(playerid, "Engine turned ~r~OFF", 3);
		SwitchVehicleLight(vehicleid, false);
	}//a
	return 1;
}

function Vehicle_TurnOnEngine(playerid) {

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		new vehicleid = GetPlayerVehicleID(playerid);
		new Float: f_vHealth;
		GetVehicleHealth(vehicleid, f_vHealth);
		if(f_vHealth < 350.0)
			return SendErrorMessage(playerid, "This vehicle is damaged!");

		if(Vehicle_GetFuel(vehicleid) <= 0)
			return SendErrorMessage(playerid, "There is no fuel on this vehicle!");

		SwitchVehicleEngine(vehicleid, true);
		ShowMessage(playerid, "Engine turned ~g~ON", 3);
	}
	return 1;
}


IsVehicleSupportsNeonLights(modelid){
	
	modelid -= 400;
	return !(NeonOffsetData[modelid][NeonX] == 0.0 && NeonOffsetData[modelid][NeonY] == 0.0 && NeonOffsetData[modelid][NeonZ] == 0.0);
}

Vehicle_SetNeon(vehicleid, bool:enable = true, color = VEHICLE_NEON_RED, slotid = 0){

	if(!IsValidVehicle(vehicleid)) 
		return 0;
		

	new modelid = GetVehicleModel(vehicleid);

	modelid -= 400;
	
	for(new i = 0; i < 2; i++) {
		if(IsValidDynamicObject(NeonObject[vehicleid][slotid][i])) {
			DestroyDynamicObject(NeonObject[vehicleid][slotid][i]);
			NeonObject[vehicleid][slotid][i] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
		}
	}
	
	if(!enable) 
		return 0;

	NeonObject[vehicleid][slotid][0] = CreateDynamicObject(color,0.0,0.0,0.0,0.0,0.0,0.0, .streamdistance  = 30.0, .drawdistance = 30.0);
	NeonObject[vehicleid][slotid][1] = CreateDynamicObject(color,0.0,0.0,0.0,0.0,0.0,0.0, .streamdistance  = 30.0, .drawdistance = 30.0);
	AttachDynamicObjectToVehicle(NeonObject[vehicleid][slotid][0],vehicleid,NeonOffsetData[modelid][NeonX], NeonOffsetData[modelid][NeonY],NeonOffsetData[modelid][NeonZ],0.0,0.0,0.0);
	AttachDynamicObjectToVehicle(NeonObject[vehicleid][slotid][1],vehicleid,-NeonOffsetData[modelid][NeonX], NeonOffsetData[modelid][NeonY],NeonOffsetData[modelid][NeonZ],0.0,0.0,0.0);
	return 1;
}


timer OnVehicleTireLock[3000](vehicleid) {

	if(!IsValidVehicle(vehicleid)) {
		stop VehicleData[vehicleid][vTireLockTimer];
		return 0;
	}

	new Float:x, Float:y, Float:z, Float:a;

	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, a);

	if(x != VehicleData[vehicleid][vPos][0] && y != VehicleData[vehicleid][vPos][1] && z != VehicleData[vehicleid][vPos][2]) {

		SetVehiclePos(vehicleid, VehicleData[vehicleid][vPos][0],  VehicleData[vehicleid][vPos][1],  VehicleData[vehicleid][vPos][2]);
		SetVehicleZAngle(vehicleid,  VehicleData[vehicleid][vPos][3]);
	}
	return 1;
}

hook OnPlayerDisconnectEx(playerid) {
	UnloadPlayerVehicle(playerid);
	UnloadRentalVehicle(playerid);
}

hook OnVehicleUpdate(playerid, vehicleid) {
	if(VehicleData[vehicleid][vFuel] < 1.0 && IsEngineVehicle(vehicleid) && GetEngineStatus(vehicleid) && GetVehicleSpeed(vehicleid) > 20) {

		new keys, keysa, keysb;
        GetPlayerKeys(playerid, keys, keysa, keysb);
	    if ((keys & (KEY_VEHICLE_FORWARD | KEY_VEHICLE_BACKWARD | KEY_HANDBRAKE)) == KEY_VEHICLE_FORWARD) { // modify the speed only if player is pressing the forward key without the brake or handbrake.
			new random_chance = random(5);

			if(random_chance == 0 || random_chance == 2 || random_chance == 4) {
				SetVehicleSpeed(vehicleid, RandomEx(0, 5));
			}
			else {
				SetVehicleSpeed(vehicleid, GetVehicleSpeed(vehicleid)-5);
			}
        }
	}
}
Car_GetItemID(carid, item[])
{
	if (!Iter_Contains(Vehicle, carid))
	    return 0;

	for (new i = 0; i < MAX_CAR_STORAGE; i ++)
	{
	    if (!CarStorage[carid][i][cItemExists])
	        continue;

		if (!strcmp(CarStorage[carid][i][cItemName], item)) return i;
	}
	return -1;
}

Car_GetFreeID(carid)
{
	if (!Iter_Contains(Vehicle, carid))
	    return 0;

	for (new i = 0; i < MAX_CAR_STORAGE; i ++)
	{
	    if (!CarStorage[carid][i][cItemExists])
	        return i;
	}
	return -1;
}

Car_AddItem(carid, item[], model, quantity = 1, slotid = -1)
{
    if (!Iter_Contains(Vehicle, carid))
	    return 0;

	new
		itemid = Car_GetItemID(carid, item),
		string[256];

	if (itemid == -1)
	{
	    itemid = Car_GetFreeID(carid);

	    if (itemid != -1)
	    {
	        if (slotid != -1)
	            itemid = slotid;

	        CarStorage[carid][itemid][cItemExists] = true;
	        CarStorage[carid][itemid][cItemModel] = model;
	        CarStorage[carid][itemid][cItemQuantity] = quantity;

	        strpack(CarStorage[carid][itemid][cItemName], item, 32 char);

			mysql_format(sqlcon, string, sizeof(string), "INSERT INTO `carstorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`) VALUES('%d', '%s', '%d', '%d')", VehicleData[carid][vID], item, model, quantity);
			mysql_tquery(sqlcon, string, "OnCarStorageAdd", "dd", carid, itemid);

	        return itemid;
		}
		return -1;
	}
	else
	{
	    mysql_format(sqlcon, string, sizeof(string), "UPDATE `carstorage` SET `itemQuantity` = `itemQuantity` + %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, VehicleData[carid][vID], CarStorage[carid][itemid][cItemID]);
	    mysql_tquery(sqlcon, string);

	    CarStorage[carid][itemid][cItemQuantity] += quantity;
	}
	return itemid;
}

Car_RemoveItem(carid, item[], quantity = 1)
{
    if (!Iter_Contains(Vehicle, carid))
	    return 0;

	new
		itemid = Car_GetItemID(carid, item),
		string[128];

	if (itemid != -1)
	{
	    if (CarStorage[carid][itemid][cItemQuantity] > 0)
	    {
	        CarStorage[carid][itemid][cItemQuantity] -= quantity;
		}
		if (quantity == -1 || CarStorage[carid][itemid][cItemQuantity] < 1)
		{
		    CarStorage[carid][itemid][cItemExists] = false;
		    CarStorage[carid][itemid][cItemModel] = 0;
		    CarStorage[carid][itemid][cItemQuantity] = 0;

		    mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `carstorage` WHERE `ID` = '%d' AND `itemID` = '%d'", VehicleData[carid][vID], CarStorage[carid][itemid][cItemID]);
	        mysql_tquery(sqlcon, string);
		}
		else if (quantity != -1 && CarStorage[carid][itemid][cItemQuantity] > 0)
		{
			mysql_format(sqlcon, string, sizeof(string), "UPDATE `carstorage` SET `itemQuantity` = `itemQuantity` - %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, VehicleData[carid][vID], CarStorage[carid][itemid][cItemID]);
            mysql_tquery(sqlcon, string);
		}
		return 1;
	}
	return 0;
}

Car_RemoveAllItems(carid)
{
	static
	    query[64];

	for (new i = 0; i != MAX_CAR_STORAGE; i ++) {
        CarStorage[carid][i][cItemExists] = false;
        CarStorage[carid][i][cItemModel] = 0;
        CarStorage[carid][i][cItemQuantity] = 0;
	}
	mysql_format(sqlcon, query, 64, "DELETE FROM `carstorage` WHERE `ID` = '%d'", VehicleData[carid][vID]);
	mysql_tquery(sqlcon, query);
	return 1;
}

forward OnCarStorageAdd(carid, itemid);
public OnCarStorageAdd(carid, itemid)
{
	CarStorage[carid][itemid][cItemID] = cache_insert_id();
	return 1;
}

function Vehicle_ObjectLoad(vehicleid)
{
	if(cache_num_rows())
	{
		for(new slot = 0; slot != cache_num_rows(); slot++)
        { 
            if(!VehicleObjects[vehicleid][slot][vehObjectExists])
            {
                VehicleObjects[vehicleid][slot][vehObjectExists] = true;

                cache_get_field_content(slot, "text", VehicleObjects[vehicleid][slot][vehObjectText], 32);
                cache_get_field_content(slot, "font", VehicleObjects[vehicleid][slot][vehObjectFont], 32);			

                VehicleObjects[vehicleid][slot][vehObjectID] 		        = cache_get_field_int(slot, "id");
                VehicleObjects[vehicleid][slot][vehObjectVehicleIndex] 		= cache_get_field_int(slot, "vehicle");
                VehicleObjects[vehicleid][slot][vehObjectType] 		    	= cache_get_field_int(slot, "type");
                VehicleObjects[vehicleid][slot][vehObjectModel] 		    = cache_get_field_int(slot, "model");
				VehicleObjects[vehicleid][slot][vehObjectColor]				= cache_get_field_int(slot, "color");

                VehicleObjects[vehicleid][slot][vehObjectFontColor] 	    = cache_get_field_int(slot, "fontcolor");
                VehicleObjects[vehicleid][slot][vehObjectFontSize] 	    	= cache_get_field_int(slot, "fontsize");

                VehicleObjects[vehicleid][slot][vehObjectPosX] 				= cache_get_field_float(slot, "x");
                VehicleObjects[vehicleid][slot][vehObjectPosY] 				= cache_get_field_float(slot, "y");
                VehicleObjects[vehicleid][slot][vehObjectPosZ] 				= cache_get_field_float(slot, "z");

                VehicleObjects[vehicleid][slot][vehObjectPosRX] 		    = cache_get_field_float(slot, "rx");
                VehicleObjects[vehicleid][slot][vehObjectPosRY] 		    = cache_get_field_float(slot, "ry");
                VehicleObjects[vehicleid][slot][vehObjectPosRZ] 		    = cache_get_field_float(slot, "rz");

                Vehicle_AttachObject(vehicleid, slot);
            }
        }
	}
	return 1;
}

Vehicle_ObjectSave(vehicleid, slot)
{
	if(VehicleObjects[vehicleid][slot][vehObjectExists])
    {
        new query[500];

        mysql_format(sqlcon, query, sizeof(query), "UPDATE `vehicle_object` SET `model`='%d', `color`='%d',`type`='%d', `x`='%f',`y`='%f',`z`='%f', `rx`='%f',`ry`='%f',`rz`='%f'",
            VehicleObjects[vehicleid][slot][vehObjectModel],
            VehicleObjects[vehicleid][slot][vehObjectColor],
            VehicleObjects[vehicleid][slot][vehObjectType],
            VehicleObjects[vehicleid][slot][vehObjectPosX], 
            VehicleObjects[vehicleid][slot][vehObjectPosY], 
            VehicleObjects[vehicleid][slot][vehObjectPosZ], 
            VehicleObjects[vehicleid][slot][vehObjectPosRX],
            VehicleObjects[vehicleid][slot][vehObjectPosRY], 
            VehicleObjects[vehicleid][slot][vehObjectPosRZ]
        );

        mysql_format(sqlcon, query, sizeof(query), "%s, `text`='%e',`font`='%e', `fontsize`='%d',`fontcolor`='%d' WHERE `id`='%d' AND `vehicle` = '%d'",
            query, 
            VehicleObjects[vehicleid][slot][vehObjectText], 
            VehicleObjects[vehicleid][slot][vehObjectFont], 
            VehicleObjects[vehicleid][slot][vehObjectFontSize], 
            VehicleObjects[vehicleid][slot][vehObjectFontColor], 
            VehicleObjects[vehicleid][slot][vehObjectID],
			VehicleObjects[vehicleid][slot][vehObjectVehicleIndex]
        );
        
        mysql_tquery(sqlcon, query);
    }
	return 1;
}

Vehicle_ObjectAdd(playerid, vehicleid, model, type)
{
    if(Iter_Contains(Vehicle, vehicleid))
	{

		for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot++)
		{ 
			if(VehicleObjects[vehicleid][slot][vehObjectExists] == false)
			{
				VehicleObjects[vehicleid][slot][vehObjectExists] = true;

				VehicleObjects[vehicleid][slot][vehObjectType] = type;
				VehicleObjects[vehicleid][slot][vehObjectVehicleIndex] = VehicleData[vehicleid][vID];
				VehicleObjects[vehicleid][slot][vehObjectModel] = model;		

				VehicleObjects[vehicleid][slot][vehObjectColor] = 0;

				VehicleObjects[vehicleid][slot][vehObjectPosX] = 0.0;
				VehicleObjects[vehicleid][slot][vehObjectPosY] = 0.0;
				VehicleObjects[vehicleid][slot][vehObjectPosZ] = 0.0;

				VehicleObjects[vehicleid][slot][vehObjectPosRX] = 0.0;
				VehicleObjects[vehicleid][slot][vehObjectPosRY] = 0.0;
				VehicleObjects[vehicleid][slot][vehObjectPosRZ] = 0.0;

				if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_TEXT)
				{
					format(VehicleObjects[vehicleid][slot][vehObjectText], 32, "TEXT");
					format(VehicleObjects[vehicleid][slot][vehObjectFont], 24, "Arial");
					VehicleObjects[vehicleid][slot][vehObjectFontColor] = 1;
					VehicleObjects[vehicleid][slot][vehObjectFontSize] = 24; 
					Vehicle_ObjectUpdate(vehicleid, slot);
					Vehicle_AttachObject(vehicleid, slot);
					Vehicle_ObjectSave(vehicleid, slot);
				}

				if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
					Vehicle_ObjectEdit(playerid, vehicleid, slot);

				mysql_tquery(sqlcon, sprintf("INSERT INTO `vehicle_object` (`vehicle`) VALUES ('%d')", VehicleObjects[vehicleid][slot][vehObjectVehicleIndex]), "Vehicle_ObjectDB", "dd", vehicleid, slot);
				return 1;
			}
		}
	}
	return 0;
}

Vehicle_AttachObject(vehicleid, slot)
{
    if(Iter_Contains(Vehicle, vehicleid))
	{
        new
            model       = VehicleObjects[vehicleid][slot][vehObjectModel],
            Float:x     = VehicleObjects[vehicleid][slot][vehObjectPosX],
            Float:y     = VehicleObjects[vehicleid][slot][vehObjectPosY],
            Float:z     = VehicleObjects[vehicleid][slot][vehObjectPosZ],
            Float:rx    = VehicleObjects[vehicleid][slot][vehObjectPosRX],
            Float:ry    = VehicleObjects[vehicleid][slot][vehObjectPosRY],
            Float:rz    = VehicleObjects[vehicleid][slot][vehObjectPosRZ],
            Float:vposx,
            Float:vposy,
            Float:vposz
        ;

        if(IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
            DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);

        VehicleObjects[vehicleid][slot][vehObject] = INVALID_OBJECT_ID;

        GetVehiclePos(vehicleid, vposx, vposy, vposz);

        VehicleObjects[vehicleid][slot][vehObject] = CreateDynamicObject(model, vposx, vposy, vposz, rx, ry, rz);

        if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
        {
            Vehicle_ObjectColorSync(vehicleid, slot);
        }
        else 
        {
            Vehicle_ObjectTextSync(vehicleid, slot);
        }

        AttachDynamicObjectToVehicle(VehicleObjects[vehicleid][slot][vehObject], vehicleid, x, y, z, rx, ry, rz);
        // printf("Vehicle ID : %d Vehicle ID 2 : %d Slot : %d Real X : %.2f Y: %.2f Z: %.2f RX : %.2f RY : %.2f RZ : %.2f", vehicleid, VehicleData[vehicleid][vehVehicleID], slot, x, y, z, rx, ry, rz);
        Vehicle_ObjectUpdate(vehicleid, slot);
        return 1;
    }
    return 0;
}
Vehicle_ObjectColorSync(vehicleid, slot)
{
    if(Iter_Contains(Vehicle, vehicleid))
	{
        SetDynamicObjectMaterial(VehicleObjects[vehicleid][slot][vehObject], 0, VehicleObjects[vehicleid][slot][vehObjectModel], "none", "none", RGBAToARGB(ColorList[VehicleObjects[vehicleid][slot][vehObjectColor]]));
        Vehicle_ObjectSave(vehicleid, slot);
	    return 1;
    }
    return 0;
}
Vehicle_ObjectTextSync(vehicleid, slot)
{
    if(Iter_Contains(Vehicle, vehicleid))
	{
        SetDynamicObjectMaterialText(VehicleObjects[vehicleid][slot][vehObject], 0, VehicleObjects[vehicleid][slot][vehObjectText], 130, VehicleObjects[vehicleid][slot][vehObjectFont], VehicleObjects[vehicleid][slot][vehObjectFontSize], 1, RGBAToARGB(ColorList[VehicleObjects[vehicleid][slot][vehObjectFontColor]]), 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
        Vehicle_ObjectSave(vehicleid, slot);
        return 1;
    }
    return 0;
}
Vehicle_ObjectUpdate(vehicleid, slot)
{   
	if(Iter_Contains(Vehicle, vehicleid))
	{
        new
            Float:x     = VehicleObjects[vehicleid][slot][vehObjectPosX],
            Float:y     = VehicleObjects[vehicleid][slot][vehObjectPosY],
            Float:z     = VehicleObjects[vehicleid][slot][vehObjectPosZ],
            Float:rx    = VehicleObjects[vehicleid][slot][vehObjectPosRX],
            Float:ry    = VehicleObjects[vehicleid][slot][vehObjectPosRY],
            Float:rz    = VehicleObjects[vehicleid][slot][vehObjectPosRZ]
        ;

        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_X, x);
        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_Y, y);
        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_Z, z);
        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_R_X, rx);
        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_R_Y, ry);
        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_R_Z, rz);
        return 1;
    }
    return 0;
}

Vehicle_ObjectDelete(vehicleid, slot)
{
    if(Iter_Contains(Vehicle, vehicleid))
	{
        if(IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
            DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);

        VehicleObjects[vehicleid][slot ][vehObject] = INVALID_OBJECT_ID;

        VehicleObjects[vehicleid][slot][vehObjectModel] = 0;
        VehicleObjects[vehicleid][slot][vehObjectExists] = false;

        VehicleObjects[vehicleid][slot][vehObjectColor] = 0;


        VehicleObjects[vehicleid][slot][vehObjectPosX] = VehicleObjects[vehicleid][slot][vehObjectPosY] = VehicleObjects[vehicleid][slot][vehObjectPosZ] = 0.0;
        VehicleObjects[vehicleid][slot][vehObjectPosRX] = VehicleObjects[vehicleid][slot][vehObjectPosRY] = VehicleObjects[vehicleid][slot][vehObjectPosRZ] = 0.0;
        mysql_tquery(sqlcon, sprintf("DELETE FROM `vehicle_object` WHERE `id` = '%d'", VehicleObjects[vehicleid][slot][vehObjectID]));
        return 1;
    }
    return 0;
}

function OnSpawnVehicle(playerid, sql_id) {

	new bool:thereis = false;
	if(cache_num_rows()) {

		new Float:x, Float:y, Float:z;
		cache_get_value_name_float(0, "vehX", x);
		cache_get_value_name_float(0, "vehY", y);
		cache_get_value_name_float(0, "vehZ", z);

		foreach(new i : Vehicle) if(IsVehicleInRangeOfPoint3D(i, 3.0,  x, y, z)) {
			thereis  = true;
			break;
		}

		if(thereis) {
			SendErrorMessage(playerid, "Sedang ada kendaraan lain ditempat terakhir kendaraan yang akan kamu spawn.");
		}
		else {
			mysql_tquery(sqlcon, sprintf("UPDATE `vehicle` SET `vehState` = %d WHERE `vehID` = %d", VEHICLE_STATE_SPAWNED, sql_id));

			mysql_tquery(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehID`='%d';", sql_id), "OnVehicleLoaded", "");

			SendServerMessage(playerid, "You have spawned your vehicle back :)");
		}
	}
	return 1;
}

function QueryVehSpawn(playerid) {
	if(cache_num_rows()) {

		new count = 0, string[256];
		for(new i = 0; i < cache_num_rows(); i++) {

			new sql_id, modelid;

			cache_get_value_name_int(i, "vehModel", modelid);
			cache_get_value_name_int(i, "vehID", sql_id);
			g_Selected_Vehicle_ID[playerid][count++] = sql_id;
			strcat(string, sprintf("%d). %s\n", i + 1, ReturnVehicleModelName(modelid)));
		}
		ShowPlayerDialog(playerid, DIALOG_VEHSPAWN, DIALOG_STYLE_LIST, "Despawned Vehicle", string, "Spawn", "Close");
	}
	else {
		SendErrorMessage(playerid, "Tidak ada kendaraanmu yang ter-despawn.");
	}
	return 1;
}