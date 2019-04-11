# ORM-by-C 嵌入式数据库编程

C语言实现基于libdbi仿python ORM数据库操作
----------------------------------------------
前言: 
*		在用C编写数据库程序，假如使用的是mysql，那么程序猿需要针对mysql的的库提供的api进行编程，
*	而若使用的是sqlite，程序猿需要针对sqlite库提供的api进行编程，大量的使用sql原生语句会
*	造成代码的结构变得混乱，维护麻烦，甚至很多sql可以组合使用，就拿select来说都有很多组合使用，
*	要写多个函数，多种sql语句来实现不同的select，每个函数中还要声明buf出来用sprintf等函数来构
*	造拼接字符串，万一后面切换到了其他数据库，那程序猿的应用程序改动不是一丁半点了。
*		之前在利用Python Django框架开发后台过程中接触到了ORM，在对数据库编程的过程中，基本上
*	不需要构造一句sql语句，sql语句中的命令都被实现成了方法，比如加入一个判断，直接调用过滤器中
*	的_and方法或者_or方法，底层会进行构造sql语句。
*		由于嵌入式系统中，一般开发都是使用的是C或者C++（C++实现ORM会相对来说会更方便，因为C++有模板），
*	为了方便嵌入式下C语言编写数据库程序，同时也是本人目前正在维护项目所需，解决上述麻烦，
*	为了以后程序的维护性，可读性，同时也是同事之间更好的维护和扩展，所以想设计一个仿python ORM的
*	C语言数据库编程框架，让底层更封闭，让上层更统一。
----------------------------------------------
dbc介绍:
*		ORM-by-C项目是基于libdbi库进行实现的，同时编写实现代码思想是编写一个容器，这个容器模版，
*	这个容器能被赋能，当程序猿开发应用时，通过传参方式告诉容器选用何种数据库引擎，容器就会被赋能指定
*	引擎的API方法，所以容器我命名为dbc (database container)。
*		目前简单的实现了sqlite3的数据库封装（项目需要，先实现sqlite3），对于其他数据库，只需要仿照
*	sqlite3来实现各个数据库的封装，程序猿针对sqlite3编程时，基本不需要再构造sql语句，通过sqlite3中
*	封装的insert select update delete 以及过滤器中的and or limit 等来进行操作。
dbc组成:
*	dbc结构体:
*		作为模板或者接口，抽象类；
*		dbc结构体起到一个namespace的作用（因为insert， select ...这些名词并不是sqlite所有）
*	dbi_object:
*		实现对libdbi的API进行进一步封装，对外统一使用dbi object来操作接口；
*		dbi_object 是线程不安全的(后续改进并且增加连接池管理~~)
*	sql_sqlite3:
*		dbc数据类型的变量，可以理解为继承了抽象类的子类；
*		实现sqlite3基于dbi_object的进一步封装，所有函数静态化，对外通过sqlite3结构体来操作：
*			- sqlite3.insert;
*			- sqlite3.select
*			- sqlite3.filter.and
*			- 具体看dbc.h
--------------------------------------------------
编译: 
*		在编译dbc之前，需要安装libdbi，libsqlite3等库文件。
*		安装数据库引擎的源码库，比如我现在使用的是sqlite3，则需要安装sqlite3源码库，因为dbi就是这些源码库
*	的API的一个统一的封装，必须依赖，否则在安装libdriver时，会提示找不到sqlite3的头文件等错误，libdbddriver
*	也必须基于数据库引擎源码库以及libdbi安装成功才能进行编译安装。
*
* libsqlite3安装方法：（其他数据库如mysql可以到网上搜索方法，大同小异）
*	下载最新版sqlite3源码
*	 wget https://www.sqlite.org/2019/sqlite-autoconf-3270200.tar.gz
*	 解压文件
*	 tar zxvf sqlite-autoconf-3270200.tar.gz
*	 进入到解压后的文件夹中
*	 cd sqlite-autoconf-3270200
*	 ./configure
*	 make
*	 sudo make install
*
* libdbi的安装方法:
*	 下载最新版libdbi
*	 wget https://nchc.dl.sourceforge.net/project/libdbi/libdbi/libdbi-0.9.0/libdbi-0.9.0.tar.gz
*	 解压文件
*	 tar zxvf libdbi-0.9.0.tar.gz
*	 进入到解压后的文件夹中
*	 cd libdbi-0.9.0
*	 ./configure
*	 make
*	 sudo make install
*	 
* liddriver的安装方法：
*	 下载与libdbi对应的版本
*	 wget https://jaist.dl.sourceforge.net/project/libdbi-drivers/libdbi-drivers/libdbi-drivers-0.9.0/libdbi-drivers-0.9.0.tar.gz
*	 解压文件
*	 tar zxvf libdbi-drivers-0.9.0.tar.gz
*	 进入到解压目录
*	 cd libdbi-drivers-0.9.0
*	 ./configure --with-sqlite3 (你也可以选定支持的数据库引擎 ./configure --with-sqlite --with-pgsql)
*	 make
*	 sudo make install
*	 
*	至此，dbi相关的库都已经编译安装完成，默认库位置在/usr/local/lib/和/usr/local/lib/dbd/目录下，
*	分别为libdbi的库目录以及libdriver的库目录，/usr/local/lib/dbd/就是dbi_object_new中需要制定的driver路径。
------------------------------------------------
更新说明：
* 2019年4月10日：
*		新增dbc容器，在C++中类似于接口，对外程序猿通过创建dbc实例操作数据库，不用关系底层用的是何种数据库，
*	dbc旨在把sql语句全部封装，insert、select、update、delete、create、join、order by、where等等sql命令全部封装成函数，
*	比如程序猿需要select的时候 只需要调用dbc.select方法，具体的select的sql语句是底层去构造对应数据库的sql语句。
*	dbc其实是结构体，结构体中有sql的方法，也就是函数指针，如果要支持sqlite3 或者mysql等，只需要继承dbc结构体，实现结构体中的方法，
*	上层使用者在创建一个dbc的时候，传入当前要连接的数据（sqlite3，mysql等），dbc自动选择子类对象，实际上就是定义声明dbc数据类型的
*	sqlite，mysql变量，然后实现dbc中的各种方法，这样用户创建一个dbc的时候，就是返回一个对应数据库的dbc类型变量，具体看dbc_connect函数，
*	里面有set_fun的宏，有点类似于C++中的子类重写父类方法。
--------------------------------------------------
后续还会更新，让C针对数据库编程更简便。。。
--------------------------------------------------
--------------------------------------------------
因本人水平有限，欢迎各位提供建议和指导，共同打造这个C版的"ORM" !
--------------------------------------------------
