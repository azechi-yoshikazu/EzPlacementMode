// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EasyPlacementModeSettings.generated.h"

USTRUCT()
struct FEzPlacementCategory
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	int32 Priority = 100;

	UPROPERTY(EditDefaultsOnly, meta = (MetaClass = "Actor", OnlyPlaceable))
	TArray<FSoftClassPath> Classes;

	FName GetHandle() const
	{
		return FName(Name.ToString());
	}
};

UCLASS(config=Engine, defaultconfig, meta=(DisplayName="Ez Placement Mode"))
class UEasyPlacementModeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UEasyPlacementModeSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(config, EditDefaultsOnly)
	TArray<FEzPlacementCategory> Categories;
};