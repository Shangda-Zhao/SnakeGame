# SnakeGame
## 1.实验问题

  编写贪吃蛇游戏涉及结构体，函数的定义及调用、指针变量、指针和数组、逻辑表达式、基本的选择和循环语句和文件的读写等知识，可以说是麻雀虽小，五脏俱全，是练习C语言的绝佳小项目。贪吃蛇的移动是难点，我通过“一个方块消失，相邻地方出现一个方块”的方式，来表现视觉上的移动。

## 2.实验算法
**算法描述**

(1) 蛇的部分。蛇的身子是一节一节的，此时最容易联想到的数据结构就是顺序表，链表，如果把蛇看作顺序表或者链表，在之后吃到食物的时候，身子肯定会变长，这就涉及到插入的操作，为了更高的效率，用链表实现我们的蛇的部分，最初把蛇身子按照三个结点打印在屏幕。

(2) 蛇的移动。在屏幕上面蛇的移动看起来是整个身子向前方平移一个单位，但是其原理是我们在屏幕的另一个地方把蛇从新打印一遍，又把之前的蛇身子去除掉。

(3) 食物的产生。随机的在地图中产生一个节点，在蛇的头坐标和食物的坐标重复的时候，食物消失，蛇的身子加长，也就是蛇的节点数增加一个。

(4) 蛇在其中的几种状态。正常状态：蛇头节点的坐标没有和墙的坐标以及自己身子的坐标重合；被自己杀死：蛇头的坐标和蛇身子的坐标重合；撞墙：蛇头的坐标和墙的坐标重合。

(5) 当键盘有输入的时候判断是上或者下后者左或者右，然后重置DIRECT的值，就将方向重置了。当然在向上走的时候按下键是不行的(其他也是类似)，所以还要判断一下。键盘读入事件需要用到一个函数_KBHIT();如果有键盘敲击，这个函数就会返回一个非0的数。所以我们可以在每一次刷新的时候。

**算法流程图**
