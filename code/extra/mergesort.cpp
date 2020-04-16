// Merge Sort
// ordena o vetor arr
// complexidade: O(nlogn)

// merges two subarrays of arr[] 
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    // temp arrays 
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) R[j] = arr[m + 1+ j]; 
  
    i = 0; // initial index of first subarray 
    j = 0; // initial index of second subarray 
    k = l; // initial index of merged subarray 
    while (i < n1 and j < n2) { 
        if (L[i] <= R[j]) { 
            arr[k] = L[i]; 
            i++; 
        } 
        else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    // copy the remaining elements of L[] 
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    // copy the remaining elements of R[] 
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
void mergesort(int arr[], int l, int r) { 
    if (l < r) { 
        // same as (l+r)/2, but avoids overflow for large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergesort(arr, l, m); 
        mergesort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 
