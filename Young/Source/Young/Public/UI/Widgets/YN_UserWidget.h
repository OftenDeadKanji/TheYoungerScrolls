// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YN_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class YOUNG_API UYN_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	bool IsBlockingMovementAndCameraInput() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockingMovementAndCameraInput;
};
