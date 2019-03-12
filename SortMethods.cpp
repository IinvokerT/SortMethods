//
//  SortMethods.cpp
//
//  Created by Yanfei Liu.
//  Copyright © 2019 Yanfei Liu. All rights reserved.
//

#include <iostream>
using namespace std;

/// 八大排序法，接受输入为int整数的数组，其中基数排序可以按照十进制位来划分。
/// 除了基数排序，reverse的实现在于多了一个与或判断，代码注释部分按照升序理解。


//=====---------------交换排序法start---------------=====//
//------------------包含冒泡和快排-------------------//
/**
 冒泡排序法
 
 @discussion
 1. 时间复杂度：最好O(n)，最差O(n^2)，平均O(n^2)
 
 2. 空间复杂的：O(1)
 
 3. 稳定性：稳定
 @param a 数组
 @param length 数组长度
 @param reverse 是否降序（默认否）
 */
void BubbleSort(int *a, int length, bool reverse=false) {
    // 每次扫描，两两交换，一边得到一个准确位置
    for (int i = 1; i < length; i++) {
        for (int j = 0; j < length - i ; j++) {
            if ((!reverse && a[j] > a[j+1]) || (reverse && a[j] < a[j+1])) {
                a[j] = a[j] ^ a[j+1];
                a[j+1] = a[j] ^ a[j+1];
                a[j] = a[j] ^ a[j+1];
            }
        }
    }
}


/**
 快速排序法
 
 @discussion
 1. 时间复杂度：最好O(n*log2n，每次的标识位都能折半划分序列)，最差O(n^2，每次的标识位都是最大或最小)，平均O(n*log2n)
 
 2. 空间复杂的：O(log2n)
 
 3. 稳定性：不稳定
 @param a 数组
 @param left 排序起始下标
 @param right 排序结束下标
 @param reverse 是否降序（默认否）
 
 方法原理：设两个指针 low 和 high，其初值分别指向数组的元素1和元素n。
 
 a. 选第 1 个记录为枢轴，关键字为pivotkey。
 
 b. 将 pivotkey 复制到 r[0] 中，从 high 所指的位置起 向前 搜索找到第一个关键字 小于pivotkey 的记录，复制到 low 所指位置中；然后从 low 所指位置起向后搜索，找到第一个关键字 大于 pivotkey 的记录，复制到 high 所指位置中。
 
 c. 重复上两步直到 low＝high 为止。
 */
void QuickSort(int *a, int left, int right, bool reverse=false) {
    if (left > right) return;
    int i = left, j = right;
    int pivotKey = a[i];
    while (i < j) {
        // 后面找到比pivotKeyd小的时，将其放到前面即left(i)
        // ((!reverse && pivotKey <= a[j]) || (reverse &&
        while (i < j && ((!reverse && pivotKey <= a[j]) || (reverse && pivotKey >= a[j]))) {
            j --;
        }
        a[i] = a[j];
        
        // 前面找到比pivotKeyd大的时，将其放到后面即right(j)
        // ((!reverse && pivotKey >= a[i]) || (reverse &&
        while (i < j && ((!reverse && pivotKey >= a[i]) || (reverse && pivotKey <= a[i]))) {
            i ++;
        }
        
        a[j] = a[i];
    }
    // 一边扫完之后，pivotKey归位，前面都小于自己，后面都大于自己
    a[i] = pivotKey;
    // 继续pivotKey前的序列和后的y序列快排
    QuickSort(a, left, i-1, reverse);
    QuickSort(a, i+1, right, reverse);
}
//=====---------------交换排序法end---------------=====//


//=====---------------选择排序法start---------------=====//
//-----------------包含简单选择和堆排-----------------//
/**
 简单选择排序法
 
 @discussion
 时间复杂度：最好O(n^2)，最差O(n^2)，平均O(n^2)
 
 空间复杂度：O(1)
 
 稳定性：不稳定
 @param a 数组
 @param length 数组长度
 @param reverse 是否降序（默认否）
 */
void SelectionSort(int *a, int length, bool reverse=false) {
    // 序列中每个元素都与其他比，每次把最小的找出来放好位置
    for (int i = 0; i < length; i++) {
        int minOrMaxIndex = i;
        for (int j = i + 1; j < length; j++) {
            if ((!reverse && a[minOrMaxIndex] > a[j]) || (reverse && a[minOrMaxIndex] < a[j])) {
                minOrMaxIndex = j;
            }
        }
        if (minOrMaxIndex != i) {
            a[minOrMaxIndex] = a[minOrMaxIndex] ^ a[i];
            a[i] = a[minOrMaxIndex] ^ a[i];
            a[minOrMaxIndex] = a[minOrMaxIndex] ^ a[i];
        }
    }
}


//=====---------------堆排法start---------------=====//
/**
 堆排序-筛选调整堆

 @param a 输入数组
 @param parent 需要调整的根结点
 @param len 需要调整堆的大小
 @param reverse 是否降序（默认否）
 */
void heapAdjust(int *a, int parent, int len, bool reverse=false) {
    // 记录孩子中最大的，开始选取左孩子的位置
    int mChild = (parent << 1) + 1;
    // 当前需要调整的结点
    int current = a[parent];
    
    while (mChild < len) {
        // 寻找是否有右孩子，找孩子中的最大的
        if (mChild + 1 < len && ((!reverse && a[mChild] < a[mChild + 1]) || (reverse && a[mChild] > a[mChild + 1]))) {
            mChild ++;
        }
        // 如果当前的节点比自己的孩子都大，则结束
        if ((!reverse && current >= a[mChild]) || (reverse && current <= a[mChild])) {
            break;
        }
        //否则，最大的孩子“上位”，在自己最大孩子以下再找自己的位置
        a[parent] = a[mChild];
        parent = mChild;
        mChild = (parent << 1) + 1;
    }
    // 结束后当前结点就找到了自己应该待的位置
    a[parent] = current;
}



/**
 堆排序
 
 @discussion
 时间复杂度：最好O((n*log2n)，最差O((n*log2n)，平均O((n*log2n)
 
 空间复杂度：O(1)
 
 稳定性：不稳定
 
 @param a 输入数组
 @param len 数组长度
 @param reverse 是否降序（默认否）
 */
void HeapSort(int *a, int len, bool reverse=false) {
    // 先根据数列建一个大根堆
    // 由于属于完全二叉树，所以最后一个非叶子结点位置在n/2 - 1处
    for (int i = (len >> 1) - 1; i >= 0; i --) {
        heapAdjust(a, i, len, reverse);
    }
    // 进行n-1次排序，每次把堆顶输出，把最后一个叶子结点放在顶上，调整堆
    for (int i = len - 1; i > 0; i --) {
        a[0] = a[0] ^ a[i];
        a[i] = a[0] ^ a[i];
        a[0] = a[0] ^ a[i];
        heapAdjust(a, 0, i, reverse);
    }
}
//=====---------------堆排法end---------------=====//
//=====---------------选择排序法end---------------=====//


//=====---------------插入排序法start---------------=====//
//-----------------包含直接插入（含折半）和希尔排序-----------------//
/**
 插入排序法
 
 @discussion
 时间复杂度：最好O(n)，最差O(n^2)，平均O(n^2)
 
 空间复杂度：O(1)
 
 稳定性：稳定
 
 @param a 数组
 @param length 数组长度
 @param reverse 是否降序（默认否）
 @param binary 是否采用折半查找（默认是）
 */
void InsertSort(int *a, int length, bool reverse=false, bool binary=true) {
    // 从第一个元素开始，当作排好序的序列，后面来的就在这个序列中插入即可
    for (int i = 1;  i < length; i++) {
        if ((!reverse && a[i] < a[i-1]) || (reverse && a[i] > a[i-1])) {
            // 存新来的元素，因为后面找位置的时候会被覆盖
            int temp = a[i];
            
            if (binary) {
                // 采用折半查找的方式来给新来的元素找位置
                // 有序序列的开始和截止
                int low = 0, high = i-1;
                // 折半查找插入位置
                while (low <= high) {
                    int mid = (low + high) / 2;
                    if ((!reverse && a[mid] < temp) || (reverse && a[mid] > temp)) {
                        low = mid + 1;
                    }else {
                        high = mid - 1;
                    }
                }
                // 有序序列后移，给新来的腾位置
                for (int j = i - 1; j >= high+1; j--) {
                    a[j+1] = a[j];
                }
                a[high+1] = temp;
                
            }else {
                // 不采用折半查找方式一个一个比较查找给新来的元素找位置
                int j = 0;
                // 有序序列后移，给新来的找位置
                for (j = i - 1; j >= 0 && ((!reverse && temp < a[j]) || (reverse && temp > a[j])); j--) {
                    a[j+1] = a[j];
                }
                // 新来的插入找好的位置
                a[j+1] = temp;
            }
        }
    }
}


/**
 希尔排序法
 
 @discussion
 时间复杂度：最好O(n^2)，最差O(n^2)，平均O(n^2)
 
 空间复杂度：O(1)
 
 稳定性：不稳定
 
 @param a 数组
 @param len 数组长度
 @param reverse 是否降序（默认否）
 */
void ShellSort(int *a, int len, bool reverse=false) {
    // gap为步长，初始为长度的一半
    //迭代步长直到为1，每次取一半
    for (int gap = len >> 1; gap > 0; gap >>= 1) {
        
        //开始可以划分为多少个子序列就循环多少次
        for (int i = gap; i < len; i++) {
            int temp = a[i];
            int j = i - gap;
            // 在该子序列中，找合适的插入位置位置
            while (j >= 0 && ((!reverse && a[j] > temp) || (reverse && a[j] < temp))) {
                a[j + gap] = a[j];
                j -= gap;
            }
            a[j + gap] = temp;
        }
    }
}
//=====---------------插入排序法end---------------=====//


//=====---------------二路_归并排序法start---------------=====//
/**
 二路_归并排序法-合并

 @param a 输入数组
 @param left 合并的第一组开始位置
 @param mid 合并的第一组结束位置（第二组开始的前一位）
 @param right 合并的第二组结束位置
 @param reverse 是否降序（默认否）
 */
void merge(int *a, int left, int mid, int right, bool reverse=false) {
    int length = right - left + 1;
    int temp[length];
    int i = left, j = mid + 1, k = 0;
    
    // 两组元素一位一位比较，小的插入辅助数列
    while (i <= mid && j <= right) {
        if ((!reverse && a[i] <= a[j]) || (reverse && a[i] > a[j])) {
            temp[k++] = a[i++];
        }else {
            temp[k++] = a[j++];
        }
    }
    // 至此表示有一组已经全部放入辅助数列中了
    
    // 第一组还剩余元素，则添到辅助数列中
    while (i <= mid) {
        temp[k++] = a[i++];
    }
    // 第二组还剩余元素，则添到辅助数列中
    while (j <= right) {
        temp[k++] = a[j++];
    }
    // 将辅助数列中的值（排好序的）替换之前的数组中的值
    k = 0;
    for (int e = left; e <= right; e++) {
        a[e] = temp[k++];
    }
}


/**
 二路_归并排序法-入口
 
 @discussion
 时间复杂度：最好O(n*log2n)，最差O(n*log2n)，平均O(n*log2n)
 
 空间复杂度：O(n)，辅助数组
 
 稳定性：稳定
 
 分治思想，分为单个的，两两合并，一直往上合并
 
 @param a 输入数组
 @param left 需要排序的开始位置
 @param right 需要排序的结束位置
 @param reverse 是否降序（默认否）
 */
void MergeSort(int *a, int left, int right, bool reverse=false) {
    if (left < right) {
        int mid = (left + right) >> 1;
        // 分治
        MergeSort(a, left, mid, reverse);
        MergeSort(a, mid+1, right, reverse);
        // 合并
        merge(a, left, mid, right, reverse);
    }
}
//=====---------------二路_归并排序法end---------------=====//


//=====---------------基数排序法start---------------=====//
/**
 基数排序法-求数组中最大值的位数

 @param a 输入数组
 @param len 数组长度
 @return 数组中最大数卫视
 */
int maxBit(int *a, int len) {
    if (!len) {
        return -1;
    }
    // 数组中最大的值
    int maxOfA = a[0];
    // 找数组中最大的值
    for (int i = 1; i < len; i++) {
        if (a[i] > maxOfA) {
            maxOfA = a[i];
        }
    }
    // 算出最大值的位数即为所求
    int bitsCount = 0;
    while (maxOfA) {
        bitsCount++;
        maxOfA /= 10;
    }
    
    return bitsCount;
}


/**
 基数排序-求某数指定位数上的数值

 @param number 所求数
 @param digit 指定位数
 @return 该数指定位数上的值
 */
int getValueOfDigit(int number, int digit) {
    int pow = 1;
    while (--digit > 0) {
        pow *= 10;
    }
    return number / pow %  10;
}



/**
 基数排序（其他方法也可使用）-反转数组

 @param a 输入数组
 @param len 数组长度
 */
void _reverse(int *a, int len) {
    for (int i = 0; i < (len >> 1); i++) {
        a[i] = a[i] ^ a[len-1-i];
        a[len-1-i] = a[i] ^ a[len-1-i];
        a[i] = a[i] ^ a[len-1-i];
    }
}



/**
 基数排序
 
 @discussion
 时间复杂度：最好O(d*(n+r))，最差O(d*(n+r))，平均O(d*(n+r))，d为最高位数，n为元素个数，r为每个位数上取值范围
 
 空间复杂度：O(n+r)，辅助数组count和temp
 
 稳定性：稳定

 @param a 输入数组
 @param len 数组长度
 @param reverse 是否降序（默认否）
 */
void RadixSort(int *a, int len, bool reverse=false) {
    int temp[len];
    for (int d = 1; d <= maxBit(a, len); d ++) {
        // d位数上值为count下标的数的个数（桶）
        int count[10] = {0};
        // 桶统计完毕
        for (int i = 0; i < len; i++) {
            count[getValueOfDigit(a[i], d)] ++;
        }
        // 计算d位上值为index的数能在该遍排序后放的可行的位置
        // 如[0,1,2,2,3,0,0]则变为[0,1,3,5,8,8,8]
        // 其中3表示d位上值为2的数可以放的位置可能为1,2
        // 其中5表示d位上值为3的数可以放的位置可能为3,4
        for (int i = 1; i < 10; i++) {
            count[i] += count[i-1];
        }
        // 开始归位（桶排序）
        for (int i = len-1;i >= 0 ; i--) {
            int value = getValueOfDigit(a[i], d);
            // 跟据之前的count来按照d位的数值排好
            temp[count[value] - 1] = a[i];
            count[value] --;
        }
        // 赋值拷贝
        for (int i = 0; i < len; i++) {
            a[i] = temp[i];
        }
    }
    // 由于基数排序的复杂性，降序排列直接反转即可:-)
    if (reverse) {
        _reverse(a, len);
    }
}
//=====---------------基数排序法end---------------=====//


/**
 得到数组长度
 
 @param arr 数组
 @return int型数组长度
 */
template<class T>
int getArrLength(T& arr){
    return sizeof(arr) / sizeof(arr[0]);
}


/**
 数组输出函数

 @param array 需要输出的数组
 @param len 数组长度
 */
void printArray(int *array, int len) {
    for (int i = 0; i < len; i++) {
        i == 0 ? cout << array[i] : cout << ' ' << array[i];
    }
    cout << endl;
}


int main() {
    int array[10] = {50, 123, 543, 187, 49, 30, 11, 2, 11, 100};
    int len = getArrLength(array);
    
    BubbleSort(array, len);
    cout << "冒泡排序升序：\t\t\t";
    printArray(array, len);
    
    BubbleSort(array, len, true);
    cout << "冒泡排序降序：\t\t\t";
    printArray(array, len);
    
    QuickSort(array, 0, 9);
    cout << "快速排序升序：\t\t\t";
    printArray(array, len);
    
    QuickSort(array, 0, 9, true);
    cout << "快速排序降序：\t\t\t";
    printArray(array, len);
    
    SelectionSort(array, len);
    cout << "简单选择排序升序：\t\t";
    printArray(array, len);
    
    SelectionSort(array, len, true);
    cout << "简单选择排序降序：\t\t";
    printArray(array, len);
    
    HeapSort(array, len);
    cout << "堆排序升序：\t\t\t";
    printArray(array, len);
    
    HeapSort(array, len, true);
    cout << "堆排序降序：\t\t\t";
    printArray(array, len);
    
    InsertSort(array, len, false, false);
    cout << "插入排序升序：\t\t\t";
    printArray(array, len);
    
    InsertSort(array, len, true, false);
    cout << "插入排序降序：\t\t\t";
    printArray(array, len);
    
    InsertSort(array, len, false, true);
    cout << "插入排序(二分查找)升序：\t";
    printArray(array, len);
    
    InsertSort(array, len, true, true);
    cout << "插入排序(二分查找)降序：\t";
    printArray(array, len);
    
    ShellSort(array, len);
    cout << "希尔排序升序：\t\t\t";
    printArray(array, len);
    
    ShellSort(array, len, true);
    cout << "希尔排序降序：\t\t\t";
    printArray(array, len);
    
    MergeSort(array, 0, 9);
    cout << "二分归并排序升序：\t\t";
    printArray(array, len);
    
    MergeSort(array, 0, 9, true);
    cout << "二分归并排序降序：\t\t";
    printArray(array, len);
    
    RadixSort(array, len);
    cout << "基数排序升序：\t\t\t";
    printArray(array, len);
    
    RadixSort(array, len, true);
    cout << "基数排序降序：\t\t\t";
    printArray(array, len);
    
    return 0;
}


