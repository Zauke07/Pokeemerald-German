AbandonedShip_Corridors_1F_MapScripts::
	.byte 0

AbandonedShip_Corridors_1F_EventScript_Youngster::
	msgbox AbandonedShip_Corridors_1F_Text_IsntItFunHere, MSGBOX_NPC
	end

AbandonedShip_Corridors_1F_EventScript_Charlie::
	trainerbattle_single TRAINER_CHARLIE, AbandonedShip_Corridors_1F_Text_CharlieIntro, AbandonedShip_Corridors_1F_Text_CharlieDefeat
	msgbox AbandonedShip_Corridors_1F_Text_CharliePostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Corridors_1F_Text_CharlieIntro:
	.string "Was ist so lustig daran, dass ich meinen\n"
	.string "Schwimmreifen mit an Bord habe?$"

AbandonedShip_Corridors_1F_Text_CharlieDefeat:
	.string "Hui, du hast mir die Luft rausgelassen!$"

AbandonedShip_Corridors_1F_Text_CharliePostBattle:
	.string "Es ist gar nicht so einfach, POKéBÄLLe\n"
	.string "zu werfen, wenn man einen Schwimmreifen\l"
	.string "trägt!$"

AbandonedShip_Corridors_1F_Text_IsntItFunHere:
	.string "Hier ist es doch wirklich lustig, nicht\n"
	.string "wahr? Ich bin total aufgeregt.$"
