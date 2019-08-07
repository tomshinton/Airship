// Airship Project - Tom Shinton 2018

#include "Runtime/UI/Public/Elements/SequentialGridPanel.h"

#include <Runtime/UMG/Public/Components/UniformGridPanel.h>
#include <Runtime/UMG/Public/Components/UniformGridSlot.h>

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

#if WITH_EDITOR
const FText USequentialGridPanel::GetPaletteCategory()
{
	return LOCTEXT("", "Inventory Elements");
}
#endif //WITH_EDITOR

#undef LOCTEXT_NAMESPACE