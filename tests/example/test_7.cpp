// 测试文件7: 全局变量和作用域
int global_var;
int global_array[5];

void init_globals() {
    global_var = 100;
    int i;
    for (i = 0; i < 5; i = i + 1) {
        global_array[i] = i * 10;
    }
}

int get_sum() {
    int sum;
    sum = 0;
    int i;
    for (i = 0; i < 5; i = i + 1) {
        sum = sum + global_array[i];
    }
    return sum;
}

int test_scope() {
    int a;
    a = 1;
    
    {
        int a; // 内部作用域的新变量
        a = 2;
        global_var = global_var + a; // 使用内部的a (2)
    }
    
    return a; // 返回外部作用域的a (1)
}

int test_shadowing(int a) {
    int global_var; // 局部变量遮蔽全局变量
    global_var = 50;
    
    return global_var + a; // 使用局部变量global_var (50)
}

int main() {
    init_globals();
    
    int local_var;
    local_var = global_var;
    
    int result;
    result = get_sum() + test_scope() + test_shadowing(10);
    
    return result;
} 