// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UInventoryItem;
class UWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YOUNG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	const TArray<UInventoryItem*>& GetAllItems() const;

	void AddWeapon(UWeapon* Weapon);
	const TArray<UWeapon*>& GetWeapons() const;
	const TArray<UInventoryItem*>& GetWeaponsAsItems() const;

protected:
	UFUNCTION(Server, Reliable)
	void Server_AddWeapon(UWeapon* Weapon);
	void Authority_AddWeapon(UWeapon* Weapon);

	UPROPERTY(VisibleInstanceOnly, Replicated)
	TArray<UInventoryItem*> Items;

	UPROPERTY(VisibleInstanceOnly, Replicated)
	TArray<UWeapon*> Weapons;
	UPROPERTY(VisibleInstanceOnly, Replicated)
	TArray<UInventoryItem*> ItemsWeapons;

};
