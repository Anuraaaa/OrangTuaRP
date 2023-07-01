stock DisplayTemporaryDamages(targetid, playerid)
{
    if(!CountDamages(playerid)) 
    	return SendErrorMessage(targetid, "There is no temporary damages on %s", ReturnName(targetid));

    new gsText[1000];
    format(gsText, sizeof(gsText), "Bullet(s)\tWeapon\tBodypart\n");
    forex(i, MAX_BODY_PARTS)
    {
        forex(z, MAX_WEAPONS)
        {
            if(!Damage[playerid][i][z]) 
            	continue;

            format(gsText, sizeof(gsText), "%s%d\t%s\t%s\n", gsText, Damage[playerid][i][z], ReturnWeaponName(z), GetBodyPartName(i + 3));
        }
    }
    return ShowPlayerDialog(targetid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, sprintf("%s temporary damages", ReturnName(playerid)), gsText, "Close", "");
}

CMD:damage(playerid, params[])
{
    if(!PlayerData[playerid][pSpawned])
        return SendErrorMessage(playerid, "You're not spawned.");
        
    new targetid;
    if(sscanf(params, "u", targetid))
        return DisplayTemporaryDamages(playerid, playerid);

    if (targetid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, targetid, 5.0))
        return SendErrorMessage(playerid, "That player is disconnected or not near you.");
        
    DisplayTemporaryDamages(playerid, targetid);
    return 1;   
}
