// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

#include "EzPlacementModeSettings.h"


const FLinearColor FEzPlacementCategory::DefaultIconColor = FLinearColor(0.84375f, 0.84375f, 0.84375f, 1.0f);

UEzPlacementModeSettings::UEzPlacementModeSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CategoryName = "Plugins";
}