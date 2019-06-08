// Airship Project - Tom Shinton 2018

#pragma once

#include "Engine/DataTable.h"
#include "SoftObjectPath.h"
#include "Utils/Datatypes/InventoryItemRow.h"

#include "InventorySettings.generated.h"

class UDataTable;

///////////////////////////////////////////////////////////////////////////
// InventorySettings asset for global assets - accessed via UnmutableDefaults
//////////////////////////////////////////////////////////////////////////

UCLASS(config = Game, defaultconfig, MinimalAPI)
class  UInventorySettings : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, config, Category = "Lookup", meta = (AllowedClasses = "DataTable"))
	FStringAssetReference InventoryLookup;

	static UInventorySettings* Get()
	{
		return GetMutableDefault<UInventorySettings>();
	}

	static FInventoryItemRow* GetItemInfo(const FName& ItemID)
	{
		FInventoryItemRow NewRow;
		FInventoryItemRow* NewRowPtr = &NewRow;
		UDataTable* ItemDataTable = GetItemLookupTable();
		if (ItemDataTable)
		{
			const int32 NumRows = ItemDataTable->GetRowNames().Num();
			FString Context;

			NewRowPtr = ItemDataTable->FindRow<FInventoryItemRow>(ItemID, Context, false);
		}

		return NewRowPtr;
	}

	static UDataTable* GetItemLookupTable()
	{
		if (UDataTable* InventoryDataTable = Cast<UDataTable>(Get()->InventoryLookup.TryLoad()))
		{
			return InventoryDataTable;
		}

		return nullptr;
	}

};
