// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include <Developer/AssetTools/Public/AssetTypeActions_Base.h>
#include <Editor/UnrealEd/Public/Toolkits/IToolkitHost.h>

class FAssetTypeActions_Manager : public FAssetTypeActions_Base
{

public:
	
	FAssetTypeActions_Manager();

	//IAssetTypeActions
	virtual void GetActions(const TArray<UObject *>& InObjects, class FMenuBuilder& MenuBuilder) override;
	virtual bool HasActions(const TArray<UObject *>& InObjects) const override { return true; };
	virtual FColor GetTypeColor() const override;
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;
	virtual void OpenAssetEditor(const TArray<UObject *>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	//~IAssetTypeActions

	void TryAddToInvokeList(UObject* InObject);
};