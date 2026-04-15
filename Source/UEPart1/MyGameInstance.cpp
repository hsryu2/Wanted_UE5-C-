// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "StudentData.h"
#include "Student.h"

UMyGameInstance::UMyGameInstance()
{
}

void UMyGameInstance::Init()
{
	Super::Init();

	// 구조체 객체 생성.
	FStudentData RawDataSource(23, TEXT("장세윤"));

	// 파일로 저장하기 위한 경로 생성.
	const FString SavePath = FPaths::Combine(
		FPlatformMisc::ProjectDir(), TEXT("Saved")
	);

	// 파일 저장 테스트를 위한 구간.
	{
		// 파일 이름
		const FString RawDataFileName(TEXT("RawData.bin"));

		// 저장 경로 + 파일 이름.
		FString RawDataAbsolutePath
			= FPaths::Combine(SavePath, RawDataFileName);
		UE_LOG(LogTemp, Log, TEXT("저장할 파일 전체 경로 : %s"), *RawDataAbsolutePath);

		// 경로 정리.
		FPaths::MakeStandardFilename(RawDataAbsolutePath);

		UE_LOG(LogTemp, Log, TEXT("변경할 파일 전체 경로 : %s"), *RawDataAbsolutePath);


		// 직렬화 사용해서 저장.
		// 파일 열기(쓰기 모드로).
		FArchive* RawFileWriteAr
			= IFileManager::Get().CreateFileWriter(
				*RawDataAbsolutePath
			);
		

		if (RawFileWriteAr)
		{
			// 파일에 기록.
			//*RawFileWriteAr << RawDataSource.Order;
			//*RawFileWriteAr << RawDataSource.Name;
			*RawFileWriteAr << RawDataSource;


			// 파일 닫기.
			RawFileWriteAr->Close();

			// 메모리 해제
			delete RawFileWriteAr;
			RawFileWriteAr = nullptr;

		}

		// 파일로부터 데이터를 읽어와서 구조체에 복원.
		// 역직렬화(Deserialization).
		FStudentData RawDataDeserialized;

		// 파일 읽기를 위한 아카이브 얻어오기.
		FArchive* RawFileReaderAr
			= IFileManager::Get().CreateFileReader(
				*RawDataAbsolutePath
			);
		if (RawFileReaderAr)
		{
			// 구조체로 값 전달.
			*RawFileReaderAr << RawDataDeserialized;

			// 파일 닫기
			RawFileReaderAr->Close();

			// 객체 메모리 해제
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;

			// 복원된 구조체 값 출력.
			UE_LOG(LogTemp, Log, TEXT("[RawData] 이름 : %s, 순번 : %d"), *RawDataDeserialized.Name, RawDataDeserialized.Order);
		}

	
	}

	// 언리얼 오브젝트 생성.
	StudentSource = NewObject<UStudent>();
	StudentSource->SetName(TEXT("유현석"));
	StudentSource->SetOrder(31);

	// 직렬화 테스트를 위한 구간 나누기.
	{
		const FString& ObjectDataFileName(
			TEXT("ObjectData.bin")
		);

		// 파일이름을 포함한 경로 생성.
		FString ObjectDataAbsolutePath
			= FPaths::Combine(SavePath, ObjectDataFileName);

		FPaths::MakeStandardFilename(ObjectDataAbsolutePath);

		// 메모리를 담을 버퍼.
		TArray<uint8> BufferArray;
		FMemoryWriter MemoryWriter(BufferArray);
		
		// MemoryWriter를 사용해서
		// 언리얼 오브젝트를 직렬화해 값을 기록.
		StudentSource->Serialize(MemoryWriter);

		// 파일에 기록.
		TUniquePtr<FArchive> FileWriteAr
			= TUniquePtr<FArchive>(
				IFileManager::Get().CreateFileWriter(
				*ObjectDataAbsolutePath)
			);

		// 파일을 잘 열었는지 확인.
		if (FileWriteAr)
		{
			// 파일에 기록 처리.
			*FileWriteAr << BufferArray;
			// 파일 닫기.
			FileWriteAr->Close();

			// 스마트포인터를 이용했기 때문에 알아서 처리 해줄것이라
			// 따로 메모리 해제를 안해도 됨.
		}

		// 언리얼 오브젝트를 복원.
		TArray<uint8> BufferArrayFromFile;
		TUniquePtr<FArchive> FileReaderAr
			= TUniquePtr<FArchive>(
				IFileManager::Get().CreateFileReader(
					*ObjectDataAbsolutePath
				)
			);

		if (FileReaderAr)
		{
			*FileReaderAr << BufferArrayFromFile;
			FileReaderAr->Close();

			// 바이트 배열에 저장된 정보를
			// 메모리 리더를 통해 객체로 복원.
			FMemoryReader MemoryReaderAr(BufferArrayFromFile);
			UStudent* StudentDest = NewObject<UStudent>();
			StudentDest->Serialize(MemoryReaderAr);


			// 출력.
			UE_LOG(LogTemp, Log, TEXT("[ObjectData] 이름 : %s, 순번 : %d"), *StudentDest->GetName(), StudentDest->GetOrder());
		}

	}

}
