#include "BaseFixtures.h"
#include "AirInventory.h"
#include <GameFramework\Character.h>

class FInventoryTestFixture : public FAirBaseFixture
{

public:

	FInventoryTestFixture(const FString& InName, const bool bInComplexTask)
		: FAirBaseFixture(InName, bInComplexTask) {}

	void CreateInventory()
	{
		AActor* OwningCharacter = SpawnActor<AActor>();
		SpawnedInventoryComponent = NewObject<UAirInventory>(OwningCharacter);
		SpawnedInventoryComponent->RegisterComponent();
	}

	UAirInventory* SpawnedInventoryComponent;
};

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FBeginPlayCalledOnInventory_InventoryInitialisedAtCorrectSize, FInventoryTestFixture, "InventoryComponent.BeginPlay.BeginPlayCalledOnInventory_InventoryInitialisedAtCorrectSize", FAirBaseFixture::TestFlags)
bool FBeginPlayCalledOnInventory_InventoryInitialisedAtCorrectSize::RunTest(const FString& Parameters)
{
	CreateInventory();
	SpawnedInventoryComponent->BeginPlay();

	const FInventory PlayerInventory = SpawnedInventoryComponent->GetInventory();

	TestEqual("Expected Inventory to be initialized at correct size", SpawnedInventoryComponent->InventorySize, PlayerInventory.InventorySize);

	for (const FInventoryItem& Item : PlayerInventory.ItemSlots)
	{
		TestEqual("Expected default ItemID", Item.ItemID, InventoryItemStatics::DefaultItemName);
	}

	return true;
}