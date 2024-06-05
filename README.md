# 高级程序设计大作业之塔防游戏
## 编译环境
本人环境：windows系统下，调用rapidjson库（存取地图）和ege图形库（GUI），使用mingW编译器编译。
故应当在code文件夹中加入rapidjson库，并在mingW的include文件中加入ege库
在控制台输入
```bash
clang++ *.cpp -lgraphics64 -luuid -lmsimg32 -lgdi32 -limm32 -lole32 -loleaut32 -lwinmm -lgdiplus
```
来编译。  
ege安装教程：[EGE安装与配置](https://blog.csdn.net/qq_39151563/article/details/100161986)  
ege官网：[](https://xege.org/)  
rapidjson下载: [](https://github.com/Tencent/rapidjson)


## 地图文件
地图采用json文件保存，必须按照一定的格式写！  
由于本人技术原因，未做出“另存存档”的功能，导入存档后保存就会覆盖掉原存档，
建议将地图拷贝一份后再导入。  
提供了两张地图，在resources里的data文件夹中。  

## 教程
找到Game.exe文件打开后，进入主界面。  
主界面： 点"start"进入选图界面，点左下角的×退出游戏。  
选图界面： 输入存档json文件的路径来打开存档，路径错误会直接退出程序。  
游戏内： 点塔或者词缀可以拖动，右键取消拖动。  
敌人会从家里出来到你家里去，一旦有一个敌人进入家，游戏结束。  
杀掉所有敌人后游戏结束。  
右上角分别是"存档并退出"和"不存档退出"按钮。  

## 问题
游戏存在闪退问题，并且地图上单位多起来就会变得不流畅。

## 游戏内画面
![](.\\resources\\screenshot1.png)
![](.\\resources\\screenshot2.png)
![](.\\resources\\screenshot3.png)
