// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimSeqReader.h"

// Sets default values
AAnimSeqReader::AAnimSeqReader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnimSeqReader::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnimSeqReader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnimSeqReader::ReadAnimSequenceRoot(UAnimSequence * sequence)
{
	RootTransform.Empty();
	float DeltaTime = sequence->GetPlayLength() / sequence->GetNumberOfFrames();
	for (int i = 0; i < sequence->GetNumberOfFrames(); i++) 
	{
		FTransform out;
		sequence->GetBoneTransform(out, 1, i * DeltaTime, true);
		RootTransform.Add(out);
	}
}

void AAnimSeqReader::ReadAnimSequenceBone(UAnimSequence* sequence, int BoneIdx) 
{
	BoneTransform.Empty();

}

