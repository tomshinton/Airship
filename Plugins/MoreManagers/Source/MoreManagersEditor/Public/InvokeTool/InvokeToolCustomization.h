// Airship Project - Tom Shinton 2018

#pragma once

#include <IDetailCustomization.h>
#include <Editor/PropertyEditor/Public/DetailLayoutBuilder.h>

class FInvokeToolCustomization : public IDetailCustomization
{

public:

	static TSharedRef<IDetailCustomization> MakeInstance()
	{
		return MakeShareable(new FInvokeToolCustomization);
	};

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override
	{
		TSet<UClass*> Classes;

		TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;
		DetailBuilder.GetObjectsBeingCustomized(ObjectsBeingCustomized);

		for (auto WeakObject : ObjectsBeingCustomized)
		{
			if (UObject* Instance = WeakObject.Get())
			{
				Classes.Add(Instance->GetClass());
			}
		}
	}
};
