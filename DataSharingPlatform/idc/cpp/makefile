# 开发框架头文件路径。
PUBINCL = -I/DataSharingPlatform/public

# 开发框架cpp文件名，这里直接包含进来，没有采用链接库，是为了方便调试。
PUBCPP = /DataSharingPlatform/public/_public.cpp

################################
# oracle头文件路径
ORAINCL = -I$(ORACLE_HOME)/rdbms/public -I/DataSharingPlatform/public

# oracle库文件路径
ORALIB =  -L$(ORACLE_HOME)/lib -L.

# oracle的oci库
ORALIBS = -lclntsh

# 开发框架oracle的cpp文件名，这里直接包含进来，没有采用链接库，是为了方便调试。
ORACPP = /DataSharingPlatform/public/_ooci.cpp
################################

# 编译参数。
CFLAGS = -g

all:crtsurfdata obtcodetodb obtmindtodb

crtsurfdata:crtsurfdata.cpp
	g++ $(CFLAGS) -o crtsurfdata crtsurfdata.cpp $(PUBINCL) $(PUBCPP) 
	cp -f crtsurfdata ../bin/.

obtcodetodb:obtcodetodb.cpp
	g++ $(CFLAGS) -o obtcodetodb obtcodetodb.cpp $(PUBINCL) $(PUBCPP) $(ORAINCL) $(ORALIB) $(ORALIBS) $(ORACPP) 
	cp obtcodetodb ../bin/.

obtmindtodb:obtmindtodb.cpp idcapp.h idcapp.cpp
	g++ $(CFLAGS) -o obtmindtodb obtmindtodb.cpp idcapp.cpp $(PUBINCL) $(PUBCPP) $(ORAINCL) $(ORALIB) $(ORALIBS) $(ORACPP) 
	cp obtmindtodb ../bin/.

clean:
	rm -f crtsurfdata obtcodetodb obtmindtodb