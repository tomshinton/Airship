// Airship Project - Tom Shinton 2018

#pragma once

class FInvokeToolCommands : public TCommands<FInvokeToolCommands>
{

public:

	/** Default constructor. */
	FInvokeToolCommands();

	/** Initialize commands */
	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> ShowInvokeTool;
};
