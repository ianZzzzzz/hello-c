/**************************************************
程序功能：
 * 对数组内的成绩进行添加/插入/删除，
 * 统计分数段人数并打印图表，
 * 计算平均分/中值/极值，
 * 对特定分数进行线性/折半查找
函数参数设置：
 * 如无特殊说明，函数的参数均为成绩数组，及数组内有效成绩个数
 * 有效成绩个数由函数checkout给出，调用函数checkout，返回有效成绩个数
***********************************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#define SIZE_ARRAY 50 /*成绩数组大小*/
#define LENGTH 16
#define SIZE_STRING 40
/*存储提示语句的字符串行数*/
void print(char string[16][SIZE_STRING]);      /*1 打印提示语句及选择列表。       参数：提示字符串数组  */
int checkout(int array[], size_t size);        /*2 判定数组中的有效成绩数量。*/
void statistics(int array[], size_t i);        /*3  统计各分数段学生人数*/
void bubble(int array, size_t size);           /*4  冒泡排序*/
void swap(int *Ptr1, int *Ptr2);               /*5  交换函数 函数内部以指针操作   参数：参与交换的两个元素的地址*/
void show_all(int array[], size_t size);       /*6  显示所有成绩*/
void up_side_down(int array[], size_t size);   /*7  逆序重排*/
void linear_search(int array[], size_t size);  /*8  线性查找*/
int half_search(int array[], size_t size);     /*9  折半查找*/
void added(int array[], size_t size);          /*10 在数组末尾添加元素*/
void insert(int array[], size_t size);         /*11 特定位置插入成绩*/
void delete_element(int array[], size_t size); /*12 删除特定位置成绩*/
void extre_avg_mid_num(int array[], size_t size, size_t menu_num);
/*13 计算平均分/中值/极值            参数：menu_num 在函数内选择具体内容*/
void bubble_choose(int array[], size_t size, int (*compare)(int element1, int element2));
int ascending(int element1, int element2);
int descending(int element1, int element2);
int main(void)
{
    int menu_num = -1;
    int sort = -1;
    char hint[][SIZE_STRING] = {
        "1.统计学生数", " 2.统计各分数段人数",
        "3.最高分", "4.最低分", "5.平均分", "6.中值",
        "7.线性查找", "8.折半查找", "9.添加成绩", "10.插入成绩", "11.删除指定成绩", "12.冒泡排序",
        "13.逆序重排", "14.显示有效成绩", "15.退出", "16."
    };

    //成绩赋值
    int grade[SIZE_ARRAY] = {
        1, 99, 20, 25, 30,
        35, 40, 43, 45, 50,
        52, 54, 56, 58, 60,
        61, 62, 63, 64, 65,
        66, 67, 68, 69, 70,
        75, 76, 77, 78, 80,
        85, 90, 95, 100
    };

    //无效的数组单元 赋值 -1 以便checkout函数区别于有效成绩
    for (size_t i = 34; i < SIZE_ARRAY; i++)
    {

        grade[i] = -1;
    } //for

    //选择菜单 15退出
    while (1)
    {

        print(hint);
        scanf("%2d", &menu_num);
        if (menu_num == 15)
        {
            return 0;
            system("pause");
        }
        while (getchar() != '\n')
            ;

        switch (menu_num)
        {
        case 1:
            printf("有效成绩数量为%d", checkout(grade, SIZE_ARRAY));
            break; //打印有效成绩数
        case 2:
            statistics(grade, checkout(grade, SIZE_ARRAY));
            break; //统计分数段打印统计图

            //3 4 5 6 使用同一个函数  menu_num作为实参传递 控制四个功能的选择
        case 3:
            extre_avg_mid_num(grade, checkout(grade, SIZE_ARRAY), menu_num);
            break;
        case 4:
            extre_avg_mid_num(grade, checkout(grade, SIZE_ARRAY), menu_num);
            break;
        case 5:
            extre_avg_mid_num(grade, checkout(grade, SIZE_ARRAY), menu_num);
            break;
        case 6:
            extre_avg_mid_num(grade, checkout(grade, SIZE_ARRAY), menu_num);
            break;

        case 8:
            half_search(grade, checkout(grade, SIZE_ARRAY));
            break; //折半
        case 7:
            linear_search(grade, checkout(grade, SIZE_ARRAY));
            break; //线性
        case 9:
            added(grade, checkout(grade, SIZE_ARRAY));
            break; //末端添加成绩
        case 10:
            insert(grade, checkout(grade, SIZE_ARRAY));
            break; //插入
        case 11:
            delete_element(grade, checkout(grade, SIZE_ARRAY));
            break; //删除指定位置
        //选择冒泡排序升序降序
        case 12:
            puts("请选择：1.降序  2.升序");
            scanf("%d", &sort);
            while (getchar() != '\n')
                ;
            if (sort == 1)
            {
                bubble_choose(grade, checkout(grade, SIZE_ARRAY), ascending);
            }
            else if (sort == 2)
            {
                bubble_choose(grade, checkout(grade, SIZE_ARRAY), descending);
            }
            else
            {
                puts("请输入正确的编号");
            }
            break; //冒泡排序
        case 13:
            up_side_down(grade, checkout(grade, SIZE_ARRAY));
            break; //逆序重排
        case 14:
            show_all(grade, checkout(grade, SIZE_ARRAY));
            break; //显示所有成绩
        //case 15: break;
        default:
            puts("请输入正确的编号");
            menu_num = 0;
            break;
        }
        system("pause");
        system("cls");
        menu_num = -1;
    } //whlie

} //main

/*1 打印函数  打印提示语句及选择列表。 参数：提示字符串数组 */
void print(char string[16][SIZE_STRING])
{
    printf("\n\t     学 生 成 绩 管 理 系 统  1.0 \n");
    printf("\t        136102017014 郑义恒\n\n");

    for (size_t i = 0; i < LENGTH; i++)
    {
        printf("\t%s\t", string[i]);
        if (i % 2 == 1)
        {
            printf("\n\n"); //打印两项换行一次
        }
    } //for inside
    printf("\n 请输入菜单编号\n");
}
/*2 判定数组中的有效成绩数量。 参数：成绩数组*/
int checkout(int array[], size_t size)
{

    int i = 0;
    while (array[i] != -1)
    {
        i++;
    }
    return i;
} //checkout
/*3  统计分数段人数并打印柱状图。  参数 学生成绩数组 有效成绩数*/
void statistics(int array[], size_t i)
{
    int grade_level[10] = {0};
    for (size_t j = 0; j < i; j++)
    {
        if (array[j] == 100) //解决统计100分时 100/10=10 导致数组grade_level[10] 产生越界问题
        {
            grade_level[9]++;
            continue;
        }
        grade_level[array[j] / 10]++;
    } //for
    for (size_t i = 0; i < 10; i++)
    {
        printf("%3d到%3d分数段的人数为%3d人.  ", i * 10, i * 10 + 10, grade_level[i]);

        for (size_t j = 0; j < grade_level[i]; j++)
        {
            printf("*");
        }
        puts("");
    } //for
} //satistics
/*4  排序 使所有成绩按升序排列*/
void bubble(int array[], size_t size)
{
    for (size_t i = 1; i < size; i++)
    {
        for (size_t j = 0; j < size - 1; j++)
        {
            if (array[j] < array[j + 1])
            {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
} //bubble
/*5  交换两个元素的指针*/
void swap(int *Ptr1, int *Ptr2)
{
    int hold = *Ptr1;
    *Ptr1 = *Ptr2;
    *Ptr2 = hold;
} //swap
/*6  显示所有有效成绩*/
void show_all(const int array[], size_t size)
{
    int j = 0;
    for (size_t i = 0; i < size; i++)
    {
        j++;
        printf("[%2d]%3d  ", i, array[i]);
        if (j % 5 == 0)
        {
            puts("");
        } //if
    }     //for in

} //show_effort
/*7  逆序重拍*/
void up_side_down(int array[], size_t size)
{

    for (size_t j = 0; j < (size / 2); j++)
    {
        swap(&array[j], &array[size - j - 1]);
    } //for

    show_all(array, size);
} //up_side_down
/*8 线性查找*/
void linear_search(int array[], size_t size)
{

    int j = 0;
    int k = 0;
    int target = 0;
    puts("请输入要查找的数0~100：");
    scanf("%d", &target);

    for (size_t i = 0; i != -2; i++)
    {

        if (array[i] == target)
        {

            printf("%3d是数组的第%3d个元素\n", target, i);
            i = -2;
            break;
        } //if

        else if (i > size - 1)
        {
            puts("查找的成绩在数组中不存在");
            break;
        } //if

    } //for
} //linear_lookup
/*9 折半查找*/
int half_search(int array[], size_t size)
{
    bubble(array, size);
    int target = 0;
    int high = size - 1;
    int low = 0;
    puts("请输入要查找的数0~100：");
    scanf("%d", &target);
    while (low <= high)
    {
        int middle = (high + low) / 2;
        if (array[middle] == target)
        {
            printf("%3d是数组的第%3d个元素。", target, middle);
            return 0;
        }
        else if (array[middle] > target)
        {
            low = middle + 1;
        }
        else
        {
            high = middle - 1;
        }

    } //while
    puts("未在数组内找到对应元素");
} //half_search
/*10 添加*/
void added(int array[], size_t size)
{
    int add_num;
    puts("请输入添加的成绩：");
    scanf("%d", &add_num);
    array[size] = add_num;
    show_all(array, size + 1);

} //added
/*11 插入*/
void insert(int array[], size_t size)
{
    size_t num, postion;
    puts("请输入添加的成绩：");
    scanf("%d", &num);
    fflush(stdin);
    puts("请输入插入的位置：");
    scanf("%d", &postion);

    for (size_t element = size; element > postion; element--)
    {
        array[element] = array[element - 1];
    }
    array[postion] = num;
    show_all(array, size + 1);
} //insert
/*12 删除*/
void delete_element(int array[], size_t size)
{
    int postion;
    int size2 = size - 1;

    puts("请输入要删除的成绩的位置：");
    scanf("%d", &postion);

    for (postion; postion < size2; postion++)
    {
        array[postion] = array[postion + 1];
    }
    array[size - 1] = -1;
    show_all(array, size - 1);
} //delete
/*13 极值 均值 中值*/
void extre_avg_mid_num(int array[], size_t size, size_t menu_num)
{
    int sum = 0;
    bubble(array, size);
    if (menu_num == 3)
    {
        printf("最高分为：%3d 分", array[0]);
    } //if
    else if (menu_num == 4)
    {
        printf("最高分为：%3d 分", array[size - 1]);
    } //else if1
    else if (menu_num == 5)
    {
        for (size_t i = 0; i < (size - 1); i++)
        {
            sum = sum + array[i];
        } //for
        printf("平均分为：%3d 分", sum / size);

    } //else if2
    else
    {
        if (size % 2 == 0)
        {
            printf("中值为%3d", (array[size / 2] + array[(size / 2) - 1]) / 2);
        } //if in
        else
        {
            printf("中值为%3d", array[(size / 2)]);
        } //else in
    }     //else out
}
/*14 升序*/
int ascending(int element1, int element2)
{
    return element1 < element2;
} //ascending
/*15 降序*/
int descending(int element1, int element2)
{
    return element1 > element2;
} //descending
/*16  排序 使所有成绩按升序或降序排列*/
void bubble_choose(int array[], size_t size, int (*compare)(int element1, int element2))
{

    for (size_t i = 1; i < size; i++)
    {
        for (size_t j = 0; j < size - 1; j++)
        {
            if ((*compare)(array[j], array[j + 1]))
            {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
    show_all(array, size);
} //bubble_choose