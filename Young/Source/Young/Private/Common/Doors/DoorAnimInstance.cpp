// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Common/Doors/DoorAnimInstance.h"

#include "Common/Doors/Door.h"

void UDoorAnimInstance::NativeInitializeAnimation()
{
	Super::NativeBeginPlay();

	if(IsValid(OpeningAnimation))
	{
		OpeningAnimationDuration = OpeningAnimation->GetPlayLength();
	}

	if(IsValid(ClosingAnimation))
	{
		ClosingAnimationDuration = ClosingAnimation->GetPlayLength();
	}

	ADoor* OwnerDoor = Cast<ADoor>(GetOwningActor());
	if(OwnerDoor == nullptr)
	{
		return;
	}

	OwnerDoorState = OwnerDoor->GetState();
	OwnerDoor->OnStateChanged.AddDynamic(this, &UDoorAnimInstance::OnDoorStateChanged);
}

void UDoorAnimInstance::OnDoorStateChanged(EDoorState State)
{
	OwnerDoorState = State;
}
