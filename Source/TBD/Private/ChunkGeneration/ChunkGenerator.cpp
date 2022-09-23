// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkGeneration/ChunkGenerator.h"

AChunkGenerator::AChunkGenerator()
{
	adjacency_grid.Init(nullptr, 9);
	
}

void AChunkGenerator::BeginPlay() {
	AChunkGenerator::generateChunks({4,0,1,2,3,5,6,7,8 });
}

void AChunkGenerator::cullChunks(TArray<uint8> chunks) {
	for (int i = 0; i < chunks.Num(); i++) {
		if (adjacency_grid[chunks[i]] == nullptr) {
			continue;
		}
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Yellow, FString::Printf(TEXT("DELETING %i"), chunks[i]));
		adjacency_grid[i]->Destroy();
		adjacency_grid[i] = nullptr;
	}
}

void AChunkGenerator::remapChunks(TArray<uint8> old_chunks, TArray<uint8> new_chunks) {
	check(old_chunks.Num() == new_chunks.Num());

	for (int i = 0; i < old_chunks.Num(); i++) {
		adjacency_grid[new_chunks[i]] = adjacency_grid[old_chunks[i]];
	}
}

void AChunkGenerator::generateChunks(TArray<uint8> chunks) {
	for (int i = 0; i < chunks.Num(); i++) {

		FTransform chunk_transform = (adjacency_grid[4] == nullptr) ? AChunkGenerator::GetActorTransform() : adjacency_grid[4]->GetActorTransform();
		float xoff = size  * (chunks[i] % 3 - 1);
		float yoff = -size * (chunks[i] / 3 - 1);

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Yellow, FString::Printf(TEXT("GENERATING %i"), chunks[i]));
		chunk_transform.SetLocation(chunk_transform.GetLocation() + FVector(xoff,yoff, 0));

		FActorSpawnParameters spawn_params;

		adjacency_grid[chunks[i]] = GetWorld()->SpawnActor<AChunk>(ChunkBP, chunk_transform, spawn_params);
	}
}

void AChunkGenerator::updateGrid(FVector location) {
	uint8 loc = adjacency_grid[4]->check_player_adjacency(location);

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Yellow, FString::Printf(TEXT("AT %i"), loc));

	if (loc != 4){
		TArray<uint8> c_chunks, r_chunks_old, r_chunks_new, g_chunks;

		AChunk* focus = adjacency_grid[4];
		switch(loc){
			case 0:
				c_chunks = { 2,5,6,7,8 };
				r_chunks_old = {1,3,4};
				r_chunks_new = {5,7,8};
				g_chunks = { 0,1,2,3,6 };
				break;
			case 1:
				c_chunks = { 6,7,8 };
				r_chunks_old = { 3,4,5,0,2 };
				r_chunks_new = { 6,7,8,3,5 };
				g_chunks = { 0,1,2 };
				break;
			case 2:
				c_chunks = { 0,3,6,7,8 };
				r_chunks_old = { 1,4,5 };
				r_chunks_new = { 3,6,7 };
				g_chunks = { 0,1,2,5,8 };
				break;
			case 3:
				c_chunks = { 2,5,8 };
				r_chunks_old = { 1,4,7,0,6 };
				r_chunks_new = { 2,5,8,1,7 };
				g_chunks = { 0,3,6 };
				break;
			case 5:
				c_chunks = { 0,3,6 };
				r_chunks_old = { 1,7,2,5,8 };
				r_chunks_new = { 0,3,6,1,7 };
				g_chunks = { 2,5,8 };
				break;
			case 6:
				c_chunks = { 0,1,2,5,8 };
				r_chunks_old = { 3,4,7 };
				r_chunks_new = { 1,2,5 };
				g_chunks = { 0,3,6,7,8 };
				break;
			case 7:
				c_chunks = { 0,1,2 };
				r_chunks_old = { 3,4,5,6,8 };
				r_chunks_new = { 0,1,2,3,5 };
				g_chunks = { 6,7,8 };
				break;
			case 8:
				c_chunks = { 0,1,2,3,6 };
				r_chunks_old = { 5,7,8 };
				r_chunks_new = { 1,3,4 };
				g_chunks = { 2,5,6,7,8 };
				break;
		}
		
		/*
		AChunkGenerator::cullChunks(c_chunks);
		AChunkGenerator::remapChunks(r_chunks_old, r_chunks_new);
		adjacency_grid[4] = adjacency_grid[loc];
		AChunkGenerator::generateChunks(g_chunks);*/
	}

}