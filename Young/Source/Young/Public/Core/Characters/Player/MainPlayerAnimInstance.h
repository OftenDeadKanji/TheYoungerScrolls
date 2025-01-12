// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainPlayerAnimInstance.generated.h"

class AMainPlayer;
/**
 * 
 */
UCLASS()
class YOUNG_API UMainPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	TWeakObjectPtr<AMainPlayer> OwningMainPlayer;

	UPROPERTY(BlueprintReadOnly)
	float Speed = 0.0f;
};
