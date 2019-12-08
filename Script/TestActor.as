
class TestActor:AActor
{
    UPROPERTY(BlueprintReadWrite)
    float Value=0.f;

     UPROPERTY(DefaultComponent, RootComponent)
    UStaticMeshComponent Mesh;

    UFUNCTION(BlueprintCallable)
    void Update()
    {
      SetActorLocation(FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z+0.1));
      Log(GetActorLocation().ToString());
    }

    UFUNCTION(BlueprintOverride)
    void Tick(float DeltaSeconds)
    {
        Update();
    }

    UFUNCTION(BlueprintCallable)
    void OnInteraction(AActor interactor,UActorComponent interactedComponent)
    {

    }
}