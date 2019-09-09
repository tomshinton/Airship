// Airship Project - Tom Shinton 2018

#include "AirCore.h"
 
DEFINE_LOG_CATEGORY(AirCoreModuleLog);
 
#define LOCTEXT_NAMESPACE "FAirCore"
 
void FAirCore::StartupModule()
{
	UE_LOG(AirCoreModuleLog, Warning, TEXT("AirCore module has started!"));
}
 
void FAirCore::ShutdownModule()
{
	UE_LOG(AirCoreModuleLog, Warning, TEXT("AirCore module has shut down"));
}
 
#undef LOCTEXT_NAMESPACE
 
IMPLEMENT_MODULE(FAirCore,AirCore)