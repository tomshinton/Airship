// Airship Project - Tom Shinton 2018

#include "AirGameInst.h"
#include "AirUINavigationConfig.h"
#include <SlateApplication.h>

void UAirGameInst::Init()
{
	FSlateApplication::Get().SetNavigationConfig(MakeShareable(new FAirUINavigationConfig));
}
