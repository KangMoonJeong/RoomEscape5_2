#include "AddCombine.h"
#include "Components/Button.h"
#include "Kismet/GamePlayStatics.h"
#include "Inspection_Interface.h"


bool UAddCombine::Initialize()
{
	if (!Super::Initialize())
		return false;

	Insepect_Button->OnClicked.AddDynamic(this, &UAddCombine::OnClicked_Insepect_Button);
	Combine_Button->OnClicked.AddDynamic(this, &UAddCombine::OnClicked_Combine_Button);
	return true;

}

void UAddCombine::SetItemNum(int32 Set)
{
	ItemNum = Set;
}

void UAddCombine::OnClicked_Insepect_Button()
{
	//TArray<AActor*> InterfaceActor;
	//UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInspection_Interface::StaticClass(), InterfaceActor);
	//for (AActor* Actor : InterfaceActor)
	//{
	//	IInspection_Interface* Inspection_Interface = Cast<IInspection_Interface>(Actor);
	//	Inspection_Interface->SetChildActorClassFromPath();
	//}
}

void UAddCombine::OnClicked_Combine_Button()
{
	UE_LOG(LogTemp, Warning, TEXT("UAddCombine::OnClicked_Combine_Button()"))
}


