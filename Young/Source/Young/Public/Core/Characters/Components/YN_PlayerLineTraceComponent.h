// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YN_PlayerLineTraceComponent.generated.h"

class UCameraComponent;
class UPrimitiveComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YOUNG_API UYN_PlayerLineTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UYN_PlayerLineTraceComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	AActor* GetHitActor();

	UFUNCTION(BlueprintCallable)
	UPrimitiveComponent* GetHitComponent();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECollisionChannel> TraceChannel;

	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* HitActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPrimitiveComponent* HitComponent;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	bool bLogOnScreen = false;
	UPROPERTY(EditAnywhere)
	bool bDebugDraw = false;
#endif
};
