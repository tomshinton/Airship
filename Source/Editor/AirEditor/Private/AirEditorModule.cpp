// Airship Project - Tom Shinton 2018

#include "Editor/AirEditor/Public/AirEditorModule.h"

#include <Developer/Settings/Public/ISettingsContainer.h>
#include <Developer/Settings/Public/ISettingsModule.h>
#include <Developer/Settings/Public/ISettingsSection.h>

IMPLEMENT_MODULE(FAirEditorModule, AirEditor);
DEFINE_LOG_CATEGORY(AirEditorLog)

void FAirEditorModule::StartupModule()
{
	UE_LOG(AirEditorLog, Log, TEXT("AirEditor: Module Started"));

	RegisterSettings();
}

void FAirEditorModule::ShutdownModule()
{
	UE_LOG(AirEditorLog, Warning, TEXT("AirEditor: Module Shutdown"));
}

void FAirEditorModule::RegisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		SettingsContainer->DescribeCategory("Airship Settings", FText::FromString("Airship Settings"), FText::FromString("Base gameplay settings for Airship"));
		
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Airship Settings", "General", FText::FromString("Airship Settings"), FText::FromString("Base gameplay settings for Airship"), GetMutableDefault<UAirSettings>());
		ISettingsSectionPtr UISettingsSection = SettingsModule->RegisterSettings("Project", "Airship Settings", "UI", FText::FromString("Airship UI Settings"), FText::FromString("UI Settings"), GetMutableDefault<UUISettings>());
		ISettingsSectionPtr InventorySettingsSection = SettingsModule->RegisterSettings("Project", "Airship Settings", "Inventory", FText::FromString("Airship Inventory Settings"), FText::FromString("Inventory Settings"), GetMutableDefault<UInventorySettings>());
		ISettingsSectionPtr AirInputSettingsSection = SettingsModule->RegisterSettings("Project", "Airship Settings", "Input", FText::FromString("Airship Input Settings"), FText::FromString("Bespoke Input settings for InputModule"), GetMutableDefault<UAirInputSettings>());

		if (SettingsSection.IsValid() &&
			UISettingsSection.IsValid() &&
			InventorySettingsSection.IsValid() &&
			AirInputSettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FAirEditorModule::HandleSettingsSaved);
			UISettingsSection->OnModified().BindRaw(this, &FAirEditorModule::HandleSettingsSaved);
			InventorySettingsSection->OnModified().BindRaw(this, &FAirEditorModule::HandleSettingsSaved);
			AirInputSettingsSection->OnModified().BindRaw(this, &FAirEditorModule::HandleSettingsSaved);
		}
	}
}

void FAirEditorModule::UnregisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Airship Settings", "General");
		SettingsModule->UnregisterSettings("Project", "AirShip Settings", "UI");
		SettingsModule->UnregisterSettings("Project", "AirShip Settings", "Inventory");
		SettingsModule->UnregisterSettings("Project", "AirShip Settings", "Input");
	}
}
