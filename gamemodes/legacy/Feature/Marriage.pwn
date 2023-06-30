#include <YSI_Coding\y_hooks>
hook OnPlayerConnect(playerid) {
    MarryOffer[playerid] = INVALID_PLAYER_ID;
    DivorceOffer[playerid] = INVALID_PLAYER_ID;
}

/*
ShowMarriageCertificate(playerid, showto) {

}*/

CMD:propose(playerid, params[]) {
    new targetid;

    if(!IsPlayerInRangeOfPoint(playerid, 5.0, 2214.3958,-1332.6309,252.4141))
        return SendErrorMessage(playerid, "Kamu tidak berada pada propose point atau tidak didalam church.");
         
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
            return SendErrorMessage(playerid, "Come on.. you're not gonna be a %s person.", (PlayerData[playerid][pGender] == 1) ? ("Gay") : ("Lesbians"));

        MarryOffer[targetid] = playerid;
        SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Marriage) "WHITE"You've proposed to "YELLOW"%s"WHITE", awaiting his/her approval.", GetName(targetid, false));
        SendClientMessageEx(targetid, X11_LIGHTBLUE, "(Marriage) "YELLOW"%s "WHITE"just proposed you "CYAN"(/accept marriage) "WHITE"to accept.", GetName(playerid, false));    
    }
    else SendErrorMessage(playerid, "You have already married with someone.");

    return 1;
}

CMD:divorce(playerid, params[]) {

    new targetid;

    if(isequal(MarryWith[playerid], "Unknown"))
        return SendErrorMessage(playerid, "You are not married with someone.");

    if(sscanf(params, "u", targetid))
        return SendSyntaxMessage(playerid, "/divorce [playerid/PartOfName]");

    if(!IsPlayerNearPlayer(playerid, targetid, 5.0))
        return SendErrorMessage(playerid, "That player is disconnected or not near you."); 

    if(!isequal(MarryWith[targetid], GetName(playerid)))
        return SendErrorMessage(playerid, "That player is not married to you!");


    SendClientMessageEx(playerid, X11_LIGHTBLUE, "(Divorce) "WHITE"You have asking "YELLOW"%s "WHITE"for a divorce.", ReturnName(targetid));
    SendClientMessageEx(targetid, X11_LIGHTBLUE, "(Divorce) "YELLOW"%s "WHITE"is asking you for a Divorce "CYAN"(/accept divorce) "WHITE"to accept.", ReturnName(playerid));
    DivorceOffer[targetid] = playerid;
    return 1;
}