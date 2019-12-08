class APlayer:ACharacter
{
     // An input component that we will set up to handle input from the player 
    // that is possessing this pawn.
    UPROPERTY(DefaultComponent)
    UInputComponent ScriptInputComponent;

    UPROPERTY(BlueprintReadWrite)
    bool bSprinting=false;

    UPROPERTY(BlueprintReadWrite)
    float DefaultSprintSpeed=900.f;

    UPROPERTY(BlueprintReadWrite)
    float DefaultWalkSpeed=600.f;

    UPROPERTY(BlueprintReadWrite)
    float DefaultCrouchSpeed=300.f;

    UPROPERTY(BlueprintReadWrite)
    float MaxSprintTime=10.f;

     UPROPERTY(BlueprintReadWrite)
    float CurrentSprintTime=0.f;

     UPROPERTY(BlueprintReadWrite)
     USoundBase StartSprintingSound;

     UPROPERTY(BlueprintReadWrite)
     USoundBase OutOfBreathSound;

    UPROPERTY(BlueprintReadWrite)
    FTimerHandle SprintTimerHandle;

    UFUNCTION(BlueprintCallable)
    bool CanSprint()
    {
        return !bSprinting;
    }

    UFUNCTION(BlueprintEvent)
    void PlaySound(FVector location,USoundBase sound,bool is2D){}

    UFUNCTION(BlueprintCallable)
    void StartCrouching(FKey Key=EKeys::AnyKey)
    {
        if(CanCrouch())
        {
            Crouch();
        }
    }

    UFUNCTION(BlueprintCallable)
    void StopCrouching(FKey Key=EKeys::AnyKey)
    {
        UnCrouch();      
    }

    UFUNCTION(BlueprintCallable)
    void StopSprinting(FKey Key=EKeys::AnyKey)
    {

        CharacterMovement.MaxWalkSpeed=DefaultWalkSpeed;
        bSprinting=false;
    }

     UFUNCTION(BlueprintCallable)
    void StartSprinting(FKey Key=EKeys::AnyKey)
    {
        if(bIsCrouched)
        {
            CharacterMovement.MaxWalkSpeed=DefaultSprintSpeed;
            bSprinting=true;
            if(StartSprintingSound!=nullptr)
            {
                PlaySound(GetActorLocation(),StartSprintingSound,true);
            }
        }
    }

    UFUNCTION(BlueprintCallable)
    void UpdateSprintTime()
    {
        float Time=0.01f;
        CurrentSprintTime+=Time;
        if(CurrentSprintTime>=MaxSprintTime)
        {
            StopSprinting();
            CurrentSprintTime=0.f;
            if(StartSprintingSound!=nullptr)
            {
                PlaySound(GetActorLocation(),OutOfBreathSound,true);
            }
        }
    }

    UFUNCTION(BlueprintEvent)
    void SetupCamera(){}

    UFUNCTION(BlueprintEvent)
    void UpdateResources(){}

    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        
        ScriptInputComponent.BindAction(n"CrouchInput", EInputEvent::IE_Pressed, FInputActionHandlerDynamicSignature(this, n"StartCrouching"));
        ScriptInputComponent.BindAction(n"CrouchInput", EInputEvent::IE_Released, FInputActionHandlerDynamicSignature(this, n"StopCrouching"));

        ScriptInputComponent.BindAction(n"Sprint", EInputEvent::IE_Pressed, FInputActionHandlerDynamicSignature(this, n"StartSprinting"));
        ScriptInputComponent.BindAction(n"Sprint", EInputEvent::IE_Released, FInputActionHandlerDynamicSignature(this, n"StopSprinting"));

        SprintTimerHandle=System::SetTimer(this,n"UpdateSprintTime",0.01f,true);

         SprintTimerHandle=System::SetTimer(this,n"UpdateResources",0.1f,true);

         CharacterMovement.MaxWalkSpeed = DefaultSprintSpeed;
         SetupCamera();

    }
};