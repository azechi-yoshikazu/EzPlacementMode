// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EasyPlacementModeSettings.generated.h"

UCLASS(config=Engine, meta=(DisplayName="Ez Placement Mode"))
class UEasyPlacementModeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UEasyPlacementModeSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};