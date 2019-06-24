#include <process.h>
#include "MultiThread.h"


using namespace GameL;

bool			 CMultiThread::m_execution;		//スレッド実行フラグ
CRITICAL_SECTION CMultiThread::m_cs;			//クリティカルセクション
HANDLE			 CMultiThread::m_handoru_game;	//ゲームスレッド

bool CMultiThread::GetEnd()
{
	return m_execution;	
}

//初期化
void CMultiThread::Init( void(*game_sub)() )
{
	m_handoru_game =nullptr;
	m_execution	   =true;

	//クリティカルセクション起動
	InitializeCriticalSection(&m_cs);

	//スレッド起動
	m_handoru_game = (HANDLE)_beginthreadex(NULL, 0, GameThread ,(void *)game_sub , 0, NULL);
	
}

//削除
void CMultiThread::Delete()
{
	//スレッド終了フラグを立てる
	End();
	//スレッド終了確認
	WaitForSingleObject(m_handoru_game , INFINITE);
    //スレッド終了
	CloseHandle(m_handoru_game);
	//クリティカルセクション終了
	DeleteCriticalSection(&m_cs);

}

//ゲームスレッド停止メソッド
void CMultiThread::End()
{
	EnterCriticalSection(&m_cs);
	m_execution=false;
	LeaveCriticalSection(&m_cs);
}

//ゲームスレッド用メソッド
unsigned __stdcall CMultiThread::GameThread(void *p)
{
	void (*sub)() = (void(*)()) p;
	
	//ゲームループ
	while(m_execution)
	{
		sub();
	}

    _endthreadex(0);
    return 0;
}