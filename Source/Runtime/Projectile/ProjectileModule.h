// Airship Project - Tom Shinton 2018

#pragma once
 
#include "ModuleManager.h"
 
DECLARE_LOG_CATEGORY_EXTERN(ProjectileLog, All, All);
 
class FProjectileModule : public IModuleInterface
{
	public:
 
	/* This will get called when the editor loads the module */
	virtual void StartupModule() override;
 
	/* This will get called when the editor unloads the module */
	virtual void ShutdownModule() override;
};