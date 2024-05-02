// Copyright Epic Games, Inc. All Rights Reserved.

#include "AreYouLostGameMode.h"
#include "AreYouLostCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAreYouLostGameMode::AAreYouLostGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
