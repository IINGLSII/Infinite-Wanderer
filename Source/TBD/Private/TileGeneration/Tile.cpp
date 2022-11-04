// Fill out your copyright notice in the Description page of Project Settings.


#include "TileGeneration/Tile.h"

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	floor = CreateDefaultSubobject<UStaticMeshComponent>("floor");
	ATile::SetRootComponent(floor);
	
}


// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	floor->SetRelativeScale3D(FVector(tile_data.tile_size / 400));
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// returns the chunk offset of a given location, bool indicates axis (1 = X, 0 = Y)
int8 ATile::get_player_offset(FVector loc, bool dir) const
{
	float offs;
	if (dir)
		offs = loc.X - tile_data.tile_size / 2 - Super::GetActorLocation().X;
	else
		offs = loc.Y - tile_data.tile_size / 2 - Super::GetActorLocation().Y;

	if (abs(offs) > tile_data.tile_size / 2) {
		if (offs > 0)
			return 1;
		else
			return -1;
	}
	return 0;
}

void ATile::load_tile_data(FTileData new_tile_data)
{
	tile_data = new_tile_data;
}
