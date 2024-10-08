// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "UI/UserWidgetEx.h"

#include "Utilities/PlayerInputMode.h"

bool UUserWidgetEx::IsBlockingPawnInput() const
{
	return bBlockPawnInput || bChildrenBlockPawnInput;
}

EPlayerInputMode UUserWidgetEx::GetRequiredInputMode() const
{
	if(RequiredInputMode == EPlayerInputMode::EUIOnly || ChildrenRequiredInputMode == EPlayerInputMode::EUIOnly)
	{
		return EPlayerInputMode::EUIOnly;
	}

	if(RequiredInputMode == EPlayerInputMode::EGameAndUI || ChildrenRequiredInputMode == EPlayerInputMode::EGameAndUI)
	{
		return EPlayerInputMode::EGameAndUI;
	}
	
	return EPlayerInputMode::EGameOnly;
}

void UUserWidgetEx::UpdateCachedChildrenData(const TArray<const UUserWidgetEx*>& Children)
{
	bChildrenBlockPawnInput = false;
	ChildrenRequiredInputMode = EPlayerInputMode::EGameOnly;

	for (const UUserWidgetEx* Child : Children)
	{
		if (IsValid(Child) == false)
		{
			continue;
		}

		bChildrenBlockPawnInput |= Child->IsBlockingPawnInput();

		if (RequiredInputMode == EPlayerInputMode::EUIOnly || Child->GetRequiredInputMode() == EPlayerInputMode::EUIOnly)
		{
			ChildrenRequiredInputMode = EPlayerInputMode::EUIOnly;
		}
		else if (RequiredInputMode == EPlayerInputMode::EGameAndUI || Child->GetRequiredInputMode() == EPlayerInputMode::EGameAndUI)
		{
			ChildrenRequiredInputMode = EPlayerInputMode::EGameAndUI;
		}
		else
		{
			ChildrenRequiredInputMode = EPlayerInputMode::EGameOnly;
		}
	}
}

void UUserWidgetEx::UpdateInputMode()
{
	EPlayerInputMode Mode = GetRequiredInputMode();

	APlayerController* PlayerController = GetOwningPlayer();
	if(IsValid(PlayerController) == false)
	{
		return;
	}

	if(Mode == EPlayerInputMode::EGameOnly)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
	}
	else if (Mode == EPlayerInputMode::EUIOnly)
	{
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->SetShowMouseCursor(true);
	}
	else
	{
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
	}
}
