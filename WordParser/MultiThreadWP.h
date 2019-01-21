#pragma once
#include "WordParser.h"
#include <mutex>
#include <queue>
#include <future>

using namespace std;

namespace WP {

	class MultiThreadWP
	{
		WordParser *m_pWP;
		thread *m_pParserThr;
		mutex m_lockParser;
		mutex m_lockCmdQueue;
		condition_variable m_waitCommand;
		queue<function<void()>> m_cmdQueue;
		function<void(string)> m_showException;
	public:

		//Проброс методов
		MultiThreadWP(function<void(string)>, function<void(string)> showMessage);
		~MultiThreadWP();
		future<vector<QuestionsList>> readFile(string path);
		void createHeader(Header header);
		void createTickets(TicketsOptions QCopt);
		void saveAs(string path);
		void closeFile();

	};

}
