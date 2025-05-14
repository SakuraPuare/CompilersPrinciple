int main() {
    int count;
    count = 0;
    do { // do-while 循环体是 block
        int temp;
        temp = 1; // 内部语句
        count = count + temp;
    } while (count < 3); // count 会是 1, 2, 3. 循环执行 3 次。

    int flag;
    flag = 1;
    do flag = flag - 1; // do-while 循环体是单语句
    while (flag > 0); // flag 会是 1, 0. 循环执行 2 次。

    return count + flag; // count 最终为 3, flag 最终为 0. 返回 3.
}