// Airship Project - Tom Shinton 2018#

#include "Public/AirTestingModule.h"
#include "ModuleManager.h"

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