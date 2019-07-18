ORM-by-C 嵌入式数据库编程
=======

C语言实现基于libdbi仿python ORM数据库操作

前言:

		在用C编写数据库程序，假如使用的是mysql，程序猿需要针对mysql的的库提供的api进行编程，而若使用的是sqlite，程序猿需要针对sqlite库提
	供的api进行编程，不同数据库的API各不相同，带来的不便也可想而知，同时大量的使用sql原生语句会造成代码的结构变得混乱，维护麻烦，尤其是
	涉及到sql组合使用的时候，如果直接使用数据库的API来编写，则在C语言下的函数实现会变得繁杂，就拿select来说都有很多组合使用，要写多个函数，
	多种sql语句来实现不同的select，每个函数中还要声明buf出来用sprintf等函数来构造拼接字符串，万一后面切换到了其他数据库，那应用程序的改动
	就不是一丁半点了.
		之前我在使用Python Django框架开发后台过程中接触到了ORM，在对数据库编程的过程中，基本上不需要构造一句sql语句，切换数据库也是非常方便
	顺手，直接在初始化的时候告诉ORM框架当前使用的数据库引擎是什么就可以了，其他地方逻辑不需要进行更改，ORM框架把sql语句中的命令都被实现成了
	方法，比如加入一个判断，直接调用过滤器中的_and方法或者_or方法，底层会进行构造sql语句。
		由于嵌入式系统中，一般开发都是使用的是C或者C++（C++实现ORM会相对来说会更方便，这里不讨论C++），为了方便嵌入式下C语言编写数据库程序，
	同时也是本人目前正在维护项目所需，解决上述麻烦，为了以后程序的维护性，可读性，方便同事之间更好的维护和扩展，所以想设计一个仿python ORM的
	C语言数据库编程框架，抽象出公共接口，使底层更封闭，上层更统一.

dbc（database container）介绍:

		ORM-by-C项目是基于libdbi库进行实现的，libdbi统一了各个数据库引擎的API，但是没有把SQL与应用隔离，因此dbc作为数据库引擎的容器，隔离SQL，
	开发者通过dbc的方法来对数据库进行操作，开发者在开发应用时，通过传参方式告诉容器选用何种数据库引擎，容器就会被赋能指定引擎的API方法，因项目需
	要，目前实现了sqlite3的数据库封装，对于其他数据库，只需要仿照sqlite3来实现各个数据库的封装，程序猿针对sqlite3编程时，基本不需要再构造sql语
	句，通过sqlite3中封装的insert select update delete 以及过滤器中的and or limit 等来进行操作.

dbc组成:

1、dbc结构体:
	作为模板或者接口，抽象类;
	dbc结构体起到一个namespace的作用（因为insert， select ...这些名词并不是sqlite所有）;

2、dbi_object:

	实现对libdbi的API进行进一步封装，对外统一使用dbi object来操作接口;
	dbi_object 是线程不安全的(后续改进并且增加连接池管理~);

3、sql_sqlite3:

	dbc数据类型的变量，可以理解为继承了抽象类的子类;
	实现sqlite3基于dbi_object的进一步封装，所有函数静态化，对外通过sqlite3结构体来操作:
		- sqlite3.insert
		- sqlite3.select
		- sqlite3.filter.and
		- 具体看dbc.h

编译:

		在编译dbc之前，需要安装libdbi，libsqlite3等库文件。安装数据库引擎的源码库，比如我现在使用的是sqlite3，则需要安装sqlite3源码库，
	因为dbi就是这些源码库的API的一个统一的封装，必须依赖，否则在安装libdriver时，会提示找不到sqlite3的头文件等错误，libdbddriver也必须
	基于数据库引擎源码库以及libdbi安装成功才能进行编译安装.

1、libsqlite3安装方法：（其他数据库如mysql可以到网上搜索方法，大同小异）

	下载最新版sqlite3源码
	wget https://www.sqlite.org/2019/sqlite-autoconf-3270200.tar.gz
	解压文件
	tar zxvf sqlite-autoconf-3270200.tar.gz
	进入到解压后的文件夹中
	cd sqlite-autoconf-3270200
	./configure
	 make
	sudo make install

2、libdbi的安装方法:

	下载最新版libdbi
	wget https://nchc.dl.sourceforge.net/project/libdbi/libdbi/libdbi-0.9.0/libdbi-0.9.0.tar.gz
	解压文件
	tar zxvf libdbi-0.9.0.tar.gz
	进入到解压后的文件夹中
	cd libdbi-0.9.0
	./configure
	make>
	sudo make install

3、liddriver的安装方法：

	下载与libdbi对应的版本
	wget https://jaist.dl.sourceforge.net/project/libdbi-drivers/libdbi-drivers/libdbi-drivers-0.9.0/libdbi-drivers-0.9.0.tar.gz
	解压文件
	tar zxvf libdbi-drivers-0.9.0.tar.gz
	进入到解压目录
	cd libdbi-drivers-0.9.0
	./configure --with-sqlite3 (你也可以选定支持的数据库引擎 ./configure --with-sqlite --with-pgsql)
	make
	sudo make install

		至此，dbi相关的库都已经编译安装完成，默认库位置在/usr/local/lib/和/usr/local/lib/dbd/目录下，分别为libdbi的库目录以及libdriver
	的库目录，/usr/local/lib/dbd/就是dbi_object_new中需要制定的driver路径.

更新说明：

2019年4月10日：

		新增dbc容器，类似于接口，对外程序猿通过创建dbc实例操作数据库，不用关系底层用的是何种数据库，dbc旨在把sql语句全部封装，insert、
	select、update、delete、create、join、order by、where等等sql命令全部封装成函数，比如程序猿需要select的时候 只需要调用dbc.select方法，
	具体的select的sql语句是底层去构造对应数据库的sql语句.
		dbc其实是结构体，结构体中有sql的方法，也就是函数指针，如果要支持sqlite3 或者mysql等，只需要继承dbc结构体，实现结构体中的方法，上层
	使用者在创建一个dbc的时候，传入当前要连接的数据（sqlite3，mysql等），dbc自动选择子类对象，实际上就是定义声明dbc数据类型的sqlite，mysql变
	量，然后实现dbc中的各种方法，这样用户创建一个dbc的时候，就是返回一个对应数据库的dbc类型变量，具体看dbc_connect函数，里面有set_fun的宏

2019年4月12日：

	dbc中增加了事务begin、commit、rollback
	dbc中增加了continuty方法用于作为sql与sql之间的连接符，dbc.query可以批量执行多条sql
	dbc中增加了insert_many、value_add方法用于批量插入

2019年6月18日：

	dbc中增加互斥锁
	dbc中增加sql中的function方法：count，distinct，max，sum
	dbc中增加对结果result的操作方法（取值操作，count操作等
	修改dbi_results_t *dbi_object_get_results函数返回dbi_results_t *改为dbi_results_t类型

2019年7月3日：

	dbi_object增加副本操作,dbi_object_copy_new和dbi_object_copy_delete，通过副本来进行dbc操作，不需要使用dbc.lock来进行保护，但是全局
	副本的话，多线程操作还是需要进行保护的，详见demo中main.c使用

--------------------------------------------------

持续更新中 ...

--------------------------------------------------
