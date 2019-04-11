# ORM-by-C
C语言实现基于libdbi仿python ORM数据库操作
----------------------------------------------
目的，方便嵌入式下C语言编写数据库程序
----------------------------------------------
先说说libdbi的好处：
	在用C编写数据库程序，当使用的是mysql，那么程序猿需要针对mysql的的库提供的api进行数据操作，
	当使用的是sqlite，程序猿需要针对sqlite库提供的api进行数据操作，也就是说，不同的数据库提供的api
	是不一样的，同时大量的使用sql原生语句会造成代码的结构变得混乱，维护麻烦。
	libdbi支持很多数据库(msyql sqlite sqlite3 PostgreSQL ...)，它把数据库的api统一封装，对外提供dbi的接口，
	程序猿在操作通过dbi来操作数据库，只需要告诉dbi使用的是啥数据库，dbi会根据当前使用的数据库调用对于的api，
	而不管数据库更换到何种，对于程序猿来说，只需要关系的是dpi的接口，剩下的交给dbi底层去干了
	(实际上dbi的下一层是libdriver，dbi是基于动态库来实现的高度模块化框架，每个数据库引擎被进一步封装成各自的libdriver，也就是dbd的驱动，
	dbi通过动态加载dbd来选择并操作用户需要操作的数据库)。

不足：	
	我把dbi的提供的API基本浏览了一遍，dbi其实只是对数据库的统一封装而已，并没有ORM（其实C语言不存在ORM，因为C语言是面向过程的）,
	上层应用程序还是需要造sql语句。
------------------------------------------------
之前在用python开发后台过程中接触到了ORM，在操作数据库的过程中，基本上不需要构造一句sql语句，sql语句中的命令都被实现成了方法，
比如我要加一个判断，直接调用过滤器中的and方法或者or方法，底层会进行构造sql语句。

由于嵌入式系统中，一般开发都是使用的是C或者C++（C++实现ORM会更方便，因为C++有模板，能做到真正意义上的ORM），C语言是面向过程的，无奈，考虑过用宏来和结构体来做关系映射，
但是使用起来并不是特别方便（source insight 结构体成员可以自动补全，如果用宏来生成，那source insight做不到自动补全，编程不方便）

目前简单的实现了sqlite3的数据库封装（项目需要，先实现sqlite3），对于其他数据库，只需要仿照sqlite3来实现各个数据库的封装。
程序猿在操作sqlite3时，基本不需要再构造sql语句，通过sqlite3中封装的insert select update delete 以及过滤器中的and or limit 等来进行操作
------------------------------------------------
dbi_object 实现对libdbi的API进行进一步封装，对外统一使用dbi object来操作接口
sql_sqlite3 实现sqlite3基于dbi_object的进一步封装，所有函数静态化，对外通过sqlite3结构体来操作：
	sqlite3.insert， sqlite3.select, sqlite3.filter.and ...，
	sqlite3结构体起到一个namespace的作用（因为insert， select ...这些名词并不是sqlite所有）
--------------------------------------------------
编译:
	在编译dbc之前，需要安装libdbi，libsqlite3
安装数据库引擎的源码库，比如我现在使用的是sqlite3，那就要安装sqlite3源码库，因为dbi就是这些源码库的api的一个统一的封装，必须依赖，否则在安装libdriver时，会提示找不到sqlite3的头文件等
libsqlite3安装方法：
	wget https://www.sqlite.org/2019/sqlite-autoconf-3270200.tar.gz 下载最新版sqlite3源码
	tar zxvf sqlite-autoconf-3270200.tar.gz 解压文件
	cd sqlite-autoconf-3270200 进入到解压后的文件夹中
	./configure
	make
	sudo make install
（其他数据库如mysql可以到网上搜索方法，大同小异）

libdbi的安装方法:
	wget https://nchc.dl.sourceforge.net/project/libdbi/libdbi/libdbi-0.9.0/libdbi-0.9.0.tar.gz 下载最新版libdbi
	tar zxvf libdbi-0.9.0.tar.gz 解压文件
	cd libdbi-0.9.0 进入到解压后的文件夹中
	./configure
	make
	sudo make install

至此，libdbi库编译安装完毕，接着编译liddriver
	wget https://jaist.dl.sourceforge.net/project/libdbi-drivers/libdbi-drivers/libdbi-drivers-0.9.0/libdbi-drivers-0.9.0.tar.gz 下载与libdbi对应的版本
	tar zxvf libdbi-drivers-0.9.0.tar.gz 解压文件
	cd libdbi-drivers-0.9.0 进入到解压目录
	./configure --with-sqlite3 (你也可以选定支持的数据库引擎 ./configure --with-sqlite --with-pgsql)
	make
	sudo make install
至此，dbi相关的库都已经编译安装完成，默认库位置在/usr/local/lib/和/usr/local/lib/dbd/目录下，分别为libdbi的库目录以及libdriver的库目录，/usr/local/lib/dbd/就是dbi_object_new中需要制定的driver路径
------------------------------------------------
--------------------------------------------------
dbi_object 是线程不安全的(后续改进并且增加连接池管理~~)
--------------------------------------------------
2019年4月10日：
新增dbc容器，在C++中类似于接口，对外程序猿通过创建dbc实例操作数据库，不用关系底层用的是何种数据库，
dbc旨在把sql语句全部封装，insert、select、update、delete、create、join、order by、where等等sql命令全部封装成函数，
程序猿需要select的时候 只需要调用dbc.select方法，具体的select的sql语句是底层去构造对应数据库的sql语句.
dbc其实是结构体，结构体中有sql的方法，也就是函数指针，如果要支持sqlite3 或者mysql等，只需要继承dbc结构体，实现结构体中的方法，
上层使用者在new 一个dbc的时候，传入当前要连接的数据（sqlite3，mysql等），dbc自动选择子类对象（实际上就是定义声明dbc数据类型的sqlite，mysql变量，然后实现dbc中的各种方法，
这样用户new一个dbc的时候，就是返回一个对应数据库的dbc类型变量，具体看dbc_connect函数，里面有set_fun的宏，有点类似于C++中的子类重写父类方法）。
--------------------------------------------------
先git commit一下吧，虽然是初版，但是后续还会更新，让C针对数据库编程更简便。。。

