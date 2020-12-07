// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ffaGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPELLSHOOTER_API AffaGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AffaGameMode();
	virtual void PostLogin(APlayerController* newPlayer) override;

	void playerKilled(class AHumanCharacter* killed, class AHumanCharacter* killer, class AcasterCharacterBP* alienKilled, class AcasterCharacterBP* alienKiller);
	void winPlayer(class AffaPlayerState* winner);

	/*
	UPROPERTY(Transient)

		TArray<class AffaPlayerController*> playersAlive; */

	UPROPERTY(Transient)
		TArray<class ASpellshooterPlayerController*> playersAlive;
};
