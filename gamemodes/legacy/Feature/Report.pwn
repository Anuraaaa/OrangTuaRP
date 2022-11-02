#include <YSI_Coding\y_hooks>

enum E_REPORT_DATA {
	reportOwner,
	reportText[144],
	reportTime,
};
new ReportData[MAX_REPORTS][E_REPORT_DATA],
	Iterator:Report<MAX_REPORTS>,
	ListedReport[MAX_PLAYERS][MAX_REPORTS],
	selectReport[MAX_PLAYERS];

Report_Show(playerid) {

	if(!Iter_Count(Report))
		return SendErrorMessage(playerid, "Tidak ada pending report saat ini.");

	new str[2012], count = 0;
	foreach(new i : Report) 
	{
		format(str, sizeof(str), "%s[%s] %s: %s\n", str, GetName(ReportData[i][reportOwner]), GetDuration(gettime() - ReportData[i][reportTime]), ReportData[i][reportText]);
		ListedReport[playerid][count++] = i;
	}
	ShowPlayerDialog(playerid, DIALOG_REPORTS, DIALOG_STYLE_LIST, "Listed Report", str, "Select",  "Close");
	return 1;
}

Report_Create(playerid, reason[]) {

	new index = INVALID_ITERATOR_SLOT;
	if((index = Iter_Alloc(Report)) != INVALID_ITERATOR_SLOT) {
		ReportData[index][reportOwner] = playerid;
		ReportData[index][reportTime] = gettime();
		format(ReportData[index][reportText], 64, reason);
	}
	return index;
}

bool:IsPlayerHaveReport(playerid) {

	new bool:have = false;
	foreach(new i : Report) if(ReportData[i][reportOwner] == playerid) {
		have = true;
		break;
	}
	return have;
}
Report_Remove(reportid, bool:remove_safe = false) {

	format(ReportData[reportid][reportText], 64, "");
	ReportData[reportid][reportOwner] = INVALID_PLAYER_ID;
	ReportData[reportid][reportTime] = 0;

	if(!remove_safe)
		Iter_Remove(Report, reportid);
	else {
		new next_js = reportid;
		Iter_SafeRemove(Report, next_js, reportid);
	}
	return 1;
}

CMD:clearreport(playerid, params[]) {
	if(PlayerData[playerid][pAdmin] < 5)
		return PermissionError(playerid);

	if(!Iter_Count(Report))
		return SendErrorMessage(playerid, "There is no pending report.");

	foreach(new reportid : Report) {
		format(ReportData[reportid][reportText], 64, "");
		ReportData[reportid][reportOwner] = INVALID_PLAYER_ID;
		ReportData[reportid][reportTime] = 0;

		new next_js = reportid;

		Iter_SafeRemove(Report, next_js, reportid);
	}
	SendAdminMessage(X11_TOMATO, "AdmCmd: %s has cleared all pending reports.", GetUsername(playerid));
	return 1;
}
CMD:report(playerid, params[]) {

	if(reportDelay[playerid])
		return SendErrorMessage(playerid, "Tunggu %d detik untuk membuat report.", reportDelay[playerid]);

	if(IsPlayerHaveReport(playerid))
		return SendErrorMessage(playerid, "Kamu masih memiliki pending report.");

	new reason[144];
	if(sscanf(params, "s[144]", reason))
		return SendSyntaxMessage(playerid, "/report [report reason]"), SendServerMessage(playerid, "Gunakan /report untuk tujuan yang valid.");

	if(strlen(reason) > 144)
		return SendErrorMessage(playerid, "Tidak bisa lebih dari 144 karakter.");

	new index = Report_Create(playerid, reason);

	if(index == INVALID_ITERATOR_SLOT)
		return SendErrorMessage(playerid, "Server ini tidak bisa menampung lebih banyak report.");

	SendAdminMessage(X11_LIGHTBLUE, "[REPORT] "YELLOW"%s(%d): "WHITE"%s.", GetName(playerid), playerid, reason);
	SendServerMessage(playerid, "Laporanmu berhasil dikirim ke administrator yang sedang online.");
	reportDelay[playerid] = 300;
	return 1;

}

CMD:reports(playerid, params[]) {
	if(PlayerData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	Report_Show(playerid);
	return 1;
}

hook OnPlayerDisconnectEx(playerid) {

	if(IsPlayerHaveReport(playerid)) {

		foreach(new reportid : Report) if(ReportData[reportid][reportOwner] == playerid)  {

			format(ReportData[reportid][reportText], 64, "");
			ReportData[reportid][reportOwner] = INVALID_PLAYER_ID;
			ReportData[reportid][reportTime] = 0;
			new next_js = reportid;
			Iter_SafeRemove(Report, next_js, reportid);
		}
	}
}
