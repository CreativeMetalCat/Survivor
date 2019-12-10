struct FItemDefaultInfo
{
    UPROPERTY(BlueprintReadWrite)
    int MaxAmountPerStack = 64;

    UPROPERTY(BlueprintReadWrite)
    FName InGameName=n"MissingName";

    UPROPERTY(BlueprintReadWrite)
    UTexture2D Icon;

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

//DO NOT USE THIS CLASS BUT USE IT'S CHILDREN
//BECAUSE SOME FUNCTIONS HAVE TO BE OVERRIDEN
class UInventoryComponent:UActorComponent
{
    UPROPERTY(BlueprintReadWrite)
    TArray<FItemInfo> Items;

    UPROPERTY(BlueprintReadWrite)
    UDataTable ItemDefaultInfoTable;

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

    //did this way because angel script doesn't support static classes yet
    //THIS FUNCTION MUST BE OVERRIDEN IN EVERY CHILD CLASS
    UFUNCTION(BlueprintEvent)
    FItemDefaultInfo GetDataTableRow(FName name)
    {
        PrintError("MISSING FUNCTION OVERRIDE! Name:FItemDefaultInfo GetDataTableRowName() Class:UInventoryComponent");
        return FItemDefaultInfo();
    }

     UFUNCTION(BlueprintEvent)
     void OwnerNotify_ItemAdded(FItemInfo info){}

     UFUNCTION(BlueprintEvent)
     void OwnerNotify_ItemRemoved(FItemInfo info){}

     UFUNCTION(BlueprintEvent)
     void OwnerNotify_ItemDropped(FItemInfo info){}

    UFUNCTION(BlueprintCallable)
    bool AddItem(FItemInfo info)
    {
        if(info.Amount>0)
        {
        if(ItemDefaultInfoTable!=nullptr)
        {
           if(DataTable::DoesDataTableRowExist(ItemDefaultInfoTable,info.Name))
           {

               int stackAmount = GetDataTableRow(info.Name).MaxAmountPerStack;
              int valueToAdd = info.Amount;
               for(int i=0;i<Items.Num();i++)
               {
                   if(Items[i].Name==info.Name&&Items[i].Amount<stackAmount)
                   {
                       
                       if((stackAmount-Items[i].Amount)<valueToAdd)
                       {
                        valueToAdd-=(stackAmount-Items[i].Amount);
                       
                         Items[i].Amount+= (stackAmount-Items[i].Amount); 
                          
                       }
                       else if((stackAmount-Items[i].Amount)==valueToAdd)
                       {
                         
                        Items[i].Amount += (stackAmount-Items[i].Amount); 
                         valueToAdd = 0;
                         OwnerNotify_ItemAdded(info);
                         return true;
                       }
                       else
                       {
                             
                            Items[i].Amount+= valueToAdd;
                            valueToAdd=0;
                            OwnerNotify_ItemAdded(info);
                            return true;
                       }
                   }
               }
               
               if(info.Amount > stackAmount)
               {
                 TArray<FItemInfo> itemsToAdd;
                 int value = valueToAdd;
                 while((value-stackAmount) > 0)
                 {
                    itemsToAdd.Add(FItemInfo(info.Name,stackAmount));
                    value-=stackAmount;
                 }
                 if(value>0)
                 {
                     
                     itemsToAdd.Add(FItemInfo(info.Name,value));
                 }
                
                for(int j=0;j<itemsToAdd.Num();j++){OwnerNotify_ItemAdded(itemsToAdd[j]);}
                 Items.Append(itemsToAdd);
               }
               else
               {
                   
                  OwnerNotify_ItemAdded(info);
                   Items.Add(FItemInfo(info.Name,valueToAdd));
               }
           }
           else
           {
               int stackAmount = 64;
              int valueToAdd = info.Amount;
               for(int i=0;i<Items.Num();i++)
               {
                   if(Items[i].Name==info.Name&&Items[i].Amount<stackAmount)
                   {
                       if((stackAmount-Items[i].Amount)<valueToAdd)
                       {
                          valueToAdd-=(stackAmount-Items[i].Amount);
                         Items[i].Amount+= (stackAmount-Items[i].Amount); 
                       }
                       else if((stackAmount-Items[i].Amount)==valueToAdd)
                       {
                        Items[i].Amount += (stackAmount-Items[i].Amount); 
                         valueToAdd = 0;
                         OwnerNotify_ItemAdded(info);
                         return true;
                       }
                       else
                       {
                            Items[i].Amount+= valueToAdd;
                            valueToAdd=0;
                            OwnerNotify_ItemAdded(info);
                            return true;
                       }
                   }
               }
               if(info.Amount > stackAmount)
               {
                 TArray<FItemInfo> itemsToAdd;
                 int value=valueToAdd;
                 while((value-stackAmount) > 0)
                 {
                    itemsToAdd.Add(FItemInfo(info.Name,stackAmount));
                    value-=stackAmount;
                 }
                 if(value>0)
                 {
                     
                     itemsToAdd.Add(FItemInfo(info.Name,value));
                 }
                 
                  for(int j=0;j<itemsToAdd.Num();j++){OwnerNotify_ItemAdded(itemsToAdd[j]);}
                 Items.Append(itemsToAdd);
               }
               else
               {
                   OwnerNotify_ItemAdded(info);
                   Items.Add(FItemInfo(info.Name,valueToAdd));
               }
           }
        }
        else
        {
               int stackAmount = 64;
               int valueToAdd = info.Amount;
               for(int i=0;i<Items.Num();i++)
               {
                   if(Items[i].Name==info.Name&&Items[i].Amount<stackAmount)
                   {
                       if((stackAmount-Items[i].Amount)<valueToAdd)
                       {
                          valueToAdd-=(stackAmount-Items[i].Amount);
                         Items[i].Amount+= (stackAmount-Items[i].Amount); 
                       }
                       else if((stackAmount-Items[i].Amount)==valueToAdd)
                       {
                        Items[i].Amount += (stackAmount-Items[i].Amount); 
                         valueToAdd = 0;
                         OwnerNotify_ItemAdded(info);
                         return true;
                       }
                       else
                       {
                            Items[i].Amount+= valueToAdd;
                            valueToAdd=0;
                            OwnerNotify_ItemAdded(info);
                            return true;
                       }
                   }
               }
               if(info.Amount > stackAmount)
               {
                 TArray<FItemInfo> itemsToAdd;
                 int value=valueToAdd;
                 while((value-stackAmount) > 0)
                 {
                    itemsToAdd.Add(FItemInfo(info.Name,stackAmount));
                    value-=stackAmount;
                 }
                 if(value>0)
                 {
                     itemsToAdd.Add(FItemInfo(info.Name,value));
                 }
                  for(int j=0;j<itemsToAdd.Num();j++){OwnerNotify_ItemAdded(itemsToAdd[j]);}
                 Items.Append(itemsToAdd);
               }
               else
               {
                   OwnerNotify_ItemAdded(info);
                  Items.Add(FItemInfo(info.Name,valueToAdd));
               }
               return true;
           }

        return true;
    }
    return true;
 }

    //Removes specified amount of item from the inventory
    UFUNCTION(BlueprintCallable)
    bool RemoveItem(FItemInfo info)
    {
        if(Items.Num() > 0 && info.Amount>0)
        {
            
            int value = 0;
            TArray<int> indeciesToRemove;
            for(int i=0;i<Items.Num();i++)
            {
                if(Items[i].Name==info.Name)
                {
                    if((info.Amount-value)>Items[i].Amount)
                    {
                        indeciesToRemove.Add(i);
                        value+=Items[i].Amount;
                    }
                    else
                    {
                        Items[i].Amount-=(info.Amount-value);
                        value+=(info.Amount-value);
                    }
                    
                    if(value>=info.Amount)
                    {                        
                        
                        for(int o=0;o<indeciesToRemove.Num();o++)
                        {
                            OwnerNotify_ItemRemoved(Items[indeciesToRemove[o]]);
                            Items.RemoveAt(indeciesToRemove[o]);
                        }
                         return true;
                    }
                }
            }
            return false;         
        }
        return false;
    }

    //Removes specified amount of item from the inventory
    UFUNCTION(BlueprintCallable)
    bool DropItem(FItemInfo info)
    {
        if(Items.Num() > 0 && info.Amount>0)
        {
            
            int value = 0;
            TArray<int> indeciesToRemove;
            for(int i=0;i<Items.Num();i++)
            {
                if(Items[i].Name==info.Name)
                {
                    if((info.Amount-value)>=Items[i].Amount)
                    {
                        indeciesToRemove.Add(i);
                        value+=Items[i].Amount;
                    }
                    else
                    {
                        Items[i].Amount-=(info.Amount-value);
                        value+=(info.Amount-value);
                    }
                    
                    if(value>=info.Amount)
                    {                        
                        
                        for(int o=0;o<indeciesToRemove.Num();o++)
                        {
                            OwnerNotify_ItemDropped(Items[indeciesToRemove[o]]);
                            Items.RemoveAt(indeciesToRemove[o]);
                        }
                         return true;
                    }
                }
            }
            return false;         
        }
        return false;
    }

};