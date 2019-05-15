// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagers/Public/ManagerCore/Manager.h"
#include "MoreManagersEditor/Public/Factories/ManagerFactory.h"

#include <AssetTypeCategories.h>
#include <Engine/Blueprint.h>
#include <Internationalization.h>
#include <KismetEditorUtilities.h>
#include <Engine/BlueprintGeneratedClass.h>

#define LOCTEXT_NAMESPACE "MoreManagers"

UManagerFactory::UManagerFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;

	SupportedClass = UManager::StaticClass();
}

uint32 UManagerFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Misc;
}

FText UManagerFactory::GetDisplayName() const
{
	return LOCTEXT("MoreManagersManagerBaseDescription", "Manager");
}

bool UManagerFactory::ConfigureProperties()
{
	return true;
}

UObject* UManagerFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	return FKismetEditorUtilities::CreateBlueprint(UManager::StaticClass() , InParent, Name, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), CallingContext);
}

#undef LOCTEXT_NAMESPACE