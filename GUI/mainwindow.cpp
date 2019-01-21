#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QFormLayout>
//#include <QtCore/QDebug>
#include <ctime>
#include <chrono>
#include <QtWidgets/QDesktopWidget>

/////////////////////////////////
// TODO: ОТРЕФАКТОРИТЬ ВСЁ !!! //
/////////////////////////////////

using namespace std::chrono;

GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Парсер билетов Word");

    /* КОД КОТОРЫЙ ГЕНЕРИРУЕТ СКРОЛЛ AREA. (если нет секции, то не будет скролл area =()
    int section = 0;
    if(section == 0)
    {
        ui->scrollArea->hide();
        ui->button_ready->move(30, 460);
        ui->button_open_file->move(600, 460);
        this->setFixedSize(788, 550);

    }
    else GUI::addSection(5, 15);*/
    //GUI::addSection(5, 15);

	
	QObject::connect(this, SIGNAL(sendException(QString)), this, SLOT(showDialogException(QString)));
	QObject::connect(this, SIGNAL(sendMessage(QString)), this, SLOT(setProgressBar(QString)));

	m_pMTWP = new WP::MultiThreadWP(
		[this](string str) {
		emit sendException(QString::fromLocal8Bit(str.c_str()));
	}, 
		[this](string str) {
		emit sendMessage(QString::fromLocal8Bit(str.c_str()));
	});
}

GUI::~GUI()
{
    delete ui;
	delete m_pMTWP;
}
void GUI::setProgressBar(QString message)
{
	ui->progress->setText(message);
}
void GUI::on_button_open_file_clicked()
{
    GUI::path_to_word = QFileDialog::getOpenFileName(
                this,
                tr("Открыть файл"),
                "С://",
                "Word File (*.doc *.docx)"
                );

	future<vector<WP::QuestionsList>> ftr = m_pMTWP->readFile(path_to_word.toLocal8Bit().constData());
	ftr.wait();
	try {
		m_pQS = make_shared<vector<WP::QuestionsList>>(ftr.get());
	}
	catch (...) {
		return;
	}
	addSection(*m_pQS);
}

void GUI::on_button_ready_clicked()
{
    GUI::getNameTechnicalSchool(GUI::name_teh_school);
    GUI::getChairperson(GUI::chairperson);
    GUI::getReviewDate(GUI::review_date);
    GUI::getApporvalDate(GUI::date_apporval);
    GUI::getDeputyDirector(GUI::deputy_director);
    GUI::getDiscipline(GUI::discipline);
    GUI::getSpecialty(GUI::specialty);
    GUI::getLecturer(GUI::lecturer);
    GUI::getExamined(GUI::examined);
    GUI::getAffirm(GUI::affirm);
    GUI::getProtocolId(GUI::protocol_id);
    GUI::getValueTicketSpinBox(GUI::count_ticket);
   
	m_pMTWP->createHeader({
		name_teh_school.toLocal8Bit().constData(), //Название шараги

		examined.toLocal8Bit().constData(), // рассмотрено...
		review_date.toLocal8Bit().constData(), // дата рассмотрения
		protocol_id.toLocal8Bit().constData(), // протокол
		chairperson.toLocal8Bit().constData(), // председатель

		affirm.toLocal8Bit().constData(), // УТВЕРЖДАЮ:...
		date_apporval.toLocal8Bit().constData(), // дата утверждения
		deputy_director.toLocal8Bit().constData(), // зам. директор

		discipline.toLocal8Bit().constData(), // дисциплина
		specialty.toLocal8Bit().constData(), // специальность
	});
	m_pMTWP->createTickets({
		count_ticket,
		lecturer.toLocal8Bit().constData(),
		discipline.toLocal8Bit().constData(),
		specialty.toLocal8Bit().constData(),
		getQuestionSections(m_pQS->size())
	});
	showSaveDialog();

	m_pMTWP->saveAs(path_to_save.toLocal8Bit().constData());

	m_pMTWP->closeFile();

}
//void GUI::on_review_date_dateChanged(const QDate &date)
//{
//    ui -> review_date-> setDate(date);
//}
//
//void GUI::on_date_apporval_dateChanged(const QDate &date)
//{
//    ui -> date_apporval -> setDate(date);
//}
void GUI::showDialogException(QString message)
{
    QMessageBox::critical(this, "Exception", message);
}
void GUI::getNameTechnicalSchool(QString &name)
{
    name = ui -> header -> toPlainText();
}
void GUI::getChairperson(QString &name)
{
    name = ui -> chairperson -> toPlainText();
}
void GUI::getReviewDate(QString &name)
{
	name = ui -> review_date -> toPlainText();
}
void GUI::getApporvalDate(QString &name)
{
	name = ui -> date_apporval -> toPlainText();
}
void GUI::getDeputyDirector(QString &name)
{
    name = ui -> input_deputy_director -> toPlainText();
}
void GUI::getDiscipline(QString &name)
{
    name = ui -> input_discipline -> toPlainText();
}
void GUI::getSpecialty(QString &name)
{
    name = ui -> input_specialty -> toPlainText();
}
void GUI::getLecturer(QString &name)
{
    name = ui -> input_teacher -> toPlainText();
}
void GUI::getExamined(QString &buffer)
{
    buffer = ui -> examined -> toPlainText();
}
void GUI::getAffirm(QString &buf)
{
    buf = ui -> affirim ->toPlainText();
}
void GUI::getProtocolId(QString &buffer)
{
    buffer = ui -> protocol_id -> toPlainText();
}
void GUI::getTextDynamicTextBox(QString &str, const int qtext_browser_id)
{
    QTextBrowser * text_box = findChild<QTextBrowser *>(QStringLiteral("box_text_id_%1").arg(qtext_browser_id));
    if(text_box == NULL)
    {
         QMessageBox::critical(this, "Exception", "null");
         return;
    }
    str = text_box -> toPlainText();
}
void GUI::getValueDynamicSpinBox(int &value, const int spin_box_id)
{
   QSpinBox * spin_box = findChild<QSpinBox *>(QStringLiteral("spin_id_%1").arg(spin_box_id));
   if(spin_box == NULL)
   {
        QMessageBox::critical(this, "Exception", "null");
        return;
   }
   value = spin_box -> value();
}

//Это просто кто-то здесь оставил, не будем тыкать пальцем, проект очень древний.
//
//void GUI::getAllValueDynamicSpinBox(std::unordered_map <int, int> &map,
//                                     const int count_section)
//{
//    QSpinBox * spin_box;
//    for(int k = 0; k < count_section+1; k++)
//    {
//        spin_box = findChild<QSpinBox *>(QStringLiteral("spin_id_%1").arg(k));
//        if(spin_box == NULL) continue;
//        map.insert(std::make_pair(k, spin_box -> value()));
//    }
//}
//void GUI::getAllTextDynamicTextBox(std::unordered_map <int, QString> &map,
//                                     const int count_section)
//{
//    QTextBrowser * text_box;
//    for(int k = 0; k < count_section+1; k++)
//    {
//        text_box = findChild<QTextBrowser *>(QStringLiteral("box_text_id_%1").arg(k));
//        if(text_box == NULL) continue;
//        map.insert(std::make_pair(k, text_box -> toPlainText()));
//    }
//}

vector<WP::QuestionsSection> GUI::getQuestionSections(int sectCount) {
	vector<WP::QuestionsSection> qs(sectCount);
	for (int i = 0; i < sectCount; i++) {
		qs[i].numOfQuestions = findChild<QSpinBox *>(QStringLiteral("spin_id_%1").arg(i))->value();
		qs[i].name = findChild<QTextBrowser *>(QStringLiteral("box_text_id_%1").arg(i))->toPlainText().toLocal8Bit().constData();
	}
	return qs;
}

void GUI::addSection(vector<WP::QuestionsList> qs)
{
	GUI::destroyAllScrollArea();
	GUI::count_section = qs.size();

	QVBoxLayout * vlay = new QVBoxLayout();
	vlay->setObjectName("q_grid_layout");
	vlay->setSpacing(4);

	QFont params_font("MS Shell Dlg 2", 10, QFont::Bold);

	for (int i = 0; i < GUI::count_section; i++)
	{
		{
			QLabel * main_label = new QLabel(this);
			main_label->setText("[" + QString::number(i + 1) + "] " + QString::number(qs[i].numOfQuestions) + " вопросов. Заголовок секции: ");
			main_label->setFont(params_font);
			main_label->setObjectName(QStringLiteral("main_label_%1").arg(i));

			QTextBrowser * box_text = new QTextBrowser(this);
			box_text->setFixedHeight(25);
			box_text->setObjectName(QStringLiteral("box_text_id_%1").arg(i));
			box_text->setReadOnly(false);

			QHBoxLayout * hlay = new QHBoxLayout();
			hlay->addWidget(main_label);
			hlay->addWidget(box_text);

			vlay->addLayout(hlay);
		}
		{
			QLabel * label_section = new QLabel(this);
			label_section->setText("Добавить в каждый билет ");
			label_section->setFont(params_font);
			label_section->setObjectName(QStringLiteral("label_section_id_%1").arg(i));

			QSpinBox *box_input_value = new QSpinBox(this);
			box_input_value->setMaximum(LONG_MAX);
			box_input_value->setObjectName(QStringLiteral("spin_id_%1").arg(i));
			box_input_value->setFixedSize(100, 25);

			QLabel * label_answer = new QLabel(this);
			label_answer->setText(" вопросов");
			label_answer->setFont(params_font);
			label_answer->setObjectName(QStringLiteral("label_answer_%1").arg(i));

			QHBoxLayout * hlay = new QHBoxLayout();
			hlay->addWidget(label_section);
			hlay->addWidget(box_input_value);
			hlay->addWidget(label_answer);
			hlay->addStretch(10);

			vlay->addLayout(hlay);
		}
	}
	ui->scrollContents->setLayout(vlay);
}
void GUI::setCurrentDateTimeBox(QDateEdit * widget)
{
    system_clock::time_point time_now = system_clock::now();

    time_t convert_to_normal_format;

    convert_to_normal_format = system_clock::to_time_t ( time_now );

    QDateTime convert_time_t_to_date_time(QDateTime::fromTime_t(convert_to_normal_format));
    QString dateString = convert_time_t_to_date_time.toString("dd/MM/yyyy");
    QDate final_date = QDate::fromString(dateString,"dd/MM/yyyy"); // конечная дата, после конвертаций.
    widget->setDate(final_date);
}
void GUI::getValueTicketSpinBox(int &value)
{
    value = ui->spin_box_count_ticket->value();
}
void GUI::showSaveDialog()
{
    GUI::path_to_save = QFileDialog::getSaveFileName(
                    this,
                    tr("Save file"),
                    "",
                    "Word File (*.doc *.docx)"
                    );
}
void GUI::on_action_4_triggered()
{
   QString information = "Разработчики: \n\n"
                        "terr (telegram: @terr)\n"
                        "$continue$ (telegram: @continue98)\n\n"
                        "\t© 2017 год";
   QMessageBox::information(this, "Информация о разработчиках", information);
}

void GUI::destroyDynamicSpinBox()
{
	QSpinBox * spin_box;
	for (int k = 0; k < GUI::count_section; k++)
	{
		spin_box = findChild<QSpinBox *>(QStringLiteral("spin_id_%1").arg(k));
		if (spin_box == NULL) continue;
		spin_box->destroyed();
		delete spin_box;
	}
}
void GUI::destroyAnswerLabel()
{
	QLabel * label;
	for (int k = 0; k < GUI::count_section; k++)
	{
		label = findChild<QLabel *>(QStringLiteral("label_answer_%1").arg(k));
		if (label == NULL) continue;
		label->destroyed();
		delete label;
	}
}
void GUI::destroyMainLabel()
{
	QLabel * label;
	for (int k = 0; k < GUI::count_section; k++)
	{
		label = findChild<QLabel *>(QStringLiteral("main_label_%1").arg(k));
		if (label == NULL) continue;
		label->destroyed();
		delete label;
	}
}
void GUI::destroyLabelSection()
{
	QLabel * label;
	for (int k = 0; k < GUI::count_section; k++)
	{
		label = findChild<QLabel *>(QStringLiteral("label_section_id_%1").arg(k));
		if (label == NULL) continue;
		label->destroyed();
		delete label;
	}
}
void GUI::destroyTextBox()
{
	QTextBrowser * text_box;
	for (int k = 0; k < GUI::count_section; k++)
	{
		text_box = findChild<QTextBrowser *>(QStringLiteral("box_text_id_%1").arg(k));
		if (text_box == NULL) continue;
		text_box->destroyed();
		delete text_box;
	}
}
void GUI::clearLayout()
{
	QVBoxLayout * lay = findChild<QVBoxLayout *>("q_grid_layout");
	if (lay == NULL) return;
	lay->destroyed();
	delete lay;
}

void GUI::destroyAllScrollArea()
{
	GUI::destroyDynamicSpinBox();
	GUI::destroyMainLabel();
	GUI::destroyAnswerLabel();
	GUI::destroyLabelSection();
	GUI::destroyTextBox();
	GUI::clearLayout();
}
