// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YN_SpawnPoint.generated.h"

class UArrowComponent;
class UCapsuleComponent;

UCLASS()
class YOUNG_API AYN_SpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AYN_SpawnPoint();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCapsuleComponent> CharacterCapsuleCollider;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UArrowComponent> Arrow;
};
