#pragma once

template<class T>
TArray<T*> GetInterfacesDescending(const AActor* InActor)
{
	TArray<T*> FoundInterfaces;

	TArray<UActorComponent*> FoundComponents;
	InActor->GetComponents(FoundComponents);

	for (UActorComponent* FoundComponent : FoundComponents)
	{
		if (T* FoundInterface = Cast<T>(FoundComponent))
		{
			FoundInterfaces.AddUnique(FoundInterface);
		}
	}

	if (FoundInterfaces.Num() > 0)
	{
		return FoundInterfaces;
	}
	else
	{
		UE_LOG(Log, Log, TEXT("Actor doesnt implement requested interface"));
		return TArray<T*>();
	}

}