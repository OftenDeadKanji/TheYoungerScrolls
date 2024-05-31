// Copyright (c) 2024, Mateusz Chłopek. All rights reserved.

#include "Core/GameStates/YN_GameStateGame.h"

UDataTable* AYN_GameStateGame::GetInventoryItemsDataTable() const
{
	return InventoryItemsDataTable;
}

UDataTable* AYN_GameStateGame::GetWeaponsDataTable() const
{
	return WeaponsDataTable;
}
