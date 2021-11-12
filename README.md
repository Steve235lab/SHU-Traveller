# SHU-Traveller
上海大学“数据结构与算法基础”课程项目：校园最短路径漫游
Copyright (C) 2021 Steve D. J.. All rights reserved.

使用cpp在MFC框架下编写的带有图形界面的Windows应用程序。仅供学习与参考。

*****程序必须的地图文件"SHU_map_dark.bmp"太大无法放入主目录中，所以放在了Release里面，下载解压（如需解压）后放在项目根目录即可*****

1. 基本信息
采用Floyd最短路径算法实现；地图是绘制在MapDlg对话框控件picture control里面的；路线绘制的代码在MapDlg对话框的OnPaint()函数中；数据文件的读取及对象初始化在MapDlg对话框初始化时完成。

2. 程序存在的一些问题
(1) 该程序没有实现缩放功能;
(2) 该程序的拖动功能是通过对话框自带的滚动条实现的，并不是早先计划的通过响应鼠标事件来实现的；
(3) 因为顶点连通性数据存在部分难以排查更正的错误，所以选择某些地点作为起点/终点时绘制出的路径会有误；
(4) 项目创建时选择类型错误，导致主窗口的客户区没有滚动条，所以后来在主窗口之上又套了一个对话框来实现
因为这个项目归根结底只是一个课程大作业，我需要做的只是在老师面前完成展示，并不需要把它做到完美无缺的程度；同时由于MFC框架本身的一些缺点，我们在完成此程序的主体开发后使用某“学院派最爱”的高级语言又开发了另一款程序，达到了更好的实现效果，在最终演示中该程序因为结构更为简单明晰仅作讲解之用。

3. 给后来人的话
如果你是寻找现成项目的学弟/学妹，那么我非常理解你此时激动的心情，因为我当时也曾寄希望于找到一个别人已经做好的项目然后改一下界面就算完工，认为找到一个这样的项目就算完成了一大半，可惜事情往往没有这么简单。
首先，如果你对MFC应用程序的设计方法并不精通，那么恐怕你也很难在此基础上做出有益的改动。
其次，虽然我在源代码中写了相当多的注释，但是受限于MFC的隐式流程控制，恐怕你也无从看起。
再者，我设计了一个相当复杂的数据结构，如果你真的想了解该程序是如何被一点点构建起来的，可以好好看一下Landmark、Edge、ShortestPath这三个类的定义，也许能窥知一二。
最后，希望我留下的这份开源程序能救你于水火，但是如果你的时间还充裕，最好亲自动手从零开始构建一个完整的程序，这将对你能力的提升大有裨益。
