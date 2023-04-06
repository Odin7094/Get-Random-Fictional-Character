#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <stdio.h>

int main()
{
	srand(time(NULL));
	struct dataObj{std::string values[2];};
	std::vector<dataObj> data;
	std::fstream file("charactersWithArticles.csv");
	
	for(int a = 1; !file.eof(); a++)
	{
		std::string temp = "";
		std::getline(file, temp);
		
		size_t EndPart1 = temp.find_first_of(",");
		std::string Part1 = temp.substr(0, EndPart1);
		std::string Part2 = temp.substr(EndPart1 + 1);
		dataObj temp2 = {Part1, Part2};
		data.push_back(temp2);
	}
	
	std::cout << "Content-type: text/html" << std::endl << std::endl;
	
	int amount = 1;
	
	char* value = getenv("QUERY_STRING");
	if(value != NULL)
	{
		try
		{
			amount = std::stoi( std::string(value) );
		}
		catch(...)
		{
			
		}
	}
	
	for(int a=0; a<amount; a++)
	{
		int b = std::rand()%data.size();
		std::cout << "<a style=\"font-size: 45px;\" href=\"" << data[b].values[0] << "\">" << data[b].values[1] << "</a>" << "</br></br></br>";
	}
	
	file.close();
	
	return 0;
}
