// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "casterCharacterBP.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent; //might be obsolete


UCLASS()
class SPELLSHOOTER_API AcasterCharacterBP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AcasterCharacterBP();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")   //might be obsolete
		USkeletalMeshComponent* MeshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Value);
	void LookUpAtRate(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseLookUpAtRate;
		

public:	
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
