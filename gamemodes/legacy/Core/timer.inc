task MinuteUpdate[60000]()
{
	for(new i = 0; i < MAX_WEED; i++) if(WeedData[i][weedExists])
	{
		if(WeedData[i][weedGrow] < MAX_GROW)
		{
			WeedData[i][weedGrow]++;
		}
	}
	for(new i = 0; i < MAX_ADVERT; i ++) if(AdvertData[i][advertExists])
	{
		if(--AdvertData[i][advertTime] == 0) {
  
			foreach(new  p : Player)
			{
				SendClientMessageEx(p, -1, ""COOL_GREEN"Advertisement: "WHITE"%s", AdvertData[i][advertText]);
				SendClientMessageEx(p, -1, ""COOL_GREEN"Contact Person: "WHITE"#%d", AdvertData[i][advertNumber]);
			}  
			Advert_Delete(i);
		}
	}
	return 1;
}

ptask OnSickCharacterCheck[1000](playerid)
{

	if(!IsPlayerSpawned(playerid))
		return 0;

	if(Character_CanUpdate(playerid)) {
		
		if(PlayerData[playerid][pThirst] <= 20 || PlayerData[playerid][pHunger] <= 20)
		{
			if(++PlayerData[playerid][pFeverRate] >= 600) {

				if(PlayerData[playerid][pFever] < 4) {
					PlayerData[playerid][pFever]++;

					if(!IsPlayerDrunk(playerid)) {
						SetPlayerDrunkLevelEx(playerid, 20000*PlayerData[playerid][pFever] + 1, 20000);
						SendClientMessage(playerid, X11_GREEN, "(Sickness) "WHITE"Kamu terkena demam tinggi! kamu harus berobat untuk menghilangkan demam.");
						SetTimerEx("HidePlayerBox", 20000, false, "dd", playerid, _:ShowPlayerBox(playerid, 0xFF000066));

						new Float:health;
						GetPlayerHealth(playerid, health);
						SetPlayerHealth(playerid, health-RandomFloat(2.0, 5.0));
					}

				}
			}
		}
        if(PlayerData[playerid][pCough])
        {
            if(++PlayerData[playerid][pCoughTime] > 120)
            {
                cmd_ame(playerid, "is cough.");
				SetTimerEx("HidePlayerBox", 500, false, "dd", playerid, _:ShowPlayerBox(playerid, 0xFF000066));
                PlayerData[playerid][pCoughTime] = 0;
            }
        }
	}
	return 1;
}

ptask OnEnergyUpdate[1000](playerid)
{
	if(PlayerData[playerid][pSpawned] && !PlayerData[playerid][pAduty] && !PlayerData[playerid][pJailTime])
	{
		new animidx = GetPlayerAnimationIndex(playerid),
			k,
			ud,
			lr,
			Float:adjustment,
			Float:adjustment1;    

		GetPlayerKeys(playerid, k, ud, lr);

		if(animidx == 43) {
			adjustment = (0.06 * 0.4);
			adjustment1 = (0.06 * 0.3); // Sitting
		} else if(animidx == 1159) {
			adjustment = (0.06 * 0.7);
			adjustment1 = (0.06 * 0.7); // Crouching
		} else if(animidx == 1195) {
			adjustment = (0.06 * 1.9);
			adjustment1 = (0.06 * 1.5); // Jumping
		} else if(animidx == 1231) {
			if(k & KEY_WALK) {
				adjustment = (0.06 * 0.08);
				adjustment1 = (0.06 * 0.07); // Walking
			} else if(k & KEY_SPRINT) {
				adjustment = (0.06 * 1.5);
				adjustment1 = (0.06 * 1.2); // Sprinting
			} else if(k & KEY_JUMP) {
				adjustment = (0.06 * 1.8);
				adjustment1 = (0.06 * 1.7); // Jumping
			} else {
				adjustment = (0.06 * 0.8);
				adjustment1 = (0.06 * 0.4); // Jogging
			}
		} else {
			adjustment = 0.05;
			adjustment1 = 0.04;
		}

		adjustment *= 0.2;
		adjustment1 *= 0.2;

		if(PlayerData[playerid][pHunger] > 0) {
			PlayerData[playerid][pHunger] -= adjustment;
		}
		if(PlayerData[playerid][pThirst] > 0){ 
			PlayerData[playerid][pThirst] -= adjustment1;
		}
	}
	return 1;
}

task SecondUpdate[1000]()
{
	forex(i, MAX_TREE) if(TreeData[i][treeExists] && TreeData[i][treeTime] > 0)
	{
		TreeData[i][treeTime]--;
		if(TreeData[i][treeTime] <= 0)
		{
			TreeData[i][treeCutted] = false;
			Tree_Refresh(i);
		}
	}
    if(countdown_tick)
    {
        new string[64], times[3];

        countdown_tick--;

        GetElapsedTime(countdown_tick, times[0], times[1], times[2]);

        switch(countdown_tick)
        {
            case 0:
            {
                format(string, 32, "~p~Countdown:~w~Done");
                TextDrawHideForAll(COUNTDOWNGUI);
                countdown_tick = 0;
            }
            case 1:format(string, 32, "~p~Countdown:~g~~h~ %02d:%02d", times[1], times[2]);
            case 2:format(string, 32, "~p~Countdown:~y~~h~ %02d:%02d", times[1], times[2]);
            case 3:format(string, 32, "~p~Countdown:~r~~h~ %02d:%02d", times[1], times[2]);
            default: format(string, 32, "~p~Countdown:~w~~h~ %02d:%02d", times[1], times[2]);
        }
        TextDrawSetString(COUNTDOWNGUI, string);
    }
	return 1;
}

task RentalUpdate[1000]()
{
	foreach(new i : Vehicle) if(VehicleData[i][vType] == VEHICLE_TYPE_RENTAL && VehicleData[i][vRental] != -1)
	{
		if(VehicleData[i][vRentTime])
		{
			if(--VehicleData[i][vRentTime] <= 0)
			{

				VehicleData[i][vRentTime] = 0;
				
				foreach(new playerid : Player) if(VehicleData[i][vExtraID] == PlayerData[playerid][pID]) {
					SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Rental) "WHITE"Durasi rental kendaraan "YELLOW"(%s) "WHITE"telah habis, kendaraan dihilangkan.", GetVehicleName(i));
					break;
				}
				mysql_tquery(sqlcon, sprintf("DELETE FROM `crates` WHERE `Vehicle` = '%d'", VehicleData[i][vID]));
				mysql_tquery(sqlcon, sprintf("DELETE FROM vehicle WHERE vehID = '%d'", VehicleData[i][vID]));	

				new next = i;

				DestroyVehicle(i);

				Iter_SafeRemove(Vehicle, next, i);
			}
		}
	}
	return 1;
}

/*
task vehicle_RentalUpdate[1000]() {

	foreach(new i : Vehicle) if(IsValidVehicle(i) && VehicleData[i][vType] == VEHICLE_TYPE_RENTAL) {
		if(VehicleData[i][vRentTime] > 0) {
			VehicleData[i][vRentTime]--;
			if(!VehicleData[i][vRentTime]) {

				foreach(new playerid : Player) if(VehicleData[i][vExtraID] == PlayerData[playerid][pID]) {
					SendClientMessageEx(playerid, COLOR_SERVER, "(Rental) {FFFFFF}Durasi waktu Rental {FFFF00}%s {FFFFFF}telah habis, kendaraan otomatis dihilangkan.", GetVehicleName(VehicleData[i][vVehicle]));
				}
				Vehicle_Delete(i, true);
			}
		}
	}
	return 1;
}*/

task Timer_OnVehicleUpdate[35000]()
{
	foreach(new i : Vehicle) if (IsValidVehicle(i) && IsEngineVehicle(i) && GetEngineStatus(i) && GetVehicleSpeed(i) > 1)
	{
	    if (Vehicle_GetFuel(i) > 0.0)
	    {
			VehicleData[i][vFuel] -= RandomFloat(0.1, 0.5);
	        if(VehicleData[i][vFuel] <= 0.0)
			{
			    VehicleData[i][vFuel] = 0.0;
	      		SwitchVehicleEngine(i, false);
				
				if(GetVehicleDriver(i) != INVALID_PLAYER_ID)
	      			GameTextForPlayer(GetVehicleDriver(i), "Bensin kendaraan telah habis!", 3000, 3);
			}
		}
	}
	return 1;
}

task Server_MinuteUpdate[60000]() {
	static taxi_notify, mechanic_notify;

	if(++taxi_notify >= 10) {
		
		new count = 0;
		foreach(new i : Player) if(CheckPlayerJob(i, JOB_TAXI) && PlayerData[i][pJobduty]) {
			count++;
		}

		if(count) {
			SendClientMessageToAllEx(X11_YELLOW, "(Taxi Information) "WHITE"Saat ini sedang ada "LIGHTBLUE"%d "WHITE"Taxi yang sedang bertugas! (telfon taxi pada nomor: 1222)", count);
		}

		taxi_notify = 0;
	}

	if(++mechanic_notify >= 15) {
		new count = 0;
		foreach(new i : Player) if(CheckPlayerJob(i, JOB_MECHANIC) && PlayerData[i][pJobduty]) {
			count++;
		}

		if(count) {
			SendClientMessageToAllEx(X11_GREEN, "(Mechanic Information) "WHITE"Saat ini sedang ada "LIGHTBLUE"%d "WHITE"Mechanic yang sedang bertugas! (telfon mechanic pada nomor: 132)", count);
		}

		mechanic_notify = 0;
	}
	return 1;
}
ptask Player_MinuteUpdate[60000](playerid)
{
    if(!IsPlayerSpawned(playerid))
        return 0;

    static save_counter;

    if(save_counter++ >= 5)
    {
        SQL_SaveCharacter(playerid);    
        save_counter = 0;
    }
    return 1;
}

ptask OnSpeedometerUpdate[200](playerid) {
	if(PlayerData[playerid][pSpawned]) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsEngineVehicle(GetPlayerVehicleID(playerid)) && !PlayerData[playerid][pTogHud])
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new Float:fDamage;
			new Float:fuel;
			new Float:v_hp;
			new location[64], Float:x, Float:y, Float:z;
			new Float:darah;

			GetVehicleHealth(vehicleid, fDamage);
			GetPlayerPos(playerid, x, y, z);
			
			if(PlayerData[playerid][pHudType] == 1) {
				fuel = VehicleData[vehicleid][vFuel] * 59.5/GetVehicleFuelMax(GetVehicleModel(vehicleid));
				PlayerTextDrawTextSize(playerid,FUELTD[playerid], fuel, 6.5);
				PlayerTextDrawShow(playerid, FUELTD[playerid]);

				v_hp = VehicleData[vehicleid][vFuel] * 59.5/1000.0;
				PlayerTextDrawTextSize(playerid,VHPTD[playerid], v_hp, 6.5);
				PlayerTextDrawShow(playerid, VHPTD[playerid]);

				

				format(location, sizeof(location), "%s", RemoveSpace(GetLocation(x, y, z)));
				PlayerTextDrawSetString(playerid, VEHNAMETD[playerid], sprintf("%s", RemoveSpace(GetVehicleName(vehicleid))));
				PlayerTextDrawSetString(playerid, LOCATIONTD[playerid], location);
				
				if(fDamage <= 1000.0)
				{
					darah = fDamage * 59.5/1000.0;
					PlayerTextDrawTextSize(playerid,VHPTD[playerid], darah, 6.5);
					PlayerTextDrawShow(playerid,VHPTD[playerid]);
				}
				else
				{
					PlayerTextDrawTextSize(playerid,VHPTD[playerid], 59.5, 6.5);
					PlayerTextDrawShow(playerid,VHPTD[playerid]);
				}
				PlayerTextDrawSetString(playerid, KMHTD[playerid], sprintf("%i", floatround(GetVehicleSpeed(vehicleid))));

				PlayerTextDrawSetString(playerid, ENGINETD[playerid], sprintf("%s", (GetEngineStatus(vehicleid)) ? ("~g~ON") : ("~r~OFF")));
			}
			else if(PlayerData[playerid][pHudType] == 2) {
				new string[156];

				new Float:fuel_percent = VehicleData[vehicleid][vFuel];
				
				format(string, sizeof(string), "%s I %s~n~%dKM/h I Fuel: %.2f%% I Health: %.2f I Engine: %s",
					GetVehicleName(vehicleid), GetLocation(x, y, z), floatround(GetVehicleSpeed(vehicleid)), fuel_percent, fDamage, GetEngineStatus(vehicleid) ? ("ON") : ("OFF"));
			
				PlayerTextDrawSetString(playerid, SPEEDO_2[playerid], string);
			}
			else {


				new Float:fuel_percent = VehicleData[vehicleid][vFuel];

				if(IsValidPlayerProgressBar(playerid, PROGRESS_FUEL[playerid]))
					SetPlayerProgressBarValue(playerid, PROGRESS_FUEL[playerid], fuel_percent);

				PlayerTextDrawSetString(playerid, HBE3_SPEEDO[playerid][5], sprintf("%s", GetVehicleName(vehicleid)));
				PlayerTextDrawSetString(playerid, HBE3_SPEEDO[playerid][2], sprintf("HEALTH_____:_%.2f", fDamage));
				PlayerTextDrawSetString(playerid, HBE3_SPEEDO[playerid][3], sprintf("SPEED______:_%dKM/h", floatround(GetVehicleSpeed(vehicleid))));
			}
		}
	}
}
ptask PlayerUpdate[1000](playerid)
{
	if(IsPlayerSpawned(playerid))
	{
		UpdateHBE(playerid);
		AFKCheck(playerid);
		UpdateTime(playerid);

		if(PlayerData[playerid][pHunger] > 100)
			PlayerData[playerid][pHunger] = 100;

		if(PlayerData[playerid][pThirst] > 100)
			PlayerData[playerid][pThirst] = 100;

		if(PlayerData[playerid][pThirst] < 1) {
			PlayerData[playerid][pThirst] = 0;
		}

		if(PlayerData[playerid][pHunger] < 1) {
			PlayerData[playerid][pHunger] = 0;
		}

		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			new vehicleid = GetPlayerVehicleID(playerid);

			if(VehicleData[vehicleid][vFuel] > GetVehicleFuelMax(GetVehicleModel(vehicleid))) {
				VehicleData[vehicleid][vFuel] = GetVehicleFuelMax(GetVehicleModel(vehicleid));
			}
		}
		if (GetPlayerMoney(playerid) != PlayerData[playerid][pMoney])
		{
		    ResetPlayerMoney(playerid);
		    GivePlayerMoney(playerid, PlayerData[playerid][pMoney]);
		}
		if(PlayerData[playerid][pTazer] && GetWeapon(playerid) > 0)
		{
			SetPlayerArmedWeapon(playerid, 0);
			SendClientMessage(playerid, COLOR_LIGHTRED, "(Warning) {FFFFFF}You can't holding weapon since you holding Tazer");
		}
		if(GetEquipedItem(playerid) != EQUIP_ITEM_NONE && GetWeapon(playerid) > 0)
		{
			SetPlayerArmedWeapon(playerid, 0);
			SendClientMessage(playerid, COLOR_LIGHTRED, "(Warning) {FFFFFF}You can't holding weapon since you holding something!");
		}
		if(IsDragging[playerid] != INVALID_PLAYER_ID)
		{
			new targetid = IsDragging[playerid];
			PlayerData[targetid][pInBiz] = PlayerData[playerid][pInBiz];
			PlayerData[targetid][pInHouse] = PlayerData[playerid][pInHouse];
			PlayerData[targetid][pInDoor] = PlayerData[playerid][pInDoor];

			new Float:X, Float:Y, Float:Z, Float:Ang;
			GetPlayerPos(playerid, X, Y, Z);
			GetPlayerFacingAngle(playerid, Ang);

			X += (0.75 * -floatsin(-Ang, degrees));
			Y += (0.75 * -floatcos(-Ang, degrees));
			SetPlayerPos(targetid, X, Y, Z);
			if(GetPlayerInterior(targetid) != GetPlayerInterior(playerid))
			{
				SetPlayerInterior(targetid, GetPlayerInterior(playerid));
			}
			if(GetPlayerVirtualWorld(targetid) != GetPlayerVirtualWorld(playerid))
			{
				SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));
			}
		}
		if(CheckPlayerJob(playerid, JOB_TAXI) && PlayerData[playerid][pJobduty] && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
			
			new taxi_veh = GetPVarInt(playerid, "TaxiVehicle");

			if(!IsPlayerInRangeOfVehicle(playerid, taxi_veh, 30.0)) {
				PlayerData[playerid][pJobduty] = false;
				SetPlayerColor(playerid, COLOR_WHITE);
				IssuePendingSalary(playerid);
				DeletePVar(playerid, "TaxiVehicle");

				SendServerMessage(playerid, "Kamu tidak lagi duty sebagai taxi driver karena terlalu jauh dari taxi");
			}
		}
		if(PlayerData[playerid][pFishing] && GetPlayerAnimationIndex(playerid) != 1549 && ReturnFishPlace(playerid) != FISHPLACE_NONE)
		{
			ApplyAnimation(playerid, "SWORD", "SWORD_BLOCK", 4.1, 0, 0, 0, 1, 0);
		}
		if(GetPlayerAnimationIndex(playerid) != 392 && InHospital[playerid])
		{
			ApplyAnimation(playerid, "CRACK", "crckidle4", 4.1, 0, 0, 0, 1, 0, 1);
		}
		if(GetPlayerAnimationIndex(playerid) != 322 && IsMining[playerid]) {
			ApplyAnimation(playerid, "CHAINSAW", "WEAPON_csawlo", 4.1, 1, 0, 0, 0, 0, 1);
		}
		if(GetPlayerAnimationIndex(playerid) != 40 && MinerIndex[playerid] == 2) {
			ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
		}
		if(PlayerData[playerid][pWP])
		{
			PlayerTextDrawSetString(playerid, GPSTD[playerid], sprintf("%s~n~Distance:_%.2f_Meter", GetLocation(Destination[playerid][0], Destination[playerid][1], Destination[playerid][2]), GetPlayerDistanceFromPoint(playerid, Destination[playerid][0], Destination[playerid][1], Destination[playerid][2])));
		}
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK && PlayerData[playerid][pAdmin] < 1)
		{
			SendAdminMessage(COLOR_LIGHTRED, "AdmWarning: Cheat detected on {FFFF00}%s (%s) {FF6347}(Jetpack Hack)", GetName(playerid), PlayerData[playerid][pUCP]);
			KickEx(playerid);
		}
		if(GetPlayerAnimationIndex(playerid) != 1701 && PlayerData[playerid][pInjured])
		{
		    ApplyAnimation(playerid, "WUZI", "CS_DEAD_GUY", 4.1, 0, 0, 0, 1, 0, 1);
		}
		if(!PlayerData[playerid][pAFK]) {
			PlayerData[playerid][pSecond]++;
			if(PlayerData[playerid][pSecond] >= 60)
			{
				SyncPlayerTime(playerid);
				PlayerData[playerid][pMinute]++;
				PlayerData[playerid][pSecond] = 0;
				if(PlayerData[playerid][pMinute] % 15 == 0) {
					if(PlayerData[playerid][pJobduty]) {
						
						PlayerData[playerid][pPendingSalary] += 5000;
						SendServerMessage(playerid, "Kamu mendapatkan "GREEN"$50.00 "WHITE"dari jobduty (pending salary: "GREEN"$%s"WHITE")", FormatNumber(PlayerData[playerid][pPendingSalary]));
						
					}
				}
				if(PlayerData[playerid][pMinute] >= 60)
				{
					PlayerData[playerid][pHour]++;
					PlayerData[playerid][pMinute] = 0;

					new nxtlevel = PlayerData[playerid][pLevel] + 1,
						expamount = nxtlevel * 3;

					PlayerData[playerid][pExp]++;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);

					if (PlayerData[playerid][pExp] < expamount) {
						SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Level) "WHITE"Kamu membutuhkan %d jam lagi untuk ke level selanjutnya.", expamount - PlayerData[playerid][pExp]);
					}
					else {
						PlayerData[playerid][pLevel]++;
						PlayerData[playerid][pExp] = PlayerData[playerid][pExp]-expamount;
						SetPlayerScore(playerid, PlayerData[playerid][pLevel]);
						SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Level) "WHITE"Level naik! Sekarang kamu level %d.", PlayerData[playerid][pLevel]);
					}
				}
			}
			if(PlayerData[playerid][pOnDuty] && !PlayerData[playerid][pAFK])
			{
				PlayerData[playerid][pDutySecond]++;
				if(PlayerData[playerid][pDutySecond] >= 60)
				{
					PlayerData[playerid][pDutyMinute]++;
					PlayerData[playerid][pDutySecond] = 0;
					if(PlayerData[playerid][pDutyMinute] >= 60)
					{
						PlayerData[playerid][pDutyHour]++;
						PlayerData[playerid][pDutyMinute] = 0;
					}
				}
				
				PlayerData[playerid][pFactionSecond]++;
				if(PlayerData[playerid][pFactionSecond] >= 60) {

					PlayerData[playerid][pFactionMinute]++;
					PlayerData[playerid][pFactionSecond] = 0;

					if(PlayerData[playerid][pFactionHour] >= 60) {
						PlayerData[playerid][pFactionHour]++;
						PlayerData[playerid][pFactionMinute] = 0;
					}
				}
			}
		}
	}
	return 1;
}

ptask DelayUpdate[1000](playerid)
{
	if(IsPlayerSpawned(playerid))
	{
		if(GetFactionType(playerid) != FACTION_NONE && PlayerData[playerid][pOnDuty] && !PlayerData[playerid][pAFK])
		{
			if(PlayerData[playerid][pDutyTime]) {
				PlayerData[playerid][pDutyTime]--;
				if(PlayerData[playerid][pDutyTime] <= 0)
				{
					AddSalary(playerid, "Faction Duty", FactionData[PlayerData[playerid][pFaction]][factionSalary][PlayerData[playerid][pFactionRank] - 1]);
					PlayerData[playerid][pDutyTime] = 3600;
					notification.Show(playerid, "PAYCHECK", sprintf("~w~Faction Salary has been issued.~n~(~g~+$%s~w~)", FormatNumber(FactionData[PlayerData[playerid][pFaction]][factionSalary][PlayerData[playerid][pFactionRank] - 1])), "hud:radar_cash");
				}
			}
		}
		if(reportDelay[playerid] > 0) {
			reportDelay[playerid]--;
		}
		if(askDelay[playerid] > 0) {
			askDelay[playerid]--;
		}
		if(PlayerData[playerid][pDoorDelay] > 0) {
			PlayerData[playerid][pDoorDelay]--;
		}
		if(PlayerData[playerid][pUsePill] > 0) {
			PlayerData[playerid][pUsePill]--;
		}
		if(PlayerData[playerid][pMineDelay]) {
			if(--PlayerData[playerid][pMineDelay] <= 0) {
				SendServerMessage(playerid, "Kamu bisa menambang lagi sekarang.");
			}
		}
		if(PlayerData[playerid][pDriverDelay] > 0)
		{
			PlayerData[playerid][pDriverDelay]--;
			if(PlayerData[playerid][pDriverDelay] <= 0)
			{
				SendServerMessage(playerid, "Kamu bisa bekerja kembali sebagai {FFFF00}Delivery Driver");
				PlayerData[playerid][pDriverDelay] = 0;
			}
		}
		if(PlayerData[playerid][pCourierDelay] > 0)
		{
			PlayerData[playerid][pCourierDelay]--;
			if(PlayerData[playerid][pCourierDelay] <= 0)
			{
				SendServerMessage(playerid, "Kamu bisa bekerja kembali sebagai {FFFF00}Box Courier");
				PlayerData[playerid][pCourierDelay] = 0;
			}
		}
		if(PlayerData[playerid][pSweeperDelay] > 0)
		{
			PlayerData[playerid][pSweeperDelay]--;
			if(PlayerData[playerid][pSweeperDelay] <= 0)
			{
				SendServerMessage(playerid, "Kamu bisa bekerja kembali sebagai {FFFF00}Street Sweeper");
				PlayerData[playerid][pSweeperDelay] = 0;
			}
		}
		if(PlayerData[playerid][pMowerDelay] > 0)
		{
			PlayerData[playerid][pMowerDelay]--;
			if(PlayerData[playerid][pMowerDelay] <= 0)
			{
				SendServerMessage(playerid, "Kamu bisa bekerja kembali sebagai {FFFF00}Mower");
				PlayerData[playerid][pMowerDelay] = 0;
			}
		}
		if(PlayerData[playerid][pTrashmasterDelay] > 0)
		{
			PlayerData[playerid][pTrashmasterDelay]--;
			if(PlayerData[playerid][pTrashmasterDelay] <= 0)
			{
				SendServerMessage(playerid, "Kamu bisa bekerja kembali sebagai {FFFF00}Trashmaster");
				PlayerData[playerid][pTrashmasterDelay] = 0;
			}
		}
		if(PlayerData[playerid][pFishDelay] > 0)
		{
			PlayerData[playerid][pFishDelay]--;
			if(PlayerData[playerid][pFishDelay] <= 0)
			{
				SendServerMessage(playerid, "Kamu bisa {FFFF00}menjual ikan {FFFFFF}lagi sekarang!");
				PlayerData[playerid][pFishDelay] = 0;
			}
		}
		if(PlayerData[playerid][pPizzaDelay] > 0)
		{
			PlayerData[playerid][pPizzaDelay]--;
			if(PlayerData[playerid][pPizzaDelay] <= 0)
			{
				PlayerData[playerid][pPizzaDelay] = 0;
			}
		}
		if(PlayerData[playerid][pInjuredTime] > 0)
		{
			PlayerData[playerid][pInjuredTime]--;
		}
		if(PlayerData[playerid][pJailTime] > 0 && !PlayerData[playerid][pAduty])
		{
			PlayerData[playerid][pJailTime]--;
			new hours, seconds, minutes;
			GetElapsedTime(PlayerData[playerid][pJailTime], hours, minutes, seconds);
			new string[156];
			if(!PlayerData[playerid][pArrest])
			{
				format(string, sizeof(string), "~r~Jail_Time:~w~_%02d:%02d:%02d~n~~r~Jail_Reason:~w~_%s~n~~r~Jailed_by:~w~_%s", hours, minutes, seconds, PlayerData[playerid][pJailReason], PlayerData[playerid][pJailBy]);
			}
			else
			{
				format(string, sizeof(string), "~r~Arrest_Time:~w~_%02d:%02d:%02d~n~~r~Arrest_Reason:~w~_%s~n~~r~Arrested_by:~w~_%s", hours, minutes, seconds, PlayerData[playerid][pJailReason], PlayerData[playerid][pJailBy]);
			}	
			PlayerTextDrawSetString(playerid, JAILTD[playerid], string);
			if(PlayerData[playerid][pJailTime] <= 0)
			{
		        PlayerData[playerid][pArrest] = 0;
		        format(PlayerData[playerid][pJailBy], MAX_PLAYER_NAME, "_");
		        format(PlayerData[playerid][pJailReason], 32, "_");

				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);

				SetPlayerPos(playerid, -2450.5044,503.7565,30.0853);
				Streamer_Update(playerid, -1);
				
				SendServerMessage(playerid, "Kamu telah dikeluarkan dari penjara.");
		        PlayerTextDrawHide(playerid, JAILTD[playerid]);
				TogglePlayerControllable(playerid, 1);
			}
		}
		if(PlayerData[playerid][pPaycheck] > 3600)
		{
			PlayerData[playerid][pPaycheck] = 0;
		}
		if(PlayerData[playerid][pHaulingDelay]) {
			if(--PlayerData[playerid][pHaulingDelay] == 0) {
				PlayerData[playerid][pHaulingDelay] = 0;
				SendServerMessage(playerid, "Kamu bisa melakukan misi "YELLOW"Hauling "WHITE"lagi.");
			}
		}
		if(PlayerData[playerid][pLumberDelay]) {
			if(--PlayerData[playerid][pLumberDelay] == 0) {
				PlayerData[playerid][pLumberDelay] = 0;
				SendServerMessage(playerid, "Kamu bisa bekerja sebagai "YELLOW"Lumberjack");
			}
		}
		if(PlayerData[playerid][pDrugTime]) {
			if(--PlayerData[playerid][pDrugTime] == 0) {
				PlayerData[playerid][pDrugCondition] = false;
				PlayerData[playerid][pDrugTime] = 0;
				SendServerMessage(playerid, "Kamu tidak lagi dalam pengaruh drug.");
				SetPlayerDrunkLevel(playerid, 0);
			}
		}
		if(PlayerData[playerid][pPaycheck] > 0)
		{
			PlayerData[playerid][pPaycheck]--;
			if(PlayerData[playerid][pPaycheck] <= 0)
			{
				if(PlayerData[playerid][pAutoPaycheck]) {
					PayCheck(playerid);
				}
				else {

					SendServerMessage(playerid, "Kamu sudah bisa mengambil Paycheck sekarang!");
					PlayerData[playerid][pPaycheck] = 0;
				}
			}
		}
		if(PlayerData[playerid][pCarryingPizza])
		{
			SetPlayerArmedWeapon(playerid, 0);
		}
		if(PlayerData[playerid][pPizza] > 0 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 586)
			{
			    if(PlayerData[playerid][pPizzaTime] < 90)
				{
					PlayerData[playerid][pPizzaTime]++;
				}
			}
			else
			{
			    PlayerData[playerid][pPizza] = 0;

			    HideWaypoint(playerid);
			    SendClientMessage(playerid, COLOR_ORANGE, "PIZZA: {ffffff}Pengiriman otomatis batal, karena kamu keluar dari kendaraan!");
			}
		}
	}
	return 1;
}

ptask TimerBoomBoxCheck[1000](playerid) {

	new 
		boomboxid;
		
	if((PlayerData[playerid][pTogMusic]) || (PlayerData[playerid][pBoomboxListen] != INVALID_PLAYER_ID && GetNearbyBoombox(playerid) != PlayerData[playerid][pBoomboxListen]))
	{
		PlayerData[playerid][pBoomboxListen] = INVALID_PLAYER_ID;

		if(PlayerData[playerid][pStreamType] == MUSIC_BOOMBOX)
		{
			StopAudioStreamForPlayer(playerid);
			PlayerData[playerid][pStreamType] = MUSIC_NONE;
		}
	}
	if((!PlayerData[playerid][pTogMusic]) && ((boomboxid = GetNearbyBoombox(playerid)) != INVALID_PLAYER_ID && PlayerData[playerid][pBoomboxListen] != boomboxid))
	{
		PlayerData[playerid][pBoomboxListen] = boomboxid;

		if(PlayerData[playerid][pStreamType] == MUSIC_NONE)
		{
			PlayAudioStreamForPlayer(playerid, PlayerData[boomboxid][pBoomboxURL]);
			PlayerData[playerid][pStreamType] = MUSIC_BOOMBOX;
		}
	}
	return 1;
}
ptask TimerPlayerCheck[1000](playerid) {

	if(!PlayerData[playerid][pSpawned])
		return 0;

	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && PlayerData[playerid][pInjured])
		RemovePlayerFromVehicle(playerid);

    if(!PlayerData[playerid][pTogHud])
    {
		new String[256],year,month,day,hours,minutes,seconds;
		getdate(year, month, day), gettime(hours, minutes, seconds);

		format(String, sizeof String, "%d/%s%d/%s%d", day, ((month < 10) ? ("0") : ("")), month, (year < 10) ? ("0") : (""), year);
		PlayerTextDrawSetString(playerid, TIMEGUI[playerid][1], String);
		format(String, sizeof String, "%s%d:%s%d:%s%d", (hours < 10) ? ("0") : (""), hours, (minutes < 10) ? ("0") : (""), minutes, (seconds < 10) ? ("0") : (""), seconds);
		PlayerTextDrawSetString(playerid, TIMEGUI[playerid][0], String);
    }
	if(PlayerData[playerid][pIDCard] && PlayerData[playerid][pIDCardExpired] != 0) {

		if(PlayerData[playerid][pIDCardExpired] < gettime()) {
			PlayerData[playerid][pIDCardExpired] = 0;
			SendServerMessage(playerid, "ID Card milikmu tidak lagi valid, perpanjang ID Card di CityHall.");
			PlayerData[playerid][pJob] = JOB_NONE;
		}
	}
	if(GetPlayerPing(playerid) > 800) {
            SendClientMessageToAllEx(X11_TOMATO_1, "BotCmd: %s have been kicked for high ping: (%d/800ms)", GetName(playerid), GetPlayerPing(playerid));
            SendClientMessageEx(playerid, X11_TURQUOISE_1,"Anda telah di kick karena ping melebihi matas maksimal: (%d/800ms)", GetPlayerPing(playerid));
            KickEx(playerid);
	}
	return 1;
}

task timer_OnGlobalSec[1000]()
{
	if(rob_biz_delay > 0) {
		if(--rob_biz_delay <= 0) {
			rob_biz_delay = 0;
		}
	}
	return 1;
}


ptask VehicleSpamCheck[3000](playerid) {

	if(!IsPlayerSpawned(playerid))
		return 0;

	if(EnterVehicle[playerid] > 0)
		EnterVehicle[playerid]--;

	return 1;
}

task OnSaveServerData[180000]() {
	SaveServerData();
	return 1;
}