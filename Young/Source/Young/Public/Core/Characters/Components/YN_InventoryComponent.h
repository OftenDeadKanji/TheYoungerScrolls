// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YN_InventoryComponent.generated.h"

class UYN_InventoryItem;
class UYN_Weapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YOUNG_API UYN_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UYN_InventoryComponent();

	UFUNCTION(BlueprintCallable)
	const TArray<UYN_InventoryItem*>& GetItems() const;

	UFUNCTION(BlueprintCallable)
	void AddWeapon(UYN_Weapon* Weapon);
	UFUNCTION(BlueprintCallable)
	const TArray<UYN_Weapon*>& GetWeapons() const;
	UFUNCTION(BlueprintCallable)
	const TArray<UYN_InventoryItem*>& GetWeaponsAsItems() const;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TArray<UYN_InventoryItem*> Items;
	UPROPERTY(VisibleAnywhere)
	TArray<UYN_InventoryItem*> ItemsWeapons;

	UPROPERTY(VisibleAnywhere)
	TArray<UYN_Weapon*> Weapons;
};
