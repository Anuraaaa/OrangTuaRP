enum jobtype
{
    jobName[24],
    jobType,
}

new const Job_Type[][jobtype] =
{	
	{"None", 			JOB_NONE},
	{"Trucker", 		JOB_TRUCKER},
	{"Taxi Driver", 	JOB_TAXI},
	{"Mechanic", 		JOB_MECHANIC},
	{"Lumberjack",		JOB_LUMBERJACK},
	{"Miner",			JOB_MINER},
	{"Smuggler", 		JOB_SMUGGLER}
};
stock GetJobName(job)
{
	new str[50];
	format(str, sizeof(str), "%s", Job_Type[job][jobName]);
	return str;
}

stock SendJobMessage(job, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player)
		{
			if (CheckPlayerJob(i, job))
			{
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player)
	{
		if (CheckPlayerJob(i, job)) {
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

CMD:takejob(playerid, params[])
{
	new job;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 1077.6029, -960.2651, 1338.3207))
	{
		if(sscanf(params, "d", job))
			return SendSyntaxMessage(playerid, "/takejob [slot (1/2)]");

		if(!PlayerData[playerid][pIDCard])
			return SendErrorMessage(playerid, "Kamu harus memiliki ID Card untuk mengambil pekerjaan.");

		if(PlayerData[playerid][pIDCardExpired] == 0) 
			return SendErrorMessage(playerid, "ID Card milikmu tidak valid, kamu harus memperpanjangnya terlebih dahulu.");
			

		if(job == 1) {


			if(PlayerData[playerid][pJob] != JOB_NONE)
				return SendErrorMessage(playerid, "Silahkan keluar dari pekerjaanmu dahulu!");

			ShowPlayerDialog(playerid, DIALOG_TAKEJOB, DIALOG_STYLE_LIST, "Job Center", "Trucker\nTaxi Driver\nMechanic\nLumberjack\nMiner", "Select", "Close");
		}
		else if(job == 2) {

			if(!GetPlayerVIPLevel(playerid))
				return SendErrorMessage(playerid, "Job slot 2 hanya untuk status donater player.");

			if(PlayerData[playerid][pJob2] != JOB_NONE)
				return SendErrorMessage(playerid, "Silahkan keluar dari pekerjaanmu dahulu!");

			ShowPlayerDialog(playerid, DIALOG_TAKEJOB2, DIALOG_STYLE_LIST, "Job Center", "Trucker\nTaxi Driver\nMechanic\nLumberjack\nMiner", "Select", "Close");
		}
		else SendSyntaxMessage(playerid, "/takejob [slot (1/2)]");
	}
	else if(IsPlayerInRangeOfPoint(playerid, 3.0, -2215.5137,117.5038,35.3203)) {

		if(sscanf(params, "d", job))
			return SendSyntaxMessage(playerid, "/takejob [slot (1/2)]");
			
		if(job == 1) {


			if(PlayerData[playerid][pJob] != JOB_NONE)
				return SendErrorMessage(playerid, "Silahkan keluar dari pekerjaanmu dahulu!");

			PlayerData[playerid][pJob] = JOB_SMUGGLER;
			SendServerMessage(playerid, "Kamu sekarang adalah "YELLOW"Smuggler "WHITE"- gunakan "YELLOW"\"/help > Job Commands > Smuggler\" "WHITE"untuk bantuan.");
		}
		else if(job == 2) {

			if(!GetPlayerVIPLevel(playerid))
				return SendErrorMessage(playerid, "Job slot 2 hanya untuk status donater player.");

			if(PlayerData[playerid][pJob2] != JOB_NONE)
				return SendErrorMessage(playerid, "Silahkan keluar dari pekerjaanmu dahulu!");

			PlayerData[playerid][pJob2] = JOB_SMUGGLER;
			SendServerMessage(playerid, "Kamu sekarang adalah "YELLOW"Smuggler "WHITE"- gunakan "YELLOW"\"/help > Job Commands > Smuggler\" "WHITE"untuk bantuan.");
		}
		else SendSyntaxMessage(playerid, "/takejob [slot (1/2)]");
	}
	else SendErrorMessage(playerid,"Anda tidak berada di JobCenter atau tempat pengambilan kerja manapun!");
	return 1;
}

CMD:quitjob(playerid, params[])
{
	new job;

	if(PlayerData[playerid][pQuitjob] > 0 && PlayerData[playerid][pAdmin] < 7)
		return SendErrorMessage(playerid, "Kamu harus melakukan %d PayCheck lagi untuk quitjob!", PlayerData[playerid][pQuitjob]);

	if(sscanf(params, "d", job))
		return SendSyntaxMessage(playerid, "/quitjob [slot (1/2)]");

	if(job == 1) {

		if(PlayerData[playerid][pJob] == JOB_NONE)
			return SendErrorMessage(playerid, "Tidak ada pekerjaan pada slot ini.");

		SendServerMessage(playerid, "Kamu berhasil keluar dari pekerjaan {FFFF00}%s {FFFFFF}kamu bisa takejob lagi sekarang!", GetJobName(PlayerData[playerid][pJob]));
		PlayerData[playerid][pJob] = JOB_NONE;
	}
	else if(job == 2) {
		if(PlayerData[playerid][pJob2] == JOB_NONE)
			return SendErrorMessage(playerid, "Tidak ada pekerjaan pada slot ini.");
			
		SendServerMessage(playerid, "Kamu berhasil keluar dari pekerjaan {FFFF00}%s {FFFFFF}kamu bisa takejob lagi sekarang!", GetJobName(PlayerData[playerid][pJob2]));
		PlayerData[playerid][pJob2] = JOB_NONE;
	}
	else SendSyntaxMessage(playerid, "/quitjob [slot (1/2)]");
	return 1;
}

CMD:jobdelay(playerid, params[])
{
	new str[512];
	strcat(str, "Job Name\tTime\n");
	strcat(str, sprintf("Street Sweeper\t%d Minute\n", PlayerData[playerid][pSweeperDelay]/60));
	strcat(str, sprintf("Bus Driver\t%d Minute\n", PlayerData[playerid][pBusDelay]/60));
	strcat(str, sprintf("Trashmaster\t%d Minute\n", PlayerData[playerid][pTrashmasterDelay]/60));
	strcat(str, sprintf("Selling Fish\t%d Minute\n", PlayerData[playerid][pFishDelay]/60));
	strcat(str, sprintf("Mower\t%d Minute\n", PlayerData[playerid][pMowerDelay]/60));
	strcat(str, sprintf("Delivery Driver\t%d Minute\n", PlayerData[playerid][pDriverDelay]/60));
	strcat(str, sprintf("Lumberjack\t%d Minute\n", PlayerData[playerid][pLumberDelay]/60));
	strcat(str, sprintf("Hauling\t%d Minute\n", PlayerData[playerid][pHaulingDelay]/60));
	ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, "Delay's information", str, "Close", "");
	return 1;
}
