// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpellshooterPlayerController.generated.h"



UCLASS()
class SPELLSHOOTER_API ASpellshooterPlayerController : public APlayerController
{
	GENERATED_BODY()


private:
	//	Store for player (individual since some players have already purchased specific weapons/spells)	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UStoreComponent* playerStore;

public:
	ASpellshooterPlayerController();

	//	Return players store

	//	Get the charater that player is controlling
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Controller")
		class AHumanCharacter* GetControlledSpellshooterCharacter() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Store")
	class UStoreComponent* GetPlayerStore() const { return playerStore; }

};
