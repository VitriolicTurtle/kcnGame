// Copyright Epic Games, Inc. All Rights Reserved.

#include "humanCharacter.h"
//#include "GameplayAbility.h" 
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "../Public/SpellshooterItemWeapon.h"
#include "GameFramework/SpringArmComponent.h"
#include "bullet.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "playerHUD.h"


//////////////////////////////////////////////////////////////////////////
// ASpellshooterCharacter

AHumanCharacter::AHumanCharacter()
{

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	/*
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("sFollowCamera"));
	FollowCamera->AttachTo(GetMesh(), "CamAttach");
	FollowCamera->SetRelativeRotation(FRotator(90.0f, 0.0f, 250.0f));
	FollowCamera->bUsePawnControlRotation = false; // Rotate the arm based on the controller
	*/
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;			 // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 540.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	bUseControllerRotationYaw = true;

	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

}

//////////////////////////////////////////////////////////////////////////
// Input


void AHumanCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AHumanCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AHumanCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHumanCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHumanCharacter::MoveRight);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AHumanCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AHumanCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AHumanCharacter::OnResetVR);

	// Shoot
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AHumanCharacter::shoot);
}




void AHumanCharacter::BeginPlay()
{
	Super::BeginPlay();
	maxPlayerHP = 100.0f;
	currentPlayerHP = maxPlayerHP;
	playerHPpercent = 1.0f;
}

void AHumanCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AHumanCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AHumanCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AHumanCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHumanCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHumanCharacter::MoveForward(float Value)
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

void AHumanCharacter::MoveRight(float Value)
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

float AHumanCharacter::getPlayerHP() {
	return playerHPpercent;
}


void AHumanCharacter::updatePlayerHP(float HP) {
	currentPlayerHP += HP;
	currentPlayerHP = FMath::Clamp(currentPlayerHP, 0.0f, maxPlayerHP);
	tempPlayerHP = playerHPpercent;
	playerHPpercent = currentPlayerHP / maxPlayerHP;
	UE_LOG(LogTemp, Warning, TEXT("hp should update, %f"), playerHPpercent);
}

void AHumanCharacter::playerTakeDamage(float damage) {
	updatePlayerHP(-damage);
}

void AHumanCharacter::onRep_currentPlayerHP() {
	updatePlayerHP(0);
}

void AHumanCharacter::serverOnShoot_Implementation() {
	shoot();
}

void AHumanCharacter::shoot() {
	if (!HasAuthority()) {
		serverOnShoot();
	}
	else {
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
		MuzzleOffset.Set(50.0f, 0.0f, 0.0f);

		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		// Skew the aim to be slightly upwards.
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 0.0f;

		UWorld* World = GetWorld();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		Abullet* bullet = World->SpawnActor<Abullet>(BPbullet, MuzzleLocation, MuzzleRotation, SpawnParams);

		if (bullet) {
			FVector LaunchDirection = MuzzleRotation.Vector();
			bullet->FireInDirection(LaunchDirection);
		}
	}
}

void AHumanCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHumanCharacter, killer);
	DOREPLIFETIME(AHumanCharacter, currentPlayerHP);
}

void AHumanCharacter::onRep_kill() {
	if (IsLocallyControlled()) {
		displayDeathScreen();
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);
	SetLifeSpan(05.0f);
}