// Fill out your copyright notice in the Description page of Project Settings.


#include "Tests/TileGeneratorTest.h"


void ATileGeneratorTest::StartTest(){
	
	minimum_distance_TEST();
	unit_TEST();
	AFunctionalTest::FinishTest(EFunctionalTestResult::Succeeded, TEXT("TileGenerator works as expected"));
}

void ATileGeneratorTest::minimum_distance_TEST() {
	AFunctionalTest::LogMessage(TEXT("minimum distance test:"));
	float minimum_tile_size = generator->get_tile_size();
	generator->populate_grid(true);
	int array_length = generator->get_dim();
	array_length *= array_length;
	for (int32 idx = 0; idx < array_length; ++idx)
	{
		ATile* tile_1 = generator->get_tile_by_index(idx);
		for (int32 comparator_idx = idx + 1; comparator_idx < array_length; ++comparator_idx) {
			ATile* tile_2 = generator->get_tile_by_index(comparator_idx);

			float distance = FVector::DistXY(tile_1->GetActorLocation(), tile_2->GetActorLocation());
			if (distance < minimum_tile_size)
				AFunctionalTest::FinishTest(EFunctionalTestResult::Failed, FString::Printf(TEXT("minimum distance test failed (got %f, expected value > %f )"), distance, minimum_tile_size));
		}

	}

	AFunctionalTest::LogMessage(TEXT("minimum distance test succeeded"));
	return;
}

void ATileGeneratorTest::unit_TEST() {
	AFunctionalTest::LogMessage(TEXT("UNIT TESTS:"));
	verify(generator->get_dim() == 3);

	AFunctionalTest::LogMessage(TEXT("index to offset conversion:"));
	if (generator->convert_idx_to_offset(4) != FOffset(0, 0))
		AFunctionalTest::FinishTest(EFunctionalTestResult::Failed, FString::Printf(TEXT("idx to offset conversion failed for dim = 3, index = 4 (expected (0,0))")));
	if (generator->convert_idx_to_offset(0) != FOffset(1, -1))
		AFunctionalTest::FinishTest(EFunctionalTestResult::Failed, FString::Printf(TEXT("idx to offset conversion failed for dim = 3, index = 0 (expected (1,-1))")));
	if (generator->convert_idx_to_offset(8) != FOffset(-1, 1))
		AFunctionalTest::FinishTest(EFunctionalTestResult::Failed, FString::Printf(TEXT("idx to offset conversion failed for dim = 3, index = 8 (expected (-1,1))")));

	AFunctionalTest::LogMessage(TEXT("offset to index conversion:"));
	if (generator->convert_offset_to_idx(FOffset(0, 0)) != 4)
		AFunctionalTest::FinishTest(EFunctionalTestResult::Failed, FString::Printf(TEXT("offset to index conversion failed for dim = 3, offset = (0,0) (expected 4)")));
	if (generator->convert_offset_to_idx(FOffset(1, -1)) != 0)
		AFunctionalTest::FinishTest(EFunctionalTestResult::Failed, FString::Printf(TEXT("offset to index conversion failed for dim = 3, offset = (1,-1) (expected 0)")));
	if (generator->convert_offset_to_idx(FOffset(-1, 1)) != 8)
		AFunctionalTest::FinishTest(EFunctionalTestResult::Failed, FString::Printf(TEXT("offset to index conversion failed for dim = 3, offset = (-1,1) (expected 8)")));

	AFunctionalTest::LogMessage(TEXT("offset validation:"));
	if (generator->validate_offset(FOffset(0,0)) == false)
		AFunctionalTest::FinishTest(EFunctionalTestResult::Failed, FString::Printf(TEXT("offset validation failed for offset = (0,0) (expected True)")));
	if (generator->validate_offset(FOffset(2, 2)) == true)
		AFunctionalTest::FinishTest(EFunctionalTestResult::Failed, FString::Printf(TEXT("offset validation failed for offset = (2,2) (expected False)")));

	return;

}
