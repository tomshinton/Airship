// Airship Project - Tom Shinton 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/UniformGridPanel.h"
#include "SequentialGridPanel.generated.h"

UCLASS(meta = (DisplayName = "Sequential Grid Panel"))
class USequentialGridPanel : public UUniformGridPanel
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
#endif //WITH_EDITOR
	
};
