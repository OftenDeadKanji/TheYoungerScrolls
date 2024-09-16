// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Common/Doors/Door.h"

#include "Common/Doors/DoorMiscTypes.h"
#include "Net/UnrealNetwork.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	GetSkeletalMeshComponent()->SetGenerateOverlapEvents(true);
}

void ADoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADoor, State);
}

void ADoor::Authority_OnUsePressed_Implementation(AMainPlayerController* PlayerController)
{
	IInteractable::Authority_OnUsePressed_Implementation(PlayerController);

	if(State == EDoorState::EOpen)
	{
		State = EDoorState::EClosing;
	}
	else if (State == EDoorState::EClosed)
	{
		State = EDoorState::EOpening;
	}
	else
	{
		return;
	}

	OnRep_State();
}

float ADoor::GetMaxFacingHalfAngle_Implementation() const
{
	return 60.0f;
}

bool ADoor::IsInteractionByServerRequired_Implementation() const
{
	return true;
}

EDoorState ADoor::GetState() const
{
	return State;
}

void ADoor::OpeningAnimationEnded()
{
	if (GetNetMode() != NM_Client)
	{
		State = EDoorState::EOpen;
		OnRep_State();
	}
}

void ADoor::ClosingAnimationEnded()
{
	if (GetNetMode() != NM_Client)
	{
		State = EDoorState::EClosed;
		OnRep_State();
	}
}

void ADoor::OnRep_State()
{
	OnStateChanged.Broadcast(State);
}
