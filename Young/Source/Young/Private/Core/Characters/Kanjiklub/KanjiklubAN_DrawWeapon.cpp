// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/Characters/Kanjiklub/KanjiklubAN_DrawWeapon.h"

#include "Core/Characters/CharacterEx.h"

void UKanjiklubAN_DrawWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACharacterEx* Character = Cast<ACharacterEx>(MeshComp->GetOwner());
	if(IsValid(Character))
	{
		Character->DrawnWeapon();
	}
}
