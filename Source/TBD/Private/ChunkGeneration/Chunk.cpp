// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkGeneration/Chunk.h"

// Sets default values
AChunk::AChunk()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	floor = CreateDefaultSubobject<UStaticMeshComponent>("floor");
	
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

int8 AChunk::get_player_offset(FVector loc, bool dir) const
{
	float offs;
	if (dir)
		offs = loc.X - size / 2 - Super::GetActorLocation().X;
	else
		offs = loc.Y - size / 2 - Super::GetActorLocation().Y;

	if (abs(offs) > size/2) {
		if (offs > 0)
			return 1;
		else
			return -1;
	}
	return 0;
}

void AChunk::set_size(float x)
{
	if (x > 0)
		AChunk::size = x;
}
