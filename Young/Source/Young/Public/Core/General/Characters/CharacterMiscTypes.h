// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMiscTypes.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseHealthRegeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseStaminaRegeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseManaRegeneration;
};
