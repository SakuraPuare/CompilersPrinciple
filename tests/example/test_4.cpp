// 测试文件4: 函数定义和调用
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void swap(int a, int b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

int main() {
    int x, y, result;
    x = 10;
    y = 5;
    
    // 测试基本函数调用
    result = add(x, y);      // 15
    result = subtract(x, y);  // 5
    result = multiply(x, y);  // 50
    
    // 测试递归函数
    result = factorial(5);    // 120
    result = fibonacci(7);    // 13
    
    // 测试void函数
    swap(x, y);
    
    return result;
} 