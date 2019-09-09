// Airship Project - Tom Shinton 2018

#pragma once

#include <Runtime/Slate/Public/Framework/Application/NavigationConfig.h>

class FAirUINavigationConfig : public FNavigationConfig
{
public:

	//Air Override all ui navigation to cede TAB and arrow keys back to UI design
	virtual EUINavigation GetNavigationDirectionFromKey(const FKeyEvent& InKeyEvent) const override
	{
		return EUINavigation::Invalid;
	}
};