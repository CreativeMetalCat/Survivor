import Player.InventoryComponent;
import Player.Player;

class ADroppedItem:AActor
{
    UPROPERTY(BlueprintReadWrite)
    TArray<FItemInfo> info;

    UPROPERTY(DefaultComponent, RootComponent)
    UStaticMeshComponent Mesh;
    //default Mesh.StaticMesh = Asset("/Game/models/hl2/box/box");
}