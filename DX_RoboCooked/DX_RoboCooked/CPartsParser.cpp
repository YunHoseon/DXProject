#include "stdafx.h"
#include "CPartsParser.h"
#include "CParts.h"

CPartsParser::CPartsParser()
{
}


CPartsParser::~CPartsParser()
{
}

char* CPartsParser::ReadFile(char* fileName, int* readSize)
{
	FILE *fp = fopen(fileName, "rb");
	if (fp == NULL)
		return NULL;

	int size;
	char *buffer;

	// 파일 크기 구하기
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// 파일 크기 + NULL 공간만큼 메모리를 할당하고 0으로 초기화
	buffer = (char*)malloc(size + 1);
	memset(buffer, 0, size + 1);

	// 파일 내용 읽기
	if (fread(buffer, size, 1, fp) < 1)
	{
		*readSize = 0;
		free(buffer);
		fclose(fp);
		return NULL;
	}

	*readSize = size;	// 파일 크기를 넘겨줌
	fclose(fp);

	return buffer;
}

void CPartsParser::ParseJSON(char* doc, int size, JSON* json)
{
	int tokenIndex = 0;    // 토큰 인덱스
	int pos = 0;           // 문자 검색 위치를 저장하는 변수

	if (doc[pos] != '[')   // 문서의 시작이 [ 인지 검사
		return;

	pos++;    // 다음 문자로

	if (doc[pos] != '{')   // 다음 문자가 { 인지 검사
		return;

	while (pos < size)       // 문서 크기만큼 반복
	{
		switch (doc[pos])    // 문자의 종류에 따라 분기
		{
		case '"':            // 문자가 "이면 문자열
		{
			// 문자열의 시작 위치를 구함. 맨 앞의 "를 제외하기 위해 + 1
			char *begin = doc + pos + 1;

			// 문자열의 끝 위치를 구함. 다음 "의 위치
			char *end = strchr(begin, '"');
			if (end == NULL)    // "가 없으면 잘못된 문법이므로 
				break;          // 반복을 종료

			int stringLength = end - begin;    // 문자열의 실제 길이는 끝 위치 - 시작 위치

											   // 토큰 배열에 문자열 저장, 토큰 종류는 문자열
			json->tokens[tokenIndex].type = (MY_TOKEN_TYPE)TOKEN_STRING;
			// 문자열 길이 + NULL 공간만큼 메모리 할당
			json->tokens[tokenIndex].string = (char*)malloc(stringLength + 1);
			// 할당한 메모리를 0으로 초기화
			memset(json->tokens[tokenIndex].string, 0, stringLength + 1);

			// 문서에서 문자열을 토큰에 저장
			// 문자열 시작 위치에서 문자열 길이만큼만 복사
			memcpy(json->tokens[tokenIndex].string, begin, stringLength);

			tokenIndex++; // 토큰 인덱스 증가

			pos = pos + stringLength + 1;    // 현재 위치 + 문자열 길이 + "(+ 1)
		}
		break;

		case '0': case '1': case '2': case '3': case '4': case '5':    // 문자가 숫자이면
		case '6': case '7': case '8': case '9': case '-':              // -는 음수일 때
		{
			// 문자열의 시작 위치를 구함
			char *begin = doc + pos;
			char *end;
			char *buffer;

			// 문자열의 끝 위치를 구함. ,가 나오거나
			end = strchr(doc + pos, ',');
			if (end == NULL)
			{
				// } 가 나오면 문자열이 끝남
				end = strchr(doc + pos, '}');
				if (end == NULL)    // }가 없으면 잘못된 문법이므로
					break;          // 반복을 종료
			}

			int stringLength = end - begin;    // 문자열의 실제 길이는 끝 위치 - 시작 위치

											   // 문자열 길이 + NULL 공간만큼 메모리 할당
			buffer = (char*)malloc(stringLength + 1);
			// 할당한 메모리를 0으로 초기화
			memset(buffer, 0, stringLength + 1);

			// 문서에서 문자열을 버퍼에 저장
			// 문자열 시작 위치에서 문자열 길이만큼만 복사
			memcpy(buffer, begin, stringLength);

			// 토큰 종류는 숫자
			json->tokens[tokenIndex].type = TOKEN_NUMBER;
			// 문자열을 숫자로 변환하여 토큰에 저장
			json->tokens[tokenIndex].number = atof(buffer);

			free(buffer);    // 버퍼 해제

			tokenIndex++;    // 토큰 인덱스 증가

			pos = pos + stringLength + 1;    // 현재 위치 + 문자열 길이 + , 또는 }(+ 1)
		}
		break;
		}
		pos++; // 다음 문자로
	}
}

void CPartsParser::SavePartsData(JSON json)
{
	CParts* parts;
	//m_mapPartsData.insert();
}

void CPartsParser::FreeJSON(JSON* json)
{
	for (int i = 0; i < TOKEN_COUNT; i++)            // 토큰 개수만큼 반복
	{
		if (json->tokens[i].type == (MY_TOKEN_TYPE)TOKEN_STRING)    // 토큰 종류가 문자열이면
			free(json->tokens[i].string);							// 동적 메모리 해제
	}
}
