#pragma once
#include <Windows.h>

namespace GameL
{
	typedef class CMultiThread
	{
		public:
			static void Init(void(*game_sub)());
			static void Delete();
			static void End();
			static bool GetEnd();
		private:

			static unsigned __stdcall GameThread(void *p);	//ゲームスレッド用メソッド
			static bool   m_execution;						//スレッド実行フラグ
			static CRITICAL_SECTION m_cs;					//クリティカルセクション
			static HANDLE m_handoru_game;					//ゲームスレッド
	}GameLoop;
};