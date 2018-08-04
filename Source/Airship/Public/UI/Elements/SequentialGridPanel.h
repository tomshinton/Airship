// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UniformGridPanel.h"
#include "SequentialGridPanel.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Sequential Grid Panel"))
class AIRSHIP_API USequentialGridPanel : public UUniformGridPanel
{
	GENERATED_BODY()

	USequentialGridPanel();

public:

	UPROPERTY(EditAnywhere, Category = "Layout", meta = (ClampMin = "1", UIMin = "1"))
	int32 Columns;

	UFUNCTION(BlueprintCallable, Category = Layout)
	void AddChildrenInSequence(UWidget* Child);

#if WITH_EDITOR
		virtual const FText GetPaletteCategory() override;
#endif
	
};
