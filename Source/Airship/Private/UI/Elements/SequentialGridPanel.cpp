// Fill out your copyright notice in the Description page of Project Settings.

#include "SequentialGridPanel.h"
#include <UniformGridSlot.h>

#define LOCTEXT_NAMESPACE "UMG"

USequentialGridPanel::USequentialGridPanel()
	: Columns(1)
{

}

void USequentialGridPanel::AddChildrenInSequence(UWidget* Content)
{
	if (UUniformGridSlot* AddedChild = AddChildToUniformGrid(Content))
	{
		int32 TotalSlots = Slots.Num() -1;

		const int32 TargetRow = TotalSlots / Columns;
		const int32 TargetColumn = (TotalSlots % Columns);

		AddedChild->SetRow(TargetRow);
		AddedChild->SetColumn(TargetColumn);
	}
}

const FText USequentialGridPanel::GetPaletteCategory()
{
	return LOCTEXT("", "Inventory Elements");
}

#undef LOCTEXT_NAMESPACE