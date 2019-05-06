// Fill out your copyright notice in the Description page of Project Settings.

#include "AirGameMode.h"
#include "Public/Core/AirPawn.h"
#include "Public/Core/AirController.h"
#include "Public/Core/AirChar.h"
#include "AirHUD.h"

AAirGameMode::AAirGameMode()
{
	DefaultPawnClass = AAirChar::StaticClass();
	PlayerControllerClass = AAirController::StaticClass();
	HUDClass = AAirHUD::StaticClass();
}