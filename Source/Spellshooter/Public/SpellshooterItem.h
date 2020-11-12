// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/StaticMesh.h"
#include "Styling/SlateBrush.h"
#include "SpellshooterItem.generated.h"

/**
 * 
 */
UCLASS()
class SPELLSHOOTER_API USpellshooterItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "item")
		FText itemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "item")
		FPrimaryAssetType itemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		USkeletalMesh* storedMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FSlateBrush weaponIcon;



	FString GetIdentifierString() const;
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

};
