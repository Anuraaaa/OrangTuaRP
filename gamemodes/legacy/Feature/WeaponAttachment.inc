
enum weaponSettings
{
    Float:Position[6],
    Bone,
    Hidden
}
new WeaponSettings[MAX_PLAYERS][17][weaponSettings], WeaponTick[MAX_PLAYERS], EditingWeapon[MAX_PLAYERS];

function OnWeaponsLoaded(playerid)
{
	new rows, weaponid, index;

	rows = cache_num_rows();

	if(rows)
	{
		for (new i; i < rows; i++)
		{
			cache_get_value_name_int(i, "WeaponID", weaponid);
			index = weaponid - 22;

			cache_get_value_name_float(i, "PosX", WeaponSettings[playerid][index][Position][0]);
			cache_get_value_name_float(i, "PosY", WeaponSettings[playerid][index][Position][1]);
			cache_get_value_name_float(i, "PosZ", WeaponSettings[playerid][index][Position][2]);

			cache_get_value_name_float(i, "RotX", WeaponSettings[playerid][index][Position][3]);
			cache_get_value_name_float(i, "RotY", WeaponSettings[playerid][index][Position][4]);
			cache_get_value_name_float(i, "RotZ", WeaponSettings[playerid][index][Position][5]);

			cache_get_value_name_int(i, "Bone", WeaponSettings[playerid][index][Bone]);
			cache_get_value_name_int(i, "Hidden", WeaponSettings[playerid][index][Hidden]);
		}
	}
	return 1;
}

IsWeaponWearable(weaponid)
    return (weaponid >= 22 && weaponid <= 31);
 
IsWeaponHideable(weaponid)
    return (weaponid >= 22 && weaponid <= 24 || weaponid == 28 || weaponid == 32);

GetWeaponObjectSlot(weaponid)
{
    new objectslot;
 
    switch (weaponid)
    {
        case 22..24: objectslot = 5;
        case 25..27: objectslot = 6;
        case 28, 29, 32: objectslot = 7;
        case 30, 31: objectslot = 8;
    }
    return objectslot;
}
 
 
GetWeaponModel(weaponid) //Will only return the model of wearable weapons (22-38)
{
    new model;
   
    switch(weaponid)
    {
        case 22..29: model = 324 + weaponid;
        case 30: model = 355;
        case 31: model = 356;
        case 32: model = 372;
    }
    return model;
}