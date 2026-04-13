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

	// 학사 정보 객체 생성.
	CourseInfo = NewObject<UCourseInfo>(this);


	// 3명의 학생 추가.
	UStudent* student1 = NewObject<UStudent>();
	student1->SetName(TEXT("학생1"));
	
	UStudent* student2 = NewObject<UStudent>();
	student2->SetName(TEXT("학생2"));
	
	UStudent* student3 = NewObject<UStudent>();
	student3->SetName(TEXT("학생3"));

	// 알림에 구독.
	CourseInfo->OnChanged.AddUObject(student1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(student2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(student3, &UStudent::GetNotification);

	// 변경된 학사 정보 발생.
	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("변경된 학사 정보"));

	UE_LOG(LogTemp, Log, TEXT("====================="));

}
