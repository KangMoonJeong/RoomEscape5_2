#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoomEscape\Inspection_Interface.h"
#include "FP_FirstPersonCharacter.generated.h"

class UInputComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class USoundBase;
class UAnimMontage;

UCLASS(config=Game)
class AFP_FirstPersonCharacter : public ACharacter, public IInspection_Interface
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	AFP_FirstPersonCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	

protected:
	void MoveForward(float Val);
	void MoveRight(float Val);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);


	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
public:
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }





protected:
	UFUNCTION()
	virtual void BeginPlay() override;





private:
	AActor* TracedItem;
	class ARE_PlayerController* PlayerController;
	int32 PressedItemSlotLocation = -1;
	bool bCurrentHiddenItemInsepctionWidget = true;





	/* Line Trace */
protected:
	void StartTrace();
	void BindInteract();





	/* Whole Widget */
public:
	void ToggleWholeWidget();





	/* Item Interaction Widget */
	void StartInteractionSetting()  override;
	void ClearInteractionSetting() override;






	/* Press Item Slot */
protected:
	void PressZero();
	void PressOne();
	void PressTwo();
	void PressThree();
	void PressFour();
	void PressFive();
	void PressSix();
	void PressSeven();
	void PressEight();
	void PressNine();


public:
	int32 GetPressedItemSlotItemNum();

	int32 GetPressedItemSlotLocation();




	/***/
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> RE_WholeWidgetClass;

protected:
	void QuitGame();


	void ToggleTemp();


public:
	class URE_WholeWidget* RE_WholeWidget;
	void RelocationGridPanel();


	void SetIntemInspectionPath(int32 PathNum);
};

