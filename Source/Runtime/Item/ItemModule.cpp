// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/Item/ItemModule.h"
 
DEFINE_LOG_CATEGORY(ItemModuleLog);

#define LOCTEXT_NAMESPACE "FItemModule"
 
void FItemModule::StartupModule()
{
	UE_LOG(ItemModuleLog, Log, TEXT("ItemModuleLog module has started!"));
}
 
void FItemModule::ShutdownModule()
{
	UE_LOG(ItemModuleLog, Log, TEXT("ItemModuleLog module has shut down"));
}
 
#undef LOCTEXT_NAMESPACE
 
IMPLEMENT_MODULE(FItemModule, Item)