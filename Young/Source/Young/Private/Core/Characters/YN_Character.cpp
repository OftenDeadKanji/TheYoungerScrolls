// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.


#include "Core/Characters/YN_Character.h"

#include "Net/UnrealNetwork.h"

#include "Core/Characters/Components/YN_InventoryComponent.h"
#include "Utilities/DebugMacros.h"

AYN_Character::AYN_Character()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Inventory = CreateDefaultSubobject<UYN_InventoryComponent>(TEXT("Inventory"));
}

UYN_InventoryComponent* AYN_Character::GetInventory() const
{
	return Inventory;
}

void AYN_Character::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(StatsUpdateTimer, this, &AYN_Character::Authority_StatsUpdateCallback, StatsUpdateRate, true);
	}
}

void AYN_Character::Authority_StatsUpdateCallback()
{
	CheckHasAuthority();

	Stats.CurrentHealth += Stats.BaseHealthRegeneration * StatsUpdateRate;
	Stats.CurrentHealth = FMath::Clamp(Stats.CurrentHealth, 0.0f, Stats.MaxHealth);

	Stats.CurrentStamina += Stats.BaseStaminaRegeneration * StatsUpdateRate;
	Stats.CurrentStamina = FMath::Clamp(Stats.CurrentStamina, 0.0f, Stats.MaxStamina);

	Stats.CurrentMana += Stats.BaseManaRegeneration * StatsUpdateRate;
	Stats.CurrentMana = FMath::Clamp(Stats.CurrentMana, 0.0f, Stats.MaxMana);
}

void AYN_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AYN_Character, Stats);
}
