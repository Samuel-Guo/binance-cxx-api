#include <iostream>
#include <json/json.h>
#include <map>
#include <string>
#include <vector>
#include <fstream>
//#include <cctype>
#include "binance_logger.h"

#include "dataGetor.h"
#include "timeStringConvert.h"
const std::string verString =
"V1.0"
;

//Server serverUs("https://api.binance.us");
//Server serverCn;
//Server& server = serverCn;

using namespace binance;
using namespace std;

map<long, map<string, double> > klinesCache;

int main(int argc, char* argv[])
{
	ofstream  myfile("he.txt");

	bool b = getenv("FREEZE_ON_ERROR");

	Logger::set_debug_level(1);
	Logger::set_debug_logfp(stdout);

	system("echo ALL_PROXY = $ALL_PROXY");

	srand(time(NULL));
	
	time_t startTime = time(NULL);

	cout << "----start at----" << ctime(&startTime) << verString << endl;

	
	//cout << "<>Server::getTime<>" << endl;
	//Json::Value result;

	//server.getTime(result);


	//Json::Value tl = result["serverTime"];
	//if (!tl.isNull())
	//{
	//	cout << "serverTime = " << result["serverTime"] << endl;

	//}
	//else
	//{
	//	cerr << "result =" << result << endl;
	//	cerr << "<>Server::getTime<> failed" << endl;
	//}

	dataGetor getor;
	for (int i = 1; i < argc-1; ++i)
	{
		cout << argv[i] << " - " << argv[i + 1] << endl;
		if (strcasecmp(argv[i], "-s")==0)
		{
			getor.symbol =  argv[i + 1];
		}
		else if (strcasecmp(argv[i], "-st") == 0)
		{
			getor.startTime = timeConvertor::str2time(argv[i + 1],"%Y%m%d-%H%M%S");
		}
		else if (strcasecmp(argv[i], "-et") == 0)
		{
			getor.endTime = timeConvertor::str2time(argv[i + 1], "%Y%m%d-%H%M%S");
		}
		else if (strcasecmp(argv[i], "-i") == 0)
		{
			getor.interval = argv[i + 1];
		}
	}

	getor.startTime -= 3600 * 8;
	getor.endTime -= 3600 * 8;

	auto data =getor.getData();

	cout << "@@data.size()@@" << data.size() << endl;
	int count = 1;
	for (auto& item : data)
	{
		cout << count <<"\t" << timeConvertor::ShowDateTime(item.datatime) << "\t" << item.datatime << "\t" << item.open << endl;
		myfile << count << "\t" << timeConvertor::ShowDateTime(item.datatime) << "\t" << item.datatime << "\t" << item.open << endl;
		count++;

	}


	return 0;
}

