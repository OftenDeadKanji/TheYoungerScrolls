// Copyright (c) 2024, Mateusz Chlopek. All rights reserved.


#include "UI/Characters/CharacterStatsWidget.h"

#include "Components/ProgressBar.h"
#include "Core/Characters/CharacterMiscTypes.h"


void UCharacterStatsWidget::Update(const FCharacterStats& Stats)
{
	BarHealth->SetPercent(Stats.CurrentHealth / Stats.MaxHealth);
	BarStamina->SetPercent(Stats.CurrentStamina / Stats.MaxStamina);
	BarMana->SetPercent(Stats.CurrentMana / Stats.MaxMana);
}
