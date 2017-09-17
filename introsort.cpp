const int threshold=16;

int parent(int i)
{
    return (int)((i-1)/2);
}
 
int left(int i)
{
    return 2 * i+1;
}
 
int right(int i)
{
    return (2 * i + 2);
}
 
void heapShiftDown(int heap[], int i, int begin,int end)
{
    int l = left(i-begin)+begin;
    int r = right(i-begin)+begin;
    int largest=i;
    
    if(l < end && heap[l] > heap[largest])
        largest = l;
    if(r < end && heap[r] > heap[largest])
        largest = r;
    
    if(largest != i)
    {
        swap(heap[largest],heap[i]);
        heapShiftDown(heap, largest, begin,end);
    }
}
 
void buildHeap(int heap[],int begin,int end)
{
    for(int i = (begin+end)/2; i >= begin; i--)
    {
        heapShiftDown(heap, i, begin,end);
    }
}
 
void heapSort(int heap[], int begin,int end)
{
    buildHeap(heap,begin,end);
    for(int i = end; i >begin; i--)
    {
        swap(heap[begin],heap[i]);
        heapShiftDown(heap,begin,begin, i);
    }
}

void insertionSort(int array[],int len)
{
    int i,j,temp;
    for(i=1;i<len;i++)
    {
      temp = array[i];
      for(j=i;j>0 && temp < array[j-1];j--)
      {
          array[j]=array[j-1];
      }
      array[j]=temp;
    }
}

int median3(int array[],int first,int median,int end)
{
        if(array[first]<array[median])
        {
                if(array[median]<array[end])
                        return median;
                else if(array[first]<array[end])
                        return end;
                else
                        return first;
        }
        else if(array[first]<array[end])
                return first;
        else if(array[median]<array[end])
                return end;
        else 
                return median;
}

int partition(int array[],int left,int right,int p)
{
        int index = left;
        swap(array[p],array[right]);
        int pivot = array[right]; 
            
        for (int i=left; i<right; i++)
        {
                if (array[i] < pivot)    
                        swap(array[index++],array[i]);
        }
        
        swap(array[right],array[index]);
        return index;
}


void introSortLoop(int array[],int begin,int end,int depthLimit)
{
        while((end-begin+1)>threshold) 
        {
                if(depthLimit==0)      
                {
                        heapSort(array,begin,end);
                        return ;
                }
                --depthLimit;
                
                int cut=partition(array,begin,end,
                                median3(array,begin,begin+(end-begin)/2,end)); 
                introSortLoop(array,cut,end,depthLimit);
                end=cut;    
        }
}

int lg(int n)
{
        int k;
        for(k=0;n>1;n>>=1) ++k;
        return k;
}

void introSort(int array[],int len)
{
        if(len!=1)
        {
                introSortLoop(array,0,len-1,lg(len)*2);
                insertionSort(array,len);
        }
}
