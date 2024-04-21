// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Common/YN_SpawnPoint.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"

AYN_SpawnPoint::AYN_SpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	CharacterCapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CharacterCapsuleCollider"));
	RootComponent = CharacterCapsuleCollider;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
}


