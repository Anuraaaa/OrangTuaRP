#include <YSI_Coding\y_hooks>

new gr_Ammo[MAX_VEHICLES][5],
    gr_Weapon[MAX_VEHICLES][5],
    gr_Durability[MAX_VEHICLES][5],
	gr_HighVelocity[MAX_VEHICLES][5];

hook OnVehicleCreated(vehicleid) {
    for(new i = 0; i < 5; i++) {
        gr_Ammo[vehicleid][i] = 0;
        gr_Weapon[vehicleid][i] = 0;
        gr_Durability[vehicleid][i] = 0;
		gr_HighVelocity[vehicleid][i] = 0;
    }
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {

	if(dialogid == DIALOG_GUNRACK)
	{
	    new vehicleid = PlayerData[playerid][pVehicle];
		if (response)
		{

			new weaponid = GetWeapon(playerid);
			
			if (!gr_Weapon[vehicleid][listitem])
			{
			    if (!GetWeapon(playerid))
			        return SendErrorMessage(playerid, "You aren't holding any weapon.");

	   			gr_Weapon[vehicleid][listitem] = GetWeapon(playerid);
	            gr_Ammo[vehicleid][listitem] = PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]];
				gr_Durability[vehicleid][listitem] = PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]];
				gr_HighVelocity[vehicleid][listitem] = PlayerData[playerid][pHighVelocity][g_aWeaponSlots[weaponid]];

          		ResetWeapon(playerid, gr_Weapon[vehicleid][listitem]);
	            SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s stored a %s into the gunrack.", ReturnName(playerid), ReturnWeaponName(gr_Weapon[vehicleid][listitem]));

	            Gunrack_Show(playerid, vehicleid);

			}
			else
			{

				if(PlayerHasWeapon(playerid, gr_Weapon[vehicleid][listitem]))
				    return SendErrorMessage(playerid, "You already have this weapon.");
				    
				if (PlayerData[playerid][pGuns][g_aWeaponSlots[weaponid]] != 0)
					return SendErrorMessage(playerid, "You already have weapon on the same slot.");

			    GiveWeaponToPlayer(playerid, gr_Weapon[vehicleid][listitem], gr_Ammo[vehicleid][listitem],gr_Durability[vehicleid][listitem], gr_HighVelocity[vehicleid][listitem]);
	            SendNearbyMessage(playerid, 30.0,X11_PLUM, "** %s takes a %s from the gunrack.", ReturnName(playerid), ReturnWeaponName(gr_Weapon[vehicleid][listitem]));

	            gr_Weapon[vehicleid][listitem] = 0;
                gr_Ammo[vehicleid][listitem] = 0;
                gr_Durability[vehicleid][listitem] = 0;
				gr_HighVelocity[vehicleid][listitem] = 0;

	            Gunrack_Show(playerid, vehicleid);
			}
		}
	}
    return Y_HOOKS_CONTINUE_RETURN_1;
}


Gunrack_Show(playerid, carid)
{
	if(!IsValidVehicle(carid))
		return SendErrorMessage(playerid, "Kendaraan tidak lagi valid (tidak didekatmu).");

    static
	    string[264];

	string[0] = 0;

	for (new i = 0; i < 5; i ++)
	{
	    if (22 <= gr_Weapon[carid][i] <= 38)
	        format(string, sizeof(string), "%s%s - Ammo: %d - Durability: %d\n", string, ReturnWeaponName(gr_Weapon[carid][i]), gr_Ammo[carid][i], gr_Durability[carid][i]);

		else
		    format(string, sizeof(string), "%s%s\n", string, (gr_Weapon[carid][i]) ? (ReturnWeaponName(gr_Weapon[carid][i])) : ("Empty Slot"));
	}
	ShowPlayerDialog(playerid, DIALOG_GUNRACK, DIALOG_STYLE_LIST, "Car Gunrack", string, "Select", "Cancel");
	return 1;
}
CMD:gunrack(playerid, params[]) {


    if (GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "You must be a police officer.");

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return SendErrorMessage(playerid, "You must be onfoot first.");


    new vehicleid = Vehicle_Nearest(playerid, 3.5);

    if(!IsDoorVehicle(vehicleid))
        return SendErrorMessage(playerid, "There is no gunrack on this vehicle.");

    if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_FACTION)
        return SendErrorMessage(playerid, "There is no gunrack on this vehicle.");  

    if(VehicleData[vehicleid][vFactionType] != FACTION_POLICE)
        return SendErrorMessage(playerid, "There is no gunrack on this vehicle.");

    if(!PlayerData[playerid][pOnDuty])
        return SendErrorMessage(playerid, "You must faction duty first.");

    Gunrack_Show(playerid, vehicleid);
    PlayerData[playerid][pVehicle] = vehicleid;
    return 1;
}