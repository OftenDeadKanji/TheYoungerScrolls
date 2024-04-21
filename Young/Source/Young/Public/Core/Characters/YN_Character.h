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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	FYN_CharacterStats Stats;
};
