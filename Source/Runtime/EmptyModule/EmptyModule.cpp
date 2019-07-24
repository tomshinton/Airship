#include "Inventory.h"
 
DEFINE_LOG_CATEGORY(EmptyModuleLog);
 
#define LOCTEXT_NAMESPACE "FAirCore"
 
void FEmptyModule::StartupModule()
{
	UE_LOG(EmptyModuleLog, Warning, TEXT("EmptyModule module has started!"));
}
 
void FEmptyModule::ShutdownModule()
{
	UE_LOG(EmptyModuleLog, Warning, TEXT("EmptyModule module has shut down"));
}
 
#undef LOCTEXT_NAMESPACE
 
IMPLEMENT_MODULE(FEmptyModule, EmptyModule)