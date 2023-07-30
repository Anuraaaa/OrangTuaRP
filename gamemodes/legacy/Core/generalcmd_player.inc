CMD:selltostate(playerid, params[]) {

	new vehicleid = GetPlayerVehicleID(playerid);

	if(!IsPlayerInRangeOfPoint(playerid, 5.0, -2095.2434,95.1803,35.3203))
		return SendErrorMessage(playerid, "Kamu tidak berada pada vehicle state sales point.");

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return SendErrorMessage(playerid, "Kamu harus mengemudikan kendaraanmu.");

	if(!Iter_Contains(Vehicle, vehicleid))
		return SendErrorMessage(playerid, "Kendaraan ini tidak bisa dijual.");

	if(!Vehicle_IsOwner(playerid, vehicleid))
		return SendErrorMessage(playerid, "Kamu harus mengemudikan kendaraanmu.");

	if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
		return SendErrorMessage(playerid, "Tidak bisa menjual kendaraan rental!");

	new veh_price = 0;

	if(VehicleData[vehicleid][vPrice] > 0)
		veh_price = floatround(VehicleData[vehicleid][vPrice] / 2);

	SendServerMessage(playerid, "Kendaraan ini dihargai sebesar: "GREEN"$%s", FormatNumber(veh_price));
	SendServerMessage(playerid, "Ketik "YELLOW"/selltostate confirm "WHITE"untuk menjual kendaraanmu.");

	if(!strcmp(params, "confirm", true)) {

		SendServerMessage(playerid, "Kamu berhasil menjual %s milikmu ke state seharga "GREEN"$%s", GetVehicleName(vehicleid), FormatNumber(veh_price));
		GiveMoney(playerid, veh_price, "Jual veh ke state");
		Vehicle_Delete(vehicleid, true);
	}
	return 1;
}

CMD:flipcoin(playerid, params[]) {
	new result = RandomEx(1, 3);

	SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s flips a coin landing on "RED"%s", ReturnName(playerid), (result == 2) ? ("head") : ("tail"));
	return 1;
}
CMD:dice(playerid, params[])
{
    static
        dice;

    if(sscanf(params, "d", dice))
        return SendSyntaxMessage(playerid, "/dice [1,2,3,4]");

    if(dice < 1 || dice > 4)
        return SendErrorMessage(playerid, "Invalid dice value.");

    switch(dice)
    {
        case 1: SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s rolls a dice landing on the number "RED"%d.", ReturnName(playerid), (random(6) + 1));
        case 2: SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s rolls a dice landing on the number "RED"%d-%d.", ReturnName(playerid), (random(6) + 1), (random(6) + 1));
        case 3: SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s rolls a dice landing on the number "RED"%d-%d-%d.", ReturnName(playerid), (random(6) + 1), (random(6) + 1), (random(6) + 1));
        case 4: SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s rolls a dice landing on the number "RED"%d-%d-%d-%d.", ReturnName(playerid), (random(6) + 1), (random(6) + 1), (random(6) + 1), (random(6) + 1));
    }
    return 1;
}

CMD:rcp(playerid, params[]) {

	new vehicleid = GetPlayerVehicleID(playerid);

	if(IsPlayerWorkInBus(playerid) && (IsBusVehicle(vehicleid) || IsBus2Vehicle(vehicleid))) {
		new mode = 0;
		switch(busSelect[playerid]) {
			case 1: {
				SetPlayerRaceCheckpoint(playerid, 0, arr_busRoute[currentBRoute[playerid]][b_x], arr_busRoute[currentBRoute[playerid]][b_y], arr_busRoute[currentBRoute[playerid]][b_z], mode ? (-1.0) : (arr_busRoute[currentBRoute[playerid] + 1][b_x]), mode ? (-1.0) : (arr_busRoute[currentBRoute[playerid] + 1][b_y]), mode ? (-1.0) : (arr_busRoute[currentBRoute[playerid] + 1][b_z]), 4);
				SendServerMessage(playerid, "Checkpoint reloaded.");
			}
			case 2: {
				SetPlayerRaceCheckpoint(playerid, 0, arr_busRoute2[currentBRoute[playerid]][b_x], arr_busRoute2[currentBRoute[playerid]][b_y], arr_busRoute2[currentBRoute[playerid]][b_z], mode ? (-1.0) : (arr_busRoute2[currentBRoute[playerid] + 1][b_x]), mode ? (-1.0) : (arr_busRoute2[currentBRoute[playerid] + 1][b_y]), mode ? (-1.0) : (arr_busRoute2[currentBRoute[playerid] + 1][b_z]), 4);
				SendServerMessage(playerid, "Checkpoint reloaded.");			
			}
		}
		return 1;
	}
	if(OnSweeping[playerid] && IsSweeperVehicle(vehicleid)) {
		SetPlayerCheckpoint(playerid, SweeperPoint[SweeperIndex[playerid]][0], SweeperPoint[SweeperIndex[playerid]][1], SweeperPoint[SweeperIndex[playerid]][2], 4.0);
		SendServerMessage(playerid, "Checkpoint reloaded.");
		return 1;
	}
	if(PlayerData[playerid][pOnDMV] && vehicleid == PlayerData[playerid][pVehicleDMV]) {
		SetPlayerCheckpoint(playerid, DMVPoint[PlayerData[playerid][pIndexDMV]][0], DMVPoint[PlayerData[playerid][pIndexDMV]][1], DMVPoint[PlayerData[playerid][pIndexDMV]][2], 3.4);
		SendServerMessage(playerid, "Checkpoint reloaded.");
		return 1;
	}
	if(OnDeliveryWork[playerid] && GetPVarInt(playerid, "ReturnRumpo")) {
		SetPlayerCheckpoint(playerid, -1720.2201,53.4831,3.5495, 5.0);
		SendServerMessage(playerid, "Checkpoint reloaded.");
		return 1;
	}
	if(OnMower[playerid]) {
		SetPlayerCheckpoint(playerid, arr_MowerCP[MowerIndex[playerid]][mowerX], arr_MowerCP[MowerIndex[playerid]][mowerY], arr_MowerCP[MowerIndex[playerid]][mowerZ], 4.0);
		SendServerMessage(playerid, "Checkpoint reloaded.");
		return 1;
	}
	if(MinerIndex[playerid] == 1) {
		SetPlayerCheckpoint(playerid, -1332.8300, 2518.1953, 87.0469, 2.0);
		SendServerMessage(playerid, "Checkpoint reloaded.");
	}
	if(MinerIndex[playerid] == 3) {
		SetPlayerCheckpoint(playerid, -1299.5569,2549.2720,87.5599, 2.0);
		SendServerMessage(playerid, "Checkpoint reloaded.");
	}
	if(MinerIndex[playerid] == 4) {
		SetPlayerCheckpoint(playerid, -1304.1875,2491.8530,87.1437, 3.0);
		SendServerMessage(playerid, "Checkpoint reloaded.");
	}
    if(InRace[playerid] && RaceWith[playerid] != INVALID_PLAYER_ID) {

        Race_ProgressCP(playerid);
		SendServerMessage(playerid, "Checkpoint reloaded.");
    }

	if(HaulingIndex[playerid] == 2) {
		new idx = HaulingSelect[playerid];

		SetPlayerRaceCheckpoint(playerid, 2, cp_Trailer_arr[idx][0], cp_Trailer_arr[idx][1], cp_Trailer_arr[idx][2], 0.0, 0.0, 0.0, 5.0);
		SendServerMessage(playerid, "Checkpoint reloaded.");
	}
	if(SmugglerData[smugCarrier] == playerid) {
		SetPlayerRaceCheckpoint(playerid, 2, SmugglerData[smugDelivX], SmugglerData[smugDelivY], SmugglerData[smugDelivZ], 0.0, 0.0, 0.0, 5.0);
	}
	if(g_CourierState[playerid] == COURIER_STATE_ONFINISH) {
		SetPlayerCheckpoint(playerid, -1945.0291,-1085.2745,30.7779,  3.5);
	}
	return 1;
}

CMD:hudtype(playerid, params[]) {

	if(PlayerData[playerid][pTogHud])
		return SendErrorMessage(playerid, "Kamu masih mematikan HUD display.");

	ShowPlayerDialog(playerid, DIALOG_HUD_TYPE, DIALOG_STYLE_LIST, "Change HUD", "Original\nSimple\nProper", "Select", "Close");
	return 1;
}
CMD:changepassword(playerid, params[])
{
	ShowPlayerDialog(playerid, DIALOG_CHANGEPASS, DIALOG_STYLE_PASSWORD, "Change Password", "Silahkan masukkan password-mu yang terbaru:\n(note) Untuk keamanan, Jangan menggunakan password yang mirip dengan sebelumnya.", "Change", "Cancel");
	return 1;
}

CMD:svd(playerid, params[]) {
	if(IsPlayerSpawned(playerid))  {
		SQL_SaveCharacter(playerid);
		SendServerMessage(playerid, "Data karaktermu berhasil "YELLOW"diperbaharui");
	}
	return 1;
}
CMD:refuel(playerid, params[])
{
    static index, vehicleid;

	vehicleid = GetPlayerVehicleID(playerid);
    if((index = Pump_Nearest(playerid, 7.0)) != -1)
    {


	    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	        return SendErrorMessage(playerid, "Kamu harus mengemudi kendaraan untuk mengisi bensin.");
	    
	    if(GetEngineStatus(GetPlayerVehicleID(playerid)))
	        return SendErrorMessage(playerid, "Matikan mesin kendaraan terlebih dahulu!");

        if(BizData[PumpData[index][pumpBusiness]][bizOwner] == -1) 
        	return SendErrorMessage(playerid, "Bisnis ini masih tutup!");

        if(PumpData[index][pumpFuel] < 1) 
        	return SendErrorMessage(playerid, "Tidak ada bahan bakar pada fuelpump!");

        if(GetMoney(playerid) < 50) 
        	return SendErrorMessage(playerid, "Minimal kamu harus memiliki $0.5 untuk mengisi bahan bakar.");
        
		if(!IsEngineVehicle(vehicleid))	
			return SendErrorMessage(playerid, "Kendaraan ini tidak memiliki mesin.");

		if(Vehicle_GetFuel(vehicleid) > 100)
			return SendErrorMessage(playerid, "Kendaraan ini sudah memiliki bensin yang penuh.");

		SendServerMessage(playerid, "Kendaraan ini dapat menampung bahan bakar hingga %.2f liter.", GetVehicleFuelMax(GetVehicleModel(vehicleid)));
		PlayerData[playerid][pGasPump] = index;
		ShowPlayerDialog(playerid, DIALOG_REFUEL, DIALOG_STYLE_INPUT, "Refuel Vehicle", ""WHITE"Masukkan jumlah bahan bakar (liter) untuk mengisi kendaraan ini\nHarga per-liter nya adalah "GREEN"$0.5\n\n"GREY"(ketik \"FULLTANK\" jika ingin mengisi hingga penuh)", "Refuel", "Close");
    }
    else SendErrorMessage(playerid, "Kamu tidak berada didekat pengisian bahan bakar.");

    return 1;
}

CMD:livemode(playerid, params[]) {

	liveMode[playerid] = !(liveMode[playerid]);
	SendServerMessage(playerid, "Live Mode has been %s", (liveMode[playerid]) ? (""GREEN"enabled.") : (""RED"disabled."));
	return 1;
}
CMD:getidcard(playerid, params[]) {

	if(!IsPlayerInRangeOfPoint(playerid, 5.0, 2846.3269,2882.9648,320.1620))
		return SendErrorMessage(playerid, "Kamu harus berada didalam City Hall untuk mendapatkan ID Card.");

	if(PlayerData[playerid][pIDCard])
		return SendErrorMessage(playerid, "Kamu sudah memiliki ID Card.");

	if(GetMoney(playerid) < 1500)
		return SendErrorMessage(playerid, "Kamu membutuhkan $15.00 untuk membuat ID Card.");

	GiveMoney(playerid, -1500, "Bayar ID Card");

	PlayerData[playerid][pIDCard] = 1;
	PlayerData[playerid][pIDCardExpired] = (gettime()+((24*3600)*30));

	SendServerMessage(playerid, "Kamu berhasil mendapatkan ID Card!");
	new str[352];

	strcat(str, sprintf("1). Masa expired ID Card mu adalah hingga %s.\n", ConvertTimestamp(Timestamp:PlayerData[playerid][pIDCardExpired])));
	strcat(str, "2). Jika ID Card expired, kamu otomatis keluar dari pekerjaan-mu.\n");
	strcat(str, "3). Kamu bisa memperpanjang ID Card disini dengan menggunakan \"/extendidcard\"\n");
	strcat(str, "4). Perpanjangan ID Card tidak dipungut biaya.");
	ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "Identification Card", str, "Close", "");
	return 1;
}

CMD:extendidcard(playerid, params[]) {

	if(!IsPlayerInRangeOfPoint(playerid, 5.0, 2846.3269,2882.9648,320.1620))
		return SendErrorMessage(playerid, "Kamu harus berada didalam City Hall untuk memperpanjang ID Card.");

	if(!PlayerData[playerid][pIDCard])
		return SendErrorMessage(playerid, "Kamu tidak memiliki ID Card untuk diperpanjang.");

	if(PlayerData[playerid][pIDCardExpired] != 0)
		return SendErrorMessage(playerid,  "Sekarang belum waktunya memperpanjang ID Card.");

	PlayerData[playerid][pIDCardExpired] = (gettime()+((24*3600)*30));
	SendServerMessage(playerid, "Kamu berhasil memperpanjang ID Card milikmu.");
	SendServerMessage(playerid, "Masa aktif ID Card mu adalah hingga "LIGHTBLUE"%s.", ConvertTimestamp(Timestamp:PlayerData[playerid][pIDCardExpired]));
	return 1;
}

CMD:showidcard(playerid, params[])
{
    static
        userid;

	if(!PlayerData[playerid][pIDCard])
		return SendErrorMessage(playerid, "Kamu tidak memiliki ID Card.");
		
    if(sscanf(params, "u", userid)) 
		return SendSyntaxMessage(playerid, "/showidcard [playerid/PartOfName]");

    if(userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0)) 
		return SendErrorMessage(playerid, "That player is disconnected or not near you.");

    SendClientMessageEx(playerid, COLOR_WHITE, "Kamu memperlihatkan ID Card mu kepada %s.", ReturnName(userid));
    
    SendClientMessage(userid, X11_LIGHTBLUE, "=========== San Fierro Identification Card ===========");
    SendCustomMessage(userid, X11_GREY, "Registered ID","SF-%07d", PlayerData[playerid][pID] + 99);
    SendCustomMessage(userid, X11_GREY, "Name","%s", ReturnName(playerid));
    SendCustomMessage(userid, X11_GREY, "Birthdate","%s", PlayerData[playerid][pBirthdate]);
    SendCustomMessage(userid, X11_GREY, "Gender","%s", (PlayerData[playerid][pGender] == 2) ? ("Female") : ("Male"));
    SendCustomMessage(userid, X11_GREY, "Residence","San Fierro");
    SendCustomMessage(userid, X11_GREY, "Origin","%s", PlayerData[playerid][pOrigin]);
	if(PlayerData[playerid][pIDCardExpired] != 0) SendCustomMessage(userid, X11_GREY, "Validation", ""GREEN"Valid "WHITE"until %s", ConvertTimestamp(Timestamp:PlayerData[playerid][pIDCardExpired]));
	else SendCustomMessage(userid, X11_GREY, "Validation", ""RED"Expired");
    return 1;
}

CMD:cursor(playerid, params[])
{
	if(isnull(params))
		return SendSyntaxMessage(playerid, "/cursor [show/hide]");

	if(!strcmp(params, "show", true))
	{
		SelectTextDraw(playerid, COLOR_YELLOW);
	}
	else if(!strcmp(params, "hide", true))
	{
		CancelSelectTextDraw(playerid);
	}
	return 1;
}

CMD:stuck(playerid, params[]) {

	if(isnull(params)) 
		return SendSyntaxMessage(playerid, "/stuck [vwid/intid/freeze/pos]");

	if(!strcmp(params, "vwid", true)) {
		SendServerMessage(playerid, "Virtual world fixed.");

		SetPlayerVirtualWorld(playerid, 0);
	}
	else if(!strcmp(params, "intid", true)) {
		SendServerMessage(playerid, "Interior id fixed.");

		SetPlayerInterior(playerid, 0);
	}
	else if(!strcmp(params, "freeze", true)) {
		SendServerMessage(playerid, "You have been unfreezed.");
		TogglePlayerControllable(playerid, true);
	}
	else if(!strcmp(params, "pos", true)) {
		
		if(PlayerData[playerid][pLastPos][0] == 0.0 && PlayerData[playerid][pLastPos][1] == 0.0 && PlayerData[playerid][pLastPos][2] == 0.0) {
			return SendErrorMessage(playerid, "Tidak dapat menggunakan Opsi ini sekarang.");
		}

		SetPlayerPos(playerid, PlayerData[playerid][pLastPos][0],  PlayerData[playerid][pLastPos][1],  PlayerData[playerid][pLastPos][2]);
		SetPlayerVirtualWorld(playerid, PlayerData[playerid][pLastWorld]);
		SetPlayerInterior(playerid, PlayerData[playerid][pLastInterior]);

		SendServerMessage(playerid, "Posisi mu berhasil diperbaiki! (tidak berubah? silahkan relogin)");

		FreezePlayer(playerid, 2000);
		PlayerData[playerid][pPos][0] = PlayerData[playerid][pLastPos][0];
		PlayerData[playerid][pPos][1] = PlayerData[playerid][pLastPos][1];
		PlayerData[playerid][pPos][2] = PlayerData[playerid][pLastPos][2];
		PlayerData[playerid][pInterior] = PlayerData[playerid][pLastInterior];
		PlayerData[playerid][pWorld] = PlayerData[playerid][pLastWorld];

		ResetPlayerOutsideInfo(playerid);
		ResetInteriorData(playerid);

		SQL_SaveCharacter(playerid);
	}
	return 1;
}
CMD:tog(playerid, params[])
	return cmd_toggle(playerid, params);

CMD:toggle(playerid, params[])
{
	if(isnull(params)) {
		SendSyntaxMessage(playerid, "/tog(gle) [Names]");

		if(PlayerData[playerid][pAdmin])
			SendClientMessage(playerid, COLOR_SERVER, "Names: {FFFFFF}amsg, pmlog, hud, chatanim, login, ooc, pm, autopc, speedcam");
		else
			SendClientMessage(playerid, COLOR_SERVER, "Names: {FFFFFF}hud, chatanim, login, ooc, pm, autopc, speedcam");
		return 1;
	}
	if(!strcmp(params, "hud", true))
	{
		if(!PlayerData[playerid][pTogHud])
		{
			PlayerData[playerid][pTogHud] = true;

			HidePlayerHUD(playerid);

			TextDrawHideForPlayer(playerid,sen);
			TextDrawHideForPlayer(playerid,koma2);
			SendClientMessage(playerid, COLOR_CLIENT, "(HUD) {FFFFFF}You have {FF0000}disabled {FFFFFF}the HUD");
		}
		else
		{
			PlayerData[playerid][pTogHud] = false;
			SendClientMessage(playerid, COLOR_CLIENT, "(HUD) {FFFFFF}You have {00FF00}enabled {FFFFFF}the HUD");


			TextDrawShowForPlayer(playerid,sen);
			TextDrawShowForPlayer(playerid,koma2);

			ShowPlayerHUD(playerid);
		}
	}
	else if(!strcmp(params, "speedcam", true)) {
		if(GetFactionType(playerid) != FACTION_POLICE)
			return SendErrorMessage(playerid, "Opsi ini hanya bisa untuk Police Department!");

		PlayerData[playerid][pToggleSpeed] = !(PlayerData[playerid][pToggleSpeed]);
		SendServerMessage(playerid, "Speedcam Notification has been %s", (PlayerData[playerid][pToggleSpeed]) ? (""GREEN"enabled.") : (""RED"disabled."));
	}
	else if(!strcmp(params, "autopc", true)) {

		if(PlayerData[playerid][pPaycheck] < 1)
			return SendErrorMessage(playerid, "Ambil PayCheck-mu yang sekarang dahulu.");

		PlayerData[playerid][pAutoPaycheck] = !(PlayerData[playerid][pAutoPaycheck]);
		SendServerMessage(playerid, "AutoPayCheck has been %s", (PlayerData[playerid][pAutoPaycheck]) ? (""GREEN"enabled.") : (""RED"disabled."));
	}
	else if(!strcmp(params, "pmlog", true)) {

		if(PlayerData[playerid][pAdmin] < 1)
			return SendErrorMessage(playerid, "Opsi ini hanya untuk admin.");

		PlayerData[playerid][pPMLog] = !(PlayerData[playerid][pPMLog]);
		SendClientMessageEx(playerid, COLOR_CLIENT, "(PMLog) {FFFFFF}You have %s {FFFFFF}Private Message logs.", (!PlayerData[playerid][pPMLog]) ? ("{FF0000}disabled") : ("{00FF00}enabled"));
	}
	else if(!strcmp(params, "amsg", true)) {

		if(PlayerData[playerid][pAdmin] < 1)
			return SendErrorMessage(playerid, "Opsi ini hanya untuk admin.");

		PlayerData[playerid][pAMSG] = !(PlayerData[playerid][pAMSG]);
		SendClientMessageEx(playerid, COLOR_CLIENT, "(AMSG) {FFFFFF}You have %s {FFFFFF}Admin Messages.", (!PlayerData[playerid][pAMSG]) ? ("{FF0000}disabled") : ("{00FF00}enabled"));
	}
	else if(!strcmp(params, "ooc", true))
	{
		PlayerData[playerid][pTogGlobal] = !(PlayerData[playerid][pTogGlobal]);
		SendClientMessageEx(playerid, COLOR_CLIENT, "(OOC) {FFFFFF}You have %s {FFFFFF}Global OOC chat's!", (PlayerData[playerid][pTogGlobal]) ? ("{FF0000}disabled") : ("{00FF00}enabled"));
	}
	else if(!strcmp(params, "login", true))
	{
		PlayerData[playerid][pTogLogin] = !(PlayerData[playerid][pTogLogin]);
		SendClientMessageEx(playerid, COLOR_CLIENT, "(Login) {FFFFFF}You have %s {FFFFFF}Login message's!", (PlayerData[playerid][pTogLogin]) ? ("{FF0000}disabled") : ("{00FF00}enabled"));
	}
	else if(!strcmp(params, "pm", true))
	{
		PlayerData[playerid][pTogPM] = !(PlayerData[playerid][pTogPM]);
		SendClientMessageEx(playerid, COLOR_CLIENT, "(PM) {FFFFFF}You have %s {FFFFFF}Private Message!", (PlayerData[playerid][pTogPM]) ? ("{FF0000}disabled") : ("{00FF00}enabled"));
	}
	else if(!strcmp(params, "buy", true))
	{
		PlayerData[playerid][pTogBuy] = !(PlayerData[playerid][pTogBuy]);
		SendClientMessageEx(playerid, COLOR_CLIENT, "(BUY) {FFFFFF}You have changed /buy display to %s", (PlayerData[playerid][pTogBuy]) ? ("{FF0000}TextDraw") : ("{00FF00}Dialog list"));
	}
	else if(!strcmp(params, "chatanim", true))
	{
		PlayerData[playerid][pTogAnim] = !(PlayerData[playerid][pTogAnim]);
		SendClientMessageEx(playerid, COLOR_CLIENT, "(Animation) {FFFFFF}You have %s {FFFFFF}Chat animation!", (PlayerData[playerid][pTogAnim]) ? ("{FF0000}disabled") : ("{00FF00}enabled"));
	}
	return 1;
}
CMD:time(playerid, params[])
{
	new
	    string[128],
		month[12],
		date[6];

	getdate(date[2], date[1], date[0]);
	gettime(date[3], date[4], date[5]);

	switch (date[1])
	{
	    case 1: month = "January";
	    case 2: month = "February";
	    case 3: month = "March";
	    case 4: month = "April";
	    case 5: month = "May";
	    case 6: month = "June";
	    case 7: month = "July";
	    case 8: month = "August";
	    case 9: month = "September";
	    case 10: month = "October";
	    case 11: month = "November";
	    case 12: month = "December";
	}
	format(string, sizeof(string), "~g~%s %02d %d~n~~b~%02d:%02d:%02d", month, date[0], date[2], date[3], date[4], date[5]);
	GameTextForPlayer(playerid, string, 6000, 1);
	ApplyAnimation(playerid, "COP_AMBIENT", "Coplook_watch", 4.1, 0, 0, 0, 0, 0);
	if(PlayerData[playerid][pPaycheck] > 0)
	{
	    SendClientMessageEx(playerid, COLOR_SERVER, "(Info) {FFFFFF}Kamu dapat mengambil Paycheck dalam %d Menit lagi.", PlayerData[playerid][pPaycheck]/60);
	}
	else
	{
	    SendClientMessage(playerid, COLOR_SERVER, "(Info) {FFFFFF}Kamu sudah bisa mengambil Paycheck di Bank/ATM sekarang!");
	}
	if(PlayerData[playerid][pOnDuty])
	{
		new hour, minute, second;
		GetElapsedTime(PlayerData[playerid][pDutyTime], hour, minute, second);
		SendClientMessageEx(playerid, COLOR_SERVER, "(Salary) {FFFFFF}Salary dari faction akan di-issue dalam %02d menit dan %02d detik.", minute, second);
	}
	return 1;
}

CMD:cc(playerid, params[])
{
	for (new i = 0; i < 100; i ++)
	{
	    SendClientMessage(playerid, -1, "");
	}
	return 1;
}

CMD:untow(playerid, params[])
{
	if (GetVehicleModel(GetPlayerVehicleID(playerid)) != 525)
	    return SendErrorMessage(playerid, "You are not driving a tow truck.");

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return SendErrorMessage(playerid, "You are not the driver.");

	new
	    trailerid = GetVehicleTrailer(GetPlayerVehicleID(playerid));

    if (!trailerid)
	    return SendErrorMessage(playerid, "There is no vehicle hooked onto the truck.");

	DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));
	SendNearbyMessage(playerid, 20.0, X11_PLUM, "** %s has unhooked the %s from the tow truck.", ReturnName(playerid), ReturnVehicleModelName(GetVehicleModel(trailerid)));

	return 1;
}

CMD:tow(playerid, params[])
{
	if (GetVehicleModel(GetPlayerVehicleID(playerid)) != 525)
	    return SendErrorMessage(playerid, "You are not driving a tow truck.");

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return SendErrorMessage(playerid, "You are not the driver.");

	new vehicleid = GetVehicleFromBehind(GetPlayerVehicleID(playerid));

	if (vehicleid == INVALID_VEHICLE_ID)
	    return SendErrorMessage(playerid, "There is no vehicle in range.");

	if (!IsDoorVehicle(vehicleid))
	    return SendErrorMessage(playerid, "You can't tow this vehicle.");

	AttachTrailerToVehicle(vehicleid, GetPlayerVehicleID(playerid));
	SendNearbyMessage(playerid, 20.0, X11_PLUM, "** %s has hooked a %s onto their tow truck.", ReturnName(playerid), ReturnVehicleModelName(GetVehicleModel(vehicleid)));
	return 1;
}

CMD:sb(playerid, params[]) {
	return cmd_seatbelt(playerid, "");
}
CMD:seatbelt(playerid, params[])
{
	if(!IsPlayerInAnyVehicle(playerid))
		return SendErrorMessage(playerid, "You must be inside of any car!");

	if(!IsDoorVehicle(GetPlayerVehicleID(playerid)))
		return SendErrorMessage(playerid, "You must be inside of any car!");

	SetPlayerSeatbelt(playerid);
	return 1;
}

CMD:helm(playerid,params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);

    if(IsPlayerInAnyVehicle(playerid) && Helmet[playerid] == 0)
    {
        if(IsABike(vehicleid) || IsABicycle(vehicleid))
        {
            Helmet[playerid] = 1;
            SetPlayerAttachedObject(playerid,9 , 18645, 2, 0.07, 0.017, 0, 88, 75, 9);
            SendClientMessage(playerid, X11_GREEN, "You have put on a bike helmet. This will supress the impact of a crash.");
            SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s reaches for their helmet, and takes it off.", ReturnName(playerid));
        }
    }
    else if(IsPlayerInAnyVehicle(playerid) && Helmet[playerid] == 1)
    {
        if(IsABike(vehicleid) || IsABicycle(vehicleid))
        {
            Helmet[playerid] = 0;
            SendClientMessage(playerid, X11_GREEN, "You have taken off your helmet. You will no longer be protected from crashes.");
            SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s reaches for their helmet, and unbuckles it.", ReturnName(playerid));
            if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) 
				RemovePlayerAttachedObject(playerid, 9);
        }
    }
    return 1;
}

CMD:myproperty(playerid, params[])
{
	new str[1012], date[6], curtime = gettime(), time[3], header[128];
	gettime(time[0], time[1], time[2]);

	TimestampToDate(curtime, date[2], date[1], date[0], date[3], date[4], date[5]);
	format(header, sizeof(header), "{AFAFAF}%s %s %s %i | %02d:%02d:%02d", GetWeekDay(date[0], date[1], date[2]), GetDay(date[0]), GetMonthName(date[1]), date[2], time[0], time[1], time[2]);
	format(str, sizeof(str), "Property Type\tProperty ID\tProperty Location\n");
	foreach(new i : House) if(House_IsOwner(playerid, i))
	{
		format(str, sizeof(str), "%sHouse(%s)\t%d\t%s\n", str, House_GetType(HouseData[i][houseType]), i, GetLocation(HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2]));
	}
	forex(i, MAX_BUSINESS) if(BizData[i][bizExists] && Biz_IsOwner(playerid, i))
	{
		format(str, sizeof(str), "%sBusiness\t%d\t%s\n", str, i, GetLocation(BizData[i][bizExt][0], BizData[i][bizExt][1], BizData[i][bizExt][2]));
	}
	foreach(new i : Flat) if(Flat_IsOwner(playerid, i))
	{
		format(str, sizeof(str), "%sFlat\t%d\t(null)\n", str, i);
	}
	ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, header, str, "Close", "");
	return 1;
}
CMD:licenses(playerid, params[])
{
	static
	    userid;

	if (sscanf(params, "u", userid))
	{
		SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");

		if (PlayerData[playerid][pLicense][0]) SendClientMessageEx(playerid, COLOR_WHITE, "Driving License: {33CC33}Passed");
	 	else SendClientMessageEx(playerid, COLOR_WHITE, "Driving License: {AA3333}Not Passed");

		if (PlayerData[playerid][pLicense][1]) SendClientMessageEx(playerid, COLOR_WHITE, "Boat License: {33CC33}Passed");
		else SendClientMessageEx(playerid, COLOR_WHITE, "Boat License: {AA3333}Not Passed");

		if (PlayerData[playerid][pLicense][2]) SendClientMessageEx(playerid, COLOR_WHITE, "Lumberjack License: {33CC33}Passed");
		else SendClientMessageEx(playerid, COLOR_WHITE, "Lumberjack License: {AA3333}Not Passed");

		if (PlayerData[playerid][pLicense][3]) SendClientMessageEx(playerid, COLOR_WHITE, "Hauling License: {33CC33}Passed");
		else SendClientMessageEx(playerid, COLOR_WHITE, "Hauling License: {AA3333}Not Passed");

		SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");
		return 1;
	}

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	SendClientMessage(userid, COLOR_GREY, "-----------------------------------------------------------");

	if (PlayerData[playerid][pLicense][0]) SendClientMessageEx(userid, COLOR_WHITE, "Driving License: {33CC33}Passed");
 	else SendClientMessageEx(userid, COLOR_WHITE, "Driving License: {AA3333}Not Passed");

	if (PlayerData[playerid][pLicense][1]) SendClientMessageEx(userid, COLOR_WHITE, "Boat License: {33CC33}Passed");
	else SendClientMessageEx(userid, COLOR_WHITE, "Boat License: {AA3333}Not Passed");

	if (PlayerData[playerid][pLicense][2]) SendClientMessageEx(userid, COLOR_WHITE, "Lumberjack License: {33CC33}Passed");
	else SendClientMessageEx(userid, COLOR_WHITE, "Lumberjack License: {AA3333}Not Passed");

	if (PlayerData[playerid][pLicense][3]) SendClientMessageEx(userid, COLOR_WHITE, "Hauling License: {33CC33}Passed");
	else SendClientMessageEx(userid, COLOR_WHITE, "Hauling License: {AA3333}Not Passed");

	SendClientMessage(userid, COLOR_GREY, "-----------------------------------------------------------");
	SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s takes out their licenses and shows them to %s.", ReturnName(playerid), ReturnName(userid));
	return 1;
}

CMD:id(playerid, params[])
{
	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/id [playerid/name]");

	if (strlen(params) < 3)
		return SendErrorMessage(playerid, "You must specify at least 3 characters.");

	new count;

	foreach (new i : Player)
	{
	    if (strfind(GetName(i), params, true) != -1)
	    {
			new version_ret[64];
			if(IsPlayerUsingAndroid(i)) {
				version_ret = "Mobile";
			}
			else {
				GetPlayerVersion(i, version_ret, 64);
			}
	        SendClientMessageEx(playerid, -1, "- [ID:%d] "WHITE"%s | "LIGHTBLUE"Ping: "WHITE"%dms | "LIGHTBLUE"Packetloss: "WHITE"%.2f | "LIGHTBLUE"Client: "WHITE"%s", i, GetName(i, false), GetPlayerPing(i), NetStats_PacketLossPercent(i), version_ret);
	        count++;
		}
	}
	if (!count)
	    return SendErrorMessage(playerid, "No users matched the search criteria: \"%s\".", params);

	return 1;
}

CMD:admins(playerid, params[])
{
	new count = 0;

    SendClientMessage(playerid, X11_WHITE, ""GREY"============ [ "WHITE"Online Administrator "GREY"] ============");
	foreach(new i : Player) if(PlayerData[i][pAdmin] && !PlayerData[i][pAhide]) {

		new p_status[34];

		if(PlayerData[i][pAduty]) {
			p_status = ""RED"Admin Duty";
		}
		else {
			if(IsPlayerPaused(i)) {
				p_status = ""GOLD"Alt-tabbing";
			}
			else if(PlayerData[i][pAFK]) {
				p_status = ""GOLD"Away from Keyboard";
			}
			else {
				p_status = ""LIGHTGREEN"Roleplaying";
			}
		}
		SendClientMessageEx(playerid, X11_WHITE, ""TOMATO"%s "WHITE": %s(ID:%d) [ Status: %s"WHITE" ]", GetAdminRank(i), GetUsername(i), i, p_status);
		count++;
	}

	if(!count)
		SendErrorMessage(playerid, "There is no administrator online.");

	return 1;
}

CMD:pr(playerid, params[])
{

	if(PlayerData[playerid][pInjured])
		return SendErrorMessage(playerid, "Kamu sedang injured dan tidak dapat menggunakan radio!");
		
    if (!Inventory_Count(playerid, "Portable Radio"))
	    return SendErrorMessage(playerid, "You must have a portable radio.");
	    
	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/pr [radio chat]"), SendClientMessage(playerid, COLOR_LIGHTRED, "(Warning) {FFFFFF}Radio chat is only for IC purposes!");

	if (!PlayerData[playerid][pChannel])
	    return SendErrorMessage(playerid, "Your portable radio is disabled (/setfreq).");

	new
	    stringz[128], string[128];
		
	format(stringz, sizeof(stringz), "<RADIO> %s", params);
 	SetPlayerChatBubble(playerid, stringz, 0xFFFF90FF, 30.0, 5000);

 	foreach(new i : Player) if(PlayerData[i][pChannel] == PlayerData[playerid][pChannel] && Inventory_Count(i, "Portable Radio"))
	{
		if(strlen(params) > 64)
		{
			if(liveMode[i]) {
				format(string, sizeof(string), "[CH] %s: %.64s", GetName(playerid, false), params);
				SendClientMessageEx(i, 0xFFFF90FF, string);
			}
			else {
				format(string, sizeof(string), "[CH %d] %s: %.64s", PlayerData[playerid][pChannel], GetName(playerid, false), params);
				SendClientMessageEx(i, 0xFFFF90FF, string);
			}

			format(string, sizeof(string), "...%s", params[64]);
			SendClientMessageEx(i, 0xFFFF90FF, string);
		}
		else
		{
			if(liveMode[i]) {
				format(string, sizeof(string), "[CH] %s: %s", GetName(playerid, false), params);
				SendClientMessageEx(i, 0xFFFF90FF, string);	
			}
			else {
				format(string, sizeof(string), "[CH %d] %s: %s", PlayerData[playerid][pChannel], GetName(playerid, false), params);
				SendClientMessageEx(i,0xFFFF90FF, string);	
			}
		}
	}
	return 1;
}

CMD:setfreq(playerid, params[])
{
	new channel;

    if (!Inventory_Count(playerid, "Portable Radio"))
	    return SendErrorMessage(playerid, "You must have a portable radio.");

	if (sscanf(params, "d", channel))
 	{       
	 	SendSyntaxMessage(playerid, "/setfreq [radio channel] (0 to disable)");

	 	if (PlayerData[playerid][pChannel] > 0)
			SendClientMessageEx(playerid, COLOR_YELLOW, "(Note){FFFFFF} Your current radio channel is set to %d.", PlayerData[playerid][pChannel]);

		return 1;
	}
	if (channel < 0 || channel > 999999)
	    return SendErrorMessage(playerid, "The channel can't be below 0 or above 999,999.");

	if(channel == 911 && GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "This frequency only for Police Departement.");
		
	PlayerData[playerid][pChannel] = channel;

	if (channel == 0)
	    SendServerMessage(playerid, "You have disabled your portable radio.");

	else SendServerMessage(playerid, "You have set your radio's channel to %d (\"/pr [text]\" to chat).", channel);
	return 1;
}

CMD:levelinfo(playerid, params[]) {
	

	new nxtlevel = PlayerData[playerid][pLevel] + 1,
		expamount = nxtlevel * 3;

	SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Level) "WHITE"Kamu membutuhkan %d jam lagi untuk ke level selanjutnya.", expamount - PlayerData[playerid][pExp]);
	return 1;
}


CMD:shout(playerid, params[])
	return cmd_s(playerid, params);

CMD:s(playerid, params[])
{
	if(PlayerData[playerid][pInjured])
		return SendErrorMessage(playerid, "Tidak bisa berteriak ketika injured.");

    if(isnull(params)) 
		return SendSyntaxMessage(playerid, "/(s)hout [shout text]");

	if(PlayerData[playerid][pDrugCondition]) {

		new
			len = strlen(params);

		static const charset[] = "qwertyuiopasdfghjklzxcvbnm";

		for(new i = 0; i < len / 2; i++) {

			params[i] = (charset[random(sizeof charset)]);
		}
	}

    new
        line_1[56],
        line_2[84],
		id = -1
    ;

    format(line_1, sizeof(line_1), "%.48s ..", params);
    format(line_2, sizeof(line_2), ".. %s", params[48]);
    line_1[0] = toupper(line_1[0]);


	if (strlen(params) > 64)
	{
		ProxDetector(playerid, 30.0, X11_WHITE, sprintf("%s shouts: %s", ReturnName(playerid), line_1));
		ProxDetector(playerid, 30.0, X11_WHITE, sprintf("%s!", line_2));

		if((id = Business_Nearest(playerid, 3.0)) != -1) {
			ProxDetectorOnPosition(BizData[id][bizInt][0], BizData[id][bizInt][1], BizData[id][bizInt][2], BizData[id][bizInterior], BizData[id][bizWorld], 15.0, X11_WHITE, sprintf("%s shouts(from outside): %s", ReturnName(playerid), line_1));
			ProxDetectorOnPosition(BizData[id][bizInt][0], BizData[id][bizInt][1], BizData[id][bizInt][2], BizData[id][bizInterior], BizData[id][bizWorld], 15.0, X11_WHITE, sprintf("%s!", line_2));
		}
		if((id = PlayerData[playerid][pInBiz]) != -1) {
			ProxDetectorOnPosition(BizData[id][bizExt][0], BizData[id][bizExt][1], BizData[id][bizExt][2], 0, 0, 15.0, X11_WHITE, sprintf("%s shouts(from inside): %s", ReturnName(playerid), line_1));
			ProxDetectorOnPosition(BizData[id][bizExt][0], BizData[id][bizExt][1], BizData[id][bizExt][2], 0, 0, 15.0, X11_WHITE, sprintf("%s!", line_2));
		}
		if((id = House_Nearest(playerid)) != -1) {
			ProxDetectorOnPosition(HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2], HouseData[id][houseInterior], HouseData[id][houseID] + 5000, 15.0, X11_WHITE, sprintf("%s shouts(from outside): %s", ReturnName(playerid), line_1));
			ProxDetectorOnPosition(HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2], HouseData[id][houseInterior], HouseData[id][houseID] + 5000, 15.0, X11_WHITE, sprintf("%s!", line_2));
		}
		if((id = House_Inside(playerid)) != -1 && IsPlayerInRangeOfPoint(playerid, 3.0, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2])) {
			ProxDetectorOnPosition(HouseData[id][housePos][0], HouseData[id][housePos][1], HouseData[id][housePos][2], 0, 0, 15.0, X11_WHITE, sprintf("%s shouts(from inside): %s", ReturnName(playerid), line_1));
			ProxDetectorOnPosition(HouseData[id][housePos][0], HouseData[id][housePos][1], HouseData[id][housePos][2], 0, 0, 15.0, X11_WHITE, sprintf("%s!", line_2));
		}
		if((id = Flat_Exterior(playerid)) != -1) {
			ProxDetectorOnPosition(FlatData[id][flatInt][0], FlatData[id][flatInt][1], FlatData[id][flatInt][2], FlatData[id][flatIntInterior], FlatData[id][flatIntWorld], 15.0, X11_WHITE, sprintf("%s shouts(from outside): %s", ReturnName(playerid), line_1));
			ProxDetectorOnPosition(FlatData[id][flatInt][0], FlatData[id][flatInt][1], FlatData[id][flatInt][2], FlatData[id][flatIntInterior], FlatData[id][flatIntWorld], 15.0, X11_WHITE, sprintf("%s!", line_2));
		}
		if((id = Flat_Interior(playerid)) != -1) {
			ProxDetectorOnPosition(FlatData[id][flatPos][0], FlatData[id][flatPos][1], FlatData[id][flatPos][2], FlatData[id][flatExtInterior], FlatData[id][flatExtWorld], 15.0, X11_WHITE, sprintf("%s shouts(from inside): %s", ReturnName(playerid), line_1));
			ProxDetectorOnPosition(FlatData[id][flatPos][0], FlatData[id][flatPos][1], FlatData[id][flatPos][2], FlatData[id][flatExtInterior], FlatData[id][flatExtWorld], 15.0, X11_WHITE, sprintf("%s!", line_2));
		}
	}
	else
	{
		ProxDetector(playerid, 30.0, X11_WHITE, sprintf("%s shouts: %s!", ReturnName(playerid), params));

		if((id = Business_Nearest(playerid, 3.0)) != -1) {
			ProxDetectorOnPosition(BizData[id][bizInt][0], BizData[id][bizInt][1], BizData[id][bizInt][2], BizData[id][bizInterior], BizData[id][bizWorld], 15.0, X11_WHITE, sprintf("%s shouts(from outside): %s!", ReturnName(playerid), params));
		}
		if((id = PlayerData[playerid][pInBiz]) != -1) {
			ProxDetectorOnPosition(BizData[id][bizExt][0], BizData[id][bizExt][1], BizData[id][bizExt][2], 0, 0, 15.0, X11_WHITE, sprintf("%s shouts(from inside): %s!", ReturnName(playerid), params));
		}
		if((id = House_Nearest(playerid)) != -1) {
			ProxDetectorOnPosition(HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2], HouseData[id][houseInterior], HouseData[id][houseID] + 5000, 15.0, X11_WHITE, sprintf("%s shouts(from outside): %s!", ReturnName(playerid), params));
		}
		if((id = House_Inside(playerid)) != -1 && IsPlayerInRangeOfPoint(playerid, 3.0, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2])) {
			ProxDetectorOnPosition(HouseData[id][housePos][0], HouseData[id][housePos][1], HouseData[id][housePos][2], 0, 0, 15.0, X11_WHITE, sprintf("%s shouts(from inside): %s!", ReturnName(playerid), params));
		}
		if((id = Flat_Exterior(playerid)) != -1) {
			ProxDetectorOnPosition(FlatData[id][flatInt][0], FlatData[id][flatInt][1], FlatData[id][flatInt][2], FlatData[id][flatIntInterior], FlatData[id][flatIntWorld], 15.0, X11_WHITE, sprintf("%s shouts(from outside): %s!", ReturnName(playerid), params));
		}
		if((id = Flat_Interior(playerid)) != -1) {
			ProxDetectorOnPosition(FlatData[id][flatPos][0], FlatData[id][flatPos][1], FlatData[id][flatPos][2], FlatData[id][flatExtInterior], FlatData[id][flatExtWorld], 15.0, X11_WHITE, sprintf("%s shouts(from inside): %s!", ReturnName(playerid), params));
		}
	}
    return 1;
}
CMD:health(playerid, params[])
{
	if(!PlayerData[playerid][pSpawned])
	    return SendErrorMessage(playerid, "You're not spawned.");
	    
	new targetid;
	if(sscanf(params, "u", targetid))
	{
		DisplayHealth(playerid, playerid);
		return 1;
	}
	if (targetid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, targetid, 5.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");
	    
	DisplayHealth(targetid, playerid);
	SendServerMessage(playerid, "You have showing your body status to {FFFF00}%s", ReturnName(targetid));
	return 1;
}

CMD:accept(playerid, params[])
{
	if(isnull(params))
		return SendSyntaxMessage(playerid, "/accept [Options]"), SendClientMessage(playerid, COLOR_SERVER, "(Option) {FFFFFF}death, frisk, drag, vehicle, flat, house, marriage");

	if(!strcmp(params, "death", true))
	{
		new hours, minutes, seconds;
		GetElapsedTime(PlayerData[playerid][pInjuredTime], hours, minutes, seconds);

		if(!PlayerData[playerid][pInjured])
			return SendErrorMessage(playerid, "You are not injured at the moment.");

		if(PlayerData[playerid][pInjuredTime] > 0 && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, "Kamu harus menunggu %02d menit dan %02d detik untuk accept death!", minutes, seconds);

		if(CountPlayerShootWound(playerid) > 0) {
			
			TogglePlayerControllable(playerid, 1);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

			SetPlayerHealth(playerid, 100);
			SetPlayerPos(playerid, -2655.2048,634.7786,14.4531);
			SetPlayerFacingAngle(playerid, 179.1246);
			SetCameraBehindPlayer(playerid);
			SendServerMessage(playerid, "You have been respawned at {FFFF00}San Fierro Hospital {FFFFFF}and fined {FF0000}$50.00");
			GiveMoney(playerid, -5000, "Bayar hospital");
			ResetWeapons(playerid);
		}
		else {
			SendServerMessage(playerid, "Kamu dibangunkan ditempat karena tidak ada luka tembak pada tubuhmu.");
			SetPlayerHealth(playerid, 50.0);
			PlayerData[playerid][pInjured] = false;
			PlayerData[playerid][pDead] = false;
			ClearAnimations(playerid, 1);
		}

		ResetPlayerDamages(playerid);
		PlayerData[playerid][pInjured] = false;
		PlayerData[playerid][pDead] = false;
		ClearAnimations(playerid, 1);

		Damage_Reset(playerid);
		SetCameraBehindPlayer(playerid);
	
		RemoveDrag(playerid);

		DragCheck(playerid);
	}
	else if(!strcmp(params, "divorce", true)) {
		if(DivorceOffer[playerid] == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid, "No one is asking you for a divorce.");

		new targetid = DivorceOffer[playerid];


		if(!IsPlayerNearPlayer(playerid, targetid, 5.0))
			return SendErrorMessage(playerid, "You are not near player that divorcing you.");	

		format(MarryWith[playerid], 24, "Unknown");
		format(MarryWith[targetid], 24, "Unknown");
		format(MarryDate[playerid], 28, "_");
		format(MarryDate[targetid], 28, "_");

		SendClientMessageEx(targetid, X11_LIGHTBLUE, "(Divorce) "YELLOW"%s "WHITE"is accepting your divorce offer, you are no longer married with "YELLOW"%s", ReturnName(playerid), ReturnName(playerid));
		SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Divorce) "WHITE"You have accepted the divorce offer, you are no longer married with "YELLOW"%s", ReturnName(targetid));

		DivorceOffer[playerid] = INVALID_PLAYER_ID;
	}
	else if(!strcmp(params, "marriage", true)) {
		if(MarryOffer[playerid] == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid, "No one is proposing you.");

		new targetid = MarryOffer[playerid];

		if(!IsPlayerNearPlayer(playerid, targetid, 5.0))
			return SendErrorMessage(playerid, "You are not near player that proposing you.");

		format(MarryWith[playerid], 24, "%s", GetName(targetid));
		format(MarryWith[targetid], 24, "%s", GetName(playerid));
		format(MarryDate[playerid], 28, "%s", ReturnDate());
		format(MarryDate[targetid], 28, "%s", ReturnDate());

		GiveMoney(targetid, -200000, "Marriage");
		serverVault += 200000;

		SendClientMessageToAllEx(-1, ""GREY_SAMP"MARRIAGE: "WHITE"Please congratulate to our new "CYAN"couple");
		SendClientMessageToAllEx(-1, ""GREY_SAMP"MARRIAGE: "YELLOW"%s "WHITE"and "YELLOW"%s", GetName(targetid, false), GetName(playerid, false));

		MarryOffer[playerid] = INVALID_PLAYER_ID;
	}
	else if(!strcmp(params, "house", true)) {

		new sellerid = PlayerData[playerid][pHouseOfferID],
			houseid = PlayerData[playerid][pHouseOffer];

		if(sellerid == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid, "Tidak ada yang menawarkanmu flat.");

		if(!IsPlayerConnected(sellerid))
			return SendErrorMessage(playerid, "Player yang menawarkanmu flat tidak lagi diserver.");

		if(!House_IsOwner(sellerid, houseid))
			return SendErrorMessage(playerid, "Rumah tersebut tidak lagi milik %s.", ReturnName(sellerid));

		HouseData[houseid][houseOwner] = PlayerData[playerid][pID];
		format(HouseData[houseid][houseOwnerName], 64, PlayerData[playerid][pName]);

		HouseData[houseid][houseTaxDate] = gettime() + (14 * 86400);
		HouseData[houseid][houseTaxState] = TAX_STATE_COOLDOWN;
		HouseData[houseid][houseTaxPaid] = true;

		Log_Write("Logs/give_veh.txt", "[%s] %s(%s) accept house(ID:%d) from %s(%s)", ReturnDate(), GetName(playerid,false), GetUsername(playerid), houseid, GetName(sellerid), GetUsername(sellerid));

		House_Refresh(houseid);
		House_Save(houseid);
		SendServerMessage(playerid, "Kamu menerima tawaran kunci rumah dari %s.", ReturnName(sellerid));
		SendServerMessage(sellerid, "%s telah menerima tawaran kunci rumah, sekarang rumah tersebut miliknya.", ReturnName(playerid));


		PlayerData[playerid][pHouseOffer] = -1;
		PlayerData[playerid][pHouseOfferID] = INVALID_PLAYER_ID;
	}
	else if(!strcmp(params, "flat", true)) {

		new sellerid = PlayerData[playerid][pFlatOfferID],
			flatid = PlayerData[playerid][pFlatOffer];

		if(sellerid == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid, "Tidak ada yang menawarkanmu flat.");

		if(!IsPlayerConnected(sellerid))
			return SendErrorMessage(playerid, "Player yang menawarkanmu flat tidak lagi diserver.");

		if(!Flat_IsOwner(sellerid, flatid))
			return SendErrorMessage(playerid, "Flat tersebut tidak lagi milik %s.", ReturnName(sellerid));

		FlatData[flatid][flatOwner] = PlayerData[playerid][pID];
		format(FlatData[flatid][flatOwnerName], MAX_PLAYER_NAME, GetName(playerid));

		FlatData[flatid][flatTaxDate] = gettime() + (14 * 86400);
		FlatData[flatid][flatTaxState] = TAX_STATE_COOLDOWN;
		FlatData[flatid][flatTaxPaid] = true;

		Flat_Sync(flatid);
		Flat_Save(flatid);

		Log_Write("Logs/give_veh.txt", "[%s] %s(%s) accept flat (ID:%d) from %s(%s)", ReturnDate(), GetName(playerid,false), GetUsername(playerid), flatid, GetName(sellerid), GetUsername(sellerid));

		SendServerMessage(playerid, "Kamu menerima tawaran kunci flat dari %s.", ReturnName(sellerid));
		SendServerMessage(sellerid, "%s telah menerima tawaran kunci flat, sekarang flat tersebut miliknya.", ReturnName(playerid));

		PlayerData[playerid][pFlatOffer] = -1;
		PlayerData[playerid][pFlatOfferID] = INVALID_PLAYER_ID;
	}
	else if(!strcmp(params, "vehicle", true)) {

		new sellerid = PlayerData[playerid][pVehicleOfferID],
			vehicleid = PlayerData[playerid][pVehicleOffer];

		if(sellerid == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid, "Tidak ada yang menawarkanmu kendaraan.");

		if(!IsPlayerConnected(sellerid))
			return SendErrorMessage(playerid, "Player yang menawarkanmu kendaraan tidak lagi diserver.");

		if(!Vehicle_IsOwner(sellerid, vehicleid))
			return SendErrorMessage(playerid, "Kendaraan tersebut tidak lagi milik %s.", ReturnName(sellerid));

		Vehicle_RemoveOwner(vehicleid);
		Vehicle_SetOwner(vehicleid, playerid, true);
		SendServerMessage(playerid, "Kamu menerima tawaran kunci kendaraan %s dari %s.", GetVehicleName(vehicleid), ReturnName(sellerid));
		SendServerMessage(sellerid, "%s telah menerima tawaran kunci %s, sekarang kendaraan tersebut miliknya.", ReturnName(playerid), GetVehicleName(vehicleid));

		Log_Write("Logs/give_veh.txt", "[%s] %s(%s) accept vehicle(%s) from %s(%s)", ReturnDate(), GetName(playerid,false), GetUsername(playerid), GetVehicleName(vehicleid), GetName(sellerid), GetUsername(sellerid));

		PlayerData[playerid][pVehicleOffer] = -1;
		PlayerData[playerid][pVehicleOfferID] = INVALID_PLAYER_ID;

	}
	else if(!strcmp(params, "drag", true))
	{
		new dragerid = PlayerData[playerid][pDragOffer];
		if(dragerid == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid, "No one offered you a drag request!");

		IsDragging[dragerid] = playerid;

		SendNearbyMessage(dragerid, 20.0, X11_PLUM, "** %s grabs hold of %s and starts dragging them.", ReturnName(dragerid), ReturnName(playerid));
		SendServerMessage(dragerid, "You are now start dragging {FFFF00}%s {FFFFFF}type {00FFFF}/undrag {FFFFFF}to stop.", ReturnName(dragerid));
	}
	else if(!strcmp(params, "frisk", true))
	{
		new targetid = PlayerData[playerid][pFrisked];
		if(targetid == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid, "No one ask you for a frisk!");

		ShowInventory(targetid, playerid);

		if(PlayerData[playerid][pInjured] && !PlayerData[targetid][pAdmin]) 
			SendClientMessage(targetid, X11_TOMATO, "(Warning) "WHITE"Dilarang untuk looting player yang sedang injured!");
			
		PlayerData[playerid][pFrisked] = INVALID_PLAYER_ID;
	}
	return 1;
}


CMD:disablecp(playerid, params[])
{


	HideWaypoint(playerid);
	DisablePlayerRaceCheckpoint(playerid);
	DisablePlayerCheckpoint(playerid);
	SendServerMessage(playerid, "You have disabled any active checkpoints.");
	return 1;
}

CMD:o(playerid, params[])
{
    if(ToggleData[togOOC] && PlayerData[playerid][pAdmin] < 1)
        return SendErrorMessage(playerid, "Perintah ini dinonaktifkan sementara.");

    if(isnull(params))
        return SendSyntaxMessage(playerid, "/o [Global OOC]");

    if(PlayerData[playerid][pTogGlobal])
        return SendErrorMessage(playerid, "Aktifkan OOC chatmu terlebih dahulu dengan perintah /toggle.");

    if(strlen(params) > 120)
        return SendClientMessage(playerid, -1, "Text terlalu panjang, maksimal 120 karakter.");

    foreach (new i : Player) if(!PlayerData[i][pTogGlobal] && IsPlayerSpawned(i))
    {
        if(PlayerData[playerid][pAduty] && PlayerData[playerid][pAdmin])
            SendClientMessageEx(i, -1, "(( "RED"Admin %s"WHITE" (%d): %s ))", GetName(playerid, false), playerid, params);

        else
        {
            new vip_level = GetPlayerVIPLevel(playerid);
            new chat_color[][] = {LIGHTBLUE, CYAN, YELLOW, GOLD};

			SendClientMessageEx(i, -1, "(( %s%s %s"WHITE" (%d): %s ))", chat_color[vip_level], GetGlobalRank(playerid), GetName(playerid, false), playerid, params);
        }
    }
    return 1;
}


CMD:b(playerid, params[])
{

    if(isnull(params))
        return SendSyntaxMessage(playerid, "/b [local OOC]");

    if(strlen(params) > 64)
    {
        if(PlayerData[playerid][pAduty])
        {
            SendNearbyMessage(playerid, 15.0, 0xFF0000FF, "%s:"WHITE" (( %.64s ..", ReturnName(playerid), params);
            SendNearbyMessage(playerid, 15.0, X11_WHITE, ".. %s "WHITE"))", params[64]);
            return 1;
        }
        else
        {
            ProxDetector(playerid, 15.0, X11_WHITE, sprintf("%s: (( %.64s ..", ReturnName(playerid), params));
            ProxDetector(playerid, 15.0, X11_WHITE, sprintf(".. %s ))", params[64]));
            return 1;
        }
    }
    else
    {
        if(PlayerData[playerid][pAduty])
            return SendNearbyMessage(playerid, 15.0, 0xFF0000FF, "%s:"WHITE" (( %s ))", ReturnName(playerid), params);

        ProxDetector(playerid, 13.0, X11_WHITE, sprintf("%s: (( %s ))", ReturnName(playerid), params));
    }
    return 1;
}

CMD:me(playerid, params[])
{

	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/me [action]");

	if (strlen(params) > 64)
	{
	    SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s %.64s", ReturnName(playerid), params);
	    SendNearbyMessage(playerid, 30.0, X11_PLUM, "...%s", params[64]);
	}
	else
	{
	    SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s %s", ReturnName(playerid), params);
	}
	return 1;
}

CMD:lme(playerid, params[])
{
    if(isnull(params))
        return SendSyntaxMessage(playerid, "/lme [action]");

    if(strlen(params) > 64) {
        SendNearbyMessage(playerid, 8.0, 0xD0AEEBFF, "* %s %.64s ..", ReturnName(playerid), params);
        SendNearbyMessage(playerid, 8.0, 0xD0AEEBFF, ".. %s", params[64]);
    }
    else {
        SendNearbyMessage(playerid, 8.0, 0xD0AEEBFF, "* %s %s", ReturnName(playerid), params);
    }
    return 1;
}

CMD:ldo(playerid, params[])
{
	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/ldo [description]");

	if (strlen(params) > 64) {
	    SendNearbyMessage(playerid, 9.0, 0xD0AEEBFF, "* %.64s", params);
	    SendNearbyMessage(playerid, 9.0, 0xD0AEEBFF, "...%s (( %s ))", params[64], ReturnName(playerid));
	}
	else 
	{
	    SendNearbyMessage(playerid, 9.0, 0xD0AEEBFF, "* %s (( %s ))", params, ReturnName(playerid));
	}
    return 1;
}

CMD:ame(playerid, params[])
{
	new
	    string[128];

	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/ame [action]");

	format(string, sizeof(string), "* %s",  params);
 	SetPlayerChatBubble(playerid, string, X11_PLUM, 30.0, 5000);

 	SendClientMessageEx(playerid, COLOR_WHITE, "* [AME]: {D0AEEB}%s", params);
	return 1;
}

CMD:low(playerid, params[])
	return cmd_l(playerid, params);

CMD:l(playerid, params[])
{
    if(isnull(params))
        return SendSyntaxMessage(playerid, "/(l)ow [low text]");

	if(PlayerData[playerid][pDrugCondition]) {

		new
			len = strlen(params);

		static const charset[] = "qwertyuiopasdfghjklzxcvbnm";

		for(new i = 0; i < len / 2; i++) {

			params[i] = (charset[random(sizeof charset)]);
		}
	}

    new
        line_1[56],
        line_2[84]
    ;

    format(line_1, sizeof(line_1), "%.48s ..", params);
    format(line_2, sizeof(line_2), ".. %s", params[48]);

    if(strlen(params) < 128) 
    {
        params[0] = toupper(params[0]);
		if (strlen(params) > 48)
		{

			ProxDetector(playerid, 5.0, X11_WHITE, sprintf("[low] %s says: %s", ReturnName(playerid), line_1));
			ProxDetector(playerid, 5.0, X11_WHITE, sprintf("[low] %s", line_2));
		}
		else
		{
			ProxDetector(playerid, 5.0, X11_WHITE, sprintf("[low] %s says: %s", ReturnName(playerid), params));
		}
    }
    return 1;
}
CMD:do(playerid, params[])
{
	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/do [description]");

	if (strlen(params) > 64) {
	    SendNearbyMessage(playerid, 30.0, X11_PLUM, "* %.64s", params);
	    SendNearbyMessage(playerid, 30.0, X11_PLUM, "...%s (( %s ))", params[64], ReturnName(playerid));
	}
	else 
	{
	    SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s (( %s ))", params, ReturnName(playerid));
	}
	return 1;
}

CMD:answer(playerid, params[])
{
	if (!PlayerData[playerid][pIncomingCall])
	    return SendErrorMessage(playerid, "There are no incoming calls to accept.");

	if (PlayerData[playerid][pCuffed])
	    return SendErrorMessage(playerid, "You can't use this command at the moment.");

    if (PlayerData[playerid][pPhoneOff])
    	return SendErrorMessage(playerid, "Your phone must be powered on.");

	new targetid = PlayerData[playerid][pCallLine];

	PlayerData[playerid][pIncomingCall] = 0;
	PlayerData[targetid][pIncomingCall] = 0;

    SendClientMessageEx(playerid, X11_GREY, "Kamu telah menerima panggilan, gunakan text chat biasa untuk berkomunikasi.");
    SendClientMessageEx(targetid, X11_GREY, "Penerima telah menerima panggilan, gunakan text chat biasa untuk berkomunikasi.");

	SendNearbyMessage(playerid, 10.0, X11_PLUM, "** %s has accepted the incoming call.", ReturnName(playerid));
	if(!IsPlayerInAnyVehicle(playerid))
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);

	SetPlayerAttachedObject(playerid, 3, 18867, 6, 0.0909, -0.0030, 0.0000, 80.4001, 159.8000, 18.0000, 1.0000, 1.0000, 1.0000, 0xFFFFFFFF, 0xFFFFFFFF);
	return 1;
}

CMD:h(playerid, params[])
	return cmd_hangup(playerid, "");

CMD:hangup(playerid, params[])
{
	new targetid = PlayerData[playerid][pCallLine];

	if (targetid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "There are no calls to hangup.");

	if (PlayerData[playerid][pIncomingCall])
	{
	    SendClientMessage(playerid, X11_GREY, "Kamu telah menolak panggilan yang masuk...");
	    SendClientMessage(targetid, X11_GREY, "Panggilanmu ditolak oleh penerima...");
	    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
	    RemovePlayerAttachedObject(playerid, 3);
	}
	else
	{
        SendClientMessage(playerid, X11_GREY, "Kamu telah mengakhiri panggilan...");
	    SendClientMessage(targetid, X11_GREY, "Panggilan berakhir...");

	    SendNearbyMessage(playerid, 10.0, X11_PLUM, "** %s has hung up their cellphone.", ReturnName(playerid));
	    SendNearbyMessage(targetid, 10.0, X11_PLUM, "** %s has hung up their cellphone.", ReturnName(targetid));

	    SetPlayerSpecialAction(targetid, SPECIAL_ACTION_STOPUSECELLPHONE);
	    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
	    RemovePlayerAttachedObject(playerid, 3);
	    RemovePlayerAttachedObject(targetid, 3);

	}
	PlayerData[playerid][pIncomingCall] = 0;
	PlayerData[targetid][pIncomingCall] = 0;
	ServiceIndex[playerid] = 0;
	PlayerData[playerid][pCallLine] = INVALID_PLAYER_ID;
	PlayerData[targetid][pCallLine] = INVALID_PLAYER_ID;
	PlayerData[playerid][pCalling] = INVALID_PLAYER_ID;
	PlayerData[targetid][pCalling] = INVALID_PLAYER_ID;
	return 1;
}

CMD:autotreatment(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 4.5, -1436.1725,-1528.6896,3001.5059))
		return SendErrorMessage(playerid, "Kamu tidak berada di Hospital!");

	if(CountFaction(FACTION_MEDIC) >= 1)
		return SendErrorMessage(playerid, "Kamu bisa melakukan command ini hanya jika tidak ada SFFD Onduty!");

	if(GetMoney(playerid) < 15000)
		return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang!");
		
	GiveMoney(playerid, -15000, "Autotreatment");
	SetPlayerHealth(playerid, 100.0);
	PlayerData[playerid][pHealthy] = 100.0;
	PlayerData[playerid][pCough] = 0;
	PlayerData[playerid][pFever] = 0;
	PlayerData[playerid][pFeverRate] = 0;

	SendServerMessage(playerid, "Kamu berhasil melakukan autotreatment!");
	serverVault += 15000;

	SetPlayerDrunkLevelEx(playerid, 0);
	return 1;
}

CMD:stats(playerid, params[])
{
	ShowPlayerStats(playerid, playerid);
	return 1;
}


CMD:deleteado(playerid, params[])
{
	if(!IsValidDynamic3DTextLabel(PlayerData[playerid][pAdoLabel]))
		return SendErrorMessage(playerid, "You don't have placed ADO!");

	RemovePlayerADO(playerid);
	SendServerMessage(playerid, "You have removed your placed ADO");
	return 1;
}
CMD:ado(playerid, params[])
{
    static
		msg[128],
		Float:x,
		Float:y,
		Float:z;

    GetPlayerPos(playerid, x, y, z);

	if (sscanf(params,"s[128]",msg))
		return SendSyntaxMessage(playerid, "/ado [text]");

	SendClientMessage(playerid,COLOR_GREY,"(Info) {FFFFFF}ADO Has been placed, use {FFFF00}/deleteado {FFFFFF}to remove your ADO.");

	RemovePlayerADO(playerid);
	PlayerData[playerid][pAdoLabel] = CreateDynamic3DTextLabel(sprintf("%s\n(( %s ))", msg, ReturnName(playerid)), X11_PLUM, x, y, z, 20);
	return 1;
}

CMD:drag(playerid, params[])
{
	if(IsDragging[playerid] != INVALID_PLAYER_ID) 
		return SendErrorMessage(playerid,"You are already dragging someone.");

	if(IsPlayerInAnyVehicle(playerid)) 
		return SendErrorMessage(playerid,"You can't drag from inside a vehicle.");

	new targetid;
	if(sscanf(params, "u", targetid)) 
		return SendSyntaxMessage(playerid, "/drag [playerid/PartOfName]");

	if(targetid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "You have specified invalid player!");

	if(!IsPlayerNearPlayer(playerid, targetid, 5.0))
		return SendErrorMessage(playerid, "You must close to this player!");

	if(IsPlayerInAnyVehicle(targetid))
		return SendErrorMessage(playerid, "The target must be onfoot!");

	foreach(new i: Player)
	{
		if(IsDragging[i] == targetid) 
			return SendErrorMessage(playerid, "That player is already dragged by someone!");
	}

	SendServerMessage(targetid, "%s has offered to drag you (type \"/accept drag\").", ReturnName(playerid));
	SendServerMessage(playerid, "You have offering drag to %s, please wait for the respond.", ReturnName(targetid));
	PlayerData[targetid][pDragOffer] = playerid;
	return true;
}
CMD:undrag(playerid, params[])
{

	if(IsDragging[playerid] == INVALID_PLAYER_ID) 
		return SendErrorMessage(playerid,"You are not dragging anyone.");

	new targetid = IsDragging[playerid];
	TogglePlayerControllable(targetid, 1);
	SendNearbyMessage(playerid, 20.0, X11_PLUM, "** %s releases their grip on %s and lets them go.", ReturnName(playerid), ReturnName(targetid));
	IsDragging[playerid] = INVALID_PLAYER_ID;
	return true;
}

CMD:buycomponent(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, -1862.1053,-145.7666,11.8984))
		return SendErrorMessage(playerid, "Kamu tidak berada di Component Warehouse!");

	new amount;
	if(sscanf(params, "d", amount))
		return SendSyntaxMessage(playerid, "/buycomponent [amount]"), SendClientMessage(playerid, COLOR_YELLOW, "(Info) {FFFFFF}Harga component adalah {00FF00}$0.50 {FFFFFF}per 1 Component.");

	if(amount < 1)
		return SendErrorMessage(playerid, "Invalid component amount!");

	if(amount > 1000)
		return SendErrorMessage(playerid, "Tidak bisa lebih dari 1000 dalam satu kali pembelian.");

	if(StockData[stockComponent] < amount)
		return SendErrorMessage(playerid, "Stok komponen tidak mencukupi!");

	if(GetMoney(playerid) < amount*50)
		return SendErrorMessage(playerid, "You don't have enough money!");

	new success = Inventory_Add(playerid, "Component", 19627, amount);

	if(success == -1)
		return 1;

	GiveMoney(playerid, -amount*50, "Beli Component");
	SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Component) "WHITE"Berhasil membeli {FFFF00}%d component(s) "WHITE"dengan harga {00FF00}$%s", amount, FormatNumber(amount*50));
	StockData[stockComponent] -= amount;

	UpdateServerStock(SERVER_STOCK_COMPONENT);
	return 1;
}

CMD:pm(playerid, params[])
{
	new
	    targetid,
		msg[128];
	    
	if(sscanf(params, "us[128]", targetid, msg))
	    return SendSyntaxMessage(playerid, "/pm [playerid/PartOfName] [message]");

	if(targetid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Invalid player!");
	    
	if (strlen(msg) > 128)
	    return SendErrorMessage(playerid, "Cannot more than 128 Characters!");

	if(PlayerData[playerid][pTogPM])
	    return SendErrorMessage(playerid, "You must enabled your Private Message!");
	    
	if(PlayerData[targetid][pTogPM])
	    return SendErrorMessage(playerid, "That players has disabled Private Message!");
	    
	SendClientMessageEx(targetid, COLOR_YELLOW, "(( PM From %s[%d]: %s ))", GetName(playerid), playerid, msg);
	SendClientMessageEx(playerid, COLOR_YELLOW, "(( PM To %s[%d]: %s ))", GetName(targetid), targetid, msg);

	foreach(new i : Player) if(PlayerData[i][pAdmin] && PlayerData[i][pPMLog]) {

		SendClientMessageEx(i, X11_GREEN_YELLOW, "PM: %s (%d) to %s (%d): %s", GetName(playerid, false), playerid, GetName(targetid, false), targetid, msg);
	}
	PlayerPlaySound(targetid, 1085, 0.0, 0.0, 0.0);
	return 1;
}

CMD:help(playerid, params[])
{
	if(!PlayerData[playerid][pSpawned])
		return SendErrorMessage(playerid, "You're not spawned!");

	ShowPlayerDialog(playerid, DIALOG_HELP, DIALOG_STYLE_LIST, "Help Menu", "General Commands\nChat Commands\nJob Commands\nFaction Commands\nBusiness Commands\nHouse Commands\nFlat Commands\nBank Commands\nDealership Commands\nVehicle ShareKey Commands\nWorkshop Commands\nRace Commands\nMarriage Commands", "Select", "Close");
	return 1;
}

CMD:unimpound(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1378.8019,1557.6079,3001.0859))
		return SendErrorMessage(playerid, "You're not at SFPD lobby!");

	mysql_tquery(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehType` = '%d' AND `vehExtraID` = '%d' AND `vehState` = '%d' ORDER BY `vehID` ASC;", VEHICLE_TYPE_PLAYER, PlayerData[playerid][pID], VEHICLE_STATE_IMPOUNDED), "Vehicle_OnUnimpound", "d", playerid);
	return 1;	
}

CMD:buyplate(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1380.9594,1557.6090,3001.0859))
		return SendErrorMessage(playerid, "You're not at SFPD lobby!");

	new str[512], bool:found = false, count = 0;
	format(str, sizeof(str), "Model\tPrice\n");
	foreach(new i : Vehicle) if(IsValidVehicle(i) && Vehicle_IsOwner(playerid, i))
	{
		format(str, sizeof(str), "%s%s\t$150.00\n", str, ReturnVehicleModelName(VehicleData[i][vModel]));
		g_ListedVehicle[playerid][count++] = i;
		found = true;
	}
	if(found)
		ShowPlayerDialog(playerid, DIALOG_BUYPLATE, DIALOG_STYLE_TABLIST_HEADERS, "Vehicle Plate", str, "Buy", "Close");
	else
		SendErrorMessage(playerid, "You don't have any unnamed Vehicle Plate");

	return 1;
}

CMD:weapon(playerid, params[])
{
	new
	    type[24],
	    string[128],
	    weaponid = GetWeapon(playerid);

	if (sscanf(params, "s[24]S()[128]", type, string))
	{
	    SendSyntaxMessage(playerid, "/weapon [Name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "(Name){FFFFFF} give, view, attachment");
	    return 1;
	}
	if(!strcmp(type, "view", true))
	{
		new targetid;
		if(sscanf(string, "u", targetid))
		{
		    ShowWeapon(playerid, playerid);
		    return 1;
		}
		if(targetid == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid, "You're not close to that player!");
			
		if(!IsPlayerNearPlayer(playerid, targetid, 7.0))
			return SendErrorMessage(playerid, "You're not close to that player!");

		ShowWeapon(targetid, playerid);
		SendServerMessage(playerid, "You have showing your weapon list to {FFFF00}%s", ReturnName(targetid));
	}
	else if(!strcmp(type, "attachment", true))
	{
		if(!weaponid)
			return SendErrorMessage(playerid, "You are not holding any weapon.");

		if (EditingWeapon[playerid] != 0)
			return SendErrorMessage(playerid, "You are already editing a weapon attachment");

		if (!IsWeaponWearable(weaponid))
			return SendErrorMessage(playerid, "You can't edit this weapon attachment!");

		ShowPlayerDialog(playerid, DIALOG_HIDEGUN, DIALOG_STYLE_LIST, sprintf("%s Weapon Attachment", ReturnWeaponName(weaponid)), "Edit Attachment Position\nEdit Attachment Bone\nHide Weapon Attachment", "Select", "Close");
	}
	else if(!strcmp(type, "give", true))
	{

		new 
			targetid;

		new
		    ammo = PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]];

		if(sscanf(string, "u", targetid))
			return SendSyntaxMessage(playerid, "/weapon give [playerid/PartOfName]");

		if (!weaponid)
		    return SendErrorMessage(playerid, "You are not holding any weapon to pass.");

		if(targetid == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid, "You're not close to that player!");

		if(!IsPlayerNearPlayer(playerid, targetid, 7.0))
			return SendErrorMessage(playerid, "You're not close to that player!");

		if (targetid == playerid)
			return SendErrorMessage(playerid, "You can't give yourself a weapon.");

		if (PlayerData[targetid][pGuns][g_aWeaponSlots[weaponid]] != 0)
		    return SendErrorMessage(playerid, "That player has a weapon in the same slot already.");

		if(PlayerData[targetid][pLevel] < 3)
		    return SendErrorMessage(playerid, "That Player must level 3 first to holding weapon.");

		if(GetFactionType(playerid) == FACTION_POLICE && GetFactionType(targetid) != FACTION_POLICE)
			return SendErrorMessage(playerid, "You only can give weapon to police!");
				    
		PassWeaponToPlayer(targetid, weaponid, ammo, PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]], PlayerData[playerid][pHighVelocity][g_aWeaponSlots[weaponid]]);
		ResetWeapon(playerid, weaponid);
		SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s has passed their %s to %s.", GetName(playerid, false), ReturnWeaponName(weaponid), GetName(targetid, false));
		Log_Write("Logs/weapon_log.txt", "[%s] %s memberikan senjata %s kepada %s", ReturnDate(), GetName(playerid, false), ReturnWeaponName(weaponid), GetName(targetid, false));
	}
	return 1;
}

CMD:paycheck(playerid, params[])
{
	if(!IsAtBank(playerid))
		return SendErrorMessage(playerid, "Kamu tidak berada di Bank Point!");

	if(PlayerData[playerid][pPaycheck] > 0 && !PlayerData[playerid][pAduty])
		return SendErrorMessage(playerid, "Kamu harus menunggu %d menit untuk Paycheck!", PlayerData[playerid][pPaycheck]/60);

	new str[256];
	new taxval = PlayerData[playerid][pSalary]/100*GovData[govTax];
	format(str, sizeof(str), "{FFFFFF}Salary: {009000}$%s\n{FFFFFF}Tax: {FFFF00}-$%s {FF0000}(%d percent)\n{FFFFFF}Total Interest: {00FF00}$%s", FormatNumber(PlayerData[playerid][pSalary]), FormatNumber(taxval), GovData[govTax], FormatNumber(PlayerData[playerid][pSalary]-taxval));
	ShowPlayerDialog(playerid, DIALOG_PAYCHECK, DIALOG_STYLE_MSGBOX, "Paycheck", str, "Get", "Close");
	return 1;
}

CMD:transfer(playerid, params[])
{
    new id, cash[32];
    new dollars, cents, totalcash[25];

	if(!IsAtBank(playerid))
		return SendErrorMessage(playerid, "Kamu tidak berada di Bank Point!");
		
    if(sscanf(params, "us[32]", id, cash)) 
    	return SendSyntaxMessage(playerid, "/transfer [playerid/PartOfName] [amount (dollar.cents)]");

	if(PlayerData[playerid][pHour] < 2)
		return SendErrorMessage(playerid, "Minimal bermain 2 jam untuk melakukan ini.");

 	if(id == INVALID_PLAYER_ID)
 		return SendErrorMessage(playerid, "Invalid player specified.");

 	if(id == playerid)
 		return SendErrorMessage(playerid, "Tidak bisa transfer ke diri sendiri!");

    if(strfind(cash, ".", true) != -1)
    {
		sscanf(cash, "p<.>dd", dollars, cents);
		format(totalcash, sizeof(totalcash), "%d%02d", dollars, cents);

		if(strval(totalcash) < 1)
			return SendErrorMessage(playerid, "Jumlah tidak bisa kurang dari $1,00");

		if(strval(totalcash) > 5000000)
			return SendErrorMessage(playerid, "Jumlah tidak bisa diatas $50.000,00");

		if(PlayerData[playerid][pBank] < strval(totalcash))
			return SendErrorMessage(playerid, "Kamu tidak memiliki uang sebanyak itu di bank.");

       	PlayerData[playerid][pBank] -= strval(totalcash); 
		PlayerData[id][pBank] += strval(totalcash);
		SendClientMessageEx(playerid, COLOR_SERVER, "(Transfer) {FFFFFF}You have successfully transfer {00FF00}$%s {FFFFFF}to {FFFF00}", FormatNumber(strval(totalcash)), GetName(id));
		SendClientMessageEx(id, COLOR_SERVER, "(Transfer) {FFFFFF}You've received {00FF00}$%s {FFFFFF}from {FFFF00}%s", FormatNumber(strval(totalcash)), GetName(playerid));
		Log_Write("Logs/transfer_log.txt", "[%s] %s(%s) has transfer to %s(%s) with amount $%s", ReturnDate(), GetName(playerid, false), GetUsername(playerid), GetName(id, false), GetUsername(id), FormatNumber(strval(totalcash)));
	
		if(strval(totalcash) > 100000) {
			SendAdminDutyMessage(X11_YELLOW, "(TransferLog) "WHITE"%s(%s) transfer to %s(%s) with amount: "DARKGREEN"$%s", GetName(playerid, false), GetUsername(playerid), GetName(id, false), GetUsername(id), FormatNumber(strval(totalcash)));
		}
	}
	else
	{
		sscanf(cash, "d", dollars);
		format(totalcash, sizeof(totalcash), "%d00", dollars);

		if(strval(totalcash) < 1)
			return SendErrorMessage(playerid, "Jumlah tidak bisa kurang dari $1,00");

		if(strval(totalcash) > 5000000)
			return SendErrorMessage(playerid, "Jumlah tidak bisa diatas $50.000,00");

		if(PlayerData[playerid][pBank] < strval(totalcash))
			return SendErrorMessage(playerid, "Kamu tidak memiliki uang sebanyak itu di bank.");

       	PlayerData[playerid][pBank] -= strval(totalcash); 
		PlayerData[id][pBank] += strval(totalcash);
		SendClientMessageEx(playerid, COLOR_SERVER, "(Transfer) {FFFFFF}You have successfully transfer {00FF00}$%s {FFFFFF}to {FFFF00}", FormatNumber(strval(totalcash)), GetName(id));
		SendClientMessageEx(id, COLOR_SERVER, "(Transfer) {FFFFFF}You've received {00FF00}$%s {FFFFFF}from {FFFF00}%s", FormatNumber(strval(totalcash)), GetName(playerid));
		Log_Write("Logs/transfer_log.txt", "[%s] %s(%s) has transfer to %s(%s) with amount $%s", ReturnDate(), GetName(playerid, false), GetUsername(playerid), GetName(id, false), GetUsername(id), FormatNumber(strval(totalcash)));
	
		if(strval(totalcash) > 100000) {
			SendAdminDutyMessage(X11_YELLOW, "(TransferLog) "WHITE"%s(%s) transfer to %s(%s) with amount: "DARKGREEN"$%s", GetName(playerid, false), GetUsername(playerid), GetName(id, false), GetUsername(id), FormatNumber(strval(totalcash)));
		}
	}
    return 1;
 }

CMD:balance(playerid, params[])
{
	if(!IsAtBank(playerid))
		return SendErrorMessage(playerid, "Kamu tidak berada di Bank Point!");

	SendClientMessage(playerid, 0x6896F1FF,     "< ======== Bank Balance ======== >");
	SendClientMessageEx(playerid, -1,   		"Balance: {00FF00}$%s", FormatNumber(PlayerData[playerid][pBank]));
	SendClientMessageEx(playerid, -1,   		"Current Tax: {FFFF00}%d percent", GovData[govTax]);	
	SendClientMessage(playerid, 0x6896F1FF,     "< ============================ >");

	return 1;
}
CMD:deposit(playerid, params[])
{
	if(!IsAtBank(playerid))
		return SendErrorMessage(playerid, "Kamu tidak berada di Bank Point!");

	new cash[32], amount;
	if(sscanf(params, "s[32]", cash))
		return SendSyntaxMessage(playerid, "/deposit [amount (dollar.cents)]");

	amount = strcash(cash);

	if(amount < 1)
		return SendErrorMessage(playerid, "Jumlah tidak bisa kurang dari $1,00");

	if(amount > 5000000)
		return SendErrorMessage(playerid, "Jumlah tidak bisa diatas $50.000,00");

	if(GetMoney(playerid) < amount)
		return SendErrorMessage(playerid, "Kamu tidak membawa uang sebanyak itu! ($%s)", FormatNumber(amount));

	GiveMoney(playerid, -amount, "Deposit ke bank");
	PlayerData[playerid][pBank] += amount;
	SendClientMessageEx(playerid, COLOR_SERVER, "(Bank) {FFFFFF}Kamu berhasil menyimpan {009000}$%s {FFFFFF}ke akun Bank!", FormatNumber(amount));
	return 1;
}

CMD:withdraw(playerid, params[])
{
	if(!IsAtBank(playerid))
		return SendErrorMessage(playerid, "Kamu tidak berada di Bank Point!");

	new dollars, cents, totalcash[25], cash[32];
	if(sscanf(params, "s[32]", cash))
		return SendSyntaxMessage(playerid, "/withdraw [amount (dollar.cents)]");

	if(strfind(cash, ".", true) != -1)
	{
		sscanf(cash, "p<.>dd", dollars, cents);
		format(totalcash, sizeof(totalcash), "%d%02d", dollars, cents);
		if(strval(totalcash) < 1)
			return SendErrorMessage(playerid, "Jumlah tidak bisa kurang dari $1,00");

		if(strval(totalcash) > 5000000)
			return SendErrorMessage(playerid, "Jumlah tidak bisa diatas $50.000,00");

		if(PlayerData[playerid][pBank] < strval(totalcash))
			return SendErrorMessage(playerid, "Tidak ada uang sebanyak itu dalam Bank-mu!");

		GiveMoney(playerid, strval(totalcash), "Withdraw dari bank");
		PlayerData[playerid][pBank] -= strval(totalcash);
		SendClientMessageEx(playerid, COLOR_SERVER, "(Bank) {FFFFFF}Kamu berhasil mengambil {009000}$%s {FFFFFF}dari akun Bank!", FormatNumber(strval(totalcash)));
	}
	else
	{
		sscanf(cash, "d", dollars);
		format(totalcash, sizeof(totalcash), "%d00", dollars);

		if(strval(totalcash) < 1)
			return SendErrorMessage(playerid, "Jumlah tidak bisa kurang dari $1,00");

		if(strval(totalcash) > 5000000)
			return SendErrorMessage(playerid, "Jumlah tidak bisa diatas $50.000,00");

		if(PlayerData[playerid][pBank] < strval(totalcash))
			return SendErrorMessage(playerid, "Tidak ada uang sebanyak itu dalam Bank-mu!");

		GiveMoney(playerid, strval(totalcash), "Withdraw dari bank");
		PlayerData[playerid][pBank] -= strval(totalcash);
		SendClientMessageEx(playerid, COLOR_SERVER, "(Bank) {FFFFFF}Kamu berhasil mengambil {009000}$%s {FFFFFF}dari akun Bank!", FormatNumber(strval(totalcash)));
	}
	return 1;
}


CMD:pay(playerid, params[])
{
    new id, cash[32];
    new dollars, cents, totalcash[25];

	if(PlayerData[playerid][pHour] < 2)
		return SendErrorMessage(playerid, "Minimal bermain 2 jam untuk melakukan ini.");

    if(sscanf(params, "us[32]", id, cash)) 
    	return SendSyntaxMessage(playerid, "/pay [playerid/PartOfName] [amount (dollar.cents)]");

    if(PlayerData[playerid][pLevel] < 1) 
    	return SendErrorMessage(playerid, "Minimal level 2 untuk menggunakan Command ini.");

 	if(id == INVALID_PLAYER_ID)
 		return SendErrorMessage(playerid, "Invalid player specified.");

 	if(id == playerid)
 		return SendErrorMessage(playerid, "You can't pay to yourself!");

 	if(!IsPlayerNearPlayer(playerid, id, 3.0))  
 		return SendErrorMessage(playerid, "You must close to that player!");

    if(strfind(cash, ".", true) != -1)
    {
		sscanf(cash, "p<.>dd", dollars, cents);
		format(totalcash, sizeof(totalcash), "%d%02d", dollars, cents);

		if(strval(totalcash) < 1)
			return SendErrorMessage(playerid, "Jumlah tidak bisa kurang dari $1,00");

		if(strval(totalcash) > 5000000)
			return SendErrorMessage(playerid, "Jumlah tidak bisa diatas $50.000,00");

		if(GetMoney(playerid) < strval(totalcash))
			return SendErrorMessage(playerid, "Kamu tidak memiliki uang sebanyak itu.");

       	GiveMoney(playerid, -strval(totalcash), sprintf("Pay to %s", GetName(id)));
		GiveMoney(id, strval(totalcash), sprintf("Pay from %s", GetName(playerid)));
		SendClientMessageEx(id, COLOR_SERVER, "(PayInfo) {FFFFFF}You've received {009000}$%s {FFFFFF}from "YELLOW"%s", FormatNumber(strval(totalcash)), ReturnName(playerid));
		SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s takes out $%s from their wallet and hands it to %s.", ReturnName(playerid), FormatNumber(strval(totalcash)), ReturnName(id));
		SendClientMessageEx(playerid, COLOR_SERVER, "(PayInfo) {FFFFFF}You've given {009000}$%s {FFFFFF}to "YELLOW"%s", FormatNumber(strval(totalcash)), ReturnName(id));
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		PlayerPlaySound(id, 1052, 0.0, 0.0, 0.0);
        ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
        ApplyAnimation(id, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
		Log_Write("Logs/pay_log.txt", "[%s] %s(%s) has paid to %s(%s) with amount $%s", ReturnDate(), GetName(playerid, false), GetUsername(playerid), GetName(id, false), GetUsername(id), FormatNumber(strval(totalcash)));
		ShowMessage(playerid, sprintf("~w~Kamu telah memberikan ~g~$%s ~w~ kepada %s", FormatNumber(strval(totalcash)), ReturnName(id)));
        ShowMessage(id, sprintf("~w~Kamu telah menerima ~g~$%s ~w~ dari %s", FormatNumber(strval(totalcash)), ReturnName(playerid)));
		if(!IsPlayerInAnyVehicle(playerid))
        	SetPlayerToFacePlayer(playerid, id);

        if(!IsPlayerInAnyVehicle(id))
        	SetPlayerToFacePlayer(id, playerid);

		if(strval(totalcash) > 100000) {
			SendAdminDutyMessage(X11_YELLOW, "(PayLog) "WHITE"%s(%s) pay to %s(%s) with amount: "DARKGREEN"$%s", GetName(playerid, false), GetUsername(playerid), GetName(id, false), GetUsername(id), FormatNumber(strval(totalcash)));
		}
	}
	else
	{
		sscanf(cash, "d", dollars);
		format(totalcash, sizeof(totalcash), "%d00", dollars);

		if(strval(totalcash) < 1)
			return SendErrorMessage(playerid, "Jumlah tidak bisa kurang dari $1,00");

		if(strval(totalcash) > 5000000)
			return SendErrorMessage(playerid, "Jumlah tidak bisa diatas $50.000,00");
		
		if(GetMoney(playerid) < strval(totalcash))
			return SendErrorMessage(playerid, "Kamu tidak memiliki uang sebanyak itu.");

       	GiveMoney(playerid, -strval(totalcash), sprintf("Pay to %s", GetName(id)));
		GiveMoney(id, strval(totalcash), sprintf("Pay from %s", GetName(playerid)));
		SendClientMessageEx(id, COLOR_SERVER, "(PayInfo) {FFFFFF}You've received {009000}$%s {FFFFFF}from "YELLOW"%s", FormatNumber(strval(totalcash)), ReturnName(playerid));
		SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s takes out $%s from their wallet and hands it to %s.", ReturnName(playerid), FormatNumber(strval(totalcash)), ReturnName(id));
		SendClientMessageEx(playerid, COLOR_SERVER, "(PayInfo) {FFFFFF}You've given {009000}$%s {FFFFFF}to "YELLOW"%s", FormatNumber(strval(totalcash)), ReturnName(id));
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		PlayerPlaySound(id, 1052, 0.0, 0.0, 0.0);
        ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
        ApplyAnimation(id, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
		Log_Write("Logs/pay_log.txt", "[%s] %s(%s) has paid to %s(%s) with amount $%s", ReturnDate(), GetName(playerid, false), GetUsername(playerid), GetName(id, false), GetUsername(id), FormatNumber(strval(totalcash)));
		
        if(!IsPlayerInAnyVehicle(playerid))
        	SetPlayerToFacePlayer(playerid, id);

        if(!IsPlayerInAnyVehicle(id))
        	SetPlayerToFacePlayer(id, playerid);


		if(strval(totalcash) > 100000) {
			SendAdminDutyMessage(X11_YELLOW, "(PayLog) "WHITE"%s(%s) pay to %s(%s) with amount: "DARKGREEN"$%s", GetName(playerid, false), GetUsername(playerid), GetName(id, false), GetUsername(id), FormatNumber(strval(totalcash)));
		}
	}
    return 1;
}



CMD:frisk(playerid, params[])
{
	new targetid;
	if(sscanf(params, "u", targetid))
		return SendSyntaxMessage(playerid, "/frisk [playerid/PartOfName]");

	if(targetid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "You have specified invalid player!");

	if(!IsPlayerNearPlayer(playerid, targetid, 5.0))
		return SendErrorMessage(playerid, "You must close to that player!");

	PlayerData[targetid][pFrisked] = playerid;
	SendClientMessageEx(playerid, COLOR_SERVER, "(Info) {FFFFFF}You've requested {FFFF00}%s {FFFFFF}For Frisk.",ReturnName(targetid));
	SendClientMessageEx(targetid, COLOR_SERVER, "(Info) {FFFF00}%s {FFFFFF}requested for frisking you, use {00FFFF}/accept frisk", ReturnName(playerid));
	return 1;
}

CMD:enter(playerid, params[])
{
	new id = -1;
	if(!IsPlayerInAnyVehicle(playerid))
	{
		for(new bid = 0; bid < MAX_BUSINESS; bid++) if(BizData[bid][bizExists])
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.8, BizData[bid][bizExt][0], BizData[bid][bizExt][1], BizData[bid][bizExt][2]))
			{
				if(BizData[bid][bizLocked])
					return ShowText(playerid, "~r~Locked", 2);

				if(BizData[bid][bizOwner] == -1)
					return SendErrorMessage(playerid, "This business is closed.");

				if(BizData[bid][bizSealed])
					return SendErrorMessage(playerid, "This business is sealed by the authority.");

				GetPlayerOutsideInfo(playerid);
				PlayerData[playerid][pInBiz] = bid;
				//SetPlayerCompensatedPos(playerid, BizData[bid][bizInt][0], BizData[bid][bizInt][1], BizData[bid][bizInt][2], _, BizData[bid][bizWorld], BizData[bid][bizInterior]);
				SetPlayerPositionEx(playerid, BizData[bid][bizInt][0], BizData[bid][bizInt][1], BizData[bid][bizInt][2], 4000, BizData[bid][bizInterior], BizData[bid][bizWorld]);
			}
	    }
		new inbiz = PlayerData[playerid][pInBiz];
		if(PlayerData[playerid][pInBiz] != -1 && IsPlayerInRangeOfPoint(playerid, 2.8, BizData[inbiz][bizInt][0], BizData[inbiz][bizInt][1], BizData[inbiz][bizInt][2]))
		{
			SetCameraBehindPlayer(playerid);
			SetPlayerCompensatedPos(playerid, BizData[inbiz][bizExt][0], BizData[inbiz][bizExt][1], BizData[inbiz][bizExt][2], _, 0, 0);

			PlayerData[playerid][pInBiz] = -1;
			ResetPlayerOutsideInfo(playerid);
		}
	    if ((id = House_Nearest(playerid)) != -1)
	    {
	        if (HouseData[id][houseLocked])
	            return ShowText(playerid, "~r~Locked", 2);

			if(HouseData[id][houseSealed])
				return SendErrorMessage(playerid, "This house is sealed by the authority");

			GetPlayerOutsideInfo(playerid);
			//SetPlayerCompensatedPos(playerid, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2], _, HouseData[id][houseID] + 5000, HouseData[id][houseInterior]);
			SetPlayerFacingAngle(playerid, HouseData[id][houseInt][3]);
			SetPlayerPositionEx(playerid, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2], 4000, HouseData[id][houseInterior],HouseData[id][houseID] + 5000);

			//SetCameraBehindPlayer(playerid);

			PlayerData[playerid][pInHouse] = HouseData[id][houseID];

			return 1;
		}
		if ((id = House_Inside(playerid)) != -1 && IsPlayerInRangeOfPoint(playerid, 2.5, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2]))
	    {

			SetPlayerCompensatedPos(playerid, HouseData[id][housePos][0], HouseData[id][housePos][1], HouseData[id][housePos][2], _, HouseData[id][houseExteriorVW], HouseData[id][houseExterior]);
			SetPlayerFacingAngle(playerid, HouseData[id][housePos][3] - 180.0);

			SetCameraBehindPlayer(playerid);
			PlayerData[playerid][pInHouse] = -1;

			ResetPlayerOutsideInfo(playerid);
			return 1;
		}
		if((id = Flat_Exterior(playerid)) != -1)
		{
			if(FlatData[id][flatLocked])
				return ShowText(playerid, "~r~Locked", 2);

			if(FlatData[id][flatSealed])
				return SendErrorMessage(playerid, "This flat is sealed by the authority.");

			GetPlayerOutsideInfo(playerid);

			//SetPlayerCompensatedPos(playerid, FlatData[id][flatInt][0], FlatData[id][flatInt][1], FlatData[id][flatInt][2], _, FlatData[id][flatIntWorld], FlatData[id][flatIntInterior]);
			//SetCameraBehindPlayer(playerid);

			SetPlayerPositionEx(playerid, FlatData[id][flatInt][0], FlatData[id][flatInt][1], FlatData[id][flatInt][2], 4000, FlatData[id][flatIntInterior], FlatData[id][flatIntWorld]);

			PlayerData[playerid][pInFlat] = id;
		} 
		if((id = Flat_Interior(playerid)) != -1) 
		{
			
			if(FlatData[id][flatLocked])
				return ShowText(playerid, "~r~Locked", 2);
				
			SetPlayerCompensatedPos(playerid,FlatData[id][flatPos][0], FlatData[id][flatPos][1], FlatData[id][flatPos][2], _, FlatData[id][flatExtWorld], FlatData[id][flatExtInterior]);
			SetCameraBehindPlayer(playerid);

			PlayerData[playerid][pInFlat] = -1;	
		}

		foreach(new did : Doors)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.8, drData[did][dExtposX], drData[did][dExtposY], drData[did][dExtposZ]) && GetPlayerVirtualWorld(playerid) == drData[did][dExtvw])
			{
				if(drData[did][dIntposX] == 0.0 && drData[did][dIntposY] == 0.0 && drData[did][dIntposZ] == 0.0)
					return SendErrorMessage(playerid, "Interior entrance masih kosong, atau tidak memiliki interior.");

				if(drData[did][dLocked])
					return SendErrorMessage(playerid, "This entrance is locked at the moment.");
					
				if(drData[did][dFaction] != -1)
				{
					if(drData[did][dFaction] != PlayerData[playerid][pFaction])
						return SendErrorMessage(playerid, "This door only for faction.");
				}
				
				if(drData[did][dAdmin] > PlayerData[playerid][pAdmin])
					return SendErrorMessage(playerid, "Your admin level not enough to enter this door.");
					
				GetPlayerOutsideInfo(playerid);

				if(strlen(drData[did][dPass]))
				{
					new paramss[256];
					if(sscanf(paramss, "s[256]", paramss)) return SendClientMessageEx(playerid, COLOR_WHITE, "[USAGE]: /enter [password]");
					if(strcmp(paramss, drData[did][dPass])) return SendErrorMessage(playerid, "Invalid door password.");
					
					//SetPlayerCompensatedPos(playerid, drData[did][dIntposX], drData[did][dIntposY], drData[did][dIntposZ], _, drData[did][dIntvw], drData[did][dIntint]);
					PlayerData[playerid][pInDoor] = did;
					//SetPlayerFacingAngle(playerid, drData[did][dIntposA]);
					//SetCameraBehindPlayer(playerid);
					SetPlayerPositionEx(playerid, drData[did][dIntposX], drData[did][dIntposY], drData[did][dIntposZ], 4000, drData[did][dIntint], drData[did][dIntvw]);
				}
				else
				{
					SetPlayerPositionEx(playerid, drData[did][dIntposX], drData[did][dIntposY], drData[did][dIntposZ], 4000, drData[did][dIntint], drData[did][dIntvw]);
				}
				SQL_SaveCharacter(playerid);
			}
			if(IsPlayerInRangeOfPoint(playerid, 2.8, drData[did][dIntposX], drData[did][dIntposY], drData[did][dIntposZ]) && GetPlayerVirtualWorld(playerid) == drData[did][dIntvw])
			{
				if(drData[did][dFaction] > 0)
				{
					if(drData[did][dFaction] != PlayerData[playerid][pFaction])
						return SendErrorMessage(playerid, "This door only for faction.");
				}


				SetPlayerCompensatedPos(playerid, drData[did][dExtposX], drData[did][dExtposY], drData[did][dExtposZ], _, drData[did][dExtvw], drData[did][dExtint]);
				PlayerData[playerid][pInDoor] = -1;
				SetPlayerFacingAngle(playerid, drData[did][dExtposA]);
				SetCameraBehindPlayer(playerid);

				ResetPlayerOutsideInfo(playerid);
			}
        }
	}
	return 1;
}

CMD:c(playerid, params[])
{
	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/c [Car Chat]");

    if(IsPlayerInAnyVehicle(playerid) && IsWindowedVehicle(GetPlayerVehicleID(playerid)))
    {
		SendVehicleMessage(GetPlayerVehicleID(playerid), 0xBBFFEEFF, "%s says [car]: %s", ReturnName(playerid), params);
	}
	else
	{
	    SendErrorMessage(playerid, "You're not in any Vehicle's!");
	}
	return 1;
}

CMD:whisper(playerid, params[])
	return cmd_w(playerid, params);

CMD:w(playerid, params[])
{
	new userid, text[128];

    if (sscanf(params, "us[128]", userid, text))
	    return SendSyntaxMessage(playerid, "/(w)hisper [playerid/PartOfName] [text]");

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 3.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	if (userid == playerid)
		return SendErrorMessage(playerid, "Kamu tidak dapat berbisik kepada diri sendiri.");

	if(PlayerData[playerid][pDrugCondition]) {

		new
			len = strlen(params);

		static const charset[] = "qwertyuiopasdfghjklzxcvbnm";

		for(new i = 0; i < len / 2; i++) {

			params[i] = (charset[random(sizeof charset)]);
		}
	}

    if (strlen(text) > 64)
	{
	    text[0] = toupper(text[0]);
	    SendClientMessageEx(userid, COLOR_YELLOW, "* Whisper from %s (%d): %.64s", ReturnName(playerid), playerid, text);
	    SendClientMessageEx(userid, COLOR_YELLOW, "...%s **", text[64]);

	    SendClientMessageEx(playerid, COLOR_YELLOW, "* Whisper to %s (%d): %.64s", ReturnName(userid), userid, text);
	    SendClientMessageEx(playerid, COLOR_YELLOW, "...%s **", text[64]);
	}
	else
	{
	    text[0] = toupper(text[0]);
	    SendClientMessageEx(userid, COLOR_YELLOW, "* Whisper from %s (%d): %s **", ReturnName(playerid), playerid, text);
	    SendClientMessageEx(playerid, COLOR_YELLOW, "* Whisper to %s (%d): %s **", ReturnName(userid), userid, text);
	}
	SendNearbyMessage(playerid, 15.0, X11_PLUM, "** %s mutters something in %s's ear.", ReturnName(playerid), ReturnName(userid));
    Log_Write("Logs/whisper_log.txt", "[%s] ** %s Whisper to %s (%d): %s **", ReturnDate(), GetName(playerid, false), GetName(userid, false), userid, text);
	return 1;
}

CMD:vehicle(playerid, params[])
	return cmd_v(playerid, params);

CMD:v(playerid, params[])
{
	new
	    type[24],
	    string[512],
		vehicleid;

	if (sscanf(params, "s[24]S()[128]", type, string))
	{
	    SendSyntaxMessage(playerid, "/v(ehicle) [entity]");
	    SendClientMessage(playerid, COLOR_SERVER, "(Entity){FFFFFF} list, lock, engine, hood, trunk, light");
		SendClientMessage(playerid, COLOR_SERVER, "(Entity){FFFFFF} attachment, give, storage, detail, neon");
	    return 1;
	}
	if(!strcmp(type, "engine", true))
	{
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			vehicleid = GetPlayerVehicleID(playerid);
			if(!IsEngineVehicle(vehicleid))
				return SendErrorMessage(playerid, "You're not inside of any engine vehicle!");

			if((Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER || Vehicle_GetType(vehicleid) == VEHICLE_TYPE_RENTAL) && !Vehicle_IsOwner(playerid, vehicleid) && !Vehicle_IsShared(playerid, vehicleid) && !PlayerData[playerid][pAduty])
				return ShowMessage(playerid, "~r~ERROR ~w~Kamu tidak memiliki kunci kendaraan ini!", 2);
				
			if(VehicleData[vehicleid][vTireLock])
				return SendErrorMessage(playerid, "This vehicle is tirelocked!");
				
			if(IsValidLoadingBar(playerid))
				return SendErrorMessage(playerid, "Harap tunggu beberapa saat.");

			if(GetEngineStatus(vehicleid))
			{
			    SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s inserts the key into the ignition and stops the engine.", ReturnName(playerid));

				SwitchVehicleEngine(vehicleid, false);
				ShowMessage(playerid, "Engine turned ~r~OFF", 3);
				SwitchVehicleLight(vehicleid, false);
			}
			else
			{
				if(VehicleData[vehicleid][vHandbrake])
					return SendErrorMessage(playerid, "Please disable vehicle handbrake first!");

				SendNearbyMessage(playerid, 30.0, X11_PLUM, "** %s inserts the key into the ignition and starts the engine.", ReturnName(playerid));
				StartPlayerLoadingBar(playerid, 50, "Turning_on_engine...", 40, "Vehicle_TurnOnEngine");
				SwitchVehicleLight(vehicleid, true);
			}
		}
	}
	else if(!strcmp(type, "neon", true)) {

		vehicleid = GetPlayerVehicleID(playerid);

		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return SendErrorMessage(playerid, "Kamu harus mengemudikan kendaraan terlebih dahulu.");
			
		if(VehicleData[vehicleid][vNeonColor] == VEHICLE_NEON_NONE)
			return SendErrorMessage(playerid, "Kendaraan ini tidak memiliki neon.");

		if(!VehicleData[vehicleid][vNeonStatus]) {
			Vehicle_SetNeon(vehicleid, true, VehicleData[vehicleid][vNeonColor], 0);
			Vehicle_SetNeon(vehicleid, true, VehicleData[vehicleid][vNeonColor], 1);
			Vehicle_SetNeon(vehicleid, true, VehicleData[vehicleid][vNeonColor], 2);
			VehicleData[vehicleid][vNeonStatus] = true;

			SendClientMessage(playerid, X11_LIGHTBLUE, "(Vehicle) "WHITE"Vehicle neon has been "GREEN"turned on");
		}
		else {
			Vehicle_SetNeon(vehicleid, false, VehicleData[vehicleid][vNeonColor], 0);
			Vehicle_SetNeon(vehicleid, false, VehicleData[vehicleid][vNeonColor], 1);
			Vehicle_SetNeon(vehicleid, false, VehicleData[vehicleid][vNeonColor], 2);
			VehicleData[vehicleid][vNeonStatus] = false;		

			SendClientMessage(playerid, X11_LIGHTBLUE, "(Vehicle) "WHITE"Vehicle neon has been "RED"turned off");	
		}

		Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	}
	else if(!strcmp(type, "storage", true)) {

		if(IsPlayerInAnyVehicle(playerid))
			return SendErrorMessage(playerid, "Turun dari kendaraan terlebih dahulu!");

		if((vehicleid = Vehicle_Nearest(playerid, 5.0)) != INVALID_VEHICLE_ID && Vehicle_GetType(vehicleid) == VEHICLE_TYPE_PLAYER) {

			if(Vehicle_IsOwner(playerid, vehicleid) || Vehicle_IsShared(playerid, vehicleid) || GetFactionType(playerid) == FACTION_POLICE) {

				if(!IsDoorVehicle(vehicleid))
					return SendErrorMessage(playerid, "This vehicle doesn't have a storage.");
					
				if(!GetTrunkStatus(vehicleid))
					return SendErrorMessage(playerid, "Buka trunk terlebih dahulu!");

				Vehicle_ShowTrunk(playerid, vehicleid);
				PlayerData[playerid][pVehicle] = vehicleid;
			}
			else SendErrorMessage(playerid, "Kamu tidak memiliki akses kendaraan ini.");
		}
		else SendErrorMessage(playerid, "Kamu tidak berada didekat kendaraanmu!");
	}
	else if(!strcmp(type, "detail", true)) {

		new targetid;
		vehicleid = GetPlayerVehicleID(playerid);

		if(!IsPlayerInAnyVehicle(playerid))
			return SendErrorMessage(playerid, "Kamu harus berada dalam kendaraan milikmu.");

		if(!Iter_Contains(Vehicle, vehicleid))
			return SendErrorMessage(playerid, "Opsi ini tidak dapat digunakan pada kendaraan ini.");

		if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
			return SendErrorMessage(playerid, "Kamu harus berada dalam kendaraan milikmu.");

		if(!Vehicle_IsOwner(playerid, vehicleid))
			return SendErrorMessage(playerid, "Kamu harus berada dalam kendaraan milikmu.");

		if(sscanf(string, "u", targetid)) {
			Vehicle_ShowRegistration(playerid, vehicleid);
			return 1;
		}
		if(!IsPlayerNearPlayer(playerid, targetid, 5.0) || targetid == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid, "You have specified invalid player.");

		
		Vehicle_ShowRegistration(targetid, vehicleid);
	}
	else if(!strcmp(type, "give", true)) {

		new targetid;
		vehicleid = GetPlayerVehicleID(playerid);

		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return SendErrorMessage(playerid, "Kamu harus mengemudikan kendaraan milikmu.");

		if(!Iter_Contains(Vehicle, vehicleid))
			return SendErrorMessage(playerid, "Kendaraan ini tidak bisa diberikan.");

		if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
			return SendErrorMessage(playerid, "Kamu harus mengemudikan kendaraan milikmu.");

		if(!Vehicle_IsOwner(playerid, vehicleid))
			return SendErrorMessage(playerid, "Kamu harus mengemudikan kendaraan milikmu.");

		if(sscanf(string, "u", targetid)) 
			return SendSyntaxMessage(playerid, "/v(vehicle) [give] [playerid/PartOfName]");

		if(!IsPlayerNearPlayer(playerid, targetid, 5.0) || targetid == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid, "You have specified invalid player.");

		if(Vehicle_Count(targetid) >= CountPlayerVehicleSlot(targetid))
			return SendErrorMessage(playerid, "Player tersebut tidak bisa memiliki lebih banyak kendaraan lagi.");
			

		PlayerData[targetid][pVehicleOffer] = vehicleid;
		PlayerData[targetid][pVehicleOfferID] = playerid;
		SendServerMessage(targetid, "%s telah menawarkan kunci %s miliknya, \"/accept vehicle\" untuk menerima.", ReturnName(playerid), GetVehicleName(vehicleid));
		SendServerMessage(playerid, "Kamu telah menawarkan kunci %s kepada %s.", GetVehicleName(vehicleid), ReturnName(targetid));
	}
	else if(!strcmp(type, "attachment", true))
	{
		vehicleid = GetPlayerVehicleID(playerid);

		if(!IsPlayerInAnyVehicle(playerid))
			return SendErrorMessage(playerid, "You must be inside of any Vehicle's!");
	        
	    if(GetEngineStatus(vehicleid))
	        return SendErrorMessage(playerid, "Turn off the engine first!");
	        
		if(Vehicle_GetType(vehicleid) != VEHICLE_TYPE_PLAYER)
		    return SendErrorMessage(playerid, "You're not inside valid player vehicle!");
		    
	    if(IsPlayerInDynamicArea(playerid, AreaData[areaMechanic]))
		{
			ShowVehicleAttachmentMenu(playerid, vehicleid);
			PlayerData[playerid][pVehicle] = vehicleid;
		}
		else
			SendErrorMessage(playerid, "You must be in Mechanic Center!");
	}
	else if(!strcmp(type, "hood", true))
	{
	    if(IsPlayerInAnyVehicle(playerid))
			return SendErrorMessage(playerid, "You must be in front of Vehicle.");

		vehicleid = GetNearestVehicle(playerid, 5.0);

	    if(vehicleid == INVALID_VEHICLE_ID)
	    	return SendErrorMessage(playerid, "You're not in range of any vehicles.");

		if(!IsDoorVehicle(vehicleid))
			return SendErrorMessage(playerid, "Kendaraan ini tidak memiliki hood.");

	    switch (GetHoodStatus(vehicleid))
	    {
	    	case false:
	    	{
	    		SetHoodStatus(vehicleid, true);
	    		ShowMessage(playerid, "Hood ~g~Opened", 1);
	   		 	ApplyAnimation(playerid, "CARRY", "liftup", 3.0, 0, 0, 0, 0, 0);
	   		 	VehicleData[vehicleid][vHood] = true;
	    	}
	    	case true:
	    	{
	    		SetHoodStatus(vehicleid, false);
	    		ShowMessage(playerid, "Hood ~r~Closed", 1);
	    		ApplyAnimation(playerid, "CARRY", "putdwn", 3.0, 0, 0, 0, 0, 0);
	    		VehicleData[vehicleid][vHood] = false;
	    	}
	    }
	}
	else if(!strcmp(type, "trunk", true))
	{

		vehicleid = GetNearestVehicle(playerid, 5.0);

		if(vehicleid == INVALID_VEHICLE_ID)
			return SendErrorMessage(playerid, "You are not in behind of any vehicle!");

		if(!IsPlayerNearBoot(playerid, vehicleid))
			return SendErrorMessage(playerid, "You are not in behind of any vehicle!");

		if(VehicleData[vehicleid][vLocked])
			return SendErrorMessage(playerid, "Kendaraan ini masih terkunci!");
	
		if(!IsDoorVehicle(vehicleid))
			return SendErrorMessage(playerid, "Kendaraan ini tidak memiliki trunk.");

    	switch (GetTrunkStatus(vehicleid))
    	{
    		case false:
    		{
    			SwitchVehicleBoot(vehicleid, true);
    			ShowMessage(playerid, "Trunk ~g~Opened", 1);
    		}
    		case true:
    		{
    			SwitchVehicleBoot(vehicleid, false);
    			ShowMessage(playerid, "Trunk ~r~Closed", 1);
    		}
    	}
	}
	else if(!strcmp(type, "light", true))
	{
		vehicleid = GetPlayerVehicleID(playerid);
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			if(!IsEngineVehicle(vehicleid))
				return SendErrorMessage(playerid, "This vehicle doesn't have a lights!");

			switch(GetLightStatus(vehicleid))
			{
				case false:
				{
					SwitchVehicleLight(vehicleid, true);
					SendClientMessage(playerid, COLOR_SERVER, "(Vehicle) {FFFFFF}Lights {00FF00}ON");
				}
				case true:
				{
					SwitchVehicleLight(vehicleid, false);
					SendClientMessage(playerid, COLOR_SERVER, "(Vehicle) {FFFFFF}Lights {FF0000}OFF");
				}
			}
		}
	}
	else if(!strcmp(type, "unstuck", true)) {
		
		if(Vehicle_Count(playerid) < 1)
			return SendErrorMessage(playerid, "Kamu tidak memiliki kendaraan.");

		new str[312], count = 0;
		foreach(new i : Vehicle) if(IsValidVehicle(i) && Vehicle_IsOwner(playerid, i))
		{
			format(str, sizeof(str), "%s%s(ID:%d)\n", str, GetVehicleName(i), i);
			g_ListedVehicle[playerid][count++] = i;
		}
		ShowPlayerDialog(playerid, DIALOG_UNSTUCK, DIALOG_STYLE_LIST, "Unstuck Vehicle", str, "Unstuck", "Close");
	}
	else if(!strcmp(type, "spawn", true)) {

		new query[156];
		mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `vehicle` WHERE `vehState` = '%d' AND `vehExtraID` = '%d'", VEHICLE_STATE_STUCK, PlayerData[playerid][pID]);
		mysql_tquery(sqlcon, query, "QueryVehSpawn", "d", playerid);
	}
	else if(!strcmp(type, "lock", true))
	{
		new bool:found = false;

		vehicleid = GetPlayerVehicleID(playerid);

		if(IsPlayerInAnyVehicle(playerid))
		{
			
			if(!Vehicle_IsOwner(playerid, vehicleid) && !Vehicle_IsShared(playerid, vehicleid))
				return SendClientMessage(playerid, -1, "You don't have key for this vehicle!");

			PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
			VehicleData[vehicleid][vLocked] = !(VehicleData[vehicleid][vLocked]);
			LockVehicle(vehicleid, VehicleData[vehicleid][vLocked]);

			ShowMessage(playerid, sprintf("%s %s", GetVehicleName(vehicleid), (VehicleData[vehicleid][vLocked]) ? ("~r~Locked") : ("~g~Unlocked")), 3);
		}
		else
		{
			new str[312], count;
			format(str, sizeof(str), "Vehicle\tModel\tStatus\n");
			foreach(new i : Vehicle) if(Vehicle_IsOwner(playerid, i))
			{
				format(str, sizeof(str), "%s#%d\t%s\t%s\n", str, i, GetVehicleName(i), (VehicleData[i][vLocked]) ? ("{FF0000}Locked") : ("{00FF00}Unlocked"));
				g_ListedVehicle[playerid][count++] = i;
				found = true;
			}
			foreach(new i : Vehicle) if((Vehicle_GetType(i) == VEHICLE_TYPE_PLAYER || Vehicle_GetType(i) == VEHICLE_TYPE_RENTAL) && Vehicle_IsShared(playerid, i)) {
				format(str, sizeof(str), "%s#%d\t%s "YELLOW"(Shared)\t"WHITE"%s\n", str, i, GetVehicleName(i), (VehicleData[i][vLocked]) ? ("{FF0000}Locked") : ("{00FF00}Unlocked"));
				g_ListedVehicle[playerid][count++] = i;
				found = true;
			}
			if(found)
				ShowPlayerDialog(playerid, DIALOG_LOCK, DIALOG_STYLE_TABLIST_HEADERS, "Lock Vehicle", str, "Select", "Close");
			else
				SendErrorMessage(playerid, "You don't have any vehicle.");
		}
	}
	else if(!strcmp(type, "handbrake", true))
	{
		vehicleid = GetPlayerVehicleID(playerid);

		if(vehicleid == INVALID_VEHICLE_ID)
			return SendErrorMessage(playerid, "You must driving a vehicle!");

		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return SendErrorMessage(playerid, "You must driving a vehicle!");

		if(!IsDoorVehicle(vehicleid))
			return SendErrorMessage(playerid, "You can't handbrake this vehicle!");
		
		if(GetEngineStatus(vehicleid))
			return SendErrorMessage(playerid, "Turn off your vehicle engine first!");

		VehicleData[vehicleid][vHandbrake] = (!VehicleData[vehicleid][vHandbrake]);
		SendClientMessageEx(playerid, COLOR_SERVER, "(Vehicle) {FFFFFF}You have successfully %s {FFFFFF}vehicle Handbrake!", (VehicleData[vehicleid][vHandbrake]) ? ("{00FF00}engaged") : ("{FF0000}disengaged"));
		GetVehiclePos(vehicleid, VehicleData[vehicleid][vHandbrakePos][0], VehicleData[vehicleid][vHandbrakePos][1], VehicleData[vehicleid][vHandbrakePos][2]);
		GetVehicleZAngle(vehicleid, VehicleData[vehicleid][vHandbrakePos][3]);
	}
	else if(!strcmp(type, "list", true))
	{
		mysql_tquery(sqlcon, sprintf("SELECT * FROM `vehicle` WHERE `vehExtraID` = '%d' AND `vehState` != '%d' AND `vehType` = '%d' ORDER BY `vehID` ASC", PlayerData[playerid][pID], VEHICLE_STATE_SPAWNED, VEHICLE_TYPE_PLAYER), "Vehicle_ShowList", "d", playerid);
	}
	return 1;
}


CMD:fixmask(playerid, params[]) {

	if(!PlayerHasItem(playerid, "Mask"))
		return SendErrorMessage(playerid, "Kamu tidak memiliki mask.");

	if(PlayerData[playerid][pMaskID] != 0) {
		return SendErrorMessage(playerid, "Kamu tidak dapat menggunakan CMD ini sekarang.");
	}

	PlayerData[playerid][pMaskID] = PlayerData[playerid][pID]+random(90000) + 10000;
	SendServerMessage(playerid, "Mask ID mu telah difix! "YELLOW"("WHITE"%d"YELLOW")", PlayerData[playerid][pMaskID]);
	Log_Write("Logs/maskid_log.txt", "[%s] %s(%s) new maskid: %d", ReturnDate(), GetName(playerid, false), GetUsername(playerid), PlayerData[playerid][pMaskID]);
	return 1;
}

CMD:changenameme(playerid, params[]) {

	new query[156];
	mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM `changenamesweb` WHERE `cnOwner` = '%d' LIMIT 1;", PlayerData[playerid][pID]);
	mysql_tquery(sqlcon, query, "OnChangenameCheck", "d", playerid);
	return 1;
}

function OnChangenameCheck(playerid) {
	if(!cache_num_rows()) {
		return SendErrorMessage(playerid, "Kamu belum membuat pending changename request.");
	}

	new 
		status, birthdate[24], name[24], gender, origin[32];

	cache_get_value_name_int(0, "cnStatus", status);

	cache_get_value_name_int(0, "cnGender", gender);
	cache_get_value_name(0, "cnName", name, sizeof(name));
	cache_get_value_name(0, "cnBirthdate", birthdate, sizeof(birthdate));
	cache_get_value_name(0, "cnOrigin", origin, sizeof(origin));

	if(!status) {
		return SendErrorMessage(playerid, "Changename requestmu belum disetujui.");
	}



	if(ChangeName(playerid, name)) {
		mysql_tquery(sqlcon, sprintf("DELETE FROM `changenamesweb` WHERE `cnOwner` = '%d' AND `cnOwnerID` = '%d'", PlayerData[playerid][pID], UcpData[playerid][ucpID]));
		format(PlayerData[playerid][pOrigin], 32, origin);
		format(PlayerData[playerid][pBirthdate], 24, birthdate);
		PlayerData[playerid][pGender] = gender;

		SendServerMessage(playerid, "Namamu berhasil diubah menjadi "GREY"%s", name);
	}
	return 1;
}