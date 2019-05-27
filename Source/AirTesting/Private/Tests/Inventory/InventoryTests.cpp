#include "BaseFixtures.h"
#include "AirInventory.h"
#include <GameFramework\Character.h>

namespace
{
	namespace TestItemInfo
	{
		const FName TestItemID = "TestActor";
		const int32 TestQuantity = 1;
	}
}

class FInventoryTestFixture : public FAirBaseFixture
{

public:

	FInventoryTestFixture(const FString& InName, const bool bInComplexTask)
		: FAirBaseFixture(InName, bInComplexTask) {}

	void CreateInventory()
	{
		ACharacter* OwningCharacter = SpawnActor<ACharacter>();
		SpawnedInventoryComponent = NewObject<UAirInventory>(OwningCharacter);
		SpawnedInventoryComponent->RegisterComponent();

		USceneComponent* RightHand = NewObject<USceneComponent>(OwningCharacter);
		USceneComponent* LeftHand = NewObject<USceneComponent>(OwningCharacter);

		SpawnedInventoryComponent->SetHandComponents(LeftHand, RightHand);
	}

	UAirInventory* SpawnedInventoryComponent;
};

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FBeginPlayCalledOnInventory_InventoryInitialisedAtCorrectSize, FInventoryTestFixture, "Air.InventoryComponent.BeginPlay.BeginPlayCalledOnInventory_InventoryInitialisedAtCorrectSize", FAirBaseFixture::TestFlags)
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

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FBeginPlayCalledOnInventory_OnSlotFocusedUpdateCalled, FInventoryTestFixture, "Air.InventoryComponent.BeginPlay.BeginPlayCalledOnInventory_OnSlotFocusedUpdateCalled", FAirBaseFixture::TestFlags)
bool FBeginPlayCalledOnInventory_OnSlotFocusedUpdateCalled::RunTest(const FString& Parameters)
{
	CreateInventory();

	bool HasBroadcastCorrectly = false;

	SpawnedInventoryComponent->OnSlotFocusUpdated.AddLambda([this, &HasBroadcastCorrectly](const int32 FocusedSlot)
	{
		TestEqual("Expected the initially focused slot to be 0", 0, FocusedSlot);
		
		if (FocusedSlot == 0)
		{
			HasBroadcastCorrectly = true;
		}
	});

	SpawnedInventoryComponent->BeginPlay();

	return HasBroadcastCorrectly;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAddItemCalled_ValidItemBeingPassedIn_ItemAddedToInventory, FInventoryTestFixture, "Air.InventoryComponent.AddItem.AddItemCalled_ValidItemBeingPassedIn_ItemAddedToInventory", FAirBaseFixture::TestFlags)
bool FAddItemCalled_ValidItemBeingPassedIn_ItemAddedToInventory::RunTest(const FString& Parameters)
{
	CreateInventory();
	SpawnedInventoryComponent->BeginPlay();

	SpawnedInventoryComponent->AddItem(TestItemInfo::TestItemID, TestItemInfo::TestQuantity);

	FInventory PlayerInventory = SpawnedInventoryComponent->GetInventory();

	for (const FInventoryItem& Slot : PlayerInventory.ItemSlots)
	{
		if (Slot.ItemID == TestItemInfo::TestItemID && Slot.Quantity == TestItemInfo::TestQuantity)
		{
			return true;
		}
	}

	return false;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAddItemCalled_ValidItemBeingPassedIn_InventoryUpdateCalled, FInventoryTestFixture, "Air.InventoryComponent.AddItem.AddItemCalled_ValidItemBeingPassedIn_InventoryUpdateCalled", FAirBaseFixture::TestFlags)
bool FAddItemCalled_ValidItemBeingPassedIn_InventoryUpdateCalled::RunTest(const FString& Parameters)
{
	CreateInventory();
	SpawnedInventoryComponent->BeginPlay();

	bool HasBroadcastCorrectly = false;

	SpawnedInventoryComponent->OnInventoryUpdated.AddLambda([this, &HasBroadcastCorrectly]()
	{
		HasBroadcastCorrectly = true;
	});

	SpawnedInventoryComponent->AddItem(TestItemInfo::TestItemID, TestItemInfo::TestQuantity);

	return HasBroadcastCorrectly;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAddItemCalled_CurrentFocusHasWieldable_WieldAttempted, FInventoryTestFixture, "Air.InventoryComponent.AddItem.AddItemCalled_CurrentFocusHasWieldable_WieldAttempted", FAirBaseFixture::TestFlags)
bool FAddItemCalled_CurrentFocusHasWieldable_WieldAttempted::RunTest(const FString& Parameters)
{
	CreateInventory();
	SpawnedInventoryComponent->BeginPlay();
	SpawnedInventoryComponent->AddItem(TestItemInfo::TestItemID, TestItemInfo::TestQuantity);



	return true;
}