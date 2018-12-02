#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "UnrealEd.h"
#include "AirSettings.h"

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
		UAirSettings* Settings = GetMutableDefault<UAirSettings>();
		Settings->SaveConfig();

		return true;
	}
};