/*bool:IsTVModel(modelid) {

    new istv = false;

    switch(modelid) {
        case 1518: istv = true;
        case 1717: istv = true;
        case 1747, 1748, 1749, 1750, 1752: istv = true;
        case 1781: istv = true;
        case 1791, 1792: istv = true;
        case 2312: istv = true;
        case 2316, 2317, 2318, 2320: istv = true;
        case 2595: istv = true;
        case 16377: istv = true;
        default: istv = false;
    }
    return istv;
}

CMD:watchtv(playerid, params[]) {

    new STREAMER_TAG_OBJECT:objectid, modelid;

    if((objectid = GetClosestDynObjectToPlayer(playerid)) != INVALID_STREAMER_ID) {

        modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID);

        if(!IsTVModel(modelid))
            return SendErrorMessage(playerid, "Kamu tidak berada didekat televisi.");

        SendClientMessage(playerid, X11_WHITE, "Kamu sekarang menonton televisi.");
        SendClientMessage(playerid, X11_WHITE, "Gunakan "YELLOW"/help > Television Commands "WHITE"untuk bantuan.");
    }
    else SendErrorMessage(playerid, "Kamu tidak berada didekat televisi.");

    return 1;
}*/