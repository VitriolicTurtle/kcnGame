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
	bulletMovement->InitialSpeed = 5000.f;
	bulletMovement->MaxSpeed = 5000.f;
	bulletMovement->ProjectileGravityScale = 0.0f;
	bulletMovement->bRotationFollowsVelocity = true;

	SetReplicates(true);
	SetReplicateMovement(true);

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
			if(playerHit != Cast<AHumanCharacter>(GetOwner())) playerHit->playerTakeDamage(25.0f);
			if (playerHit->currentPlayerHP <= 0.0f) {
				if (AffaGameMode* mode = Cast<AffaGameMode>(GetWorld()->GetAuthGameMode())) {
					UE_LOG(LogTemp, Warning, TEXT("you are dead"));
					AHumanCharacter* killer = Cast<AHumanCharacter>(GetOwner());
					mode->playerKilled(playerHit, killer, nullptr, nullptr);
					playerHit->killer = killer;
					playerHit->onRep_kill();
				}
			}
		}
		/*else if (AcasterCharacterBP* playerHit2 = Cast<AcasterCharacterBP>(otherActor)) {
			playerHit2->playerTakeDamage(25.0f);
			if (playerHit2->currentPlayerHP <= 0.0f) {
				if (AffaGameMode* mode2 = Cast<AffaGameMode>(GetWorld()->GetAuthGameMode())) {
					UE_LOG(LogTemp, Warning, TEXT("you are dead"));
					if (AcasterCharacterBP* killer2 = Cast<AcasterCharacterBP>(GetOwner())) {
						mode2->playerKilled(nullptr, nullptr, playerHit2, killer2);
						playerHit2->killer = killer2;
						playerHit2->onRep_kill();
					}
				}
			}
		}*/
	}
}