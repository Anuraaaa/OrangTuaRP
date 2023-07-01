#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_ACTION))
	{
		static vehicleid;

		if(IsPlayerInAnyVehicle(playerid) && ((vehicleid = GetPlayerVehicleID(playerid)) != INVALID_VEHICLE_ID))
		{
			if(GetVehicleModel(vehicleid) == 509 || GetVehicleModel(vehicleid) == 481 || GetVehicleModel(vehicleid) == 510) {
				new Float:x, Float:y, Float:z;
				GetPlayerPos(playerid, x, y, z);
				SetPlayerPos(playerid, x, y, z);

				ApplyAnimation(playerid, "PED", "BIKE_fall_off", 4.1, 0, 1, 1, 1, 0, 1);
				defer ABH_Clear[2000](playerid);
			}
		}
	}
}

timer ABH_Clear[200](playerid) {

	ClearAnimations(playerid, 1);
	return 1;
}