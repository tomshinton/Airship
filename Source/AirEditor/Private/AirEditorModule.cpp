// Fill out your copyright notice in the Description page of Project Settings.

#include "ModuleManager.h"
#include "AirEditorModule.h"
#include <ISettingsModule.h>
#include <ISettingsContainer.h>
#include <Internationalization.h>
#include <ISettingsSection.h>
#include "AirSettings.h"

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
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Airship Settings", "General", FText::FromString("Airship Settings"),  FText::FromString("Base gameplay settings for Airship"), GetMutableDefault<UAirSettings>());

		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FAirEditorModule::HandleSettingsSaved);
		}
	}
}

void FAirEditorModule::UnregisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Airship Settings", "General");
	}
}
