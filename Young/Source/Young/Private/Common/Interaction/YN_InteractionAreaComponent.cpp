// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Common/Interaction/YN_InteractionAreaComponent.h"

#include "Core/Controllers/YN_PlayerController.h"

void UYN_InteractionAreaComponent::SetMaxFacingHalfAngle(float Angle)
{
	MaxFacingHalfAngle = FMath::Clamp(Angle, 0.0f, 180.0f);
}

void UYN_InteractionAreaComponent::Interact(AYN_PlayerController* InteractingPlayerController) const
{
	APawn* InteractingPawn = InteractingPlayerController->GetPawn();

	FVector PawnToArea = (GetComponentLocation() - InteractingPawn->GetActorLocation()).GetUnsafeNormal();
	FVector PawnForward = InteractingPawn->GetActorForwardVector();

	if(PawnToArea.Dot(PawnForward) >= FMath::Cos(MaxFacingHalfAngle))
	{
		OnInteracted.ExecuteIfBound(InteractingPlayerController);
	}
}
