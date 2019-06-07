#include "BaseFixtures.h"
#include "AirInventory.h"
#include <GameFramework\Character.h>
#include <EngineUtils.h>
#include "WorldItem.h"
#include "Utils\Functions\InventoryFunctions.h"

#if WITH_DEV_AUTOMATION_TESTS

namespace
{
	namespace TestItemInfo
	{
		const FName TestItemID = "TestItem";
		const int32 TestQuantity = 2;
	}
}

class FInventoryTestFixture : public FAirBaseFixture
{

public:

	FInventoryTestFixture(const FString& InName, const bool bInComplexTask)
		: FAirBaseFixture(InName, bInComplexTask) {}

	virtual void BeginTest()
	{
		FAirBaseFixture::BeginTest();

		CreateInventory();
	}

	virtual void EndTest()
	{
		FAirBaseFixture::EndTest();

		if (SpawnedInventoryComponent)
		{
			SpawnedInventoryComponent = nullptr;
		}
	}

	void CreateInventory()
	{
		if (ACharacter* SpawnedCharacter = SpawnActor<ACharacter>())
		{
			SpawnedInventoryComponent = NewObject<UAirInventory>(SpawnedCharacter);
			SpawnedInventoryComponent->RegisterComponent();

			USceneComponent* RightHand = NewObject<USceneComponent>(SpawnedCharacter);
			USceneComponent* LeftHand = NewObject<USceneComponent>(SpawnedCharacter);

			SpawnedInventoryComponent->SetHandComponents(LeftHand, RightHand);
		}
	}

	int32 GetWorldItems() const
	{
		int32 FoundItems = 0;
		if (GameWorld)
		{
			for (TActorIterator<AWorldItem> Itr(GameWorld); Itr; ++Itr)
			{
				if (AWorldItem* Item = *Itr)
				{
					if(!Item->IsActorBeingDestroyed())
					{
						FoundItems++;
					}
				}
			}
		}

		return FoundItems;
	}

	UAirInventory* SpawnedInventoryComponent;
	F
};

/** Initialization*/

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FBeginPlayCalledOnInventory_InventoryInitialisedAtCorrectSize, FInventoryTestFixture, "Air.InventoryComponent.BeginPlay.BeginPlayCalledOnInventory_InventoryInitialisedAtCorrectSize", FAirBaseFixture::TestFlags)
bool FBeginPlayCalledOnInventory_InventoryInitialisedAtCorrectSize::RunTest(const FString& Parameters)
{
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

/** Adding Items */

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAddItemCalled_ValidItemBeingPassedIn_ItemAddedToInventory, FInventoryTestFixture, "Air.InventoryComponent.AddItem.AddItemCalled_ValidItemBeingPassedIn_ItemAddedToInventory", FAirBaseFixture::TestFlags)
bool FAddItemCalled_ValidItemBeingPassedIn_ItemAddedToInventory::RunTest(const FString& Parameters)
{
	SpawnedInventoryComponent->BeginPlay();

	SpawnedInventoryComponent->AddItem(TestItemInfo::TestItemID, TestItemInfo::TestQuantity);

	FInventory PlayerInventory = SpawnedInventoryComponent->GetInventory();
	TestTrue(TEXT("Expected the player inventory to contain the TestItem"), UInventoryFunctions::InventoryContains(PlayerInventory, TestItemInfo::TestItemID, TestItemInfo::TestQuantity));

	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAddItemCalled_ValidItemBeingPassedIn_InventoryUpdateCalled, FInventoryTestFixture, "Air.InventoryComponent.AddItem.AddItemCalled_ValidItemBeingPassedIn_InventoryUpdateCalled", FAirBaseFixture::TestFlags)
bool FAddItemCalled_ValidItemBeingPassedIn_InventoryUpdateCalled::RunTest(const FString& Parameters)
{
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
	SpawnedInventoryComponent->BeginPlay();
	SpawnedInventoryComponent->AddItem(TestItemInfo::TestItemID, TestItemInfo::TestQuantity);

	TestTrue("Expected there to be at least 1 spawned wieldable in the world", GetWorldItems() > 0);

	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAddItemCalled_CurrentFocusHasWieldable_WieldAttempted, FInventoryTestFixture, "Air.InventoryComponent.AddItem.AddItemCalled_AmountSpansOverTwoStacks_InventoryContainsTwoPopulatedStacks", FAirBaseFixture::TestFlags)
bool FAddItemCalled_CurrentFocusHasWieldable_WieldAttempted::RunTest(const FString& Parameters)
{
	SpawnedInventoryComponent->BeginPlay();
	SpawnedInventoryComponent->AddItem(TestItemInfo::TestItemID, TestItemInfo::TestQuantity);

	TestTrue("Expected there to be at least 1 spawned wieldable in the world", GetWorldItems() > 0);

	return true;
}

/** Removing items*/

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FRemoveItemCalled_ValidItemRequestingRemoval_ItemRemovedFromInventory, FInventoryTestFixture, "Air.InventoryComponent.RemoveItem.RemoveItemCalled_ValidItemRequestingRemoval_ItemRemovedFromInventory", FAirBaseFixture::TestFlags)
bool FRemoveItemCalled_ValidItemRequestingRemoval_ItemRemovedFromInventory::RunTest(const FString& Parameters)
{
	SpawnedInventoryComponent->BeginPlay();
	SpawnedInventoryComponent->AddItem(TestItemInfo::TestItemID, TestItemInfo::TestQuantity);

	TestTrue(TEXT("Expected the player inventory to contain the TestItem"), UInventoryFunctions::InventoryContains(SpawnedInventoryComponent->GetInventory(), TestItemInfo::TestItemID, TestItemInfo::TestQuantity));

	SpawnedInventoryComponent->RemoveItem(TestItemInfo::TestItemID, TestItemInfo::TestQuantity);

	TestFalse(TEXT("Expected there to be no instances of item in inventory"), UInventoryFunctions::InventoryContains(SpawnedInventoryComponent->GetInventory(), TestItemInfo::TestItemID, TestItemInfo::TestQuantity));

	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FRemoveItemCalled_ValidItemBeingPassedIn_InventoryUpdateCalled, FInventoryTestFixture, "Air.InventoryComponent.RemoveItem.RemoveItemCalled_ValidItemBeingPassedIn_InventoryUpdateCalled", FAirBaseFixture::TestFlags)
bool FRemoveItemCalled_ValidItemBeingPassedIn_InventoryUpdateCalled::RunTest(const FString& Parameters)
{
	SpawnedInventoryComponent->BeginPlay();

	bool HasBroadcastCorrectly = false;

	SpawnedInventoryComponent->OnInventoryUpdated.AddLambda([this, &HasBroadcastCorrectly]()
	{
		HasBroadcastCorrectly = true;
	});

	SpawnedInventoryComponent->RemoveItem(TestItemInfo::TestItemID, TestItemInfo::TestQuantity);

	return HasBroadcastCorrectly;
}
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FRemoveItemCalled_ValidItemRequestingRemoval_ItemRemovedFromInventoryAndReturned, FInventoryTestFixture, "Air.InventoryComponent.RemoveItem.RemoveItemCalled_ValidItemRequestingRemoval_ItemRemovedFromInventoryAndReturned", FAirBaseFixture::TestFlags)
bool FRemoveItemCalled_ValidItemRequestingRemoval_ItemRemovedFromInventoryAndReturned::RunTest(const FString& Parameters)
{
	//We're allowed to try and remove more than we have in the inventory.  IN this case, request 20 be removed, but only expect 10 to be returned.
	const int32 RequestAmount = 20;
	const int32 AmountActuallyInInventory = 10;

	SpawnedInventoryComponent->BeginPlay();
	SpawnedInventoryComponent->AddItem(TestItemInfo::TestItemID, AmountActuallyInInventory);

	TestTrue(TEXT("Expected the player inventory to contain the TestItem"), UInventoryFunctions::InventoryContains(SpawnedInventoryComponent->GetInventory(), TestItemInfo::TestItemID, AmountActuallyInInventory));

	FInventory Inventory = SpawnedInventoryComponent->GetInventory();

	const FInventoryItem ReturnedItem = UInventoryFunctions::RemoveItem(Inventory, TestItemInfo::TestItemID, RequestAmount);

	TestEqual(TEXT("Expected the ReturnedItem to have the correct quantity"), ReturnedItem.Quantity, AmountActuallyInInventory);
	TestEqual(TEXT("Expected the ReturnedItem to have the correct ItemID"), ReturnedItem.ItemID, TestItemInfo::TestItemID);

	TestFalse(TEXT("Expected the inventory to no longer contain the TestItem"), UInventoryFunctions::InventoryContains(Inventory, TestItemInfo::TestItemID, AmountActuallyInInventory));
		
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FRemoveItemCalled_ValidItemRequestingPartialRemoval_ItemPartiallyRemovedFromInventory, FInventoryTestFixture, "Air.InventoryComponent.RemoveItem.RemoveItemCalled_ValidItemRequestingPartialRemoval_ItemPartiallyRemovedFromInventory", FAirBaseFixture::TestFlags)
bool FRemoveItemCalled_ValidItemRequestingPartialRemoval_ItemPartiallyRemovedFromInventory::RunTest(const FString& Parameters)
{
	SpawnedInventoryComponent->BeginPlay();
	SpawnedInventoryComponent->AddItem(TestItemInfo::TestItemID, TestItemInfo::TestQuantity);

	TestTrue(TEXT("Expected the player inventory to contain the TestItem"), UInventoryFunctions::InventoryContains(SpawnedInventoryComponent->GetInventory(), TestItemInfo::TestItemID, TestItemInfo::TestQuantity));

	//remove 1
	SpawnedInventoryComponent->RemoveItem(TestItemInfo::TestItemID, (int32)TestItemInfo::TestQuantity * 0.5);

	//should still have 1 left in the inventory
	TestEqual(TEXT("Expected there to be half as many instances of TestItem in player inventory"), UInventoryFunctions::GetNumItemsInInventory(SpawnedInventoryComponent->GetInventory(), TestItemInfo::TestItemID), (int32)TestItemInfo::TestQuantity * 0.5);

	return true;
}

/** Focus Changing */

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FFocusChange_ItemWieldedThenFocusChanged_ItemDestroyed, FInventoryTestFixture, "Air.InventoryComponent.Focus.FocusChange_ItemWieldedThenFocusChanged_ItemDestroyed", FAirBaseFixture::TestFlags)
bool FFocusChange_ItemWieldedThenFocusChanged_ItemDestroyed::RunTest(const FString& Parameters)
{
	const int32 NumHotbarSlots = 10;
	SpawnedInventoryComponent->HotbarSlots = NumHotbarSlots;
	SpawnedInventoryComponent->SetCurrentFocusSlot(0);

	SpawnedInventoryComponent->BeginPlay();
	SpawnedInventoryComponent->AddItem(TestItemInfo::TestItemID, TestItemInfo::TestQuantity);

	TestTrue("Expected there to be at least 1 spawned wieldable in the world", GetWorldItems() > 0);

	SpawnedInventoryComponent->FocusNextItem();

	TestTrue("Expected previous wieldable to have been destroyed", GetWorldItems() == 0);
	
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FFocusChange_FocusAlreadyAtEndOfHotbarAndFocusNextItemCalled_FocusSetToStart, FInventoryTestFixture, "Air.InventoryComponent.Focus.FocusChange_FocusAlreadyAtEndOfHotbarAndFocusNextItemCalled_FocusSetToStart", FAirBaseFixture::TestFlags)
bool FFocusChange_FocusAlreadyAtEndOfHotbarAndFocusNextItemCalled_FocusSetToStart::RunTest(const FString& Parameters)
{
	const int32 NumHotbarSlots = 10;
	SpawnedInventoryComponent->HotbarSlots = NumHotbarSlots;
	SpawnedInventoryComponent->SetCurrentFocusSlot(NumHotbarSlots - 1);
	SpawnedInventoryComponent->FocusNextItem();

	TestTrue("Expected focused slot to have wrapped around to 0", SpawnedInventoryComponent->GetCurrentFocusedSlot() == 0);

	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FFocusChange_FocusAtStartOfHotbarAndLastItemCalled_FocusSetToEnd, FInventoryTestFixture, "Air.InventoryComponent.Focus.FocusChange_FocusAtStartOfHotbarAndLastItemCalled_FocusSetToEnd", FAirBaseFixture::TestFlags)
bool FFocusChange_FocusAtStartOfHotbarAndLastItemCalled_FocusSetToEnd::RunTest(const FString& Parameters)
{
	const int32 NumHotbarSlots = 10;
	SpawnedInventoryComponent->HotbarSlots = NumHotbarSlots;
	SpawnedInventoryComponent->SetCurrentFocusSlot(0);
	SpawnedInventoryComponent->FocusLastItem();

	TestTrue("Expected focused slot to have wrapped around to 0", SpawnedInventoryComponent->GetCurrentFocusedSlot() == NumHotbarSlots - 1);

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS
