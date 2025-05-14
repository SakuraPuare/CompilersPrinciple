// 测试文件6: 数组操作
int main() {
    int a[10];
    int i, sum;
    
    // 初始化数组
    for (i = 0; i < 10; i = i + 1) {
        a[i] = i * i;
    }
    
    // 求和
    sum = 0;
    for (i = 0; i < 10; i = i + 1) {
        sum = sum + a[i];
    }
    
    // 查找最大值
    int max;
    max = a[0];
    for (i = 1; i < 10; i = i + 1) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    
    // 数组元素交换
    int temp;
    temp = a[0];
    a[0] = a[9];
    a[9] = temp;
    
    // 冒泡排序
    for (i = 0; i < 9; i = i + 1) {
        int j;
        for (j = 0; j < 9 - i; j = j + 1) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    
    return sum;
} 