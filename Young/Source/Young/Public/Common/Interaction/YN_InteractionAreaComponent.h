// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "YN_InteractionAreaComponent.generated.h"

class AYN_PlayerController;

DECLARE_DELEGATE_OneParam(FOnInteracted, AYN_PlayerController*);

UCLASS()
class YOUNG_API UYN_InteractionAreaComponent : public UCapsuleComponent
{
	GENERATED_BODY()

public:
	FOnInteracted OnInteracted;

	void Interact(AYN_PlayerController* InteractingPlayerController) const;
protected:
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0.0f, UIMin = 0.0f, ClampMax = 180.0f, UIMax = 180.0f))
	float MaxFacingHalfAngle = 180.0f;

};
