// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/Characters/CharacterEx.h"

#include "Core/Characters/Components/InventoryComponent.h"
#include "Net/UnrealNetwork.h"

ACharacterEx::ACharacterEx()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

void ACharacterEx::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACharacterEx, Stats);
}

ELifetimeCondition ACharacterEx::AllowActorComponentToReplicate(const UActorComponent* ComponentToReplicate) const
{
	return Super::AllowActorComponentToReplicate(ComponentToReplicate);
}

const FCharacterStats& ACharacterEx::GetCharacterStats() const
{
	return Stats;
}

void ACharacterEx::BeginPlay()
{
	Super::BeginPlay();

	if(GetNetMode() != NM_Client)
	{
		GetWorldTimerManager().SetTimer(StatsUpdateTimer, this, &ACharacterEx::Authority_StatsUpdateCallback, StatsUpdateRate, true);
	}
}

void ACharacterEx::Authority_StatsUpdateCallback()
{
	Stats.CurrentHealth = FMath::Clamp(Stats.CurrentHealth + Stats.BaseHealthRegeneration * StatsUpdateRate, 0.0f, Stats.MaxHealth);
	Stats.CurrentStamina = FMath::Clamp(Stats.CurrentStamina + Stats.BaseStaminaRegeneration * StatsUpdateRate, 0.0f, Stats.MaxStamina);
	Stats.CurrentMana = FMath::Clamp(Stats.CurrentMana + Stats.BaseManaRegeneration * StatsUpdateRate, 0.0f, Stats.MaxMana);
}
