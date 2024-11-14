// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UInventoryItemInstanceData;
class UWeaponInstanceData;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class YOUNG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	const TArray<UInventoryItemInstanceData*>& GetAllItems() const;

	void AddWeapon(UWeaponInstanceData* Weapon);
	const TArray<UWeaponInstanceData*>& GetWeapons() const;
	const TArray<UInventoryItemInstanceData*>& GetWeaponsAsItems() const;

protected:
	void InitArrays();

	UFUNCTION(Server, Reliable)
	void Server_AddWeapon(UWeaponInstanceData* Weapon);
	void Authority_AddWeapon(UWeaponInstanceData* Weapon);

	UPROPERTY(VisibleInstanceOnly, Replicated)
	TArray<UInventoryItemInstanceData*> Items;

	UPROPERTY(VisibleInstanceOnly, Replicated, Instanced)
	TArray<UWeaponInstanceData*> Weapons;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Replicated)
	TArray<UInventoryItemInstanceData*> ItemsWeapons;

};
