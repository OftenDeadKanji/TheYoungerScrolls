// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Common/Doors/DoorClosedNotify.h"

#include "Common/Doors/Door.h"

void UDoorClosedNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ADoor* OwnerDoor = Cast<ADoor>(MeshComp->GetOwner());
	if(OwnerDoor == nullptr)
	{
		return;
	}

	OwnerDoor->ClosingAnimationEnded();
}
