.set LOCALID_BRINEY, 11
.set LOCALID_WANDAS_BF_OUTSIDE, 21

Route116_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route116_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route116_OnFrame
	.byte 0

Route116_OnTransition:
	call_if_set FLAG_RECOVERED_DEVON_GOODS, Route116_EventScript_SetWandasBoyfriendPos
	call_if_eq VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_HideMapNamePopup
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_NORTH, AbnormalWeather_StartGroudonWeather
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_SOUTH, AbnormalWeather_StartGroudonWeather
	end

Route116_EventScript_SetWandasBoyfriendPos::
	setobjectxyperm LOCALID_WANDAS_BF_OUTSIDE, 38, 10
	return

Route116_OnLoad:
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_NORTH, AbnormalWeather_EventScript_PlaceTilesRoute116North
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_SOUTH, AbnormalWeather_EventScript_PlaceTilesRoute116South
	end

Route116_OnFrame:
	map_script_2 VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_EndEventAndCleanup_1
	.2byte 0

Route116_EventScript_WandasBoyfriend::
	lock
	faceplayer
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, Route116_EventScript_BoyfriendGruntLeftTunnel
	goto_if_set FLAG_DEVON_GOODS_STOLEN, Route116_EventScript_BoyfriendGruntInTunnel
	msgbox Route116_Text_WantToDigTunnel, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_BoyfriendGruntLeftTunnel::
	msgbox Route116_Text_GoonHightailedItOutOfTunnel, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_BoyfriendGruntInTunnel::
	msgbox Route116_Text_DiggingTunnelWhenGoonOrderedMeOut, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_DevonEmployee::
	lock
	faceplayer
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, Route116_EventScript_TryGiveRepeatBallAgain
	msgbox Route116_Text_ThankYouTokenOfAppreciation, MSGBOX_DEFAULT
	goto Route116_EventScript_GiveRepeatBall
	end

Route116_EventScript_GiveRepeatBall::
	setflag FLAG_MET_DEVON_EMPLOYEE
	giveitem ITEM_REPEAT_BALL
	goto_if_eq VAR_RESULT, FALSE, Route116_EventScript_NoRoomForRepeatBall
	msgbox Route116_Text_NewBallAvailableAtMart, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, Route116_EventScript_DevonEmployeeExit
	call_if_eq VAR_FACING, DIR_SOUTH, Route116_EventScript_DevonEmployeeExit
	call_if_eq VAR_FACING, DIR_WEST, Route116_EventScript_DevonEmployeeExit
	call_if_eq VAR_FACING, DIR_EAST, Route116_EventScript_DevonEmployeeExitEast
	removeobject VAR_LAST_TALKED
	clearflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setflag FLAG_RECEIVED_REPEAT_BALL
	release
	end

Route116_EventScript_DevonEmployeeExit::
	applymovement VAR_LAST_TALKED, Route116_Movement_DevonEmployeeExit
	waitmovement 0
	return

Route116_EventScript_DevonEmployeeExitEast::
	applymovement VAR_LAST_TALKED, Route116_Movement_DevonEmployeeExitEast
	waitmovement 0
	return

Route116_EventScript_TryGiveRepeatBallAgain::
	msgbox Route116_Text_TokenOfAppreciation, MSGBOX_DEFAULT
	goto Route116_EventScript_GiveRepeatBall
	end

Route116_EventScript_NoRoomForRepeatBall::
	msgbox Route116_Text_BagIsJamPacked, MSGBOX_DEFAULT
	release
	end

Route116_Movement_DevonEmployeeExit:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route116_Movement_DevonEmployeeExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route116_EventScript_RouteSignRustboro::
	msgbox Route116_Text_RouteSignRustboro, MSGBOX_SIGN
	end

Route116_EventScript_RusturfTunnelSign::
	msgbox Route116_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

Route116_EventScript_TunnelersRestHouseSign::
	msgbox Route116_Text_TunnelersRestHouse, MSGBOX_SIGN
	end

Route116_EventScript_TrainerTipsBToStopEvolution::
	msgbox Route116_Text_TrainerTipsBToStopEvolution, MSGBOX_SIGN
	end

Route116_EventScript_TrainerTipsBagHasPockets::
	msgbox Route116_Text_TrainerTipsBagHasPockets, MSGBOX_SIGN
	end

Route116_EventScript_Briney::
	lock
	faceplayer
	msgbox Route116_Text_ScoundrelMadeOffWithPeeko, MSGBOX_DEFAULT
	setvar VAR_ROUTE116_STATE, 2
	release
	end

Route116_EventScript_BrineyTrigger::
	lockall
	applymovement LOCALID_BRINEY, Common_Movement_WalkInPlaceFasterRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox Route116_Text_ScoundrelMadeOffWithPeeko, MSGBOX_DEFAULT
	setvar VAR_ROUTE116_STATE, 2
	releaseall
	end

Route116_EventScript_GlassesMan::
	lock
	faceplayer
	checkitem ITEM_BLACK_GLASSES
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_PlayerHasGlasses
	specialvar VAR_RESULT, FoundBlackGlasses
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_FoundGlassesNotOnPlayer
	msgbox Route116_Text_CanYouHelpMeFindGlasses, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_FoundGlassesNotOnPlayer::
	msgbox Route116_Text_CantFindGlassesNotHere, MSGBOX_DEFAULT
	closemessage
	goto Route116_EventScript_GlassesManExit
	end

Route116_EventScript_PlayerHasGlasses::
	msgbox Route116_Text_CanYouHelpMeFindGlasses, MSGBOX_DEFAULT
	msgbox Route116_Text_MayISeeThoseGlasses, MSGBOX_DEFAULT
	specialvar VAR_RESULT, FoundBlackGlasses
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_FoundGlassesOnPlayer
	msgbox Route116_Text_NotWhatImLookingFor, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_FoundGlassesOnPlayer::
	msgbox Route116_Text_NotWhatImLookingForMaybeTheyArentHere, MSGBOX_DEFAULT
	closemessage
	goto Route116_EventScript_GlassesManExit
	end

Route116_EventScript_GlassesManExit::
	delay 20
	call_if_eq VAR_FACING, DIR_NORTH, Route116_EventScript_GlassesManExitNormal
	call_if_eq VAR_FACING, DIR_SOUTH, Route116_EventScript_GlassesManExitNormal
	call_if_eq VAR_FACING, DIR_WEST, Route116_EventScript_GlassesManExitNormal
	call_if_eq VAR_FACING, DIR_EAST, Route116_EventScript_GlassesManExitEast
	removeobject VAR_LAST_TALKED
	release
	end

Route116_EventScript_GlassesManExitNormal::
	applymovement VAR_LAST_TALKED, Route116_Movement_GlassesManExit
	waitmovement 0
	return

Route116_EventScript_GlassesManExitEast::
	applymovement VAR_LAST_TALKED, Route116_Movement_GlassesManExitEast
	waitmovement 0
	return

Route116_Movement_GlassesManExit:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route116_Movement_GlassesManExitEast:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route116_EventScript_Joey::
	trainerbattle_single TRAINER_JOEY, Route116_Text_JoeyIntro, Route116_Text_JoeyDefeat
	msgbox Route116_Text_JoeyPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Jose::
	trainerbattle_single TRAINER_JOSE, Route116_Text_JoseIntro, Route116_Text_JoseDefeat
	msgbox Route116_Text_JosePostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Jerry::
	trainerbattle_single TRAINER_JERRY_1, Route116_Text_JerryIntro, Route116_Text_JerryDefeat, Route116_EventScript_TryRegisterJerryAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_RematchJerry
	setvar VAR_0x8004, TRAINER_JERRY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route116_EventScript_TryRegisterJerry
	msgbox Route116_Text_JerryPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_TryRegisterJerryAfterBattle::
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterJerryAfterBattle
	release
	end

Route116_EventScript_RegisterJerryAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route116_Text_JerryRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_JERRY_1
	release
	end

Route116_EventScript_TryRegisterJerry::
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterJerry
	msgbox Route116_Text_JerryPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_RegisterJerry::
	msgbox Route116_Text_JerryRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_JERRY_1
	release
	end

Route116_EventScript_RematchJerry::
	trainerbattle_rematch TRAINER_JERRY_1, Route116_Text_JerryRematchIntro, Route116_Text_JerryRematchDefeat
	msgbox Route116_Text_JerryPostRematch, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Clark::
	trainerbattle_single TRAINER_CLARK, Route116_Text_ClarkIntro, Route116_Text_ClarkDefeat
	msgbox Route116_Text_ClarkPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Janice::
	trainerbattle_single TRAINER_JANICE, Route116_Text_JaniceIntro, Route116_Text_JaniceDefeat
	msgbox Route116_Text_JanicePostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Karen::
	trainerbattle_single TRAINER_KAREN_1, Route116_Text_KarenIntro, Route116_Text_KarenDefeat, Route116_EventScript_TryRegisterKarenAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_RematchKaren
	setvar VAR_0x8004, TRAINER_KAREN_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route116_EventScript_TryRegisterKaren
	msgbox Route116_Text_KarenPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_TryRegisterKarenAfterBattle::
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterKarenAfterBattle
	release
	end

Route116_EventScript_RegisterKarenAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route116_Text_KarenRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_KAREN_1
	release
	end

Route116_EventScript_TryRegisterKaren::
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterKaren
	msgbox Route116_Text_KarenPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_RegisterKaren::
	msgbox Route116_Text_KarenRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_KAREN_1
	release
	end

Route116_EventScript_RematchKaren::
	trainerbattle_rematch TRAINER_KAREN_1, Route116_Text_KarenRematchIntro, Route116_Text_KarenRematchDefeat
	msgbox Route116_Text_KarenPostRematch, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Sarah::
	trainerbattle_single TRAINER_SARAH, Route116_Text_SarahIntro, Route116_Text_SarahDefeat
	msgbox Route116_Text_SarahPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Dawson::
	trainerbattle_single TRAINER_DAWSON, Route116_Text_DawsonIntro, Route116_Text_DawsonDefeat
	msgbox Route116_Text_DawsonPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Devan::
	trainerbattle_single TRAINER_DEVAN, Route116_Text_DevanIntro, Route116_Text_DevanDefeat
	msgbox Route116_Text_DevanPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Johnson::
	trainerbattle_single TRAINER_JOHNSON, Route116_Text_JohnsonIntro, Route116_Text_JohnsonDefeat
	msgbox Route116_Text_JohnsonPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_Text_ScoundrelMadeOffWithPeeko:
	.string "Oooh, was mache ich nur?!?\p"
	.string "PECKO und ich waren auf einem Spazier-\n"
	.string "gang und da kam so ein Schlägertyp…\p"
	.string "Der Schurke hat mir meinen Liebling\n"
	.string "PECKO geklaut!\p"
	.string "Ooooooooooooaaaargh! PECKO!$"

Route116_Text_WantToDigTunnel:
	.string "Nnn… Brüll!\p"
	.string "Ich will diesen vermaledeiten Tunnel\n"
	.string "graben!$"

Route116_Text_DiggingTunnelWhenGoonOrderedMeOut:
	.string "Nnn… Brüll!\n"
	.string "Was ist hier los?\p"
	.string "Ich war dabei, einen Tunnel ohne Werk-\n"
	.string "zeug zu graben, als so ein Idiot mich\l"
	.string "verjagt hat!\p"
	.string "Dieser Tunnel ist voller POKéMON, die\n"
	.string "sensibel auf Lärm reagieren. Sie können\l"
	.string "einen Aufruhr veranstalten.\p"
	.string "Daher arbeiten wir ohne schwere\n"
	.string "Maschinen an dem Tunnel…\p"
	.string "Ich befürchte, dieser Idiot wird\n"
	.string "irgendetwas Dummes tun und die\l"
	.string "POKéMON in Aufruhr versetzen.$"

Route116_Text_GoonHightailedItOutOfTunnel:
	.string "Nnn… Brüll!\p"
	.string "Dieser dämliche Idiot ist aus dem Tun-\n"
	.string "nel abgehauen. Ich kann weitergraben!$"

Route116_Text_ThankYouTokenOfAppreciation:
	.string "Oh! Du bist das!\p"
	.string "Du hast mir nicht nur im BLÜTEN-\n"
	.string "BURGWALD geholfen, sondern auch\l"
	.string "mein gestohlenes Paket zurückgeholt\l"
	.string "und nach GRAPHITPORT CITY gebracht!\p"
	.string "KAPT. BRIGG hat uns über die Ankunft\n"
	.string "des Paketes unterrichtet!\p"
	.string "Vielen, vielen Dank!\p"
	.string "Wäre ich ein Meer, würde ich\n"
	.string "dich in Dankbarkeit baden und als\l"
	.string "Held auf meinen Wellen tragen!\p"
	.string "Ich habe für dich, den wunderbarsten\n"
	.string "TRAINER, gute Nachrichten!\p"
	.string "Unsere Firma hat vor kurzem eine\n"
	.string "neue Art von POKéBALL entwickelt…\p"
	.string "Als Zeichen meiner Dankbarkeit\n"
	.string "schenke ich ihn dem wunderbarsten\l"
	.string "TRAINER!$"

Route116_Text_NewBallAvailableAtMart:
	.string "Unser neuer POKéBALL wird im PKMN-\n"
	.string "MARKT in METAROST CITY erhältlich sein.\p"
	.string "Bitte, probiere ihn aus!\n"
	.string "Vielen Dank und Lebewohl.$"

Route116_Text_BagIsJamPacked:
	.string "Dein BEUTEL ist brechend voll.\n"
	.string "Ich kann dir diesen WIEDERBALL nicht\l"
	.string "geben.$"

Route116_Text_TokenOfAppreciation:
	.string "Als Zeichen unseres Dankes für die\n"
	.string "Überbringung unseres Paketes, habe ich\l"
	.string "eine neue Art von POKéBALL für dich.\l"
	.string "Für unseren wunderbarsten TRAINER!$"

Route116_Text_CanYouHelpMeFindGlasses:
	.string "Ich habe meine Brille fallen lassen…\n"
	.string "Kannst du mir helfen, sie zu finden?$"

Route116_Text_MayISeeThoseGlasses:
	.string "Deine Brille…\n"
	.string "Darf ich sie mal kurz ausprobieren?$"

Route116_Text_NotWhatImLookingForMaybeTheyArentHere:
	.string "Hmm…\n"
	.string "Das ist ein SCHATTENGLAS.\l"
	.string "Das habe ich nicht gesucht…\p"
	.string "Vielleicht ist meine Brille gar nicht\n"
	.string "hier zu finden…$"

Route116_Text_CantFindGlassesNotHere:
	.string "Hmm…\n"
	.string "Ich kann meine Brille nirgends finden…\l"
	.string "Vielleicht liegt sie gar nicht hier…$"

Route116_Text_NotWhatImLookingFor:
	.string "Hmm…\n"
	.string "Das ist ein SCHATTENGLAS.\l"
	.string "Das habe ich nicht gesucht…$"

Route116_Text_RouteSignRustboro:
	.string "ROUTE 116\n"
	.string "{LEFT_ARROW} METAROST CITY$"

Route116_Text_RusturfTunnelSign:
	.string "METAFLURTUNNEL\n"
	.string "“Verbindet METAROST CITY und\p"
	.string "WIESENFLUR.\n"
	.string "Das Tunnelprojekt wurde abgebrochen.”$"

Route116_Text_TunnelersRestHouse:
	.string "BERGRASTHAUS$"

Route116_Text_TrainerTipsBToStopEvolution:
	.string "TIPPS für TRAINER\p"
	.string "Wenn du die Entwicklung eines POKéMON\n"
	.string "stoppen willst, musst du den B-Knopf\l"
	.string "drücken, während es sich entwickeln\l"
	.string "will.\p"
	.string "Das POKéMON entwickelt sich dann nicht.\n"
	.string "Das nennt man Entwicklungsstopp.$"

Route116_Text_TrainerTipsBagHasPockets:
	.string "TIPPS für TRAINER\p"
	.string "Dein BEUTEL hat mehrere TASCHEn.\p"
	.string "Items werden automatisch in die dafür\n"
	.string "vorgesehene TASCHE gelegt.\p"
	.string "Kein TRAINER kann auf einen eigenen\n"
	.string "BEUTEL verzichten.$"

Route116_EventScript_Geckabor::
    msgbox Route116_Text_Geckabor, MSGBOX_NPC
    end

Route116_Text_Geckabor:
	.string "Hey {PLAYER}, ich bin ein\n"
	.string "Bote von diesem Rom Entwickler.\l"
	.string "Sein name ist Zauke07!\p"
	.string "Immer wenn du mich am ende einer\n"
	.string "Route Siehst, sprich mich an, denn\l"
	.string "ich habe einen Heißen Tipp für dich!\p"
	.string "Tipp:\p"
	.string "Auf dieser Route versteckt sich ein\n"
	.string "Starter aus der 3 Generation mit\l"
	.string "einer Spawnrate von 1%!\p"
	.string "Welches es ist, musst du selbst\n"
	.string "herausfinden :D !$"
