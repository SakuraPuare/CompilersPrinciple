// 测试文件2: 条件语句和运算符
int main() {
    int a, b, c;
    a = 10;
    b = 5;
    c = 0;
    
    // 测试if-else语句
    if (a > b) {
        c = a;
    } else {
        c = b;
    }
    
    // 测试复杂条件表达式
    if (a >= 10 && b <= 5) {
        c = c + 1;
    }
    
    if (a == 10 || b != 4) {
        c = c * 2;
    }
    
    // 测试嵌套if语句
    if (a > 0) {
        if (b > 0) {
            c = c + a + b;
        } else {
            c = c + a - b;
        }
    }
    
    return c; // 应返回32
} 