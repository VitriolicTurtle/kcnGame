// Fill out your copyright notice in the Description page of Project Settings.


#include "casterCharacterBP.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AcasterCharacterBP::AcasterCharacterBP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);   //this attaches SpringArmComp to the rootComponent which here is the capsule

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	MeshComp = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	MeshComp->SetupAttachment(RootComponent);

	BaseTurnRate = 45.0f;
	BaseLookUpAtRate = 45.0f;
}

// Called when the game starts or when spawned
void AcasterCharacterBP::BeginPlay()
{
	Super::BeginPlay();
	
}

void AcasterCharacterBP::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AcasterCharacterBP::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AcasterCharacterBP::TurnAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AcasterCharacterBP::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpAtRate * GetWorld()->GetDeltaSeconds());
}



// Called to bind functionality to input
void AcasterCharacterBP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AcasterCharacterBP::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AcasterCharacterBP::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AcasterCharacterBP::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AcasterCharacterBP::MoveRight);

}

