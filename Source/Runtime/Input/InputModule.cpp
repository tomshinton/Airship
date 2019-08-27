// Airship Project - Tom Shinton 2018

#include "Runtime/Input/InputModule.h"
 
DEFINE_LOG_CATEGORY(InputModuleLog);
 
#define LOCTEXT_NAMESPACE "FInputModule"
 
void FInputModule::StartupModule()
{
	UE_LOG(InputModuleLog, Log, TEXT("InputModule module has started!"));
}
 
void FInputModule::ShutdownModule()
{
	UE_LOG(InputModuleLog, Log, TEXT("InputModule module has shut down"));
}
 
#undef LOCTEXT_NAMESPACE
 
IMPLEMENT_MODULE(FInputModule, Input)