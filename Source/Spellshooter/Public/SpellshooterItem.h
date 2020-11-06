// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpellshooterItem.generated.h"

/**
 * 
 */
UCLASS()
class SPELLSHOOTER_API USpellshooterItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
		FText itemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
		FPrimaryAssetType itemType;

	FString GetIdentifierString() const;
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

};
