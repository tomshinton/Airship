#include "WieldingModule.h"
 
DEFINE_LOG_CATEGORY(WieldingModuleLog);
 
#define LOCTEXT_NAMESPACE "FWieldingModule"
 
void FWieldingModule::StartupModule()
{
	UE_LOG(WieldingModuleLog, Warning, TEXT("WieldingModule module has started!"));
}
 
void FWieldingModule::ShutdownModule()
{
	UE_LOG(WieldingModuleLog, Warning, TEXT("WieldingModule module has shut down"));
}
 
#undef LOCTEXT_NAMESPACE
 
IMPLEMENT_MODULE(FWieldingModule, Wielding)