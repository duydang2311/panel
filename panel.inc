#if defined _panel_included
    #endinput
#endif

#define _panel_included

/*
    Callback: 
        Panel_OnSelect(playerid, panel_id, item_id)
            item_id: default -> item index
            item_id: PREVIOUS_BUTTON_ITEM -> previous button
            item_id: NEXT_BUTTON_ITEM -> next button

    Functions: 
        Panel_Show(playerid, panel_id, items[], item_size = MAX_PANEL_ITEMS, max_page = 1);
        Panel_Destroy(playerid);
        Panel_UpdatePage(playerid, page, items[], item_size = MAX_PANEL_ITEMS);
        Panel_NextPage(playerid, items[], item_size = MAX_PANEL_ITEMS);
        Panel_PreviousPage(playerid, items[], item_size = MAX_PANEL_ITEMS);
        Panel_GetCurrentPage(playerid);
        Panel_GetMaxPage(playerid);
        Panel_GetId(playerid);
*/

const MAX_PANEL_ITEMS = 10;
const PREVIOUS_BUTTON_ITEM = -1;
const NEXT_BUTTON_ITEM = -2; 

static const Float:FIRST_ITEM_POS_X = 97.000000;
static const Float:FIRST_ITEM_POS_Y = 132.000000;

static const Float:itemPositionOffsets[MAX_PANEL_ITEMS][] = {
    {0.0000, 0.0000},
    {90.0000, 0.0000},
    {90.0000, 0.0000},
    {90.0000, 0.0000},
    {90.0000, 0.0000},
    {0.0000, 90.0000},
    {90.0000, 90.0000},
    {90.0000, 90.0000},
    {90.0000, 90.0000},
    {90.0000, 90.0000}
};

static enum e_PANEL_DATA
{
    panel_Id,
    panel_Current_Page,
    panel_Max_Page
}

static panelData[MAX_PLAYERS][e_PANEL_DATA];

static PlayerText:td_Panel_Container_Box[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...},
    PlayerText:td_Panel_Items[MAX_PLAYERS][MAX_PANEL_ITEMS] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...},
    PlayerText:td_Panel_Name[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...},
    PlayerText:td_Panel_Page_Box[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...},
    PlayerText:td_Panel_Page_Text[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...},
    PlayerText:td_Panel_Previous_Button[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...},
    PlayerText:td_Panel_Next_Button[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};

stock Panel_Show(const playerid, const panel_id, const items[], const item_size = MAX_PANEL_ITEMS, const max_page = 1)
{
    if(panel_id < 0)
    {
        return Panel_Destroy(playerid);
    }
    
    panelData[playerid][panel_Id] = panel_id;
    panelData[playerid][panel_Current_Page] = 1;
    panelData[playerid][panel_Max_Page] = max_page;
    
    if(td_Panel_Container_Box[playerid] == PlayerText:INVALID_TEXT_DRAW)
    {
        td_Panel_Container_Box[playerid] = CreatePlayerTextDraw(playerid, 320.000000, 130.000000, "_");
        PlayerTextDrawFont(playerid, td_Panel_Container_Box[playerid], 1);
        PlayerTextDrawLetterSize(playerid, td_Panel_Container_Box[playerid], 0.999999, 22.000003);
        PlayerTextDrawTextSize(playerid, td_Panel_Container_Box[playerid], 358.500000, 449.000000);
        PlayerTextDrawSetOutline(playerid, td_Panel_Container_Box[playerid], 1);
        PlayerTextDrawSetShadow(playerid, td_Panel_Container_Box[playerid], 0);
        PlayerTextDrawAlignment(playerid, td_Panel_Container_Box[playerid], 2);
        PlayerTextDrawColor(playerid, td_Panel_Container_Box[playerid], -1);
        PlayerTextDrawBackgroundColor(playerid, td_Panel_Container_Box[playerid], 255);
        PlayerTextDrawBoxColor(playerid, td_Panel_Container_Box[playerid], 757935615);
        PlayerTextDrawUseBox(playerid, td_Panel_Container_Box[playerid], 1);
        PlayerTextDrawSetProportional(playerid, td_Panel_Container_Box[playerid], 1);
        PlayerTextDrawSetSelectable(playerid, td_Panel_Container_Box[playerid], 0);
    }

    for(new i = 0; i < item_size; i++)
    {
        if(td_Panel_Items[playerid][i] == PlayerText:INVALID_TEXT_DRAW)
        {
            td_Panel_Items[playerid][i] = CreatePlayerTextDraw(playerid, FIRST_ITEM_POS_X + itemPositionOffsets[i][0], FIRST_ITEM_POS_Y + itemPositionOffsets[i][1], "Preview_Model");
            PlayerTextDrawFont(playerid, td_Panel_Items[playerid][i], 5);
            PlayerTextDrawLetterSize(playerid, td_Panel_Items[playerid][i], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, td_Panel_Items[playerid][i], 86.000000, 86.000000);
            PlayerTextDrawSetOutline(playerid, td_Panel_Items[playerid][i], 0);
            PlayerTextDrawSetShadow(playerid, td_Panel_Items[playerid][i], 0);
            PlayerTextDrawAlignment(playerid, td_Panel_Items[playerid][i], 1);
            PlayerTextDrawColor(playerid, td_Panel_Items[playerid][i], -1);
            PlayerTextDrawBackgroundColor(playerid, td_Panel_Items[playerid][i], -294500353);
            PlayerTextDrawBoxColor(playerid, td_Panel_Items[playerid][i], 255);
            PlayerTextDrawUseBox(playerid, td_Panel_Items[playerid][i], 0);
            PlayerTextDrawSetProportional(playerid, td_Panel_Items[playerid][i], 1);
            PlayerTextDrawSetSelectable(playerid, td_Panel_Items[playerid][i], 1);
            PlayerTextDrawSetPreviewModel(playerid, td_Panel_Items[playerid][i], items[i]);
            PlayerTextDrawSetPreviewRot(playerid, td_Panel_Items[playerid][i], -10.000000, 0.000000, -20.000000, 1.000000);
            PlayerTextDrawSetPreviewVehCol(playerid, td_Panel_Items[playerid][i], 1, 1);
        }
        else
        {
            PlayerTextDrawSetPreviewModel(playerid, td_Panel_Items[playerid][i], items[i]);
        }
        PlayerTextDrawShow(playerid, td_Panel_Items[playerid][i]);
    }

    if(td_Panel_Name[playerid] == PlayerText:INVALID_TEXT_DRAW)
    {
        td_Panel_Name[playerid] = CreatePlayerTextDraw(playerid, 97.000000, 309.000000, "PANEL_NAME");
        PlayerTextDrawFont(playerid, td_Panel_Name[playerid], 3);
        PlayerTextDrawLetterSize(playerid, td_Panel_Name[playerid], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, td_Panel_Name[playerid], 220.000000, -16.500000);
        PlayerTextDrawSetOutline(playerid, td_Panel_Name[playerid], 1);
        PlayerTextDrawSetShadow(playerid, td_Panel_Name[playerid], 0);
        PlayerTextDrawAlignment(playerid, td_Panel_Name[playerid], 1);
        PlayerTextDrawColor(playerid, td_Panel_Name[playerid], -1);
        PlayerTextDrawBackgroundColor(playerid, td_Panel_Name[playerid], 255);
        PlayerTextDrawBoxColor(playerid, td_Panel_Name[playerid], 50);
        PlayerTextDrawUseBox(playerid, td_Panel_Name[playerid], 0);
        PlayerTextDrawSetProportional(playerid, td_Panel_Name[playerid], 1);
        PlayerTextDrawSetSelectable(playerid, td_Panel_Name[playerid], 0);
    }

    if(panelData[playerid][panel_Max_Page] <= 1)
    {
        if(td_Panel_Page_Box[playerid] == PlayerText:INVALID_TEXT_DRAW)
        {
            td_Panel_Page_Box[playerid] = CreatePlayerTextDraw(playerid, 517.000000, 313.000000, "_");
            PlayerTextDrawFont(playerid, td_Panel_Page_Box[playerid], 1);
            PlayerTextDrawLetterSize(playerid, td_Panel_Page_Box[playerid], 0.600000, 1.200002);
            PlayerTextDrawTextSize(playerid, td_Panel_Page_Box[playerid], 298.500000, 46.000000);
            PlayerTextDrawSetOutline(playerid, td_Panel_Page_Box[playerid], 1);
            PlayerTextDrawSetShadow(playerid, td_Panel_Page_Box[playerid], 0);
            PlayerTextDrawAlignment(playerid, td_Panel_Page_Box[playerid], 2);
            PlayerTextDrawColor(playerid, td_Panel_Page_Box[playerid], -1);
            PlayerTextDrawBackgroundColor(playerid, td_Panel_Page_Box[playerid], 255);
            PlayerTextDrawBoxColor(playerid, td_Panel_Page_Box[playerid], 731415807);
            PlayerTextDrawUseBox(playerid, td_Panel_Page_Box[playerid], 1);
            PlayerTextDrawSetProportional(playerid, td_Panel_Page_Box[playerid], 1);
            PlayerTextDrawSetSelectable(playerid, td_Panel_Page_Box[playerid], 0);
        }

        new string[11];
        format(string, sizeof(string), "%02d/%02d", panelData[playerid][panel_Current_Page], panelData[playerid][panel_Max_Page]);
        if(td_Panel_Page_Text[playerid] == PlayerText:INVALID_TEXT_DRAW)
        {
            td_Panel_Page_Text[playerid] = CreatePlayerTextDraw(playerid, 517.000000, 313.000000, string);
            PlayerTextDrawFont(playerid, td_Panel_Page_Text[playerid], 1);
            PlayerTextDrawLetterSize(playerid, td_Panel_Page_Text[playerid], 0.300000, 1.200000);
            PlayerTextDrawTextSize(playerid, td_Panel_Page_Text[playerid], 12.000000, 27.000000);
            PlayerTextDrawSetOutline(playerid, td_Panel_Page_Text[playerid], 1);
            PlayerTextDrawSetShadow(playerid, td_Panel_Page_Text[playerid], 0);
            PlayerTextDrawAlignment(playerid, td_Panel_Page_Text[playerid], 2);
            PlayerTextDrawColor(playerid, td_Panel_Page_Text[playerid], -1);
            PlayerTextDrawBackgroundColor(playerid, td_Panel_Page_Text[playerid], 255);
            PlayerTextDrawBoxColor(playerid, td_Panel_Page_Text[playerid], 0);
            PlayerTextDrawUseBox(playerid, td_Panel_Page_Text[playerid], 1);
            PlayerTextDrawSetProportional(playerid, td_Panel_Page_Text[playerid], 1);
            PlayerTextDrawSetSelectable(playerid, td_Panel_Page_Text[playerid], 1);
        }
        else PlayerTextDrawSetString(playerid, td_Panel_Page_Text[playerid], string);

        if(td_Panel_Previous_Button[playerid] == PlayerText:INVALID_TEXT_DRAW)
        {
            td_Panel_Previous_Button[playerid] = CreatePlayerTextDraw(playerid, 497.000000, 313.000000, "<");
            PlayerTextDrawFont(playerid, td_Panel_Previous_Button[playerid], 3);
            PlayerTextDrawLetterSize(playerid, td_Panel_Previous_Button[playerid], 0.300000, 1.200000);
            PlayerTextDrawTextSize(playerid, td_Panel_Previous_Button[playerid], 10.000000, 6.000000);
            PlayerTextDrawSetOutline(playerid, td_Panel_Previous_Button[playerid], 1);
            PlayerTextDrawSetShadow(playerid, td_Panel_Previous_Button[playerid], 0);
            PlayerTextDrawAlignment(playerid, td_Panel_Previous_Button[playerid], 2);
            PlayerTextDrawColor(playerid, td_Panel_Previous_Button[playerid], -1);
            PlayerTextDrawBackgroundColor(playerid, td_Panel_Previous_Button[playerid], 255);
            PlayerTextDrawBoxColor(playerid, td_Panel_Previous_Button[playerid], 0);
            PlayerTextDrawUseBox(playerid, td_Panel_Previous_Button[playerid], 1);
            PlayerTextDrawSetProportional(playerid, td_Panel_Previous_Button[playerid], 1);
            PlayerTextDrawSetSelectable(playerid, td_Panel_Previous_Button[playerid], 1);
        }

        if(td_Panel_Next_Button[playerid] == PlayerText:INVALID_TEXT_DRAW)
        {
            td_Panel_Next_Button[playerid] = CreatePlayerTextDraw(playerid, 537.000000, 313.000000, ">");
            PlayerTextDrawFont(playerid, td_Panel_Next_Button[playerid], 3);
            PlayerTextDrawLetterSize(playerid, td_Panel_Next_Button[playerid], 0.300000, 1.200000);
            PlayerTextDrawTextSize(playerid, td_Panel_Next_Button[playerid], 10.000000, 6.000000);
            PlayerTextDrawSetOutline(playerid, td_Panel_Next_Button[playerid], 1);
            PlayerTextDrawSetShadow(playerid, td_Panel_Next_Button[playerid], 0);
            PlayerTextDrawAlignment(playerid, td_Panel_Next_Button[playerid], 2);
            PlayerTextDrawColor(playerid, td_Panel_Next_Button[playerid], -1);
            PlayerTextDrawBackgroundColor(playerid, td_Panel_Next_Button[playerid], 255);
            PlayerTextDrawBoxColor(playerid, td_Panel_Next_Button[playerid], 0);
            PlayerTextDrawUseBox(playerid, td_Panel_Next_Button[playerid], 1);
            PlayerTextDrawSetProportional(playerid, td_Panel_Next_Button[playerid], 1);
            PlayerTextDrawSetSelectable(playerid, td_Panel_Next_Button[playerid], 1);
        }

        PlayerTextDrawShow(playerid, td_Panel_Page_Box[playerid]);
        PlayerTextDrawShow(playerid, td_Panel_Page_Text[playerid]);
        PlayerTextDrawShow(playerid, td_Panel_Previous_Button[playerid]);
        PlayerTextDrawShow(playerid, td_Panel_Next_Button[playerid]);
    }
    else
    {
        if(td_Panel_Page_Box[playerid] != PlayerText:INVALID_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, td_Panel_Page_Box[playerid]);
            td_Panel_Page_Box[playerid] = PlayerText:INVALID_TEXT_DRAW;
        }

        if(td_Panel_Page_Text[playerid] != PlayerText:INVALID_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, td_Panel_Page_Text[playerid]);
            td_Panel_Page_Text[playerid] = PlayerText:INVALID_TEXT_DRAW;
        }

        if(td_Panel_Previous_Button[playerid] != PlayerText:INVALID_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, td_Panel_Previous_Button[playerid]);
            td_Panel_Previous_Button[playerid] = PlayerText:INVALID_TEXT_DRAW;
        }

        if(td_Panel_Next_Button[playerid] != PlayerText:INVALID_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, td_Panel_Next_Button[playerid]);
            td_Panel_Next_Button[playerid] = PlayerText:INVALID_TEXT_DRAW;
        }
    }

    PlayerTextDrawShow(playerid, td_Panel_Container_Box[playerid]);
    PlayerTextDrawShow(playerid, td_Panel_Name[playerid]);
    return 1;
}

stock Panel_UpdatePage(const playerid, const page, const items[], const item_size = MAX_PANEL_ITEMS)
{
    if(panelData[playerid][panel_Id] < 0)
    {
        return Panel_Destroy(playerid);
    }
    
    if(page < 0)
    {
        page = 1;
    }
    else if(page > panelData[playerid][panel_Max_Page])
    {
        page = panelData[playerid][panel_Max_Page]; 
    }

    panelData[playerid][panel_Current_Page] = page;
    
    for(new i = 0; i < MAX_PANEL_ITEMS; i++)
    {
        if(i < item_size)
        {
            if(td_Panel_Items[playerid][i] == PlayerText:INVALID_TEXT_DRAW)
            {
                td_Panel_Items[playerid][i] = CreatePlayerTextDraw(playerid, FIRST_ITEM_POS_X + itemPositionOffsets[i][0], FIRST_ITEM_POS_Y + itemPositionOffsets[i][1], "Preview_Model");
                PlayerTextDrawFont(playerid, td_Panel_Items[playerid][i], 5);
                PlayerTextDrawLetterSize(playerid, td_Panel_Items[playerid][i], 0.600000, 2.000000);
                PlayerTextDrawTextSize(playerid, td_Panel_Items[playerid][i], 86.000000, 86.000000);
                PlayerTextDrawSetOutline(playerid, td_Panel_Items[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, td_Panel_Items[playerid][i], 0);
                PlayerTextDrawAlignment(playerid, td_Panel_Items[playerid][i], 1);
                PlayerTextDrawColor(playerid, td_Panel_Items[playerid][i], -1);
                PlayerTextDrawBackgroundColor(playerid, td_Panel_Items[playerid][i], -294500353);
                PlayerTextDrawBoxColor(playerid, td_Panel_Items[playerid][i], 255);
                PlayerTextDrawUseBox(playerid, td_Panel_Items[playerid][i], 0);
                PlayerTextDrawSetProportional(playerid, td_Panel_Items[playerid][i], 1);
                PlayerTextDrawSetSelectable(playerid, td_Panel_Items[playerid][i], 1);
                PlayerTextDrawSetPreviewModel(playerid, td_Panel_Items[playerid][i], items[i]);
                PlayerTextDrawSetPreviewRot(playerid, td_Panel_Items[playerid][i], -10.000000, 0.000000, -20.000000, 1.000000);
                PlayerTextDrawSetPreviewVehCol(playerid, td_Panel_Items[playerid][i], 1, 1);
            }
            else
            {
                PlayerTextDrawSetPreviewModel(playerid, td_Panel_Items[playerid][i], items[i]);
            }
            PlayerTextDrawShow(playerid, td_Panel_Items[playerid][i]);
        }
        else
        {
            if(td_Panel_Items[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
            {
                PlayerTextDrawDestroy(playerid, td_Panel_Items[playerid][i]);
                td_Panel_Items[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            }
        }
    }

    new string[11];
    format(string, sizeof(string), "%02d/%02d", page, panelData[playerid][panel_Max_Page]);
    PlayerTextDrawSetString(playerid, td_Panel_Name[playerid]);
    return 1;
}

stock Panel_NextPage(const playerid, const items[], const item_size = MAX_PANEL_ITEMS)
{
    return Panel_UpdatePage(playerid, panelData[playerid][panel_Current_Page] + 1, items, item_size);
}

stock Panel_PreviousPage(const playerid, const items[], const item_size = MAX_PANEL_ITEMS)
{
    return Panel_UpdatePage(playerid, panelData[playerid][panel_Current_Page] - 1, items, item_size);
}

stock Panel_Destroy(const playerid)
{
    panelData[playerid][panel_Id] = -1;
    panelData[playerid][panel_Current_Page] = 1;
    panelData[playerid][panel_Max_Page] = 1;

    if(td_Panel_Container_Box[playerid] != PlayerText:INVALID_TEXT_DRAW)
    {
        PlayerTextDrawDestroy(playerid, td_Panel_Container_Box[playerid]);
        td_Panel_Container_Box[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    for(new i = 0; i < MAX_PANEL_ITEMS; i++)
    {
        if(td_Panel_Items[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, td_Panel_Items[playerid][i]);
            td_Panel_Items[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
        }
    }

    if(td_Panel_Name[playerid] != PlayerText:INVALID_TEXT_DRAW)
    {
        PlayerTextDrawDestroy(playerid, td_Panel_Name[playerid]);
        td_Panel_Name[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if(td_Panel_Page_Box[playerid] != PlayerText:INVALID_TEXT_DRAW)
    {
        PlayerTextDrawDestroy(playerid, td_Panel_Page_Box[playerid]);
        td_Panel_Page_Box[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if(td_Panel_Page_Text[playerid] != PlayerText:INVALID_TEXT_DRAW)
    {
        PlayerTextDrawDestroy(playerid, td_Panel_Page_Text[playerid]);
        td_Panel_Page_Text[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if(td_Panel_Previous_Button[playerid] != PlayerText:INVALID_TEXT_DRAW)
    {
        PlayerTextDrawDestroy(playerid, td_Panel_Previous_Button[playerid]);
        td_Panel_Previous_Button[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if(td_Panel_Next_Button[playerid] != PlayerText:INVALID_TEXT_DRAW)
    {
        PlayerTextDrawDestroy(playerid, td_Panel_Next_Button[playerid]);
        td_Panel_Next_Button[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    return 1;
}

stock Panel_GetCurrentPage(const playerid)
{
    return panelData[playerid][panel_Current_Page];
}

stock Panel_GetMaxPage(const playerid)
{
    return panelData[playerid][panel_Max_Page];
}

stock Panel_GetId(const playerid)
{
    return panelData[playerid][panel_Id];
}

public OnPlayerConnect(playerid)
{
    panelData[playerid][panel_Id] = -1;
    panelData[playerid][panel_Current_Page] = 1;
    panelData[playerid][panel_Max_Page] = 1;
    
    Panel_Destroy(playerid);

	CallLocalFunction("panel@OnPlayerConnect", "i", playerid);
    return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    if(panelData[playerid][panel_Id] != -1)
    {
        for(new i = 0; i < MAX_PANEL_ITEMS; i++)
        {
            if(playertextid == td_Panel_Items[playerid][i])
            {
                CallLocalFunction("Panel_OnSelect", "iii", playerid, panelData[playerid][panel_Id], (panelData[playerid][panel_Current_Page] - 1) * MAX_PANEL_ITEMS + i);
                return 1;
            }
        }

        if(playertextid == td_Panel_Previous_Button[playerid])
        {
            CallLocalFunction("Panel_OnSelect", "iii", playerid, panelData[playerid][panel_Id], PREVIOUS_BUTTON_ITEM);
            return 1;
        }

        if(playertextid == td_Panel_Next_Button[playerid])
        {
            CallLocalFunction("Panel_OnSelect", "iii", playerid, panelData[playerid][panel_Id], NEXT_BUTTON_ITEM);
            return 1;
        }
    }

	CallLocalFunction("panel@OnPlayerClickPlayerTD", "ii", playerid, _:playertextid);
    return 1;
}

#if defined _ALS_OnPlayerClickPlayerTD
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw panel@OnPlayerClickPlayerTD

forward panel@OnPlayerClickPlayerTD(playerid, PlayerText:playertextid);

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect panel@OnPlayerConnect

forward panel@OnPlayerConnect(playerid);