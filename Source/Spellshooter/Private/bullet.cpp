// Fill out your copyright notice in the Description page of Project Settings.


#include "bullet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "humanCharacter.h"
#include "casterCharacterBP.h"
#include "ffaGameMode.h"
#include "playerHUD.h"

// Sets default values
Abullet::Abullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("bulletMesh");
	SetRootComponent(bulletMesh);

	bulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>("bulletMovement");
	bulletMovement->InitialSpeed = 50000.f;
	bulletMovement->MaxSpeed = 50000.f;
	bulletMovement->ProjectileGravityScale = 0.0f;
	bulletMovement->bRotationFollowsVelocity = true;

	SetReplicates(true);
	SetReplicateMovement(true);
	damageValue = 25.0f;

}

// Called when the game starts or when spawned
void Abullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Abullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Abullet::FireInDirection(const FVector& ShootDirection) {
	bulletMovement->Velocity = ShootDirection * bulletMovement->InitialSpeed;
}

void Abullet::onHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit) {
	if (HasAuthority()) {
			if (AHumanCharacter* playerHit = Cast<AHumanCharacter>(otherActor)) {
				//playerHit->playerTakeDamage(25.0f);
				if (playerHit != Cast<AHumanCharacter>(GetOwner())) playerHit->playerTakeDamage(damageValue);
				if (playerHit->currentPlayerHP <= 0.0f) {
					if (AffaGameMode* mode = Cast<AffaGameMode>(GetWorld()->GetAuthGameMode())) {
						UE_LOG(LogTemp, Warning, TEXT("you are dead1"));
						if (GetOwner()->IsA(AHumanCharacter::StaticClass())) {
							UE_LOG(LogTemp, Warning, TEXT("prob in 1"));
							AHumanCharacter* killer = Cast<AHumanCharacter>(GetOwner());
							mode->playerKilled(playerHit, killer, nullptr, nullptr);
							playerHit->killerHuman = killer;
							playerHit->onRep_kill();
						}
						else if (GetOwner()->IsA(AcasterCharacterBP::StaticClass())) {
							UE_LOG(LogTemp, Warning, TEXT("prob in 2"));
							AcasterCharacterBP* killer = Cast<AcasterCharacterBP>(GetOwner());
							mode->playerKilled(playerHit, nullptr, nullptr, killer);
							playerHit->killerHuman = killer;//this-------------------------------------------------
							playerHit->onRep_kill();
						}
					}
				}
			}
			else if (AcasterCharacterBP* playerHitAli = Cast<AcasterCharacterBP>(otherActor)) {
				if (playerHitAli != Cast<AcasterCharacterBP>(GetOwner())) playerHitAli->playerTakeDamage(damageValue);
				if (playerHitAli->currentPlayerHP <= 0.0f) {
					if (AffaGameMode* mode = Cast<AffaGameMode>(GetWorld()->GetAuthGameMode())) {
						UE_LOG(LogTemp, Warning, TEXT("you are dead2"));
						if (GetOwner()->IsA(AHumanCharacter::StaticClass())) {
							UE_LOG(LogTemp, Warning, TEXT("prob in 3"));
							AHumanCharacter* killer = Cast<AHumanCharacter>(GetOwner());
							mode->playerKilled(nullptr, killer, playerHitAli, nullptr);							
							playerHitAli->killerAlien = killer;//this----------------------------------------------
							playerHitAli->onRep_kill();
						}
						else if (GetOwner()->IsA(AcasterCharacterBP::StaticClass())) {
							UE_LOG(LogTemp, Warning, TEXT("prob in 4"));
							AcasterCharacterBP* killer = Cast<AcasterCharacterBP>(GetOwner());
							mode->playerKilled(nullptr, nullptr, playerHitAli, killer);
							playerHitAli->killerAlien = killer;
							playerHitAli->onRep_kill();
						}
					}
				}
			}
	}
}