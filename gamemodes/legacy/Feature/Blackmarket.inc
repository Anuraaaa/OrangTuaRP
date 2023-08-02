#include <YSI_Coding\y_hooks>

new STREAMER_TAG_ACTOR:g_actorSchematic,
    STREAMER_TAG_ACTOR:g_actorSchematicHighVelocity,
    STREAMER_TAG_ACTOR:g_actorSeed,
    STREAMER_TAG_ACTOR:g_actorClip,
    STREAMER_TAG_ACTOR:g_actorMaterial,
    Text3D:g_textSchematic,
    Text3D:g_textSchematicHighVelocity,
    Text3D:g_textSeed,
    Text3D:g_textClip,
    Text3D:g_textMaterial,
    Float:g_posSchematic[3],
    Float:g_posSchematicHighVelocity[3],
    Float:g_posSeed[3],
    Float:g_posClip[3],
    Float:g_posMaterial[3];

new Float:pos_schema[][] = {
    {2796.5669,-2395.3843,13.9560,356.6309},
    {-543.6356,-562.3427,25.5234,357.1937},
    {2376.3765,2797.0608,10.8203,271.9779}
};

new Float:pos_schemahigh[][] = {
    {-2251.3259,2371.8286,5.0017,219.9575},
    {1346.1797,-1657.1619,13.5891,87.9641},
    {1232.5825,-992.4854,43.4843,85.8497}
};

new Float:pos_seed[][] = {
    {2440.5476,-1971.3048,13.5469,265.7346},
    {-1073.4191,-1201.6643,129.2188,178.3768},
    {-306.0645,1781.1932,42.7813,180.3981}
};

new Float:pos_clip[][] = {
    {-2514.5222,759.3554,35.1719,273.5806},
    {-100.0894,1127.2766,19.7422,2.9044},
    {2352.9873,-651.5322,128.0547,88.3435}
};

new Float:pos_mats[][] = {
    {825.8713,-639.4835,16.3359,182.1617},
    {2269.4900,65.7605,26.4844,88.5530},
    {-1518.6404,1193.3412,7.1875,276.1466}
};

RandomizeSchematic() {
    new Float:ang, idx = random(3);

    g_posSchematic[0] = pos_schema[idx][0];
    g_posSchematic[1] = pos_schema[idx][1];
    g_posSchematic[2] = pos_schema[idx][2];
    ang = pos_schema[idx][3];


    if(!IsValidDynamicActor(g_actorSchematic)) {
	    g_actorSchematic = CreateDynamicActor(24,g_posSchematic[0], g_posSchematic[1], g_posSchematic[2],ang, _, _, 0, 0, -1, 15.0); //schematic 
    }
    else {
        Streamer_SetItemPos(STREAMER_TYPE_ACTOR, g_actorSchematic, g_posSchematic[0], g_posSchematic[1], g_posSchematic[2]);
        Streamer_SetFloatData(STREAMER_TYPE_ACTOR, g_actorSchematic, E_STREAMER_ROTATION, ang);
    }
    if(!IsValidDynamic3DTextLabel(g_textSchematic))
        g_textSchematic = CreateDynamic3DTextLabel("Schematic\nPress {FFFF00}H {FFFFFF}to interract.", -1,g_posSchematic[0], g_posSchematic[1], g_posSchematic[2], 1.0);
    else
        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, g_textSchematic, g_posSchematic[0], g_posSchematic[1], g_posSchematic[2]);

    return 1;
}

RandomizeSchematicHigh() { 
    new Float:ang, idx = random(3);

    g_posSchematicHighVelocity[0] = pos_schemahigh[idx][0];
    g_posSchematicHighVelocity[1] = pos_schemahigh[idx][1];
    g_posSchematicHighVelocity[2] = pos_schemahigh[idx][2];
    ang = pos_schemahigh[idx][3];

    if(!IsValidDynamicActor(g_actorSchematicHighVelocity)) {
	    g_actorSchematicHighVelocity = CreateDynamicActor(27,g_posSchematicHighVelocity[0], g_posSchematicHighVelocity[1], g_posSchematicHighVelocity[2],ang, _, _, 0, 0, -1, 15.0); //schematic 
    }
    else {
        Streamer_SetItemPos(STREAMER_TYPE_ACTOR, g_actorSchematicHighVelocity, g_posSchematicHighVelocity[0], g_posSchematicHighVelocity[1], g_posSchematicHighVelocity[2]);
        Streamer_SetFloatData(STREAMER_TYPE_ACTOR, g_actorSchematicHighVelocity, E_STREAMER_ROTATION, ang);
    }
    if(!IsValidDynamic3DTextLabel(g_textSchematicHighVelocity))
        g_textSchematicHighVelocity = CreateDynamic3DTextLabel("Schematic High Velocity\nPress {FFFF00}H {FFFFFF}to interract.", -1,g_posSchematicHighVelocity[0], g_posSchematicHighVelocity[1], g_posSchematicHighVelocity[2], 1.0);
    else
        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, g_textSchematicHighVelocity, g_posSchematicHighVelocity[0], g_posSchematicHighVelocity[1], g_posSchematicHighVelocity[2]);

    return 1;
}

RandomizeSeed() {
    new Float:ang, idx = random(3);

    g_posSeed[0] = pos_seed[idx][0];
    g_posSeed[1] = pos_seed[idx][1];
    g_posSeed[2] = pos_seed[idx][2];
    ang = pos_seed[idx][3];

    if(!IsValidDynamicActor(g_actorSeed)) {
	    g_actorSeed = CreateDynamicActor(269,g_posSeed[0], g_posSeed[1], g_posSeed[2],ang, _, _, 0, 0, -1, 15.0); //weed
    }
    else {
        Streamer_SetItemPos(STREAMER_TYPE_ACTOR, g_actorSeed, g_posSeed[0], g_posSeed[1], g_posSeed[2]);
        Streamer_SetFloatData(STREAMER_TYPE_ACTOR, g_actorSeed, E_STREAMER_ROTATION, ang);
    }
    if(!IsValidDynamic3DTextLabel(g_textSeed))
        g_textSeed = CreateDynamic3DTextLabel("Type {FFFF00}/buyweed {FFFFFF}to purchase weed seeds.", -1,g_posSeed[0], g_posSeed[1], g_posSeed[2], 1.0);
    else
        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, g_textSeed, g_posSeed[0], g_posSeed[1], g_posSeed[2]);

    return 1;
}

RandomizeMaterial() {
    new Float:ang, idx = random(3);

    g_posMaterial[0] = pos_mats[idx][0];
    g_posMaterial[1] = pos_mats[idx][1];
    g_posMaterial[2] = pos_mats[idx][2];
    ang = pos_mats[idx][3];

    if(!IsValidDynamicActor(g_actorMaterial)) {
	    g_actorMaterial = CreateDynamicActor(269,g_posMaterial[0], g_posMaterial[1], g_posMaterial[2],ang, _, _, 0, 0, -1, 15.0); //weed
    }
    else {
        Streamer_SetItemPos(STREAMER_TYPE_ACTOR, g_actorMaterial, g_posMaterial[0], g_posMaterial[1], g_posMaterial[2]);
        Streamer_SetFloatData(STREAMER_TYPE_ACTOR, g_actorMaterial, E_STREAMER_ROTATION, ang);
    }
    if(!IsValidDynamic3DTextLabel(g_textMaterial))
        g_textMaterial = CreateDynamic3DTextLabel("Weapon Materials\nPress {FFFF00}H {FFFFFF}to interract.", -1, g_posMaterial[0], g_posMaterial[1], g_posMaterial[2], 1.0);
    else
        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, g_textMaterial, g_posMaterial[0], g_posMaterial[1], g_posMaterial[2]);

    return 1;
}

RandomizeClip() {
    new Float:ang, idx = random(3);

    g_posClip[0] = pos_clip[idx][0];
    g_posClip[1] = pos_clip[idx][1];
    g_posClip[2] = pos_clip[idx][2];
    ang = pos_clip[idx][3];

    if(!IsValidDynamicActor(g_actorClip)) {
	    g_actorClip = CreateDynamicActor(269,g_posClip[0], g_posClip[1], g_posClip[2],ang, _, _, 0, 0, -1, 15.0); //weed
    }
    else {
        Streamer_SetItemPos(STREAMER_TYPE_ACTOR, g_actorClip, g_posClip[0], g_posClip[1], g_posClip[2]);
        Streamer_SetFloatData(STREAMER_TYPE_ACTOR, g_actorClip, E_STREAMER_ROTATION, ang);
    }
    if(!IsValidDynamic3DTextLabel(g_textClip))
        g_textClip = CreateDynamic3DTextLabel("Weapon Clip\nPress {FFFF00}H {FFFFFF}to interract.", -1, g_posClip[0], g_posClip[1], g_posClip[2], 1.0);
    else
        Streamer_SetItemPos(STREAMER_TYPE_3D_TEXT_LABEL, g_textClip, g_posClip[0], g_posClip[1], g_posClip[2]);

    return 1;
}
hook OnGameModeInit() {

    RandomizeClip();
    RandomizeMaterial();
    RandomizeSchematic();
    RandomizeSchematicHigh();
    RandomizeSeed();
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(newkeys & KEY_CTRL_BACK) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0,g_posSchematicHighVelocity[0], g_posSchematicHighVelocity[1], g_posSchematicHighVelocity[2]))
		{
			if(PlayerData[playerid][pLevel] < 3)
				return SendErrorMessage(playerid, "Minimal level 3 untuk melakukan ini!");

			if(GetFactionType(playerid) != FACTION_FAMILY)
				ShowPlayerDialog(playerid, DIALOG_BM_HV_SCHEMATIC, DIALOG_STYLE_LIST, "High Velocity Schematic", "9mm Silenced | Price: $2,300.00\nShotgun | Price: $4,200.00", "Buy", "Close");
			else	
				ShowPlayerDialog(playerid, DIALOG_BM_HV_SCHEMATIC, DIALOG_STYLE_LIST, "High Velocity Schematic", "9mm Silenced | Price: $2,300.00\nShotgun | Price: $4,200.00\nDesert Eagle | Price: $2,900.00\nRifle | Price: $6,100.00\nAK-47 | Price: $14,300.00", "Buy", "Close"); //memek

		}
		if(IsPlayerInRangeOfPoint(playerid, 3.0, g_posSchematic[0], g_posSchematic[1], g_posSchematic[2]))//schematic
		{
			if(PlayerData[playerid][pLevel] < 3)
				return SendErrorMessage(playerid, "Minimal level 3 untuk melakukan ini!");

			if(GetFactionType(playerid) != FACTION_FAMILY)
				ShowPlayerDialog(playerid, DIALOG_BM_SCHEMATIC, DIALOG_STYLE_LIST, "Schematic", "9mm Silenced schematic | Price: $1,700.00\nShotgun schematic | Price: $3,000.00", "Buy", "Close");
			else
				ShowPlayerDialog(playerid, DIALOG_BM_SCHEMATIC, DIALOG_STYLE_LIST, "Schematic", "9mm Silenced schematic | Price: $1,700.00\nShotgun schematic | Price: $3,000.00\nDesert Eagle schematic | Price: $2,000.00\nRifle schematic | Price: $4,600.00\nAK-47 Schematic | Price: $9,800.00", "Buy", "Close");
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.0, g_posClip[0], g_posClip[1], g_posClip[2]))
		{
			if(PlayerData[playerid][pLevel] < 3)
				return SendErrorMessage(playerid, "Minimal level 3 untuk melakukan ini!");

			if(GetFactionType(playerid) != FACTION_FAMILY)
				ShowPlayerDialog(playerid, DIALOG_BM_CLIP, DIALOG_STYLE_LIST, "Gun Clip", "9mm Luger | 17 rounds / 1 Clip | Price: $47.n00\n12 Gauge | 12 rounds / 1 Clip | Price: $69.00", "Buy", "Close");
			else
				ShowPlayerDialog(playerid, DIALOG_BM_CLIP, DIALOG_STYLE_LIST, "Gun Clip", "9mm Luger | Price: $47.00\n12 Gauge | Price: $69.00\n.44 Magnum | Price: $55.00\n7.62mm Caliber | Price: $150.00", "Buy", "Close");
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.0,g_posMaterial[0], g_posMaterial[1], g_posMaterial[2]))
		{
			if(PlayerData[playerid][pLevel] < 3)
				return SendErrorMessage(playerid, "Minimal level 3 untuk melakukan ini!");

			if(GetFactionType(playerid) != FACTION_FAMILY)
				ShowPlayerDialog(playerid, DIALOG_BM_MATERIAL, DIALOG_STYLE_LIST, "Material", "9mm Silenced | Price: $200.00\nShotgun | Price: $450.00", "Buy", "Close");
			else	
				ShowPlayerDialog(playerid, DIALOG_BM_MATERIAL, DIALOG_STYLE_LIST, "Material", "9mm Silenced | Price: $200.00\nShotgun | Price: $450.00\nDesert Eagle | Price: $350.00\nRifle | Price: $900.00\nAK-47 | Price: $2,500.00", "Buy", "Close");
		}
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

CMD:buyweed(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, g_posSeed[0], g_posSeed[1], g_posSeed[2]))
		return SendErrorMessage(playerid, "You're not at Drug Dealer point!");

	if(PlayerData[playerid][pLevel] < 3)
		return SendErrorMessage(playerid, "Minimal level 3 untuk melakukan ini!");

	new amount;
	if(sscanf(params, "d", amount))
		return SendSyntaxMessage(playerid, "/buyweed [amount]"), SendClientMessage(playerid, COLOR_YELLOW, "(Info) {FFFFFF}The weed price is $5.00 / 1 weed seeds.");

	if(amount < 1 || amount < -1)
		return SendErrorMessage(playerid, "Invalid seeds amount!");

	if(GetMoney(playerid) < amount*500)
		return SendErrorMessage(playerid, "You don't have enough money!");

	if(amount*500 < 1)
		return SendErrorMessage(playerid, "Invalid seeds amount!");
				
	Inventory_Add(playerid, "Weed Seed", 1279, amount);
	SendClientMessageEx(playerid, COLOR_SERVER, "(Drugs) {FFFFFF}Kamu berhasil membeli {FF0000}%d Weed seeds {FFFFFF}seharga {00FF00}$%s", amount, FormatNumber(amount*500));
	GiveMoney(playerid, -amount*500);
	return 1;

}

task timer_OnBmUpdated[3600000]() {

    RandomizeClip();
    RandomizeMaterial();
    RandomizeSchematic();
    RandomizeSchematicHigh();
    RandomizeSeed();

    return 1;
}

CMD:gotobm(playerid, params[]) {
    if(PlayerData[playerid][pAdmin] < 4) {
        return SendErrorMessage(playerid, NO_PERMISSION);
    }

    new option[32];
    if(sscanf(params, "s[32]", option))
        return SendSyntaxMessage(playerid, "/gotobm [schema/schemahigh/seed/material/clip/sellweed]");

    if(!strcmp(option, "schema", true)) {
        SetPlayerPos(playerid, g_posSchematic[0], g_posSchematic[1], g_posSchematic[2]);
        SendAdminAction(playerid, "Anda telah diteleportasi ke Schematic");
    }
    else if(!strcmp(option, "schemahigh", true)) {
        SetPlayerPos(playerid, g_posSchematicHighVelocity[0], g_posSchematicHighVelocity[1], g_posSchematicHighVelocity[2]);
        SendAdminAction(playerid, "Anda telah diteleportasi ke Schematic High Velocity");
    }
    else if(!strcmp(option, "seed", true)) {
        SetPlayerPos(playerid, g_posSeed[0], g_posSeed[1], g_posSeed[2]);
        SendAdminAction(playerid, "Anda telah diteleportasi ke Weed Seed");    
    }
    else if(!strcmp(option, "clip", true)) {
        SetPlayerPos(playerid, g_posClip[0], g_posClip[1], g_posClip[2]);
        SendAdminAction(playerid, "Anda telah diteleportasi ke Weapon Clip");    
    }
    else if(!strcmp(option, "material", true)) {
        SetPlayerPos(playerid, g_posMaterial[0], g_posMaterial[1], g_posMaterial[2]);
        SendAdminAction(playerid, "Anda telah diteleportasi ke Weapon Material");    
    }
    else if(!strcmp(option, "sellweed", true)) {
        SetPlayerPos(playerid, -774.2181,2425.2349,157.1011);
        SendAdminAction(playerid, "Anda telah diteleportasi ke Sell Weed");    
    }
    else SendSyntaxMessage(playerid, "/gotobm [schema/schemahigh/seed/material/clip/sellweed]");

    return 1;
}