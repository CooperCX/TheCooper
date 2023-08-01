## GDB
* GDB（GNU Debugger）是由DNU提供的调试工具，和GCC组成一套完整的开发环境
* 准备工作：在调试前，编译选项：关掉编译优化-O，打开编译调试-g，打开所有警告-Wall
    * -g: 在可执行文件中加入源文件的信息，必须保障GDB可以找到源文件
* 命令：
```
    启动：gdb 可执行程序
    退出：quit

    设置断点：b/break 行号/函数名/文件名:行号/文件名:函数名
    删除断点：delete 断点编号
    查看断点：info break
    设置条件断点：b/break 行号 if 条件

    运行：r/run
    继续：c
    向下执行：n, s

    变量：p
    变量类型：ptype

    查看函数栈：bt
    选择栈帧：f
    查看core：gdb 可执行文件 core文件
```