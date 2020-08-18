#include <iostream>
#include <json/json.h>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>
//#include <cctype>
#include "binance_logger.h"

#include "dataGetor.h"
#include "timeStringConvert.h"
const std::string verString =
"V1.21"
;

//Server serverUs("https://api.binance.us");
//Server serverCn;
//Server& server = serverCn;

using namespace binance;
using namespace std;

map<long, map<string, double> > klinesCache;

int main(int argc, char* argv[])
{

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
	string outfile;
	dataGetor getor;
	if (argc < 8)
	{
		cout << "usage:" << endl;
		exit(0);
	}
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
		else if (strcasecmp(argv[i], "-f") == 0)
		{
			outfile = argv[i + 1];
		}

	}

	cout << "start Time = " << timeConvertor::ShowDateTime(getor.startTime) << endl
		<< "end time = " << timeConvertor::ShowDateTime(getor.endTime) << endl;
	cout << "interval:" << getor.interval << endl;


	if (outfile == "")
	{
		outfile = "getorData" + timeConvertor::ShowDateTime(getor.startTime)
			+ "-" + timeConvertor::ShowDateTime(getor.endTime) + "-" + getor.interval + ".txt";
	}

	auto data =getor.getData();

	ofstream  myfile(outfile);

	cout << "@@data.size()@@" << data.size() << endl;
	int count = 1;
	for (auto& item : data)
	{
		ostringstream os;
		os << count <<"\t" << timeConvertor::ShowDateTime(item.datatime) << "\t" << item.datatime << "\t" 
			<< item.open << "\t" <<item.high<<"\t" <<item.low <<"\t" << item.close;
		cout << os.str() << endl;
		myfile << os.str() << endl;
		count++;

	}

	cout << endl<< "output:" << outfile << endl;

	return 0;
}

