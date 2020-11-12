// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellshooterPlayerController.h"
#include "../Public/humanCharacter.h"
#include "../Public/StoreComponent.h"


ASpellshooterPlayerController::ASpellshooterPlayerController() {
	playerStore = CreateDefaultSubobject<UStoreComponent>(TEXT("playerStore"));
}



AHumanCharacter* ASpellshooterPlayerController::GetControlledSpellshooterCharacter() const {
	return Cast<AHumanCharacter>(GetPawn());
}

