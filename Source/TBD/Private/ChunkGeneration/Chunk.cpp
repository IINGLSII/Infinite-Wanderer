// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkGeneration/Chunk.h"

// Sets default values
AChunk::AChunk()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	floor = CreateDefaultSubobject<UStaticMeshComponent>("floor");
	size = 400;
	
}

AChunk::AChunk(float chunk_size)
{
	AChunk::AChunk();
	size = chunk_size;
}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

uint8 AChunk::get_player_offset(FVector loc, bool dir) const
{
	float offs;
	if (dir)
		offs = Super::GetActorLocation().X - loc.X;
	else
		offs = Super::GetActorLocation().Y - loc.Y;

	if (abs(offs) > size) {
		if (offs > 0)
			return 1;
		else
			return -1;
	}
	return 0;
}