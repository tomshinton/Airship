// Airship Project - Tom Shinton 2018

#include "Runtime/Utils/UtilsModule.h"

DEFINE_LOG_CATEGORY(UtilsModuleLog);
 
#define LOCTEXT_NAMESPACE "FAirCore"
 
void FUtilsModule::StartupModule()
{
	UE_LOG(UtilsModuleLog, Log, TEXT("UtilsModule module has started!"));
}
 
void FUtilsModule::ShutdownModule()
{
	UE_LOG(UtilsModuleLog, Log, TEXT("UtilsModule module has shut down"));
}
 
#undef LOCTEXT_NAMESPACE
 
IMPLEMENT_MODULE(FUtilsModule, Utils)