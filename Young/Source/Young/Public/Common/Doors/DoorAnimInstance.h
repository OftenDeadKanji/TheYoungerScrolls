// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "DoorMiscTypes.h"
#include "Animation/AnimInstance.h"
#include "DoorAnimInstance.generated.h"

UCLASS()
class YOUNG_API UDoorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

protected:
	UFUNCTION()
	void OnDoorStateChanged(EDoorState State);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> OpeningAnimation;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float OpeningAnimationDuration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> ClosingAnimation;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float ClosingAnimationDuration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	EDoorState OwnerDoorState;
};
