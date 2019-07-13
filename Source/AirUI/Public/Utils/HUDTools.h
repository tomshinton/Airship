// Airship Project - Tom Shinton 2018

#pragma once

#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

namespace HUDTools
{
	bool IsVisible(const UUserWidget& InWidget)
	{
		return InWidget.GetVisibility() == ESlateVisibility::Visible;
	}
}