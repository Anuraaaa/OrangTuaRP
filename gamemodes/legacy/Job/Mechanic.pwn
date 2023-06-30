#include <YSI_Coding\y_hooks>

/* Modification Entity */

new
	g_ListedComponent[MAX_PLAYERS][17];
	
enum E_WHEEL_ENTITY {
	wheelModel,
	wheelName[24]
};

new const g_WheelData[][E_WHEEL_ENTITY] = {

  {1025, "Off road"},
  {1073, "Shadow"},
  {1074, "Mega"},
  {1075, "Rimshine"},
  {1076, "Wires"},
  {1077, "Classic"},
  {1078, "Twist"},
  {1079, "Cutter"},
  {1080,"Switch"},
  {1081, "Grove"},
  {1082, "Import"},
  {1083, "Dollar"},
  {1084, "Trance"},
  {1085, "Atomic"},
  {1096, "Ahab"},
  {1097, "Virtual"},
  {1098, "Access"}
};


/* =================== */

function OnTuneLoad(playerid, idx)
{
    switch (idx)
    {
        case 0:
        {
            new dialog_info[83], part_name[15], partije = 0;

            for (new i, j = cache_num_rows(); i != j; i++)
            {
                cache_get_value_name(i, "part", part_name);

                strcat(dialog_info, part_name);
                strcat(dialog_info, "\n");
				partije++;
            }
			
			if(!partije)
				SendErrorMessage(playerid, "Modifikasi tidak tersedia untuk kendaraan ini.");
			else
            	ShowPlayerDialog(playerid, DIALOG_TUNE, DIALOG_STYLE_LIST, "Available Parts", dialog_info, "Select", "Cancel");
        }
        case 1:
        {
            if (cache_num_rows())
            {
                new dialog_info[83], part_name[14], num_fields;

                cache_get_field_count(num_fields);
			    
                for (new i; i != num_fields; i++)
                {
                    cache_get_value(0, i, part_name);

                    if (!isnull(part_name))
                    {
                        strcat(dialog_info, part_name);
                        strcat(dialog_info, "\n");
                    }
                }
                ShowPlayerDialog(playerid, DIALOG_TUNE, DIALOG_STYLE_LIST, "Available Parts", dialog_info, "Select", "Cancel");
            }
            else SendErrorMessage(playerid, "Kendaraan ini tidak bisa dimodifikasi!");
        }
        case 2:
        {
            static dialog_info[716];
            new componentid, type[22];

            dialog_info = "{FF0000}Component ID\t{FF8000}Type\n";
	        
            for (new i, j = cache_num_rows(); i != j; i++)
            {
                cache_get_value_name_int(i, "componentid", componentid);
                cache_get_value_name(i, "type", type);
	            
                format(dialog_info, sizeof dialog_info, "%s%d\t%s\n", dialog_info, componentid, type);
            }
            ShowPlayerDialog(playerid, DIALOG_TUNE_2, DIALOG_STYLE_TABLIST_HEADERS, "Available Components", dialog_info, "Install", "Back");
        }
    }
	return 1;
}

function TimeRepairTire(playerid, vehicleid)
{
	new nearest = GetNearestVehicle(playerid, 5.0);
	if(nearest != vehicleid)
		return SendErrorMessage(playerid, "The vehicle is no longer valid.");

	SendClientMessage(playerid, COLOR_SERVER, "(Mechanic) {FFFFFF}You've successfully repaired the tires of vehicle!");
	ClearAnimations(playerid, 1);
    PlayerPlaySound(playerid,1133,0.0,0.0,0.0);
	new panels, doors, lights, tires;
    GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, 0);
	VehicleData[vehicleid][vRepair] = false;
	ShowMechanicMenuInfo(playerid);
	return 1;
}

function SprayTimer(playerid)
{
	new vehicleid = PlayerData[playerid][pVehicle];
	new nearest = GetNearestVehicle(playerid, 4.5);
	if(PlayerData[playerid][pSpraying] && CheckPlayerJob(playerid, JOB_MECHANIC))
	{
		if(nearest != PlayerData[playerid][pVehicle])
		{
		    SendServerMessage(playerid, "Kamu gagal mengganti warna kendaraan!");
			PlayerData[playerid][pSpraying] = false;
			KillTimer(PlayerData[playerid][pSprayTime]);
			ResetWeapon(playerid, 41);
			PlayerData[playerid][pColoring] = 0;
			return 1;
		}
	    if(PlayerData[playerid][pColoring] < 15)
	    {
	        PlayerData[playerid][pColoring]++;
			ShowMessage(playerid, sprintf("~g~Spray the (Vehicle) ~y~%d/15", PlayerData[playerid][pColoring]), 1);
	        return 1;
		}
		else if(PlayerData[playerid][pColoring] >= 15)
		{
 		    SendServerMessage(playerid, "Kamu berhasil mengganti warna kendaraan!");
			VehicleData[vehicleid][vColor][0] = PlayerData[playerid][pColor1];
			VehicleData[vehicleid][vColor][1] = PlayerData[playerid][pColor2];
			
			ChangeVehicleColor(vehicleid, PlayerData[playerid][pColor1], PlayerData[playerid][pColor2]);
			ShowMessage(playerid, "Vehicle ~y~Resprayed!", 3);
			PlayerPlaySound(playerid,1133,0.0,0.0,0.0);
			Inventory_Remove(playerid, "Component", 30);
			KillTimer(PlayerData[playerid][pSprayTime]);
			PlayerData[playerid][pSpraying] = false;
			ResetWeapon(playerid, 41);
			PlayerData[playerid][pColoring] = 0;
			SetPlayerArmedWeapon(playerid, 0);
			ShowMechanicMenuInfo(playerid);
			return 1;
		}
	}
	return 1;
}

function TimeRepairBody(playerid, vehicleid)
{
	new nearest = GetNearestVehicle(playerid, 4.0);
	if(nearest != vehicleid)
		return SendErrorMessage(playerid, "The vehicle is no longer valid.");

	SendClientMessage(playerid, COLOR_SERVER, "(Mechanic) {FFFFFF}You've successfully repaired the body of vehicle!");
	TogglePlayerControllable(playerid, 1);
	ClearAnimations(playerid, 1);
    PlayerPlaySound(playerid,1133,0.0,0.0,0.0);
	new panels, doors, lights, tires;
    GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	UpdateVehicleDamageStatus(vehicleid, 0, 0, 0, tires);
    VehicleData[vehicleid][vRepair] = false;
	ShowMechanicMenuInfo(playerid);
	return 1;
}

function TimeRepairEngine(playerid, vehicleid)
{
	new nearest = GetNearestVehicle(playerid, 4.0);
	if(nearest != vehicleid)
		return SendErrorMessage(playerid, "The vehicle is no longer valid.");

	SendClientMessage(playerid, COLOR_SERVER, "(Mechanic) {FFFFFF}You've successfully repaired the engine of vehicle!");
	ClearAnimations(playerid, 1);
	PlayerPlaySound(playerid,1133,0.0,0.0,0.0);
	VehicleData[vehicleid][vRepair] = false;

	SetVehicleHealth(vehicleid, (VehicleData[vehicleid][vEngineUpgrade] + 1) * 1000.0);

	if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_FACTION)
		SetVehicleHealth(vehicleid, 2000.0);
		
	ShowMechanicMenuInfo(playerid);
	return 1;
}

stock GetComponent(playerid)
{
	return Inventory_Count(playerid, "Component");
}

ShowMechanicMenuInfo(playerid) {

	new vehicleid = PlayerData[playerid][pVehicle], ws_id = -1, string[352];

	if(!IsValidVehicle(vehicleid))
		return SendErrorMessage(playerid, "The vehicle is no longer valid.");

	if(GetNearestVehicle(playerid, 5.0) != vehicleid) 
		return SendErrorMessage(playerid, "The vehicle is no longer near you.");

	new Float:health;
	new panels, doors, light, tires;

	GetVehicleHealth(vehicleid, health);
	if(health > 1000.0) health = 1000.0;
	if(health > 0.0) health *= -1;

	GetVehicleDamageStatus(vehicleid, panels, doors, light, tires);
	new cpanels = panels / 1000000;
	new lights = light / 2;
	new pintu;
	if(doors != 0) pintu = 5;
	if(doors == 0) pintu = 0;
	PlayerData[playerid][pMechPrice][0] = floatround(health, floatround_round) / 10 + 100;
	PlayerData[playerid][pMechPrice][1] = cpanels + lights + pintu + 10;

	if((ws_id = Workshop_Nearest(playerid, 20.0)) != -1) {

		if(!Workshop_HaveAccess(playerid, ws_id))
			return SendErrorMessage(playerid, "Kamu tidak memiliki akses workshop ini.");
			
		if(vehicleid == INVALID_VEHICLE_ID)
			return SendErrorMessage(playerid, "You're not in range of any vehicles!");

		if(!GetHoodStatus(vehicleid) && !IsABike(vehicleid))
			return ShowMessage(playerid, "Buka ~y~kap ~w~kendaraan terlebih dahulu!", 3, 1);

		format(string, sizeof(string), "Repair Engine\t\t%d Component\nRepair Body\t\t%d Component\nRepair Tire\t\t15 Component\nChange Color\t\t30 Component\nTune Vehicle\t\t50 Component\nSet Paintjob\t\t30 Component\nInstall Nitro\t\t150 Component\nUninstall Modification\nUpgrade Engine\t350 Component\nUpgrade Body\t\t350 Component\nInstall Neon\t\t200 Component", PlayerData[playerid][pMechPrice][0], PlayerData[playerid][pMechPrice][1]);
		ShowPlayerDialog(playerid, DIALOG_MM, DIALOG_STYLE_LIST, "Vehicle Menu", string, "Select", "Close");
	}
	else {

		if(IsPlayerInDynamicArea(playerid, AreaData[areaMechanic]) || IsPlayerInDynamicArea(playerid, AreaData[areaMechanicBoat])) {

			if(!PlayerData[playerid][pJobduty])
				return SendErrorMessage(playerid, "You must mechanic duty to use this command.");

			if(vehicleid == INVALID_VEHICLE_ID)
				return SendErrorMessage(playerid, "You're not in range of any vehicles!");

			if(!GetHoodStatus(vehicleid) && IsFourWheelVehicle(vehicleid))
				return ShowMessage(playerid, "Buka ~y~kap ~w~kendaraan terlebih dahulu!", 3, 1);

			format(string, sizeof(string), "Repair Engine\t\t%d Component\nRepair Body\t\t%d Component\nRepair Tire\t\t15 Component\nChange Color\t\t30 Component", PlayerData[playerid][pMechPrice][0], PlayerData[playerid][pMechPrice][1]);
			ShowPlayerDialog(playerid, DIALOG_MM, DIALOG_STYLE_LIST, "Vehicle Menu", string, "Select", "Close");
		}
		else {

			new vehicle_tow = INVALID_VEHICLE_ID;

			if((vehicle_tow = IsPlayerNearTowTruck(playerid)) == INVALID_VEHICLE_ID) 
				return SendErrorMessage(playerid, "Kamu tidak berada di workshop, mechanic center atau disekitar towtruck.");

			vehicleid = GetVehicleNearExceptThisVehicle(playerid, vehicle_tow);

			if(vehicleid == INVALID_VEHICLE_ID)
				return SendErrorMessage(playerid, "You're not in range of any vehicles!");

			if(!GetHoodStatus(vehicleid) && IsFourWheelVehicle(vehicleid))
				return ShowMessage(playerid, "Buka ~y~kap ~w~kendaraan terlebih dahulu!", 3, 1);


			format(string, sizeof(string), "Repair Engine\t\t%d Component", PlayerData[playerid][pMechPrice][0]);
			ShowPlayerDialog(playerid, DIALOG_MM, DIALOG_STYLE_LIST, "Vehicle Menu", string, "Select", "Close");

		}
	}
	return 1;
}
function OnExaminingVehicle(playerid) {

	new vehicleid = PlayerData[playerid][pVehicle];

	if(!IsValidVehicle(vehicleid))
		return SendErrorMessage(playerid, "The vehicle that you examine is no longer valid.");

	if(GetNearestVehicle(playerid, 5.0) != vehicleid) 
		return SendErrorMessage(playerid, "The vehicle that you examine is no longer near you.");

	ShowMechanicMenuInfo(playerid);
	return 1;
}
CMD:mech(playerid, params[])
{
	new 
		ws_id = -1,
		vehicleid = INVALID_VEHICLE_ID,
		text[144];

	if(!CheckPlayerJob(playerid, JOB_MECHANIC))
	    return SendErrorMessage(playerid, "You must be a Mechanic!");

	if(isnull(params))
		return SendSyntaxMessage(playerid, "/mech [Names]"), SendClientMessage(playerid, COLOR_SERVER, "Names: {FFFFFF}duty, menu");

	if(!strcmp(params, "menu", true))
	{

		if(IsPlayerInAnyVehicle(playerid))
		    return SendErrorMessage(playerid, "You must exit the vehicle first!");
		    
		if(IsValidLoadingBar(playerid))
		    return SendErrorMessage(playerid, "You can't do this at the moment.");

		vehicleid = GetNearestVehicle(playerid, 4.0);

		if((ws_id = Workshop_Nearest(playerid, 20.0)) != -1) {

			if(!Workshop_HaveAccess(playerid, ws_id))
				return SendErrorMessage(playerid, "Kamu tidak memiliki akses workshop ini.");
				
			if(vehicleid == INVALID_VEHICLE_ID)
				return SendErrorMessage(playerid, "You're not in range of any vehicles!");

			if(!GetHoodStatus(vehicleid) && !IsABike(vehicleid))
				return ShowMessage(playerid, "Buka ~y~kap ~w~kendaraan terlebih dahulu!", 3, 1);

			StartPlayerLoadingBar(playerid, 100, "Examining_vehicle...", 30, "OnExaminingVehicle");

			PlayerData[playerid][pVehicle] = vehicleid;
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Mechanic) "WHITE"Kamu mulai memeriksa kendaraan "YELLOW"%s"WHITE".", GetVehicleName(vehicleid));
			SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Mechanic) "WHITE"Jangan terlalu jauh dari kendaraan atau kamu akan "RED"gagal"WHITE"!");

			if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER || Vehicle_GetType(vehicleid) == VEHICLE_TYPE_RENTAL) {

				format(text, sizeof(text), "(Vehicle) "WHITE"Kendaraan "CYAN"%s "WHITE"milikmu sedang diperiksa oleh mekanik "YELLOW"%s"WHITE".", GetVehicleName(vehicleid), ReturnName(playerid));
				NotifyVehicleOwner(vehicleid, text, X11_LIGHTBLUE);
			}
		}
		else {

			if(IsPlayerInDynamicArea(playerid, AreaData[areaMechanic]) || IsPlayerInDynamicArea(playerid, AreaData[areaMechanicBoat])) {

				if(!PlayerData[playerid][pJobduty])
					return SendErrorMessage(playerid, "You must mechanic duty to use this command.");

				if(vehicleid == INVALID_VEHICLE_ID)
					return SendErrorMessage(playerid, "You're not in range of any vehicles!");

				if(!GetHoodStatus(vehicleid) && IsFourWheelVehicle(vehicleid))
					return ShowMessage(playerid, "Buka ~y~kap ~w~kendaraan terlebih dahulu!", 3, 1);

				PlayerData[playerid][pVehicle] = vehicleid;
				SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Mechanic) "WHITE"Kamu mulai memeriksa kendaraan "YELLOW"%s"WHITE".", GetVehicleName(vehicleid));
				SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Mechanic) "WHITE"Jangan terlalu jauh dari kendaraan atau kamu akan "RED"gagal"WHITE"!");
				StartPlayerLoadingBar(playerid, 100, "Examining_vehicle...", 30, "OnExaminingVehicle");

				if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER || Vehicle_GetType(vehicleid) == VEHICLE_TYPE_RENTAL) {

					format(text, sizeof(text), "(Vehicle) "WHITE"Kendaraan "CYAN"%s "WHITE"milikmu sedang diperiksa oleh mekanik "YELLOW"%s"WHITE".", GetVehicleName(vehicleid), ReturnName(playerid));
					NotifyVehicleOwner(vehicleid, text, X11_LIGHTBLUE);
				}
			}
			else {

				new vehicle_tow = INVALID_VEHICLE_ID;

				if((vehicle_tow = IsPlayerNearTowTruck(playerid)) == INVALID_VEHICLE_ID) 
					return SendErrorMessage(playerid, "Kamu tidak berada di workshop, mechanic center atau disekitar towtruck.");

				vehicleid = GetVehicleNearExceptThisVehicle(playerid, vehicle_tow);

				if(vehicleid == INVALID_VEHICLE_ID)
					return SendErrorMessage(playerid, "You're not in range of any vehicles!");

				if(!GetHoodStatus(vehicleid) && IsFourWheelVehicle(vehicleid))
					return ShowMessage(playerid, "Buka ~y~kap ~w~kendaraan terlebih dahulu!", 3, 1);

				PlayerData[playerid][pVehicle] = vehicleid;	
				SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Mechanic) "WHITE"Kamu mulai memeriksa kendaraan "YELLOW"%s"WHITE".", GetVehicleName(vehicleid));
				SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Mechanic) "WHITE"Jangan terlalu jauh dari kendaraan atau kamu akan "RED"gagal"WHITE"!");
				StartPlayerLoadingBar(playerid, 100, "Examining_vehicle...", 30, "OnExaminingVehicle");

				if(Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER || Vehicle_GetType(vehicleid) == VEHICLE_TYPE_RENTAL) {

					format(text, sizeof(text), "(Vehicle) "WHITE"Kendaraan "CYAN"%s "WHITE"milikmu sedang diperiksa oleh mekanik "YELLOW"%s"WHITE".", GetVehicleName(vehicleid), ReturnName(playerid));
					NotifyVehicleOwner(vehicleid, text, X11_LIGHTBLUE);
				}
			}
		}
	}
	else if(!strcmp(params, "duty", true))
	{
	    if(PlayerData[playerid][pThirst] < 15)
	    	return SendErrorMessage(playerid, "Kamu terlalu lelah untuk bekerja!");

	    if(!PlayerData[playerid][pJobduty])
	    {
			if(!IsPlayerInDynamicArea(playerid, AreaData[areaMechanic]) && !IsPlayerInDynamicArea(playerid, AreaData[areaMechanicBoat]))
				return SendErrorMessage(playerid, "Kamu tidak berada pada area mekanik!");

				
	    	PlayerData[playerid][pJobduty] = true; 
	    	SetPlayerColor(playerid, COLOR_LIGHTGREEN);
	    	SendClientMessage(playerid, COLOR_SERVER, "(Mechanic) {FFFFFF}Kamu sekarang on-duty sebagai "YELLOW"Mechanic "WHITE"kamu akan mendapatkan panggilan dari "YELLOW"143");
	    }
	    else
	    {
	    	PlayerData[playerid][pJobduty] = false;
	    	SetPlayerColor(playerid, COLOR_WHITE);
	    	SendClientMessage(playerid, COLOR_SERVER, "(Mechanic) {FFFFFF}Kamu tidak lagi on-duty sebagai "YELLOW"Mechanic");
	    }
	}
    return 1;

}


hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid) {
	if(areaid == AreaData[areaMechanic] || areaid == AreaData[areaMechanicBoat])
	{
		if(PlayerData[playerid][pJobduty] && (PlayerData[playerid][pJob] == JOB_MECHANIC || PlayerData[playerid][pJob2] == JOB_MECHANIC))
		{
			PlayerData[playerid][pJobduty] = false;
			SetPlayerColor(playerid, COLOR_WHITE);
			SendClientMessage(playerid, COLOR_SERVER, "(Mechanic) {FFFFFF}Kamu tidak lagi on-duty sebagai "YELLOW"Mechanic "WHITE"karena keluar dari area mekanik.");
		}
	}
}