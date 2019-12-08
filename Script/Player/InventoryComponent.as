struct FItemDefaultInfo
{
    UPROPERTY(BlueprintReadWrite)
    int MaxAmountPerStack = 64;

    UPROPERTY(BlueprintReadWrite)
    FName InGameName=n"MissingName";

    UPROPERTY(BlueprintReadWrite)
    FText Description=FText::FromName(n"MissingDescription");
}

struct FItemInfo
{
    UPROPERTY(BlueprintReadWrite)
    FName Name = n"none";

    UPROPERTY(BlueprintReadWrite)
    int Amount = 0;

    FItemInfo(FName name,int amount)
    {
        Name=name;
        Amount=amount;
    }
}

class UInventoryComponent:UActorComponent
{
    UPROPERTY(BlueprintReadWrite)
    TArray<FItemInfo> Items;

    UPROPERTY(BlueprintReadWrite)
    UDataTable ItemDefaultInfoTabel;

    UFUNCTION(BlueprintPure)
    TArray<FItemInfo> GetAllItemsByName(FName name)
    {
        if(Items.Num()>0)
        {
            TArray<FItemInfo> result;
            for(int i=0;i<Items.Num();i++)
            {
                if(Items[i].Name==name)
                {
                    result.Add(Items[i]);
                }
            }
            return result;
        }
        return TArray<FItemInfo>();
    }

    UFUNCTION(BlueprintPure)
    int GetAmountOfItemsWithName(FName name)
    {
        if(Items.Num() > 0)
        {
            int result = 0;
            for(int i = 0;i < Items.Num(); i++)
            {
                if(Items[i].Name == name)
                {
                    result+=Items[i].Amount;
                }
            }
            return result;
        }
        return 0;
    }

    UFUNCTION(BlueprintCallable)
    bool AddItem(FItemInfo info)
    {
       
        if(ItemDefaultInfoTabel!=nullptr)
        {
           if(DataTable::DoesDataTableRowExist(ItemDefaultInfoTabel,info.Name))
           {
              //placeholder
                int stackAmount = 64;
              
               if(info.Amount > stackAmount)
               {
                 TArray<FItemInfo> itemsToAdd;
                 int value=info.Amount;
                 while((value-stackAmount) > 0)
                 {
                    itemsToAdd.Add(FItemInfo(info.Name,stackAmount));
                    value-=stackAmount;
                 }
                 if(value>0)
                 {
                     itemsToAdd.Add(FItemInfo(info.Name,value));
                 }
                
                 Items.Append(itemsToAdd);
               }
               else
               {
                  
                   Items.Add(info);
               }
           }
           else
           {
               int stackAmount = 64;
              
               if(info.Amount > stackAmount)
               {
                 TArray<FItemInfo> itemsToAdd;
                 int value=info.Amount;
                 while((value-stackAmount) > 0)
                 {
                    itemsToAdd.Add(FItemInfo(info.Name,stackAmount));
                    value-=stackAmount;
                 }
                 if(value>0)
                 {
                     itemsToAdd.Add(FItemInfo(info.Name,value));
                 }
                 PrintError("Items.Append(itemsToAdd)");
                 Items.Append(itemsToAdd);
               }
               else
               {
                   PrintError("Items.Add(info)");
                   Items.Add(info);
               }
           }
        }
        else
        {
               int stackAmount = 64;
              
               if(info.Amount > stackAmount)
               {
                 TArray<FItemInfo> itemsToAdd;
                 int value=info.Amount;
                 while((value-stackAmount) > 0)
                 {
                    itemsToAdd.Add(FItemInfo(info.Name,stackAmount));
                    value-=stackAmount;
                 }
                 if(value>0)
                 {
                     itemsToAdd.Add(FItemInfo(info.Name,value));
                 }
                  
                 Items.Append(itemsToAdd);
               }
               else
               {
                   
                   Items.Add(info);
               }
               return true;
           }

        return true;
    }

     UFUNCTION(BlueprintCallable)
    bool RemoveItem(FItemInfo info)
    {
        return true;
    }
}