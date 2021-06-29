// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnimSeqReader.generated.h"

UCLASS()
class ANIMSEQUENCEREADER_API AAnimSeqReader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimSeqReader();

	UFUNCTION(BlueprintCallable)
		void ReadAnimSequenceRoot(UAnimSequence * sequence);
	UFUNCTION(BlueprintCallable)
		void ReadAnimSequenceBone(UAnimSequence* sequence, int BoneIdx);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		TArray<FTransform> RootTransform;

	UPROPERTY(VisibleAnywhere)
		TArray<FTransform> BoneTransform;

};
