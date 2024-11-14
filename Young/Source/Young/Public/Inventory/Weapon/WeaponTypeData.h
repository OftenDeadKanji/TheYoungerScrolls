// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/InventoryItemTypeData.h"
#include "WeaponTypeData.generated.h"

class AWeapon;

UCLASS()
class YOUNG_API UWeaponTypeData : public UInventoryItemTypeData
{
	GENERATED_BODY()

public:
	float GetDamage() const;

	const TSubclassOf<AWeapon>& GetActorClass() const;

	const UStaticMesh* GetStaticMesh() const;
	UStaticMesh* GetStaticMesh();

	const USkeletalMesh* GetSkeletalMesh() const;
	USkeletalMesh* GetSkeletalMesh();

	const FName& GetMeshSocketSheathed() const;
	const UAnimSequence* GetAnimSheathing() const;

	const FName& GetMeshSocketDrawn() const;
	const UAnimSequence* GetAnimDrawing() const;

	virtual UInventoryItemInstanceData* CreateItem(UObject* Outer) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AWeapon> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MeshSocketSheathed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* AnimSheathing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MeshSocketDrawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* AnimDrawing;
};
