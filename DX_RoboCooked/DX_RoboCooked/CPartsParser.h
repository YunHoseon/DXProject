#pragma once
#define TOKEN_COUNT 200  // 토큰의 최대 개수

enum MY_TOKEN_TYPE { TOKEN_STRING = 0, TOKEN_NUMBER };

struct MY_TOKEN
{
	MY_TOKEN_TYPE type;
	union {             // 두 종류 중 한 종류만 저장할 것이므로 공용체
		char *string;
		double number;
	};
	bool isArray;       
};

struct JSON
{
	MY_TOKEN tokens[TOKEN_COUNT];
};

class CParts;

class CPartsParser
{
private:
	bool isExistFile;
	map<string, CParts*> m_mapPartsData;
public:
	CPartsParser();
	~CPartsParser();

	char* ReadFile(char* fileName, int* readSize);
	void ParseJSON(char* doc, int size, JSON* json);
	void SavePartsData(JSON json);
	void FreeJSON(JSON* json);
};

