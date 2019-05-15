// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include "Factories/BlueprintFactory.h"
#include <Factories/Factory.h>
#include "ManagerFactory.generated.h"

UCLASS()
class MOREMANAGERSEDITOR_API UManagerFactory : public UFactory
{
	GENERATED_BODY()

public:

	UManagerFactory();

	virtual uint32 GetMenuCategories() const override;
	virtual FText GetDisplayName() const override;

	virtual bool ConfigureProperties() override;
private:

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;

};
