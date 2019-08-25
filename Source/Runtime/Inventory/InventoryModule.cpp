#include "InventoryModule.h"
 
DEFINE_LOG_CATEGORY(InventoryLog);
 
#define LOCTEXT_NAMESPACE "InventoryModule"
 
void FInventoryModule::StartupModule()
{
	UE_LOG(InventoryLog, Log, TEXT("Inventory module has started!"));
}
 
void FInventoryModule::ShutdownModule()
{
	UE_LOG(InventoryLog, Log, TEXT("Inventory module has shut down"));
}
 
#undef LOCTEXT_NAMESPACE
 
IMPLEMENT_MODULE(FInventoryModule, Inventory)