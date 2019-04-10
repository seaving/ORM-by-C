# dbi
C语言实现基于libdbi仿python ORM数据库操作

先说说libdbi的好处：
	在用C编写数据库程序，当使用的是mysql，那么程序猿需要针对mysql的的库提供的api进行数据操作，
	当使用的是sqlite，程序猿需要针对sqlite库提供的api进行数据操作，也就是说，不同的数据库提供的api
	是不一样的，同时大量的使用sql原生语句会造成代码的结构变得混乱，维护麻烦。
	libdbi支持很多数据库(msyql sqlite sqlite3 PostgreSQL ...)，它把数据库的api统一封装，对外提供dbi的接口，
	程序猿在操作通过dbi来操作数据库，只需要告诉dbi使用的是啥数据库，dbi会根据当前使用的数据库调用对于的api，
	而不管数据库更换到何种，对于程序猿来说，只需要关系的是dpi的接口，剩下的交给dbi底层去干了。

不足：	
	我把dbi的提供的API基本浏览了一遍，dbi其实只是对数据库的统一封装而已，并没有ORM（其实C语言不存在ORM，因为C语言是面向过程的）,
	上层应用程序还是需要造sql语句。

------------------------------------------------
之前在用python开发后台过程中接触到了ORM，一个字爽，太方便了。在操作数据库的过程中，基本上不需要构造一句sql语句，sql语句中的命令都被实现成了方法，
比如我要加一个判断，直接调用过滤器中的and方法或者or方法，底层会进行构造sql语句。

由于嵌入式系统中，一般开发都是使用的是C或者C++（C++实现ORM会更方便，能做到真正意义上的ORM），C语言是面向过程的，无奈，考虑过用宏来和结构体来做关系映射，
但是使用起来并不是特别方便（source insight 结构体成员可以自动补全，如果用宏来生成，那source insight做不到自动补全，编程不方便）

为了赶项目进度，就把关系映射实现放弃了，直接做简单版本的。
目前简单的实现了sqlite3的数据库封装（项目需要，先实现sqlite3），对于其他数据库，只需要仿照sqlite3来实现各个数据库的封装。
程序猿在操作sqlite3时，基本不需要再构造sql语句，通过sqlite3中封装的insert select update delete 以及过滤器中的and or limit 等来进行操作
--------------------------------------------------
dbi_object 实现对libdbi的API进行进一步封装，对外统一使用dbi object来操作接口
sql_sqlite3 实现sqlite3基于dbi_object的进一步封装，所有函数静态化，对外通过sqlite3结构体来操作：
	sqlite3.insert， sqlite3.select, sqlite3.filter.and ...，
	sqlite3结构体起到一个namespace的作用（因为insert， select ...这些名词并不是sqlite所有）
--------------------------------------------------
现在实现的是简单版本，只是实现了最基本的增删改查，复杂的像join，like，have，create等还未实现，但是实现起来也并不复杂，因为本质是构造字符串
--------------------------------------------------
dbi_object 是线程不安全的(改进空间还有很多啊~~)
--------------------------------------------------
2019年4月10日：
新增dbc容器，在C++中类似于接口，对外程序猿通过创建dbc实例操作数据库，不用关系底层用的是何种数据库，
dbc旨在把sql语句全部封装，insert、select、update、delete、create、join、order by、where等等sql命令全部封装成函数，
程序猿需要select的时候 只需要调用dbc.select方法，具体的select的sql语句是底层去构造对应数据库的sql语句
--------------------------------------------------
先git commit一下吧，虽然是初版，但是后续还会更新，让C针对数据库编程更简便。。。

