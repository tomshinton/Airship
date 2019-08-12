// Copyright 2019 Tom Shinton. All Rights Reserved.

#pragma once

#include <Editor/BlueprintGraph/Classes/EdGraphSchema_K2.h>

#include "ManagerEditorSchema.generated.h"

UCLASS()
class UManagerEditorSchema : public UEdGraphSchema_K2
{
	GENERATED_BODY()
	
	//EdGraphSchemaInterface
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual void GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, class FMenuBuilder* MenuBuilder, bool bIsDebugging) const override;
	//~EdGraphSchemaInterface

	void GetAllGraphActions(FGraphContextMenuBuilder& ContextMenuBuilder);
};
