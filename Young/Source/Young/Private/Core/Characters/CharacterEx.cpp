// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "Core/Characters/CharacterEx.h"

#include "Core/Characters/Components/InventoryComponent.h"
#include "Inventory/Weapon/Weapon.h"
#include "Inventory/Weapon/WeaponInstanceData.h"
#include "Inventory/Weapon/WeaponTypeData.h"
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

void ACharacterEx::ToggleWeapon_RightHand(UWeaponInstanceData* WeaponData)
{
	if(IsValid(WeaponData) == false)
	{
		return;
	}

	if(HasAuthority())
	{
		Authority_ToggleWeapon_RightHand(WeaponData);
	}
	else
	{
		Server_ToggleWeapon_RightHand(WeaponData);
	}
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

void ACharacterEx::Server_ToggleWeapon_RightHand_Implementation(UWeaponInstanceData* WeaponData)
{
	Authority_ToggleWeapon_RightHand(WeaponData);
}

void ACharacterEx::Authority_ToggleWeapon_RightHand(UWeaponInstanceData* WeaponData)
{
	if(IsValid(WeaponData) == false)
	{
		return;
	}

	if (EquippedWeaponRightHand.IsValid())
	{
		const bool bUnequippedSameWeapon = EquippedWeaponRightHand->GetInstanceData() == WeaponData;

		EquippedWeaponRightHand->Destroy();
		EquippedWeaponRightHand.Reset();

		if (bUnequippedSameWeapon)
		{
			if(Combat)
			return;
		}
	}


	UWorld* World = GetWorld();

	FTransform SpawnTransform = GetActorTransform();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	UWeaponTypeData* WeaponTypeData = Cast<UWeaponTypeData>(WeaponData->GetItemTypeData());
	AWeapon* Weapon = World->SpawnActor<AWeapon>(WeaponTypeData->GetActorClass(), SpawnTransform, SpawnParams);

	Weapon->Init(WeaponData);

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponTypeData->GetMeshSocketSheathed());

	EquippedWeaponRightHand = Weapon;
	WeaponData->SetHandMode(EWeaponCurrentHandMode::RightHand);
}

void ACharacterEx::DrawnWeapon()
{
	if (EquippedWeaponRightHand.IsValid() == false)
	{
		return;
	}

	if (UWeaponTypeData* WeaponData = EquippedWeaponRightHand->GetTypeData())
	{
		EquippedWeaponRightHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponData->GetMeshSocketDrawn());
	}
}

void ACharacterEx::EnteredCombat()
{
	OnEnteredCombatDelegate.Broadcast();
}

