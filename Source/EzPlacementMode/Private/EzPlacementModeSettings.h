// Copyright 2023 Yoshikazu Azechi All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EzPlacementModeSettings.generated.h"

USTRUCT()
struct FEzPlacementCategory
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Ez Placement Mode")
	FText Name;

	UPROPERTY(EditDefaultsOnly, Category = "Ez Placement Mode")
	int32 Priority = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Ez Placement Mode", meta = (MetaClass = "Actor", OnlyPlaceable))
	TArray<FSoftClassPath> Classes;

	FName GetHandle() const
	{
		return FName(Name.ToString());
	}
};

UCLASS(config=Engine, defaultconfig, meta=(DisplayName="Ez Placement Mode"))
class UEzPlacementModeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UEzPlacementModeSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(config, EditDefaultsOnly, Category = "Ez Placement Mode")
	TArray<FEzPlacementCategory> Categories;
};