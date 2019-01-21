#pragma once
#include <string>
#include <vector>
#include <functional>

#pragma region Import the type libraries

#import "libid:2DF8D04C-5BFA-101B-BDE5-00AA0044DE52" \
	rename("RGB", "MSORGB") \
	rename("DocumentProperties", "MSODocumentProperties")
// [-or-]
//#import "C:\\Program Files\\Common Files\\Microsoft Shared\\OFFICE12\\MSO.DLL" \
//	rename("RGB", "MSORGB") \
//	rename("DocumentProperties", "MSODocumentProperties")

using namespace Office;

#import "libid:0002E157-0000-0000-C000-000000000046"
// [-or-]
//#import "C:\\Program Files\\Common Files\\Microsoft Shared\\VBA\\VBA6\\VBE6EXT.OLB"

using namespace VBIDE;

#import "libid:00020905-0000-0000-C000-000000000046" \
	rename("ExitWindows", "WordExitWindows") \
	rename("FindText", "WordFindText")
// [-or-]
//#import "C:\\Program Files\\Microsoft Office\\Office12\\MSWORD.OLB" \
//	rename("ExitWindows", "WordExitWindows") \
//	rename("FindText", "WordFindText")

#pragma endregion

using namespace std;

namespace WP {

	struct Header {
		string name_teh_school; // шапка (название организации)

		string examined; // рассмотрено...
		string review_date; // дата рассмотрения
		string protocol; // протокол
		string chairperson; // председатель

		string affirm; // УТВЕРЖДАЮ:...
		string date_apporval; // дата утверждения
		string deputy_director; // зам. директор

		string discipline; // дисциплина
		string specialty; // специальность
	};

	struct QuestionsList {
		int numOfQuestions;
	};

	struct QuestionsSection {
		string name;
		int numOfQuestions;
	};

	struct TicketsOptions {
		int ticketCount;
		string teacherName;
		string disciplineTitle;
		string specialtyName;
		vector<QuestionsSection> questionsSections;
	};

	class WordParser {
		Word::_ApplicationPtr m_spWordApp;
		Word::_DocumentPtr m_spDoc;
		vector<QuestionsList> m_questionsLists;
		function<void(string)> m_showMessage;
	public:
		WordParser(function<void(string)> showMessage);
		~WordParser();
		vector<QuestionsList> readFile(string path);
		void createHeader(Header header);
		void createTickets(TicketsOptions opt);
		void saveAs(string path);
		void closeFile();

	};

}
