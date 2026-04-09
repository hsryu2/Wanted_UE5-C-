// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Teacher.h"
#include "Student.h"

UMyGameInstance::UMyGameInstance()
{

	// 기본 값은 CDO라는 툭별한 템플릿 객체에 저장됨.
	SchoolName = TEXT("기본학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	UClass* ClassRuntime = GetClass();
	UClass* ClassCompile = UMyGameInstance::StaticClass();

	// 어서트. -> 얘 무조건 통과 시켜야하는 애만 써야함. 통과 못하면 에디터에 크래시를 던짐.
	//check(ClassRuntime == ClassCompile);
	// 출력 로그 창에 오류 표시.
	//ensure(ClassRuntime == ClassCompile);

	// 클래스 이름 출력.
	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 : %s %s"), *ClassRuntime->GetName(), *ClassCompile->GetName());

	SchoolName = TEXT("청강문화산업대학교");
	
	// 실행중 즉 런타임에 바뀐것이라 청강문화산업대학교가 나옴.
	UE_LOG(LogTemp, Log, TEXT("학교 이름: %s"), *SchoolName);

	// CDO에 저장되어있음. CDO는 변수 기본값이며 변화하지않음. -> 기본학교 출력
	UE_LOG(LogTemp, Log, TEXT("학교 이름: %s"), *GetClass()->GetDefaultObject<UMyGameInstance>()-> SchoolName);

	UE_LOG(LogTemp, Log, TEXT("========================"));

	// 학생 / 선생님 객체 생성.
	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();

	// 학생 클래스의 Getter/Setter 사용.
	Student->SetName(TEXT("학생1"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름: %s"), *Student->GetName());

	// 언리얼의 리플렉션을 활용해 프로퍼티 정ㅇ보 설정 및 가져오기.
	// FindPropertyByName -> 검색기능을 쓰는 것이고, 반환이 포인터이므로 리턴값은 null
	//UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	FProperty* NameProp = Teacher->GetClass()->FindPropertyByName(TEXT("Name"));
	if (NameProp)
	{
		// 리플렉션을 활용해 현재 프로퍼티에 저장된 값 가져오기.
		FString CurrentTeacherName;
		NameProp->GetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름: %s"), *CurrentTeacherName);

		// 리플렉션을 활용해 프로퍼티에 새로운 값 저장.
		FString NewTeacherName(TEXT("로니"));
		NameProp->SetValue_InContainer(Teacher, &NewTeacherName);

		UE_LOG(LogTemp, Log, TEXT("새로운 선생님 이름: %s"), *Teacher->GetName());

	}


	// 함수 호출 (리플렉션 활용).
	UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFunc)
	{
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}



} 