#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction_Interfece.h"
#include "LockedItem_Interface.h"
#include "RE_PasswordLockedItem.generated.h"

UCLASS()
class ROOMESCAPE_API ARE_PasswordLockedItem : public AActor, public IInteraction_Interfece, public ILockedItem_Interface
{
	GENERATED_BODY()
	
public:	
	ARE_PasswordLockedItem();

protected:
	virtual void BeginPlay() override;


protected:	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Door;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* WidgetBound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PasswordWidgetClass;

	UPROPERTY()
	class UPasswordWidget* PasswordWidget;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> FourDigitPasswordWidgetClass;

	UPROPERTY()
	class UFourDigitPasswordWidget* FourDigitPasswordWidget;


	UPROPERTY(EditAnywhere)
	int32 ItemNum = 0;

	bool bCanOpenWidget = false;

	bool bEverSolveLock = false;

protected:
	UFUNCTION()
	virtual void WidgetBoundBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void WidgetBoundEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	void Interact() override;

private:


protected:
	UPROPERTY(EditAnywhere)
	bool bFourDigitPassword;
	UPROPERTY(EditAnywhere)
	bool bSixDigitPassword;





public:
	void SolevedItem() override;
	int32 GetItemNum() override;


};
