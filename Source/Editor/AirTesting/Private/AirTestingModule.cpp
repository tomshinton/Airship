// Fill out your copyright notice in the Description page of Project Settings.

#include "ModuleManager.h"
#include "Public/AirTestingModule.h"

IMPLEMENT_MODULE(FAirTestingModule, AirTesting);
DEFINE_LOG_CATEGORY(AirTestingLog)

void FAirTestingModule::StartupModule()
{
	UE_LOG(AirTestingLog, Log, TEXT("AirTesting: Module Started"));
}

void FAirTestingModule::ShutdownModule()
{
	UE_LOG(AirTestingLog, Warning, TEXT("AirTesting: Module Shutdown"));
}