// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/Characters/Player/MainPlayerAnimInstance.h"

#include "Core/Characters/Player/MainPlayer.h"

void UMainPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningMainPlayer = Cast<AMainPlayer>( GetOwningActor());

	if (OwningMainPlayer.IsValid())
	{
		OwningMainPlayer->OnEnteredCombatDelegate.AddUniqueDynamic(this, &UMainPlayerAnimInstance::EnteredCombat);
	}
}

void UMainPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(OwningMainPlayer.IsValid())
	{
		Speed = OwningMainPlayer->GetVelocity().Size();
	}
}

void UMainPlayerAnimInstance::EnteredCombat()
{
	bInCombat = true;
}
