IsPizzaVehicle(vehicleid)
{
    forex(i, sizeof(PizzaVehicle))
	{
		if(vehicleid == PizzaVehicle[i]) return 1;
	}
	return 0;
}

RandomPizzaPoint(playerid)
{
	new index, houseIDs[MAX_HOUSES] = {-1, ...};

	forex(i, MAX_HOUSES)
	{
	    if(HouseData[i][houseExists] && HouseData[i][houseExterior] == 0 && HouseData[i][houseExteriorVW] == 0)
	    {
	        if(300.0 <= GetPlayerDistanceFromPoint(playerid, HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2]) <= 1200.0)
	        {
	        	houseIDs[index++] = i;
			}
		}
	}

	if(index == 0)
	{
	    return -1;
	}

	return houseIDs[random(index)];
}

CMD:getpizza(playerid, params[])
{
    if(PlayerData[playerid][pJob] != JOB_PIZZA) 
        return SendErrorMessage(playerid, "You're not Pizza Delivery");
        
	if(!IsPlayerInRangeOfPoint(playerid, 6.0, -2323.69, -150.614, 35.5547))
	{
		return SendErrorMessage(playerid, "Kamu tidak dalam jangkauan Manager Pizzaman.");
	}
	if(PlayerData[playerid][pCarryingPizza])
		return SendErrorMessage(playerid, "Kamu sudah membawa Pizza, silahkan taruh di kendaraan {FFFF00}/putpizza");

	if(PlayerData[playerid][pPizzaDelay] > 0)
	{
	    return SendClientMessageEx(playerid, COLOR_WHITE, "(Pizza) {FFFFFF}Kamu perlu menunggu %i detik", PlayerData[playerid][pPizzaDelay]);
	}
	
	PlayerData[playerid][pCarryPizza] = 1;
	PlayerData[playerid][pCarryingPizza] = true;
	SetPlayerAttachedObject(playerid, 1, 2663, 6, 0.308999, 0.020000, 0.000000, 15.600001, -103.199974, -2.500001, 1.000000, 1.000000, 1.000000);
	SendClientMessageEx(playerid, COLOR_ORANGE, "(Pizza) {FFFFFF}Kamu telah mengambil Pizza, silahkan taruh di kendaraan {FFFF00}/putpizza");
	return 1;
}

CMD:putpizza(playerid, params[])
{
	new houseid;

    if(PlayerData[playerid][pJob] != JOB_PIZZA) 
        return SendErrorMessage(playerid, "You're not Pizza Delivery");

	if(!PlayerData[playerid][pCarryingPizza])
		return SendErrorMessage(playerid, "Kamu tidak membawa Pizza.");

	if(PlayerData[playerid][pCarryPizza] != 1)
		return SendErrorMessage(playerid, "Itu bukan makanan yang kamu bawa!(atau kamu akan memberikan pengiriman)");

	new i = GetNearestVehicle(playerid, 3.0);

	if((IsPizzaVehicle(i) && IsVehicleOccupied(i)) || !IsPizzaVehicle(i))
		return SendErrorMessage(playerid, "Kamu tidak berada di kendaraan Pizza Delivery");

	if(VehicleData[i][vPizza])
		return SendErrorMessage(playerid, "Kendaraan ini sudah ada Pizza");

	if((houseid = RandomPizzaPoint(playerid)) == -1)
		return SendErrorMessage(playerid, "Tidak ada rumah di kota untuk mengirim makanan. Minta admin untuk mengaturnya.");

	PlayerData[playerid][pCarryPizza] = 0;
	PlayerData[playerid][pCarryingPizza] = false;

	VehicleData[i][vPizza] = true;

	RemovePlayerAttachedObject(playerid, 1);
	//PlayerData[playerid][pDistance] = GetPlayerDistanceFromPoint(playerid, HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2]);
    PlayerData[playerid][pPizza] = 1;
	//PlayerData[playerid][pLastPizza] = gettime();
    PlayerData[playerid][pPizzaTime] = 0;
    PlayerData[playerid][pPizzaDelay] = 60;

	SetWaypoint(playerid, HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2], 2.0);
    PlayerData[playerid][pPizzas] = true;

	SendClientMessageEx(playerid, COLOR_ORANGE, "(Pizza) {FFFFFF}Kamu telah menaruh pesanan dikendaraan. Kirimkan ke %s.", GetLocation(HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2]));
	SendClientMessageEx(playerid, COLOR_ORANGE, "(Pizza) {FFFFFF}Jika sudah sampai ke checkpoint gunakan {FFFF00}/grabpizza");
	return 1;
}

CMD:grabpizza(playerid, params[])
{
    if(PlayerData[playerid][pJob] != JOB_PIZZA) 
        return SendErrorMessage(playerid, "You're not Pizza Delivery");

	if(PlayerData[playerid][pCarryingPizza])
		return SendErrorMessage(playerid, "Kamu sudah membawa Pizza.");

	new i = GetNearestVehicle(playerid, 4.5);

	if((IsPizzaVehicle(i) && IsVehicleOccupied(i)) || !IsPizzaVehicle(i))
		return SendErrorMessage(playerid, "Kamu tidak berada di kendaraan Pizza Delivery");

	if(!VehicleData[i][vPizza])
		return SendErrorMessage(playerid, "Kendaraan ini tidak ada Pizza, Silahkan ambil di gudang terlebih dahulu");

	PlayerData[playerid][pCarryPizza] = 2;
	PlayerData[playerid][pCarryingPizza] = true;
	SetPlayerAttachedObject(playerid, 1, 2663, 6, 0.308999, 0.020000, 0.000000, 15.600001, -103.199974, -2.500001, 1.000000, 1.000000, 1.000000);

	VehicleData[i][vPizza] = false;

	SendClientMessageEx(playerid, COLOR_ORANGE, "(Pizza) {FFFFFF}Kirim ke checkpoint GPS");
	return 1;
}