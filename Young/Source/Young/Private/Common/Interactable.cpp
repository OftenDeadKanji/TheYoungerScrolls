// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Common/Interactable.h"

void IInteractable::Local_OnUsePressed_Implementation(AMainPlayerController* PlayerController)
{
#if !UE_BUILD_SHIPPING
	if(IInteractable::Execute_IsInteractionByServerRequired(Cast<UObject>(this)))
	{
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, FString::Printf(TEXT("Interact by server required!")));
	}
#endif
}

void IInteractable::Authority_OnUsePressed_Implementation(AMainPlayerController* PlayerController)
{
#if !UE_BUILD_SHIPPING
	if(IInteractable::Execute_IsInteractionByServerRequired(Cast<UObject>(this)) == false)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, FString::Printf(TEXT("Interact by server not required!")));
	}
#endif
}

float IInteractable::GetMaxFacingHalfAngle_Implementation() const
{
	return 180.0f;
}

bool IInteractable::IsInteractionByServerRequired_Implementation() const
{
	return false;
}
