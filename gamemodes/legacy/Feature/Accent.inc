enum accent
{
    accName[24],
    accNomor,
}

new const ListAccent[][accent] =
{
	{"None"},
	{"Indonesian Accent"},
    {"Italian Accent"},
    {"Arabic Accent"},
    {"Jamaican Accent"},
    {"Brazilian Accent"},
    {"Thai Accent"},
    {"Russian Accent"},
    {"French Accent"},
    {"American Accent"},
    {"Japanese Accent"},
    {"Turkish Accent"},
    {"Spanish Accent"}
};


CMD:accent(playerid, params[])
{
    new list[700];
    for(new i = 0; i < sizeof(ListAccent); i ++)
    {
        format(list, sizeof(list), "%s\n%s", list, ListAccent[i][accName]);
    }

	ShowPlayerDialog(playerid, DIALOG_ACCENT, DIALOG_STYLE_LIST, "Accent Options", list, "Select", "Cancel");
	return 1;
}