#include<iostream>
#include<string>
#include<vector>

using namespace std;

// ----- 1. 冒泡排序 -----
void bubble(vector<int> &v) {
    for(int i = 0; i < v.size()-1; i++) {
        for(int j = 0; j < v.size()-1-i; j++) {
            if (v[j] > v[j+1])
                swap(v[j], v[j+1]);
        }
    }
}


// ----- 2. 选择排序 -----
void select(vector<int> &v) {
    for(int i = 0; i < v.size()-1; i++) {
        for(int j = i+1; j < v.size(); j++) {
            if (v[i] > v[j]) 
             swap(v[i], v[j]);
        }
    }
}

// ----- 3. 快速排序 -----
// 双向扫描
int partition_2(vector<int> &v, int left, int right) {
    int key = v[left];
    int i = left, j = right;
    while(i < j) {
        while(i < j && v[j] >= key) j--;
        v[i] = v[j];
        while(i < j && v[i] <= key) i++;
        v[j] = v[i];
    }
    v[i] = key;
    return i;
}


// 单向扫描
int partition_1(vector<int> &v, int left, int right) {
    int key = v[right];
    int i = left;
    for(int j = left; j <= right; j++) {
        if(v[j] < key) {
            swap(v[i], v[j]);
            i++;
        }
    }
    swap(v[i], v[right]);
    return i;
}

void quick(vector<int> &v, int left, int right) {
    if (left < right) {
        int mid = partition_1(v, left, right);
        quick(v, left, mid-1);
        quick(v, mid+1, right);
    }
}

// ----- 4. 归并排序 -----
void merge(vector<int> &v, int left, int mid, int right) {
    int i = left, j = mid+1, k = 0;
    vector<int> temp(right - left + 1);
    while(i <= mid && j <= right) {
        if (v[i] <= v[j]) 
            temp[k++] = v[i++];
        else   
            temp[k++] = v[j++];
    }
    while(i <= mid) temp[k++] = v[i++];
    while(j <= right) temp[k++] = v[j++];
    i = left, k = 0;
    while(i <= right) v[i++] = temp[k++];
}

void mergeSort(vector<int> &v, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(v, left, mid);
        mergeSort(v, mid+1, right);
        merge(v, left, mid, right);
    }
}


// ----- 5. 插入排序 -----
void insert(vector<int> &v) {
    for(int i = 1; i < v.size(); i++) {
        int key = v[i];
        int j = i-1;
        while(j >= 0 && key <= v[j]) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = key;
    }
}


// ----- 6. 希尔排序 -----
void shellSort(vector<int> &v) {
    int len = v.size();
    // 改变步长
    for(int step = len / 2; step > 0; step /= 2) {
        // 对每一组
        for(int i = 0; i < step; i++) {
            // 插入排序, 需要插入的次数
            for(int j = i+step; j < len; j+=step) {
                int key = v[j];
                int k = j-step;
                while(k >= 0 && key <= v[k]) {
                    v[k+step] = v[k];
                    k -= step;
                }
                v[k+step] = key;
            }
        }
    }
}


// 调整堆
void adjustHeap(vector<int> &v, int i, int len) {
    int maxidx = i; // 最大指针指向父节点
    // 如果有左子树，且左子树大于父节点，最大指针指向左子树
    if(2*i+1 < len && v[2*i+1] > v[maxidx]) {
        maxidx = 2 * i + 1;
    }
    // 如果有右子树，且右子树大于父节点和左子树，最大指针指向右子树
    if(2*i+2 < len && v[2*i+2] > v[maxidx]) {
        maxidx = 2 * i + 2;
    }
    // 如果最大值不是父节点，则交换父节点和最大值，并且递归调整最大值
    if(i != maxidx) {
        swap(v[i], v[maxidx]);
        adjustHeap(v, maxidx, len);
    }
}

// ----- 7.堆排序 -----
void heapSort(vector<int> &v) {
    int len = v.size();
    // 从最后一个非叶子节点开始，调整堆,得到最大堆
    for(int i = (len-1) / 2; i >= 0; i--) {
        adjustHeap(v, i, len);
    }  
    // 循环将首位最大值与末尾交换，然后重新调整最大堆
    for(int i = len-1; i > 0; i--) {
        swap(v[0], v[i]);
        adjustHeap(v, 0, i);
    } 
}


int main() {
    // vector<int> v = {11,5,2,4,6,7,4,3,8,1,2,0,10};
    vector<int> v = {8,2,4,6,7,0,3,8,9,10};
    // mergeSort(v, 0, v.size()-1);
    // select(v);
    // bubble(v);
    // quick(v, 0, v.size()-1);
    // heapSort(v);
    shellSort(v);
    // insert(v);
    for(auto i:v)
        cout << i << " ";
    return 0;
}