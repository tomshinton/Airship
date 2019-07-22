#include "AirUI.h"
 
DEFINE_LOG_CATEGORY(AirUIModuleLog);
 
#define LOCTEXT_NAMESPACE "FAirCore"
 
void FAirUI::StartupModule()
{
	UE_LOG(AirUIModuleLog, Warning, TEXT("AirUI module has started!"));
}
 
void FAirUI::ShutdownModule()
{
	UE_LOG(AirUIModuleLog, Warning, TEXT("AirUI module has shut down"));
}
 
#undef LOCTEXT_NAMESPACE
 
IMPLEMENT_MODULE(FAirUI,AirUI)