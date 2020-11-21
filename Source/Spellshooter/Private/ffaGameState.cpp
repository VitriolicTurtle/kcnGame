// Fill out your copyright notice in the Description page of Project Settings.


#include "ffaGameState.h"
#include "Net/UnrealNetwork.h"

void AffaGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AffaGameState, winner);
}

void AffaGameState::onRep_winPlayer() {
	onWinPlayerFound.Broadcast();
}