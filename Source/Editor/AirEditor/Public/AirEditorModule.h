#pragma once

#include <Runtime/Core/Public/Modules/ModuleManager.h>

#include <AirCore/Public/Core/GameSettings/AirSettings.h>
#include <AirCore/Public/Core/GameSettings/UISettings.h>
#include <Runtime/Input/Public/AirInputSettings.h>
#include <Runtime/Inventory/Public/InventorySettings.h>

DECLARE_LOG_CATEGORY_EXTERN(AirEditorLog, All, All)

class FAirEditorModule : public IModuleInterface
{

public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool SupportsDynamicReloading() override
	{
		return true;
	}

private:

	void RegisterSettings();
	void UnregisterSettings();

	/** Callback for when the settings were saved. */
	bool HandleSettingsSaved()
	{
		UAirSettings* AirSettings = GetMutableDefault<UAirSettings>();
		AirSettings->SaveConfig();

		UUISettings* UISettings = GetMutableDefault<UUISettings>();
		UISettings->SaveConfig();

		return true;
	}
};