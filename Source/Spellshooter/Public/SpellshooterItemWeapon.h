// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellshooterItem.h"
#include "SpellshooterItemWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SPELLSHOOTER_API USpellshooterItemWeapon : public USpellshooterItem
{
	GENERATED_BODY()
public:
	USpellshooterItemWeapon() { itemType =TEXT("Weapon"); }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
		TSubclassOf<AActor> weaponActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "shooting")
		TSubclassOf<class Abullet> BPbullet;
};
