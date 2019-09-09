// Airship Project - Tom Shinton 2018

#include "ProjectileModule.h"
 
DEFINE_LOG_CATEGORY(ProjectileLog);
 
#define LOCTEXT_NAMESPACE "FProjectileModule"
 
void FProjectileModule::StartupModule()
{
	UE_LOG(ProjectileLog, Log, TEXT("Projectile module has started!"));
}
 
void FProjectileModule::ShutdownModule()
{
	UE_LOG(ProjectileLog, Log, TEXT("Projectile module has shut down"));
}
 
#undef LOCTEXT_NAMESPACE
 
IMPLEMENT_MODULE(FProjectileModule, Projectile)