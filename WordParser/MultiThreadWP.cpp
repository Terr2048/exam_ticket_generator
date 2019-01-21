#include "MultiThreadWP.h"
#include <thread>
#include <future>

using namespace std;

namespace WP {
	MultiThreadWP::MultiThreadWP(function<void(string)> showException, function<void(string)> showMessage)
		: m_showException(showException)
	{
		m_pParserThr = new thread([this, showMessage]() {
			setlocale(LC_ALL, "rus");
			unique_lock<mutex> lkParser(m_lockParser);
			m_pWP = new WordParser(showMessage);
			while (m_pWP != nullptr) {
				m_waitCommand.wait(lkParser);
				while (!m_cmdQueue.empty()) {
					try {
						m_lockCmdQueue.lock();
						function<void()> cmd = m_cmdQueue.front();
						m_cmdQueue.pop();
						m_lockCmdQueue.unlock();

						cmd();
					}
					catch (exception e) {
						async(launch::async, [this, e]() {
							m_showException(e.what()); 
						});
					}
					catch (_com_error e) {
						async(launch::async, [this, e]() {
							std::wstring str((wstring)e.ErrorMessage());
							m_showException(string(str.begin(),str.end()));
						});
					}
				}
			}
		});

	}

	MultiThreadWP::~MultiThreadWP()
	{
		{
			lock_guard<mutex> lk(m_lockCmdQueue);
			m_cmdQueue.push([this]() {
				delete m_pWP;
				m_pWP = nullptr;
			});
		}
		m_waitCommand.notify_all();
		if (m_pParserThr->joinable()) m_pParserThr->join();
		delete m_pParserThr;
		m_pParserThr = nullptr;
	}

	future<vector<QuestionsList>> MultiThreadWP::readFile(string path)
	{
		shared_ptr<promise<vector<QuestionsList>>> prm = make_shared<promise<vector<QuestionsList>>>();
		future<vector<QuestionsList>> ftr = prm->get_future();
		{
			lock_guard<mutex> lk(m_lockCmdQueue);
			m_cmdQueue.push([this, path, prm]() {
				prm->set_value(m_pWP->readFile(path));
			});
		}
		m_waitCommand.notify_all();
		return ftr;
	}

	void MultiThreadWP::createHeader(Header header)
	{
		{
			lock_guard<mutex> lk(m_lockCmdQueue);
			m_cmdQueue.push([this, header]() {
				m_pWP->createHeader(header);
			});
		}
		m_waitCommand.notify_all();
	}

	void MultiThreadWP::createTickets(TicketsOptions QCopt)
	{
		{
			lock_guard<mutex> lk(m_lockCmdQueue);
			m_cmdQueue.push([this, QCopt]() {
				m_pWP->createTickets(QCopt);
			});
		}
		m_waitCommand.notify_all();
	}

	void MultiThreadWP::saveAs(string path)
	{
		{
			lock_guard<mutex> lk(m_lockCmdQueue);
			m_cmdQueue.push([this, path]() {
				m_pWP->saveAs(path);
			});
		}
		m_waitCommand.notify_all();
	}

	void MultiThreadWP::closeFile()
	{
		{
			lock_guard<mutex> lk(m_lockCmdQueue);
			m_cmdQueue.push([this]() {
				m_pWP->closeFile();
			});
		}
		m_waitCommand.notify_all();
	}

}
