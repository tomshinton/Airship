// Airship Project - Tom Shinton 2018

#pragma once

namespace InterfaceHelpers
{
	template<class T>
	T* GetInterface(AActor& InActor)
	{
		if (T* BaseImpl = Cast<T>(&InActor))
		{
			return BaseImpl;
		}

		TArray<T*> FoundInterfaces;
		for (UActorComponent* FoundComponent : InActor.GetComponentsByClass(UActorComponent::StaticClass()))
		{
			if (T* FoundInterface = Cast<T>(FoundComponent))
			{
				return FoundInterface;
			}
		}
		
		return nullptr;
	}
}