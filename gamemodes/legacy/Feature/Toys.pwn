#define 			MAX_ACC					5

enum acc {
    accID,
    accName[32],
    accExists,
    accColor1[3],
    accColor2[3],
    accModel,
    accBone,
    accShow,
    Float:accOffset[3],
    Float:accRot[3],
    Float:accScale[3],
};

new
    AccData[MAX_PLAYERS][MAX_ACC][acc],
    ListedPreset[MAX_PLAYERS][15];

stock const accBones[][24] = {
    {"Spine"},
    {"Head"},
    {"Left upper arm"},
    {"Right upper arm"},
    {"Left hand"},
    {"Right hand"},
    {"Left thigh"},
    {"Right thigh"},
    {"Left foot"},
    {"Right foot"},
    {"Right calf"},
    {"Left calf"},
    {"Left forearm"},
    {"Right forearm"},
    {"Left clavicle"},
    {"Right clavicle"},
    {"Neck"},
    {"Jaw"}
};

enum g_accList
{
    accListType,
    accListModel,
    accListName[24]
};

new const accList[][g_accList] =
{
    //Cap
    {1,18955,"CapOverEye1"},
    {1,18956,"CapOverEye2"},
    {1,18957,"CapOverEye3"},
    {1,18958,"CapOverEye4"},
    {1,18959,"CapOverEye5"},
    {1,19553,"StrawHat1"},
    {1,19554,"Beanie1"},
    {1,19558,"19558"},
    {1,18639,"BlackHat1"},
    {1,18638,"HardHat1"},
    {1,19097,"CowboyHat4"},
    {1,19096,"CowboyHat3"},
    {1,18964,"SkullyCap1"},
    {1,18969,"HatMan1"},
    {1,18968,"HatMan2"},
    {1,18967,"HatMan3"},
    {1,18950,"HatBowler4"},
    {1,18948,"HatBowler2"},
    {1,18949,"HatBowler3"},
    {1,19137,"CluckinBellHat1"},
    {1,18926,"Hat1"},
    {1,18927,"Hat2"},
    {1,18928,"Hat3"},
    {1,18940,"CapBack3"},
    {1,18943,"CapBack5"},
    {1,18922,"Beret2"},
    {1,18921,"Beret1"},
    {1,18923,"Beret3"},
    {1,9067,"HoodyHat1"},
    {1,19069,"HoodyHat3"},
    {1,19161,"PoliceHat1"},
    {1,18636,"PoliceCap1"},
    {1,19099,"PoliceCap2"},
    {1,19100,"PoliceCap3"},
    {1,19162,"PoliceHat2"},


    //Bandana
    {2,18891, "Bandana1"},
    {2,18892, "Bandana2"},
    {2,18893, "Bandana3"},
    {2,18894, "Bandana4"},
    {2,18895, "Bandana5"},
    {2,18896, "Bandana6"},
    {2,18897, "Bandana7"},
    {2,18898, "Bandana8"},
    {2,18899, "Bandana9"},
    {2,18900, "Bandana10"},
    {2,18901, "Bandana11"},
    {2,18902, "Bandana12"},
    {2,18903, "Bandana13"},
    {2,18904, "Bandana14"},
    {2,18905, "Bandana15"},
    {2,18906, "Bandana16"},
    {2,18907, "Bandana17"},
    {2,18908, "Bandana18"},
    {2,18909, "Bandana19"},
    {2,18910, "Bandana20"},

    //Mask
    {3,18911, "Mask1"},
    {3,18912, "Mask2"},
    {3,18913, "Mask3"},
    {3,18914, "Mask4"},
    {3,18915, "Mask5"},
    {3,18916, "Mask6"},
    {3,18917, "Mask7"},
    {3,18918, "Mask8"},
    {3,18919, "Mask9"},
    {3,18920, "Mask10"},
    {3,19036,"HockeyMask1"},
    {3,18974,"MaskZorro1"},
    {3,19163,"GimpMask1"},

    //Helmet
    {4,19113, "SillyHelmet1"},
    {4,19114, "SillyHelmet2"},
    {4,19115, "SillyHelmet3"},
    {4,19116, "PlainHelmet1"},
    {4,19117, "PlainHelmet2"},
    {4,19118, "PlainHelmet3"},
    {4,19119, "PlainHelmet4"},
    {4,19120, "PlainHelmet5"},
    {4,18976, "MotorcycleHelmet2"},
    {4,18977, "MotorcycleHelmet3"},
    {4,18978, "MotorcycleHelmet4"},
    {4,18979, "MotorcycleHelmet5"},

    //Watch
    {5,19039, "WatchType1"},
    {5,19040, "WatchType2"},
    {5,19041, "WatchType3"},
    {5,19042, "WatchType4"},
    {5,19043, "WatchType5"},
    {5,19044, "WatchType6"},
    {5,19045, "WatchType7"},
    {5,19046, "WatchType8"},
    {5,19047, "WatchType9"},
    {5,19048, "WatchType10"},
    {5,19049, "WatchType11"},
    {5,19050, "WatchType12"},
    {5,19051, "WatchType13"},
    {5,19052, "WatchType14"},
    {5,19053, "WatchType15"},

    //Glasses
    {6,19006, "GlassesType1"},
    {6,19007, "GlassesType2"},
    {6,19008, "GlassesType3"},
    {6,19009, "GlassesType4"},
    {6,19010, "GlassesType5"},
    {6,19011, "GlassesType6"},
    {6,19012, "GlassesType7"},
    {6,19013, "GlassesType8"},
    {6,19014, "GlassesType9"},
    {6,19015, "GlassesType10"},
    {6,19016, "GlassesType11"},
    {6,19017, "GlassesType12"},
    {6,19018, "GlassesType13"},
    {6,19019, "GlassesType14"},
    {6,19020, "GlassesType15"},
    {6,19021, "GlassesType16"},
    {6,19022, "GlassesType17"},
    {6,19023, "GlassesType18"},
    {6,19024, "GlassesType19"},
    {6,19025, "GlassesType20"},
    {6,19026, "GlassesType21"},
    {6,19027, "GlassesType22"},
    {6,19028, "GlassesType23"},
    {6,19029, "GlassesType24"},
    {6,19030, "GlassesType25"},
    {6,19031, "GlassesType26"},
    {6,19032, "GlassesType27"},
    {6,19033, "GlassesType28"},
    {6,19034, "GlassesType29"},
    {6,19035, "GlassesType30"},

    //Misc
    {7,19896,"CigarettePack1"},
    {7,19897,"CigarettePack2"},
    {7,19904,"ConstructionVest1"},
    {7,19942,"PoliceRadio1"},
    {7,19801,"Balaclava1"},
    {7,19623,"Camera1"},
    {7,19624,"Case1"},
    {7,19559,"HikerBackpack1"},
    {7,19556,"BoxingGloveR"},
    {7,19555,"BoxingGloveL"},
    {7,19142,"SWATARMOUR1"},
    {7,19141,"SWATHELMET1"},
    {7,19520,"pilotHat01"},
    {7,19521,"policeHat01"},
    {7,19515,"SWATAgrey"},
    {7,19330,"fire_hat01"},
    {7,1550,"CJ_MONEY_BAG"},
    {7,19347,"badge01"},
    {7,371,"gun_para"},
    {7,2919,"kmb_holdall"},
    {7,11738,"MedicCase1"},
    {7,19610,"Microphone1"}
};



RGBAToARGB(rgba)
    return rgba >>> 8 | rgba << 24;

GetRGBColor(playerid, id, type = 0)
{
    if(!type) return 0;
    else if(type == 1) return AccData[playerid][id][accColor1][0] << 24 | AccData[playerid][id][accColor1][0] << 16 | AccData[playerid][id][accColor1][0] << 8 | 0xFF;
    else if(type == 2) return AccData[playerid][id][accColor2][0] << 24 | AccData[playerid][id][accColor2][0] << 16 | AccData[playerid][id][accColor2][0] << 8 | 0xFF;
    else return 0;
}

Aksesoris_Attach(playerid, index)
{
    SetPlayerAttachedObject(playerid,index, AccData[playerid][index][accModel], AccData[playerid][index][accBone],
        AccData[playerid][index][accOffset][0], AccData[playerid][index][accOffset][1], AccData[playerid][index][accOffset][2],
        AccData[playerid][index][accRot][0], AccData[playerid][index][accRot][1], AccData[playerid][index][accRot][2],
        AccData[playerid][index][accScale][0], AccData[playerid][index][accScale][1], AccData[playerid][index][accScale][2], RGBAToARGB(GetRGBColor(playerid, index, 1)), RGBAToARGB(GetRGBColor(playerid, index, 2)));

    AccData[playerid][index][accShow] = 1;

    Aksesoris_Save(playerid, index);
    return 1;
}

Aksesoris_Save(playerid, id)
{
    new query[1024];

    mysql_format(sqlcon, query,sizeof(query),"UPDATE `aksesoris` SET `Model`='%d',`Bone`='%d',`Color1`='%03d|%03d|%03d',`Color2`='%d|%d|%d',`Offset`='%.04f|%.04f|%.04f',`Rot`='%.04f|%.04f|%.04f'",
        AccData[playerid][id][accModel],
        AccData[playerid][id][accBone],
        AccData[playerid][id][accColor1][0],
        AccData[playerid][id][accColor1][1],
        AccData[playerid][id][accColor1][2],
        AccData[playerid][id][accColor2][0],
        AccData[playerid][id][accColor2][1],
        AccData[playerid][id][accColor2][2],
        AccData[playerid][id][accOffset][0],
        AccData[playerid][id][accOffset][1],
        AccData[playerid][id][accOffset][2],
        AccData[playerid][id][accRot][0],
        AccData[playerid][id][accRot][1],
        AccData[playerid][id][accRot][2]
    );

    mysql_format(sqlcon, query,sizeof(query),"%s,`Scale`='%.04f|%.04f|%.04f', `Type`='%s', `Show`='%d' WHERE `ID` = '%d'",
        query,
        AccData[playerid][id][accScale][0],
        AccData[playerid][id][accScale][1],
        AccData[playerid][id][accScale][2],
        AccData[playerid][id][accName],
        AccData[playerid][id][accShow],
        AccData[playerid][id][accID]
    );

    return mysql_tquery(sqlcon, query);
}

GetAksesorisNameByModel(model)
{
    new
        name[32];

    for (new i = 0; i < sizeof(accList); i ++) if(accList[i][accListModel] == model) {
        strcat(name, accList[i][accListName]);

        break;
    }
    return name;
}

Aksesoris_GetCount(playerid)
{
    new count;
    for (new i = 0; i != MAX_ACC; i++) if(AccData[playerid][i][accExists]) {
        count++;
    }
    return count;
}

Aksesoris_Create(playerid, model, name[])
{
    new query[128];

    for (new i = 0; i != MAX_ACC; i++)
    { 
        if(!AccData[playerid][i][accExists]) 
        {
            AccData[playerid][i][accExists] = 1;

            format(AccData[playerid][i][accName], 32, name);

            AccData[playerid][i][accModel] = model;

            AccData[playerid][i][accBone] = 1;

            PlayerData[playerid][pAksesoris] = i;
            AccData[playerid][i][accColor1][0] = AccData[playerid][i][accColor1][1] = AccData[playerid][i][accColor1][2] = 255;
            AccData[playerid][i][accColor2][0] = AccData[playerid][i][accColor2][1] = AccData[playerid][i][accColor2][2] = 255;

            AccData[playerid][i][accScale][0] = AccData[playerid][i][accScale][1] = AccData[playerid][i][accScale][2] = 1.0;

            mysql_format(sqlcon, query,sizeof(query),"INSERT INTO `aksesoris` (`accID`) VALUES (%d)", PlayerData[playerid][pID]);
            mysql_tquery(sqlcon, query, "OnAksesorisCreated", "dd", playerid, i);

            SendServerMessage(playerid, "Aksesoris berhasil dibuat! gunakan "YELLOW"/acc "WHITE"untuk mengatur.");
            return i;
        }
    }
    return 1;
}

Aksesoris_ShowAndroid(playerid)
{

    new stringg[512], id = PlayerData[playerid][pAksesoris];
    format(stringg, sizeof(stringg), "Offset X (%.2f)\nOffset Y (%.2f)\nOffset Z (%.2f)\nRotation X (%.2f)\nRotation Y (%.2f)\nRotation Z (%.2f)\nScale X (%.2f)\nScale Y (%.2f)\nScale Z (%.2f)",
    AccData[playerid][id][accOffset][0],//pPosX
    AccData[playerid][id][accOffset][1],//pPosY
    AccData[playerid][id][accOffset][2],//pPosZ
    AccData[playerid][id][accRot][0],//pRotX
    AccData[playerid][id][accRot][1],//pRotY
    AccData[playerid][id][accRot][2],//pRotZ
    AccData[playerid][id][accScale][0],//pScaleX
    AccData[playerid][id][accScale][1],//pScaleY
    AccData[playerid][id][accScale][2]);//pScaleZ
    ShowPlayerDialog(playerid, DIALOG_ANDROID, DIALOG_STYLE_LIST, "Accessory Coordinate", stringg, "Select", "Cancel");
    return 1;
}

Aksesoris_Sync(playerid)
{
    for(new i = 0; i < MAX_ACC; i++) if(AccData[playerid][i][accExists] && AccData[playerid][i][accShow])
        Aksesoris_Attach(playerid, i);

    return 1;
}
//a
function Aksesoris_Load(playerid)
{
    if(cache_num_rows())
    {
        static
            string[128];

        for (new i = 0; i != cache_num_rows(); i ++) 
        {
            AccData[playerid][i][accExists] = true;

            cache_get_value_name(i, "Type", AccData[playerid][i][accName], 32);

            cache_get_value_name(i, "Color1", string);
            sscanf(string, "p<|>ddd",AccData[playerid][i][accColor1][0],AccData[playerid][i][accColor1][1],AccData[playerid][i][accColor1][2]);

            cache_get_value_name(i, "Color2", string);
            sscanf(string, "p<|>ddd",AccData[playerid][i][accColor2][0],AccData[playerid][i][accColor2][1],AccData[playerid][i][accColor2][2]);

            cache_get_value_name(i, "Offset", string);
            sscanf(string, "p<|>fff",AccData[playerid][i][accOffset][0],AccData[playerid][i][accOffset][1],AccData[playerid][i][accOffset][2]);

            cache_get_value_name(i, "Rot", string);
            sscanf(string, "p<|>fff",AccData[playerid][i][accRot][0],AccData[playerid][i][accRot][1],AccData[playerid][i][accRot][2]);

            cache_get_value_name(i, "Scale", string);
            sscanf(string, "p<|>fff",AccData[playerid][i][accScale][0],AccData[playerid][i][accScale][1],AccData[playerid][i][accScale][2]);

            cache_get_value_name_int(i, "ID", AccData[playerid][i][accID]);
            cache_get_value_name_int(i, "Model", AccData[playerid][i][accModel]);
            cache_get_value_name_int(i, "Bone", AccData[playerid][i][accBone]);
            cache_get_value_name_int(i, "Show", AccData[playerid][i][accShow]);

            if(AccData[playerid][i][accShow])
                Aksesoris_Attach(playerid, i);
        }
    }
    return 1;
}
function OnAksesorisCreated(playerid, id)
{
    AccData[playerid][id][accID] = cache_insert_id();
    Aksesoris_Save(playerid, id);
    Aksesoris_Attach(playerid, id);

    new string[256+1];
    for(new i; i < sizeof(accBones); i++)
    {
        format(string,sizeof(string),"%s%s\n",string,accBones[i]);
    }
    ShowPlayerDialog(playerid, DIALOG_BONE, DIALOG_STYLE_LIST, "Edit Bone",string,"Select","Close");
    SendCustomMessage(playerid, X11_LIGHTBLUE, "Accessory",""WHITE"Aksesoris berhasil dibuat! gunakan "YELLOW"/acc "WHITE"untuk mengatur.");
    return 1;
}

ShowAksesorisMenu(playerid) {
	new 
		string[552]
	;
	
	format(string,sizeof(string),"Index\tName\tStatus\n");
	for (new id = 0; id < MAX_ACC; id++)
	{
        if(id == -1) 
            return SendErrorMessage(playerid, "Tidak dapat membuka aksesoris menu! lapor ini kepada developer terganteng se abad jagat raya slebew :b");

        if(AccData[playerid][id][accExists])
		    format(string,sizeof(string),"%s"WHITE"#%d\t%s\t%s\n", string, id, AccData[playerid][id][accName], (AccData[playerid][id][accShow]) ? ("attached") : ("not attached"));
        else 
            format(string, sizeof(string), "%s"GREY"Empty slot\n", string);
	}
	ShowPlayerDialog(playerid, DIALOG_ACC_MENU, DIALOG_STYLE_TABLIST_HEADERS, "Editing Accessory", string, "Select","Exit");

    return 1;
}

CMD:acc(playerid, params[])
{
    ShowAksesorisMenu(playerid);
    return 1;
}
