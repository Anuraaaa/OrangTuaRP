#include <YSI_Coding\y_hooks>
hook OnPlayerConnect(playerid) {
    MarryOffer[playerid] = INVALID_PLAYER_ID;
}


ShowMarriageCertificate(playerid, showto) {

}

CMD:propose(playerid, params[]) {
    new targetid;

    if(isequal(MarryWith[playerid], "Unknown")) {
        if(GetMoney(playerid) < 200000)
            return SendErrorMessage(playerid, "The marriage & reception costs $2,000.00!");

        if(sscanf(params, "u", targetid))
            return SendSyntaxMessage(playerid, "/propose [playerid/PartOfName]");

        if(!IsPlayerNearPlayer(playerid, targetid, 5.0))
            return SendErrorMessage(playerid, "That player is disconnected or not near you.");

        if(!isequal(MarryWith[targetid], "Unknown")) 
            return SendErrorMessage(playerid, "That player is already in a marriage.");

        if(PlayerData[targetid][pGender] == PlayerData[playerid][pGender])
            return SendErrorMessage(playerid, "Come one.. you're not gonna be a %s person.", (PlayerData[playerid][pGender] == 1) ? ("Gay") : ("Lesbians"));

        MarryOffer[targetid] = playerid;
        SendClientMessageEx(playerid, X11_LIGHTBLUE, "MARRIAGE: "WHITE"You've proposed to "YELLOW"%s"WHITE", awaiting his/her approval.", GetName(targetid, false));
        SendClientMessageEx(targetid, X11_LIGHTBLUE, "MARRIAGE: "YELLOW"%s "WHITE"just proposed you "CYAN"(/accept marriage) "WHITE"to accept.", GetName(playerid, false));    
    }
    else SendErrorMessage(playerid, "You have already marriage someone.");

    return 1;
}
CMD:showmrctf(playerid, params[]) {

    if(isequal(MarryWith[playerid], "Unknown")) 
        return SendErrorMessage(playerid, "You are not in a Marriage.");

    new Cache:result = mysql_query(sqlcon, sprintf("SELECT * FROM `characters` WHERE `Name` = '%s' LIMIT 1;", MarryWith[playerid]));
    return 1;
}