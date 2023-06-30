CMD:seal(playerid, params[]) {

    if(GetFactionType(playerid) != FACTION_POLICE)
        return SendErrorMessage(playerid, "Command ini hanya dapat diakses oleh SAPD.");

    if(!PlayerData[playerid][pOnDuty])
        return SendErrorMessage(playerid, "Kamu harus bertugas terlebih dahulu untuk menggunakan command ini.");

    new id = -1;

    if((id = House_Nearest(playerid)) != -1) {
        
        if(!HouseData[id][houseOwner])
            return SendErrorMessage(playerid, "Tidak bisa dilakukan jika rumah dijual.");

        HouseData[id][houseSealed] = !(HouseData[id][houseSealed]);
        SendClientMessageEx(playerid, X11_YELLOW, "(Seal) "WHITE"You have %s "WHITE"the house ID:%d.", (HouseData[id][houseSealed]) ? (""RED"sealed") : (""GREEN"unsealed"), id);
        House_Refresh(id);
    }
    if((id = Business_Nearest(playerid)) != -1) {
        if(BizData[id][bizOwner] == -1) {
            return SendErrorMessage(playerid, "Tidak bisa dilakukan jika bisnis dijual.");
        }

        BizData[id][bizSealed] = !(BizData[id][bizSealed]);
        SendClientMessageEx(playerid, X11_YELLOW, "(Seal) "WHITE"You have %s "WHITE"the business ID:%d.", (BizData[id][bizSealed]) ? (""RED"sealed") : (""GREEN"unsealed"), id);
        Business_Refresh(id);
    }
    if((id = Flat_Exterior(playerid)) != -1) {
        if(FlatData[id][flatOwner] == -1) {
            return SendErrorMessage(playerid, "Tidak bisa dilakukan jika flat dijual.");
        }

        FlatData[id][flatSealed] = !(FlatData[id][flatSealed]);
        SendClientMessageEx(playerid, X11_YELLOW, "(Seal) "WHITE"You have %s "WHITE"the flat ID:%d.", (FlatData[id][flatSealed]) ? (""RED"sealed") : (""GREEN"unsealed"), id);
        Flat_Sync(id);
    }

    return 1;
}