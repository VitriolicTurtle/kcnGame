// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpellshooterGameMode.h"
#include "SpellshooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpellshooterGameMode::ASpellshooterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
