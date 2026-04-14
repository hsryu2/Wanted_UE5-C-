// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"


// 이름 자동완성 해주는 함수.
FString MakeRandomName()
{
	// 3글자.
	TCHAR FirstChar[] = TEXT("김이박최");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[] = TEXT("수은원연");

	// 동적 배열을 사용할 때 가능하다면 재할당을 방지하는게 좋음.
	TArray<TCHAR> RandArray;
	RandArray.SetNum(3);
	RandArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandArray[2] = LastChar[FMath::RandRange(0, 3)];

	// 문자열로 변환이 가능하도록 반환.
	return RandArray.GetData();
}

void UMyGameInstance::Init()
{
	Super::Init();
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
	// 학생 이름 데이터 생성.
	const int32 StudentNum = 300;
	for (int32 i = 1; i <= StudentNum; i++)
	{
		StudentsData.Emplace(FStudentData(MakeRandomName(), i));
	}
	 	

	UE_LOG(LogTemp, Log, TEXT("모든 학생 데이터의 수: %d"), StudentsData.Num());

	// 학생 ㅇ데이터에서 이름 값만 추출해서 배열에 저장.
	TArray<FString> AllStudentNames;

	// 알고리즘을 활용해서 이름 값 추출.
	Algo::Transform(
		StudentsData,
		AllStudentNames,
		[](const FStudentData& Val) // 구조체가 가지고 있는 Name만 반환 요청
		{
			return Val.Name;
		}
	);

		UE_LOG(LogTemp, Log, TEXT("모든 학생 이름의 수: %d"), AllStudentNames.Num());

	//UE_LOG(LogTemp, Log, TEXT("====================="));

}
