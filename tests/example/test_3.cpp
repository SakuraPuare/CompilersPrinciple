// 测试文件3: 循环语句
int main() {
    int sum, i;
    
    // 测试for循环
    sum = 0;
    for (i = 1; i <= 5; i = i + 1) {
        sum = sum + i;
    }
    
    // 测试while循环
    i = 10;
    while (i > 0) {
        sum = sum + 1;
        i = i - 2;
    }
    
    // 测试do-while循环
    i = 3;
    do {
        sum = sum * 2;
        i = i - 1;
    } while (i > 0);
    
    // 测试break语句
    i = 0;
    while (i < 10) {
        i = i + 1;
        if (i == 5) {
            break;
        }
        sum = sum + 1;
    }
    
    // 测试continue语句
    for (i = 0; i < 5; i = i + 1) {
        if (i == 2) {
            continue;
        }
        sum = sum + 10;
    }
    
    return sum;
} 