// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MoreManagersEditor/Public/InvokeTool/InvokeToolCommands.h"

#include <Runtime/Slate/Public/Framework/Commands/Commands.h>
#include <Runtime/Slate/Public/Framework/Commands/UICommandInfo.h>

#define LOCTEXT_NAMESPACE "InvokeToolCommands"

FInvokeToolCommands::FInvokeToolCommands()
	: TCommands<FInvokeToolCommands>("FInvokeToolCommands", LOCTEXT("InvokeToolCommands", "Invoke Tool Commands"), NAME_None, "FInvokeToolCommandsStyle")
{
}

void FInvokeToolCommands::RegisterCommands()
{
	UI_COMMAND(ShowInvokeTool, "Show MoreManagers Invoke Tool", "Allow for Editor side configuration of the MoreManagers Invoke tool", EUserInterfaceActionType::RadioButton, FInputChord());
}

#undef LOCTEXT_NAMESPACE
