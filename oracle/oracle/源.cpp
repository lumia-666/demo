/***************************����oracle�����ṩOCCI��ʽ�������ݿ�*******************/
//�����Ŀ�ľ�����֤makefile��oracle��ͷ�ļ���lib�ļ�·���Ƿ���ȷ��  
#define WIN32COMMON //���⺯���ض������  
#include <iostream>  
#include <occi.h>  
#include <math.h>
#include <sstream>
#include <float.h>
#include <time.h>
#include <string.h>
using namespace std;
using namespace oracle::occi;
const char** value;

class A {
public:
	A& f1(int b)
	{
		a1 = b;
		return *this;
	}
	A& f2(int b)
	{
		a2 = b;
		return *this;
	}
	A& f3(int b)
	{
		a2 = b;
		return *this;
	}
private:
	int a1;
	int a2;
};

float f() {
	auto str = "123456780912";
	auto f = atof(str);
	auto f2 = 123456780912.0;
	return f;
}

void f2() {
	int a = 2;
	auto b = to_string(a);
	value[0] = b.c_str();
	cout << value[0] << endl;
}

void f3(void* p) {
	auto ptr = (char*)p + 4;
	int c = 0;
	memcpy(&c, ptr, 4);
	cout << c << endl;
}

void f4(char** c) {
	char s[3] = "12";
	*c = s;
}

/*
	�˲���������Ҫ�ǲ���������ѯ����ѯ������¼��������ѯ1��εĺ�ʱʱ��
*/
bool case1(Connection* conn)
{
	Statement* stmt = conn->createStatement();
	try
	{
		char szSQL[1024] = {};
		ResultSet* rs = nullptr;
		stmt->setAutoCommit(false);
		for (int i = 0; i < 10000; ++i)
		{
			sprintf(szSQL, "SELECT col1 FROM tt where col1 = %d", i + 1);
			rs = stmt->executeQuery(szSQL);
			rs->next();
			stmt->closeResultSet(rs);
		}
		conn->terminateStatement(stmt);
	}
	catch (SQLException e)
	{
		cout << e.what() << endl;
		return false;
	}
}

/*
	�˲���������Ҫ�ǲ���insert������¼����������1��εĺ�ʱʱ��
*/
bool case3(Connection* conn)
{
	Statement* stmt = nullptr;
	try
	{
		const int ROW_NUM = 1;
		stmt = conn->createStatement("insert into tt values(:1, :2, :3, :4)");
		cout << stmt->getAutoCommit() << endl;
		stmt->setAutoCommit(false);
		for (int index = 0; index < 10000; ++index)
		{
			stmt->setInt(1, index + 1);
			stmt->setString(2, "true");
			stmt->setString(3, "testNew");
			stmt->setString(4, "testNew");
			stmt->executeUpdate();
		}
		conn->terminateStatement(stmt);
	}
	catch (SQLException e)
	{
		cout << e.what() << endl;
		conn->terminateStatement(stmt);
		return false;
	}
}

/*
PGTransactionStatusType PQtransactionStatus(const PGconn *conn);
PQTRANS_IDLE��ʾ���Ӵ��ڿ���״̬��û��ִ���κ�����
PQTRANS_ACTIVE��ʾ���Ӵ���һ�������У����Ҹ���������ִ�����
PQTRANS_INTRANS��ʾ����һ�������У��������ڿ���״̬��
PQTRANS_INERROR��ʾ����һ�������У�����������������󣬴��ڿ���״̬���ȴ��û���һ��COMMIT��ROLLBACK��������������
PQTRANS_UNKNOWN��ʾ���ݿ������ѱ���ֹ��ֻ�����û�������һ����ѯ�����ݿ⣬���������ѯ��Ȼ����ִ�е�����£��Ż᷵��PQTRANS_ACTIVE��
*/
void f(int index, void* s, sb4 size, ub2* length)
{
	auto p = (char*)s;
	int i = 100;
	while (i--)
	{
		char tmp[30];
		memcpy(tmp, p + size, 30);
		*tmp = (char)'8';
		//auto st = strstr(tmp, "\0");
		cout << i << '\t' << tmp << endl;
		p += size;
	}

}

inline void tolower(char* ch)
{
	int len = strlen(ch);
	for (int i = 0; i < len; ++i)
	{
		if (ch[i] >= 'A' && ch[i] <= 'Z')
		{
			ch[i] += 32;
		}
	}
}

inline bool getFirstWord(char* ch, char* out)
{
	int len = strlen(ch);
	int index = 0;
	while (true)
	{
		if (index == len)
		{
			return false;
		}
		if (ch[index] != ' ')
		{
			break;
		}
		++index;
	}
	for (int i = index; i < len; ++i)
	{
		if (ch[i] == ' ' && i - index < 10)
		{
			memcpy(out, ch + index, i - index);
			tolower(out);
			return true;
		}
	}
	return false;
}

inline bool isDDL(char* sql)
{
	char buf[10];
	if (!getFirstWord(sql, buf))
	{
		return false;
	}
	if ((strcmp("create", buf) == 0) ||
		(strcmp("alter", buf) == 0) ||
		(strcmp("drop", buf) == 0) ||
		(strcmp("truncate", buf) == 0))
		return true;
	else
		return false;
}

void test_toString()
{
	auto cnt = 1000000;
	while (cnt--)
	{
		auto a = 12333333.234355345353434657;
		auto b = to_string(a);
	}
}

class Data {
public:
	void f() {
		a[0] = 123;
	}
private:
	char a[100];
};

int main()
{
	char dd1[100];
	char dd2[100];
	memcpy(dd2, dd1, 100);
	dd1[0] = 12;
	A aa;
	aa.f1(1).f2(2).f3(3);
	char cc123[32];
	sprintf(cc123, "%d", 3123);
	cout << cc123 << endl;
	sprintf(cc123, "%d", 314);
	cout << cc123 << endl;
	const char* buf1 = "  TruncAte 5678";
	char buf2[5];
	cout << isDDL((char*)buf1) << endl;
	cout << buf2 << endl;
	char** ccc = new char* [10];
	cout << (ccc[0] == nullptr) << endl;
	float valFloat[8] = {};
	float ff1 = 1.01;
	double tmpFloat = 0;
	for (int i = 0; i < 8; ++i)
	{
		auto ptr1 = (char*)valFloat + i * 4;

		memcpy(ptr1, &ff1, 4);
	}
	cout << atoi("") << endl;
	long long a33 = 121;
	char c33;
	memcpy(&c33, &a33, 1);
	char* t = nullptr;
	f4(&t);
	cout << t << endl;
	int bbb[2];
	bbb[0] = 1;
	bbb[1] = 2;
	f3(bbb);
	value = new const char* [4];
	f2();
	cout << value[0] << endl;
	auto dd = 3.123;
	auto ddd = 8.123;
	ostringstream strStream;
	strStream << dd;
	strStream << ddd;
	auto abb = strStream.str();
	cout << strStream.str() << endl;  // 6.7592
	long long a22 = 12213213123123;
	cout << a22 << endl;
	int* p = new int(888);
	int* p22 = new int;
	memcpy(p22, p, 1);
	cout << *p22 << endl;
	cout << *p << endl;
	cout << *(p + 4) << endl;
	auto p2 = new char[0];
	A a;
	//����OCCI�����Ļ���  
	Environment* env = Environment::createEnvironment();
	if (NULL == env) {
		printf("createEnvironment error.\n");
		return -1;
	}
	else
		cout << "success" << endl;


	string name = "system";
	string pass = "123";
	string srvName = "localhost:1521/orcl";

	Connection* conn = nullptr;
	try {
		//�������ݿ�����  
		conn = env->createConnection(name, pass, srvName);//�û��������룬���ݿ���  
		if (NULL == conn) {
			printf("createConnection error.\n");
			return -1;
		}
		else
			cout << "conn success" << endl;

		//  ���ݲ���,����Statement����  
		Statement* pStmt = NULL;    // Statement����  
		pStmt = conn->createStatement();
		if (NULL == pStmt) {
			printf("createStatement error.\n");
			return -1;
		}
		pStmt->setAutoCommit(false);
		//pStmt->executeUpdate("DECLARE num NUMBER; \
			//					BEGIN \
			//					SELECT \
			//						count( 1 ) INTO num \
			//					FROM \
			//						user_tables \
			//					WHERE \
			//						table_name = upper( 'tbl_01' ); \
			//					IF \
			//						num > 0 THEN \
			//						execute IMMEDIATE 'drop table tbl_01'; \
			//					END IF; \
			//					END;");
			//// ��ѯ���ݿ�ʱ��    
			//std::string strTemp;
			//auto pRs = pStmt->executeUpdate(
			//	"select* from tbl_01");
			//cout << pRs << endl;
			//ResultSet* pRs = pStmt->executeQuery(
			//	"insert into tbl_01 values (4,'4')");
			//ResultSet* pRs = pStmt->executeQuery("create table tbl_10(col1 number)");
		//try
		//{
		//ResultSet* pRs = pStmt->executeQuery("select *from tbl_01 where col1 = 11");
		////ResultSet* pRs = pStmt->executeQuery("select* from tbl_01");
		//while (pRs->next(1)) {
		//	//auto a = pRs->getUInt(2);
		//	auto b = pRs->getFloat(2);
		//	//cout << a << endl;
		//	cout << b << endl;
		//	//auto strTemp = pRs->getString(2);
		//	//printf("%d,%s.\n", a, strTemp.c_str());
		//	// int����ȡֵ��getInt()    
		//}
		//}
		//catch (SQLException e)
		//{
		//	cout << e.what() << endl;
		//}
		//auto pRs = pStmt->executeUpdate("insert into tbl_01 values(8,'2')");
		//auto qwe = pStmt->executeQuery("select *from tbl_01");
		//auto pRs2 = pStmt->executeUpdate("insert into tbl_01 values(9,'2')");
		//pStmt->closeResultSet(pRs);

		////--------����---------    
		//// ָ��DMLΪ�Զ��ύ    
		//pStmt->setAutoCommit(TRUE);
		//// ����ִ�е�SQL���    
		////pStmt->setSQL("INSERT INTO TA (ID, NAME) VALUES (1, 'ZS')");    
		//pStmt->setSQL("INSERT INTO STUDENT_INFO (sno, sname, sex) VALUES (1, 'lumia', 'm')");

		//// ִ��SQL���    
		//unsigned int nRet = pStmt->executeUpdate();
		//if (nRet == 0) {
		//	printf("executeUpdate insert error.\n");
		//}

		//auto t1 = clock();
		//case3(conn);
		//cout << "case3 use " << clock() - t1 << endl;
		//pStmt->executeUpdate("");
		//case1(conn);
		//cout << "case1 use " << clock() - t1 << endl;
		/*
			����������ѯ

		*/
		//Statement* stmt = conn->createStatement(
		//	"select * from TBL");

		//auto rest = stmt->getResultSet();
		//char dnames[4][20];
		//ub2 dnameLen[4];


		//for (int i = 0; i < 4; i++)
		//	dnameLen[i] = 20;
		// ÿ�β����������������123��456��789��1089
		// ÿ�β����������������1234��5678��91089
		//int ids[6];
		//ub2 idLen[6];
		//stmt->setPrefetchRowCount(3);
		//ub2 idLen[4] = { sizeof(ids[0]), sizeof(ids[1]),sizeof(ids[2]),sizeof(ids[3]) };
		//auto pRs = stmt->executeQuery();
		//pRs->setDataBuffer(1, ids, OCCIINT, 4, idLen);
		//pRs->setDataBuffer(1, ids, OCCIINT, 8, idLen);
		//pRs->setDataBuffer(2, dnames, OCCI_SQLT_STR, 20, dnameLen);
		//while (pRs->next()) {
		//	auto a = pRs->getInt(1);
		//	auto strTemp = pRs->getString(2);
		//	//printf("%d\n", pRs->getNumArrayRows());//4 4 2
		//	 printf("%d,%s\n", a, strTemp.c_str());//4 4 2
		//	auto c = pRs->getObject(1);
		//}
		////cout << stmt->getUpdateCount() << endl;
		////cout << (stmt->getResultSet() == NULL) << endl;
		////stmt->executeUpdate("insert into tbl_01 values(1,'2')");
		//cout << stmt->getUpdateCount() << endl;
		//auto rs = stmt->getResultSet();
		//rs->next(1);
		//auto a = rs->getInt(1);
		//auto strTemp = rs->getString(2);
		//printf("%d,%s\n", a, strTemp.c_str());//4 4 2
		//����getResultSet��executeQuery��ȡ�Ƿ���ͬһ��ResultSet��������



		/*
			����ռλ����ѯ
		*/
		//Statement* stmt = conn->createStatement(
		//	"");
		//auto sql = stmt->getSQL();
		//char dnames[4][10];
		//ub2 dnameLen[4];


		//for (int i = 0; i < 4; i++)
		//	dnameLen[i] = 10;

		//int ids1[4];
		//ub2 idLen1[4] = {4};
		//// ÿ�β����������������123��456��789��1089
		//// ÿ�β����������������1234��5678��91089
		//int ids[4] = {  };
		//ub2 idLen[4] = { 4,4,4,4 };
		////stmt->setDataBuffer(1, ids, OCCIINT, 4, idLen);
		//auto pRs = stmt->executeQuery("select * from tbl_01");
		//pRs->setDataBuffer(1, ids1, OCCIINT, sizeof(ids1[0]), idLen1);
		//pRs->setDataBuffer(2, dnames, OCCI_SQLT_STR, 10, dnameLen);
		////pRs->setDataBuffer(2, dnames, OCCI_SQLT_STR, 10, dnameLen);//��ȡ����ֵ���ضϣ����ĸ�����Size of the data buffer. For array fetches, it is the size of each element of the data items.
		//while (pRs->next(3)) {
		//	//auto a = pRs->getInt(1);
		//	//auto strTemp = pRs->getString(2);
		//	printf("%d\n", pRs->getNumArrayRows());//4 4 2
		//	// int����ȡֵ��getInt()    
		//}

		///*��������д�����*/
		//Statement* stmt = conn->createStatement(
		//	"insert into tbl_01 values(:1,:2)");

		//auto dnames = new char*[8];
		//for (int i = 0; i < 8; ++i)
		//{
		//	dnames[i] = new char[10];
		//	char tmp[10] = "123456789";
		//	memcpy(dnames[i], tmp, 10);
		//	cout << &(dnames[i][0]) << endl;
		//	cout << &(dnames[i][1]) << endl;
		//	cout << &(dnames[i][2]) << endl;
		//	cout << &(dnames[i][3]) << endl;
		//	cout << &(dnames[i][4]) << endl;
		//	cout << &(dnames[i][5]) << endl;
		//	cout << &(dnames[i][6]) << endl;
		//	cout << &(dnames[i][7]) << endl;
		//	cout << &(dnames[i][8]) << endl;
		//	cout << &(dnames[i][9]) << endl;
		//}
		//ub2 dnameLen[8];
		//dnameLen[0] = 10;
		//dnameLen[1] = 10;
		//dnameLen[2] = 10;
		//dnameLen[3] = 10;
		//dnameLen[4] = 10;
		//dnameLen[5] = 10;
		//dnameLen[6] = 10;
		//dnameLen[7] = 10;
		//auto ids = new double[8]{ 73693646, 3.12312323};
		//ub2 idLen[8] = { 8,8,8,8,8,8,8,8};
		////f(1, dnames, 30, dnameLen);
		//stmt->setDataBuffer(1, ids, OCCIFLOAT, 8, idLen);
		////stmt->setDataBuffer(1, ids, OCCIINT, 4, idLen);
		//stmt->setDataBuffer(2, dnames, OCCI_SQLT_STR, 10, dnameLen);
		//delete []ids;
		////delete dnames[0];
		////delete dnames[1];
		////delete dnames[2];
		////delete dnames[3];
		////delete dnames[4];
		////delete dnames[5];
		////delete dnames[6];
		////delete dnames[7];
		////delete []dnames;
		//stmt->executeArrayUpdate(8);
		/*��������д��*/
		Statement* stmt = conn->createStatement(
			"insert into TBL_01 values(:1,2)");
		//auto status = stmt->getUpdateCount();

		{
			Number num[8] = { 1,2,3,4.3,5,6.66,7,8 };
			char dnames[8][10] = { "123","112","113","114","115","116","117","118" };
			ub2 dnameLen[8];
			int ids[8] = { 1,2,3,4,5,6,7,8 };
			ub2 idLen[8];
			for (int i = 0; i < 8; ++i)
			{
				dnameLen[i] = 10;
				idLen[i] = sizeof(Number);
			}
			stmt->setDataBuffer(1, num, OCCI_SQLT_NUM, sizeof(Number), idLen);
			stmt->setInt(1, 8);
			//stmt->setDataBuffer(2, dnames, OCCI_SQLT_CHR, 10, dnameLen);
		}
		stmt->executeUpdate();
		//stmt->executeArrayUpdate(8);
		cout << stmt->getUpdateCount() << endl;
		cout << (stmt->getResultSet() == NULL) << endl;
		cout << stmt->status() << endl;


		//����status
		//Statement* stmt = conn->createStatement();
		//stmt->setSQL("abc");
		//auto status = stmt->status();
		//auto cnt = stmt->getUpdateCount();


		//����setInt
		//Statement* stmt2 = conn->createStatement(
		//	"insert into tbl_01 values(:2,:1)");
		//stmt2->setString(1, "8");
		//stmt2->setInt(2, 9);
		////stmt->setDataBuffer(1, ids, OCCIINT, 4, idLen);
		//stmt2->executeArrayUpdate(4);
		// ��ֹStatement����    


		////����setDataBuffer��setInt���ִ��
		//Statement* stmt = conn->createStatement(
		//	"insert into tbl_01 values(:1,:2)");
		//{
		//	char dnames[8][10] = { "123","112","113","114","115","116","117","118" };
		//	ub2 dnameLen[8];
		//	dnameLen[0] = 4;
		//	dnameLen[1] = 4;
		//	int ids[8] = { 2, 5 };
		//	ub2 idLen[2] = { 4,4 };
		//	//f(1, dnames, 30, dnameLen);
		//	stmt->setInt(1, 9);

		//	stmt->setDataBuffer(2, dnames, OCCI_SQLT_STR, 10, dnameLen);
		//}
		//stmt->executeArrayUpdate(2);
		//auto status = stmt->getUpdateCount();
		//auto stas = stmt->getResultSet();
		//stmt->executeArrayUpdate(5);


		//���Զ���delete
		//Statement* stmt = conn->createStatement("select col1 from tbl_01");
		//try
		//{
		//	constexpr int ROW_NUM = 6;
		//	int valInt[ROW_NUM];
		//	ub2 lenInt[ROW_NUM] = {4,4,4,4,4,4};
		//	auto rs = stmt->executeQuery();
		//	rs->setDataBuffer(1, valInt, OCCIINT, sizeof(int), lenInt);
		//	int retNum = 0;
		//	while (rs->next(3) != ResultSet::Status::END_OF_FETCH)
		//	{
		//	}
		//	for (int i = 0; i < ROW_NUM; ++i)
		//	{
		//		if (lenInt[i] > 0)
		//		{
		//			++retNum;
		//		}
		//	}
		//	stmt->closeResultSet(rs);
		//	conn->terminateStatement(stmt);
		//	if (retNum != ROW_NUM)
		//	{
		//		std::cout << "case1 test get multiple int normally failed " << std::endl;
		//		return false;
		//	}
		//	std::cout << "case1 test get multiple int normally success " << std::endl;
		//	return true;
		//}
		//catch (SQLException e)
		//{
		//	std::cout << "case1 test get multiple int normally failed, " << e.what() << std::endl;
		//	conn->terminateStatement(stmt);
		//	return false;
		//}

		//����select�᲻���ύ����
		//Statement* stmt = conn->createStatement();

		//try
		//{
		//	stmt->executeUpdate("insert into tbl_01 value(1,'1')");
		//}
		//catch (SQLException)
		//{

		//}
		//cout << stmt->getSQL() << endl;
		//stmt->executeUpdate("insert into tbl_01 values(3,'3')");
		//ResultSet* rs = nullptr;
		//stmt->closeResultSet(rs);

		//try
		//{
		//	Statement* stmt = conn->createStatement();
		//	stmt->executeUpdate("insert into tbl_01 value(2,'2')");
		//}
		//catch (SQLException)
		//{

		//}
		//try
		//{
		//	Statement* stmt = conn->createStatement();
		//	stmt->executeUpdate("insert into tbl_01 values(3,'3')");
		//}
		//catch (SQLException)
		//{

		//}

		//����Ԥȡ����

		//Statement* stmt = conn->createStatement();
		//stmt->setPrefetchRowCount(10);
		//auto rs = stmt->executeQuery("select *from TBL");
		//while (rs->next())
		//{
		//	cout << rs->getInt(1) << endl;;
		//	cout << rs->getString(2) << endl;
		//	cout << rs->getInt(1) << endl;;
		//	cout << rs->getString(2) << endl;
		//	cout << rs->getInt(1) << endl;;
		//	cout << rs->getString(2) << endl;
		//}
		//Number n{};
		//n.shift(0);
		//n.fromText(env,"1234", "9999");
		//cout << (int)n << endl;
		//n.setNull();
		//n += 3;
		//float ff = n;
		//cout << (float)n.prec(9) << endl;
		//cout<<n.toText(env,"9GG9D99EEEE")<<endl;
		//float ff = n % n2;
		//float n2 = n.prec(0);

		//Date d{ env };
		//d.setDate(9999, 10, 1, 1, 1, 1);
		//auto dd = d.addMonths(3);
		////int year = 0;
		////unsigned int month, day, hour, minute, second = 0;
		////dd.getDate(year, month, day, hour, minute, second);
		////Date d{env,1,1,1,0,1,1};
		////auto ss1 = d.toText("mi");
		////d.fromText("1997/07/10 08:48:08","YYYY/MM/DD hh:mi:ss");
		////auto ss = d.toText("mi");

		////Date d2{ env,2,2,2,2,2,2 };
		////auto interval = d.daysBetween(d2);
		////auto ret1 = interval.getSecond();

		//IntervalDS ds2{};
		//ds2.set(1, 1, 1, 1, 1);
		//Date dt0{ env, 1997, 12, 30, 10, 48, 8 }; // test 28 day month
		//auto ret0 = dt0.toZone("ADT", "AST");
		//int year = 0;
		//unsigned int month, day, hour, min, sec = 0;
		//ret0.getDate(year, month, day, hour, min, sec);

		conn->terminateStatement(pStmt);

		//  �ر�����  
		env->terminateConnection(conn);
		// pEnv->terminateConnection(pConn);    
	}
	catch (SQLException e)
	{
		cout << e.what() << endl;
		system("pause");
	}

	//env->terminateConnection(conn);
	// �ͷ�OCCI�����Ļ���    
	Environment::terminateEnvironment(env);
	cout << "end!" << endl;
	system("pause");
	return 0;
}