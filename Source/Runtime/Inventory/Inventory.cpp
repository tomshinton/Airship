#include "Inventory.h"
 
DEFINE_LOG_CATEGORY(InventoryLog);
 
#define LOCTEXT_NAMESPACE "FAirCore"
 
void FInventory::StartupModule()
{
	UE_LOG(InventoryLog, Warning, TEXT("AirUI module has started!"));
}
 
void FInventory::ShutdownModule()
{
	UE_LOG(InventoryLog, Warning, TEXT("AirUI module has shut down"));
}
 
#undef LOCTEXT_NAMESPACE
 
IMPLEMENT_MODULE(FInventory, Inventory)