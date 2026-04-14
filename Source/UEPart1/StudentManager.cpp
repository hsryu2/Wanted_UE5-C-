#include "StudentManager.h"
#include "Student.h"


void FStudentManager::AddReferencedObjects(FReferenceCollector& Collector)
{
	// 유효성 검증
	//IsValid()
	if (SafeStudent->IsValidLowLevel())
	{
		Collector.AddReferencedObject(SafeStudent);
	}
}