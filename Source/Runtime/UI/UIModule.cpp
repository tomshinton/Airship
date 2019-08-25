// Airship Project - Tom Shinton 2018

#include "Runtime/UI/UIModule.h"
 
DEFINE_LOG_CATEGORY(UIModuleLog);
 
#define LOCTEXT_NAMESPACE "FUIModule"
 
void FUIModule::StartupModule()
{
	UE_LOG(UIModuleLog, Log, TEXT("UI module has started!"));
}
 
void FUIModule::ShutdownModule()
{
	UE_LOG(UIModuleLog, Log, TEXT("UI module has shut down"));
}
 
#undef LOCTEXT_NAMESPACE
 
IMPLEMENT_MODULE(FUIModule, UI)