new Auction;

#include <YSI_Coding\y_hooks>

new 
    int_auction, 
    int_auction_text[2],
    AuctionTime,
    AuctionType,
    AuctionCount,
    AuctionStart,
    AuctionBid,
    AuctionLelang[24],
    AuctionHighest[MAX_PLAYER_NAME],
    FollowAuction[MAX_PLAYERS];

Auction_CreateMap()
{
    int_auction = CreateDynamicObject(1297, 1334.425537, 1570.385620, 9.584179, 0.000000, -6.700006, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 19480, "signsurf", "sign", 0x00000000);
    int_auction = CreateDynamicObject(1297, 1334.425537, 1576.895751, 9.584179, 0.000000, -6.700006, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 19480, "signsurf", "sign", 0x00000000);
    int_auction = CreateDynamicObject(18762, 1367.361694, 1578.859619, 10.292508, 0.000000, 90.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 3979, "civic01_lan", "crazy paving", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(18980, 1370.440307, 1576.848388, 10.288434, 0.000000, 90.000015, 135.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 3979, "civic01_lan", "crazy paving", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(8661, 1347.412719, 1573.830810, 9.852499, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 15041, "bigsfsave", "carp11S", 0xFF1C4966);
    int_auction = CreateDynamicObject(19447, 1362.611572, 1573.911499, 9.792497, 0.000007, 90.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 15041, "bigsfsave", "carp11S", 0xFF555555);
    int_auction = CreateDynamicObject(19447, 1353.081542, 1573.911499, 9.792497, 0.000007, 90.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 15041, "bigsfsave", "carp11S", 0xFF555555);
    int_auction = CreateDynamicObject(19447, 1343.581909, 1573.911499, 9.792497, 0.000007, 90.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 15041, "bigsfsave", "carp11S", 0xFF555555);
    int_auction = CreateDynamicObject(19447, 1340.481933, 1580.481811, 9.792497, 0.000000, 90.000000, 180.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 15041, "bigsfsave", "carp11S", 0xFF555555);
    int_auction = CreateDynamicObject(19447, 1340.481933, 1567.372070, 9.792497, 0.000000, 90.000000, 180.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 15041, "bigsfsave", "carp11S", 0xFF555555);
    int_auction = CreateDynamicObject(18766, 1336.337768, 1571.308105, 9.878437, 89.999992, 179.999984, -89.999969, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18766, 1333.837524, 1578.778320, 9.878437, 89.999992, -90.000000, -89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18766, 1331.347778, 1571.308105, 9.878437, 89.999992, 179.999984, -89.999969, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18766, 1333.737426, 1582.449340, 9.578433, 89.999992, -89.999992, -90.000022, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18766, 1333.737426, 1564.639404, 9.578433, 89.999992, -89.999992, -90.000022, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF3C4D55);
    int_auction = CreateDynamicObject(19377, 1344.109863, 1564.002197, 9.878436, 0.000000, 0.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1353.679565, 1564.002197, 5.448434, 0.000000, 0.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1363.309326, 1564.002197, 9.868432, 0.000000, 0.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1353.679565, 1564.002197, 18.728437, 0.000007, 0.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 3979, "civic01_lan", "crazy paving", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1344.109863, 1583.482666, 9.878436, 0.000007, 0.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1353.679565, 1583.482666, 5.448434, 0.000007, 0.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1363.309326, 1583.482666, 9.868432, 0.000007, 0.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1353.679565, 1583.482666, 18.728437, 0.000014, 0.000000, 89.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 3979, "civic01_lan", "crazy paving", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1364.051879, 1564.744750, 9.868432, 0.000000, 0.000000, 135.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1364.051757, 1582.740234, 9.868432, 0.000007, 0.000000, 44.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1367.439697, 1568.742065, 9.868432, 0.000000, 0.000000, 180.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1367.439697, 1578.362060, 9.868432, 0.000000, 0.000000, 180.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1335.439575, 1581.641967, 9.868432, 0.000000, 0.000000, 180.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19377, 1335.439575, 1565.772583, 9.868432, 0.000000, 0.000000, 180.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19377, 1334.530029, 1564.002197, 9.878436, 0.000007, 0.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1334.530029, 1583.482666, 9.878436, 0.000014, 0.000000, 89.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19377, 1331.429443, 1573.782714, 9.868432, 0.000000, 0.000000, 180.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19434, 1365.217407, 1581.318969, 12.092498, 0.000000, 0.000000, 45.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(19434, 1364.071655, 1581.898559, 12.632498, 0.000000, 0.000000, 45.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19434, 1365.931518, 1580.038696, 12.632498, 0.000000, 0.000000, 45.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19434, 1365.351928, 1566.511230, 12.092498, 0.000004, 0.000004, -45.000034, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(19434, 1365.931518, 1567.656982, 12.632498, 0.000004, 0.000004, -45.000034, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19434, 1364.071655, 1565.797119, 12.632497, 0.000003, 0.000003, -45.000034, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(2773, 1341.830444, 1566.713012, 10.418437, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1341.830444, 1569.363037, 10.418437, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1341.830444, 1578.274658, 10.418437, 0.000000, 0.000014, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1341.830444, 1580.924682, 10.418437, 0.000000, 0.000014, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1345.895629, 1575.408813, 10.418437, 0.000007, 0.000022, 89.999946, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1343.245605, 1575.408813, 10.418437, 0.000007, 0.000022, 89.999946, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1345.895629, 1572.516967, 10.418437, 0.000014, 0.000022, 89.999923, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1343.245605, 1572.516967, 10.418437, 0.000014, 0.000022, 89.999923, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1353.776123, 1575.408813, 10.418437, 0.000014, 0.000022, 89.999923, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1351.126098, 1575.408813, 10.418437, 0.000014, 0.000022, 89.999923, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1353.776123, 1572.516967, 10.418437, 0.000022, 0.000022, 89.999900, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1351.126098, 1572.516967, 10.418437, 0.000022, 0.000022, 89.999900, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1361.648193, 1575.408813, 10.418437, 0.000029, 0.000022, 89.999877, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1358.998168, 1575.408813, 10.418437, 0.000029, 0.000022, 89.999877, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1361.648193, 1572.516967, 10.418437, 0.000037, 0.000022, 89.999855, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    int_auction = CreateDynamicObject(2773, 1358.998168, 1572.516967, 10.418437, 0.000037, 0.000022, 89.999855, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", 0xFF296D98);
    
    // papan tulis
    int_auction = CreateDynamicObject(2790, 1335.549926, 1567.444702, 12.808433, 0.000000, 0.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 19787, "samplcdtvs1", "samplcdtv1screen", -16777216);
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", -16777216);
    int_auction_text[0] = CreateDynamicObject(19477, 1335.700000, 1567.444702, 12.808433, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction_text[0], 0, "A U C T I O N", 130, "Palatino Linotype", 90, 1, -1, -16777216, 1);

    int_auction = CreateDynamicObject(2790, 1335.549926, 1580.035034, 12.808433, 0.000000, 0.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 19787, "samplcdtvs1", "samplcdtv1screen", -16777216);
    SetDynamicObjectMaterial(int_auction, 1, 10101, "2notherbuildsfe", "ferry_build14", -16777216);
    int_auction_text[1] = CreateDynamicObject(19477, 1335.700000, 1580.035034, 12.808433, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction_text[1], 0, "A U C T I O N", 130, "Palatino Linotype", 90, 1, -1, -16777216, 1);

    int_auction = CreateDynamicObject(19937, 1335.339965, 1575.344482, 10.238434, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19937, 1335.516723, 1572.628906, 10.568431, 89.999992, 104.036239, -74.036216, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19939, 1335.929565, 1572.283569, 11.558430, 0.000003, 90.000022, 29.999986, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(19939, 1336.001464, 1571.759155, 11.298433, 89.999992, 284.036254, -74.036216, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(19939, 1335.516357, 1572.599365, 11.298433, 89.999992, 284.036254, -74.036216, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(19939, 1335.524902, 1574.889526, 11.318429, 0.000000, 90.000007, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(19939, 1335.524902, 1575.799682, 11.318429, 0.000000, 90.000007, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(19939, 1335.324829, 1574.409667, 11.048432, 89.999992, 270.000000, -89.999992, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(19939, 1335.324829, 1576.280029, 11.048432, 89.999992, 270.000000, -89.999992, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18980, 1340.918457, 1582.997680, 15.628436, 0.000000, 90.000015, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(18980, 1365.888427, 1582.997680, 15.628436, 0.000000, 90.000015, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(18980, 1340.918457, 1564.407226, 15.628436, 0.000000, 90.000015, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(18980, 1365.888427, 1564.407226, 15.628436, 0.000000, 90.000015, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(18980, 1367.088500, 1574.097167, 15.628434, 0.000000, 90.000015, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18762, 1365.200073, 1581.062500, 15.628434, 0.000000, 90.000015, 135.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18762, 1365.398315, 1566.264160, 15.628435, 0.000000, 90.000015, 45.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18762, 1335.848510, 1567.384399, 15.628435, 0.000000, 90.000015, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18762, 1335.848510, 1580.024780, 15.628432, 0.000000, 90.000015, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18762, 1333.858520, 1577.134643, 15.628432, 0.000000, 90.000015, 180.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18762, 1333.858520, 1570.374023, 15.628432, 0.000000, 90.000015, 180.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18980, 1331.908447, 1572.927734, 15.628437, 0.000000, 90.000007, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(8661, 1347.365356, 1573.593750, 16.058433, 0.000000, 180.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 16640, "a51", "pavegrey128", 0x00000000);
    int_auction = CreateDynamicObject(19477, 1335.590698, 1575.270141, 11.098438, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction, 0, "A U C T I O N", 130, "Palatino Linotype", 30, 1, 0xFF333333, 0x00000000, 1);
    int_auction = CreateDynamicObject(19477, 1335.590698, 1575.270141, 10.968437, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction, 0, "HOUSE", 130, "Palatino Linotype", 30, 0, 0xFF333333, 0x00000000, 1);
    int_auction = CreateDynamicObject(19477, 1335.590698, 1575.270141, 11.098438, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction, 0, "_____", 130, "Georgia", 30, 1, 0xFF333333, 0x00000000, 1);
    int_auction = CreateDynamicObject(19477, 1335.981323, 1572.325561, 11.098438, 0.000003, 0.000029, 29.999986, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction, 0, "A U C T I O N", 130, "Palatino Linotype", 30, 1, 0xFF333333, 0x00000000, 1);
    int_auction = CreateDynamicObject(19477, 1335.981323, 1572.325561, 10.968437, 0.000003, 0.000029, 29.999986, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction, 0, "HOUSE", 130, "Palatino Linotype", 30, 0, 0xFF333333, 0x00000000, 1);
    int_auction = CreateDynamicObject(19477, 1335.961059, 1572.328613, 11.088438, 0.000000, 0.000014, 30.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction, 0, "_____", 130, "Georgia", 30, 1, 0xFF333333, 0x00000000, 1);
    int_auction = CreateDynamicObject(19477, 1331.570068, 1573.850219, 12.858446, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction, 0, "A U C T I O N", 130, "Palatino Linotype", 90, 1, 0xFF333333, 0x00000000, 1);
    int_auction = CreateDynamicObject(19477, 1331.570068, 1573.850219, 12.468442, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction, 0, "HOUSE", 130, "Palatino Linotype", 80, 0, 0xFF333333, 0x00000000, 1);
    int_auction = CreateDynamicObject(19477, 1331.570068, 1573.850219, 12.818448, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction, 0, "________", 130, "Georgia", 90, 1, 0xFF333333, 0x00000000, 1);
    int_auction = CreateDynamicObject(19447, 1330.707031, 1570.519042, 14.468443, 0.000000, 0.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19447, 1330.707031, 1576.899047, 14.458434, 0.000000, 0.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19434, 1334.684692, 1572.305297, 13.838438, 0.000000, 90.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF555555);
    int_auction = CreateDynamicObject(19434, 1334.684692, 1575.805297, 13.838438, 0.000000, 90.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF555555);
    int_auction = CreateDynamicObject(19434, 1332.155029, 1571.385131, 13.838438, 0.000000, 90.000000, 180.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF555555);
    int_auction = CreateDynamicObject(19434, 1332.694580, 1574.455688, 13.838438, 0.000000, 90.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF555555);
    int_auction = CreateDynamicObject(19434, 1332.694580, 1577.925537, 13.838438, 0.000000, 90.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF555555);
    int_auction = CreateDynamicObject(19447, 1335.406738, 1573.619506, 15.518436, 0.000000, 0.000000, 180.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19373, 1333.713256, 1574.115478, 13.878437, 0.000007, 90.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0x00000000);
    int_auction = CreateDynamicObject(19447, 1333.467163, 1573.208251, 14.158441, 0.000000, -89.999984, -0.000029, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 19787, "samplcdtvs1", "samplcdtv1screen", 0x00000000);
    int_auction = CreateDynamicObject(19373, 1333.723266, 1577.594970, 13.878437, 0.000007, 90.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0x00000000);
    int_auction = CreateDynamicObject(19373, 1332.102539, 1572.585449, 13.858439, 0.000000, 89.999992, 179.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0x00000000);
    int_auction = CreateDynamicObject(19373, 1331.782592, 1574.125610, 13.828435, 0.000007, 90.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0x00000000);
    int_auction = CreateDynamicObject(19373, 1331.782592, 1577.616088, 13.828435, 0.000007, 90.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0x00000000);
    int_auction = CreateDynamicObject(18980, 1340.918457, 1582.557373, 15.408433, 0.000000, 90.000015, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18980, 1365.888427, 1582.557373, 15.408433, 0.000000, 90.000015, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18980, 1340.918457, 1564.966796, 15.408433, 0.000000, 90.000030, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(18980, 1365.888427, 1564.966796, 15.408433, 0.000000, 90.000030, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(11714, 1367.350219, 1573.915893, 11.038436, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 8501, "casroyale", "royaledoor01_128", 0x00000000);
    int_auction = CreateDynamicObject(11714, 1367.370727, 1575.393920, 11.038436, 0.000000, 0.000000, 45.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 8501, "casroyale", "royaledoor01_128", 0x00000000);
    int_auction = CreateDynamicObject(11714, 1367.350219, 1572.435058, 11.038436, 0.000000, 0.000000, -45.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 8501, "casroyale", "royaledoor01_128", 0x00000000);
    int_auction = CreateDynamicObject(1495, 1366.340454, 1574.640625, 9.778431, 0.000014, 0.000000, 89.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    SetDynamicObjectMaterial(int_auction, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(int_auction, 2, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(1495, 1366.340454, 1573.180664, 9.778431, 0.000014, 0.000000, 89.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    SetDynamicObjectMaterial(int_auction, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(int_auction, 2, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(1495, 1366.340454, 1571.710083, 9.778431, 0.000014, 0.000000, 89.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    SetDynamicObjectMaterial(int_auction, 1, 14581, "ab_mafiasuitea", "barbersmir1", 0x90FFFFFF);
    SetDynamicObjectMaterial(int_auction, 2, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1371.067749, 1576.630737, 10.682497, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1371.067749, 1571.231323, 10.682497, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1371.087768, 1574.002197, 12.692502, 90.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0x00000000);
    int_auction = CreateDynamicObject(18762, 1335.848510, 1573.794555, 15.628435, 0.000000, 90.000015, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D55);
    int_auction = CreateDynamicObject(2229, 1338.446411, 1579.651977, 9.822497, 0.000007, 90.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0x00000000);
    SetDynamicObjectMaterial(int_auction, 2, 19787, "samplcdtvs1", "samplcdtv1screen", 0x00000000);
    int_auction = CreateDynamicObject(2229, 1338.446411, 1579.651733, 10.452496, 0.000007, 270.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0x00000000);
    SetDynamicObjectMaterial(int_auction, 2, 19787, "samplcdtvs1", "samplcdtv1screen", 0x00000000);
    int_auction = CreateDynamicObject(2229, 1338.446411, 1574.001220, 9.822497, 0.000007, 90.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0x00000000);
    SetDynamicObjectMaterial(int_auction, 2, 19787, "samplcdtvs1", "samplcdtv1screen", 0x00000000);
    int_auction = CreateDynamicObject(2229, 1338.446411, 1574.000976, 10.452496, 0.000007, 270.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0x00000000);
    SetDynamicObjectMaterial(int_auction, 2, 19787, "samplcdtvs1", "samplcdtv1screen", 0x00000000);
    int_auction = CreateDynamicObject(2229, 1338.446411, 1567.861572, 9.822497, 0.000022, 90.000000, 89.999931, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0x00000000);
    SetDynamicObjectMaterial(int_auction, 2, 19787, "samplcdtvs1", "samplcdtv1screen", 0x00000000);
    int_auction = CreateDynamicObject(2229, 1338.446411, 1567.861328, 10.452496, 0.000022, 270.000000, 89.999931, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0x00000000);
    SetDynamicObjectMaterial(int_auction, 2, 19787, "samplcdtvs1", "samplcdtv1screen", 0x00000000);
    int_auction = CreateDynamicObject(19447, 1347.111938, 1568.204345, 15.048432, 0.000007, 90.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF555555);
    int_auction = CreateDynamicObject(19447, 1347.111938, 1571.694091, 15.048432, 0.000007, 90.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF555555);
    int_auction = CreateDynamicObject(19447, 1347.111938, 1576.114379, 15.048432, 0.000014, 90.000000, 89.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF555555);
    int_auction = CreateDynamicObject(19447, 1347.111938, 1579.604125, 15.048432, 0.000014, 90.000000, 89.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF555555);
    int_auction = CreateDynamicObject(19447, 1356.752441, 1568.204345, 15.048432, 0.000014, 90.000000, 89.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF555555);
    int_auction = CreateDynamicObject(19447, 1356.752441, 1571.694091, 15.048432, 0.000014, 90.000000, 89.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF555555);
    int_auction = CreateDynamicObject(19447, 1356.752441, 1576.114379, 15.048432, 0.000022, 90.000000, 89.999931, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF555555);
    int_auction = CreateDynamicObject(19447, 1356.752441, 1579.604125, 15.048432, 0.000022, 90.000000, 89.999931, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF555555);
    int_auction = CreateDynamicObject(19377, 1366.342651, 1568.483764, 15.048432, 0.000014, 90.000000, 89.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF555555);
    int_auction = CreateDynamicObject(19377, 1366.342651, 1578.983642, 15.048432, 0.000014, 90.000000, 89.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF555555);
    int_auction = CreateDynamicObject(19377, 1337.502685, 1568.483764, 15.048432, 0.000022, 90.000000, 89.999931, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF555555);
    int_auction = CreateDynamicObject(19377, 1337.502685, 1578.983642, 15.048432, 0.000022, 90.000000, 89.999931, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF555555);
    int_auction = CreateDynamicObject(18980, 1349.410644, 1573.878906, 15.542510, 0.000000, 90.000007, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(18980, 1349.200927, 1581.669433, 15.542510, 0.000000, 90.000007, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0x00000000);
    int_auction = CreateDynamicObject(18980, 1349.410644, 1565.928100, 15.542510, 0.000000, 90.000007, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(638, 1339.025634, 1576.863647, 10.368437, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    SetDynamicObjectMaterial(int_auction, 1, 801, "gta_proc_ferns", "veg_bushgrn", 0x00000000);
    int_auction = CreateDynamicObject(638, 1339.025634, 1570.862915, 10.368437, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    SetDynamicObjectMaterial(int_auction, 1, 801, "gta_proc_ferns", "veg_bushgrn", 0x00000000);
    int_auction = CreateDynamicObject(8674, 1353.495239, 1563.906860, 12.102499, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 14581, "ab_mafiasuitea", "barbersmir1", 0x90555555);
    int_auction = CreateDynamicObject(8674, 1353.495239, 1583.498168, 12.102499, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 14581, "ab_mafiasuitea", "barbersmir1", 0x90555555);
    int_auction = CreateDynamicObject(18766, 1351.266845, 1561.575683, 9.852499, 89.999992, 89.999992, -89.999992, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 4829, "airport_las", "Grass_128HV", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1351.347045, 1559.595458, 9.852499, 180.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 9514, "711_sfw", "shingles2", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1359.419433, 1558.845214, 9.852499, 180.000000, 0.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 9514, "711_sfw", "shingles2", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1345.936401, 1558.845214, 9.852499, 180.000000, 0.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 9514, "711_sfw", "shingles2", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1361.327026, 1559.595458, 9.852499, 180.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 9514, "711_sfw", "shingles2", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1361.256591, 1561.575683, 9.852499, 89.999992, 89.999992, -89.999992, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 4829, "airport_las", "Grass_128HV", 0x00000000);
    int_auction = CreateDynamicObject(2960, 1351.476318, 1564.093505, 10.743704, 89.999992, 240.324005, -60.324054, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(2960, 1351.476318, 1564.093505, 13.413719, 89.999992, 261.967285, -81.967323, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(2960, 1356.017333, 1564.093505, 13.413719, 89.999992, 261.967285, -81.967323, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(2960, 1358.345947, 1564.113159, 12.892509, 0.000000, 90.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(2960, 1349.014770, 1564.113159, 12.892510, 0.000000, 90.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(2960, 1351.476318, 1583.703857, 10.743704, 89.999992, 254.227890, -74.227928, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(2960, 1351.476318, 1583.703857, 13.413719, 89.999992, 265.963989, -85.964004, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(2960, 1356.017333, 1564.093505, 10.743704, 89.999992, 240.324005, -60.324054, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(2960, 1356.017333, 1583.703857, 13.413719, 89.999992, 265.963989, -85.964004, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(2960, 1358.345947, 1583.723510, 12.892509, 0.000007, 90.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(2960, 1349.014770, 1583.723510, 12.892510, 0.000007, 90.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(2960, 1356.017333, 1583.703857, 10.743704, 89.999992, 254.227890, -74.227928, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19434, 1361.061157, 1564.407470, 13.402503, 0.000012, 0.000004, 89.999946, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19482, 1361.230590, 1564.297363, 13.652507, 0.000027, 0.000004, 89.999900, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0xFF296D98);
    int_auction = CreateDynamicObject(19482, 1361.230590, 1564.297363, 10.952510, 0.000027, 0.000004, 89.999900, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0xFF296D98);
    int_auction = CreateDynamicObject(19434, 1346.349731, 1564.407470, 13.402503, 0.000019, 0.000004, 89.999923, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19482, 1346.429809, 1583.126464, 13.652507, 0.000043, 0.000004, 89.999855, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0x00000000);
    int_auction = CreateDynamicObject(19482, 1346.429809, 1583.126464, 10.952510, 0.000043, 0.000004, 89.999855, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0x00000000);
    int_auction = CreateDynamicObject(19434, 1361.061157, 1564.407470, 9.942496, 0.000027, 0.000004, 89.999900, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19482, 1346.429809, 1564.297363, 13.652507, 0.000035, 0.000004, 89.999877, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0xFF296D98);
    int_auction = CreateDynamicObject(19482, 1346.429809, 1564.297363, 10.952510, 0.000035, 0.000004, 89.999877, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0xFF296D98);
    int_auction = CreateDynamicObject(19434, 1346.349731, 1564.407470, 9.942496, 0.000035, 0.000004, 89.999877, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19482, 1361.191284, 1583.126464, 13.652507, 0.000049, 0.000004, 89.999832, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0xFF296D98);
    int_auction = CreateDynamicObject(19482, 1361.191284, 1583.126464, 10.952510, 0.000049, 0.000004, 89.999832, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0xFF296D98);
    int_auction = CreateDynamicObject(19447, 1331.485473, 1573.777832, 9.798428, 180.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19434, 1346.501342, 1582.996826, 13.402503, 0.000019, 0.000004, -90.000045, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19482, 1367.301025, 1579.748291, 11.152506, 0.000049, -0.000001, 179.999786, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0xFF296D98);
    int_auction = CreateDynamicObject(19482, 1367.301025, 1579.748291, 13.852504, 0.000049, -0.000001, 179.999786, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0xFF296D98);
    int_auction = CreateDynamicObject(19434, 1361.212768, 1582.996826, 13.402503, 0.000027, 0.000004, -90.000068, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19482, 1367.301025, 1567.867187, 11.152506, 0.000049, -0.000001, 179.999786, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0xFF296D98);
    int_auction = CreateDynamicObject(19482, 1367.301025, 1567.867187, 13.852504, 0.000049, -0.000001, 179.999786, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10932, "station_sfse", "neon", 0xFF296D98);
    int_auction = CreateDynamicObject(19434, 1346.501342, 1582.996826, 9.942496, 0.000035, 0.000004, -90.000091, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19434, 1361.212768, 1582.996826, 9.942496, 0.000043, 0.000004, -90.000114, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19447, 1333.617431, 1570.309082, 7.928445, 90.000000, 0.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19447, 1330.117553, 1570.489257, 7.928445, 90.000000, 0.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(19447, 1333.617431, 1577.061035, 7.928445, 89.999992, 179.999984, -90.000007, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19447, 1330.117553, 1576.890869, 7.928445, 89.999992, 179.999984, -90.000007, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 6284, "bev_law2", "sjmlawarwall3", 0xFF3C4D63);
    int_auction = CreateDynamicObject(2310, 1344.293579, 1565.963623, 10.312500, 0.000000, 0.000014, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1344.293579, 1567.064697, 10.312500, 0.000000, 0.000014, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1344.293579, 1568.124267, 10.312500, 0.000000, 0.000022, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1344.293579, 1569.225341, 10.312500, 0.000000, 0.000022, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1344.293579, 1570.355468, 10.312500, 0.000000, 0.000022, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1344.293579, 1577.265014, 10.312500, 0.000000, 0.000022, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1344.293579, 1578.366088, 10.312500, 0.000000, 0.000022, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1344.293579, 1579.425659, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1344.293579, 1580.526733, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1344.293579, 1581.656860, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1346.653808, 1565.963623, 10.312500, 0.000000, 0.000022, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1346.653808, 1567.064697, 10.312500, 0.000000, 0.000022, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1346.653808, 1568.124267, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1346.653808, 1569.225341, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1346.653808, 1570.355468, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1346.653808, 1577.265014, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1346.653808, 1578.366088, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1346.653808, 1579.425659, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1346.653808, 1580.526733, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1346.653808, 1581.656860, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1348.884887, 1565.963623, 10.312500, 0.000000, 0.000022, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1348.884887, 1567.064697, 10.312500, 0.000000, 0.000022, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1348.884887, 1568.124267, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1348.884887, 1569.225341, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1348.884887, 1570.355468, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1348.884887, 1577.265014, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1348.884887, 1578.366088, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1348.884887, 1579.425659, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1348.884887, 1580.526733, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1348.884887, 1581.656860, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1351.245117, 1565.963623, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1351.245117, 1567.064697, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1351.245117, 1568.124267, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1351.245117, 1569.225341, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1351.245117, 1570.355468, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1351.245117, 1577.265014, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1351.245117, 1578.366088, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1351.245117, 1579.425659, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1351.245117, 1580.526733, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1351.245117, 1581.656860, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1353.354492, 1565.963623, 10.312500, 0.000000, 0.000022, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1353.354492, 1567.064697, 10.312500, 0.000000, 0.000022, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1353.354492, 1568.124267, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1353.354492, 1569.225341, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1353.354492, 1570.355468, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1353.354492, 1577.265014, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1353.354492, 1578.366088, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1353.354492, 1579.425659, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1353.354492, 1580.526733, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1353.354492, 1581.656860, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1355.714721, 1565.963623, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1355.714721, 1567.064697, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1355.714721, 1568.124267, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1355.714721, 1569.225341, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1355.714721, 1570.355468, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1355.714721, 1577.265014, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1355.714721, 1578.366088, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1355.714721, 1579.425659, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1355.714721, 1580.526733, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1355.714721, 1581.656860, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1357.945800, 1565.963623, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1357.945800, 1567.064697, 10.312500, 0.000000, 0.000029, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1357.945800, 1568.124267, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1357.945800, 1569.225341, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1357.945800, 1570.355468, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1357.945800, 1577.265014, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1357.945800, 1578.366088, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1357.945800, 1579.425659, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1357.945800, 1580.526733, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1357.945800, 1581.656860, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1360.306030, 1565.963623, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1360.306030, 1567.064697, 10.312500, 0.000000, 0.000037, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1360.306030, 1568.124267, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1360.306030, 1569.225341, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1360.306030, 1570.355468, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1360.306030, 1577.265014, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1360.306030, 1578.366088, 10.312500, 0.000000, 0.000045, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1360.306030, 1579.425659, 10.312500, 0.000000, 0.000052, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1360.306030, 1580.526733, 10.312500, 0.000000, 0.000052, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(2310, 1360.306030, 1581.656860, 10.312500, 0.000000, 0.000052, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    int_auction = CreateDynamicObject(1297, 1365.650146, 1577.576538, 11.788204, 0.000000, -8.000007, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 19480, "signsurf", "sign", 0x00000000);
    int_auction = CreateDynamicObject(1297, 1365.650146, 1570.385620, 11.788204, 0.000000, -8.000007, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 19480, "signsurf", "sign", 0x00000000);
    int_auction = CreateDynamicObject(18980, 1370.658935, 1571.127319, 10.288434, 0.000000, 90.000015, 45.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 3979, "civic01_lan", "crazy paving", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(18762, 1367.361694, 1568.359130, 10.292508, 0.000000, 90.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 3979, "civic01_lan", "crazy paving", 0xFFFFFFFF);
    int_auction = CreateDynamicObject(19477, 1366.050292, 1573.850219, 12.858446, 0.000000, 0.000037, 179.999893, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction, 0, "A U C T I O N", 130, "Palatino Linotype", 90, 1, 0xFF333333, 0x00000000, 1);
    int_auction = CreateDynamicObject(19477, 1366.050292, 1573.850219, 12.468442, 0.000000, 0.000037, 179.999893, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction, 0, "HOUSE", 130, "Palatino Linotype", 80, 0, 0xFF333333, 0x00000000, 1);
    int_auction = CreateDynamicObject(19477, 1366.050292, 1573.850219, 12.818448, 0.000000, 0.000037, 179.999893, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterialText(int_auction, 0, "________", 130, "Georgia", 90, 1, 0xFF333333, 0x00000000, 1);
    int_auction = CreateDynamicObject(19434, 1366.653198, 1576.794433, 11.238432, 0.000007, 0.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 19787, "samplcdtvs1", "samplcdtv1screen", 0x00000000);
    int_auction = CreateDynamicObject(19434, 1366.653198, 1576.514160, 11.238432, 0.000007, 0.000000, 89.999977, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 19787, "samplcdtvs1", "samplcdtv1screen", 0x00000000);
    int_auction = CreateDynamicObject(19434, 1366.653198, 1571.373291, 11.238432, 0.000014, 0.000000, 89.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 19787, "samplcdtvs1", "samplcdtv1screen", 0x00000000);
    int_auction = CreateDynamicObject(19434, 1366.653198, 1571.093017, 11.238432, 0.000014, 0.000000, 89.999954, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 19787, "samplcdtvs1", "samplcdtv1screen", 0x00000000);
    int_auction = CreateDynamicObject(640, 1353.606933, 1560.875732, 10.632499, 0.000000, 0.000000, 90.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 4830, "airport2", "bevflower2", 0x00000000);
    SetDynamicObjectMaterial(int_auction, 1, 4992, "airportdetail", "bevflower1", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1355.696533, 1585.957031, 9.852499, 89.999992, 179.934051, 0.065913, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 4829, "airport_las", "Grass_128HV", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1355.616333, 1587.937255, 9.852499, 0.000000, 179.999984, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 9514, "711_sfw", "shingles2", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1347.543945, 1588.687500, 9.852499, 0.000000, 179.999984, 89.999931, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 9514, "711_sfw", "shingles2", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1361.026977, 1588.687500, 9.852499, 0.000000, 179.999984, 89.999931, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 9514, "711_sfw", "shingles2", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1345.636352, 1587.937255, 9.852499, 0.000000, 179.999984, 0.000000, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 9514, "711_sfw", "shingles2", 0x00000000);
    int_auction = CreateDynamicObject(18766, 1345.706787, 1585.957031, 9.852499, 89.999992, 179.934051, 0.065913, 10, 100, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(int_auction, 0, 4829, "airport_las", "Grass_128HV", 0x00000000);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int_auction = CreateDynamicObject(19611, 1335.833251, 1572.167968, 10.228434, 0.000003, 0.000014, 29.999986, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(19610, 1335.856445, 1572.168701, 11.856382, 30.000009, -0.000003, 119.999954, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(8874, 1339.390014, 1569.890258, 12.211087, 0.000000, -16.700002, 180.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(8874, 1339.526855, 1577.141845, 11.632694, 0.000000, -16.700002, -89.199981, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(820, 1359.142944, 1560.688842, 8.502493, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(820, 1348.552368, 1560.688842, 8.592494, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(717, 1358.886108, 1553.227783, 7.842496, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(717, 1345.636352, 1553.227783, 7.842496, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1338.475097, 1566.928466, 9.948434, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1338.475097, 1572.379394, 9.948434, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1338.475097, 1575.680053, 9.948434, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1338.475097, 1580.990112, 9.948434, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1362.765136, 1571.888916, 9.448431, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1362.765136, 1575.899169, 9.448431, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1357.564575, 1571.888916, 9.448431, 0.000000, 0.000007, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1357.564575, 1575.899169, 9.448431, 0.000000, 0.000007, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1354.763916, 1571.888916, 9.448431, 0.000000, 0.000014, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1354.763916, 1575.899169, 9.448431, 0.000000, 0.000014, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1349.723754, 1571.888916, 9.448431, 0.000000, 0.000014, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1349.723754, 1575.899169, 9.448431, 0.000000, 0.000014, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1346.923095, 1571.888916, 9.448431, 0.000000, 0.000022, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(1215, 1346.923095, 1575.899169, 9.448431, 0.000000, 0.000022, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(2614, 1366.815307, 1573.885864, 14.160294, 24.300003, 0.000000, 270.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(715, 1351.124023, 1550.293579, 15.812498, 0.000000, 0.000000, 0.000000, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(820, 1347.820434, 1586.843872, 8.502493, 0.000000, 0.000007, 179.999893, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(820, 1358.411010, 1586.843872, 8.592494, 0.000000, 0.000007, 179.999893, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(717, 1348.077270, 1594.304931, 7.842496, 0.000000, 0.000007, 179.999893, 10, 100, -1, 300.00, 300.00); 
    int_auction = CreateDynamicObject(717, 1361.327026, 1594.304931, 7.842496, 0.000000, 0.000007, 179.999893, 10, 100, -1, 300.00, 300.00); 
    return 1;
}

hook OnGameModeInit() 
{
    Auction_CreateMap();
}

IsPlayerInAuction(playerid)
{
    static 
        Float:x1, 
        Float:y1, 
        Float:z1, 
        Float:x2, 
        Float:y2, 
        Float:z2;

    GetDynamicObjectPos(int_auction_text[0], x1, y1, z1);
    GetDynamicObjectPos(int_auction_text[1], x2, y2, z2);

    if (IsPlayerInRangeOfPoint(playerid, 100.0, x1, y1, z1) || IsPlayerInRangeOfPoint(playerid, 100.0, x2, y2, z2) && GetPlayerVirtualWorld(playerid) == 10 && GetPlayerInterior(playerid) == 100)
        return 1;

    return 0;
}

Auction_Reset()
{
    foreach(new id : Player) if(FollowAuction[id] == 1)
    {
        FollowAuction[id] = 0;
    }


    AuctionType = 0;
    AuctionCount = 0;
    AuctionStart = 0;
    AuctionBid = 0;
    format(AuctionLelang, sizeof(AuctionLelang), "none");
    format(AuctionHighest, sizeof(AuctionHighest), "none");
    KillTimer(Auction);
    return 1;
}

function AuctionTimer()
{
    new text[255];

    switch(AuctionType)
    {
        case 1:
        {
            AuctionTime = AuctionTime-1;
            format(text,sizeof(text),"{00FFFF}%s\n"GREEN"Start: "WHITE"$%s\n"GREEN"Bid: "WHITE"$%s\n"GREEN"Participants: "WHITE"%d\nStart in: %d", AuctionLelang, FormatNumber(AuctionStart), FormatNumber(AuctionBid), AuctionCount, AuctionTime);

            if(AuctionTime == 0)
            {
                if(!AuctionCount)
                {
                    SetDynamicObjectMaterialText(int_auction_text[0], 0, "No one join this auction.", 130, "Ariel", 40, 1, -1, -16777216, 1);
                    SetDynamicObjectMaterialText(int_auction_text[1], 0, "No one join this auction.", 130, "Ariel", 40, 1, -1, -16777216, 1);
                    Auction_Reset();
                }
                else
                {
                    AuctionType = 2;
                    AuctionTime = 10;
                }
            }
        }
        case 2:
        {
            AuctionTime  = AuctionTime-1;
            format(text,sizeof(text),"{00FFFF}%s\n"GREEN"Highest bidder: "WHITE"%s\n"GREEN"Offer: "WHITE"$%s\nCountdown: %d", AuctionLelang, AuctionHighest, FormatNumber(AuctionStart), AuctionTime);

            if(AuctionTime == 0)
            {
                format(text,sizeof(text),"{00FFFF}%s\n"WHITE"%s - "GREEN"$%s", AuctionLelang, AuctionHighest, FormatNumber(AuctionStart));

                foreach(new id : Player) if(IsPlayerInAuction(id))
                {
                    FollowAuction[id] = 0;
                    SendClientMessageEx(id, X11_TURQUOISE_1, "AUCTION: "WHITE"%s: %s - "GREEN"$%s.", AuctionLelang, AuctionHighest, FormatNumber(AuctionStart));

                    if(!strcmp(AuctionHighest, GetName(id), true))
                    {
                        SendClientMessageEx(id, X11_TURQUOISE_1, "AUCTION: "WHITE"Anda telah memenangkan %s - "GREEN"$%s", AuctionLelang, FormatNumber(AuctionStart));
                        GiveMoney(id, -AuctionStart);
                    }
                }
                Auction_Reset();
            }
        }
    }
    SetDynamicObjectMaterialText(int_auction_text[0], 0, text, 130, "Ariel", 40, 1, -1, -16777216, 1);
    SetDynamicObjectMaterialText(int_auction_text[1], 0, text, 130, "Ariel", 40, 1, -1, -16777216, 1);
    return 1;
}

CMD:auction(playerid, params[])
{
    new 
        option[32], 
        string[128];

    if(!IsPlayerInAuction(playerid))
        return SendErrorMessage(playerid, "You're not in auction house.");

    if(sscanf(params, "s[32]S()[128]", option, string))
        return SendSyntaxMessage(playerid, "/auction [create/join/bid/cancel]");

    if(!strcmp(option,"create", true))
    {
        new 
            lelang[128], 
            start[32], 
            bid[32], 
            dollarstart, 
            centstart, 
            dollarbid, 
            centbid, 
            totalstart[32], 
            totalbid[32];

        if(AuctionType != 0)
            return SendErrorMessage(playerid, "Auction sedang berjalan, /auction cancel tuntuk menunda.");

        if(sscanf(string, "s[32]s[32]s[128]", start, bid, lelang))
            return SendSyntaxMessage(playerid, "/auction create [start money] [bid] [property name]");

        if (strfind(start, ".", true) != -1)
        {
            sscanf(start, "p<.>dd", dollarstart, centstart);
            format(totalstart, sizeof(totalstart), "%d%02d", dollarstart, centstart);
        }
        else
        {
            sscanf(start, "d", dollarstart);
            format(totalstart, sizeof(totalstart), "%d00", dollarstart);
        }
        if (strfind(bid, ".", true) != -1)
        {
            sscanf(bid, "p<.>dd", dollarbid, centbid);
            format(totalbid, sizeof(totalbid), "%d%02d", dollarbid, centbid);
        }
        else
        {
            sscanf(bid, "d", dollarbid);
            format(totalbid, sizeof(totalbid), "%d00", dollarbid);
        }

        if(strval(totalstart) < 0)
            return SendErrorMessage(playerid, "Jangan memasukkan uang awal di bawah $0.00.");

        if (strval(totalbid) < 0)
            return SendErrorMessage(playerid, "Jangan memasukkan jumlah bid di bawah $0.00.");

        AuctionType = 1;
        AuctionTime = 15;
        AuctionCount = 0;
        AuctionStart = strval(totalstart);
        AuctionBid = strval(totalbid);
        format(AuctionLelang, sizeof(AuctionLelang), lelang);
        format(AuctionHighest, sizeof(AuctionHighest), "none");

        foreach(new id : Player) if(IsPlayerInAuction(id))
        {
            SendClientMessageEx(id, X11_TURQUOISE_1, "AUCTION: "YELLOW"Item: "WHITE"%s | "YELLOW"Start price: "GREEN"%s | "YELLOW"Bid: "GREEN"%s", lelang, FormatNumber(strval(totalstart)), FormatNumber(strval(totalbid)));
            SendClientMessageEx(id, X11_TURQUOISE_1, "AUCTION: "WHITE"Use command "YELLOW"'/auction join' "WHITE"to join auction.");
        }
        Auction = SetTimer("AuctionTimer", 1000, true);
        new text[255];
        format(text,sizeof(text),"{00FFFF}%s\n"GREEN"Start: "WHITE"$%s\n"GREEN"Bid: "WHITE"$%s\n"GREEN"Participants: "WHITE"%d\nSeart in: %d", lelang, FormatNumber(strval(totalstart)), FormatNumber(strval(totalbid)), AuctionCount, AuctionTime);
        SetDynamicObjectMaterialText(int_auction_text[0], 0, text, 130, "Ariel", 40, 1, -1, -16777216, 1);
        SetDynamicObjectMaterialText(int_auction_text[1], 0, text, 130, "Ariel", 40, 1, -1, -16777216, 1);
    }
    else if(!strcmp(option, "join", true))
    {
        if(AuctionType != 1)    
            return SendErrorMessage(playerid, "Auction belum di mulai.");

        if(FollowAuction[playerid]) 
            return SendErrorMessage(playerid, "Anda sedang mengikuti auction ini.!");

        if(GetMoney(playerid) < 100) 
            return SendErrorMessage(playerid, "Anda tidak memiliki modal uang $1.00 untuk mengikuti auction ini.");

        GiveMoney(playerid, -100);
        SendClientMessageEx(playerid, X11_TURQUOISE_1, "AUCTION: "WHITE"Gunakan perintah "YELLOW"'/auction bid' "WHITE"untuk memenangkan auction.");

        FollowAuction[playerid] = 1;
        AuctionCount = AuctionCount+1;

    }
    else if(!strcmp(option, "bid", true))
    {
        new 
            money = AuctionStart+AuctionBid;

        if(AuctionType == 1)
            return SendErrorMessage(playerid, "Auction belum di mulai.");

        if(!strcmp(AuctionHighest, GetName(playerid), true))
            return SendErrorMessage(playerid, "Anda masih berada di peringkat teratas auction ini!.");

        if(!FollowAuction[playerid])
            return SendErrorMessage(playerid, "Anda tidak mengikuti auction ini.");

        if(GetMoney(playerid) < money)
            return SendErrorMessage(playerid, "Anda tidak memiliki uang sebesar %s untuk mengikuti auction ini.", FormatNumber(money));

        AuctionStart = money;
        format(AuctionHighest, sizeof(AuctionHighest), GetName(playerid));
        AuctionTime = 10;
    }
    else if(!strcmp(option, "cancel", true))
    {
        if (PlayerData[playerid][pAdmin] < 5)
    	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

        if(AuctionType == 0)
            return SendErrorMessage(playerid, "Auction sedang tidak berlangsung!.");

        foreach(new id : Player) if(IsPlayerInAuction(id))
        {
            SendClientMessageEx(id, X11_TURQUOISE_1, "AUCTION: "YELLOW"%s "WHITE"menunda auction.", ReturnName(playerid));
        }
        Auction_Reset();
        SetDynamicObjectMaterialText(int_auction_text[0], 0, "Auction di tunda.", 130, "Ariel", 40, 1, -1, -16777216, 1);
        SetDynamicObjectMaterialText(int_auction_text[1], 0, "Auction di tunda.", 130, "Ariel", 40, 1, -1, -16777216, 1);
    }
    else
        SendSyntaxMessage(playerid, "/auction [create/join/bid/cancel]");

    return 1;
}

CMD:changeauctionboard(playerid, params[])
{
    new 
        text[128],
        string[128];

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

    if(!IsPlayerInAuction(playerid))
        return SendErrorMessage(playerid, "You're not in auction house.");

    if(AuctionType != 0)
        return SendErrorMessage(playerid, "Auction telah berlangsung, jangan di ubah dahulu sebelum selesai.");

    if(sscanf(params, "s[128]", text))
        return SendSyntaxMessage(playerid, "/changeboard [text]");

    if(strlen(text) > 128)
        return SendErrorMessage(playerid, "Text terlalu panjang.");

    FixText(text);
    format(string,sizeof(string), "%s", ColouredText(text));
    
    SetDynamicObjectMaterialText(int_auction_text[0], 0, string, 130, "Ariel", 40, 1, -1, -16777216, 1);
    SetDynamicObjectMaterialText(int_auction_text[1], 0, string, 130, "Ariel", 40, 1, -1, -16777216, 1);
    return 1;
}

CMD:gotoauction(playerid, params[]) 
{
    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

    SetPlayerPositionEx(playerid, 1364.5563, 1573.7416, 10.8784);
    SetPlayerFacingAngle(playerid, 86.8568);
    
    SetPlayerVirtualWorld(playerid, 10);
    SetPlayerInterior(playerid, 100);
    
    SendClientMessage(playerid, COLOR_SERVER, "TELEPORT: "WHITE"You have been teleported to "CYAN1"Auction Place");
    return 1;
}