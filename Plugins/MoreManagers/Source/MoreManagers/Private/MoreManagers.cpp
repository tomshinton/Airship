// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagers.h"

#define LOCTEXT_NAMESPACE "FMoreManagersModule"

DEFINE_LOG_CATEGORY(MoreManagersLog);

void FMoreManagersModule::StartupModule()
{
	UE_LOG(MoreManagersLog, Log, TEXT("MoreManagersLog: Module Started"));
}

void FMoreManagersModule::ShutdownModule()
{
	UE_LOG(MoreManagersLog, Warning, TEXT("MoreManagersLog: Module Shutdown"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMoreManagersModule, MoreManagers)