#pragma once

#include <NavigationConfig.h>

class AIRSHIP_API FAirUINavigationConfig : public FNavigationConfig
{

public:

	//Air Override all ui navigation to cede TAB and arrow keys back to UI design
	virtual EUINavigation GetNavigationDirectionFromKey(const FKeyEvent& InKeyEvent) const override
	{
		return EUINavigation::Invalid;
	}
};