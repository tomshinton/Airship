// Copyright 2019 Tom Shinton. All Rights Reserved.

#include "MoreManagers/Public/ManagerCore/Manager.h"
#include "MoreManagersEditor/Public/Factories/ManagerFactory.h"
#include "Modules/ModuleManager.h"

#include <Developer/AssetTools/Private/AssetTools.h>
#include <Developer/AssetTools/Public/AssetTypeCategories.h>
#include <Developer/AssetTools/Public/AssetToolsModule.h>
#include <Editor/UnrealEd/Public/Kismet2/KismetEditorUtilities.h>
#include <Runtime/Core/Public/Internationalization/Internationalization.h>
#include <Runtime/Engine/Classes/Engine/Blueprint.h>
#include <Runtime/Engine/Classes/Engine/BlueprintGeneratedClass.h>

#include "MoreManagersEditorModule.h"

#define LOCTEXT_NAMESPACE "MoreManagers"

UManagerFactory::UManagerFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;

	SupportedClass = UManager::StaticClass();
}

uint32 UManagerFactory::GetMenuCategories() const
{
	FMoreManagersEditorModule& MoreManagersEditorModule = FModuleManager::LoadModuleChecked<FMoreManagersEditorModule>("MoreManagersEditor");
	return MoreManagersEditorModule.GetMoreManagerCategoryBit();
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
	//return FKismetEditorUtilities::CreateBlueprint(UManager::StaticClass() , InParent, Name, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), CallingContext);

	UManager* NewManager = NewObject<UManager>(InParent, Name, Flags);
	return NewManager;
}

#undef LOCTEXT_NAMESPACE