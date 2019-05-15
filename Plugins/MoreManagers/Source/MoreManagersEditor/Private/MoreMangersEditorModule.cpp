// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagersEditorModule.h"

IMPLEMENT_MODULE(FMoreManagersEditorModule, MoreManagersEditor);
DEFINE_LOG_CATEGORY(MoreManagersEditorLog)

void FMoreManagersEditorModule::StartupModule()
{
	UE_LOG(MoreManagersEditorLog, Log, TEXT("MoreManagersEditorLog: Module Started"));
}

void FMoreManagersEditorModule::ShutdownModule()
{
	UE_LOG(MoreManagersEditorLog, Warning, TEXT("MoreManagersEditorLog: Module Shutdown"));
}
