// Fill out your copyright notice in the Description page of Project Settings.


#include "ffaGameMode.h"
#include "ffaPlayerController.h"
#include "SpellshooterPlayerController.h"
#include "ffaPlayerState.h"
#include "ffaGameState.h"
#include "humanCharacter.h"
#include "casterCharacterBP.h"
#include "Net/UnrealNetwork.h"

AffaGameMode::AffaGameMode()
	: Super() {
}

void AffaGameMode::PostLogin(APlayerController* newPlayer)
{
	Super::PostLogin(newPlayer);

	//playersAlive.Add(Cast<AffaPlayerController>(newPlayer));
	//playersAlive.Add(Cast<ASpellshooterPlayerController>(newPlayer));
}

void AffaGameMode::playerKilled(class AHumanCharacter* killed, class AHumanCharacter* killer, class AcasterCharacterBP* alienKilled, class AcasterCharacterBP* alienKiller) {
	if (HasAuthority() && doOnce == false) {
		UWorld* World = GetWorld();
		playerStArr = World->GetGameState()->PlayerArray;
		onRep_updateArr();
		numOfElements = 0;
		numOfElements = playerStArr.Num();
		UE_LOG(LogTemp, Warning, TEXT("player array:, %d"), numOfElements);
		doOnce = true;
	}
	if (killed) {
		if (APlayerState* player = Cast<APlayerState>(killed->GetPlayerState())) {
			playerStArr.RemoveSingle(player);
			onRep_updateArr();
		}
	}
	if (alienKilled) {
		if (APlayerState* player = Cast<APlayerState>(alienKilled->GetPlayerState())) {
			playerStArr.RemoveSingle(player);
			onRep_updateArr();
		}
	}
	if (playerStArr.Num() == 1 && playerStArr.IsValidIndex(0) && killer) {
		winPlayer(Cast<AffaPlayerState>(playerStArr[0]));
		killer->winnerPl = killer;
		killer->onRep_win();
	}
	if (playerStArr.Num() == 1 && playerStArr.IsValidIndex(0) && alienKiller) {
		winPlayer(Cast<AffaPlayerState>(playerStArr[0]));
		alienKiller->winnerPl = alienKiller;
		alienKiller->onRep_win();
	}
}

void AffaGameMode::winPlayer(class AffaPlayerState* winner) {
	if (AffaGameState* state = GetGameState<AffaGameState>()) {
		state->winner = winner;
	}
}

void AffaGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AffaGameMode, playerStArr);
}

void AffaGameMode::onRep_updateArr() {

}