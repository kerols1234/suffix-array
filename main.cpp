#include <iostream>

using namespace std;

class SuffixArray
{
public:
    SuffixArray(char data[])
    {
        Size = 0;
        for(int i = 0; data[i] != '\0'; i++)
            Size++;

        originalArray = new char[Size];
        suffixArray = new int[Size];
        group = new int[Size];
        mergeArray = new int[Size];

        for(int i = 0; data[i] != '\0'; i++)
        {
            originalArray[i] = data[i];
            suffixArray[i] = i;
            group[i] = data[i];
        }
    };

    ~SuffixArray() {};

    void Print()
    {
        for(int i = 0; i < Size; i++)
            cout<<suffixArray[i]<<" ";
        cout<<endl;
    };

    void merging(int low, int mid, int high, int h)
    {
        int l1, l2, i;
        for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++)
        {
            if(!(compare(suffixArray[l2],suffixArray[l1],h)))
                mergeArray[i] = suffixArray[l1++];
            else
                mergeArray[i] = suffixArray[l2++];
        }
        while(l1 <= mid)
            mergeArray[i++] = suffixArray[l1++];
        while(l2 <= high)
            mergeArray[i++] = suffixArray[l2++];
        for(i = low; i <= high; i++)
            suffixArray[i] = mergeArray[i];
    };

    void Sort(int low, int high, int h)
    {
        int mid;
        if(low < high)
        {
            mid = (low + high) / 2;
            Sort(low, mid, h);
            Sort(mid+1, high, h);
            merging(low, mid, high, h);
        }
        return;
    };

    void ConstructUsingPrefixDoubling()
    {
        Sort(0,Size-1, 0);
        int *sortGroup = new int[Size];
        sortGroup[0] = 0;

        for (int h = 1; h < Size; h = h * 2)
        {
            Sort(0,Size-1, h);

            for (int i = 1; i < Size; i++)
                sortGroup[i] = sortGroup[i - 1] + compare(suffixArray[i - 1], suffixArray[i], h);

            for (int i = 0; i < Size; i++)
                group[suffixArray[i]] = sortGroup[i];
        }
    };

    bool compare(int i, int j, int h)
    {
        if (group[i] != group[j])
            return group[i] < group[j];
        return group[i + h] < group[j + h];
    };

private:
    int Size;
    char *originalArray;
    int *suffixArray;
    int *group;
    int *mergeArray;
};

int main()
{
    SuffixArray t("ACGACTACGATAAC$");

    t.ConstructUsingPrefixDoubling();

    t.Print(); // Prints:  14 11 12  0  6  3  9 13  1  7  4  2  8 10  5

    return 0;
}
