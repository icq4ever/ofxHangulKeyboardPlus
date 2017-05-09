//
//  Created by Yi donghoon on 06/10/2016.
//
//  icq4ever@gmail.com
//  http://github.com/icq4ever/
//
//	based on hangul automata c++ source code from http://codepedia.tistory.com/entry/한글-오토마타-만들기
//
//

#include "HangulAutomata.h"

const int BASE_CODE = 0xAC00;		// 기초음성(가)
const int LIMIT_MIN = 0xAC00;		// 음성범위 MIN(가)
const int LIMIT_MAX = 0xD7A3;		// 음성범위 MAX

// 음성 테이블
const wchar_t SOUND_TABLE[110] = {
	/* 초성 19자 0 ~ 18 */
	L'ㄱ', L'ㄲ', L'ㄴ', L'ㄷ', L'ㄸ',	//   0 -   4
	L'ㄹ', L'ㅁ', L'ㅂ', L'ㅃ', L'ㅅ',	//   5 -   9
	L'ㅆ', L'ㅇ', L'ㅈ', L'ㅉ', L'ㅊ',	//  10 -  14
	L'ㅋ', L'ㅌ', L'ㅍ', L'ㅎ',		//  15 -  18
	/* 중성 21자 19 ~ 39 */
	L'ㅏ', L'ㅐ', L'ㅑ', L'ㅒ', L'ㅓ',
	L'ㅔ', L'ㅕ', L'ㅖ', L'ㅗ', L'ㅘ',
	L'ㅙ', L'ㅚ', L'ㅛ', L'ㅜ', L'ㅝ',
	L'ㅞ', L'ㅟ', L'ㅠ', L'ㅡ', L'ㅢ',
	L'ㅣ',
	/* 종성 28자 40 ~ 67 */
	L' ' ,							//  40
	L'ㄱ', L'ㄲ', L'ㄳ', L'ㄴ', L'ㄵ',	//  41 -  45
	L'ㄶ', L'ㄷ', L'ㄹ', L'ㄺ', L'ㄻ',	//  46 -  50
	L'ㄼ', L'ㄽ', L'ㄾ', L'ㄿ', L'ㅀ',	//  51 -  55
	L'ㅁ', L'ㅂ', L'ㅄ', L'ㅅ', L'ㅆ',	//  56 -  60
	L'ㅇ', L'ㅈ', L'ㅊ', L'ㅋ', L'ㅌ',	//  61 -  65
	L'ㅍ', L'ㅎ',						//  66 -  67
	
	/*숫자 및 특수문자 68 - 109*/
	L'`', L'1', L'2', L'3', L'4',	//  68 -  72
	L'5', L'6', L'7', L'8', L'9',	//  73 -  77
	L'0', L'-', L'=', L'[', L']',	//  78 -  82
	L'\\', L';', L'\'', L',' ,L'.',	//  83 -  87
	L'/',							//  88
	
	L'~', L'!', L'@', L'#', L'$',	//  89 -  93
	L'%', L'^', L'&', L'*', L'(',	//  94 -  98
	L')', L'_', L'+', L'{', L'}',	//  99 - 103
	L'|', L':', L'"', L'<', L'>',	// 104 - 108
	L'?',							// 109
};

// 초성 합성 테이블
const int MIXED_CHO_CONSON[5][3] = {
	{ 0, 0, 1}, // ㄱ,ㄱ,ㄲ
	{ 3, 3, 4}, // ㄷ,ㄷ,ㄸ
	{ 7, 7, 8}, // ㅂ,ㅂ,ㅃ
	{ 9, 9,10}, // ㅅ,ㅅ,ㅆ
	{12,12,13}  // ㅈ,ㅈ,ㅉ
};

// 초성,중성 모음 합성 테이블
const int MIXED_VOWEL[7][3] = {
	{27,19,28},	// ㅗ,ㅏ,ㅘ
	{27,20,29},	// ㅗ,ㅐ,ㅙ	// ㅘ + ㅣ -> ㅗ + ㅐ
	{27,39,30},	// ㅗ,ㅣ,ㅚ
	{32,23,33},	// ㅜ,ㅓ,ㅝ
	{32,24,34},	// ㅜ,ㅔ,ㅞ	// ㅝ + ㅓ -> ㅜ + ㅔ
	{32,39,35},	// ㅜ,ㅣ,ㅟ
	{37,39,38},	// ㅡ,ㅣ,ㅢ
};

// 종성 합성 테이블
const int MIXED_JONG_CONSON[12][3] = {
	{41,59,43}, // ㄱ,ㅅ,ㄳ
	{44,62,45}, // ㄴ,ㅈ,ㄵ
	{44,67,46}, // ㄴ,ㅎ,ㄶ
	{48,41,49}, // ㄹ,ㄱ,ㄺ
	{48,56,50}, // ㄹ,ㅁ,ㄻ
	{48,57,51}, // ㄹ,ㅂ,ㄼ
	{51,57,54}, // ㄼ,ㅂ,ㄿ
	{48,59,52}, // ㄹ,ㅅ,ㄽ
	{48,65,53}, // ㄹ,ㅌ,ㄾ	// fixed
	{48,66,54}, // ㄹ,ㅍ,ㄿ	// added
	{48,67,55}, // ㄹ,ㅎ,ㅀ
	{57,59,58}, // ㅂ,ㅅ,ㅄ
};

// 종성 분해 테이블
const int DIVIDE_JONG_CONSON[12][3] = {
	{41,59,43}, // ㄱ,ㅅ,ㄳ
	{44,62,45}, // ㄴ,ㅈ,ㄵ
	{44,67,46}, // ㄴ,ㅎ,ㄶ
	{48,41,49}, // ㄹ,ㄱ,ㄺ
	{48,56,50}, // ㄹ,ㅁ,ㄻ
	{48,57,51}, // ㄹ,ㅂ,ㄼ
	{48,66,54}, // ㄹ,ㅍ,ㄿ
	{48,59,52}, // ㄹ,ㅅ,ㄽ
	{48,65,53}, // ㄹ,ㅌ,ㄾ
	{48,66,54}, // ㄹ,ㅍ,ㄿ	// added
	{48,67,55}, // ㄹ,ㅎ,ㅀ
	{57,59,58}, // ㅂ,ㅅ,ㅄ
};

HangulAutomata::HangulAutomata() {
	Clear();
}

HangulAutomata::~HangulAutomata(){
}


// 버퍼 초기화
void HangulAutomata::Clear() {
	m_nStatus		= HS_FIRST;
	completeText	= L"";
	ingWord			= NULL;
	m_completeWord	= NULL;
}

void HangulAutomata::pushASCII(int keyCode){
	//	int keyCode = static_cast<int>(_c);
	
	if(keyCode < 0) {
		m_nStatus = HS_FIRST;
		
		if(keyCode == KEY_CODE_SPACE) { // 띄어쓰기
			if(ingWord)		completeText += ingWord;
			completeText += L' ';
			
			ingWord = NULL;
		} else if(keyCode == KEY_CODE_ENTER) {  // 내려쓰기
			if(ingWord)		completeText += ingWord;
			
			completeText += L"\n";	// windows
			//			completeText += L"\n";
			
			ingWord = NULL;
			m_completeWord = NULL;
		} else if(keyCode == KEY_CODE_BACKSPACE) { // 지우기
			if(ingWord)		ingWord = NULL;
			if(completeText.length() > 0)	completeText.pop_back();
//			wcout << completeText << endl;
		}
	}
	
	
	if(ingWord)	completeText += ingWord;
	
	completeText += static_cast<wchar_t>(keyCode);
	ingWord = NULL;
	
	m_nStatus = HS_FIRST;
}

void HangulAutomata::clearBuffer(){
	completeText.clear();
}


// 키코드 입력 및 조합 (정해진 int 코드값을 입력 받아 한글조합)
void HangulAutomata::SetKeyCode(int nKeyCode){
	m_completeWord = NULL;
	
	// 특수키 입력
	if(nKeyCode < 0) {
		m_nStatus = HS_FIRST;
		
		if(nKeyCode == KEY_CODE_SPACE) { // 띄어쓰기
			if(ingWord)		completeText += ingWord;
			completeText += L' ';
			
			ingWord = NULL;
		} else if(nKeyCode == KEY_CODE_ENTER) {  // 내려쓰기
			if(ingWord)		completeText += ingWord;
			
			completeText += L"\n";
			
			ingWord = NULL;
			m_completeWord = NULL;
		} else if(nKeyCode == KEY_CODE_BACKSPACE) { // 지우기
			if(ingWord)		ingWord = NULL;
			else if(completeText.length() > 0)	completeText.pop_back();
		}
		
		m_nStatus = HS_FIRST;
		return;
	}
	
	// 숫자 및 특수기호
	else if(nKeyCode > 67){
		if(ingWord)	completeText += ingWord;
		
		completeText += SOUND_TABLE[nKeyCode];
		ingWord = NULL;
		
		m_nStatus = HS_FIRST;
		return;
		
	// 특수키, 숫자가 아니라면...
	} else {
		switch(m_nStatus)	{
			case HS_FIRST:
				// 초성
				m_nPhonemez[0]	= nKeyCode;
				ingWord			= SOUND_TABLE[m_nPhonemez[0]];
				m_nStatus		= nKeyCode > 18 ? HS_FIRST_C : HS_FIRST_V;
				break;
				
			case HS_FIRST_C:
				// 모음 + 모음
				if(nKeyCode > 18) {	// 모음
					//if(MixVowel(&m_nPhonemez[0], nKeyCode) == false)
					{
						m_completeWord = SOUND_TABLE[m_nPhonemez[0]];
						m_nPhonemez[0] = nKeyCode;
					}
				}
				else {				// 자음
					m_completeWord	= SOUND_TABLE[m_nPhonemez[0]];
					m_nPhonemez[0]	= nKeyCode;
					m_nStatus		= HS_FIRST_V;
				}
				break;
				
			case HS_FIRST_V: // 자음이 입력된 상태..
				// 자음 + 모음
				if(nKeyCode > 18){ 	// 자음 + 모음 상태
					m_nPhonemez[1]	= nKeyCode;
					m_nStatus		= HS_MIDDLE_STATE;
				}
				
				else {				// 자음입력상태중 자음이 입력되면 ...
					
//					if(MixInitial(nKeyCode) == false){
					if(!MixInitial(nKeyCode)) {
						m_completeWord	= SOUND_TABLE[m_nPhonemez[0]];
						m_nPhonemez[0]	= nKeyCode;
						m_nStatus		= HS_FIRST_V;
					} 
				}
				break;
				
			case HS_MIDDLE_STATE:
				// 자음 + 모음
				if(nKeyCode > 18)	// 자음 + 모음 + 모음
				{
					if(MixVowel(&m_nPhonemez[1], nKeyCode) == false)	// 모음 조합이 이상하면 ..
					{
						m_completeWord	= CombineHangul(1);
						m_nPhonemez[0]	= nKeyCode;	// 입력받은 모음을 초성으로 넣어버리고 ..
						m_nStatus		= HS_FIRST_C;
					}
				}
				else
				{
					int jungCode = ToFinal(nKeyCode);
					
					if(jungCode > 0)
					{
						m_nPhonemez[2]	= jungCode;
						m_nStatus		= HS_END_STATE;
					}
					else
					{
						m_completeWord	= CombineHangul(1);
						m_nPhonemez[0]	= nKeyCode;
						m_nStatus		= HS_FIRST_V;
					}
				}
				break;
				
			case HS_END:
				// 초성 + 중성 + 종성
				if(nKeyCode > 18)
				{
					m_completeWord	= CombineHangul(1);
					m_nPhonemez[0]	= nKeyCode;
					m_nStatus		= HS_FIRST;
				}
				else
				{
					int jungCode = ToFinal(nKeyCode);
					if(jungCode > 0)
					{
						m_nPhonemez[2]	= jungCode;
						m_nStatus		= HS_END_STATE;
					}
					else
					{
						m_completeWord	= CombineHangul(1);
						m_nPhonemez[0]	= nKeyCode;
						m_nStatus		= HS_FIRST;
					}
				}
				break;
				
			case HS_END_STATE:
				// 초성 + 중성 + 자음(종) + 자음(종)
				if(nKeyCode > 18)
				{
					m_completeWord = CombineHangul(1);
					
					m_nPhonemez[0]	= ToInitial(m_nPhonemez[2]);
					m_nPhonemez[1]	= nKeyCode;
					m_nStatus		= HS_MIDDLE_STATE;
				}
				else
				{
					int jungCode = ToFinal(nKeyCode);
					if(jungCode > 0)
					{
						m_nStatus = HS_END_EXCEPTION;
						
						if(!MixFinal(jungCode))
						{
							m_completeWord	= CombineHangul(2);
							m_nPhonemez[0]	= nKeyCode;
							m_nStatus		= HS_FIRST_V;
						}
					}
					else
					{
						m_completeWord	= CombineHangul(2);
						m_nPhonemez[0]	= nKeyCode;
						m_nStatus		= HS_FIRST_V;
					}
				}
				break;
				
			case HS_END_EXCEPTION:
				// 초성 + 중성 + 종성(곁자음)
				if(nKeyCode > 18) {
					DecomposeConsonant();
					m_nPhonemez[1]	= nKeyCode;
					m_nStatus		= HS_MIDDLE_STATE;
				} else {
					int jungCode = ToFinal(nKeyCode);
					if(jungCode > 0) {
						m_nStatus = HS_END_EXCEPTION;
						
						//if(!MixFinal(jungCode))
						{
							m_completeWord	= CombineHangul(2);
							m_nPhonemez[0]	= nKeyCode;
							m_nStatus		= HS_FIRST_V;
						}
					} else {
						m_completeWord	= CombineHangul(2);
						m_nPhonemez[0]	= nKeyCode;
						m_nStatus		= HS_FIRST_V;
					}
				}
				break;
		}
		
		// 현재 보이는 글자상태
		CombineIngWord(m_nStatus);
	}
	
	// 완성 문자열 만들기
	if(m_completeWord)	completeText += m_completeWord;
	
	//	return m_completeWord;
}


// 초성으로 변환
int HangulAutomata::ToInitial(int nKeyCode) {
	switch(nKeyCode)
	{
		case 41: return 0;	// ㄱ
		case 42: return 1;	// ㄲ
		case 44: return 2;	// ㄴ
		case 47: return 3;	// ㄷ
		case 68: return 4;	// ㄸ	// added
		case 48: return 5;	// ㄹ
		case 56: return 6;	// ㅁ
		case 57: return 7;	// ㅂ
		case 69: return 8;	// ㅃ	// added
		case 59: return 9;	// ㅅ
		case 60: return 10;	// ㅆ
		case 61: return 11;	// ㅇ
		case 62: return 12;	// ㅈ
		case 70: return 13;	// ㅉ	// added
		case 63: return 14;	// ㅊ
		case 64: return 15;	// ㅋ
		case 65: return 16;	// ㅌ
		case 66: return 17;	// ㅍ
		case 67: return 18;	// ㅎ
	}
	return -1;
}

// 종성으로 변환
int HangulAutomata::ToFinal(int nKeyCode) {
	switch(nKeyCode)
	{
		case 0:  return 41;	// ㄱ
		case 1:  return 42;	// ㄲ
		case 2:  return 44;	// ㄴ
		case 3:  return 47;	// ㄷ
			//		case 4:  return 68;	// ㄸ	// added
		case 5:  return 48;	// ㄹ
		case 6:  return 56;	// ㅁ
		case 7:  return 57;	// ㅂ
			//		case 8:  return 69;	// ㅃ	// added
		case 9:  return 59;	// ㅅ
		case 10: return 60;	// ㅆ
		case 11: return 61;	// ㅇ
		case 12: return 62;	// ㅈ
			//		case 13: return 70;	// ㅉ	// added
		case 14: return 63;	// ㅊ
		case 15: return 64;	// ㅋ
		case 16: return 65;	// ㅌ
		case 17: return 66;	// ㅍ
		case 18: return 67;	// ㅎ
	}
	return -1;
}

// 자음분해
void HangulAutomata::DecomposeConsonant() {
	int i = 0;
	if(m_nPhonemez[3] > 40 || m_nPhonemez[4] > 40) {
		do {
			if(DIVIDE_JONG_CONSON[i][2] == m_nPhonemez[2]) {
				m_nPhonemez[3] = DIVIDE_JONG_CONSON[i][0];
				m_nPhonemez[4] = DIVIDE_JONG_CONSON[i][1];
				
				m_completeWord = CombineHangul(3);
				m_nPhonemez[0]	 = ToInitial(m_nPhonemez[4]);
				
				return;
			}
		}
		while(++i< 12);
	}
	
	m_completeWord = CombineHangul(1);
	m_nPhonemez[0]	 = ToInitial(m_nPhonemez[2]);
}

// 초성합성
bool HangulAutomata::MixInitial(int nKeyCode) {
	if(nKeyCode >= 19)		return false;
	
	int i = 0;
	do {
		if(MIXED_CHO_CONSON[i][0] == m_nPhonemez[0] && MIXED_CHO_CONSON[i][1] == nKeyCode) {
			m_nPhonemez[0] = MIXED_CHO_CONSON[i][2];
			return true;
		}
	}
	while(++i < );
	
	return false;
}

// 종성합성
bool HangulAutomata::MixFinal(int nKeyCode) {
	if(nKeyCode <= 40) return false;
	
	int i = 0;
	do {
		// 연속된 자음입력이 종성 합성테이블에 포함되어있다면 ...
		if(MIXED_JONG_CONSON[i][0] == m_nPhonemez[2] && MIXED_JONG_CONSON[i][1] == nKeyCode) {
			m_nPhonemez[3] = m_nPhonemez[2];
			m_nPhonemez[4] = nKeyCode;
			m_nPhonemez[2] = MIXED_JONG_CONSON[i][2];
			
			return true;
		}
	}
	while(++i < 12);
	
	return false;
}

// 모음합성
bool HangulAutomata::MixVowel(int * currentCode, int inputCode) {
	int i = 0;
	do {
		if(MIXED_VOWEL[i][0] == * currentCode && MIXED_VOWEL[i][1] == inputCode) {
			* currentCode = MIXED_VOWEL[i][2];
			return true;
		}
	}
	while(++i< 7);
	
	return false;
}

// 한글조합
wchar_t HangulAutomata::CombineHangul(int cho, int jung, int jong) {
	//	return BASE_CODE + (28*21*cho) + (jung*28) + jong;		// from the internet http://forensic-proof.com/archives/615
	
	// 초성 * 21 * 28 + (중성 - 19) * 28 + (종성 - 40) + BASE_CODE;
	return cho * 588 + (jung - 19) * 28 + (jong - 40) + BASE_CODE;
	
	//		return BASE_CODE - 572 + jong + cho * 588 + jung * 28;	// original
}

wchar_t HangulAutomata::CombineHangul(int status) {
	switch(status) {
			//초성 + 중성
		case 1: return CombineHangul(m_nPhonemez[0], m_nPhonemez[1], 40);
			
			//초성 + 중성 + 종성
		case 2: return CombineHangul(m_nPhonemez[0], m_nPhonemez[1], m_nPhonemez[2]);
			
			//초성 + 중성 + 곁자음01
		case 3: return CombineHangul(m_nPhonemez[0], m_nPhonemez[1], m_nPhonemez[3]);
	}
	return ' ';
}

void HangulAutomata::CombineIngWord(int status) {
	switch(m_nStatus)
	{
		case HS_FIRST:	// 초성
		case HS_FIRST_V:	// 자음 + 자음
		case HS_FIRST_C:	// 모음 +모음
			ingWord = SOUND_TABLE[m_nPhonemez[0]];
			break;
			
		case HS_MIDDLE_STATE:	// 초성 + 모음 + 모음
		case HS_END:		// 초성 + 중성 + 종성
			ingWord = CombineHangul(1);
			break;
			
		case HS_END_STATE:	// 초성 + 중성 + 자음 + 자음
		case HS_END_EXCEPTION:	// 초성 + 중성 + 종성 (곁자음)
			ingWord = CombineHangul(2);
			break;
	}
}

int HangulAutomata::DownGradeIngWordStatus(wchar_t word) {
	int iWord = word;
	
	//초성만 있는 경우
	if(iWord < LIMIT_MIN || iWord > LIMIT_MAX) {
		ingWord = NULL;
		
		return HS_FIRST;
	}
	
	//문자코드 체계
	//iWord = firstWord * (21*28)
	//		+ middleWord * 28
	//		+ lastWord * 27
	//		+ BASE_CODE;
	//
	int totalWord	= iWord - BASE_CODE;
	int iFirstWord	= totalWord / 28 / 21;	//초성
	int iMiddleWord = totalWord / 28 % 21;	//중성
	int iLastWord	= totalWord % 28;		//종성
	
	m_nPhonemez[0] = iFirstWord; //초성저장
	
	if(iLastWord == 0) {	//종성이 없는 경우
		ingWord = SOUND_TABLE[m_nPhonemez[0]];
		
		return HS_FIRST_V;
	}
	
	m_nPhonemez[1] = iMiddleWord + 19; //중성저장
	
	iLastWord += 40;
	
	for(int i = 0; i < 13; i++) {
		if(iLastWord == DIVIDE_JONG_CONSON[i][2]) {
			ingWord = CombineHangul(3);
			m_nPhonemez[2] = DIVIDE_JONG_CONSON[i][0]; // 종성저장
			return HS_END_EXCEPTION;
		}
	}
	
	ingWord = CombineHangul(1);
	
	return HS_MIDDLE_STATE;
}


