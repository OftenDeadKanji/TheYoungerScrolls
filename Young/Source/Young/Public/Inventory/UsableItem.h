// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UsableItem.generated.h"

UINTERFACE(MinimalAPI)
class UUsableItem : public UInterface
{
	GENERATED_BODY()
};

class YOUNG_API IUsableItem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Use(APlayerController* Player);
};
