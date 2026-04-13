// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"

UMyGameInstance::UMyGameInstance()
{
	// 기본 값은 CDO라는 특별한 템플릿 객체에 저장됨.
	SchoolName = TEXT("기본학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	//TArray 사용.
	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	for (int32 i = 1; i <= ArrayNum; i++)
	{
		Int32Array.Add(i);
	}

	// 짝수 제거.
	Int32Array.RemoveAll(
		// [] - 캡처 (외부 내용을 람다 안에서 사용할 때 활용).
		// () - 파라미터.
		// -> - 반환형 (보통 알아서 해주는데 명시적으로 보여줄 때 사용).
		// { } - 본문.
		[](int32 Val) -> bool
		{
			return Val % 2 == 0;
		}
	);

	// 짝수 삽입.
	Int32Array += {2, 4, 6, 8, 10};

	// 비교 ( 동등 비교 ).
	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = { 1,3,5,7,9,2,4,6,8,10 };
	Int32ArrayCompare.AddUninitialized(ArrayNum);

	// C스타일 배열을 TArray에 메모리 복사.
	FMemory::Memcpy(
		Int32ArrayCompare.GetData(),
		CArray,
		sizeof(int32) * ArrayNum
	);

	// 어서트 (크래시를 발생시키지 않고, 출력 로그 창에 오류 메시지 출력).
	ensureAlways(Int32Array == Int32ArrayCompare);
	
	// 합계.
	int32 Sum = 0;
	for (const int32& Int32Num : Int32Array)
	{
		Sum += Int32Num;
	}

	// 알고리즘 활용 (합계 구하기).
	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);
	ensureAlways(Sum == SumByAlgo);

	UE_LOG(LogTemp, Log, TEXT("Sum = %d | SumByAlgo = %d | Sum == SumbyAlgo = %s"),
		Sum, SumByAlgo, (Sum == SumByAlgo ? TEXT("True") : TEXT("False")));


	//UE_LOG(LogTemp, Log, TEXT("====================="));

}
