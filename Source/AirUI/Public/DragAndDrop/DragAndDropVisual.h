#pragma once

#include "TextBlock.h"
#include "Image.h"
#include "UserWidget.h"

#include "DragAndDropVisual.generated.h"

UCLASS()
class UDragAndDropVisual : public UUserWidget
{
	GENERATED_BODY()

public:

	UDragAndDropVisual(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
		, DragQuantity(nullptr)
		, DragImage(nullptr)
	{}

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DragQuantity;

	UPROPERTY(meta = (BindWidget))
	UImage* DragImage;

	void SetVisual(const FText& InQuantity, const FSlateBrush InBrush)
	{
		if (DragQuantity && DragImage)
		{
			DragQuantity->SetText(InQuantity);
			DragImage->SetBrush(InBrush);
		}
	}
};