// Fill out your copyright notice in the Description page of Project Settings.

#include "TransferWindowBase.h"

void UTransferWindowBase::SetAppropriateInventories(UAirInventory* InOwnerInventory, UAirInventory* InPlayerInventory)
{
	OwnerInventory = InOwnerInventory;
	PlayerInventory = InPlayerInventory;
}
