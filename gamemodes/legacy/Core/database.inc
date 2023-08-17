#include <YSI_Coding\y_hooks>

new MySQL:sqlcon;
new bool:sqlConnected = false; 

IsSQLConnected() {
 
    if (sqlConnected)
        return 1;
    
    return 0;
}

Database_Connect()
{
    mysql_log(ERROR | WARNING);
    sqlcon = mysql_connect_file();

    if(mysql_errno(sqlcon) != 0) {
        SendRconCommand("password otrpgaming");
        SendRconCommand("hostname Occurred error connection to database ...");

        new error[128];
        mysql_error(error, sizeof(error), sqlcon);
        printf("[Database] Failed! Error: [%d] %s", mysql_errno(sqlcon), error);
        sqlConnected = false;
		return 0;
    }
    else
    {
        printf("[Database] Connected!");
        sqlConnected = true;
    }
	return 1;
}


hook OnGameModeInit() {
    Database_Connect();
}