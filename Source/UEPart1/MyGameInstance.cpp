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
		
	UE_LOG(LogTemp, Log, TEXT("====================="));

	// TArray는 언리얼 엔진이 지원하는 동적 배열
	// STL의 std::vector와 동일한 기능 제공.
	// 언리얼 오브젝트에 특화된 동적 배열.
	TArray<UPerson*> Persons =
	{
		NewObject<UStudent>(),
		NewObject<UTeacher>(),
		NewObject<UStaff>()
	};

	// 이름 출력.
	for (const UPerson* Person : Persons)
	{
		UE_LOG(
			LogTemp,
			Log,
			TEXT("구성원 이름: %s"),
			*Person->GetName()
		);
	}

	UE_LOG(LogTemp, Log, TEXT("====================="));

	for (UPerson* Person : Persons)
	{
		// 인터페이스로 형변환.
		// 다운 캐스팅 (위험한 형변환 - RTTI 고려해야함).
		ILessonInterface* LessonInterface
			= Cast<ILessonInterface>(Person);
		if (LessonInterface)
		{
			UE_LOG(
				LogTemp,
				Log,
				TEXT("%s님은 수업에 참여할 수 있습니다."),
				*Person->GetName()
			);
			LessonInterface->DoLesson();
		}
		else
		{
			UE_LOG(
				LogTemp,
				Log,
				TEXT("%s님은 수업에 참여할 수 없습니다."),
				*Person->GetName()
			);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("====================="));

	for (const auto Person : Persons)
	{
		// 카드 가져오기.
		const UCard* OwnCard = Person->GetCard();
		// 어서트.
		ensureAlways(OwnCard);

		//UE_LOG(
		//	LogTemp,
		//	Log,
		//	TEXT("%s님이 소유한 카드 종류:  %d"),
		//	*Person->GetName(),
		//	OwnCard->GetCardType()
		//);

		// 열거형의 문자열 값 가져오기.
		const UEnum* CardEnumType = FindObject<UEnum>(
			nullptr,
			TEXT("/Script/UEPart1.ECardType")
		);

		if (CardEnumType)
		{
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue(
				(int64)OwnCard->GetCardType()
			).ToString();

			UE_LOG(
				LogTemp,
				Log,
				TEXT("%s님이 소유한 카드 종류 %s"),
				*Person->GetName(), 
				*CardMetaData
			);
		}
	}

}
