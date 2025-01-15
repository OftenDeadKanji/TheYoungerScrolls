// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/Characters/Kanjiklub/KanjiklubAN_EnteredCombat.h"

#include "Core/Characters/CharacterEx.h"

void UKanjiklubAN_EnteredCombat::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACharacterEx* Character = Cast<ACharacterEx>(MeshComp->GetOwner());
	if(IsValid(Character) == false)
	{
		return;
	}

	Character->EnteredCombat();
}
