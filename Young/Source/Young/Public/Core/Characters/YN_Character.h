// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/Characters/YN_CharacterStats.h"
#include "YN_Character.generated.h"


UCLASS()
class YOUNG_API AYN_Character : public ACharacter
{
	GENERATED_BODY()

public:
	AYN_Character();

protected:
	virtual void BeginPlay() override;

	virtual void Authority_StatsUpdateCallback();

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	FYN_CharacterStats Stats;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerStats")
	float StatsUpdateRate = 0.3f;

	FTimerHandle StatsUpdateTimer;
};
