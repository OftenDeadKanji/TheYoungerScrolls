// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/Characters/YN_CharacterStats.h"
#include "YN_Character.generated.h"

class UYN_InventoryComponent;

UCLASS()
class YOUNG_API AYN_Character : public ACharacter
{
	GENERATED_BODY()

public:
	AYN_Character();

	UYN_InventoryComponent* GetInventory() const;
protected:
	virtual void BeginPlay() override;

	virtual void Authority_StatsUpdateCallback();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UYN_InventoryComponent> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats", Replicated)
	FYN_CharacterStats Stats;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerStats")
	float StatsUpdateRate = 0.3f;

	FTimerHandle StatsUpdateTimer;
};
