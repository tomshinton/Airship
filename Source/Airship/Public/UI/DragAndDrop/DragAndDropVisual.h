#pragma once

#include <UserWidget.h>
#include <TextBlock.h>
#include <Image.h>

#include "DragAndDropVisual.generated.h"

UCLASS()
class AIRSHIP_API UDragAndDropVisual : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DragQuantity;

	UPROPERTY(meta = (BindWidget))
	UImage* DragImage;

	void SetVisual(const FText InQuantity, const FSlateBrush InBrush)
	{
		DragQuantity->SetText(InQuantity);
		DragImage->SetBrush(InBrush);
	}
};