// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpellshooterGameMode.h"
#include "humanCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpellshooterGameMode::ASpellshooterGameMode()
{
	UWorld* World = GetWorld();
	//if (!ensure(World != nullptr)) return;

	//for (FConstPlayerControllerIterator PCIterator = World->GetPlayerControllerIterator(); PCIterator; PCIterator++) {

	//	APlayerController* playerController = PCIterator->Get();
	//	AHumanCharacter* PlayerPawn = Cast<AHumanCharacter>(playerController->GetPawn());



	//}

	DefaultPawnClass = AHumanCharacter::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Human/Blueprints/humanCharacterBP"));
	if (PlayerPawnBPClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
