# Description 简介

一个可以生成gms1的timeline文件的自创语言的编译器。

自创语言的规则：(TODO)

# Compile Requires Recommendation 编译需求建议

g++ 9.2.0
flex 2.6.4
bison 3.7.4

# Compile Method 编译方法

在当前文件夹下开启命令行，输入make，即可编译生成可执行文件build/GMAM.exe。

# Running Arguments 运行参数

至少需要一个参数。

GMAM.exe InputFiles（空格隔开） (-o OutputFile)

例，在当前文件夹下开启命令行，并输入：

./build/GMAM.exe ./input/avoidance.tl -o C:/Users/XX/Documents/GameMaker/Projects/XX.gmx/timelines/XX.timeline.gmx

目前测试，可以同时开启gms1同时使用本程序，且使用完毕后gms1内编译即时有效，但若试图在gms1中查看更改后的timeline，并不会刷新。
不保证更多地有关同时使用的有效性。