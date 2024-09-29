// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMiscTypes.h"
#include "GameFramework/Character.h"
#include "CharacterEx.generated.h"

class UInventoryComponent;

UCLASS()
class YOUNG_API ACharacterEx : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterEx();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual ELifetimeCondition AllowActorComponentToReplicate(const UActorComponent* ComponentToReplicate) const override;

	const FCharacterStats& GetCharacterStats() const;
protected:
	virtual void BeginPlay() override;
	virtual void Authority_StatsUpdateCallback();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UInventoryComponent> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats", Replicated)
	FCharacterStats Stats;
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float StatsUpdateRate = 0.3f;

	FTimerHandle StatsUpdateTimer;
};
