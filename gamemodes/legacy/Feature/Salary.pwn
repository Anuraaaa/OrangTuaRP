AddSalary(playerid, name[], amount)
{
	new query[512];
	mysql_format(sqlcon, query, sizeof(query), "INSERT INTO playersalary(owner, name, amount, date) VALUES ('%d', '%s', '%d', CURRENT_TIMESTAMP())", PlayerData[playerid][pID], name, amount);
	mysql_tquery(sqlcon, query);
	PlayerData[playerid][pSalary] += amount;

	Log_Write("Logs/salary_log.txt", "[%s] %s(%s) has issued $%s salary from %s.", ReturnDate(), GetName(playerid, false), GetUsername(playerid), FormatNumber(amount), name);
	return 1;
}

ShowPlayerSalary(playerid, targetid)
{
	new query[256];
	mysql_format(sqlcon, query, sizeof(query), "SELECT * FROM playersalary WHERE owner = '%d' ORDER BY id ASC", PlayerData[targetid][pID]);
	mysql_tquery(sqlcon, query, "OnSalaryChecked", "dd", playerid, targetid);
	return 1;
}

function OnSalaryChecked(playerid, targetid) {

	new rows = cache_num_rows(), list[2056], name[32], date[40], amount, total_salary = 0;
	if(rows)
	{
	    format(list, sizeof(list), "{FFFFFF}Name\t{FFFFFF}Amount\t{FFFFFF}Date\n");
		for(new i; i < rows; ++i)
	    {
			cache_get_value_name(i, "name", name);
			cache_get_value_name(i, "date", date);
			cache_get_value_name_int(i, "amount", amount);
			total_salary += amount;

			format(list, sizeof(list), "%s{FFFFFF}%s\t{00FF00}$%s\t{FFFFFF}%s\n", list, name, FormatNumber(amount), date);
		}
		new title[48];
		format(title, sizeof(title), "Total Salary: $%s", FormatNumber(total_salary));
		ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, title, list, "Close", "");
	}
	else
	{
		SendServerMessage(playerid, "There is no Salary to display.");
	}
	return 1;
}
CMD:salary(playerid, params[])
{
	ShowPlayerSalary(playerid, playerid);
	return 1;
}

CMD:asalary(playerid, params[]) {

	if(PlayerData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	new targetid;

	if(sscanf(params, "u", targetid))
		return SendSyntaxMessage(playerid, "/asalary [playerid/PartOfName]");

	if(targetid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "You have specified invalid player.");

	ShowPlayerSalary(playerid, targetid);

	return 1;
}